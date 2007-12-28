#include <cppunit/extensions/HelperMacros.h>
#include <transformer.hpp>
#include <math/vector.hpp>
#include <iostream>

class transformer_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(transformer_test);
	CPPUNIT_TEST(multiply2d_test);
	CPPUNIT_TEST(multiply3d_test);
	CPPUNIT_TEST(multiply4d_test);
	CPPUNIT_TEST(region_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void region_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::region;

		typedef region<float> region_t;
		region_t rect(-1.f, -2.f, 3.f, 4.f);
		
		linear_transformer transformer;

		region_t rect_t = transformer * rect;
		CPPUNIT_ASSERT(rect_t.get_left() == -1.f);
		CPPUNIT_ASSERT(rect_t.get_top() == -2.f);
		CPPUNIT_ASSERT(rect_t.get_right() == 3.f);
		CPPUNIT_ASSERT(rect_t.get_bottom() == 4.f);

		const float mat[4][4] = {{ 0.f, 1.f, 0.f, 0.f},
								 {-1.f, 0.f, 0.f, 0.f},
								 { 0.f, 0.f, 1.f, 0.f},
								 { 0.f, 0.f, 0.f, 1.f}};
		transformer = linear_transformer(mat);

		rect_t = transformer * rect;
		std::cout <<
			"(" <<
			rect_t.get_left() << ", " << rect_t.get_top() << 
			")-(" <<
			rect_t.get_right() << ", " << rect_t.get_bottom() <<
			")" << std::endl;
			
		CPPUNIT_ASSERT(rect_t.get_left() == -2.f);
		CPPUNIT_ASSERT(rect_t.get_top() == -1.f);
		CPPUNIT_ASSERT(rect_t.get_right() == 4.f);
		CPPUNIT_ASSERT(rect_t.get_bottom() == -3.f);
	}

	void multiply2d_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector2;

		linear_transformer transformer;
		vector2 v(2.f, 3.f);

		vector2 v_t = (transformer * v);
		CPPUNIT_ASSERT(v_t.x == v.x);
		CPPUNIT_ASSERT(v_t.y == v.y);

		const float mat[4][4] = {{ 0.f, 1.f, 0.f, 0.f},
								 {-1.f, 0.f, 0.f, 0.f},
								 { 0.f, 0.f, 1.f, 0.f},
								 { 0.f, 0.f, 0.f, 1.f}};
		transformer = linear_transformer(mat);

		v_t = transformer * v;
		CPPUNIT_ASSERT(v_t.x == -3.f);
		CPPUNIT_ASSERT(v_t.y == 2.f);
		
	}

	void multiply3d_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector3;

		linear_transformer transformer;
		vector3 v(2.f, 3.f, 4.f);

		vector3 v_t = (transformer * v);
		CPPUNIT_ASSERT(v_t.x == v.x);
		CPPUNIT_ASSERT(v_t.y == v.y);
		CPPUNIT_ASSERT(v_t.z == v.z);

		const float mat[4][4] = {{ 1.f, 0.f, 0.f, 0.f},
								 { 0.f, 0.f, 1.f, 0.f},
								 { 0.f,-1.f, 0.f, 0.f},
								 { 0.f, 0.f, 0.f, 1.f}};
		transformer = linear_transformer(mat);

		v_t = transformer * v;
		CPPUNIT_ASSERT(v_t.x == 2.f);
		CPPUNIT_ASSERT(v_t.y ==-4.f);
		CPPUNIT_ASSERT(v_t.z == 3.f);
	}

	void multiply4d_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector4;

		linear_transformer transformer;
		vector4 v(2.f, 3.f, 4.f, 1.f);

		vector4 v_t = (transformer * v);
		CPPUNIT_ASSERT(v_t.x == v.x);
		CPPUNIT_ASSERT(v_t.y == v.y);
		CPPUNIT_ASSERT(v_t.z == v.z);
		CPPUNIT_ASSERT(v_t.w == v.w);

		const float mat[4][4] = {{ 0.f, 0.f,-1.f, 0.f},
								 { 0.f, 1.f, 0.f, 0.f},
								 { 1.f, 0.f, 0.f, 0.f},
								 { 0.f, 0.f, 0.f, 1.f}};
		transformer = linear_transformer(mat);

		v_t = transformer * v;
		CPPUNIT_ASSERT(v_t.x == 4.f);
		CPPUNIT_ASSERT(v_t.y == 3.f);
		CPPUNIT_ASSERT(v_t.z ==-2.f);
		CPPUNIT_ASSERT(v_t.w == 1.f);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(transformer_test);
