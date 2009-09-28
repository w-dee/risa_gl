#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/viewport.hpp>

class viewport_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(viewport_test);
	CPPUNIT_TEST(project_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void project_test()
	{
		using risa_gl::render::viewport;
		using risa_gl::math::coordinate;

		typedef coordinate<float> coord_type;
		typedef viewport<float> viewport_type;

		viewport_type vp0(0.f, 0.f, 640.f, 480.f);
		CPPUNIT_ASSERT_EQUAL(0.f, vp0.get_x_offset());
		CPPUNIT_ASSERT_EQUAL(0.f, vp0.get_y_offset());
		CPPUNIT_ASSERT_EQUAL(320.f, vp0.get_x_scale());
		CPPUNIT_ASSERT_EQUAL(240.f, vp0.get_y_scale());

		CPPUNIT_ASSERT_EQUAL(coord_type(0.f, 0.f),
							 vp0.project(coord_type(-1.f, -1.f)));

		viewport_type vp1(1.f, 1.f, 641.f, 481.f);
		CPPUNIT_ASSERT_EQUAL(1.f, vp1.get_x_offset());
		CPPUNIT_ASSERT_EQUAL(1.f, vp1.get_y_offset());
		CPPUNIT_ASSERT_EQUAL(320.f, vp1.get_x_scale());
		CPPUNIT_ASSERT_EQUAL(240.f, vp1.get_y_scale());

		CPPUNIT_ASSERT_EQUAL(coord_type(1.f, 1.f),
							 vp1.project(coord_type(-1.f, -1.f)));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( viewport_test );
