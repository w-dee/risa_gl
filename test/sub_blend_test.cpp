#include <cppunit/extensions/HelperMacros.h>
#include <operators/sub_blend.hpp>
#include <pixel.hpp>

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

		pixel src(128, 128, 128, 65);
		pixel dest(128, 128, 128, 129);
		pixel result;

		/**
		 * r.color = saturation(dest.color - (1 - src.color))
		 * (0, 0, 0)
		 */
		operators::sub_blend_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 1);
		CPPUNIT_ASSERT(result.get_green() == 1);
		CPPUNIT_ASSERT(result.get_blue() == 1);

		src = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 65);
		CPPUNIT_ASSERT(result.get_green() == 65);
		CPPUNIT_ASSERT(result.get_blue() == 65);
	}

	void sub_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel dest(128, 128, 128, 129);
		pixel src(128, 128, 128, 65);
		pixel result;

		/**
		 * r.color = saturation(dest.color - (1 - src.color))
		 * r.a = dest.a
		 * (0, 0, 0, 129)
		 */
		operators::sub_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 1);
		CPPUNIT_ASSERT(result.get_green() == 1);
		CPPUNIT_ASSERT(result.get_blue() == 1);
		CPPUNIT_ASSERT(result.get_alpha() == 129);

		src = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 65);
		CPPUNIT_ASSERT(result.get_green() == 65);
		CPPUNIT_ASSERT(result.get_blue() == 65);
		CPPUNIT_ASSERT(result.get_alpha() == 129);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( sub_blend_operator_test );
