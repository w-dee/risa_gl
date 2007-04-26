#include <cppunit/extensions/HelperMacros.h>
#include <pixel.hpp>
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "exception.hpp"
#include <vector>
#include <cassert>

class iterator_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(iterator_test);
	CPPUNIT_TEST(sequential_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void sequential_test()
	{
		using namespace risa_gl;
		
		typedef sequential_iterator<char> seq_iterator_t;

		seq_iterator_t itor(reinterpret_cast<char*>(4));
		seq_iterator_t end(reinterpret_cast<char*>(6));

		CPPUNIT_ASSERT(itor != end);
		CPPUNIT_ASSERT(++itor != end);
		CPPUNIT_ASSERT(++itor == end);
		CPPUNIT_ASSERT(itor == end);
		CPPUNIT_ASSERT(itor++ == end);
		CPPUNIT_ASSERT(itor != end);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( iterator_test );
