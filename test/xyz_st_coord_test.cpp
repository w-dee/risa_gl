#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/xyz_st_coord.hpp>

class xyz_st_coord_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(xyz_st_coord_test);
	CPPUNIT_TEST(property_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void property_test()
	{
		using risa_gl::render::xyz_st_coord;
		typedef xyz_st_coord<int> xyz_st_type;

		xyz_st_type value1(15, 42, 55, 11, 3);
		xyz_st_type value2(0, -55, 23, -11, 9);

		xyz_st_type actual1 = value1 + value2;
		xyz_st_type actual2 = value1 - value2;
		CPPUNIT_ASSERT_EQUAL(xyz_st_type(15, -13, 78, 0, 12), actual1);
		CPPUNIT_ASSERT_EQUAL(xyz_st_type(15, 97, 32, 22, -6), actual2);

		value1 += value2;
		CPPUNIT_ASSERT_EQUAL(xyz_st_type(15, -13, 78, 0, 12), value1);
		value1 -= value2;
		CPPUNIT_ASSERT_EQUAL(xyz_st_type(15, 42, 55, 11, 3), value1);
		
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( xyz_st_coord_test );
