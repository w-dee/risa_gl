#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/utility/compose.hpp>

class compose_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(compose_test);
	CPPUNIT_TEST(identity_test);
	CPPUNIT_TEST(compose1_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void identity_test()
	{
		using risa_gl::utility::identity;
		identity ident;


		CPPUNIT_ASSERT_EQUAL(ident(10), 10);
		CPPUNIT_ASSERT_EQUAL(ident(11.0), 11.0);
	}

	struct double_op
	{
		template <typename value_t>
		value_t operator()(const value_t& value) const
		{
			return value * 2;
		}
	};

	void compose1_test()
	{
		using risa_gl::utility::identity;
		using risa_gl::utility::compose;

		CPPUNIT_ASSERT_EQUAL(2, double_op()(1));

		CPPUNIT_ASSERT_EQUAL(4,
							 compose::compose1<int>(double_op(),
													identity())(2));

		CPPUNIT_ASSERT_EQUAL(8,
							 compose::compose1<int>(double_op(),
													double_op())(2));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( compose_test );

