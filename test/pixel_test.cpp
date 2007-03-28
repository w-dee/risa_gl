#include <cppunit/extensions/HelperMacros.h>
#include "pixel.hpp"

class pixel_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(pixel_test);
	CPPUNIT_TEST(colorTest);
	CPPUNIT_TEST_SUITE_END();

public:
	void colorTest()
	{
		using namespace risa_gl;

		pixel pic;
		CPPUNIT_ASSERT(pic.get_r() == 0);
		CPPUNIT_ASSERT(pic.get_g() == 0);
		CPPUNIT_ASSERT(pic.get_b() == 0);
		CPPUNIT_ASSERT(pic.get_a() == 255);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( pixel_test );

