#include <cppunit/extensions/HelperMacros.h>
#include <operators/ps_overlay_blend.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class ps_overlay_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_overlay_blend_operator_test);
	CPPUNIT_TEST(ps_overlay_blend_test);
	CPPUNIT_TEST(ps_overlay_blend_save_destination_alpha_test);
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

	typedef risa_gl::pixel_store<risa_gl::pixel> pixels_store;

	void ps_overlay_blend_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 256)));

		/**
		 * (213, 213, 213), (182, 41, 41)
		 * (182, 41, 41), (213, 213, 213)
		 * (255 - 73 * 42 * 2 / 256, 41 * 213 * 2 / 256, 41 * 213 * 2 / 256)
		 * (232, 68, 68)
		 *
		 * (232, 68, 68, 129), (182, 41, 41)
		 * (116, 34, 34), (91, 20, 20)
		 * (207, 54, 54)
		 *
		 */
		operators::ps_overlay_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		std::cout << *result.begin() << std::endl;

		CPPUNIT_ASSERT(result.begin()->get_red() == 205);
		CPPUNIT_ASSERT(result.begin()->get_green() == 54);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 54);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));

		/**
		 * (255, 255, 255), (255, 0, 0)
		 * (255, 0, 0), (255, 255, 255)
		 * (255 - 0 * 0 * 2, 0 * 255 * 2 / 256, 0 * 255 * 2 / 256)
		 * (255, 0, 0)
		 *
		 * (255, 0, 0, 129), (255, 0, 0)
		 * (128, 0, 0), (128, 0, 0)
		 * (255, 0, 0)
		 */
		oper(src.begin(), dest.begin(), result.begin());
		std::cout << *result.begin() << std::endl;

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 0);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 0);
	}

	void ps_overlay_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 256)));

		/**
		 * (43, 43, 43) * (74, 215, 215)
		 * (12, 36, 36)
		 * (244, 220, 220)
		 *
		 * (244, 220, 220, 129), (182, 41, 41)
		 * (122, 110, 110), (91, 20, 20)
		 * (213, 130, 130)
		 */
		operators::ps_overlay_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 213);
		CPPUNIT_ASSERT(result.begin()->get_green() == 130);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 130);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 256);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));

		/**
		 * (0, 0, 0) * (0, 255, 255)
		 * (0, 0, 0)
		 * (255, 255, 255)
		 *
		 * (255, 255, 255, 129), (255, 0, 0, 129)
		 * (128, 128, 128), (128, 0, 0)
		 * (255, 128, 128)
		 *
		 */
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 128);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 128);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 129);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_overlay_blend_operator_test );
