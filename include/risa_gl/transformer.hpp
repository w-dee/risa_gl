#ifndef RISA_TRANSFORMER_HPP_
#define RISA_TRANSFORMER_HPP_

#include <risa_gl/rectangle.hpp>
#include <risa_gl/iterator.hpp>
#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/region.hpp>
#include <risa_gl/math/matrix.hpp>
#include <risa_gl/math/differential.hpp>
#include <vector>

namespace risa_gl
{
	using  risa_gl::math::vector2;
	using  risa_gl::math::vector3;
	using  risa_gl::math::vector4;
	using  risa_gl::math::coordinate;

	class linear_transformer
	{
	public:
		typedef math::matrix<float, 4, 4> matrix_t;
		typedef math::matrix<float, 1, 4> matrix_vector;
		typedef matrix_t::elements_type elements_type;

	private:
		matrix_t matrix;

		template <typename BaseType>
		matrix_vector
		coordinate_to_matrix_vector(const coordinate<BaseType>& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.get_x();
			result(0,1) = coord.get_y();
			result(0,2) = 0;
			result(0,3) = 1;

			return result;
		}

		template <typename BaseType>
		coordinate<BaseType>
		matrix_vector_to_coordinate(const matrix_vector& coord) const
		{
			return coordinate<BaseType>(coord(0,0), coord(0,1));
		}

		matrix_vector 
		vector2_to_matrix_vector(const math::vector2<float>& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.x;
			result(0,1) = coord.y;
			result(0,2) = 0;
			result(0,3) = 1;

			return result;
		}

		vector2<float>
		matrix_vector_to_vector2(const matrix_vector& coord) const
		{
			return vector2<float>(coord(0,0), coord(0,1));
		}
			
		matrix_vector 
		vector3_to_matrix_vector(const math::vector3<float>& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.x;
			result(0,1) = coord.y;
			result(0,2) = coord.z;
			result(0,3) = 1;

			return result;
		}

		vector3<float>
		matrix_vector_to_vector3(const matrix_vector& coord) const
		{
			return vector3<float>(coord(0,0), coord(0,1), coord(0,2));
		}

		matrix_vector 
		vector4_to_matrix_vector(const math::vector4<float>& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.x;
			result(0,1) = coord.y;
			result(0,2) = coord.z;
			result(0,3) = coord.w;

			return result;
		}

		vector4<float>
		matrix_vector_to_vector4(const matrix_vector& coord) const
		{
			return vector4<float>(coord(0,0), coord(0,1), coord(0,2), coord(0,3));
		}

	public:
		linear_transformer():
			matrix()
		{}

		linear_transformer(const matrix_t::elements_type& elements):
			matrix(elements)
		{}

		linear_transformer(const linear_transformer& src):
			matrix(src.matrix)
		{}

		~linear_transformer()
		{}

		void scaling(float x_scale, float y_scale, float z_scale)
		{
			matrix_t::elements_type scaler =
				{ { x_scale, 0, 0, 0,
					0, y_scale, 0, 0,
					0, 0, z_scale, 0,
					0, 0, 0, 1 } };

			this->matrix = this->matrix * matrix_t(scaler);
		}

		void translate(float x_shift, float y_shift, float z_shift)
		{
			matrix_t::elements_type shifter = 
				{ {       1,       0,       0, 0,
						  0,       1,       0, 0,
						  0,       0,       1, 0,
						  x_shift, y_shift, z_shift, 1 } };

			this->matrix = this->matrix * matrix_t(shifter);
		}

		void rotate(const vector3<float>& axis, float angle)
		{
			const vector3<float> normed_axis = axis.get_norm();
			const float cos_ = std::cos(angle);
			const float sin_ = std::sin(angle);
			const float x = normed_axis.x;
			const float y = normed_axis.y;
			const float z = normed_axis.z;
			const float x_2 = x * x;
			const float y_2 = y * y;
			const float z_2 = z * z;

			matrix_t::elements_type rotator =
				{ { x_2+(1-x_2)*cos_, x*y*(1-cos_)+z*sin_,
					x*z*(1-cos_)-y*sin_, 0,
					x*y*(1-cos_)-z*sin_, y_2+(1-y_2)*cos_,
					y*z*(1-cos_)+x*sin_, 0,
					x*z*(1-cos_)+y*sin_, y*z*(1-cos_)-x*sin_,
					z_2+(1-z_2)*cos_, 0,
					0,0,0,1} };
				  
			this->matrix = this->matrix * matrix_t(rotator);
		}

		math::vector2<float> operator*(const math::vector2<float>& coord) const
		{
			return matrix_vector_to_vector2(
				vector2_to_matrix_vector(coord) * this->matrix);
		}

		math::vector3<float> operator*(const math::vector3<float>& coord) const
		{
			return matrix_vector_to_vector3(
				vector3_to_matrix_vector(coord) * this->matrix);
		}

		math::vector4<float> operator*(const math::vector4<float>& coord) const
		{
			return matrix_vector_to_vector4(
				vector4_to_matrix_vector(coord) * this->matrix);
		}

		template <typename BaseType>
		math::coordinate<BaseType>
		operator*(const math::coordinate<BaseType>& src) const
		{
			return matrix_vector_to_coordinate<BaseType>(
				coordinate_to_matrix_vector(src) * this->matrix);
		}

