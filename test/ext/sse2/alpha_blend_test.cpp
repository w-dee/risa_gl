#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/ext/sse2/operators/alpha_blend.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/iterator_adapter.hpp>
#include <risa_gl/ext/sse2/operators/alpha_blend.hpp>
#include "../../range.hpp"
#include <algorithm>
#include <iostream>

namespace operators = risa_gl::ext::sse2::operators;

class alpha_blend_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_blend_operator_test);
	CPPUNIT_TEST(alpha_blend_test);
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
	typedef risa_gl::iterator_adapter<risa_gl::pixel, 16> adapter_type;

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
		operators::alpha_blend_operator<pixel> oper;
		oper(adapter_type::to_alignment(src.begin()),
			 adapter_type::to_alignment(dest.begin()),
			 adapter_type::to_alignment(result.begin()));

		for (int i = 0; i < 4; ++i)
		{
			CPPUNIT_ASSERT(result(i,0).get_red() == 64);
			CPPUNIT_ASSERT(result(i,0).get_green() == 64); 
			CPPUNIT_ASSERT(result(i,0).get_blue() == 64);
		}

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 1)));

		/**
		 * src(0.5, 0.5, 0.5, 0.5)
		 * dest(1.0, 1.0, 1.0, 0)
		 * (0.5, 0.5, 0.5) * 0.5 + (1, 1, 1) * 0.5
		 * = (0.75, 0.75, 0.75)
		 */
		oper(adapter_type::to_alignment(src.begin()),
			 adapter_type::to_alignment(dest.begin()),
			 adapter_type::to_alignment(result.begin()));
		for (int i = 0; i < 4; ++i)
		{
			std::cout << i << ":" << result(i,0) << std::endl;
			CPPUNIT_ASSERT(result(i,0).get_red() == 191);
			CPPUNIT_ASSERT(result(i,0).get_green() == 191); 
			CPPUNIT_ASSERT(result(i,0).get_blue() == 191);
		}
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( alpha_blend_operator_test );
