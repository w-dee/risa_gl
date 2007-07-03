#include <cppunit/extensions/HelperMacros.h>
#include "operators/colormap.hpp"
#include "pixel.hpp"
#include "pixel_store.hpp"

#include <algorithm>

class colormap_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(colormap_test);
	CPPUNIT_TEST(colormap_blend_test);
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
	void colormap_blend_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel> pixels_store;
		typedef pixel_store<brightness> alpha_store;

		pixels_store pixels(640, 480);
		alpha_store color_map(640, 480);

		std::generate(pixels.begin(), pixels.end(),
					  generator<pixel>(pixel(128, 128, 128, 256)));
		std::generate(color_map.begin(), color_map.end(),
					  generator<brightness>(brightness(65)));

		operators::colormap_65level_operator oper;
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(*pixels.begin() == pixel(128, 128, 128, 256));

		std::generate(color_map.begin(), color_map.end(),
					  generator<brightness>(brightness(1)));
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(*pixels.begin() == pixel(0, 0, 0, 1));

		std::generate(color_map.begin(), color_map.end(),
					  generator<brightness>(brightness(65)));
		oper(pixels.begin(), color_map.begin(), pixels.begin());
		CPPUNIT_ASSERT(*pixels.begin() == pixel(0, 0, 0, 1));
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION( colormap_test );
