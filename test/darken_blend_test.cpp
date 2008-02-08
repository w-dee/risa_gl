#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/darken_blend.hpp>
#include <risa_gl/pixel.hpp>

#include <iostream>

class darken_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(darken_blend_operator_test);
	CPPUNIT_TEST(darken_blend_test);
	CPPUNIT_TEST(darken_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void darken_blend_test()
	{
		using namespace risa_gl;

		pixel src(64, 64, 64, 65);
		pixel dest(128, 128, 128, 129);
		pixel result;

		operators::darken_blend_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 64);
		CPPUNIT_ASSERT(result.get_green() == 64);
		CPPUNIT_ASSERT(result.get_blue() == 64);

		dest = pixel(0, 192, 0, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 0);
		CPPUNIT_ASSERT(result.get_green() == 64);
		CPPUNIT_ASSERT(result.get_blue() == 0);
	}

	void darken_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		operators::darken_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 64);
		CPPUNIT_ASSERT(result.get_green() == 64);
		CPPUNIT_ASSERT(result.get_blue() == 64);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 128);
		CPPUNIT_ASSERT(result.get_green() == 128);
		CPPUNIT_ASSERT(result.get_blue() == 128);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( darken_blend_operator_test );
