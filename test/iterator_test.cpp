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
	CPPUNIT_TEST(traits_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void traits_test()
	{
		using namespace risa_gl;
		typedef sequencial_iterator<pixel> seq_iterator;
		typedef aligned_iterator<pixel, 16> ali_iterator;
		typedef iterator_adapter<pixel, 16> itor_adapter;

		std::vector<seq_iterator > vec;
		for (int offset = 0; offset <= 16; ++offset)
		{
			seq_iterator::pointer_t ptr = 
				reinterpret_cast<seq_iterator::pointer_t>(offset);
			vec.push_back(seq_iterator(ptr));
		}

		assert(vec.size() == 17);
		for (int offset = 0; offset <= 16; ++offset)
		{
			if (offset == 0 || offset == 16)
			{
				ali_iterator itor = 
					itor_adapter::to_alignment(vec.at(offset));
				CPPUNIT_ASSERT_EQUAL(itor,
									 ali_iterator(reinterpret_cast<byte*>(offset)));

			}
			else
			{
				CPPUNIT_ASSERT_THROW(
					itor_adapter::to_alignment(vec.at(offset)),
					alignment_error);
			}
		}
		
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( iterator_test );
