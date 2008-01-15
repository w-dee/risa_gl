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

}


#endif /* RISA_ITERATOR_HPP_ */
