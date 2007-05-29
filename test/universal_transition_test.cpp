#include <cppunit/extensions/HelperMacros.h>
#include "operators/universal_transition.hpp"
#include "pixel.hpp"
#include "pixel_store.hpp"

class universal_transition_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(universal_transition_test);
	CPPUNIT_TEST(default_transition_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void default_transition_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel, 16> pixel_store_type;
		typedef pixel_store<brightness, 16> transition_map_type;

		pixel_store_type pixels(640, 480);
		pixel_store_type dest(640, 480);
		transition_map_type trans_map(640, 480);

		for (pixel_store_type::iterator itor = pixels.begin();
			 itor != pixels.end(); ++itor)
			*itor = pixel(255,255,255,255);

		int i = 0;
		for (transition_map_type::iterator itor = trans_map.begin();
			 itor != trans_map.end(); ++itor)
			*itor = brightness(i++%256);

		
		universal_transition<
			pixel_store_type::const_iterator,
			transition_map_type::const_iterator,
			pixel_store_type::iterator,
			pixel
		> trans;

		trans(const_cast<const pixel_store_type&>(pixels).begin(),
			  const_cast<const pixel_store_type&>(pixels).end(),
			  const_cast<const transition_map_type&>(trans_map).begin(),
			  dest.begin());

		for (int offset = 0; offset <= 256; ++offset)
		{
			const int level = offset % 256;
			CPPUNIT_ASSERT(dest(offset, 0) ==
						   pixel(level, level, level, level));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( universal_transition_test );
