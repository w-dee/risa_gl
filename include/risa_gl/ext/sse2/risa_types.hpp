#ifndef RISA_EXT_SSE2_RISA_TYPES_HPP_
#define RISA_EXT_SSE2_RISA_TYPES_HPP_

#include <emmintrin.h>
#include <risa_gl/static_array.hpp>

namespace risa_gl
{
	namespace ext 
	{
		namespace sse2
		{
			typedef __m128i aligned_wideword_type;
			typedef risa_gl::static_array<unsigned char, 16>
			unaligned_wideword_type;

			template <typename T>
			struct type_traits
			{
				typedef typename T::value_type value_type;
			};

			template <typename T>
			struct type_traits<T*>
			{
				typedef T value_type;
			};
		}
	}
}
#endif /* RISA_EXT_SSE2_RISA_TYPES_HPP_ */
