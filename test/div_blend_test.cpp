#include <cppunit/extensions/HelperMacros.h>
#include <operators/div_blend.hpp>
#include <pixel.hpp>

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
		 * r.color = dest.color / src.color
		 * (0.5, 0,5, 0,5) / (0.25, 0.25, 0.25)
		 * = (2, 2, 2)
		 * (255, 255, 255)
		 */
		operators::div_blend_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);

		/**
		 * r.color = dest.color / src.color
		 * (0.75, 0,75, 0,75) / (0.25, 0.25, 0.25)
		 * = (3/2, 3/2, 3/2)
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

		/**
		 * r.color = dest.color / src.color
		 * (0.25, 0.25, 0.25) / (0.5, 0,5, 0,5)
		 * = (0.5, 0.5, 0.5)
		 * (127, 127, 127, 65)
		 */
		CPPUNIT_ASSERT(result.get_red() == 127);
		CPPUNIT_ASSERT(result.get_green() == 127);
		CPPUNIT_ASSERT(result.get_blue() == 127);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		/**
		 * r.color = dest.color / src.color
		 * (0.25, 0,25, 0,25) / (0.25, 0.25, 0.25)
		 * = (1, 1, 1)
		 * (255, 255, 255, 193)
		 */
		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( div_blend_operator_test );
