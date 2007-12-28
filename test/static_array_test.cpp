#include <cppunit/extensions/HelperMacros.h>
#include <static_array.hpp>

using risa_gl::static_array;

typedef static_array<int, 10> array_t;

class static_array_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(static_array_test);
	CPPUNIT_TEST(dereference_test);
	CPPUNIT_TEST(equal_test);
	CPPUNIT_TEST(not_equal_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void equal_test()
	{
		array_t lhs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		array_t rhs1 = lhs;
		array_t rhs2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0 };

		CPPUNIT_ASSERT(lhs == rhs1);
		CPPUNIT_ASSERT(!(lhs == rhs2));
	}

	void not_equal_test()
	{
		array_t lhs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		array_t rhs1 = lhs;
		array_t rhs2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0 };

		CPPUNIT_ASSERT(!(lhs != rhs1));
		CPPUNIT_ASSERT(lhs != rhs2);
	}

	void dereference_test()
	{
		array_t array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (int offset = 0; offset != static_cast<int>(array.size()); ++offset)
			CPPUNIT_ASSERT(array[offset] == offset);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( static_array_test );
