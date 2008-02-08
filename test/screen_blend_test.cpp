#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/screen_blend.hpp>
#include <risa_gl/pixel.hpp>

#include <iostream>

class screen_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(screen_blend_operator_test);
	CPPUNIT_TEST(screen_blend_test);
	CPPUNIT_TEST(screen_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void screen_blend_test()
	{
		using namespace risa_gl;

		pixel src(64, 64, 64, 65);
		pixel dest(128, 128, 128, 129);
		pixel result;

		/*
		 * 1 - (1 - (0.25, 0.25, 0.25)) * (1 - (0.5, 0.5, 0.5))
		 * 1 - (0.75, 0.75, 0.75) * (0.5, 0.5, 0.5)
		 * 1 - (0.375, 0.375, 0.375)
		 * = (0.625, 0.625, 0.625)
		 * = (160, 160, 160)
		 */
		operators::screen_blend_operator oper;
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 161);
		CPPUNIT_ASSERT(result.get_green() == 161);
		CPPUNIT_ASSERT(result.get_blue() == 161);

		dest = pixel(0, 0, 0, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 65);
		CPPUNIT_ASSERT(result.get_green() == 65);
		CPPUNIT_ASSERT(result.get_blue() == 65);
	}

	void screen_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(64, 64, 64, 65);
		pixel dest(128, 128, 128, 129);
		pixel result;

		operators::screen_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 161);
		CPPUNIT_ASSERT(result.get_green() == 161);
		CPPUNIT_ASSERT(result.get_blue() == 161);
		CPPUNIT_ASSERT(result.get_alpha() == 129);

		dest = pixel(0, 0, 0, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 65);
		CPPUNIT_ASSERT(result.get_green() == 65);
		CPPUNIT_ASSERT(result.get_blue() == 65);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( screen_blend_operator_test );
