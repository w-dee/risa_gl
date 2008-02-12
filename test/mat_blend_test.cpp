#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/mat_blend.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>

#include "range.hpp"
#include <algorithm>
#include <iostream>

class mat_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(mat_blend_operator_test);
	CPPUNIT_TEST(mat_blend_save_calculate_alpha_test);
	CPPUNIT_TEST(mat_blend_save_calculate_additive_alpha_operator_test);
	CPPUNIT_TEST_SUITE_END();

	template <typename container_type>
	struct generator
	{
		const container_type container;

		generator(container_type container_):
			container(container_)
		{}

		container_type operator()() const
		{
			return container;
		}
	};

public:
	void mat_blend_save_calculate_additive_alpha_operator_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store src(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(128, 128, 128, 129)));

		/**
		 * src(1.0, 1.0, 1.0, 0.5)
		 * mat(1.0, 1.0, 1.0, 1.0)
		 * r = src * src.a + mat * (1 - src.a)
		 *   = (0.5, 0.5, 0.5) + (0.5, 0.5, 0.5)
		 *   = (1.0, 1.0, 1.0)
		 *
		 * r.a = src.a + mat.a - src.a * mat.a
		 *     = 0.5 + 1.0 - 0.5 * 1.0
		 *     = 1.5 - 0.5
		 *     = 1.0
		 */
		operators::mat_additive_blend_save_calculate_alpha_operator
			oper(pixel(255, 255, 255, 256));
		oper(src.begin(), result.begin());
		CPPUNIT_ASSERT(range<int>(result.begin()->get_red(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_green(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_blue(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_blue(), 256, 1));

		/**
		 * src(1.0, 1.0, 1.0, 0.5)
		 * mat(0.25, 0.25, 0.25, 0.25)
		 * r = src * src.a + mat * (1 - src.a)
		 *   = (0.5, 0.5, 0.5) + (0.125, 0.125, 0.125)
		 *   = (0.625, 0.625, 0.625)
		 *
		 * r.a = src.a + mat.a - src.a * mat.a
		 *     = 0.5 + 0.25 - 0.5 * 0.25
		 *     = 0.75 - 0.125
		 *     = 0.625
		 */

		operators::mat_additive_blend_save_calculate_alpha_operator
			oper2(pixel(64, 64, 64, 65));
		oper2(src.begin(), result.begin());
		CPPUNIT_ASSERT(range<int>(result.begin()->get_red(), 159, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_green(), 159, 1)); 
		CPPUNIT_ASSERT(range<int>(result.begin()->get_blue(), 159, 1));
		// 誤差でかめ
		CPPUNIT_ASSERT(range<int>(result.begin()->get_alpha(), 160, 2));
	}

	void mat_blend_save_calculate_alpha_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store src(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));

		operators::mat_blend_save_calculate_alpha_operator
			oper(pixel(255, 255, 255, 256));
		oper(src.begin(), result.begin());
		CPPUNIT_ASSERT(range<int>(result.begin()->get_red(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_green(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_blue(), 255, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_blue(), 256, 1));

		operators::mat_blend_save_calculate_alpha_operator
			oper2(pixel(64, 64, 64, 65));
		oper2(src.begin(), result.begin());
		CPPUNIT_ASSERT(range<int>(result.begin()->get_red(), 159, 1));
		CPPUNIT_ASSERT(range<int>(result.begin()->get_green(), 159, 1)); 
		CPPUNIT_ASSERT(range<int>(result.begin()->get_blue(), 159, 1));
		///  ちょっと誤差でかめ
		CPPUNIT_ASSERT(range<int>(result.begin()->get_alpha(), 160, 2));
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( mat_blend_operator_test );
