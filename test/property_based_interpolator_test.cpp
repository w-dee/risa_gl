#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/property_based_interpolator.hpp>
#include <risa_gl/math/point.hpp>
#include <risa_gl/math/fraction.hpp>

class property_based_interpolator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(property_based_interpolator_test);
	CPPUNIT_TEST(coord_interpolate_test);
 	CPPUNIT_TEST(fraction_coord_interpolate_test);
 	CPPUNIT_TEST(fraction_stepping_interpolate_test);
	CPPUNIT_TEST_SUITE_END();

public:

	struct y_coord_extractor
	{
		template <typename T>
		T operator()(const risa_gl::math::point<T>& source) const
		{
			return source.get_y();
		}
	};


	void coord_interpolate_test()
	{
		using risa_gl::math::point;
		using risa_gl::render::property_based_interpolator;

		typedef point<int> point_t;
		point_t base(0, 0, 0);
		point_t goal(10, 20, 30);
					
		property_based_interpolator<point_t, y_coord_extractor, int>
			coord_interpolator(base, goal);

		point_t step = coord_interpolator.get_stepping();
		CPPUNIT_ASSERT_EQUAL(step.get_x(),
							 (goal - base).get_x() / goal.get_y());
		CPPUNIT_ASSERT_EQUAL(step.get_y(),
							 (goal - base).get_y() / goal.get_y());
		CPPUNIT_ASSERT_EQUAL(step.get_z(),
							 (goal - base).get_z() / goal.get_y());
	}

	void fraction_coord_interpolate_test()
	{
		using risa_gl::math::point;
		using risa_gl::math::fraction;
		using risa_gl::render::property_based_interpolator;

		typedef fraction<int> fraction_type;
		typedef point<fraction_type> point_t;
		point_t base(0, 0, 0);
		point_t goal(10, 20, 30);
		property_based_interpolator<point_t, y_coord_extractor, int>
			coord_interpolator(base, goal);

		point_t step = coord_interpolator.get_stepping();
		CPPUNIT_ASSERT_EQUAL(step.get_x(),
							 (goal - base).get_x() / goal.get_y());
		CPPUNIT_ASSERT_EQUAL(step.get_y(),
							 (goal - base).get_y() / goal.get_y());
		CPPUNIT_ASSERT_EQUAL(step.get_z(),
							 (goal - base).get_z() / goal.get_y());
	}

	void fraction_stepping_interpolate_test()
	{
		using risa_gl::math::point;
		using risa_gl::math::fraction;
		using risa_gl::render::property_based_interpolator;

		typedef fraction<int> fraction_type;
		typedef point<fraction_type> point_t;
		point_t base(0, 0, 0);
		point_t goal(10, 20, 30);
		property_based_interpolator<point_t, y_coord_extractor, fraction_type>
			coord_interpolator(base, goal);

		for (int offset = 0;
			 offset < coord_interpolator.get_division().get_value();
			 ++offset)
		{
			point_t val = coord_interpolator(offset);

			CPPUNIT_ASSERT_EQUAL(val.get_x(), fraction_type(1 * offset, 2));
			CPPUNIT_ASSERT_EQUAL(val.get_y(), fraction_type(2 * offset, 2));
			CPPUNIT_ASSERT_EQUAL(val.get_z(), fraction_type(3 * offset, 2));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( property_based_interpolator_test );

