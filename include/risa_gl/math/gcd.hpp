#ifndef RISA_GCD_HPP_
#define RISA_GCD_HPP_

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType>
		ValueType gcd(ValueType lhs_, ValueType rhs_)
		{
			typedef ValueType value_type;
			value_type lhs = (lhs_ > rhs_ ? lhs_ : rhs_);
			value_type rhs = (lhs_ < rhs_ ? lhs_ : rhs_);

			while (rhs != static_cast<ValueType>(0))
			{
				const value_type temporary = lhs % rhs;
				lhs = rhs;
				rhs = temporary;
			}

			return lhs;
		}
	}
}

#endif /* RISA_GCD_HPP_ */
