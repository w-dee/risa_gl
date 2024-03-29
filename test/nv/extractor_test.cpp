#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/nv/extractor.hpp>
#include <risa_gl/nv/environment.hpp>

#include "pixel_type.hpp"

class extractor_test : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE(extractor_test);
	CPPUNIT_TEST(identity_test);
	CPPUNIT_TEST(dereference_test);
	CPPUNIT_TEST(factor_test);
	CPPUNIT_TEST(constant_value_test);
	CPPUNIT_TEST(dynamic_value_test);
	CPPUNIT_TEST(composite_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void composite_test()
	{
		extractor::composite<
		template_functions::bind_2nd<
		environments::cplusplus::basic_input_type,
			extractor::alpha_factor>::
			template currying,
			extractor::identity>::type<
		environments::cplusplus::bit_pattern_type>
			composite_extractor;

		risa_gl::pixel src(1, 2, 3, 4);
		risa_gl::pixel dest(5, 6, 7, 8);

		environments::cplusplus::bit_pattern_type 
			result = composite_extractor(src, dest);

		CPPUNIT_ASSERT_EQUAL(0x4U, result);
	}

	void identity_test()
	{
		extractor::identity<void> func;

		CPPUNIT_ASSERT_EQUAL(0x04030201U, func(0x04030201U));
	}

	void dereference_test()
	{
		extractor::dereference<unsigned long long> func;
		unsigned long long values[4] = { 1ULL, 2ULL, 3ULL, 4ULL };

		CPPUNIT_ASSERT_EQUAL(1ULL, func(values));
		CPPUNIT_ASSERT_EQUAL(4ULL, func(values + 3));
	}

	void factor_test()
	{
		extractor::alpha_factor<unsigned int, pixel_type> func;
		pixel_type color(1, 2, 3, 4);

		CPPUNIT_ASSERT_EQUAL(4U, func(color));

		extractor::factor<unsigned int, pixel_type::red_position> func_r;

		CPPUNIT_ASSERT_EQUAL(1U, func_r(color));

		extractor::factor<unsigned int, pixel_type::green_position> func_g;

		CPPUNIT_ASSERT_EQUAL(2U, func_g(color));

		extractor::factor<unsigned int, pixel_type::blue_position> func_b;

		CPPUNIT_ASSERT_EQUAL(3U, func_b(color));

		extractor::factor<unsigned int, pixel_type::alpha_position> func_a;

		CPPUNIT_ASSERT_EQUAL(4U, func_a(color));
	}

	void constant_value_test()
	{
		extractor::constant_value<0x04030201U> func;

		CPPUNIT_ASSERT_EQUAL(0x0403020104030201ULL, func(0x04030201ULL));
	}

	void dynamic_value_test()
	{
		extractor::dynamic_value<unsigned long long> func(0x0807060504030201ULL);

		CPPUNIT_ASSERT_EQUAL(0x0807060504030201ULL, func(0));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( extractor_test );
