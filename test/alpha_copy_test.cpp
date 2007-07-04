#include <cppunit/extensions/HelperMacros.h>
#include "operators/alpha_copy.hpp"
#include "pixel.hpp"
#include "pixel_store.hpp"

#include <algorithm>

class alpha_copy_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_copy_test);
	CPPUNIT_TEST(alpha_copy_blend_test);
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
	void brightness_copy_blend_test()
	{
		using namespace risa_gl;
		typedef pixel_store<pixel> pixels_store;
		typedef pixel_store<opaque> opaque_store;

		pixels_store src(640, 480);
		opaque_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(dest.begin(), dest.end(),
					  generator<opaque>(opaque(128)));

		operators::opaque_copy_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(*result.begin() == pixel(128, 128, 128, 128));
		std::generate(dest.begin(), dest.end(),
					  generator<opaque>(opaque(1)));

		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(*result.begin() == pixel(128, 128, 128, 1));
	}

	void alpha_copy_blend_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;

		pixels_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<pixel>(pixel(128, 128, 128, 128)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(0, 0, 0, 256)));

		operators::alpha_copy_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(*result.begin() == pixel(0, 0, 0, 128));

		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(255, 255, 255, 1)));

		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(*result.begin() == pixel(255, 255, 255, 128));
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( alpha_copy_test );
