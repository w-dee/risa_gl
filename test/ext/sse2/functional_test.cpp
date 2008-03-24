#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/ext/sse2/primitive/functional.hpp>
#include <risa_gl/ext/sse2/primitive/pixel_property.hpp>
#include <risa_gl/ext/sse2/primitive/blend.hpp>
#include <risa_gl/ext/sse2/risa_types.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/allocator.hpp>

#include <iostream>

using namespace risa_gl::ext::sse2;
using namespace risa_gl::ext::sse2::primitive;

class functional_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(functional_test);
	CPPUNIT_TEST(vertical_add_test);
	CPPUNIT_TEST(vertical_add_saturation_test);
	CPPUNIT_TEST(fill_values_test);
	CPPUNIT_TEST(vertical_not_test);
 	CPPUNIT_TEST(multiply_high_test);
	CPPUNIT_TEST(load_store_test);
	CPPUNIT_TEST_SUITE_END();

	typedef risa_gl::aligned_allocator<unaligned_wideword_type, 16> alloc_type;
public:
	void load_store_test()
	{
		using risa_gl::pixel;
		using risa_gl::pixel_store;

		typedef pixel_store<pixel> pixel_store_t;
		pixel_store_t ps(640, 480);
		for (pixel_store_t::iterator itor = ps.begin();
			 itor != ps.end(); ++itor)
			*itor = pixel(255, 0, 0, 1);

		CPPUNIT_ASSERT(ps(0, 0) == pixel(255, 0, 0, 1));

		converter convert;
		aligned_wideword_type pixs =
			convert.to_aligned_wideword_type_from_alignment(
				reinterpret_cast<unaligned_wideword_type&>(ps(0, 0)));

		
		convert.to_unaligned_wideword_type_on_alignment(
			reinterpret_cast<unaligned_wideword_type*>(&ps(0, 0)),
			pixs);

		CPPUNIT_ASSERT(ps(0, 0) == pixel(255, 0, 0, 1));
	}

	void multiply_high_test()
	{
		converter convert;

		unsigned int native_alpha_factors[4] =
			{ 0x00000000, 0x003f003f, 0x007f007f, 0x00ff00ff };
		aligned_wideword_type alpha_factors =
			convert.to_aligned_wideword_type(
				*reinterpret_cast<unaligned_wideword_type*>(
					native_alpha_factors));

		unaligned_wideword_type value = {{ 255, 255, 255, 255,
										   255, 255, 255, 255,
										   127, 127, 127, 127,
										   63, 63, 63, 63 }};
		
		aligned_wideword_type src_values =
			convert.to_aligned_wideword_type(value);

		aligned_wideword_type odd_mask_ = odd_mask()(src_values);
		aligned_wideword_type even_mask_ =
			logical_right_32bit_packed_shift<8>()(
				even_mask()(src_values));

		vertical_multiply func;
		
		aligned_wideword_type odd_result =
			logical_right_16bit_packed_shift<8>()(
				func(odd_mask_, alpha_factors));

		aligned_wideword_type even_result = 
			logical_right_16bit_packed_shift<8>()(
				func(even_mask_, alpha_factors));

		unaligned_wideword_type compare_result =
			convert.to_unaligned_wideword_type(
				vertical_compare()(odd_result, even_result));

		for (size_t offset = 0; offset < sizeof(compare_result); ++offset)
			CPPUNIT_ASSERT(compare_result[offset] != 0);

		unaligned_wideword_type result =
			convert.to_unaligned_wideword_type(
				vertical_or()(odd_result, 
							  logical_left_byte_shift<1>()(even_result)));


		CPPUNIT_ASSERT(result[ 0] == 0);
		CPPUNIT_ASSERT(result[ 1] == 0);
		CPPUNIT_ASSERT(result[ 2] == 0);
		CPPUNIT_ASSERT(result[ 3] == 0);
		CPPUNIT_ASSERT(result[ 4] == 62);
		CPPUNIT_ASSERT(result[ 5] == 62);
		CPPUNIT_ASSERT(result[ 6] == 62);
		CPPUNIT_ASSERT(result[ 7] == 62);
		CPPUNIT_ASSERT(result[ 8] == 63);
		CPPUNIT_ASSERT(result[ 9] == 63);
		CPPUNIT_ASSERT(result[10] == 63);
		CPPUNIT_ASSERT(result[11] == 63);
		CPPUNIT_ASSERT(result[12] == 62);
		CPPUNIT_ASSERT(result[13] == 62);
		CPPUNIT_ASSERT(result[14] == 62);
		CPPUNIT_ASSERT(result[15] == 62);
	}

	void vertical_not_test()
	{
		converter convert;
		unaligned_wideword_type value = convert.to_unaligned_wideword_type(
			vertical_not()(_mm_set1_epi8(0xaa)));

		for (size_t offset = 0;
			 offset < sizeof(unaligned_wideword_type); ++offset)
			CPPUNIT_ASSERT(value[offset] == 0x55);
	}

	void fill_values_test()
	{
		converter convert;
		unaligned_wideword_type value =
			convert.to_unaligned_wideword_type(zero_getter()(1,2));

		for (size_t offset = 0;
			 offset < sizeof(unaligned_wideword_type); ++offset)
			CPPUNIT_ASSERT(value[offset] == 0);

		value = convert.to_unaligned_wideword_type(_mm_set1_epi8(0xff));
		for (size_t offset = 0;
			 offset < sizeof(unaligned_wideword_type); ++offset)
			CPPUNIT_ASSERT(value[offset] == 0xff);
	}

	void vertical_add_saturation_test()
	{
		alloc_type allocator;
		unaligned_wideword_type* src = allocator.allocate(1);
		unaligned_wideword_type* dest = allocator.allocate(1);
		unaligned_wideword_type* result = allocator.allocate(1);

		vertical_add_saturation function;
		for (int offset = 0; offset < 16; ++offset)
		{
			(*src)[offset] = 255 - offset;
			(*dest)[offset] = offset * 2 + 1;
			(*result)[offset] = 0;
		}

		converter convert;
		*result = 
			convert.to_unaligned_wideword_type(
				function(convert.to_aligned_wideword_type(*src),
						 convert.to_aligned_wideword_type(*dest)));
		

		CPPUNIT_ASSERT((unsigned char)((*result)[0]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[1]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[2]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[3]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[4]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[5]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[6]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[7]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[8]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[9]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[10]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[11]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[12]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[13]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[14]) == 255);
		CPPUNIT_ASSERT((unsigned char)((*result)[15]) == 255);

		allocator.deallocate(src, 0);
		allocator.deallocate(dest, 0);
		allocator.deallocate(result, 0);
	}

	void vertical_add_test()
	{
		alloc_type allocator;
		unaligned_wideword_type* src = allocator.allocate(1);
		unaligned_wideword_type* dest = allocator.allocate(1);
		unaligned_wideword_type* result = allocator.allocate(1);

		vertical_add function;
		for (int offset = 0; offset < 16; ++offset)
		{
			(*src)[offset] = offset;
			(*dest)[offset] = offset * 2 + 1;
			(*result)[offset] = 0;
		}

		converter convert;
		*result = 
			convert.to_unaligned_wideword_type(
				function(convert.to_aligned_wideword_type(*src),
						 convert.to_aligned_wideword_type(*dest)));
		

		CPPUNIT_ASSERT((*result)[0] == 1);
		CPPUNIT_ASSERT((*result)[1] == 4);
		CPPUNIT_ASSERT((*result)[2] == 7);
		CPPUNIT_ASSERT((*result)[3] == 10);
		CPPUNIT_ASSERT((*result)[4] == 13);
		CPPUNIT_ASSERT((*result)[5] == 16);
		CPPUNIT_ASSERT((*result)[6] == 19);
		CPPUNIT_ASSERT((*result)[7] == 22);
		CPPUNIT_ASSERT((*result)[8] == 25);
		CPPUNIT_ASSERT((*result)[9] == 28);
		CPPUNIT_ASSERT((*result)[10] == 31);
		CPPUNIT_ASSERT((*result)[11] == 34);
		CPPUNIT_ASSERT((*result)[12] == 37);
		CPPUNIT_ASSERT((*result)[13] == 40);
		CPPUNIT_ASSERT((*result)[14] == 43);
		CPPUNIT_ASSERT((*result)[15] == 46);

		allocator.deallocate(src, 0);
		allocator.deallocate(dest, 0);
		allocator.deallocate(result, 0);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( functional_test );
