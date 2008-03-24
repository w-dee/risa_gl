#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/ext/sse2/operators/building_blocks.hpp>

using namespace risa_gl::ext::sse2::operators;
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
		source_selector selector;
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

		unaligned_wideword_type result = source_getter(&src, &dest);

		CPPUNIT_ASSERT(result[0] == src[0]);
	}

	void destination_getter_test()
	{
		source_getter getter;
		unaligned_wideword_type src;
		unaligned_wideword_type dest;

		src[0] = 1;
		dest[0] = 2;

		unaligned_wideword_type result source_getter(&src, &dest);

		CPPUNIT_ASSERT(result[0] == dest[0]);
	}

	void plus_function_test()
	{
		source_getter getter;
		unaligned_wideword_type src;
		unaligned_wideword_type dest;

		src[0] = 1;
		src[1] = 0;
		dest[0] = 2;
		dest[1] = 0;
		
		converter convert;
		aligned_wideword_type wide_src =
			convert.to_aligned_wideword_type(src);
		aligned_wideword_type wide_dest =
			convert.to_aligned_wideword_type(dest);
		
		aligned_wideword_type wide_result =
			unaligned_wideword_type result source_getter(&wide_src, &wide_dest);
		unaligned_wideword_type result =
			convert.to_unaligned_wideword_type(wide_result);

		CPPUNIT_ASSERT(result[0] == 1 + 2);
	}

	void source_alpha_getter_test()
	{
		CPPUNIT_FAIL("test not implemented yet.");
	}

	void invert_source_alpha_getter_test()
	{
		CPPUNIT_FAIL("test not implemented yet.");
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
