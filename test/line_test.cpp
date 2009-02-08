#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/line.hpp>
#include <risa_gl/math/fraction.hpp>
#include "range.hpp"

class line_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(line_test);
	CPPUNIT_TEST(distance_test);
	CPPUNIT_TEST(limit_test);
	CPPUNIT_TEST(fraction_limit_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void fraction_limit_test()
	{
		using risa_gl::render::line;
		using risa_gl::math::fraction;
		typedef fraction<int> fraction_type;
		typedef line<fraction_type> line_type;
		typedef line_type::point_type point_t;

		line_type line0(point_t(0, 0, 0), point_t(1, 2, 3));
		CPPUNIT_ASSERT_EQUAL(line0.get_dxdy(),
							  fraction_type(1, 2));
		CPPUNIT_ASSERT_EQUAL(line0.get_dzdy(),
							 fraction_type(3, 2));

		line_type line1(point_t(-1, -2, -3), point_t(0, 0, 0));
		CPPUNIT_ASSERT_EQUAL(line1.get_dxdy(),
							  fraction_type(1, 2));
		CPPUNIT_ASSERT_EQUAL(line1.get_dzdy(),
							 fraction_type(3, 2));


		line_type line2(point_t(-1, -2, -3), point_t(1, 2, 3));
		CPPUNIT_ASSERT_EQUAL(line2.get_dxdy(),
							  fraction_type(2, 4));
		CPPUNIT_ASSERT_EQUAL(line2.get_dzdy(),
							 fraction_type(6, 4));


		line_type line3(point_t(0, 0, 0), point_t(-1, -2, -3));
		CPPUNIT_ASSERT_EQUAL(line3.get_dxdy(),
							  fraction_type(1, 2));
		CPPUNIT_ASSERT_EQUAL(line3.get_dzdy(),
							 fraction_type(3, 2));

	}

	void limit_test()
	{
		using risa_gl::render::line;
		typedef line<float> line_t;
		typedef line_t::point_type point_t;

		line_t line0(point_t(0, 0, 0), point_t(1, 2, 3));
		CPPUNIT_ASSERT(range(line0.get_dxdy(), 1.f / 2.f, 0.00001f));
		CPPUNIT_ASSERT(range(line0.get_dzdy(), 3.f / 2.f, 0.00001f));

		line_t line1(point_t(-1, -2, -3), point_t(0, 0, 0));
		CPPUNIT_ASSERT(range(line1.get_dxdy(), 1.f/2.f, 0.00001f));
		CPPUNIT_ASSERT(range(line1.get_dzdy(), 3.f/2.f, 0.00001f));

		line_t line2(point_t(-1, -2, -3), point_t(1, 2, 3));
		CPPUNIT_ASSERT(range(line2.get_dxdy(), 2.f/4.f, 0.00001f));
		CPPUNIT_ASSERT(range(line2.get_dzdy(), 6.f/4.f, 0.00001f));

		line_t line3(point_t(0, 0, 0), point_t(-1, -2, -3));
		CPPUNIT_ASSERT(range(line3.get_dxdy(), -1.f/-2.f, 0.00001f));
		CPPUNIT_ASSERT(range(line3.get_dzdy(), -3.f/-2.f, 0.00001f));
	}
	
	void distance_test()
	{
		using risa_gl::render::line;
		typedef line<int> line_t;
		typedef line_t::point_type point_t;

		line_t line0(point_t(0, 0, 0), point_t(1, 2, 3));
		CPPUNIT_ASSERT_EQUAL(line0.get_x_length(), 1);
		CPPUNIT_ASSERT_EQUAL(line0.get_y_length(), 2);
		CPPUNIT_ASSERT_EQUAL(line0.get_z_length(), 3);

		line_t line1(point_t(-1, -2, -3), point_t(0, 0, 0));
		CPPUNIT_ASSERT_EQUAL(line1.get_x_length(), 1);
		CPPUNIT_ASSERT_EQUAL(line1.get_y_length(), 2);
		CPPUNIT_ASSERT_EQUAL(line1.get_z_length(), 3);

		line_t line2(point_t(-1, -2, -3), point_t(1, 2, 3));
		CPPUNIT_ASSERT_EQUAL(line2.get_x_length(), 2);
		CPPUNIT_ASSERT_EQUAL(line2.get_y_length(), 4);
		CPPUNIT_ASSERT_EQUAL(line2.get_z_length(), 6);

		line_t line3(point_t(0, 0, 0), point_t(-1, -2, -3));
		CPPUNIT_ASSERT_EQUAL(line3.get_x_length(), -1);
		CPPUNIT_ASSERT_EQUAL(line3.get_y_length(), -2);
		CPPUNIT_ASSERT_EQUAL(line3.get_z_length(), -3);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( line_test );
