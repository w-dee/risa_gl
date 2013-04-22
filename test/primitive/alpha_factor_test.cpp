#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/ext/sse2/primitive/alpha_factor.hpp>

#include "sse2_operators.hpp"
#include "../range.hpp"

class alpha_factor_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(alpha_factor_test);
	CPPUNIT_TEST(c_identity_alpha_factor_test);
	CPPUNIT_TEST(c_zero_alpha_factor_test);
	CPPUNIT_TEST(c_alpha_factor_test);
	CPPUNIT_TEST(c_inverse_alpha_factor_test);
	CPPUNIT_TEST(c_scale_factor_test);
	CPPUNIT_TEST(c_scaled_alpha_selector_test);
	CPPUNIT_TEST(c_invert_alpha_factor_test);
	CPPUNIT_TEST(c_scaled_invert_alpha_selector_test);
	CPPUNIT_TEST(c_full_transparent_alpha_factor_test);
	CPPUNIT_TEST(c_constant_alpha_factor_test);
	CPPUNIT_TEST(c_invert_constant_alpha_factor_test);

	CPPUNIT_TEST(sse2_identity_alpha_factor_test);
	CPPUNIT_TEST(sse2_zero_alpha_factor_test);
	CPPUNIT_TEST(sse2_alpha_factor_test);
	CPPUNIT_TEST(sse2_inverse_alpha_factor_test);
	CPPUNIT_TEST(sse2_scale_factor_test);
	CPPUNIT_TEST(sse2_scaled_alpha_selector_test);
	CPPUNIT_TEST(sse2_invert_alpha_factor_test);
	CPPUNIT_TEST(sse2_scaled_invert_alpha_selector_test);
	CPPUNIT_TEST(sse2_full_transparent_alpha_factor_test);
	CPPUNIT_TEST(sse2_constant_alpha_factor_test);
	CPPUNIT_TEST(sse2_invert_constant_alpha_factor_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void c_identity_alpha_factor_test()
	{
		using risa_gl::primitive::identity_alpha_factor;
		identity_alpha_factor factor;
		CPPUNIT_ASSERT_EQUAL(factor(1, 2), 256u);
	}

	void c_zero_alpha_factor_test()
	{
		using risa_gl::primitive::zero_alpha_factor;
		zero_alpha_factor factor;
		CPPUNIT_ASSERT_EQUAL(factor(1, 2), 0u);
	}

	class lhs_selector
	{
	public:
		template <typename T>
		T operator()(T lhs, T rhs) const
		{
			return lhs;
		}
	};

	class identity_selector
	{
	public:
		template <typename T>
		T operator()(T value) const
		{
			return value;
		}
	};

	void c_alpha_factor_test()
	{
		using risa_gl::primitive::alpha_factor;
		alpha_factor<lhs_selector, identity_selector> factor;
		CPPUNIT_ASSERT_EQUAL(factor(1u, 2u), 1u);
	}

	void c_inverse_alpha_factor_test()
	{
		using risa_gl::primitive::inverse_alpha_factor;
		inverse_alpha_factor<lhs_selector, identity_selector> factor;
		CPPUNIT_ASSERT_EQUAL(factor(1u, 2u), 256u);
	}

	void c_scale_factor_test()
	{
		using risa_gl::primitive::scale_factor;
		scale_factor<0, 4, 0, 100> factor;
		CPPUNIT_ASSERT_EQUAL(factor(0u), 0u);
		CPPUNIT_ASSERT_EQUAL(factor(1u), 25u);
		CPPUNIT_ASSERT_EQUAL(factor(2u), 50u);
		CPPUNIT_ASSERT_EQUAL(factor(3u), 75u);
		CPPUNIT_ASSERT_EQUAL(factor(4u), 100u);
	}

	void c_scaled_alpha_selector_test()
	{
		using risa_gl::primitive::scaled_alpha_selector;
		scaled_alpha_selector<0, 4, 0, 100, lhs_selector, identity_selector> selector;
		for (int offset = 0; offset < 5; ++offset)
		{
			CPPUNIT_ASSERT_EQUAL(selector(offset, 4 - offset), offset * 25u);
		}
	}

	void c_invert_alpha_factor_test()
	{
		using risa_gl::primitive::invert_alpha_factor;
		invert_alpha_factor<lhs_selector, identity_selector> factor;
		for (int index = 1; index <= 256; ++index)
			CPPUNIT_ASSERT_EQUAL(factor(index, 0), 257u - index);
	}

	void c_scaled_invert_alpha_selector_test()
	{
		using risa_gl::primitive::scaled_invert_alpha_selector;
		scaled_invert_alpha_selector<1, 256, 0, 255, lhs_selector, identity_selector> factor;
		for (int index = 1; index <= 256; ++index)
		{
			CPPUNIT_ASSERT_EQUAL(factor(index, 0), 256u - index);
		}
	}

	void c_full_transparent_alpha_factor_test()
	{
		using risa_gl::primitive::full_transparent_alpha_factor;
		full_transparent_alpha_factor factor;
		CPPUNIT_ASSERT_EQUAL(factor(34, 45), 1u);
	}

	void c_constant_alpha_factor_test()
	{
		using risa_gl::primitive::constant_alpha_factor;
		{
			constant_alpha_factor factor;
			CPPUNIT_ASSERT_EQUAL(factor(1, 2), 256u);
		}

		{
			constant_alpha_factor factor(123);
			CPPUNIT_ASSERT_EQUAL(factor(1, 2), 123u);
		}
	}

	void c_invert_constant_alpha_factor_test()
	{
		using risa_gl::primitive::invert_constant_alpha_factor;
		{
			invert_constant_alpha_factor factor;
			CPPUNIT_ASSERT_EQUAL(factor(100, 200), 1u);
		}

		{
			invert_constant_alpha_factor factor(201);
			CPPUNIT_ASSERT_EQUAL(factor(100, 200), 56u);
		}
	}


	void sse2_identity_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::identity_alpha_factor;
		identity_alpha_factor factor;
		__m128i actual = factor(_mm_setzero_si128(), _mm_setzero_si128());
		const __m128i& expect = _mm_set1_epi32(0x00010000u);

		CPPUNIT_ASSERT(equals(actual, expect));
	}

	void sse2_zero_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::zero_alpha_factor;
		zero_alpha_factor factor;
		CPPUNIT_ASSERT(equals(factor(_mm_setzero_si128(), _mm_setzero_si128()), _mm_setzero_si128()));
	}

	void sse2_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::alpha_factor;
		alpha_factor<lhs_selector, identity_selector> factor;

		CPPUNIT_ASSERT(
			equals(factor(_mm_set1_epi8(245), _mm_setzero_si128()),
				   _mm_set1_epi8(245)));
	}

	void sse2_inverse_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::inverse_alpha_factor;
		inverse_alpha_factor<lhs_selector, identity_selector> factor;
		__m128i actual = factor(_mm_set1_epi32(1), _mm_setzero_si128());
		__m128i expect = _mm_set1_epi32(256);

		int actuals[4];
		int expects[4];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(actuals), actual);
		_mm_storeu_si128(reinterpret_cast<__m128i*>(expects), expect);

		for (int offset = 0; offset < 4; ++offset)
		{
			CPPUNIT_ASSERT_RANGE(actuals[offset], expects[offset], 1);
		}
	}

	void sse2_scale_factor_test()
	{
		using risa_gl::ext::sse2::primitive::scale_factor;
		risa_gl::uint32 source[5] = {0u, 1u, 2u, 3u, 4u};
		__m128i src0 = _mm_loadu_si128(reinterpret_cast<__m128i*>(source));
		__m128i src1 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&source[1]));

		scale_factor<0, 4, 0, 100> factor;
		__m128i dest0 = factor(src0);
		__m128i dest1 = factor(src1);

		risa_gl::uint32 dest[5];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(dest), dest0);
		_mm_storeu_si128(reinterpret_cast<__m128i*>(&dest[1]), dest1);
		
		for (int offset = 0; offset < 5; ++offset)
		{
			CPPUNIT_ASSERT_EQUAL(dest[offset], static_cast<risa_gl::uint32>(offset) * 25u);
		}
	}

	void sse2_scaled_alpha_selector_test()
	{
		using risa_gl::ext::sse2::primitive::scaled_alpha_selector;
		scaled_alpha_selector<0, 4, 0, 100, lhs_selector, identity_selector> selector;

		int sources[] = { 0, 1, 2, 3, 4 };
		__m128i src0 = _mm_loadu_si128(reinterpret_cast<__m128i*>(sources));
		__m128i src1 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&sources[1]));

		__m128i dest0 = selector(src0, src1);
		__m128i dest1 = selector(src1, src0);
		
		int dest[5];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(dest), dest0);
		_mm_storeu_si128(reinterpret_cast<__m128i*>(&dest[1]), dest1);

		for (int offset = 0; offset < 5; ++offset)
		{
			CPPUNIT_ASSERT_EQUAL(dest[offset], offset * 25);
		}
	}

	void sse2_invert_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::invert_alpha_factor;
		invert_alpha_factor<lhs_selector, identity_selector> factor;

		
		for (int index = 1; index <= 256; index += 4)
		{
			int sources[] = { index, index + 1, index + 2, index + 3 };
			__m128i source = _mm_loadu_si128(reinterpret_cast<__m128i*>(sources));

			__m128i result = factor(source, _mm_setzero_si128());
			int dests[4];
			_mm_storeu_si128(reinterpret_cast<__m128i*>(dests), result);
			CPPUNIT_ASSERT_EQUAL(dests[0], 257 - index);
			CPPUNIT_ASSERT_EQUAL(dests[1], 257 - (index + 1));
			CPPUNIT_ASSERT_EQUAL(dests[2], 257 - (index + 2));
			CPPUNIT_ASSERT_EQUAL(dests[3], 257 - (index + 3));
		}
	}

	void sse2_scaled_invert_alpha_selector_test()
	{
		using risa_gl::ext::sse2::primitive::scaled_invert_alpha_selector;
		scaled_invert_alpha_selector<1, 256, 0, 255, lhs_selector, identity_selector> factor;
		for (int index = 1; index <= 256; index += 4)
		{
			int sources[] = { index, index + 1, index + 2, index + 3 };
			__m128i source = _mm_loadu_si128(reinterpret_cast<__m128i*>(sources));
			int results[4];
			_mm_storeu_si128(reinterpret_cast<__m128i*>(results),
							 factor(source, _mm_setzero_si128()));
			
			CPPUNIT_ASSERT_EQUAL(results[0], 256 - (index + 0));
			CPPUNIT_ASSERT_EQUAL(results[1], 256 - (index + 1));
			CPPUNIT_ASSERT_EQUAL(results[2], 256 - (index + 2));
			CPPUNIT_ASSERT_EQUAL(results[3], 256 - (index + 3));
		}
	}

	void sse2_full_transparent_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::full_transparent_alpha_factor;
		full_transparent_alpha_factor factor;

		__m128i result = factor(_mm_set1_epi32(123), _mm_set1_epi32(456));
		int results[4];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(results), result);
		for (int offset = 0; offset < 4; ++offset)
		{
			CPPUNIT_ASSERT_EQUAL(results[offset], 1);
		}
	}

	void sse2_constant_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::constant_alpha_factor;
		{
			constant_alpha_factor factor;
			__m128i result = factor(1, 2);
			int results[4];
			_mm_storeu_si128(reinterpret_cast<__m128i*>(results), result);
			for (int offset = 0; offset < 4; ++offset)
				CPPUNIT_ASSERT_EQUAL(results[offset], 256);
		}

		{
			constant_alpha_factor factor(123);
			__m128i result = factor(1, 2);
			int results[4];
			_mm_storeu_si128(reinterpret_cast<__m128i*>(results), result);
			for (int offset = 0; offset < 4; ++offset)
				CPPUNIT_ASSERT_EQUAL(results[offset], 123);
		}
	}

	void sse2_invert_constant_alpha_factor_test()
	{
		using risa_gl::ext::sse2::primitive::invert_constant_alpha_factor;
		{
			invert_constant_alpha_factor factor;
			__m128i result = factor(_mm_set1_epi32(123), _mm_set1_epi32(456));
			int results[4];
			_mm_storeu_si128(reinterpret_cast<__m128i*>(results), result);
			for (int offset = 0; offset < 4; ++offset)
			{
				CPPUNIT_ASSERT_EQUAL(results[offset], 1);
			}
		}

		{
			invert_constant_alpha_factor factor(17);
			__m128i result = factor(_mm_set1_epi32(123), _mm_set1_epi32(456));
			int results[4];
			_mm_storeu_si128(reinterpret_cast<__m128i*>(results), result);
			for (int offset = 0; offset < 4; ++offset)
			{
				CPPUNIT_ASSERT_EQUAL(results[offset], 240);
			}
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(alpha_factor_test);

