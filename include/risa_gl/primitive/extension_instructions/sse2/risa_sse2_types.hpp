#ifndef RISA_SSE2_TYPES_HPP_
#define RISA_SSE2_TYPES_HPP_

#include <emmintrin.h>
#include <risa_gl/static_array.hpp>

namespace risa_gl
{
	namespace ext_instruction 
	{
		namespace sse2
		{
			typedef __m128i word_type;
			typedef risa_gl::static_array<unsigned char, 16> native_word_type;
		}
	}
}
#endif /* RISA_SSE2_TYPES_HPP_ */
