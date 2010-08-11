#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/triangle_setup.hpp>
#include <iostream>

class triangle_setup_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(triangle_setup_test);
	CPPUNIT_TEST(interpolate_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void interpolate_test()
	{
		using risa_gl::render::triangle_setup;
		using risa_gl::render::xyzw_st_coord;

		xyzw_st_coord<float> p0(  0.f,   0.f,   1.f, 1.f, 0.f, 0.f);
		xyzw_st_coord<float> p1(200.f,   0.f,   1.f, 1.f, 1.f, 0.f);
		xyzw_st_coord<float> p2(100.f, 100.f, 100.f, 1.f, .5f, .5f);

		triangle_setup<float> setup(p0, p1, p2);
		const int y_size = setup.size();

		typedef std::pair<xyzw_st_coord<float>,xyzw_st_coord<float> > pair_t;
		for (int offset = 0; offset <= y_size; ++offset)
		{
			pair_t head_and_tail = setup[offset];
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( triangle_setup_test );
