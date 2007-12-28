#include <cppunit/extensions/HelperMacros.h>
#include <math/matrix.hpp>

using risa_gl::math::matrix;

class matrix_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(matrix_test);
	CPPUNIT_TEST(initial_test);
	CPPUNIT_TEST_SUITE_END();

public:

	void initial_test()
	{
		typedef matrix<float, 4, 4> matrix_t;

		matrix_t::elements_type mat_src = { 2, 0, 0, 0,
											0, 2, 0, 0,
											0, 0, 2, 0,
											0, 0, 0, 1 };
		matrix_t mat = mat_src;

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( matrix_test );
