#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <risa_gl/nv/scatter.hpp>

class scatter_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(scatter_test);
	CPPUNIT_TEST(utility_test);
	CPPUNIT_TEST(through_test);
	CPPUNIT_TEST(odd_test);
	CPPUNIT_TEST(even_test);
	CPPUNIT_TEST(first_test);
	CPPUNIT_TEST(second_test);
	CPPUNIT_TEST(lower_test);
	CPPUNIT_TEST(higher_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void lower_test()
	{
		scatter::lower<unsigned long long> lower_masker;
		unsigned long long result = lower_masker(0xffffffffffffffffULL);

		CPPUNIT_ASSERT_EQUAL(0xffffffffULL, result);
	}

	void higher_test()
	{
		scatter::higher<unsigned long long> higher_masker;
		unsigned long long result = higher_masker(0xdeadbeafffffffffULL);

		CPPUNIT_ASSERT_EQUAL(0xdeadbeafULL, result);
	}

	void utility_test()
	{
		CPPUNIT_ASSERT_EQUAL(0xff00ffU,
							 scatter::gen_odd_mask<unsigned int>());
		CPPUNIT_ASSERT_EQUAL(0xff00ff00U,
							 scatter::gen_even_mask<unsigned int>());
		CPPUNIT_ASSERT_EQUAL(0xffffU,
							 scatter::gen_first_mask<unsigned int>());
		CPPUNIT_ASSERT_EQUAL(0xffff0000U,
							 scatter::gen_second_mask<unsigned int>());
	}

	void through_test()
	{
		scatter::through<unsigned int> func;

		CPPUNIT_ASSERT_EQUAL(0x04030201U, func(0x04030201));
	}

	void odd_test()
	{
		scatter::odd<unsigned int> func;

		CPPUNIT_ASSERT_EQUAL(0x030001U, func(0x04030201));
	}

	void even_test()
	{
		scatter::even<unsigned int> func;

		CPPUNIT_ASSERT_EQUAL(0x040002U, func(0x04030201));
	}

	void first_test()
	{
		scatter::first<unsigned int> func;

		CPPUNIT_ASSERT_EQUAL(0x0201U, func(0x04030201));
	}

	void second_test()
	{
		scatter::second<unsigned int> func;

		CPPUNIT_ASSERT_EQUAL(0x0403U, func(0x04030201));
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( scatter_test );

