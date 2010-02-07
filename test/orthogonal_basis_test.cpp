#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/orthogonal_basis.hpp>
#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/converter.hpp>

class based_matrix_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(based_matrix_test);
	CPPUNIT_TEST(identity_based_matrix_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void identity_based_matrix_test()
	{
		using risa_gl::math::orthogonal_basis;
		typedef orthogonal_basis<float> ortho_basis_t;
		typedef ortho_basis_t::matrix_type matrix_t;
		using risa_gl::math::vector3;
		typedef vector3<float> vector_t;
		using risa_gl::math::converter;
		typedef converter<float> converter_t;
		converter_t conv;

// 		matrix_t mat = based_matrix_t::make_based_matrix(1.f, 1.f, 1.f);
// 		vector_t vec(1.f, 2.f, 3.f);

// 		vector_t result  = conv.to_matrix1x4(vec) * mat;
// 		CPPUNIT_ASSERT_EQUAL(result.x, vec.x);
// 		CPPUNIT_ASSERT_EQUAL(result.y, vec.y);
// 		CPPUNIT_ASSERT_EQUAL(result.z, vec.z);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( based_matrix_test );
