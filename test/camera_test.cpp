#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/render/camera.hpp>
#include <risa_gl/math/matrix_operation.hpp>

class camera_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(camera_test);
	CPPUNIT_TEST(transform_test);
	CPPUNIT_TEST_SUITE_END();
public:

	void transform_test()
	{
		using risa_gl::render::camera;

		typedef camera<float> camera_type;
		typedef camera_type::matrix_type matrix_t;
		typedef camera_type::vector3_type vector_t;

		camera_type cam(vector_t(0, 0, -1),
						   vector_t(0, 1, 0),
						   vector_t(1, 0, -1));

		matrix_t rotator = cam.get_matrix();
		
		vector_t object (1, 0, -1);
		vector_t actual (0, 0, 1);

		CPPUNIT_ASSERT_EQUAL(object * rotator, actual);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( camera_test );
