#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/primitive/compute_function.hpp>

#include <iostream>
#include <iomanip>

class compute_factor_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(compute_factor_test);
	CPPUNIT_TEST(saturation_function_test);
	CPPUNIT_TEST(under_saturation_function_test);
	CPPUNIT_TEST(plus_function_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void saturation_function_test()
	{
		using namespace risa_gl::primitive;

		add_saturation_function sat;

		CPPUNIT_ASSERT(sat(0x80808080, 0x7f7f7f7f) == 0xffffffff);
		CPPUNIT_ASSERT(sat(0x80808080, 0x80808080) == 0xffffffff);
		CPPUNIT_ASSERT(sat(0xffffffff, 0xffffffff) == 0xffffffff);
	}

	void under_saturation_function_test()
	{
		using namespace risa_gl::primitive;

		subtract_saturation_function<
			destination_selector,
			source_selector> sat;

		CPPUNIT_ASSERT(sat(0x00800080, 0x00000000) == 0x00800080);
		CPPUNIT_ASSERT(sat(0x00800080, 0x00700070) == 0x00100010);
		CPPUNIT_ASSERT(sat(0x00800080, 0x00800080) == 0x00000000);
		CPPUNIT_ASSERT(sat(0x00ff00ff, 0x00ff00ff) == 0x00000000);
		CPPUNIT_ASSERT(sat(0x00000000, 0x00ff00ff) == 0x00000000);
		CPPUNIT_ASSERT(sat(0x00110011, 0x00220022) == 0x00000000);
	}

	void plus_function_test()
	{
		using namespace risa_gl::primitive;

		plus_function plus;

		CPPUNIT_ASSERT(plus(0x00800080, 0x00000000) == 0x00800080);
		CPPUNIT_ASSERT(plus(0x00800080, 0x00700070) == 0x00f000f0);
		CPPUNIT_ASSERT(plus(0x00800080, 0x00800080) == 0x01000100);
		CPPUNIT_ASSERT(plus(0x00ff00ff, 0x00ff00ff) == 0x01fe01fe);
		CPPUNIT_ASSERT(plus(0x00000000, 0x00ff00ff) == 0x00ff00ff);
		CPPUNIT_ASSERT(plus(0x00110011, 0x00220022) == 0x00330033);
		
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( compute_factor_test );
