#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/interpolator.hpp>
#include <risa_gl/math/point.hpp>
#include <risa_gl/math/fraction.hpp>

class render_interpolator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(render_interpolator_test);
	CPPUNIT_TEST(coord_interpolate_test);
	CPPUNIT_TEST(fraction_coord_interpolate_test);
	CPPUNIT_TEST(fraction_stepping_interpolate_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void coord_interpolate_test()
	{
		using risa_gl::math::point;
		using risa_gl::render::interpolator;

		typedef point<int> point_t;
		interpolator<point_t, int>
			coord_interpolator(point_t(0, 0, 0),
							   point_t(10, 20, 30),
							   10);

		point_t step = coord_interpolator.get_stepping();
		CPPUNIT_ASSERT_EQUAL(step.get_x(), 1);
		CPPUNIT_ASSERT_EQUAL(step.get_y(), 2);
		CPPUNIT_ASSERT_EQUAL(step.get_z(), 3);
	}

	void fraction_coord_interpolate_test()
	{
		using risa_gl::math::point;
		using risa_gl::math::fraction;
		using risa_gl::render::interpolator;

		typedef fraction<int> fraction_type;
		typedef point<fraction_type> point_t;
		interpolator<point_t, fraction_type>
			coord_interpolator(point_t(fraction_type(0), fraction_type(0), fraction_type(0)),
							   point_t(fraction_type(10), fraction_type(20), fraction_type(30)),
							   fraction_type(10));

		point_t step = coord_interpolator.get_stepping();
		CPPUNIT_ASSERT_EQUAL(step.get_x(), fraction_type(1));
		CPPUNIT_ASSERT_EQUAL(step.get_y(), fraction_type(2));
		CPPUNIT_ASSERT_EQUAL(step.get_z(), fraction_type(3));
	}

	void fraction_stepping_interpolate_test()
	{
		using risa_gl::math::point;
		using risa_gl::math::fraction;
		using risa_gl::render::interpolator;

		typedef fraction<int> fraction_type;
		typedef point<fraction_type> point_t;
		const int division = 100;
		interpolator<point_t, fraction_type>
			coord_interpolator(point_t(fraction_type(0), fraction_type(0), fraction_type(0)),
							   point_t(fraction_type(10), fraction_type(20), fraction_type(30)),
							   fraction_type(division));

		for (int offset = 0;
			 offset < coord_interpolator.get_division().get_value();
			 ++offset)
		{
			point_t val = coord_interpolator.interpolate(fraction_type(offset));

			CPPUNIT_ASSERT_EQUAL(val.get_x(), fraction_type(10 * offset, 100));
			CPPUNIT_ASSERT_EQUAL(val.get_y(), fraction_type(20 * offset, 100));
			CPPUNIT_ASSERT_EQUAL(val.get_z(), fraction_type(30 * offset, 100));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( render_interpolator_test );

