#ifndef RISA_LCM_HPP_
#define RISA_LCM_HPP_

#include <risa_gl/math/gcd.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType>
		ValueType lcm(ValueType lhs, ValueType rhs)
		{
			return lhs * rhs / gcd(lhs, rhs);
		}
	}
}
#endif /* RISA_LCM_HPP_ */
