#ifndef RISA_MATH_ORTHOGONAL_BASIS_HPP_
#define RISA_MATH_ORTHOGONAL_BASIS_HPP_

#include <risa_gl/math/matrix.hpp>
#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/orthogonal_coordinate_system.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		struct orthogonal_basis
		{
		public:

			typedef value_t value_type;
			typedef matrix<value_type,4,4> matrix_type;
			typedef vector3<value_type> vector_type;
			typedef orthogonal_coordinate_system<value_type> coord_system_type;

			static matrix_type
			make_orthogonal_basis(const coord_system_type source)
			{
				return source.get_transformer();
			}

			static matrix_type
			make_orthogonal_basis(const vector_type& x,
								  const vector_type& y,
								  const vector_type& z)
			{
				return make_orthogonal_basis(coord_system_type(x, y, z));
			}

			static matrix_type
			make_orthogonal_basis(const value_type& x_x,
								  const value_type& x_y,
								  const value_type& x_z,
								  const value_type& y_x,
								  const value_type& y_y,
								  const value_type& y_z,
								  const value_type& z_x,
								  const value_type& z_y,
								  const value_type& z_z)
			{
				return make_orthogonal_basis(vector_type(x_x, x_y, x_z),
											 vector_type(y_x, y_y, y_z),
											 vector_type(z_x, z_y, z_z));
			}

		};
	}
}

#endif /* RISA_MATH_ORTHOGONAL_BASIS_HPP_ */
