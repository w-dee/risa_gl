#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/util.hpp>
#include <iostream>
#include <limits>
#include <cstdlib>


using risa_gl::math::util;

class math_util_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(math_util_test);
	CPPUNIT_TEST(ceil_test);
	CPPUNIT_TEST(floor_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void ceil_test()
	{
		int value = 10;
		float fvalue = value;
		float delta = std::numeric_limits<float>::epsilon();
		float greater_than = fvalue + delta * fvalue;
		float less_than = fvalue - delta * fvalue;

		CPPUNIT_ASSERT(fvalue < greater_than);
		CPPUNIT_ASSERT(fvalue > less_than);

		CPPUNIT_ASSERT_EQUAL(util::ceil(fvalue), value);
		CPPUNIT_ASSERT_EQUAL(util::ceil(greater_than), value + 1);
		CPPUNIT_ASSERT_EQUAL(util::ceil(less_than), value);

		value = -10;
		fvalue = value;
		greater_than = fvalue - delta * fvalue;
		less_than = fvalue + delta * fvalue;

		CPPUNIT_ASSERT(fvalue < greater_than);
		CPPUNIT_ASSERT(fvalue > less_than);

		CPPUNIT_ASSERT_EQUAL(util::ceil(fvalue), value);
		CPPUNIT_ASSERT_EQUAL(util::ceil(greater_than), value + 1);
		CPPUNIT_ASSERT_EQUAL(util::ceil(less_than), value);
	}

	void floor_test()
	{
		int value = 10;
		float fvalue = value;
		float delta = std::numeric_limits<float>::epsilon();
		float greater_than = fvalue + delta * fvalue;
		float less_than = fvalue - delta * fvalue;

		CPPUNIT_ASSERT(fvalue < greater_than);
		CPPUNIT_ASSERT(fvalue > less_than);

		CPPUNIT_ASSERT_EQUAL(util::floor(fvalue), value);
		CPPUNIT_ASSERT_EQUAL(util::floor(greater_than), value);
		CPPUNIT_ASSERT_EQUAL(util::floor(less_than), value - 1);

		value = -10;
		fvalue = value;
		greater_than = fvalue - delta * fvalue;
		less_than = fvalue + delta * fvalue;

		CPPUNIT_ASSERT(fvalue < greater_than);
		CPPUNIT_ASSERT(fvalue > less_than);

		CPPUNIT_ASSERT_EQUAL(util::floor(fvalue), value);
		CPPUNIT_ASSERT_EQUAL(util::floor(greater_than), value);
		CPPUNIT_ASSERT_EQUAL(util::floor(less_than), value - 1);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( math_util_test );
