#include <cppunit/extensions/HelperMacros.h>
#include <interpolate.hpp>
#include <pixel_store.hpp>
#include <pixel.hpp>
#include "range.hpp"

#include <iostream>

using risa_gl::nearest;
using risa_gl::bilinear;
using risa_gl::math::vector2;

typedef risa_gl::pixel_store<risa_gl::pixel> pixel_store_type;

class interpolate_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(interpolate_test);
	CPPUNIT_TEST(nearest_test);
	CPPUNIT_TEST(bilinear_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void bilinear_test()
	{
		pixel_store_type pixels(64, 64);
		for (int x = 0; x < 64; ++x)
			for (int y = 0; y < 64; ++y)
				pixels(x, y) =
					pixel_store_type::pixel_type(x * 4, y * 4, 0, 256);

		bilinear<pixel_store_type> bilinear_filter(pixels,
												 vector2(0.f, 0.f),
												 vector2(63.f, 63.f),
												 128);

		bilinear<pixel_store_type>::pixel_vector_type fragments =
			bilinear_filter.interpolate();

		CPPUNIT_ASSERT(fragments.size() == 128);
		for (size_t offset = 0; offset != fragments.size(); ++offset)
		{
			CPPUNIT_ASSERT(range<int>(fragments[offset].get_red(),
									  fragments[offset].get_green(), 1));
			CPPUNIT_ASSERT(fragments[offset].get_blue() == 0);
			CPPUNIT_ASSERT(fragments[offset].get_alpha() >= 250);
		}
	}

	void nearest_test()
	{
		pixel_store_type pixels(256, 256);
		for (int x = 0; x < 256; ++x)
			for (int y = 0; y < 256; ++y)
				pixels(x, y) = pixel_store_type::pixel_type(x, y, 0, 256);

		nearest<pixel_store_type> nearest_filter(pixels,
												 vector2(0.f, 0.f),
												 vector2(255.f, 0.f),
												 128);

		nearest<pixel_store_type>::pixel_vector_type fragments =
			nearest_filter.interpolate();

		CPPUNIT_ASSERT(fragments.size() == 128);
		for (size_t offset = 0; offset != fragments.size(); ++offset)
		{
			CPPUNIT_ASSERT(
				range<int>(fragments[offset].get_red(), offset * 2, 1));
			CPPUNIT_ASSERT(fragments[offset].get_green() == 0);
			CPPUNIT_ASSERT(fragments[offset].get_blue() == 0);
			CPPUNIT_ASSERT(fragments[offset].get_alpha() == 256);
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( interpolate_test );