		template <typename BaseType>
		math::rectangle_region<BaseType>
		operator*(const math::rectangle_region<BaseType>& src) const
		{
			typedef math::rectangle_region<BaseType> region_t;
			typedef typename region_t::coord_type coord_t;
		
			const coord_t left_up    = *this * src.get_left_up();
			const coord_t right_up   = *this * src.get_right_up();
			const coord_t left_down  = *this * src.get_left_down();
			const coord_t right_down = *this * src.get_right_down();

			return region_t(left_down, right_down, left_up, right_up);
		}

		template <typename BaseType>
		static const math::rectangle_region<BaseType>
		transform(const math::rectangle_region<BaseType>& region,
				  const math::vector2<float>& center,
				  const float angle)
		{
			linear_transformer transformer;
			transformer.translate(-center.x, -center.y, 0.f);
			transformer.rotate(math::vector3<float>(0.f, 0.f, 1.f), angle);
			transformer.translate(center.x, center.y, 0.f);

			return transformer * region;
		}
	};

	template <typename ValueType = float>
	class basic_transformer
	{
	public:
		typedef ValueType value_type;
		typedef math::rectangle_region<value_type> region_type;
		typedef typename region_type::coord_type coord_type;

		template <typename ValueType_>
		class projected_region
		{
		public:
			typedef math::rectangle_region<ValueType_> region_type;
			typedef typename region_type::coord_type coord_type;

		private:
			region_type region;
			coord_type x_difference;
			coord_type y_difference;

		public:
			projected_region(const region_type& region_,
							 const coord_type& x_diff,
							 const coord_type& y_diff):
				region(region_),
				x_difference(x_diff),
				y_difference(y_diff)
			{}

			region_type get_region() const
			{
				return region;
			}

			coord_type get_x_difference() const
			{
				return
					coord_type(x_difference.get_x() -
							   region.get_left_down().get_x(),
							   x_difference.get_y() -
							   region.get_left_down().get_y());
			}

			coord_type get_y_difference() const
			{
				return
					coord_type(y_difference.get_x() -
							   region.get_left_down().get_x(),
							   y_difference.get_y() -
							   region.get_left_down().get_y());
			}
		};

		typedef projected_region<value_type> projected_type;

	protected:
		linear_transformer transformer;

	private:
		const region_type region;
		coord_type x_variation;
		coord_type y_variation;
		
		const math::vector4<float>
		coord_to_vector4(const typename region_type::coord_type& coord) const
		{
			return math::vector4<float>(coord.get_x(), coord.get_y(), 0, 1);
		}

	public:
		basic_transformer(const region_type& region_,
						  const value_type& x_diff = 1,
						  const value_type& y_diff = 1):
			transformer(),
			region(region_),
			x_variation(region.get_left_down().get_x() + x_diff,
						region.get_left_down().get_y()),
			y_variation(region.get_left_down().get_x(),
						region.get_left_down().get_y() + y_diff)
		{}

		basic_transformer(const basic_transformer& src):
			transformer(src.transformer),
			region(src.region),
			x_variation(src.x_variation),
			y_variation(src.y_variation)
		{}

		region_type get_transformed_region() const
		{
			return transformer * region;
		}

		coord_type get_transformed_x_variation() const
		{
			return (transformer * x_variation);
		}

		coord_type get_transformed_y_variation() const
		{
			return (transformer * y_variation);
		}

		projected_type get_projected_region() const
		{
			return projected_type(
				get_transformed_region(),
				get_transformed_x_variation(),
				get_transformed_y_variation());
		}
	};

	template <typename ValueType>
	class rotator :
		public basic_transformer<ValueType>
	{
	public:
		typedef basic_transformer<ValueType> super_type;
		typedef typename super_type::region_type region_type;
		typedef typename super_type::projected_type projected_type;

		rotator(const region_type& region,
				const math::vector2<float>& center,
				const float angle):
			super_type(region)
		{
			super_type::transformer.translate(-center.x, -center.y, 0);
			super_type::transformer.rotate(math::vector3<float>(0.f, 0.f, 1.f),
										   angle);
			super_type::transformer.translate(center.x, center.y, 0);
		}

		rotator(const rotator& src):
			super_type(src)
		{}

		projected_type get_projected_region() const
		{
			return super_type::get_projected_region();
		}
		
	};

	template <typename ValueType>
	class scaler :
		public basic_transformer<ValueType>
	{
	public:
		typedef basic_transformer<ValueType> super_type;
		typedef typename super_type::region_type region_type;
		typedef typename super_type::projected_type projected_type;

		scaler(const region_type& region,
			   const math::vector2<float>& center,
			   const float x_scale,
			   const float y_scale,
			   const int x_stepping = 1,
			   const int y_stepping = 1):
			super_type(region, x_stepping, y_stepping)
		{
			super_type::transformer.translate(-center.x, -center.y, 0);
			super_type::transformer.scaling(x_scale, y_scale, 1.f);
			super_type::transformer.translate(center.x, center.y, 0);
		}

		scaler(const scaler& src):
			super_type(src)
		{}

		projected_type get_projected_region() const
		{
			return super_type::get_projected_region();
		}
		
	};

	template <typename ValueType>
	class translator :
		public basic_transformer<ValueType>
	{
	public:
		typedef basic_transformer<ValueType> super_type;
		typedef typename super_type::region_type region_type;
		typedef typename super_type::projected_type projected_type;

		translator(const region_type& region,
				   const math::vector2<float>& translations):
			super_type(region)
		{
			super_type::transformer.translate(translations.x,
											  translations.y, 0);
		}

		translator(const translator& src):
			super_type(src)
		{}

		projected_type get_projected_region() const
		{
			return super_type::get_projected_region();
		}
		
	};
}


#endif /* RISA_ITERATOR_HPP_ */
