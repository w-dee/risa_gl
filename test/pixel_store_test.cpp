#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/pixel.hpp>
#include <cstdlib>


static size_t another_allocator_note;

class pixel_store_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(pixel_store_test);
	CPPUNIT_TEST(allocate_test);
	CPPUNIT_TEST(fragment_test);
	CPPUNIT_TEST(fragment_size_test);
	CPPUNIT_TEST(another_allocator_test);
	CPPUNIT_TEST_SUITE_END();

public:

	
	struct another_allocator
	{
		static risa_gl::byte* allocate(size_t size)
		{
			size_t temp = another_allocator_note;
			another_allocator_note = size;
			return reinterpret_cast<risa_gl::byte*>(temp);
		}

		static void deallocate(risa_gl::byte* p)
		{
			another_allocator_note = reinterpret_cast<size_t>(p);
		}
	};

	void another_allocator_test()
	{
		using namespace risa_gl;

		typedef normal_allocator<pixel, another_allocator> allocator_t;

		typedef pixel_store<pixel, allocator_t>
			another_allocate_pixel_store_t;

		void* pointer_save = std::malloc(10 * 10 * sizeof(pixel));
		another_allocator_note = reinterpret_cast<size_t>(pointer_save);
		{
			another_allocate_pixel_store_t pixel(10, 10);
			CPPUNIT_ASSERT(another_allocator_note != (10 * 4 * 10));
		}
		CPPUNIT_ASSERT(another_allocator_note ==
			reinterpret_cast<size_t>(pointer_save));

		free(pointer_save);
	}

	template <int size>
	struct dummy_pixel
	{
		char dummy[size];
	};

	void fragment_size_test()
	{
		using namespace risa_gl;
		typedef dummy_pixel<3> pixel_3_t;
		typedef pixel_store<pixel_3_t,
			aligned_allocator<pixel_3_t, 18> > pixel_3_store_t;

		pixel_3_store_t pix_3(28, 28);
		CPPUNIT_ASSERT((pix_3.get_fragment_length() % 18) == 0);
		CPPUNIT_ASSERT((pix_3.get_fragment_length() %
						sizeof(pixel_3_t)) == 0); 
		CPPUNIT_ASSERT(pix_3.get_fragment_length() >=
					   static_cast<int>(28 * sizeof(pixel_3_t)));

		/*
		 * 一行あたり6ピクセルごとにアライメントされるので9ピクセルの
		 * 倍数になるはず
		 */
		
		pixel_3_t* p1 = &pix_3(0, 0);
		pixel_3_t* p2 = &pix_3(0, 1);
		CPPUNIT_ASSERT(((p2 - p1) % 
						(math::lcm(3, 18) / sizeof(pixel_3_t))) == 0);
		CPPUNIT_ASSERT(
			static_cast<int>((p2 - p1) * sizeof(pixel_3_t)) ==
			pix_3.get_fragment_length());

		typedef dummy_pixel<4> pixel_5_t;
		typedef pixel_store<pixel_5_t, 
			aligned_allocator<pixel_5_t, 19> > pixel_5_store_t;

		pixel_5_store_t pix_5(19, 19);
		CPPUNIT_ASSERT((pix_5.get_fragment_length() % sizeof(pixel_5_t)) == 0);
		CPPUNIT_ASSERT((pix_5.get_fragment_length() % 
						sizeof(pixel_5_t)) == 0);
		CPPUNIT_ASSERT(pix_5.get_fragment_length() >=
					   static_cast<int>(19 * sizeof(pixel_5_t)));

		pixel_5_t* p3 = &pix_5(0, 0);
		pixel_5_t* p4 = &pix_5(0, 1);
		CPPUNIT_ASSERT(((p4 - p3) % ((4 * 19) / sizeof(pixel_5_t))) == 0);
		CPPUNIT_ASSERT(
			static_cast<int>((p4 - p3) * sizeof(pixel_5_t)) ==
			pix_5.get_fragment_length());
	}

	void fragment_test()
	{
		using namespace risa_gl;

		typedef pixel_store<pixel,
			aligned_allocator<pixel, 16> > pixel_store_type;
		typedef pixel_store_type::fragment_type fragment_type;
		typedef pixel_store_type::const_fragment_type const_fragment_type;
		typedef fragment_type::iterator frag_itor_type;
		typedef const_fragment_type::iterator const_frag_itor_type;

		{
			pixel_store_type store(640, 480);
			fragment_type frag = store.get_fragment(0);
			frag_itor_type current = frag.begin();
			frag_itor_type last = frag.end();
			CPPUNIT_ASSERT(&*current == &store(0, 0));
			CPPUNIT_ASSERT(&*last == &store(0, 1));

			frag = store.get_fragment(0, 100, 200);
			current = frag.begin();
			last = frag.end();
			CPPUNIT_ASSERT(&*current == &store(100, 0));
			CPPUNIT_ASSERT(&*last == &store(200, 0));
		}
		{
			const pixel_store_type store(640, 480);
			const_fragment_type frag = store.get_fragment(0);
			const_frag_itor_type current = frag.begin();
			const_frag_itor_type last = frag.end();
			CPPUNIT_ASSERT(&*current == &store(0, 0));
			CPPUNIT_ASSERT(&*last == &store(0, 1));

			frag = store.get_fragment(0, 100, 200);
			current = frag.begin();
			last = frag.end();
			CPPUNIT_ASSERT(&*current == &store(100, 0));
			CPPUNIT_ASSERT(&*last == &store(200, 0));
		}
	}

	void allocate_test()
	{
		using namespace risa_gl;
		pixel_store<pixel,
			aligned_allocator<pixel, 16> > pixels1(257, 100);
		
		CPPUNIT_ASSERT(pixels1.get_width() == 257);
		CPPUNIT_ASSERT(pixels1.get_height() == 100);

		CPPUNIT_ASSERT(pixels1.get_fragment_length() ==
					   (260 * sizeof(pixel)));

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( pixel_store_test );
