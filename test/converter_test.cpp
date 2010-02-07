#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/converter.hpp>

class converter_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(converter_test);
	CPPUNIT_TEST(matrix1x4_convert_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void matrix1x4_convert_test() 
	{
		using risa_gl::math::converter;
		using risa_gl::math::vector2;
		typedef converter<double> converter_t;
		typedef vector2<double> vector2_t;
		typedef converter_t::matrix1x4_type matrix1x4_t;

		converter_t conv;
		vector2_t source(10.1, 20.2);

		matrix1x4_t result = conv.to_matrix1x4(source);
		CPPUNIT_ASSERT_EQUAL(result[0], 10.1);
		CPPUNIT_ASSERT_EQUAL(result[1], 20.2);
		CPPUNIT_ASSERT_EQUAL(result[2], 0.);
		CPPUNIT_ASSERT_EQUAL(result[3], 1.);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( converter_test );
