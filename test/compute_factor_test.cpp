#include <cppunit/extensions/HelperMacros.h>
#include <operators/primitive/compute_factor.hpp>

#include <iostream>
#include <iomanip>

class compute_factor_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(compute_factor_test);
	CPPUNIT_TEST(saturation_factor_test);
	CPPUNIT_TEST(under_saturation_factor_test);
	CPPUNIT_TEST(plus_factor_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void saturation_factor_test()
	{
		using namespace risa_gl::primitive;

		saturation_factor sat;

		CPPUNIT_ASSERT(sat(0x80808080, 0x7f7f7f7f) == 0xffffffff);
		CPPUNIT_ASSERT(sat(0x80808080, 0x80808080) == 0xffffffff);
		CPPUNIT_ASSERT(sat(0xffffffff, 0xffffffff) == 0xffffffff);
	}

	void under_saturation_factor_test()
	{
		using namespace risa_gl::primitive;

		under_saturation_factor sat;

		std::cout << std::hex << sat(0x80808080, 0x7f7f7f7f) << std::endl;
		CPPUNIT_ASSERT(sat(0x80808080, 0x70707070) == 0x01010101);
		CPPUNIT_ASSERT(sat(0x80808080, 0x80808080) == 0x00000000);
		CPPUNIT_ASSERT(sat(0xffffffff, 0xffffffff) == 0x00000000);
		CPPUNIT_ASSERT(sat(0x00000000, 0xffffffff) == 0x00000000);
		CPPUNIT_ASSERT(sat(0x11111111, 0x22222222) == 0x00000000);
	}

	void plus_factor_test()
	{
		CPPUNIT_FAIL("plus_factor_test");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( compute_factor_test );
