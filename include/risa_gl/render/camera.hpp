#ifndef RISA_RENDER_CAMERA_HPP_
#define RISA_RENDER_CAMERA_HPP_

#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/operators.hpp>
#include <risa_gl/math/matrix.hpp>
#include <risa_gl/math/orthogonal_coordinate_system.hpp>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class camera
		{
		public:
			typedef value_t value_type;
			typedef typename math::matrix<value_type,4,4> matrix_type;
			typedef typename math::vector3<value_type> vector3_type;

		private:
			typedef risa_gl::math::orthogonal_coordinate_system<value_type>
			eye_rotate_type;

			vector3_type position;
			vector3_type up;
			vector3_type object;

		public:
			camera(const vector3_type& position_,
				   const vector3_type& up_,
				   const vector3_type& object_):
				position(position_),
				up(up_),
				object(object_)
			{}


			matrix_type
			get_matrix() const
			{
				const vector3_type base_shift = -position;

				const vector3_type eye = (object - position).get_norm();
				const vector3_type eye_up = up.get_norm();
				const vector3_type eye_left =
					risa_gl::math::cross_product(eye, eye_up);
				
				eye_rotate_type eye_rotate(eye_left, eye_up, eye);
				typename matrix_type::elements_type shifter = 
					{ {       1,       0,       0, 0,
							  0,       1,       0, 0,
							  0,       0,       1, 0,
							  base_shift.x, base_shift.y, base_shift.z, 1 } };

				return matrix_type(shifter) * eye_rotate.get_transformer();
			}
		};
	}
}

#endif /* RISA_RENDER_CAMERA_HPP_ */
