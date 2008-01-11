#ifndef RISA_COSINE_HPP_
#define RISA_COSINE_HPP_

#include <cmath>
#include <math/factorial.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType, int max_depth, int depth>
		struct cosine_recursive_implement
		{
			typedef ValueType value_type;

			static value_type get_value(const value_type& v)
			{
				const int n = max_depth - depth + 1;
				return (std::pow(-1.0, n) * std::pow(v, n*2)) /
					static_cast<value_type>(factorial<n*2>::value) +
					cosine_recursive_implement
					<value_type, max_depth, depth - 1>::get_value(v);
			}
		};

		template <typename ValueType, int max_depth>
		struct cosine_recursive_implement<ValueType, max_depth, 1>
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
				/**      x^2    x^4     x^6
				 * 1 - ----- + ----- - ----- + ...
				 *       2!      4!     6!
				 *
				 *   1 - \sigma (-1)^n * x^(n*2) / fact(n*2)
				 */

				return static_cast<value_type>(1) + 
					cosine_recursive_implement<value_type,
					calc_depth, calc_depth>::get_value(arg);
			}
		};

	}
}
#endif /* RISA_COSINE_HPP_ */