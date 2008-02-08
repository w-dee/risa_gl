#ifndef RISA_SINE_HPP_
#define RISA_SINE_HPP_

#include <risa_gl/math/cosine.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType, int calc_depth = 7>
		class sine
		{
		public:
			typedef ValueType real_type;
	
			static real_type value(real_type arg)
			{
				return cosine<real_type, calc_depth>::
					value(arg - pi() / static_cast<real_type>(2));
			}

		private:
			static real_type pi()
			{
				return static_cast<real_type>(3.1415926535897932384);
			}
			
		};
	}
}

#endif /* RISA_SINE_HPP_ */

