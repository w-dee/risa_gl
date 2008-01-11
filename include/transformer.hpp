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
			const float cosine_result = std::cos(angle);
			const float sine_result = std::sin(angle);
			const float x_factor = axis.x;
			const float y_factor = axis.y;
			const float z_factor = axis.z;

			const float x_cos = x_factor * cosine_result;
			const float x_sin = x_factor * sine_result;
			const float y_cos = y_factor * cosine_result;
			const float y_sin = y_factor * sine_result;
			const float z_cos = z_factor * cosine_result;
			const float z_sin = z_factor * sine_result;

			matrix_t::elements_type rotator =
				{ z_cos + y_cos, z_sin, -y_sin, 0,
				  -z_sin, z_cos + x_cos, x_sin, 0,
				  y_sin, -x_sin, y_cos + x_cos, 0,
				  0, 0, 0, 1};

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
	};
}


#endif /* RISA_ITERATOR_HPP_ */
