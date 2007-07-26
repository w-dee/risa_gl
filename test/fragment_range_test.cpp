#include <cppunit/extensions/HelperMacros.h>
#include <fragment_range.hpp>
#include <pixel_store.hpp>
#include <pixel.hpp>

class fragment_range_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(fragment_range_test);
	CPPUNIT_TEST(just_aligned_test);
	CPPUNIT_TEST(offset_align_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void offset_align_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel, 16> pixel_store_t;
		typedef fragment_range<pixel_store_t, pixel_store_t::alignment_size> fragment_range_t;

		pixel_store_t pixels(640, 480);
		pixel_store_t::fragment_type frag = pixels.get_fragment(0);

		// 0 + 4, 640 * 4 - 4
		// (4, 1916) - (16, 1904)

		// (4, 1916)
		fragment_range_t frag_range(frag.begin() + 1, frag.end() - 1);
		fragment_range_t::sequential_iterator_type front_boundary =
			frag.begin() + 4;
		fragment_range_t::sequential_iterator_type back_boundary =
			frag.end() - 4;

		typedef fragment_range_t::iterator_range itor_range;
		typedef fragment_range_t::aligned_range aligned_range;
		typedef fragment_range_t::iterator_adapter_type adapter_type;

		itor_range itor_r = frag_range.get_front();
		aligned_range itor_align = frag_range.get_middle();

		CPPUNIT_ASSERT(itor_r.begin() != itor_r.end());
		fragment_range_t::sequential_iterator_type itor = itor_r.begin();
		++itor; ++itor; ++itor;

		CPPUNIT_ASSERT(itor == itor_r.end());
		CPPUNIT_ASSERT(adapter_type::to_alignment(itor_r.end()) ==
					   itor_align.begin());

		CPPUNIT_ASSERT(reinterpret_cast<size_t>
					   (&*itor_align.begin()) % 16 == 0);
		CPPUNIT_ASSERT(reinterpret_cast<size_t>
					   (&*itor_align.end()) % 16 == 0);
		CPPUNIT_ASSERT(itor_align.begin() != itor_align.end());

		itor_r = frag_range.get_back();
		CPPUNIT_ASSERT(adapter_type::to_sequential(itor_align.end()) ==
					   itor_r.begin());
		itor = itor_r.begin();
		++itor; ++itor; ++itor;
		CPPUNIT_ASSERT(itor == itor_r.end());
	}

	void just_aligned_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel, 32> pixel_store_t;
		typedef fragment_range<pixel_store_t,
			pixel_store_t::alignment_size > fragment_range_t;

		pixel_store_t pixels(640, 480);
		pixel_store_t::fragment_type frag = pixels.get_fragment(0);

		fragment_range_t frag_range(frag.begin(), frag.end());

		typedef fragment_range_t::iterator_range itor_range;
		typedef fragment_range_t::aligned_range aligned_range;
		typedef fragment_range_t::iterator_adapter_type adapter_type;

		itor_range itor_r = frag_range.get_front();
		aligned_range itor_align = frag_range.get_middle();
		CPPUNIT_ASSERT(itor_r.begin() == itor_r.end());
		CPPUNIT_ASSERT(adapter_type::to_alignment(itor_r.end()) ==
					   itor_align.begin());

		CPPUNIT_ASSERT(itor_align.begin() != itor_align.end());

		itor_r = frag_range.get_back();
		CPPUNIT_ASSERT(adapter_type::to_sequential(itor_align.end()) ==
					   itor_r.begin());
		CPPUNIT_ASSERT(itor_r.begin() == itor_r.end());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( fragment_range_test );
