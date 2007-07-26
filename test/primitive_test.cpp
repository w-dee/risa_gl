#include <cppunit/extensions/HelperMacros.h>
#include <operators/primitive/blend.hpp>
#include <pixel_store.hpp>
#include <pixel.hpp>

#include <iostream>

using namespace risa_gl;

class primitive_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(primitive_test);
	CPPUNIT_TEST(scaler_test);
	CPPUNIT_TEST(clear_test);
	CPPUNIT_TEST(blend_test);
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
			*itor = pixel(255, 255, 255, 256);

		for (pixel_store_t::iterator itor = destination.begin();
			 itor != destination.end(); ++itor)
			*itor = pixel(128, 128, 128, 129);
	}

	void blend_test()
	{
		using namespace risa_gl::primitive;
		typedef binomial_blend<
			one_minus_destination_alpha_factor,
			zero_factor,
			destination_alpha_factor,
			identity_factor> alpha_blend;

		alpha_blend blender;
		pixel_store_t::iterator itor_src = source.begin();
		pixel_store_t::iterator itor_dest = destination.begin();
		pixel_store_t::iterator itor_result = result.begin();
		
		for (; itor_src != source.end();
			 ++itor_src, ++itor_dest, ++itor_result)
		{
			blender(itor_src, itor_dest, itor_result);
			/**
			 * c = 255 * 128 + 128 * 128 = (255 + 128)
			 * a = 0 + 128
			 * result = (191, 191, 191, 128)
			 */
			CPPUNIT_ASSERT(*itor_result == pixel(191, 191, 191, 129));
		}
	}

	void saturation_blend_test()
	{
		using namespace risa_gl::primitive;
		typedef binomial_blend<
			one_minus_destination_alpha_factor,
			zero_factor,
			destination_alpha_factor,
			identity_factor> alpha_blend;

		alpha_blend blender;
		pixel_store_t::iterator itor_src = source.begin();
		pixel_store_t::iterator itor_dest = destination.begin();
		pixel_store_t::iterator itor_result = result.begin();
		
		for (; itor_src != source.end();
			 ++itor_src, ++itor_dest, ++itor_result)
		{
			blender(itor_src, itor_dest, itor_result);
			/**
			 * c = 255 * 128 + 128 * 128 = (255 + 128)
			 * a = 0 + 128
			 * result = (191, 191, 191, 128)
			 */
			CPPUNIT_ASSERT(*itor_result == pixel(191, 191, 191, 129));
		}
	}

	void clear_test()
	{
		using namespace risa_gl::primitive;
		clear blender;
		pixel_store_t::iterator itor_src = source.begin();
		pixel_store_t::iterator itor_dest = destination.begin();
		pixel_store_t::iterator itor_result = result.begin();
		
		for (; itor_src != source.end();
			 ++itor_src, ++itor_dest, ++itor_result)
		{
			blender(itor_src, itor_dest, itor_result);
			CPPUNIT_ASSERT(*itor_result == pixel(0, 0, 0, 1));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( primitive_test );
