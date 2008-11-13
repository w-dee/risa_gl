#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/math/matrix.hpp>
#include <iostream>
#include <cmath>

using risa_gl::math::matrix;

class matrix_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(matrix_test);
	CPPUNIT_TEST(add_test);
	CPPUNIT_TEST(negate_test);
	CPPUNIT_TEST(sub_test);
	CPPUNIT_TEST(initial_test);
	CPPUNIT_TEST(multiply_test);
	CPPUNIT_TEST(min_multiply_test);
	CPPUNIT_TEST(asymetric_multiply_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void add_test()
	{
		typedef matrix<float, 4, 4> matrix_t;
		matrix_t::elements_type lhs = { {  0,  1,  2,  3,
										   4,  5,  6,  7,
										   8,  9, 10, 11,
										   12, 13, 14, 15 } };
		matrix_t::elements_type rhs = { {  16, 17, 18, 19,
										   20, 21, 22, 23,
										   24, 25, 26, 27,
										   28, 29, 30, 31 } };
		matrix_t::elements_type result = { { 16, 18, 20, 22,
											 24, 26, 28, 30,
											 32, 34, 36, 38,
											 40, 42, 44, 46 } };

		matrix_t lhs_m(lhs);
		matrix_t rhs_m(rhs);
		matrix_t res_m(result);

		CPPUNIT_ASSERT(res_m == lhs_m + rhs_m);

		lhs_m += rhs_m;
		CPPUNIT_ASSERT(res_m == lhs_m);
	}

	void negate_test()
	{
		typedef matrix<float, 4, 4> matrix_t;
		matrix_t::elements_type value = { {  16, 17, 18, 19,
											 20, 21, 22, 23,
											 24, 25, 26, 27,
											 28, 29, 30, 31 } };
		matrix_t::elements_type result = { {  -16, -17, -18, -19,
											  -20, -21, -22, -23,
											  -24, -25, -26, -27,
											  -28, -29, -30, -31 } };

		matrix_t val_m(value);
		matrix_t res_m(result);

		CPPUNIT_ASSERT(res_m == val_m.get_negate());
		val_m.negate();
		CPPUNIT_ASSERT(res_m == val_m);
	}

	void sub_test()
	{
		typedef matrix<float, 4, 4> matrix_t;
		matrix_t::elements_type lhs = { {  16, 17, 18, 19,
										   20, 21, 22, 23,
										   24, 25, 26, 27,
										   28, 29, 30, 31 } };
		matrix_t::elements_type rhs = { {  0,  1,  2,  3,
										   4,  5,  6,  7,
										   8,  9, 10, 11,
										   12, 13, 14, 15 } };
		matrix_t::elements_type result = { { 16, 16, 16, 16,
											 16, 16, 16, 16,
											 16, 16, 16, 16,
											 16, 16, 16, 16 } };

		matrix_t lhs_m(lhs);
		matrix_t rhs_m(rhs);
		matrix_t res_m(result);

		CPPUNIT_ASSERT(res_m == (lhs_m - rhs_m));

		lhs_m -= rhs_m;
		CPPUNIT_ASSERT(res_m == lhs_m);
	}

	void asymetric_multiply_test()
	{
		typedef matrix<float, 4, 4> matrix4_t;
		typedef matrix<float, 4, 1> vector4_t;
		const float pi = 3.1415926535f;
		matrix4_t::elements_type mat =
			{ { std::cos(pi/2), std::sin(pi/2), 0, 0,
				-std::sin(pi/2), std::cos(pi/2), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1} };
		vector4_t::elements_type vec = { { 1, 1, 0, 0 } };

		vector4_t result = matrix4_t(mat) * vector4_t(vec);
		CPPUNIT_ASSERT(result(0) > 0.99999f && result(0) < 1.00000001f);
		CPPUNIT_ASSERT(result(1) < -0.99999f && result(0) > -1.00000001f);
		CPPUNIT_ASSERT(result(2) == 0.f);
		CPPUNIT_ASSERT(result(3) == 0.f);
	}

	void min_multiply_test()
	{
		typedef matrix<float, 2, 2> matrix_t;
		matrix_t::elements_type lhs = { {  5,  6,
										   7,  8 } };

		matrix_t::elements_type rhs = { {  1,  2,
										   3,  4 } };

		matrix_t::elements_type result1 = { { 23, 34,
											  31, 46 } };

		matrix_t result = matrix_t(lhs) * matrix_t(rhs);
		
		CPPUNIT_ASSERT(result == matrix_t(result1));
	}

	void multiply_test()
	{
		typedef matrix<float, 4, 4> matrix_t;
		matrix_t::elements_type lhs = { {  0,  1,  2,  3,
										 4,  5,  6,  7,
										 8,  9, 10, 11,
										 12, 13, 14, 15 } };
		matrix_t::elements_type rhs = { { 16, 17, 18, 19,
										  20, 21, 22, 23,
										  24, 25, 26, 27,
										  28, 29, 30, 31 } };

		matrix_t::elements_type result1 = { {  152,  158,  164,  170,
											   504,  526,  548,  570,
											   856,  894,  932,  970,
											   1208, 1262, 1316, 1370 } };
		matrix_t::elements_type result2 = { {  440,  510,  580,  650,
											   536,  622,  708,  794,
											   632,  734,  836,  938,
											   728,  846,  964, 1082 } };

		matrix_t result = matrix_t(lhs) * matrix_t(rhs);
		CPPUNIT_ASSERT(result == matrix_t(result1));

		result = matrix_t(rhs) * matrix_t(lhs);
		CPPUNIT_ASSERT(result == matrix_t(result2));
	}

	void initial_test()
	{
		typedef matrix<float, 4, 4> matrix_t;

		matrix_t::elements_type mat_src = { { 2, 0, 0, 0,
											  0, 2, 0, 0,
											  0, 0, 2, 0,
											  0, 0, 0, 1 } };
		matrix_t mat = mat_src;
		CPPUNIT_ASSERT(mat(0,0) == 2);
		CPPUNIT_ASSERT(mat(1,0) == 0);
		CPPUNIT_ASSERT(mat(2,0) == 0);
		CPPUNIT_ASSERT(mat(3,0) == 0);
		CPPUNIT_ASSERT(mat(0,1) == 0);
		CPPUNIT_ASSERT(mat(1,1) == 2);
		CPPUNIT_ASSERT(mat(2,1) == 0);
		CPPUNIT_ASSERT(mat(3,1) == 0);
		CPPUNIT_ASSERT(mat(0,2) == 0);
		CPPUNIT_ASSERT(mat(1,2) == 0);
		CPPUNIT_ASSERT(mat(2,2) == 2);
		CPPUNIT_ASSERT(mat(3,2) == 0);
		CPPUNIT_ASSERT(mat(0,3) == 0);
		CPPUNIT_ASSERT(mat(1,3) == 0);
		CPPUNIT_ASSERT(mat(2,3) == 0);
		CPPUNIT_ASSERT(mat(3,3) == 1);

		mat = matrix_t(0);
		CPPUNIT_ASSERT(mat(0,0) == 0);
		CPPUNIT_ASSERT(mat(1,0) == 0);
		CPPUNIT_ASSERT(mat(2,0) == 0);
		CPPUNIT_ASSERT(mat(3,0) == 0);
		CPPUNIT_ASSERT(mat(0,1) == 0);
		CPPUNIT_ASSERT(mat(1,1) == 0);
		CPPUNIT_ASSERT(mat(2,1) == 0);
		CPPUNIT_ASSERT(mat(3,1) == 0);
		CPPUNIT_ASSERT(mat(0,2) == 0);
		CPPUNIT_ASSERT(mat(1,2) == 0);
		CPPUNIT_ASSERT(mat(2,2) == 0);
		CPPUNIT_ASSERT(mat(3,2) == 0);
		CPPUNIT_ASSERT(mat(0,3) == 0);
		CPPUNIT_ASSERT(mat(1,3) == 0);
		CPPUNIT_ASSERT(mat(2,3) == 0);
		CPPUNIT_ASSERT(mat(3,3) == 0);

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( matrix_test );
