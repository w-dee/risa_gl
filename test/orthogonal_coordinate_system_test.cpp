#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/orthogonal_coordinate_system.hpp>

class orthogonal_coordinate_system_test : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(orthogonal_coordinate_system_test);
	CPPUNIT_TEST(getter_test);
	CPPUNIT_TEST_SUITE_END();

private:
	void getter_test()
	{
		using risa_gl::math::orthogonal_coordinate_system;
		using risa_gl::math::vector3;

		typedef orthogonal_coordinate_system<float> three_axis_t;
		three_axis_t normal(1.f, 0.f, 0.f,
							0.f, 1.f, 0.f,
							0.f, 0.f, 1.f);

		CPPUNIT_ASSERT_EQUAL(normal.get_x_axis(),
							 vector3<float>(1.f, 0.f, 0.f));
		CPPUNIT_ASSERT_EQUAL(normal.get_y_axis(),
							 vector3<float>(0.f, 1.f, 0.f));
		CPPUNIT_ASSERT_EQUAL(normal.get_z_axis(),
							 vector3<float>(0.f, 0.f, 1.f));

	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( orthogonal_coordinate_system_test );
