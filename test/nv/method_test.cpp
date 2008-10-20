#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/nv/method/getters.hpp>

#include <risa_gl/pixel.hpp>

#include <risa_gl/nv/environment.hpp>


typedef environments::cplusplus environment_type;

class getters_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(getters_test);
	CPPUNIT_TEST(source_color_getter_test);
 	CPPUNIT_TEST(source_alpha_getter_test);
	CPPUNIT_TEST(inverse_source_alpha_getter_test);
	CPPUNIT_TEST(destination_color_getter_test);
 	CPPUNIT_TEST(destination_alpha_getter_test);
	CPPUNIT_TEST(inverse_destination_alpha_getter_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void source_color_getter_test()
	{
		risa_gl::pixel src_pix (1, 2, 3, 4);
		risa_gl::pixel dest_pix (5, 6, 7, 8);

		method::source_color_getter<environment_type> src_getter;

		environment_type::bit_pattern_type result =
			src_getter(src_pix, dest_pix);

		
		CPPUNIT_ASSERT_EQUAL(0x03030201U, result);
	}

	void source_alpha_getter_test()
	{
		risa_gl::pixel src_pix (1, 2, 3, 4);
		risa_gl::pixel dest_pix (5, 6, 7, 8);

		method::source_alpha_getter<environment_type> src_getter;

		environment_type::bit_pattern_type result =
			src_getter(src_pix, dest_pix);

		
		CPPUNIT_ASSERT_EQUAL(03U, result);
	}

	void inverse_source_alpha_getter_test()
	{
		risa_gl::pixel src_pix (1, 2, 3, 4);
		risa_gl::pixel dest_pix (5, 6, 7, 8);

		method::inverse_source_alpha_getter<environment_type> getter;

		environment_type::bit_pattern_type result =
			getter(src_pix, dest_pix);

		
		CPPUNIT_ASSERT_EQUAL(252U, result);
	}

	void destination_color_getter_test()
	{
		risa_gl::pixel src_pix (1, 2, 3, 4);
		risa_gl::pixel dest_pix (5, 6, 7, 8);

		method::destination_color_getter<environment_type> dest_getter;

		environment_type::bit_pattern_type result =
			dest_getter(src_pix, dest_pix);

		
		CPPUNIT_ASSERT_EQUAL(0x07070605U, result);
	}

	void destination_alpha_getter_test()
	{
		risa_gl::pixel src_pix (1, 2, 3, 4);
		risa_gl::pixel dest_pix (5, 6, 7, 8);

		method::destination_alpha_getter<environment_type>
			destination_alpha_getter;

		environment_type::bit_pattern_type result =
			destination_alpha_getter(src_pix, dest_pix);

		
		CPPUNIT_ASSERT_EQUAL(7U, result);
	}

	void inverse_destination_alpha_getter_test()
	{
		risa_gl::pixel src_pix (1, 2, 3, 4);
		risa_gl::pixel dest_pix (5, 6, 7, 8);

		method::inverse_destination_alpha_getter<environment_type> getter;

		environment_type::bit_pattern_type result =
			getter(src_pix, dest_pix);

		
		CPPUNIT_ASSERT_EQUAL(248U, result);
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( getters_test );
