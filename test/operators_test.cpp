#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/operators.hpp>

class operators_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(operators_test);
	CPPUNIT_TEST(dot_product_test);
	CPPUNIT_TEST(cross_product_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void dot_product_test()
	{
		using risa_gl::math::vector3;
		using risa_gl::math::dot_product;

		vector3<float> lhs = vector3<float>(0.f, 0.f, 1.f);

		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(dot_product(lhs, lhs), 1.f, 0.00001f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(
			dot_product(lhs,
						vector3<float>(0.f, 0.f, -1.f)),
			-1.f, 0.00001f);

		CPPUNIT_ASSERT_DOUBLES_EQUAL(
			dot_product(lhs,
						vector3<float>(1.f, 0.f, 0.f)),
			0.f, 0.00001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(
			dot_product(lhs,
						vector3<float>(0.f, 1.f, 0.f)),
			0.f, 0.00001);												 
	}

	void cross_product_test()
	{
		using risa_gl::math::vector3;
		using risa_gl::math::cross_product;

		vector3<float> lhs(1.f, 0.f, 0.f);
		vector3<float> rhs(0.f, 1.f, 0.f);

		vector3<float> result = cross_product(lhs, rhs);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result.x, 0.f, 0.0000001f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result.y, 0.f, 0.0000001f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result.z, 1.f, 0.0000001f);

		result = cross_product(lhs, result);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result.x, 0.f, 0.0000001f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result.y, -1.f, 0.0000001f);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result.z, 0.f, 0.0000001f);
		
	}
		

};

CPPUNIT_TEST_SUITE_REGISTRATION( operators_test );
