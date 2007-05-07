#include <cppunit/extensions/HelperMacros.h>
#include <pixel_store.hpp>
#include <pixel.hpp>

class pixel_store_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(pixel_store_test);
	CPPUNIT_TEST(allocate_test);
	CPPUNIT_TEST(fragment_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void fragment_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel, 16> pixel_store_type;
		typedef fragment<pixel_store_type> fragment_type;
		typedef fragment_type::iterator frag_itor_type;
		
		pixel_store_type store(640, 480);

		fragment_type frag = store.get_fragment(0);
		frag_itor_type current = frag.begin();
		frag_itor_type last = frag.end();

		CPPUNIT_ASSERT(&*current == &store(0, 0));
		CPPUNIT_ASSERT(&*last == &store(0, 1));
	}

	void allocate_test()
	{
		using namespace risa_gl;
		pixel_store<pixel, 16> pixels1(257, 100);
		
		CPPUNIT_ASSERT(pixels1.get_width() == 257);
		CPPUNIT_ASSERT(pixels1.get_height() == 100);

		CPPUNIT_ASSERT(pixels1.get_fragment_length() ==
					   (260 * sizeof(pixel)));

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( pixel_store_test );
