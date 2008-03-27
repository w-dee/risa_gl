#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/ext/sse2/operators/building_blocks.hpp>
#include <risa_gl/pixel.hpp>

#include <iostream>

using namespace risa_gl::ext::sse2::operators;
using namespace risa_gl::ext::sse2::primitive;
using namespace risa_gl::ext::sse2;

class building_blocks_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(building_blocks_test);
	CPPUNIT_TEST(source_selector_test);
	CPPUNIT_TEST(destination_selector_test);
	CPPUNIT_TEST(source_getter_test);
	CPPUNIT_TEST(destination_getter_test);
	CPPUNIT_TEST(plus_function_test);
	CPPUNIT_TEST(source_alpha_getter_test);
	CPPUNIT_TEST(invert_source_alpha_getter_test);
	CPPUNIT_TEST(destination_alpha_getter_test);
	CPPUNIT_TEST(invert_destination_alpha_getter_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void source_selector_test()
	{
		risa_gl::ext::sse2::operators::source_selector select;
		const int src = 1;
		const int dest = 2;

		int result = select(src, dest);

		CPPUNIT_ASSERT(result == src);
	}

	void destination_selector_test()
	{
		destination_selector selector;
		int src = 1;
		int dest = 2;

		int result = selector(src, dest);

		CPPUNIT_ASSERT(result == dest);
	}

	void source_getter_test()
	{
		source_getter getter;
		unaligned_wideword_type src;
		unaligned_wideword_type dest;

		src[0] = 1;
		dest[0] = 2;
		risa_gl::ext::sse2::primitive::converter convert;

		aligned_wideword_type src_ = convert.to_aligned_wideword_type(src);
		aligned_wideword_type dest_ = convert.to_aligned_wideword_type(dest);

		aligned_wideword_type result_ = getter(&src_, &dest_);
		unaligned_wideword_type result =
			convert.to_unaligned_wideword_type(result_);

		CPPUNIT_ASSERT(result[0] == src[0]);
	}

	void destination_getter_test()
	{
		destination_getter getter;
		unaligned_wideword_type src;
		unaligned_wideword_type dest;

		src[0] = 1;
		dest[0] = 2;
		risa_gl::ext::sse2::primitive::converter convert;

		aligned_wideword_type src_ = convert.to_aligned_wideword_type(src);
		aligned_wideword_type dest_ = convert.to_aligned_wideword_type(dest);

		aligned_wideword_type result_ = getter(&src_, &dest_);
		unaligned_wideword_type result =
			convert.to_unaligned_wideword_type(result_);

		CPPUNIT_ASSERT(result[0] == dest[0]);
	}

	void plus_function_test()
	{
		plus_function func;
		unaligned_wideword_type src;
		unaligned_wideword_type dest;

		src[0] = 1;
		src[1] = 0;
		dest[0] = 2;
		dest[1] = 0;
		
		risa_gl::ext::sse2::primitive::converter convert;
		aligned_wideword_type wide_src =
			convert.to_aligned_wideword_type(src);
		aligned_wideword_type wide_dest =
			convert.to_aligned_wideword_type(dest);
		
		aligned_wideword_type wide_result =	func(wide_src, wide_dest);
		unaligned_wideword_type result =
			convert.to_unaligned_wideword_type(wide_result);

		CPPUNIT_ASSERT(result[0] == 1 + 2);
	}

	void source_alpha_getter_test()
	{
		unaligned_wideword_type src = {{
				1, 2, 3, 122,
				1, 2, 3, 124,
				1, 2, 3, 126,
				1, 2, 3, 128
			}};
		unaligned_wideword_type dest = {{
				246, 4, 5, 6,
				251, 4, 5, 6,
				253, 4, 5, 6,
				255, 4, 5, 6
			}};

		converter convert;
		source_alpha_getter<risa_gl::pixel> getter;
		aligned_wideword_type result_ = getter(&src, &dest);

		unaligned_wideword_type result = 
			convert.to_unaligned_wideword_type(result_);

		CPPUNIT_ASSERT(result[ 0] == 0);
		CPPUNIT_ASSERT(result[ 1] == 0);
		CPPUNIT_ASSERT(result[ 2] == 0);
		CPPUNIT_ASSERT(result[ 3] == 122);
		CPPUNIT_ASSERT(result[ 4] == 0);
		CPPUNIT_ASSERT(result[ 5] == 0);
		CPPUNIT_ASSERT(result[ 6] == 0);
		CPPUNIT_ASSERT(result[ 7] == 124);
		CPPUNIT_ASSERT(result[ 8] == 0);
		CPPUNIT_ASSERT(result[ 9] == 0);
		CPPUNIT_ASSERT(result[10] == 0);
		CPPUNIT_ASSERT(result[11] == 126);
		CPPUNIT_ASSERT(result[12] == 0);
		CPPUNIT_ASSERT(result[13] == 0);
		CPPUNIT_ASSERT(result[14] == 0);
		CPPUNIT_ASSERT(result[15] == 128);
	}

	void invert_source_alpha_getter_test()
	{
		unaligned_wideword_type src = {{
				1, 2, 3, 122,
				1, 2, 3, 124,
				1, 2, 3, 126,
				1, 2, 3, 128
			}};
		unaligned_wideword_type dest = {{
				246, 4, 5, 6,
				251, 4, 5, 6,
				253, 4, 5, 6,
				255, 4, 5, 6
			}};

		converter convert;
		invert_source_alpha_getter<risa_gl::pixel> getter;
		aligned_wideword_type result_ = getter(&src, &dest);

		unaligned_wideword_type result = 
			convert.to_unaligned_wideword_type(result_);

// 		for (int offset = 0; offset < 16; ++offset)
// 			std::cout << offset << ": " << static_cast<short>(result[offset]) << std::endl;


		CPPUNIT_ASSERT(result[ 0] == 0);
		CPPUNIT_ASSERT(result[ 1] == 0);
		CPPUNIT_ASSERT(result[ 2] == 0);
		CPPUNIT_ASSERT(result[ 3] == 256 - 122);
		CPPUNIT_ASSERT(result[ 4] == 0);
		CPPUNIT_ASSERT(result[ 5] == 0);
		CPPUNIT_ASSERT(result[ 6] == 0);
		CPPUNIT_ASSERT(result[ 7] == 256 - 124);
		CPPUNIT_ASSERT(result[ 8] == 0);
		CPPUNIT_ASSERT(result[ 9] == 0);
		CPPUNIT_ASSERT(result[10] == 0);
		CPPUNIT_ASSERT(result[11] == 256 - 126);
		CPPUNIT_ASSERT(result[12] == 0);
		CPPUNIT_ASSERT(result[13] == 0);
		CPPUNIT_ASSERT(result[14] == 0);
		CPPUNIT_ASSERT(result[15] == 256 - 128);
	}

	void destination_alpha_getter_test()
	{
		CPPUNIT_FAIL("test not implemented yet.");
	}

	void invert_destination_alpha_getter_test()
	{
		CPPUNIT_FAIL("test not implemented yet.");
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( building_blocks_test );
