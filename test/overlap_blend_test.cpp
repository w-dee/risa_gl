#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/overlap_blend.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include "range.hpp"
#include <algorithm>
#include <iostream>

class overlap_blend_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(overlap_blend_test);
	CPPUNIT_TEST(overlap_blend_op_test);
	CPPUNIT_TEST(overlap_blend_transmissive_destination_test);
	CPPUNIT_TEST(overlap_blend_additive_destination_test);
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
	void overlap_blend_additive_destination_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0, 0, 0, 1.0)
		 * (0.5, 0.5, 0.5) * 0.5 + (0, 0, 0) * 1.0 * 0.5
		 * = (0.25, 0.25, 0.25)
		 * 129 + 256 - (129 * 256)/256 = 256
		 */
		operators::overlap_blend_additive_destination_operator
			oper(pixel(128, 128, 128, 129));
		oper(dest.begin(), result.begin());
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
		 * 129 + 1 - (129 * 1)/256 = 130
		 */
		oper(dest.begin(), result.begin());
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_red()), 191, 2));
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_green()), 191, 2)); 
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_blue()), 191, 2));
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_alpha()), 130, 1));
	}

	void overlap_blend_transmissive_destination_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store dest(640, 480);
		pixels_store result(640, 480);

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
		operators::overlap_blend_transmissive_destination_operator
			oper(pixel(128, 128, 128, 129));
		oper(dest.begin(), result.begin());
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
		 * 129 + 1 - (129 * 1)/256 = 130 - 0
		 * 
		 */
		oper(dest.begin(), result.begin());	
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_red()), 63, 1));
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_green()), 63, 1)); 
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_blue()), 63, 1));
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_alpha()), 130, 1));
	}

	void overlap_blend_op_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(0, 0, 0, 1.0)
		 * (0.5, 0.5, 0.5) * 0.5 + (0, 0, 0) * 0.5
		 * = (0.25, 0.25, 0.25)
		 */
		operators::overlap_blend_operator oper(pixel(128, 128, 128,129));
		oper(dest.begin(), result.begin());
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
		oper(dest.begin(), result.begin());
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_red()), 191, 1));
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_green()), 191, 1)); 
		CPPUNIT_ASSERT(
			range(static_cast<int>(result.begin()->get_blue()), 191, 1));
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( overlap_blend_test );
