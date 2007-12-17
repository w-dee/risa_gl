#ifndef RISA_COSINE_HPP_
#define RISA_COSINE_HPP_

#include <cmath>
#include <math/factorial.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType, int max_depth, int depth>
		struct cosine_recirsive_implement
		{
			typedef ValueType value_type;

			static value_type get_value(const value_type& v)
			{
				const int n = max_depth - depth + 1;
				return ((-1 * n) /
						(static_cast<value_type>(factorial<n*2>::value) * 
						 std::pow(v, n*2))) +
					cosine_recirsive_implement
					<value_type, max_depth, depth - 1>::get_value(v);
			}
		};

		template <typename ValueType, int max_depth>
		struct cosine_recirsive_implement<ValueType, max_depth, 1>
		{
			typedef ValueType value_type;

			static value_type get_value(const value_type& /*v*/)
			{
				return static_cast<value_type>(0);
			}
		};

		template <typename ValueType, int calc_depth = 4>
		class cosine
		{
		public:
			typedef ValueType value_type;
	
			static value_type get(value_type arg)
			{
				/**      1       1       1
				 * 1 - ----- + ----- - ----- + ...
				 *    2!x^2    4!x^4   6!x^6
				 *
				 *   1 - \sigma (-1)*n / fact(n*2)*x^(n*2)
				 */

				return static_cast<value_type>(1) - 
					cosine_recirsive_implement<value_type,
					calc_depth, calc_depth>::get_value(arg);
			}
		};

	}
}
#endif /* RISA_COSINE_HPP_ */
