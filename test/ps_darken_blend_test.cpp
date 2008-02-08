#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/ps_darken_blend.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include <algorithm>

#include <iostream>

class ps_darken_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_darken_blend_operator_test);
	CPPUNIT_TEST(ps_darken_blend_test);
	CPPUNIT_TEST(ps_darken_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();

	typedef risa_gl::pixel_store<risa_gl::pixel> pixel_store_t;

public:
	void ps_darken_blend_test()
	{
		using namespace risa_gl;

		pixel_store_t src(640, 480);
		pixel_store_t dest(640, 480);
		pixel_store_t result(640, 480);

		std::fill(src.begin(), src.end(), pixel(64, 64, 64, 65));
		std::fill(dest.begin(), dest.end(), pixel(128, 128, 128, 129));

		operators::ps_darken_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 112);
		CPPUNIT_ASSERT(result.begin()->get_green() == 112);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 112);

		std::fill(dest.begin(), dest.end(), pixel(0, 192, 0, 193));
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 0);
		CPPUNIT_ASSERT(result.begin()->get_green() == 160);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 0);
	}

	void ps_darken_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel_store_t src(640, 480);
		pixel_store_t dest(640, 480);
		pixel_store_t result(640, 480);

		std::fill(src.begin(), src.end(), pixel(128, 128, 128, 129));
		std::fill(dest.begin(), dest.end(), pixel(64, 64, 64, 65));

		operators::ps_darken_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 64);
		CPPUNIT_ASSERT(result.begin()->get_green() == 64);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 64);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 65);

		std::fill(dest.begin(), dest.end(), pixel(192, 192, 192, 193));
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 160);
		CPPUNIT_ASSERT(result.begin()->get_green() == 160);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 160);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_darken_blend_operator_test );
