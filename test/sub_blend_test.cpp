#include <cppunit/extensions/HelperMacros.h>
#include <operators/sub_blend.hpp>
#include <pixel.hpp>

#include <iostream>

class sub_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(sub_blend_operator_test);
	CPPUNIT_TEST(sub_blend_test);
	CPPUNIT_TEST(sub_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void sub_blend_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		/**
		 * r.color = saturation(src.color - dest.color)
		 * (64, 64, 64)
		 */
		operators::sub_blend_operator oper;
		oper(&src, &dest, &result);

		std::cout << result << std::endl;
		CPPUNIT_ASSERT(result.get_red() == 64);
		CPPUNIT_ASSERT(result.get_green() == 64);
		CPPUNIT_ASSERT(result.get_blue() == 64);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 0);
		CPPUNIT_ASSERT(result.get_green() == 0);
		CPPUNIT_ASSERT(result.get_blue() == 0);
	}

	void sub_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		/**
		 * r.color = saturation(src.color - dest.color)
		 * r.a = dest.a
		 * (64, 64, 64, 65)
		 */
		operators::sub_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 64);
		CPPUNIT_ASSERT(result.get_green() == 64);
		CPPUNIT_ASSERT(result.get_blue() == 64);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 0);
		CPPUNIT_ASSERT(result.get_green() == 0);
		CPPUNIT_ASSERT(result.get_blue() == 0);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( sub_blend_operator_test );
