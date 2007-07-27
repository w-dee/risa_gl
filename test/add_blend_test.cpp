#include <cppunit/extensions/HelperMacros.h>
#include <operators/add_blend.hpp>
#include <pixel.hpp>

class add_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(add_blend_operator_test);
	CPPUNIT_TEST(add_blend_test);
	CPPUNIT_TEST(add_blend_save_destination_alpha_test);
	CPPUNIT_TEST(add_blend_addtive_destination_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void add_blend_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		/**
		 * r.color = saturation(src.color + dest.color)
		 * (192, 192, 192)
		 */
		operators::add_blend_operator oper;
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 192);
		CPPUNIT_ASSERT(result.get_green() == 192);
		CPPUNIT_ASSERT(result.get_blue() == 192);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);
	}

	void add_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		/**
		 * r.color = saturation(src.color + dest.color)
		 * r.a = dest.a
		 * (192, 192, 192, 65)
		 */
		operators::add_blend_save_destination_alpha_operator oper;
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 192);
		CPPUNIT_ASSERT(result.get_green() == 192);
		CPPUNIT_ASSERT(result.get_blue() == 192);
		CPPUNIT_ASSERT(result.get_alpha() == 65);

		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);
		CPPUNIT_ASSERT(result.get_alpha() == 193);
	}

	void add_blend_addtive_destination_test()
	{
		using namespace risa_gl;

		pixel src(128, 128, 128, 129);
		pixel dest(64, 64, 64, 65);
		pixel result;

		/**
		 * r.color = saturation(src.color * src.a + dest.color)
		 * r.a = src.a * src.a + dest.a * (1 - src.a)
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0.25, 0.25, 0.25, 0.25)
		 * r.color = (0.25, 0.25, 0.25) + (0.25, 0.25, 0.25)
		 *         = (0.5, 0.5, 0.5)
		 *         = (128, 128, 128)
		 * r.a = 0.5 * 0.5 + 0.25 * ( 1 - 0.5)
		 *     = 0.25 + 0.25 * 0.5
		 *     = 0.25 + 0.125
		 *     = 0.375
		 *     = 96
		 * r = (128, 128, 128, 97)
		 */
		operators::add_blend_additive_destination_operator oper;
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 128);
		CPPUNIT_ASSERT(result.get_green() == 128);
		CPPUNIT_ASSERT(result.get_blue() == 128);
		CPPUNIT_ASSERT(result.get_alpha() == 97);

		/**
		 * r.color = saturation(src.color * src.a + dest.color)
		 * r.a = src.a * src.a + dest.a * (1 - src.a)
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0.75, 0.75, 0.75, 0.75)
		 * r.color = (0.25, 0.25, 0.25) + (0.75, 0.75, 0.75)
		 *         = (1, 1, 1)
		 *         = (255, 255, 255)
		 * r.a = 0.5 * 0.5 + 0.75 * (1 - 0.5)
		 *     = 0.25 + 0.75 * 0.5
		 *     = 0.25 + 0.375
		 *     = 0.625
		 *     = 160
		 * r = (255, 255, 255, 160)
		 */
		dest = pixel(192, 192, 192, 193);
		oper(&src, &dest, &result);
		CPPUNIT_ASSERT(result.get_red() == 255);
		CPPUNIT_ASSERT(result.get_green() == 255);
		CPPUNIT_ASSERT(result.get_blue() == 255);
		CPPUNIT_ASSERT(result.get_alpha() == 160);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( add_blend_operator_test );
