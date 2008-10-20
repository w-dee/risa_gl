#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/nv/math.hpp>

class math_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(math_test);
	CPPUNIT_TEST(range_test);
	CPPUNIT_TEST(projector_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void range_test()
	{
		typedef math::range<unsigned int, 3, 102> test_range_t;

		CPPUNIT_ASSERT_EQUAL(3U, test_range_t::min());
		CPPUNIT_ASSERT_EQUAL(102U, test_range_t::max());
		CPPUNIT_ASSERT_EQUAL(99U, test_range_t::distance());
	}

	void projector_test()
	{
		typedef math::range<unsigned int, 3, 103> src_range_t;
		typedef math::range<int, -50, 50> dest_range_t;

		math::projector<src_range_t, dest_range_t> projector;

		CPPUNIT_ASSERT_EQUAL(-20, projector(33));
		CPPUNIT_ASSERT_EQUAL(30, projector(83));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( math_test );
