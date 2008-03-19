#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/ext/sse2/alpha_factor.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/fragment.hpp>
#include <risa_gl/fragment_range.hpp>

#include <iostream>
#include <cstring>

using namespace risa_gl::ext::sse2;

class alpha_factor_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_factor_test);
	CPPUNIT_TEST(identity_alpha_factor_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void identity_alpha_factor_test()
	{
		typedef risa_gl::pixel_store<risa_gl::pixel> pixel_store_t;
		pixel_store_t src(640, 480);
		pixel_store_t dest(640, 480);

		risa_gl::byte opaque = 0;
		for (pixel_store_t::iterator itor = src.begin();
			 itor != src.end(); ++itor)
			itor->set_alpha(opaque++ + 1);

		identity_alpha_factor factor;
		pixel_store_t::fragment_type fragment = src.get_fragment(0);
		typedef risa_gl::fragment_range<pixel_store_t> fragment_range_t;
		fragment_range_t frag_range(fragment.begin(), fragment.end());
				
		aligned_wideword_type result_ =
			factor(frag_range.get_middle().begin(),
				   frag_range.get_middle().begin());

		converter convert;
		unaligned_wideword_type result =
			convert.to_unaligned_wideword_type(result_);

		CPPUNIT_ASSERT(result[0] == 0);
		CPPUNIT_ASSERT(result[1] == 1);
		CPPUNIT_ASSERT(result[2] == 0);
		CPPUNIT_ASSERT(result[3] == 0);

		CPPUNIT_ASSERT(result[4] == 0);
		CPPUNIT_ASSERT(result[5] == 1);
		CPPUNIT_ASSERT(result[6] == 0);
		CPPUNIT_ASSERT(result[7] == 0);

		CPPUNIT_ASSERT(result[8] == 0);
		CPPUNIT_ASSERT(result[9] == 1);
		CPPUNIT_ASSERT(result[10] == 0);
		CPPUNIT_ASSERT(result[11] == 0);

		CPPUNIT_ASSERT(result[12] == 0);
		CPPUNIT_ASSERT(result[13] == 1);
		CPPUNIT_ASSERT(result[14] == 0);
		CPPUNIT_ASSERT(result[15] == 0);

		std::memcpy(&*dest.begin(), &result[0], 16);

		std::cout << dest(0, 0) << std::endl;
		CPPUNIT_ASSERT(dest(0, 0).get_blue() == 1);
		CPPUNIT_ASSERT(dest(1, 0).get_blue() == 1);
		CPPUNIT_ASSERT(dest(2, 0).get_blue() == 1);
		CPPUNIT_ASSERT(dest(3, 0).get_blue() == 1);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( alpha_factor_test );
