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

	private:
		matrix_t matrix;

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

	private:
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
		math::region<BaseType>
		operator*(const math::region<BaseType>& src) const
		{
			typedef math::region<BaseType> region_t;
			typedef typename region_t::coord_type coord_t;
		
			const coord_t left_up =
				*this * coord_t(src.get_left(), src.get_top());
			const coord_t right_bottom =
				*this * coord_t(src.get_right(), src.get_bottom());

			return region_t(
				left_up.get_x(), left_up.get_y(),
				right_bottom.get_x(), right_bottom.get_y());
		}
	};
}


#endif /* RISA_ITERATOR_HPP_ */
