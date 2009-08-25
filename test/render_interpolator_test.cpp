#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/interpolator.hpp>
#include <risa_gl/math/point.hpp>
#include <risa_gl/math/fraction.hpp>

#include <iostream>

class render_interpolator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(render_interpolator_test);
	CPPUNIT_TEST(coord_interpolate_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void coord_interpolate_test()
	{
		using risa_gl::render::xyzw_st_coord;
		using risa_gl::render::xyzw_st_coord_interpolator;

		typedef xyzw_st_coord<float> point_t;
		xyzw_st_coord_interpolator<float>
			coord_interpolator(point_t(0.f, 0.f, 1.f, 1.f, 0.f, 0.f),
							   point_t(10.f, 20.f, 30.f, 1.f, 1.f, .5f),
							   10);

		for (int offset = 0; offset <= 10; ++offset)
		{
			risa_gl::render::interpolated_values<float> result =
				coord_interpolator.interpolate(offset);

			std::cout << "(" <<
				result.s << ", " <<
				result.t << ", " <<
				result.z << ") " << std::endl;
		}
	}


};

CPPUNIT_TEST_SUITE_REGISTRATION( render_interpolator_test );

