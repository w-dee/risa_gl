#include <cppunit/extensions/HelperMacros.h>
#include <operators/with_opacity.hpp>
#include <operators/alpha_blend.hpp>
#include <operators/colormap.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class with_opacity_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(with_opacity_test);
	CPPUNIT_TEST(alpha_blend_with_opacity_test);
	CPPUNIT_TEST(colormap_6bpp_alpha_blend_with_opacity_test);
	CPPUNIT_TEST(colormap_6bpp_transparency_save_alpha_with_opacity_test);
	CPPUNIT_TEST(colormap_6bpp_transparency_with_opacity_test);
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

	void colormap_6bpp_alpha_blend_with_opacity_test()
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
		// (0.5, 0.5, 0.5) + (0.25, 0.25, 0.25)
		// (0.75, 0.75, 0.75)
		// (191, 191, 191)

		oper(color_map.begin(), pixels.begin(), pixels.begin());
		std::cout << *pixels.begin() << std::endl;
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 191);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 191);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 191);
	}

	void colormap_6bpp_transparency_save_alpha_with_opacity_test()
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

		operators::with_opacity<
			operators::colormap_transparency_save_alpha>
			oper(256, operators::colormap_transparency_save_alpha(
					 pixel(128, 128, 128, 129)));
		oper(color_map.begin(), pixels.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 64);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 64);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 64);
		CPPUNIT_ASSERT(pixels.begin()->get_alpha() == 256);
	}

	void colormap_6bpp_transparency_with_opacity_test()
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

		operators::with_opacity<operators::colormap_transparency>
			oper(256, operators::colormap_transparency(
					 pixel(128, 128, 128, 129)));
		oper(color_map.begin(), pixels.begin(), pixels.begin());

		CPPUNIT_ASSERT(pixels.begin()->get_red() == 64);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 64);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 64);
	}

	void alpha_blend_with_opacity_test()
	{
		CPPUNIT_FAIL("not implemented");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( with_opacity_test );
