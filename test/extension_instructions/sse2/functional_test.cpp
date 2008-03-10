#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/primitive/extension_instructions/sse2/functional.hpp>
#include <risa_gl/operators/primitive/extension_instructions/sse2/risa_sse2_types.hpp>
#include <risa_gl/allocator.hpp>

using namespace risa_gl::ext_instruction::sse2;

class functional_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(functional_test);
	CPPUNIT_TEST(add_test);
	CPPUNIT_TEST(add_saturation_test);
//	CPPUNIT_TSET(mulutiply_high_test);
	CPPUNIT_TEST_SUITE_END();

	typedef risa_gl::aligned_allocator<native_word_type, 16> alloc_type;
public:
	void add_saturation_test()
	{
		alloc_type allocator;
		native_word_type* src = allocator.allocate(1);
		native_word_type* dest = allocator.allocate(1);
		native_word_type* result = allocator.allocate(1);

		add_saturation function;
		for (int offset = 0; offset < 16; ++offset)
		{
			(*src)[offset] = 255 - offset;
			(*dest)[offset] = offset * 2 + 1;
			(*result)[offset] = 0;
		}

		converter convert;
		*result = 
			convert.to_native_word_type(
				function(convert.to_word_type(*src),
						 convert.to_word_type(*dest)));
		

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

	void add_test()
	{
		alloc_type allocator;
		native_word_type* src = allocator.allocate(1);
		native_word_type* dest = allocator.allocate(1);
		native_word_type* result = allocator.allocate(1);

		add function;
		for (int offset = 0; offset < 16; ++offset)
		{
			(*src)[offset] = offset;
			(*dest)[offset] = offset * 2 + 1;
			(*result)[offset] = 0;
		}

		converter convert;
		*result = 
			convert.to_native_word_type(
				function(convert.to_word_type(*src),
						 convert.to_word_type(*dest)));
		

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
