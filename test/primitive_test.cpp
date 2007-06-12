#include <cppunit/extensions/HelperMacros.h>
#include "operators/primitive/primitive.hpp"
#include "pixel_store.hpp"
#include "pixel.hpp"

using namespace risa_gl;

class primitive_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(primitive_test);
	CPPUNIT_TEST(clear_test);
	CPPUNIT_TEST_SUITE_END();

	typedef pixel_store<pixel, 16> pixel_store_t;
	pixel_store_t source;
	pixel_store_t destination;
	pixel_store_t result;

public:
	primitive_test():
		source(320, 120), destination(320, 120), result(320, 120)
	{}

	void setUp()
	{
		for (pixel_store_t::iterator itor = source.begin();
			 itor != source.end(); ++itor)
			*itor = pixel(255, 255, 255, 255);

		for (pixel_store_t::iterator itor = destination.begin();
			 itor != destination.end(); ++itor)
			*itor = pixel(128, 128, 128, 64);
	}

	void clear_test()
	{

		risa_gl::primitives::clear op;
		
		for (pixel_store_t::iterator itor = result.begin();
			 itor != result.end(); ++itor)
		{
			op(itor, itor, itor);
			CPPUNIT_ASSERT(*itor == pixel(0, 0, 0, 0));
		}

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( primitive_test );
