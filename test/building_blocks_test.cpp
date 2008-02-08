#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/operators/building_blocks.hpp>
#include <risa_gl/operators/primitive/selector.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/risa_types.hpp>

class building_blocks_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(building_blocks_test);
	CPPUNIT_TEST(multiply_alpha_and_alpha_policy_test);
	CPPUNIT_TEST(scaled_source_opacity_getter_test);
	CPPUNIT_TEST(scaled_invert_source_opacity_getter_test);
	CPPUNIT_TEST(scaled_destination_opacity_getter_test);
	CPPUNIT_TEST(scaled_invert_destination_opacity_getter_test);
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

	void scaled_source_opacity_getter_test()
	{
		using namespace risa_gl::operators;
		using namespace risa_gl;
		typedef scaled_source_opacity_getter<1, 65, 1, 256> getter_type;
		getter_type oper;
		
		opaque src(33);
		opaque dest(1);

		CPPUNIT_ASSERT(oper(&src, &dest) == 128);
	}

	void scaled_invert_source_opacity_getter_test()
	{
		using namespace risa_gl::operators;
		using namespace risa_gl;
		typedef scaled_invert_source_opacity_getter<1, 65, 1, 256> getter_type;
		getter_type oper;
		
		opaque src(1);
		opaque dest(33);

		CPPUNIT_ASSERT(oper(&src, &dest) == 255);
	}

	void scaled_destination_opacity_getter_test()
	{
		using namespace risa_gl::operators;
		using namespace risa_gl;
		typedef scaled_destination_opacity_getter<1, 65, 1, 256> getter_type;
		getter_type oper;
		
		opaque src(33);
		opaque dest(65);

		CPPUNIT_ASSERT(oper(&src, &dest) == 256);

		dest = opaque(33);
		CPPUNIT_ASSERT(oper(&src, &dest) == 128);
	}

	void scaled_invert_destination_opacity_getter_test()
	{
		using namespace risa_gl::operators;
		using namespace risa_gl;
		typedef
			scaled_invert_destination_opacity_getter<1, 65, 1, 256> getter_type;
		getter_type oper;
		
		opaque src(1);
		opaque dest(33);

		CPPUNIT_ASSERT(oper(&src, &dest) == 128);
	}

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

		result.set_bit_representation(oper(0, &result, &src, &dest));
		// src * src + dest * (1 - src)
		// (256 * 256) >> 8 + 256 * (256 - 256)
		// 256
		CPPUNIT_ASSERT(result.get_alpha() == 256);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( building_blocks_test );

