#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/div_blend.hpp>
#include <risa_gl/pixel.hpp>

#include <iostream>

class div_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(div_blend_operator_test);
	CPPUNIT_TEST(div_blend_test);
	CPPUNIT_TEST(div_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void div_blend_test()
	{
		using namespace risa_gl;

		pixel src(64, 64, 64, 65);
		pixel dest(128, 128, 128, 129);
		pixel result;

		/**
		 * r.color = dest.color / (1 - src.color)
		 * (170, 170, 170)
		 */
		operators::div_blend_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 170);
		CPPUNIT_ASSERT(result.get_green() == 170);
		CPPUNIT_ASSERT(result.get_blue() == 170);

		/**
		 * r.color = dest.color / (1 - src.color)
		 * (255, 255, 255)
		 */
		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);
	}

	void div_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		operators::div_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 128);
		CPPUNIT_ASSERT(result.get_green() == 128);
		CPPUNIT_ASSERT(result.get_blue() == 128);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( div_blend_operator_test );
