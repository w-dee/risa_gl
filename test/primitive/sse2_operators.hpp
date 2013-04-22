#include <emmintrin.h>

static bool equals(const __m128i& lhs, const __m128i& rhs)
{
	char bytes[16];
	__m128i result = _mm_cmpeq_epi32(lhs, rhs);
	_mm_storeu_si128(reinterpret_cast<__m128i*>(bytes), result);
	for (int offset = 0; offset < 16; ++offset)
	{
		if (bytes[offset] == 0)
			return false;
	}

	return true;
}

static bool not_equals(const __m128i& lhs, const __m128i& rhs)
{
	return !equals(lhs, rhs);
}
