#include <cppunit/extensions/HelperMacros.h>
#include <operators/ps_exclusion_blend.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class ps_exclusion_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_exclusion_blend_operator_test);
	CPPUNIT_TEST(ps_exclusion_blend_test);
	CPPUNIT_TEST(ps_exclusion_blend_save_destination_alpha_test);
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

	void ps_exclusion_blend_test()
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
		 * (213, 213, 213, 129), (182, 41, 41, 129)
		 * (136, 113, 113)
		 */

		operators::ps_exclusion_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 137);
		CPPUNIT_ASSERT(result.begin()->get_green() == 113);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 113);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 129)));
		/**
		 * (255, 0, 0, 129), (255, 255, 255, 129)
		 * (127, 255, 255)
		 */
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 128);
		CPPUNIT_ASSERT(result.begin()->get_green() == 255);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 255);
	}

	void ps_exclusion_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 150)));
		operators::ps_exclusion_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 137);
		CPPUNIT_ASSERT(result.begin()->get_green() == 113);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 113);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 150);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 0, 0, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 18)));
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 128);
		CPPUNIT_ASSERT(result.begin()->get_green() == 255);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 255);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 18);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_exclusion_blend_operator_test );
