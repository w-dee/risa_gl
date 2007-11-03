#include <cppunit/extensions/HelperMacros.h>
#include <operators/ps_div_blend.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class ps_div_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_div_blend_operator_test);
	CPPUNIT_TEST(ps_div_blend_test);
	CPPUNIT_TEST(ps_div_blend_save_destination_alpha_test);
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

	void ps_div_blend_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 256)));

		/**
		 * (213, 213, 213), (182, 41, 41)
		 * (218, 142, 142)
		 */
		operators::ps_div_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 219);
		CPPUNIT_ASSERT(result.begin()->get_green() == 142);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 142);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));

		/**
		 * (255, 64, 64), (255, 64, 64)
		 * (255, 74, 74)
		 */
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 74);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 74);
	}

	void ps_div_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 129)));

		operators::ps_div_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 219);
		CPPUNIT_ASSERT(result.begin()->get_green() == 142);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 142);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 129);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));

		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 74);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 74);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 129);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_div_blend_operator_test );
