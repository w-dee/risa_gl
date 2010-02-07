#ifndef RISA_MATH_ORTHOGONAL_COORDINATE_SYSTEM_HPP_
#define RISA_MATH_ORTHOGONAL_COORDINATE_SYSTEM_HPP_

#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/matrix.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		class orthogonal_coordinate_system
		{
		public:
			typedef value_t value_type;
			typedef vector3<value_type> axis_type;
			typedef matrix<value_type, 4, 4> matrix_type;

		private:
			axis_type x_axis;
			axis_type y_axis;
			axis_type z_axis;

		public:
			orthogonal_coordinate_system(const value_type& x_x,
										 const value_type& x_y,
										 const value_type& x_z,
										 const value_type& y_x,
										 const value_type& y_y,
										 const value_type& y_z,
										 const value_type& z_x,
										 const value_type& z_y,
										 const value_type& z_z):
				x_axis(x_x, x_y, x_z),
				y_axis(y_x, y_y, y_z),
				z_axis(z_x, z_y, z_z)
			{}

			orthogonal_coordinate_system(const vector3<value_type>& x_axis_,
										 const vector3<value_type>& y_axis_,
										 const vector3<value_type>& z_axis_):
				x_axis(x_axis_),
				y_axis(y_axis_),
				z_axis(z_axis_)
			{}
				
			axis_type get_x_axis() const
			{
				return x_axis;
			}

			axis_type get_y_axis() const
			{
				return y_axis;
			}

			axis_type get_z_axis() const
			{
				return z_axis;
			}

			matrix_type get_transformer() const
			{
				typename matrix_type::elements_type result_source = {{
					 x_axis.x, x_axis.y, x_axis.z, 0,
					 y_axis.x, y_axis.y, y_axis.z, 0,
					 z_axis.x, z_axis.y, z_axis.z, 0,
					 0, 0, 0, 1 }};

				return result_source;
			}
		};
	}
}

#endif /* RISA_MATH_ORTHOGONAL_COORDINATE_SYSTEM_HPP_ */
