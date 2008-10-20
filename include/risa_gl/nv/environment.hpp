#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include <risa_gl/pixel.hpp>

namespace environments
{
	struct cplusplus
	{
		typedef unsigned int bit_pattern_type;
		typedef risa_gl::pixel basic_input_type;
	};

#	ifdef x64
	struct x64
	{
		typedef unsigned long long bit_pattern_type;
		typedef pixel_t basic_input_type;
	};
#	endif /* x64 */

#	ifdef SSE2
#include <emmintrinsic.h>
	struct sse2
	{
		typedef _m128 bit_pattern_type;
		typedef pixel_t basic_input_type;
	};
#	endif /* SSE2 */

}

#endif /* ENVIRONMENT_HPP_ */
