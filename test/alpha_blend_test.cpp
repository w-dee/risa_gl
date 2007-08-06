#include <cppunit/extensions/HelperMacros.h>
#include <operators/alpha_blend.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <algorithm>
#include <iostream>

class alpha_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_blend_operator_test);
	CPPUNIT_TEST(alpha_blend_test);
	CPPUNIT_TEST(alpha_blend_calculate_alpha_test);
	CPPUNIT_TEST(alpha_blend_additive_calculate_alpha_operator_test);
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
	void alpha_blend_additive_calculate_alpha_operator_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(128, 128, 128, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0, 0, 0, 1.0)
		 * (0.5, 0.5, 0.5) * 0.5 + (0, 0, 0) * 1.0 * 0.5
		 * = (0.25, 0.25, 0.25)
		 * 129 + 256 - (129 * 256)/256 = 256
		 */
		operators::alpha_blend_additive_calculate_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 64);
		CPPUNIT_ASSERT(result.begin()->get_green() == 64); 
		CPPUNIT_ASSERT(result.begin()->get_blue() == 64);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 256);

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 1)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(1.0, 1.0, 1.0, 0)
		 * (0.5, 0.5, 0.5) * 0.5 + (1, 1, 1) * 0 * 0.5
		 * = (0.25, 0.25, 0.25)
		 *
		 * 129 + 1 - (129 * 1)/256 = 130
		 */
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 64);
		CPPUNIT_ASSERT(result.begin()->get_green() == 64); 
		CPPUNIT_ASSERT(result.begin()->get_blue() == 64);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 130);
	}

	void alpha_blend_calculate_alpha_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(128, 128, 128, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0, 0, 0, 1.0)
		 * (0.5, 0.5, 0.5) * 0.5 + (0, 0, 0) * 0.5
		 * = (0.25, 0.25, 0.25)
		 * 
		 * 0.5 + 1.0 - 0.5 * 1.0 = 1.5 - 0.5
		 * 1.0
		 */
		operators::alpha_blend_calculate_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 64);
		CPPUNIT_ASSERT(result.begin()->get_green() == 64); 
		CPPUNIT_ASSERT(result.begin()->get_blue() == 64);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 256);

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 1)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(1.0, 1.0, 1.0, 0)
		 * (0.5, 0.5, 0.5) * 0.5 + (1, 1, 1) * 0.5
		 * = (0.75, 0.75, 0.75)
		 *
		 * 129 + 1 - (129 * 1)/256 = 130 - 0
		 * 
		 */
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 191);
		CPPUNIT_ASSERT(result.begin()->get_green() == 191); 
		CPPUNIT_ASSERT(result.begin()->get_blue() == 191);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 130);
	}

	void alpha_blend_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(128, 128, 128, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0, 0, 0, 1.0)
		 * (0.5, 0.5, 0.5) * 0.5 + (0, 0, 0) * 0.5
		 * = (0.25, 0.25, 0.25)
		 */
		operators::alpha_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 64);
		CPPUNIT_ASSERT(result.begin()->get_green() == 64); 
		CPPUNIT_ASSERT(result.begin()->get_blue() == 64);

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 1)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(1.0, 1.0, 1.0, 0)
		 * (0.5, 0.5, 0.5) * 0.5 + (1, 1, 1) * 0.5
		 * = (0.75, 0.75, 0.75)
		 */
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(result.begin()->get_red() == 191);
		CPPUNIT_ASSERT(result.begin()->get_green() == 191); 
		CPPUNIT_ASSERT(result.begin()->get_blue() == 191);
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( alpha_blend_operator_test );
