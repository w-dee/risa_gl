#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/transformer.hpp>
#include <risa_gl/math/vector.hpp>
#include <risa_gl/interpolate.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/pixel.hpp>
#include <iostream>

#include "range.hpp"

const float pi = 3.14159265358979f;

class transformer_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(transformer_test);
	CPPUNIT_TEST(multiply2d_test);
	CPPUNIT_TEST(multiply3d_test);
	CPPUNIT_TEST(multiply4d_test);
	CPPUNIT_TEST(coord_test);
	CPPUNIT_TEST(region_test);
	CPPUNIT_TEST(translate_test);
	CPPUNIT_TEST(rotate_test);
	CPPUNIT_TEST(operation_order_test);
	CPPUNIT_TEST(scaling_test);
	CPPUNIT_TEST(transform_test);
	CPPUNIT_TEST(translator_test);
	CPPUNIT_TEST(rotator_test);
	CPPUNIT_TEST(scaler_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void scaler_test()
	{
		using risa_gl::scaler;
		using risa_gl::math::rectangle_region;
		using risa_gl::math::vector2;
		using risa_gl::math::vector4;

		typedef risa_gl::scaler<float> scaler_t;

		rectangle_region<float> region(0, 0, 64, 64);
		scaler_t trans(region,
					   vector2(32, 32),
					   2.f, 2.f);

		scaler_t::projected_type projected = trans.get_projected_region();
		rectangle_region<float> projected_region = projected.get_region();
		CPPUNIT_ASSERT(
			projected_region.get_left_down() ==
			risa_gl::coordinate<float>(-32, -32));
		CPPUNIT_ASSERT(
			projected_region.get_right_up() ==
			risa_gl::coordinate<float>(96, 96));

		risa_gl::coordinate<float> x_diff = projected.get_x_difference();
		risa_gl::coordinate<float> y_diff = projected.get_y_difference();

		CPPUNIT_ASSERT(range(x_diff.get_x(), 2.f, 0.01f));
		CPPUNIT_ASSERT(range(x_diff.get_y(), 0.f, 0.01f));
		CPPUNIT_ASSERT(range(y_diff.get_x(), 0.f, 0.01f));
		CPPUNIT_ASSERT(range(y_diff.get_y(), 2.f, 0.01f));
	}

	void rotator_test()
	{
		using risa_gl::rotator;
		using risa_gl::math::rectangle_region;
		using risa_gl::math::vector2;

		typedef rectangle_region<float> region_t;
		typedef region_t::coord_type coord_t;
		typedef risa_gl::pixel pixel_t;
		typedef risa_gl::pixel_store<pixel_t,
			risa_gl::aligned_allocator<pixel_t, 16> > pixel_store_t;

		typedef rotator<float> rotator_t;
		rotator_t trans(region_t(0, 0, 64, 64),
						vector2(32, 32),
						pi / 2.f);

		rotator_t::projected_type projected = trans.get_projected_region();
		rectangle_region<float> projected_region = projected.get_region();
		CPPUNIT_ASSERT(
			range<float>(projected_region.get_left_down().get_x(), 64.f, 0.01));
		CPPUNIT_ASSERT(
			range<float>(projected_region.get_left_down().get_y(), 0.f, 0.01));
		CPPUNIT_ASSERT(
			range<float>(projected_region.get_right_up().get_x(), 0.f, 0.01));
		CPPUNIT_ASSERT(
			range<float>(projected_region.get_right_up().get_y(), 64.f, 0.01));
	}

	void translator_test()
	{
		using risa_gl::translator;
		using risa_gl::math::rectangle_region;

		typedef rectangle_region<float> region_t;
		typedef region_t::coord_type coord_t;

		typedef translator<float> translator_t;
		translator_t trans(region_t(0, 0, 64, 64),
						   risa_gl::math::vector2(-32, -32));

		translator_t::projected_type projected = trans.get_projected_region();
		rectangle_region<float> projected_region = projected.get_region();
		CPPUNIT_ASSERT(
			range(projected_region.get_left_down().get_x(), -32.f, 0.01f));
		CPPUNIT_ASSERT(
			range(projected_region.get_left_down().get_y(), -32.f, 0.01f));

		CPPUNIT_ASSERT(
			range(projected_region.get_right_up().get_x(), 32.f, 0.01f));
		CPPUNIT_ASSERT(
			range(projected_region.get_right_up().get_y(), 32.f, 0.01f));
	}

	void transform_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector2;
		using risa_gl::math::rectangle_region;

		typedef rectangle_region<float> region_t;
		typedef region_t::coord_type coord_t;
		region_t rect_t(-2.f, -2.f, 2.f, 2.f);
		
		CPPUNIT_ASSERT(range(rect_t.get_left_down().get_x(), -2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_left_down().get_y(), -2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_right_down().get_x(), 2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_right_down().get_y(), -2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_left_up().get_x(), -2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_left_up().get_y(), 2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_right_up().get_x(), 2.f, 0.01f));
		CPPUNIT_ASSERT(range(rect_t.get_right_up().get_y(), 2.f, 0.01f));

		rect_t =
			linear_transformer::transform(rect_t,
										  vector2(0.f, 0.f),
										  pi / 4);

		CPPUNIT_ASSERT(range(rect_t.get_left_down().get_x(),
							 0.f, 0.001f));
		CPPUNIT_ASSERT(range(rect_t.get_left_down().get_y(),
							 -std::sqrt(8.f), 0.001f));

		CPPUNIT_ASSERT(range(rect_t.get_right_down().get_x(),
							 std::sqrt(8.f), 0.001f));
		CPPUNIT_ASSERT(range(rect_t.get_right_down().get_y(),
							 0.f, 0.001f));

		CPPUNIT_ASSERT(range(rect_t.get_left_up().get_x(),
							 -std::sqrt(8.f), 0.001f));
		CPPUNIT_ASSERT(range(rect_t.get_left_up().get_y(),
							 0.f, 0.001f));

		CPPUNIT_ASSERT(range(rect_t.get_right_up().get_x(),
							 0.f, 0.001f));
		CPPUNIT_ASSERT(range(rect_t.get_right_up().get_y(),
							 std::sqrt(8.f), 0.001f));
	}

	void scaling_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector3;
		
		vector3 coord(1, 2, 3);

		linear_transformer transformer;

		coord = transformer * coord;
		CPPUNIT_ASSERT(coord.x == 1.f);
		CPPUNIT_ASSERT(coord.y == 2.f);
		CPPUNIT_ASSERT(coord.z == 3.f);

		transformer.scaling(1.f, 1.f, 1.f);
		coord = transformer * coord;
		CPPUNIT_ASSERT(range(coord.x, 1.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.y, 2.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.z, 3.f, 0.001f));

		transformer = linear_transformer();
		transformer.scaling(2.f, 3.f, 4.f);
		coord = transformer * coord;

		CPPUNIT_ASSERT(range(coord.x, 2.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.y, 6.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.z,12.f, 0.001f));
	}

	void operation_order_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector3;
		
		vector3 coord(1, 0, 0);

		linear_transformer transformer;

		coord = transformer * coord;
		CPPUNIT_ASSERT(coord.x == 1.f);
		CPPUNIT_ASSERT(coord.y == 0.f);
		CPPUNIT_ASSERT(coord.z == 0.f);

		transformer.translate(-1.f, -1.f, 0.f);
		transformer.rotate(vector3(0.f, 0.f, 1.f), 3.1415926535f / 2.f);
		transformer.translate(1.f, 1.f, 0.f);

		coord = transformer * coord;
		CPPUNIT_ASSERT(range(coord.x, 2.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.y, 1.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.z, 0.f, 0.001f));
	}

	void rotate_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector3;
		
		vector3 coord(1, 0, 0);

		linear_transformer transformer;

		coord = transformer * coord;
		CPPUNIT_ASSERT(coord.x == 1.f);
		CPPUNIT_ASSERT(coord.y == 0.f);
		CPPUNIT_ASSERT(coord.z == 0.f);

		transformer.rotate(vector3(0.f, 0.f, 1.f), 3.1415926535f / 2.f);
		coord = transformer * coord;
		CPPUNIT_ASSERT(range(coord.x, 0.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.y, 1.f, 0.001f));
		CPPUNIT_ASSERT(range(coord.z, 0.f, 0.001f));

		coord = vector3(0, 0, 1);

		transformer = linear_transformer();
		transformer.rotate(vector3(1.f, 1.f, 0.f), 3.1415926535f / 2.f);
		coord = transformer * coord;

		const float pos = std::sqrt(2.f)/2.f;
		CPPUNIT_ASSERT(range(coord.x,  pos, 0.001f));
		CPPUNIT_ASSERT(range(coord.y, -pos, 0.001f));
		CPPUNIT_ASSERT(range(coord.z,  0.f, 0.001f));
	}

	void translate_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::vector3;
		
		vector3 coord(1, 2, 3);

		linear_transformer transformer;

		coord = transformer * coord;
		CPPUNIT_ASSERT(coord.x == 1.f);
		CPPUNIT_ASSERT(coord.y == 2.f);
		CPPUNIT_ASSERT(coord.z == 3.f);
		
		transformer.translate(-1.f, -2.f, -3.f);
		coord = transformer * coord;
		CPPUNIT_ASSERT(coord.x == 0.f);
		CPPUNIT_ASSERT(coord.y == 0.f);
		CPPUNIT_ASSERT(coord.z == 0.f);
		
		coord = transformer * coord;
		CPPUNIT_ASSERT(coord.x == -1.f);
		CPPUNIT_ASSERT(coord.y == -2.f);
		CPPUNIT_ASSERT(coord.z == -3.f);
	}

	void coord_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::coordinate;
		typedef coordinate<float> coordinate_t;

		coordinate_t coord(1.f, 1.f);

		linear_transformer transformer;

		coordinate_t coord_t = transformer * coord;
		CPPUNIT_ASSERT(coord_t.get_x() == 1.f);
		CPPUNIT_ASSERT(coord_t.get_y() == 1.f);

		const risa_gl::static_array<float, 16> mat =
			{ { 0.f, 1.f, 0.f, 0.f,
				-1.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f} };
		transformer = linear_transformer(mat);

		coord_t = transformer * coord;
		CPPUNIT_ASSERT(coord_t.get_x() == -1.f);
		CPPUNIT_ASSERT(coord_t.get_y() ==  1.f);
	}

	void region_test()
	{
		using risa_gl::linear_transformer;
		using risa_gl::math::rectangle_region;

		typedef rectangle_region<float> region_t;
		typedef region_t::coord_type coord_t;
		region_t rect(-1.f, -2.f, 3.f, 4.f);
		
		linear_transformer transformer;

		region_t rect_t = transformer * rect;
		CPPUNIT_ASSERT(rect_t.get_left_down() == coord_t(-1.f, -2.f));
		CPPUNIT_ASSERT(rect_t.get_right_down() == coord_t(3.f, -2.f));
		CPPUNIT_ASSERT(rect_t.get_left_up() == coord_t(-1.f, 4.f));
		CPPUNIT_ASSERT(rect_t.get_right_up() == coord_t(3.f, 4.f));

		const risa_gl::static_array<float, 16> mat = 
			{ { 0.f, 1.f, 0.f, 0.f,
				-1.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f} };
		transformer = linear_transformer(mat);

		rect_t = transformer * rect;

		CPPUNIT_ASSERT(rect_t.get_left_down() == coord_t(2.f, -1.f));
		CPPUNIT_ASSERT(rect_t.get_right_down() == coord_t(2.f, 3.f));
		CPPUNIT_ASSERT(rect_t.get_left_up() == coord_t(-4.f, -1.f));
		CPPUNIT_ASSERT(rect_t.get_right_up() == coord_t(-4.f, 3.f));
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

		const risa_gl::static_array<float, 16> mat =
			{ { 0.f, 1.f, 0.f, 0.f,
				-1.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f} };
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

		const risa_gl::static_array<float, 16> mat =
			{ { 1.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f,-1.f, 0.f, 0.f,
				0.f, 0.f, 0.f, 1.f} };
		transformer = linear_transformer(mat);

		v_t = transformer * v;
		CPPUNIT_ASSERT(v_t.x == 2.f);
		CPPUNIT_ASSERT(v_t.y == -4.f);
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

		const risa_gl::static_array<float, 16> mat = 
			{ { 0.f, 0.f,-1.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				1.f, 0.f, 0.f, 0.f,
				0.f, 0.f, 0.f, 1.f} };
		transformer = linear_transformer(mat);

		v_t = transformer * v;
		CPPUNIT_ASSERT(v_t.x == 4.f);
		CPPUNIT_ASSERT(v_t.y == 3.f);
		CPPUNIT_ASSERT(v_t.z ==-2.f);
		CPPUNIT_ASSERT(v_t.w == 1.f);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(transformer_test);
