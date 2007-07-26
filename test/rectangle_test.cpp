#include <cppunit/extensions/HelperMacros.h>
#include <rectangle.hpp>
#include <pixel_store.hpp>
#include <pixel.hpp>

class rectangle_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( rectangle_test );
	CPPUNIT_TEST(point_test);
	CPPUNIT_TEST(rect_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void rect_test()
	{
		using namespace risa_gl;
		typedef pixel_store<pixel, 16> pixel_store_type;
		typedef rectangle<pixel_store_type,
			alignment_iterator<pixel_store_type,
			pixel_store_type::alignment_size> > rectangle_type;
		typedef rectangle_type::fragment_set_type fragment_set_type;
		typedef fragment_set_type::fragment_type fragment_type;

		pixel_store_type bitmap(800, 600);
		rectangle_type rectangle(bitmap, point(120, 240),
								 point(150, 320));

		fragment_set_type fragments = rectangle.get_fragments();
		
		CPPUNIT_ASSERT(fragments.size() == 320 - 240);
		fragment_type fragment = fragments.get_fragment(0);
		CPPUNIT_ASSERT(&*fragment.begin() == &bitmap(120, 240));
		CPPUNIT_ASSERT(&*fragment.end() == &bitmap(150, 240));

		fragment = fragments.get_fragment(fragments.size() - 1);
		CPPUNIT_ASSERT(&*fragment.begin() == &bitmap(120, 319));
		CPPUNIT_ASSERT(&*fragment.end() == &bitmap(150, 319));
	}

	void point_test()
	{
		using namespace risa_gl;

		point p;
		CPPUNIT_ASSERT(p.get_x() == 0);
		CPPUNIT_ASSERT(p.get_y() == 0);
	
		p += point(100, 200);
		CPPUNIT_ASSERT(p.get_x() == 100);
		CPPUNIT_ASSERT(p.get_y() == 200);

		p -= point(200, 100);
		CPPUNIT_ASSERT(p.get_x() == -100);
		CPPUNIT_ASSERT(p.get_y() == 100);

		point p2 = p;
		CPPUNIT_ASSERT(p2.get_x() == -100);
		CPPUNIT_ASSERT(p2.get_y() == 100);

		p.set_x(50);
		p2 = p;
		CPPUNIT_ASSERT(p2.get_x() == 50);
		CPPUNIT_ASSERT(p2.get_y() == 100);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( rectangle_test );
