#include <cppunit/extensions/HelperMacros.h>
#include <pixel_store.hpp>
#include <pixel.hpp>

class pixel_store_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(pixel_store_test);
	CPPUNIT_TEST(allocate_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void allocate_test()
	{
		using namespace risa_gl;
		pixel_store<pixel, 16> pixels1(257, 100);
		
		CPPUNIT_ASSERT(pixels1.get_width() == 257);
		CPPUNIT_ASSERT(pixels1.get_height() == 100);
		CPPUNIT_ASSERT(pixels1.get_allocate_width() == 280);

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( pixel_store_test );
