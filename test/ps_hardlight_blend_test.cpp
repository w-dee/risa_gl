#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/ps_hardlight_blend.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include <algorithm>

#include <iostream>

class ps_hardlight_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_hardlight_blend_operator_test);
	CPPUNIT_TEST(ps_hardlight_blend_test);
	CPPUNIT_TEST(ps_hardlight_blend_save_destination_alpha_test);
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

	void ps_hardlight_blend_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(182, 41, 41, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(213, 213, 213, 256)));

		/**
		 * (213, 213, 213), (182, 41, 41)
		 * (222, 199, 199)
		 *
		 */
		operators::ps_hardlight_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 222);
		CPPUNIT_ASSERT(result.begin()->get_green() == 198);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 198);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));

		/**
		 * (255, 255, 255), (255, 0, 0)
		 * (255, 0, 0)
		 */
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 0);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 0);
	}

	void ps_hardlight_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(182, 41, 41, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(213, 213, 213, 256)));

		operators::ps_hardlight_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 222);
		CPPUNIT_ASSERT(result.begin()->get_green() == 198);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 198);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 256);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));

		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 0);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 0);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 129);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_hardlight_blend_operator_test );
