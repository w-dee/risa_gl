#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/lighten_blend.hpp>
#include <risa_gl/pixel.hpp>

#include <iostream>

class lighten_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(lighten_blend_operator_test);
	CPPUNIT_TEST(lighten_blend_test);
	CPPUNIT_TEST(lighten_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void lighten_blend_test()
	{
		using namespace risa_gl;

		pixel src(64, 128, 192, 65);
		pixel dest(192, 172, 128, 129);
		pixel result;

		operators::lighten_blend_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 192);
		CPPUNIT_ASSERT(result.get_green() == 172);
		CPPUNIT_ASSERT(result.get_blue() == 192);

		dest = pixel(0, 0, 0, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 64);
		CPPUNIT_ASSERT(result.get_green() == 128);
		CPPUNIT_ASSERT(result.get_blue() == 192);
	}

	void lighten_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(64, 128, 192, 129);
		pixel dest(192, 172, 128, 65);
		pixel result;

		operators::lighten_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 192);
		CPPUNIT_ASSERT(result.get_green() == 172);
		CPPUNIT_ASSERT(result.get_blue() == 192);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(0, 0, 0, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 64);
		CPPUNIT_ASSERT(result.get_green() == 128);
		CPPUNIT_ASSERT(result.get_blue() == 192);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( lighten_blend_operator_test );
