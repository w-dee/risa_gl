#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <operators/with_opacity.hpp>
#include <operators/alpha_blend.hpp>
#include <operators/colormap.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class with_opacity_test : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE(with_opacity_test);
	CPPUNIT_TEST(colormap_alpha_blend_with_opacity_test);
	CPPUNIT_TEST(colormap_transparency_save_alpha_with_opacity_test);
	CPPUNIT_TEST_SUITE_END();
public:
	template <typename container_type>
	struct generator
	{
		const container_type container;

		generator(container_type container_):
			container(container_)
		{}

		container_type operator()() const
		{
			return container;
		}
	};

	void colormap_alpha_blend_with_opacity_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;
		typedef pixel_store<opaque> alpha_store;

		pixels_store pixels(640, 480);
		alpha_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<opaque>(opaque(65)));

		operators::with_opacity<operators::colormap_alpha_blend>
			oper(256, operators::colormap_alpha_blend(pixel(255, 255, 255, 129)));

		// color(1.0, 1.0, 1.0, 0.5), dest(0.5, 0.5, 0.5, 1.0), opacity(1.0)
		// color * color.a + dest * (1 - color.a)
		// (1, 1, 1) * 0.5 * 0.25 + (0.5, 0.5, 0.5) * (1 - 0.5 * 0.25)
		// (1/8, 1/8, 1/8) + (0.5, 0.5, 0.5) * 7/8
		// (0.125, 0.125, 0.125) + (0.4375, 0.4375, 0.4375)
		// (0.5625, 0.5625, 0.5625)
		// f(a, b) * opa + dest * (1 - opa)
		// (0.5625, 0.5625, 0.5625) * 1 + dest * 0
		// (143, 143, 143)
		// 

		
		oper(color_map.begin(), pixels.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 143);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 143);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 143);
	}

	void colormap_transparency_save_alpha_with_opacity_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;
		typedef pixel_store<opaque> alpha_store;

		pixels_store pixels(640, 480);
		alpha_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<opaque>(opaque(65)));

		operators::with_opacity<operators::colormap_transparency_save_alpha>
			oper(256, operators::colormap_transparency_save_alpha(
					 pixel(128, 128, 128, 129)));

		// src (0.5, 0.5, 0.5, 0.5)
		// dest (0.5, 0.5, 0.5, 1.0)
		// colormap_opa(0.25)
		// opa(1)
		// src * colormap_opa + dest
		// = (0.125, 0.125, 0.125, 0.125)
		// a = 0.125 + 1.0 - (0.125 * 1.0)
		//   = 1.125 - 0.125
		oper(color_map.begin(), pixels.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 32);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 32);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 32);
		CPPUNIT_ASSERT(pixels.begin()->get_alpha() == 256);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( with_opacity_test );
