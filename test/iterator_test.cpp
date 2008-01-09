#include <cppunit/extensions/HelperMacros.h>
#include <pixel.hpp>
#include <iterator.hpp>
#include <iterator_adapter.hpp>
#include <exception.hpp>
#include <vector>
#include <cassert>

class iterator_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(iterator_test);
	CPPUNIT_TEST(sequential_test);
	CPPUNIT_TEST(alignment_test);
	CPPUNIT_TEST(traits_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void traits_test()
	{
		using namespace risa_gl;
		typedef iterator_adapter<char, 16> adapter_t;
		typedef adapter_t::iterator_type iterator_t;
		typedef adapter_t::alignment_iterator_type alignment_t;

		alignment_t align_itor((alignment_t::pointer)16);
		iterator_t itor = adapter_t::to_sequential(align_itor);
		CPPUNIT_ASSERT(itor == iterator_t((char*)16));

		align_itor = adapter_t::to_alignment(itor);
		CPPUNIT_ASSERT(++align_itor == alignment_t((alignment_t::pointer)32));

		for (int i = 17; i < 32; ++i)
			CPPUNIT_ASSERT_THROW(alignment_t((alignment_t::pointer)i),
								 alignment_error);
	}

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

	void alignment_test()
	{
		using namespace risa_gl;
		
		typedef alignment_iterator<char, 16> align_iterator_t;
		
		for (int i = 1; i < 16; ++i)
			CPPUNIT_ASSERT_THROW(
				align_iterator_t(reinterpret_cast<char*>(i)), 
				alignment_error);

		align_iterator_t itor(reinterpret_cast<char*>(0));
		align_iterator_t end(reinterpret_cast<char*>(32));

		CPPUNIT_ASSERT(itor != end);
		CPPUNIT_ASSERT(++itor != end);
		CPPUNIT_ASSERT(++itor == end);
		CPPUNIT_ASSERT(itor == end);
		CPPUNIT_ASSERT(itor++ == end);
		CPPUNIT_ASSERT(itor != end);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( iterator_test );
