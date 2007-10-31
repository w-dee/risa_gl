#include <cppunit/extensions/HelperMacros.h>
#include <operators/ps_softlight_blend.hpp>
#include <pixel.hpp>
#include <pixel_store.hpp>

#include <iostream>

class ps_softlight_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ps_softlight_blend_operator_test);
	CPPUNIT_TEST(ps_softlight_blend_test);
	CPPUNIT_TEST(ps_softlight_blend_save_destination_alpha_test);
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

	void ps_softlight_blend_test()
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
		 * (195, 63, 63)
		 */
		operators::ps_softlight_blend_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 195);
		CPPUNIT_ASSERT(result.begin()->get_green() == 62);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 62);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));

		/**
		 * (255, 64, 64), (255, 64, 64)
		 * (255, 48, 48)
		 */
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 48);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 48);
	}

	void ps_softlight_blend_save_destination_alpha_test()
	{
		using namespace risa_gl;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(213, 213, 213, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(182, 41, 41, 129)));

		operators::ps_softlight_blend_save_destination_alpha_operator oper;
		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 195);
		CPPUNIT_ASSERT(result.begin()->get_green() == 62);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 62);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 129);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 64, 64, 129)));

		oper(src.begin(), dest.begin(), result.begin());

		CPPUNIT_ASSERT(result.begin()->get_red() == 255);
		CPPUNIT_ASSERT(result.begin()->get_green() == 48);
		CPPUNIT_ASSERT(result.begin()->get_blue() == 48);
		CPPUNIT_ASSERT(result.begin()->get_alpha() == 129);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ps_softlight_blend_operator_test );
