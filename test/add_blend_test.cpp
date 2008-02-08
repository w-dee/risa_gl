#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/add_blend.hpp>
#include <risa_gl/pixel.hpp>

class add_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(add_blend_operator_test);
	CPPUNIT_TEST(add_blend_test);
	CPPUNIT_TEST(add_blend_save_destination_alpha_test);
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
};

CPPUNIT_TEST_SUITE_REGISTRATION( add_blend_operator_test );
