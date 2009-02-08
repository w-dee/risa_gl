#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/texture_point.hpp>

class texture_point_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(texture_point_test);
	CPPUNIT_TEST(property_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void property_test()
	{
		using risa_gl::render::texture_point;
		texture_point<int> tex_geometry(10, -17);
		const texture_point<int>& const_tex_geom = tex_geometry;

		CPPUNIT_ASSERT_EQUAL(tex_geometry.get_s(), 10);
		CPPUNIT_ASSERT_EQUAL(const_tex_geom.get_s(), 10);
		tex_geometry.set_s(- tex_geometry.get_s());
		CPPUNIT_ASSERT_EQUAL(tex_geometry.get_s(), -10);
		CPPUNIT_ASSERT_EQUAL(const_tex_geom.get_s(), -10);

		CPPUNIT_ASSERT_EQUAL(tex_geometry.get_t(), -17);
		CPPUNIT_ASSERT_EQUAL(const_tex_geom.get_t(), -17);
		tex_geometry.set_t(- tex_geometry.get_t());
		CPPUNIT_ASSERT_EQUAL(tex_geometry.get_t(), 17);
		CPPUNIT_ASSERT_EQUAL(const_tex_geom.get_t(), 17);

		std::pair<int, int> st = tex_geometry.get_st();
		std::pair<int, int> actual_st = std::make_pair(-10, 17);
		CPPUNIT_ASSERT_EQUAL(st.first, actual_st.first);
		CPPUNIT_ASSERT_EQUAL(st.second, actual_st.second);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( texture_point_test );
