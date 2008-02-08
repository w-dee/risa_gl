#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/alpha_copy.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>

#include <algorithm>

class alpha_copy_operator_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_copy_operator_test);
	CPPUNIT_TEST(alpha_copy_test);
	CPPUNIT_TEST(opacity_copy_test);
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
	void opacity_copy_test()
	{
		using namespace risa_gl;
		typedef pixel_store<pixel> pixels_store;
		typedef pixel_store<opaque> opaque_store;

		opaque_store src(640, 480);
		pixels_store dest(640, 480);
		pixels_store result(640, 480);

		std::generate(src.begin(), src.end(),
					  generator<opaque>(opaque(128)));
		std::generate(dest.begin(), dest.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));

		operators::opacity_copy_operator oper;
		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(*result.begin() == pixel(128, 128, 128, 128));
		std::generate(src.begin(), src.end(),
					  generator<opaque>(opaque(1)));

		oper(src.begin(), dest.begin(), result.begin());
		CPPUNIT_ASSERT(*result.begin() == pixel(128, 128, 128, 1));
	}

	void alpha_copy_test()
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


CPPUNIT_TEST_SUITE_REGISTRATION( alpha_copy_operator_test );
