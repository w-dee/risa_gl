#include <cppunit/extensions/HelperMacros.h>
#include <endian_traits.hpp>

class endian_traits_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(endian_traits_test);
	CPPUNIT_TEST(endian_check_test);
	CPPUNIT_TEST(endian_test_caller);
	CPPUNIT_TEST_SUITE_END();

public:
	void endian_check_test()
	{
		using namespace risa_gl;

		const int test_val = 1;
		endian_traits<int>::endian_type endian_types =
			endian_traits<int>::big_endian;
		if (*reinterpret_cast<const char*>(&test_val) == 1)
			endian_types = endian_traits<int>::little_endian;

		CPPUNIT_ASSERT(endian_traits<int>::get_current_endian() ==
					   endian_types);
	}

	void endian_test_caller()
	{
		using namespace risa_gl;
		typedef endian_traits<int> endian_t;

		if (endian_t::get_current_endian() == endian_t::little_endian)
			little_endian_test();
		else
			big_endian_test();
	}

	void big_endian_test()
	{
		using namespace risa_gl;
		typedef endian_traits<int> endian_t;

		endian_t converter;

		CPPUNIT_ASSERT(converter.big_to_current_offset(3) == 3);
		CPPUNIT_ASSERT(converter.little_to_current_offset(3) == 0);
	}

	void little_endian_test()
	{
		using namespace risa_gl;
		typedef endian_traits<int> endian_t;

		endian_t converter;

		CPPUNIT_ASSERT(converter.big_to_current_offset(3) == 0);
		CPPUNIT_ASSERT(converter.little_to_current_offset(3) == 3);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( endian_traits_test );
