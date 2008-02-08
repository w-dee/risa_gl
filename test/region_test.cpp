#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/region.hpp>

using namespace risa_gl::math;
class region_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(region_test);
	CPPUNIT_TEST(initializeTest);
	CPPUNIT_TEST_SUITE_END();

	typedef rectangle_region<int> region_t;

public:
	void initializeTest()
	{
		region_t reg1;
		CPPUNIT_ASSERT(reg1.get_left_up() == region_t::coord_type());
		CPPUNIT_ASSERT(reg1.get_right_up() == region_t::coord_type());
		CPPUNIT_ASSERT(reg1.get_left_down() == region_t::coord_type());
		CPPUNIT_ASSERT(reg1.get_right_down() == region_t::coord_type());

		region_t reg2(1, 2, 3, 4);
		CPPUNIT_ASSERT(reg2.get_left_up() == region_t::coord_type(1, 2));
		CPPUNIT_ASSERT(reg2.get_right_up() == region_t::coord_type(3, 2));
		CPPUNIT_ASSERT(reg2.get_left_down() == region_t::coord_type(1, 4));
		CPPUNIT_ASSERT(reg2.get_right_down() == region_t::coord_type(3, 4));

		region_t reg3 = reg2;
		CPPUNIT_ASSERT(reg3.get_left_up() == region_t::coord_type(1, 2));
		CPPUNIT_ASSERT(reg3.get_right_up() == region_t::coord_type(3, 2));
		CPPUNIT_ASSERT(reg3.get_left_down() == region_t::coord_type(1, 4));
		CPPUNIT_ASSERT(reg3.get_right_down() == region_t::coord_type(3, 4));

		reg1 = reg3;
		CPPUNIT_ASSERT(reg1.get_left_up() == region_t::coord_type(1, 2));
		CPPUNIT_ASSERT(reg1.get_right_up() == region_t::coord_type(3, 2));
		CPPUNIT_ASSERT(reg1.get_left_down() == region_t::coord_type(1, 4));
		CPPUNIT_ASSERT(reg1.get_right_down() == region_t::coord_type(3, 4));
	}
	

};

CPPUNIT_TEST_SUITE_REGISTRATION( region_test );
