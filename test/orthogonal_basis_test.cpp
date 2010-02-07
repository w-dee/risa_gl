#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/orthogonal_basis.hpp>
#include <risa_gl/math/vector.hpp>
#include <risa_gl/math/converter.hpp>
#include <risa_gl/math/operators.hpp>
#include <risa_gl/math/matrix_operation.hpp>

class orthogonal_basis_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(orthogonal_basis_test);
	CPPUNIT_TEST(identity_basis_test);
	CPPUNIT_TEST(yxz_basis_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void identity_basis_test()
	{
		using risa_gl::math::orthogonal_basis;
		typedef orthogonal_basis<float> ortho_basis_t;
		typedef ortho_basis_t::matrix_type matrix_t;
		using risa_gl::math::vector3;
		typedef vector3<float> vector_t;

		matrix_t identity_mat =
			ortho_basis_t::make_orthogonal_basis(1.f, 0.f, 0.f,
												 0.f, 1.f, 0.f,
												 0.f, 0.f, 1.f);
		vector_t vec(1.f, 2.f, 3.f);

		vector_t result  = vec * identity_mat;
		CPPUNIT_ASSERT_EQUAL(result.x, vec.x);
		CPPUNIT_ASSERT_EQUAL(result.y, vec.y);
		CPPUNIT_ASSERT_EQUAL(result.z, vec.z);
	}

	void yxz_basis_test()
	{
		using risa_gl::math::orthogonal_basis;
		typedef orthogonal_basis<float> ortho_basis_t;
		typedef ortho_basis_t::matrix_type matrix_t;
		using risa_gl::math::vector3;
		typedef vector3<float> vector_t;

		matrix_t yxz_mat =
			ortho_basis_t::make_orthogonal_basis(0.f, 1.f, 0.f,
												 1.f, 0.f, 0.f,
												 0.f, 0.f, 1.f);
		vector_t vec(1.f, 2.f, 3.f);

		vector_t result  = vec * yxz_mat;
		CPPUNIT_ASSERT_EQUAL(result.x, vec.y);
		CPPUNIT_ASSERT_EQUAL(result.y, vec.x);
		CPPUNIT_ASSERT_EQUAL(result.z, vec.z);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( orthogonal_basis_test );
