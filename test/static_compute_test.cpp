#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/cosine.hpp>
#include <risa_gl/math/sine.hpp>
#include <risa_gl/math/power.hpp>
#include <risa_gl/math/fraction.hpp>
#include <cmath>
#include <iostream>

class static_compute_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(static_compute_test);
	CPPUNIT_TEST(cosine_test);
	CPPUNIT_TEST(sine_test);
	CPPUNIT_TEST(power_test);
//	CPPUNIT_TEST(fraction_cosine_test);
	CPPUNIT_TEST(fraction_power_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void fraction_power_test()
	{
		using risa_gl::math::fraction;
		using risa_gl::math::power;

		bool result = 
			power<fraction<int>, 2>::value(-2) == fraction<int>(4, 1);
		CPPUNIT_ASSERT(result);
	}

// 	void fraction_cosine_test()
// 	{
// 		using risa_gl::math::fraction;
// 		using risa_gl::math::cosine;

// 		for (int v = -32; v <= 32; ++v)
// 		{
// 			CPPUNIT_ASSERT(
// 				std::abs(
// 					std::cos(v/64.0f) -
// 					cosine<fraction<int> >::value(
// 						fraction<int>(v, 64)).get_real_value())
// 				< 0.01f);
// 		}
// 	}

	void power_test()
	{
		CPPUNIT_ASSERT((risa_gl::math::power<float,5>::value(2.f) == 32.f));
		CPPUNIT_ASSERT((risa_gl::math::power<float,5>::value(3.f) == 243.f));
		CPPUNIT_ASSERT((risa_gl::math::power<float,6>::value(3.f) == 729.f));
	}

	void sine_test()
	{
		for (float v = -1.f; v < 1.f; v+= 0.01f)
		{
			CPPUNIT_ASSERT(
				std::abs(std::sin(v) -
						 risa_gl::math::sine<float>::value(v)) < 0.01f);
		}
	}

	void cosine_test()
	{
		for (float v = -1.f; v < 1.f; v+= 0.01f)
		{
			CPPUNIT_ASSERT(
				std::abs(std::cos(v) -
						 risa_gl::math::cosine<float>::value(v)) < 0.01f);
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( static_compute_test );
