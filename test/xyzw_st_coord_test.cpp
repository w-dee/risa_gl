#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/xyzw_st_coord.hpp>

class xyzw_st_coord_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(xyzw_st_coord_test);
	CPPUNIT_TEST(add_test);
	CPPUNIT_TEST(mul_test);
	CPPUNIT_TEST(normalize_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void add_test()
	{
		using risa_gl::render::xyzw_st_coord;
		typedef xyzw_st_coord<int> xyzw_st_type;

		xyzw_st_type value1(15, 42, 55, 1, 11, 3);
		xyzw_st_type value2(0, -55, 23, 1, -11, 9);

		xyzw_st_type actual1 = value1 + value2;
		xyzw_st_type actual2 = value1 - value2;
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(15, -13, 78, 1, 0, 12), actual1);
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(15, 97, 32, 1, 22, -6), actual2);

		value1 += value2;
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(15, -13, 78, 1, 0, 12), value1);
		value1 -= value2;
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(15, 42, 55, 1, 11, 3), value1);

		xyzw_st_type value3(15, 42, 55, 2, 11, 3);
		xyzw_st_type actual3 = value1 + value3;
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(15 + 7,
										  42 + 21,
										  55 + 27,
										  1,
										  11 + 5,
										  3 + 1), actual3);
	}

	void mul_test()
	{
		using risa_gl::render::xyzw_st_coord;
		typedef xyzw_st_coord<int> xyzw_st_type;

		xyzw_st_type value1(15, 42, 55, 1, 11, 3);

		xyzw_st_type actual1 = value1 * 10;
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(150, 420, 550, 1, 110, 30), actual1);
	}

	void normalize_test()
	{
		using risa_gl::render::xyzw_st_coord;
		typedef xyzw_st_coord<int> xyzw_st_type;

		xyzw_st_type value1(15, 42, 55, 2, 11, 3);

		xyzw_st_type actual1 = value1.to_normalize();
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(7, 21, 27, 1, 5, 1), actual1);
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(15, 42, 55, 2, 11, 3), value1);

		xyzw_st_type actual2 = value1.normalize();
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(7, 21, 27, 1, 5, 1), actual2);
		CPPUNIT_ASSERT_EQUAL(xyzw_st_type(7, 21, 27, 1, 5, 1), value1);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( xyzw_st_coord_test );
