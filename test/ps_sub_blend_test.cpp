#include <cppunit/extensions/HelperMacros.h>
#include <operators/ps_sub_blend.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class ps_sub_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_sub_blend_operator_test);
	CPPUNIT_TEST(ps_sub_blend_test);
	CPPUNIT_TEST(ps_sub_blend_save_destination_alpha_test);
	CPPUNIT_TEST_SUITE_END();
public:
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

	typedef risa_gl::pixel_store<risa_gl::pixel> pixels_store;

	void ps_sub_blend_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 129)));
		/**
		 * (140, 0, 0, 129), (182, 41, 41, 129)
		 * (70, 0, 0), (91, 21, 21)
		 * (161, 21, 21)
		 */

		operators::ps_sub_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 161);
		CPPUNIT_ASSERT(result.begin()->get_green() == 20);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 20);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));
		/**
		 * (0, 255, 255)
		 * (255, 0, 0, 129), (255, 255, 255, 129)
		 * (128, 0, 0), (128, 128, 128)
		 * (255, 128, 128)
		 */
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 127);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 127);
	}

	void ps_sub_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 150)));
		/**
		 * (140, 0, 0, 129), (182, 41, 41, 129)
		 * (70, 0, 0), (91, 21, 21)
		 * (161, 21, 21)
		 */

		operators::ps_sub_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 161);
		CPPUNIT_ASSERT(result.begin()->get_green() == 20);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 20);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 150);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 18)));
		/**
		 * (0, 255, 255)
		 * (255, 0, 0, 129), (255, 255, 255, 129)
		 * (128, 0, 0), (128, 128, 128)
		 * (255, 128, 128)
		 */
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 127);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 127);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 18);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_sub_blend_operator_test );
