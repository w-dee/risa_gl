#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <risa_gl/nv/template_functions.hpp>

#include <typeinfo>

template <typename left_t, typename right_t>
struct bindee
{
	enum {
		size = sizeof(left_t) + sizeof(right_t),
		left_size = sizeof(left_t),
		right_size = sizeof(right_t)
	};
};

template <template <typename> class partial_type, typename T>
struct concreate
{
	typedef typename partial_type<T>::type type;
};

class template_functions_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(template_functions_test);
	CPPUNIT_TEST(filler_test);
	CPPUNIT_TEST(bind_2nd_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void bind_2nd_test()
	{
		CPPUNIT_ASSERT_EQUAL(typeid(bindee<int, int>).name(),
							 typeid(bindee<int, int>).name());
		CPPUNIT_ASSERT(typeid(bindee<int, short>).name() !=
					   typeid(bindee<int, int>).name());

		namespace templ_func = template_functions;

		typedef
			templ_func::bind_2nd<int, bindee>::currying<int>::type
			expect_t;

		typedef bindee<int, int> actual_t;
		CPPUNIT_ASSERT_EQUAL((int)expect_t::size,
							 (int)actual_t::size);
		CPPUNIT_ASSERT_EQUAL((int)expect_t::left_size,
							 (int)actual_t::left_size);
		CPPUNIT_ASSERT_EQUAL((int)expect_t::right_size,
							 (int)actual_t::right_size);

		typedef
			templ_func::bind_2nd<int, bindee>::currying<short>::type
			expect2_t;

		typedef bindee<short, int> actual2_t;
		CPPUNIT_ASSERT_EQUAL((int)expect2_t::size,
							 (int)actual2_t::size);
		CPPUNIT_ASSERT_EQUAL((int)expect2_t::left_size,
							 (int)actual2_t::left_size);
		CPPUNIT_ASSERT_EQUAL((int)expect2_t::right_size,
							 (int)actual2_t::right_size);

		typedef concreate<
		templ_func::bind_2nd<short, bindee>::currying,
			int>::type expect3_t;

		CPPUNIT_ASSERT(expect3_t::size == sizeof(int) + sizeof(short));
		CPPUNIT_ASSERT(expect3_t::left_size == sizeof(int));
		CPPUNIT_ASSERT(expect3_t::right_size == sizeof(short));
	}

	void filler_test()
	{
		using template_functions::filler;

		CPPUNIT_ASSERT_EQUAL(
			0x04040404,
			(filler<int, unsigned char, 0x04>::value()));

		CPPUNIT_ASSERT_EQUAL(
			0x0404040404040404ULL,
			(filler<unsigned long long, unsigned char, 0x04>::value()));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( template_functions_test );
