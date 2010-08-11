#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/interpolator.hpp>
#include <risa_gl/render/projector.hpp>
#include <risa_gl/render/xyzw_st_coord.hpp>
#include <risa_gl/math/point.hpp>
#include <risa_gl/math/fraction.hpp>

#include <iostream>

class render_interpolator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(render_interpolator_test);
	CPPUNIT_TEST(coord_interpolate_test);
	CPPUNIT_TEST(project_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void project_test()
	{
		using risa_gl::render::projector;
		typedef projector<float> projector_t;
		projector_t proj(-1, 1, 1, -1, 1, 100);
		typedef projector_t::vector_type vector_t;
		typedef projector_t::vector_source_type vector_source_t;

		vector_source_t vs[3] = {
			{{ -1.f, -1.f, -50.f, 1.f }},
			{{ 1.f, 0.f, -50.f, 1.f }},
			{{ 0.f, 1.f, -60.f, 1.f }}};

		vector_t v0 = vs[0];
		vector_t v1 = vs[1];
		vector_t v2 = vs[2];

		vector_t p0 = proj.project(v0);
		vector_t p1 = proj.project(v1);
		vector_t p2 = proj.project(v2);

		p0[0] += 1.f;
		p1[0] += 1.f;
		p2[0] += 1.f;
		p0[1] += 1.f;
		p1[1] += 1.f;
		p2[1] += 1.f;

		p0[0] *= 100.f;
		p1[0] *= 100.f;
		p2[0] *= 100.f;
		p0[1] *= 100.f;
		p1[1] *= 100.f;
		p2[1] *= 100.f;

		using risa_gl::render::xyzw_st_coord;

		xyzw_st_coord<float> d0(p0[0], p0[1], p0[2], p0[3], 0.f, 0.f);
		xyzw_st_coord<float> d1(p1[0], p1[1], p1[2], p1[3], 1.f, 0.f);
		xyzw_st_coord<float> d2(p2[0], p2[1], p2[2], p2[3], 1.f, 1.f);

	}

	void coord_interpolate_test()
	{
		using risa_gl::render::xyzw_st_coord;
		using risa_gl::render::st_coord_interpolator;

		typedef xyzw_st_coord<float> point_t;
		st_coord_interpolator<float>
			coord_interpolator(point_t(0.f, 0.f, 1.f, 1.f, 0.f, 0.f),
							   point_t(10.f, 20.f, 30.f, 1.f, 1.f, .5f),
							   10);

		for (int offset = 0; offset <= 10; ++offset)
		{
			risa_gl::render::interpolated_values<float> result =
				coord_interpolator.interpolate(offset);

		}
	}


};

CPPUNIT_TEST_SUITE_REGISTRATION( render_interpolator_test );

