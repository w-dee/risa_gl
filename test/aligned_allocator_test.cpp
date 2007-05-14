#include <cppunit/extensions/HelperMacros.h>
#include "allocator.hpp"

class aligned_allocator_test : public CppUnit::TestFixture
{
private:
	CPPUNIT_TEST_SUITE(aligned_allocator_test);
	CPPUNIT_TEST(allocator_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void allocator_test()
	{
		using namespace risa_gl;
		typedef aligned_allocator<byte, 16> aligned_allocator_type;

		byte* p = aligned_allocator_type().allocate(18);
		CPPUNIT_ASSERT((reinterpret_cast<size_t>(p) % 16) == 0);
		aligned_allocator_type().deallocate(p, 0);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( aligned_allocator_test );

