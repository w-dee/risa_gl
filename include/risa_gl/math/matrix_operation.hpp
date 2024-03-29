#ifndef RISA_MATH_MATRIX_OPERATION_HPP_
#define RISA_MATH_MATRIX_OPERATION_HPP_

#include <risa_gl/math/matrix.hpp>
#include <risa_gl/math/matrix_type.hpp>
#include <risa_gl/math/vector.hpp>
#include <cmath>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		class translator
		{
		public:
			typedef value_t value_type;
			typedef risa_gl::math::matrix<value_type, 4, 4> matrix_type;
			typedef risa_gl::math::matrix<value_type, 4, 1> vector_type;
			typedef typename matrix_type::elements_type matrix_source_type;

		public:
			translator()
			{}

			matrix_type
			operator()(value_type x_shift,
					   value_type y_shift,
					   value_type z_shift) const
			{
				matrix_source_type shifter = {{
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						x_shift, y_shift, z_shift, 1
					}};

				return matrix_type(shifter);
			}
		};


		template <typename value_t>
		class rotator
		{
		public:
			typedef value_t value_type;
			typedef risa_gl::math::matrix<value_type, 4, 4> matrix_type;
			typedef risa_gl::math::matrix<value_type, 4, 1> vector_type;
			typedef typename matrix_type::elements_type matrix_source_type;

		public:
			rotator()
			{}

			matrix_type
			operator()(const vector_type axis, value_type angle) const
			{
				const value_type cos_value =
					static_cast<value_type>(std::cos(angle));
				const value_type sin_value =
					static_cast<value_type>(std::sin(angle));

				const value_type x = axis[0];
				const value_type x_2 = x * x;
				const value_type y = axis[1];
				const value_type y_2 = y * y;
				const value_type z = axis[2];
				const value_type z_2 = z * z;
				const value_type invert_cos_value =
					value_type(1) - cos_value;

				matrix_source_type source =
					{{ x_2+(1-x_2) * cos_value,
					   x * y * invert_cos_value+z * sin_value,
					   x * z * invert_cos_value-y * sin_value,
					   0,
					   x * y * invert_cos_value-z * sin_value,
					   y_2+(1-y_2) * cos_value,
					   y * z * invert_cos_value+x * sin_value,
					   0,
					   x * z * invert_cos_value+y * sin_value,
					   y * z * invert_cos_value-x * sin_value,
					   z_2+(1-z_2) * cos_value,
					   0,
					   0,0,0,1}};

				return matrix_type(source);
			}
		};

		template <typename value_type>
		matrix<value_type, 4, 1>
		operator*(const matrix<value_type, 4, 1>& lhs,
				  const matrix<value_type, 4, 4>& rhs)
		{
			typename matrix<value_type, 1, 4>::elements_type elem =
				{{ lhs.x, lhs.y, lhs.z, 1 }};

			matrix<value_type, 1, 4> result = elem;
			result = result * rhs;

			return matrix<value_type, 4, 1>(result[0], result[1], result[2]);
		}

		template <typename value_type>
		vector3<value_type>
		operator*(const vector3<value_type>& lhs,
				  const matrix<value_type, 4, 4>& rhs)
		{
			typename matrix<value_type, 4, 1>::elements_type elem =
				{{ lhs.x, lhs.y, lhs.z, 1 }};

			matrix<value_type, 1, 4> result = elem;
			result = result * rhs;

			return vector3<value_type>(result[0], result[1], result[2]);
		}

		template <typename value_type>
		vector4<value_type>
		operator*(const vector4<value_type>& lhs,
				  const matrix<value_type, 4, 4>& rhs)
		{
			typename matrix<value_type, 4, 1>::elements_type elem =
				{{ lhs.x, lhs.y, lhs.z, lhs.w }};

			matrix<value_type, 1, 4> result = elem;
			result = result * rhs;

			return vector4<value_type>(result[0], result[1],
									   result[2], result[3]);
		}
	}
}

#endif /* RISA_MATH_MATRIX_OPERATION_HPP_ */
