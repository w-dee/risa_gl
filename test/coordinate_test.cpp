#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/region.hpp>

using namespace risa_gl::math;
class coordinate_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(coordinate_test);
	CPPUNIT_TEST(initializeTest);
	CPPUNIT_TEST(copyTest);
	CPPUNIT_TEST(equalationTest);
	CPPUNIT_TEST_SUITE_END();

	typedef coordinate<int> coord_t;

public:
	void initializeTest()
	{
		coord_t pos;
		CPPUNIT_ASSERT(pos.get_x() == 0);
		CPPUNIT_ASSERT(pos.get_y() == 0);

		coord_t pos2(-10, 40);
		CPPUNIT_ASSERT(pos2.get_x() == -10);
		CPPUNIT_ASSERT(pos2.get_y() == 40);
	}

	void copyTest()
	{
		coord_t source(-56, 12);
		coord_t pos1 = source;
		CPPUNIT_ASSERT(pos1.get_x() == -56);
		CPPUNIT_ASSERT(pos1.get_y() == 12);

		source.set_x(92);
		source.set_y(-11);
		pos1 = source;
		CPPUNIT_ASSERT(pos1.get_x() == 92);
		CPPUNIT_ASSERT(pos1.get_y() == -11);
	}

	void equalationTest()
	{

		coord_t a, b;
		CPPUNIT_ASSERT(a == b);
		
		coord_t c(-10, 12), d(-10, 12);
		CPPUNIT_ASSERT(c == d);
		CPPUNIT_ASSERT(c != a);
		CPPUNIT_ASSERT(d != a);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( coordinate_test );

