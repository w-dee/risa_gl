#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/memory_chunk.hpp>
#include <vector>

class memory_chunk_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(memory_chunk_test);
	CPPUNIT_TEST(address_test);
	CPPUNIT_TEST_SUITE_END();
public:
	void address_test()
	{
		using namespace risa_gl;
		
		typedef memory_chunk<16> mem_chunk;
		std::vector<mem_chunk> chunks;
		chunks.resize(2);

		CPPUNIT_ASSERT(&chunks[0] == (mem_chunk*)chunks[0].get());
		mem_chunk* p = &chunks[0];
		CPPUNIT_ASSERT(++p == (mem_chunk*)chunks[1].get());
	}
};
