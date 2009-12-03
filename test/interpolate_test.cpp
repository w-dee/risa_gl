#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/interpolate.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/transformer.hpp>
#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/region.hpp>
#include <map>
#include "range.hpp"

#include <iostream>

using risa_gl::nearest;
using risa_gl::bilinear;
using risa_gl::math::vector2;
using risa_gl::math::vector3;
using risa_gl::math::coordinate;
using risa_gl::math::dividable_vector;

typedef risa_gl::pixel_store<risa_gl::pixel> pixel_store_type;

class interpolate_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(interpolate_test);
	CPPUNIT_TEST(nearest_test);
	CPPUNIT_TEST(bilinear_test);
	CPPUNIT_TEST(nearest_referencer_test);
	CPPUNIT_TEST(bilinear_referencer_test);
	CPPUNIT_TEST(bilinear_interpolate_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void bilinear_interpolate_test()
	{
		pixel_store_type pixels(64, 64);
		for (int x = 0; x < 64; ++x)
			for (int y = 0; y < 64; ++y)
			{
				pixels(x, y) =
					pixel_store_type::pixel_type(x*4, y*4, 0, 256);
			}

		risa_gl::bilinear_referencer<pixel_store_type>
			interpolator(pixels, 64,
						 vector2<float>(0, 0),
						 vector2<float>(64, 0));

		CPPUNIT_ASSERT(*interpolator.get_proxy(vector2<float>(0, 0)) ==
					   pixel_store_type::pixel_type(0, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(vector2<float>(.5, 0)) ==
					   pixel_store_type::pixel_type(2, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(vector2<float>(1, 0)) ==
					   pixel_store_type::pixel_type(4, 0, 0, 256));

		CPPUNIT_ASSERT(*interpolator.get_proxy(vector2<float>(62, 0)) ==
					   pixel_store_type::pixel_type(62*4, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(vector2<float>(62.5f, 0)) ==
					   pixel_store_type::pixel_type(250, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(vector2<float>(63, 0)) ==
					   pixel_store_type::pixel_type(63*4, 0, 0, 256));
	}

	void bilinear_referencer_test()
	{
		pixel_store_type pixels(256, 256);
		for (int x = 0; x < 256; ++x)
			for (int y = 0; y < 256; ++y)
			{
				pixels(x, y) =
					pixel_store_type::pixel_type(x/2*2, y/2*2, 0, 256);
			}

		risa_gl::bilinear_referencer<pixel_store_type>
			interpolator(pixels, 128,
						 vector2<float>(0, 0),
						 vector2<float>(256, 0));

		CPPUNIT_ASSERT(interpolator.interpolate(0) ==
					   vector2<float>(0, 0));
		CPPUNIT_ASSERT(interpolator.interpolate(1.f/256.f) ==
					   vector2<float>(1, 0));

		CPPUNIT_ASSERT(interpolator.interpolate(127.f/256.f) ==
					   vector2<float>(127, 0));
		CPPUNIT_ASSERT(interpolator.interpolate(128.f/256.f) ==
					   vector2<float>(128, 0));
		CPPUNIT_ASSERT(interpolator.interpolate(129.f/256.f) ==
					   vector2<float>(129, 0));

		CPPUNIT_ASSERT(interpolator.interpolate(255.f/256.f) ==
					   vector2<float>(255, 0));
		CPPUNIT_ASSERT(interpolator.interpolate(1) ==
					   vector2<float>(256, 0));

		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(0, 0)) ==
					   pixel_store_type::pixel_type(0, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(.5, 0)) ==
					   pixel_store_type::pixel_type(0, 0, 0, 256));

		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(127, 0)) ==
					   pixel_store_type::pixel_type(126, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(128, 0)) ==
					   pixel_store_type::pixel_type(128, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(129, 0)) ==
					   pixel_store_type::pixel_type(128, 0, 0, 256));

		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(255, 0)) ==
					   pixel_store_type::pixel_type(254, 0, 0, 256));
// 		CPPUNIT_ASSERT(*interpolator.get_proxy(
// 						   vector2(256, 0)) ==
// 					   pixel_store_type::pixel_type(256, 0, 0, 256));
	}

	void nearest_referencer_test()
	{
		pixel_store_type pixels(256, 256);
		for (int x = 0; x < 256; ++x)
			for (int y = 0; y < 256; ++y)
				pixels(x, y) =
					pixel_store_type::pixel_type(x, y, 0, 256);

		risa_gl::nearest_referencer<pixel_store_type>
			interpolator(pixels, 128,
						 vector2<float>(0, 0),
						 vector2<float>(256, 0));

		CPPUNIT_ASSERT(interpolator.interpolate(0) ==
					   vector2<float>(0, 0));
		CPPUNIT_ASSERT(interpolator.interpolate(.5f) ==
					   vector2<float>(128, 0));
		CPPUNIT_ASSERT(interpolator.interpolate(1) ==
					   vector2<float>(256, 0));

		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(0, 0)) ==
					   pixel_store_type::pixel_type(0, 0, 0, 256));
		CPPUNIT_ASSERT(*interpolator.get_proxy(
					   vector2<float>(128, 0)) ==
					   pixel_store_type::pixel_type(128, 0, 0, 256));
// 		CPPUNIT_ASSERT(*interpolator.get_proxy(
// 						   coordinate<int>(256, 0)) ==
// 					   pixel_store_type::pixel_type(256, 0, 0, 256));
	}

	void bilinear_test()
	{
		pixel_store_type pixels(64, 64);
		for (int x = 0; x < 64; ++x)
			for (int y = 0; y < 64; ++y)
				pixels(x, y) =
					pixel_store_type::pixel_type(x * 4, y * 4, 0, 256);

		bilinear<pixel_store_type> bilinear_filter(pixels,
												 vector2<float>(0.f, 0.f),
												 vector2<float>(63.f, 63.f),
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
												 vector2<float>(0.f, 0.f),
												 vector2<float>(255.f, 0.f),
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
