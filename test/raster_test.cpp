#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/raster.hpp>
#include "range.hpp"

typedef risa_gl::render::raster<float> raster_t;
typedef raster_t::coord_type coord_t;

class raster_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(raster_test);
	CPPUNIT_TEST(offset_test);
	CPPUNIT_TEST(limit_test);
	CPPUNIT_TEST(position_test);
	CPPUNIT_TEST_SUITE_END();

	raster_t* raster;

public:
	void setUp()
	{
		raster = new raster_t(coord_t(0, 0, 1, 1, 0, 0),
							  coord_t(640, 0, 1, 1, 1, 0));
	}

	void tearDown()
	{
		delete raster;
	}

public:
	raster_test():
		raster()
	{}

	void offset_test()
	{
		CPPUNIT_ASSERT_EQUAL(raster->get_start(), 0.5f);
	}

	void limit_test()
	{
		CPPUNIT_ASSERT_EQUAL(raster->get_limit(), 640.f);
	}

	void position_test()
	{
		const float limit = raster->get_limit();
		for (int offset = 0; offset < raster->get_distance(); ++offset)
		{
			const coord_t result = (*raster)[offset];
			CPPUNIT_ASSERT_RANGE(result.get_x(),
								 static_cast<float>(offset + 0.5f), 0.0001f);
			CPPUNIT_ASSERT_RANGE(result.get_s(),
								 (offset + 0.5f) / limit, 0.001f);
		}
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( raster_test );
