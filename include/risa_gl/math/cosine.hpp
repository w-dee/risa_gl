#ifndef RISA_COSINE_HPP_
#define RISA_COSINE_HPP_

#include <risa_gl/math/factorial.hpp>
#include <risa_gl/math/power.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType, int max_depth, int depth>
		struct taylor_expansion_cosine_term
		{
			typedef ValueType real_type;

			static real_type value(const real_type& v)
			{
				const int n = max_depth - depth + 1;
				return (power<real_type, n>::value(-1) *
						power<real_type, n*2>::value(v)) /
					static_cast<real_type>(factorial<n*2>::value) +
					taylor_expansion_cosine_term
					<real_type, max_depth, depth - 1>::value(v);
			}
		};

		template <typename ValueType, int max_depth>
		struct taylor_expansion_cosine_term<ValueType, max_depth, 1>
		{
			typedef ValueType real_type;

			static real_type value(const real_type& /*v*/)
			{
				return static_cast<real_type>(0);
			}
		};

		template <typename ValueType, int calc_depth = 7>
		class cosine
		{
		public:
			typedef ValueType real_type;
	
			static real_type value(real_type arg)
			{
				/**      x^2    x^4     x^6
				 * 1 - ----- + ----- - ----- + ...
				 *       2!      4!     6!
				 *
				 *   1 - \sigma (-1)^n * x^(n*2) / fact(n*2)
				 */

				return static_cast<real_type>(1) + 
					taylor_expansion_cosine_term<real_type,
					calc_depth, calc_depth>::value(arg);
			}
		};

	}
}
#endif /* RISA_COSINE_HPP_ */
