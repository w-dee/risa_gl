#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/nv/pixel_traits.hpp>

#include "pixel_type.hpp"

class pixel_traits_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(pixel_traits_test);
	CPPUNIT_TEST(traits_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void traits_test()
	{
		traits::pixel_traits<pixel_type> trait;

		pixel_type value = pixel_type(0, 1, 2, 3);
		CPPUNIT_ASSERT_EQUAL(3U, trait.factor_extract(*reinterpret_cast<unsigned int*>(&value)));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( pixel_traits_test );
