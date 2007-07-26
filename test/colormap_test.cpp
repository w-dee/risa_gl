#include <cppunit/extensions/HelperMacros.h>
#include <operators/colormap.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <algorithm>

class colormap_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(colormap_test);
	CPPUNIT_TEST(colormap_6bpp_transparency_test);
	CPPUNIT_TEST(colormap_6bpp_transparency_save_alpha_test);
	CPPUNIT_TEST(colormap_6bpp_alpha_blend_test);
	CPPUNIT_TEST(colormap_6bpp_add_blend_test);
	CPPUNIT_TEST(colormap_transparency_test);
	CPPUNIT_TEST(colormap_transparency_save_alpha_test);
	CPPUNIT_TEST(colormap_alpha_blend_test);
	CPPUNIT_TEST(colormap_add_blend_test);
	CPPUNIT_TEST_SUITE_END();

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
		
public:
	void colormap_6bpp_add_blend_test()
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

		operators::colormap_6bpp_add_blend
			oper(pixel(255, 255, 255, 129));

		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_alpha() == 256);
	}

	void colormap_6bpp_alpha_blend_test()
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

		operators::colormap_6bpp_alpha_blend
			oper(pixel(255, 255, 255, 129));

		// src(0.5, 0.5, 0.5, 1.0), color(1.0, 1.0, 1.0, 0.5), opacity(1.0)
		// r = (1.0, 1.0, 1.0, ?)

		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 255);
	}

	void colormap_6bpp_transparency_save_alpha_test()
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

		operators::colormap_6bpp_transparency_save_alpha
			oper(pixel(128, 128, 128, 129));
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_alpha() == 256);
	}

	void colormap_6bpp_transparency_test()
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

		operators::colormap_6bpp_transparency oper(pixel(128, 128, 128, 129));
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 128);
	}

	// 8bpp
	void colormap_add_blend_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store pixels(640, 480);
		pixels_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		operators::colormap_add_blend
			oper(pixel(255, 255, 255, 129));

		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_alpha() == 256);
	}

	void colormap_alpha_blend_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store pixels(640, 480);
		pixels_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		operators::colormap_alpha_blend
			oper(pixel(255, 255, 255, 129));

		// src(0.5, 0.5, 0.5, 1.0), color(1.0, 1.0, 1.0, 0.5), opacity(1.0)
		// r = (1.0, 1.0, 1.0, ?)

		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 255);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 255);
	}

	void colormap_transparency_save_alpha_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store pixels(640, 480);
		pixels_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		operators::colormap_transparency_save_alpha
			oper(pixel(128, 128, 128, 129));
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_alpha() == 256);
	}

	void colormap_transparency_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store pixels(640, 480);
		pixels_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		operators::colormap_transparency oper(pixel(128, 128, 128, 129));
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(pixels.begin()->get_red() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_green() == 128);
		CPPUNIT_ASSERT(pixels.begin()->get_blue() == 128);
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( colormap_test );
