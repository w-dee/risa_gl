#include <cppunit/extensions/HelperMacros.h>
#include <region.hpp>

using namespace risa_gl;
class region_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(region_test);
	CPPUNIT_TEST(initializeTest);
	CPPUNIT_TEST_SUITE_END();

	typedef region<int> region_t;

public:
	void initializeTest()
	{
		region_t reg1;
		CPPUNIT_ASSERT(reg1.get_left() == 0);
		CPPUNIT_ASSERT(reg1.get_right() == 0);
		CPPUNIT_ASSERT(reg1.get_top() == 0);
		CPPUNIT_ASSERT(reg1.get_bottom() == 0);
		CPPUNIT_ASSERT(reg1.get_width() == 0);
		CPPUNIT_ASSERT(reg1.get_height() == 0);

		region_t reg2(1, 2, 3, 4);
		CPPUNIT_ASSERT(reg2.get_left() == 1);
		CPPUNIT_ASSERT(reg2.get_right() == 3);
		CPPUNIT_ASSERT(reg2.get_top() == 2);
		CPPUNIT_ASSERT(reg2.get_bottom() == 4);
		CPPUNIT_ASSERT(reg2.get_width() == 2);
		CPPUNIT_ASSERT(reg2.get_height() == 2);

		region_t reg3 = reg2;
		CPPUNIT_ASSERT(reg3.get_left() == 1);
		CPPUNIT_ASSERT(reg3.get_right() == 3);
		CPPUNIT_ASSERT(reg3.get_top() == 2);
		CPPUNIT_ASSERT(reg3.get_bottom() == 4);
		CPPUNIT_ASSERT(reg3.get_width() == 2);
		CPPUNIT_ASSERT(reg3.get_height() == 2);

		reg1 = reg3;
		CPPUNIT_ASSERT(reg1.get_left() == 1);
		CPPUNIT_ASSERT(reg1.get_right() == 3);
		CPPUNIT_ASSERT(reg1.get_top() == 2);
		CPPUNIT_ASSERT(reg1.get_bottom() == 4);
		CPPUNIT_ASSERT(reg1.get_width() == 2);
		CPPUNIT_ASSERT(reg1.get_height() == 2);
	}
	

};

CPPUNIT_TEST_SUITE_REGISTRATION( region_test );
