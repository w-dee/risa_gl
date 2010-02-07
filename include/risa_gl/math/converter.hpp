#ifndef RISA_MATH_CONVERTER_HPP_
#define RISA_MATH_CONVERTER_HPP_

#include <risa_gl/math/matrix.hpp>
#include <risa_gl/math/vector.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		class converter
		{
		public:
			typedef value_t value_type;
			typedef matrix<value_type,4,4> matrix_type;
			typedef matrix<value_type,1,4> matrix1x4_type;
			typedef matrix<value_type,4,1> matrix4x1_type;

			typedef typename matrix1x4_type::elements_type
				matrix1x4_elements_type;
			typedef typename matrix4x1_type::elements_type
				matrix4x1_elements_type;

			typedef vector2<value_type> vector2_type;
			typedef vector3<value_type> vector3_type;
			typedef vector4<value_type> vector4_type;

			matrix1x4_type to_matrix1x4(const vector2_type& source) const
			{
				matrix1x4_elements_type result =
					{{ source.x, source.y, 0,  1}};
				return result;
			}
		};
	}
}

#endif /* RISA_MATH_CONVERTER_HPP_ */
