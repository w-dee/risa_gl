#ifndef RISA_TRANSFORMER_HPP_
#define RISA_TRANSFORMER_HPP__

#include <rectangle.hpp>
#include <iterator.hpp>
#include <math/vector.hpp>
#include <math/region.hpp>
#include <math/matrix.hpp>
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
		vector2_to_matrix_vector(const math::vector2& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.x;
			result(0,1) = coord.y;
			result(0,2) = 0;
			result(0,3) = 1;

			return result;
		}

		vector2
		matrix_vector_to_vector2(const matrix_vector& coord) const
		{
			return vector2(coord(0,0), coord(0,1));
		}
			
		matrix_vector 
		vector3_to_matrix_vector(const math::vector3& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.x;
			result(0,1) = coord.y;
			result(0,2) = coord.z;
			result(0,3) = 1;

			return result;
		}

		vector3
		matrix_vector_to_vector3(const matrix_vector& coord) const
		{
			return vector3(coord(0,0), coord(0,1), coord(0,2));
		}

		matrix_vector 
		vector4_to_matrix_vector(const math::vector4& coord) const
		{
			matrix_vector result;

			result(0,0) = coord.x;
			result(0,1) = coord.y;
			result(0,2) = coord.z;
			result(0,3) = coord.w;

			return result;
		}

		vector4
		matrix_vector_to_vector4(const matrix_vector& coord) const
		{
			return vector4(coord(0,0), coord(0,1), coord(0,2), coord(0,3));
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
				{ x_scale, 0, 0, 0,
				  0, y_scale, 0, 0,
				  0, 0, z_scale, 0,
				  0, 0, 0, 1 };

			this->matrix = matrix_t(scaler) * this->matrix;
		}

		void translate(float x_shift, float y_shift, float z_shift)
		{
			matrix_t::elements_type shifter = 
				{       1,       0,       0, 0,
				        0,       1,       0, 0,
				        0,       0,       1, 0,
				  x_shift, y_shift, z_shift, 1 };

			this->matrix = matrix_t(shifter) * this->matrix;
		}

		void rotate(const vector3& axis, float angle)
		{
			const vector3 normed_axis = axis.get_norm();
			const float cos_ = std::cos(angle);
			const float sin_ = std::sin(angle);
			const float x = normed_axis.x;
			const float y = normed_axis.y;
			const float z = normed_axis.z;
			const float x_2 = x * x;
			const float y_2 = y * y;
			const float z_2 = z * z;

			matrix_t::elements_type rotator =
				{ x_2+(1-x_2)*cos_, x*y*(1-cos_)+z*sin_, x*z*(1-cos_)-y*sin_, 0,
				  x*y*(1-cos_)-z*sin_, y_2+(1-y_2)*cos_, y*z*(1-cos_)+x*sin_, 0,
				  x*z*(1-cos_)+y*sin_, y*z*(1-cos_)-x*sin_, z_2+(1-z_2)*cos_, 0,
				  0,0,0,1};
				  
			this->matrix = matrix_t(rotator) * this->matrix;
		}

		math::vector2 operator*(const math::vector2& coord) const
		{
			return matrix_vector_to_vector2(
				vector2_to_matrix_vector(coord) * this->matrix);
		}

		math::vector3 operator*(const math::vector3& coord) const
		{
			return matrix_vector_to_vector3(
				vector3_to_matrix_vector(coord) * this->matrix);
		}

		math::vector4 operator*(const math::vector4& coord) const
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

			return region_t(left_up, right_up, left_down, right_down);
		}

		template <typename BaseType>
		static const math::rectangle_region<BaseType>
		transform(const math::rectangle_region<BaseType>& region,
				  const math::vector2& center,
				  const float angle)
		{
			linear_transformer transformer;
			transformer.translate(-center.x, -center.y, 0.f);
			transformer.rotate(math::vector3(0.f, 0.f, 1.f), angle);
			transformer.translate(center.x, center.y, 0.f);

			return transformer * region;
		}
	};

	template <typename PixelStoreType,
			  typename InterpolateType>
	class basic_transformer
	{
	public:
		typedef PixelStoreType pixel_store_type;
		typedef InterpolateType interpolate_type;
		typedef math::rectangle_region<float> region_type;
		typedef std::vector<typename interpolate_type::pixel_vector_type>
		fragments_type;

	protected:
		linear_transformer transformer;

	private:
		const region_type region;
		
		const math::vector2
		coord_to_vector2(const region_type::coord_type& coord) const
		{
			return math::vector2(coord.get_x(), coord.get_y());
		}

	public:
		basic_transformer(const region_type& region_):
			transformer(),
			region(region_)
		{}

		basic_transformer(const basic_transformer& src):
			transformer(src.transformer),
			region(src.region)
		{}

		fragments_type get_fragments(const pixel_store_type& pixels,
									 const int x_divide,
									 const int y_divide) const
		{
			assert (x_divide >= 2);
			assert (y_divide >= 2);

			const math::dividable_vector<math::vector2> y_heads
				(coord_to_vector2(transformer * region.get_left_down()),
				 coord_to_vector2(transformer * region.get_left_up()));
			const math::dividable_vector<math::vector2> y_tails
				(coord_to_vector2(transformer * region.get_right_down()),
				 coord_to_vector2(transformer * region.get_right_up()));
			
			fragments_type result(y_divide);

			result[0] = interpolate_type(pixels,
										 y_heads.blend(0.f),
										 y_tails.blend(0.f),
										 x_divide).interpolate();
			
			const float jitter = 1.f / static_cast<float>(x_divide - 1);
			float offset = jitter;
			for (unsigned short y_div = 1; y_div != (y_divide - 1);
				 ++y_div, offset += jitter)
			{
				result[y_div] = interpolate_type(pixels,
												 y_heads.blend(offset),
												 y_tails.blend(offset),
												 x_divide).interpolate();
			}

			result[y_divide-1] = interpolate_type(pixels,
												  y_heads.blend(1.f),
												  y_tails.blend(1.f),
												  x_divide).interpolate();

			return result;
		}
	};

	template <typename PixelStoreType,
			  typename InterpolateType>
	class rotator :
		public basic_transformer<PixelStoreType, InterpolateType>
	{
	public:
		typedef basic_transformer<PixelStoreType, InterpolateType> super_type;
		typedef typename super_type::pixel_store_type pixel_store_type;
		typedef typename super_type::interpolate_type interpolate_type;
		typedef typename super_type::region_type region_type;
		typedef typename super_type::fragments_type fragments_type;

		rotator(const region_type& region,
				const math::vector2& center,
				const float angle):
			super_type(region)
		{
			super_type::transformer.translate(center.x, center.y, 0);
			super_type::transformer.rotate(math::vector3(0.f, 0.f, 1.f), angle);
			super_type::transformer.translate(-center.x, -center.y, 0);
		}

		rotator(const rotator& src):
			super_type(src)
		{}

		fragments_type get_fragments(const pixel_store_type& pixels,
									 const int x_divide,
									 const int y_divide) const
		{
			return super_type::get_fragments(pixels, x_divide, y_divide);
		}
	};

	template <typename PixelStoreType,
			  typename InterpolateType>
	class scaler :
		public basic_transformer<PixelStoreType, InterpolateType>
	{
	public:
		typedef basic_transformer<PixelStoreType, InterpolateType> super_type;
		typedef typename super_type::pixel_store_type pixel_store_type;
		typedef typename super_type::interpolate_type interpolate_type;
		typedef typename super_type::region_type region_type;
		typedef typename super_type::fragments_type fragments_type;

		scaler(const region_type& region,
			   const math::vector2& center,
			   const float x_scale,
			   const float y_scale):
			super_type(region)
		{
			super_type::transformer.translate(-center.x, -center.y, 0);
			super_type::transformer.scaling(x_scale, y_scale, 1.f);
			super_type::transformer.translate(center.x, center.y, 0);
		}

		scaler(const scaler& src):
			super_type(src)
		{}

		fragments_type get_fragments(const pixel_store_type& pixels,
									 const int x_divide,
									 const int y_divide) const
		{
			return super_type::get_fragments(pixels, x_divide, y_divide);
		}
	};

	template <typename PixelStoreType,
			  typename InterpolateType>
	class translator :
		public basic_transformer<PixelStoreType, InterpolateType>
	{
	public:
		typedef basic_transformer<PixelStoreType, InterpolateType> super_type;
		typedef typename super_type::pixel_store_type pixel_store_type;
		typedef typename super_type::interpolate_type interpolate_type;
		typedef typename super_type::region_type region_type;
		typedef typename super_type::fragments_type fragments_type;

		translator(const region_type& region,
				   const math::vector2& translations):
			super_type(region)
		{
			super_type::transformer.translate(translations.x,
											  translations.y, 0);
		}

		translator(const translator& src):
			super_type(src)
		{}

		fragments_type get_fragments(const pixel_store_type& pixels,
									 const int x_divide,
									 const int y_divide) const
		{
			return super_type::get_fragments(pixels, x_divide, y_divide);
		}
	};

}


#endif /* RISA_ITERATOR_HPP_ */
