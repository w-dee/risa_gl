#include <cppunit/extensions/HelperMacros.h>
#include <operators/building_blocks.hpp>
#include <operators/primitive/selector.hpp>
#include <pixel.hpp>
#include <risa_types.hpp>

class building_blocks_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(building_blocks_test);
	CPPUNIT_TEST(multiply_alpha_and_alpha_policy_test);
	CPPUNIT_TEST_SUITE_END();

public:
	template <typename arg_type, typename selector>
	struct dereferencer
	{
		arg_type operator()(arg_type* left, arg_type* right) const
		{
			return *selector()(left, right);
		}

	};

	void multiply_alpha_and_alpha_policy_test()
	{
		using namespace risa_gl;
		uint32 src, dest;
		src = 256;
		dest = 256;
		pixel result;

		operators::multiply_alpha_and_alpha_policy<
			dereferencer<uint32, primitive::source_selector>,
			dereferencer<uint32, primitive::destination_selector> > oper;

		oper(&result, &src, &dest);
		// src * src + dest * (1 - src)
		// (256 * 256) >> 8 + 256 * (256 - 256)
		// 256
		CPPUNIT_ASSERT(result.get_alpha() == 256);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( building_blocks_test );

