#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/fixed_point_real.hpp>

using risa_gl::math::fixed_point_real;

class fixed_point_real_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(fixed_point_real_test);
	CPPUNIT_TEST(add_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void add_test()
	{
		typedef fixed_point_real<> fpr_type;
		fpr_type zero;

		CPPUNIT_ASSERT_EQUAL(zero + 1, fpr_type(1));
		CPPUNIT_ASSERT_EQUAL(zero + 1.5f, fpr_type(1.5f));

		zero += 10;
		CPPUNIT_ASSERT_EQUAL(zero, fpr_type(10));
		zero += 25.5f;
		CPPUNIT_ASSERT_EQUAL(zero, fpr_type(35.5f));
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( fixed_point_real_test );

