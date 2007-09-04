#include <cppunit/extensions/HelperMacros.h>
#include <operators/mul_blend.hpp>
#include <pixel.hpp>

class mul_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(mul_blend_operator_test);
	CPPUNIT_TEST(mul_blend_test);
	CPPUNIT_TEST(mul_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void mul_blend_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		/**
		 * r.color = src.color * dest.color
		 * (0.5, 0,5, 0,5) * (0.25, 0.25, 0.25)
		 * = (0.125, 0.125, 0.125)
		 * (32, 32, 32)
		 */
		operators::mul_blend_operator oper;
		oper(&src, &dest, &result);

		CPPUNIT_ASSERT(result.get_red() == 32);
		CPPUNIT_ASSERT(result.get_green() == 32);
		CPPUNIT_ASSERT(result.get_blue() == 32);

		/**
		 * r.color = src.color * dest.color
		 * (0.5, 0,5, 0,5) * (0.75, 0.75, 0.75)
		 * = (0.375, 0.375, 0.375)
		 * (96, 96, 96)
		 */
		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 96);
		CPPUNIT_ASSERT(result.get_green() == 96);
		CPPUNIT_ASSERT(result.get_blue() == 96);
	}

	void mul_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		operators::mul_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);

		/**
		 * r.color = src.color * dest.color
		 * (0.5, 0,5, 0,5) * (0.25, 0.25, 0.25)
		 * = (0.125, 0.125, 0.125)
		 * (32, 32, 32, 65)
		 */
		CPPUNIT_ASSERT(result.get_red() == 32);
		CPPUNIT_ASSERT(result.get_green() == 32);
		CPPUNIT_ASSERT(result.get_blue() == 32);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		/**
		 * r.color = src.color * dest.color
		 * (0.5, 0,5, 0,5) * (0.75, 0.75, 0.75)
		 * = (0.375, 0.375, 0.375)
		 * (96, 96, 96, 193)
		 */
		CPPUNIT_ASSERT(result.get_red() == 96);
		CPPUNIT_ASSERT(result.get_green() == 96);
		CPPUNIT_ASSERT(result.get_blue() == 96);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( mul_blend_operator_test );
