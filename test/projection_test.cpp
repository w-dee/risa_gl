#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/projection.hpp>

#include <iostream>
#include <cmath>

#define CPPUNIT_ASSERT_INRANGE(lhs, rhs, distance) \
	{\
		double temp = fabs((lhs) - (rhs));\
		CPPUNIT_ASSERT(temp < (distance));\
	}

class projection_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(projection_test);
	CPPUNIT_TEST(projection);
	CPPUNIT_TEST_SUITE_END();

public:
	void projection()
	{
		using risa_gl::math::projection;
		typedef projection<double> projection_t;
		typedef projection_t::vector_type vector_t;
		typedef projection_t::vector_source_type vector_source_t;

		projection_t projector(-1, 1, 1, -1, 1, 100);
		vector_source_t v0s = {{ 0, 0, -1, 1 }};
		vector_t v0 = v0s;

		vector_t t0 = projector.normalize(v0 * projector);

		vector_source_t r0s = {{ 0, 0, -1, -1 }};
		vector_t r0 = r0s;

		
		CPPUNIT_ASSERT_INRANGE(t0[0], r0[0], 0.001);
		CPPUNIT_ASSERT_INRANGE(t0[1], r0[1], 0.001);
		CPPUNIT_ASSERT_INRANGE(t0[2], r0[2], 0.001);

		vector_source_t v1s = {{ 0, 0, -100, 1 }};
		vector_t v1 = v1s;
		
		vector_t t1 = projector.normalize(v1 * projector);
		
		vector_source_t r1s = {{ 0, 0, 1, 1 }};
		vector_t r1 = r1s;

		CPPUNIT_ASSERT_INRANGE(t1[0], r1[0], 0.001);
		CPPUNIT_ASSERT_INRANGE(t1[1], r1[1], 0.001);
		CPPUNIT_ASSERT_INRANGE(t1[2], r1[2], 0.001);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( projection_test );
