#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/fraction.hpp>

using risa_gl::math::fraction;

class fraction_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(fraction_test);
	CPPUNIT_TEST(getter_test);
	CPPUNIT_TEST(reduce_test);
	CPPUNIT_TEST(invert_test);
	CPPUNIT_TEST(get_value_test);
	CPPUNIT_TEST(plus_test);
	CPPUNIT_TEST(minus_test);
	CPPUNIT_TEST(multiply_test);
	CPPUNIT_TEST(divide_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void divide_test()
	{
		CPPUNIT_ASSERT((fraction<int>(1, 2) / fraction<int>(2, 3)) ==
					   fraction<int>(3, 4));

		fraction<int> value(2, 3);
		value /= fraction<int>(6, 5);
		CPPUNIT_ASSERT(value == fraction<int>(10, 18));

		fraction<int> value2(0, 1);
		CPPUNIT_ASSERT_THROW(fraction<int>(0, 1) / value2,
							 std::runtime_error);
	}

	void multiply_test()
	{
		CPPUNIT_ASSERT((fraction<int>(1, 2) * fraction<int>(2, 3)) ==
					   fraction<int>(2, 6));

		fraction<int> value(2, 3);
		value *= fraction<int>(6, 5);
		CPPUNIT_ASSERT(value == fraction<int>(12, 15));
	}

	void minus_test()
	{
		fraction<int> value(10, 3);

		CPPUNIT_ASSERT((value - fraction<int>(7, 4)) ==
					   fraction<int>(40 - 21, 12));

		value -= fraction<int>(7, 4);
		CPPUNIT_ASSERT(value == fraction<int>(40 - 21, 12));
	}

	void plus_test()
	{
		fraction<int> value(10, 3);

		CPPUNIT_ASSERT((value + fraction<int>(7, 4)) ==
					   fraction<int>(40 + 21, 12));

		value += fraction<int>(7, 4);
		CPPUNIT_ASSERT(value == fraction<int>(40 + 21, 12));
	}

	void get_value_test()
	{
		fraction<int> value(10, 3);

		CPPUNIT_ASSERT(value.get_value() == 3);
		CPPUNIT_ASSERT(value.get_invert().get_value() == 0);
	}

	void invert_test()
	{

		fraction<int> value(-10, 3);

		fraction<int> invert_value = value.get_invert();
		CPPUNIT_ASSERT(invert_value == fraction<int>(-3, 10));
		value.invert();
		CPPUNIT_ASSERT(invert_value == value);
	}

	void reduce_test()
	{
		fraction<int> value1(3, 4);

		fraction<int> reduced1 = value1.get_reduce();
		CPPUNIT_ASSERT(reduced1 == value1);
		value1.reduce();
		CPPUNIT_ASSERT(reduced1 == value1);
	}

	void getter_test()
	{
		fraction<int> value(7, 5);

		CPPUNIT_ASSERT(value.get_numerator() == 7);
		CPPUNIT_ASSERT(value.get_denominator() == 5);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( fraction_test );
