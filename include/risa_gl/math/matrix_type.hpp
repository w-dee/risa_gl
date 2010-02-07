#ifndef RISA_MATH_MATRIX_TYPE_HPP_
#define RISA_MATH_MATRIX_TYPE_HPP_
#include <risa_gl/math/matrix.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		class matrix4x4
		{
		public:
			typedef matrix<value_t, 4, 4> type;
		};

		template <typename value_t>
		class matrix1x4
		{
		public:
			typedef matrix<value_t, 1, 4> type;
		};
	}
}

#endif /* RISA_MATH_MATRIX_TYPE_HPP_ */
