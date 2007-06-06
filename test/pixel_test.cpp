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
		CPPUNIT_ASSERT(pic.get_red() == 0);
		CPPUNIT_ASSERT(pic.get_green() == 0);
		CPPUNIT_ASSERT(pic.get_blue() == 0);
		CPPUNIT_ASSERT(pic.get_alpha() == 255);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( pixel_test );
