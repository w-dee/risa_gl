#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/ext/sse2/primitive/alpha_factor.hpp>
#include <risa_gl/pixel.hpp>
#include <risa_gl/pixel_store.hpp>
#include <risa_gl/fragment.hpp>
#include <risa_gl/fragment_range.hpp>

#include <iostream>
#include <cstring>

using namespace risa_gl::ext::sse2;
using namespace risa_gl::ext::sse2::primitive;

struct src_getter
{
	template <typename src_type, typename other_type>
	src_type operator()(src_type src, other_type) const
	{
		return src;
	}
};

template <typename pixel_t>
struct identity_bit_getter
{
	typedef pixel_t pixel_type;
	template <typename value_type>
	value_type operator()(value_type value) const
	{
		return value;
	}
};

class alpha_factor_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(alpha_factor_test);
	CPPUNIT_TEST(identity_alpha_factor_test);
	CPPUNIT_TEST(alpha_getter_test);
	CPPUNIT_TEST(invert_alpha_getter_test);
	CPPUNIT_TEST(alpha_bits_getter_method_test);
	CPPUNIT_TEST_SUITE_END();

public:
	void alpha_bits_getter_method_test()
	{
		typedef
			risa_gl::pixel_store<risa_gl::pixel_type<risa_gl::rgba> >
			pixel_store_t;
		typedef
			risa_gl::pixel_store<risa_gl::pixel_type<risa_gl::abgr> >
			pixel_store2_t;

		pixel_store_t src(640, 480);
		pixel_store2_t src2(640, 480);

		risa_gl::byte offset = 0;
		for (pixel_store_t::iterator itor = src.begin();
			 itor != src.end(); ++itor)
			itor->set_alpha(offset++ + 1);

		offset = 0;
		for (pixel_store2_t::iterator itor = src2.begin();
			 itor != src2.end(); ++itor)
			itor->set_alpha(offset++ + 1);

		alpha_bits_get_method<risa_gl::pixel_type<risa_gl::rgba> > getter;
		alpha_bits_get_method<risa_gl::pixel_type<risa_gl::abgr> > getter2;
		
		{
			pixel_store_t::fragment_type fragment = src.get_fragment(0);
			typedef risa_gl::fragment_range<pixel_store_t> fragment_range_t;
			fragment_range_t frag_range(fragment.begin(), fragment.end());
				
			aligned_wideword_type result_ =
				getter(*reinterpret_cast<aligned_wideword_type*>(
						   &*frag_range.get_middle().begin()));

			converter convert;
			unaligned_wideword_type result = 
				convert.to_unaligned_wideword_type(result_);

			CPPUNIT_ASSERT(result[0] == 0);
			CPPUNIT_ASSERT(result[1] == 0);
			CPPUNIT_ASSERT(result[2] == 0);
			CPPUNIT_ASSERT(result[3] == 0);

			CPPUNIT_ASSERT(result[4] == 1);
			CPPUNIT_ASSERT(result[5] == 0);
			CPPUNIT_ASSERT(result[6] == 1);
			CPPUNIT_ASSERT(result[7] == 0);

			CPPUNIT_ASSERT(result[8] == 2);
			CPPUNIT_ASSERT(result[9] == 0);
			CPPUNIT_ASSERT(result[10] == 2);
			CPPUNIT_ASSERT(result[11] == 0);

			CPPUNIT_ASSERT(result[12] == 3);
			CPPUNIT_ASSERT(result[13] == 0);
			CPPUNIT_ASSERT(result[14] == 3);
			CPPUNIT_ASSERT(result[15] == 0);
		}

		{
			pixel_store2_t::fragment_type fragment = src2.get_fragment(0);
			typedef risa_gl::fragment_range<pixel_store2_t> fragment_range_t;
			fragment_range_t frag_range(fragment.begin(), fragment.end());
				
			aligned_wideword_type result_ =
				getter2(*reinterpret_cast<aligned_wideword_type*>(
							&*frag_range.get_middle().begin()));

			converter convert;
			unaligned_wideword_type result = 
				convert.to_unaligned_wideword_type(result_);

			CPPUNIT_ASSERT(result[0] == 1);
			CPPUNIT_ASSERT(result[1] == 0);
			CPPUNIT_ASSERT(result[2] == 1);
			CPPUNIT_ASSERT(result[3] == 0);

			CPPUNIT_ASSERT(result[4] == 2);
			CPPUNIT_ASSERT(result[5] == 0);
			CPPUNIT_ASSERT(result[6] == 2);
			CPPUNIT_ASSERT(result[7] == 0);

			CPPUNIT_ASSERT(result[8] == 3);
			CPPUNIT_ASSERT(result[9] == 0);
			CPPUNIT_ASSERT(result[10] == 3);
			CPPUNIT_ASSERT(result[11] == 0);

			CPPUNIT_ASSERT(result[12] == 4);
			CPPUNIT_ASSERT(result[13] == 0);
			CPPUNIT_ASSERT(result[14] == 4);
			CPPUNIT_ASSERT(result[15] == 0);
		}
	}
	

	void invert_alpha_getter_test()
	{
		typedef risa_gl::pixel_store<risa_gl::pixel> pixel_store_t;
		pixel_store_t src(640, 480);
		risa_gl::byte offset = 0;
		for (pixel_store_t::iterator itor = src.begin();
			 itor != src.end(); ++itor, ++offset)
			*itor = risa_gl::pixel(offset, offset, offset, offset + 1);

		invert_alpha_getter<src_getter,
			alpha_bits_get_method<risa_gl::pixel> > getter;

		pixel_store_t::fragment_type fragment = src.get_fragment(0);
		typedef risa_gl::fragment_range<pixel_store_t> fragment_range_t;
		fragment_range_t frag_range(fragment.begin(), fragment.end());
				
		aligned_wideword_type result_ =
			getter(frag_range.get_middle().begin(),
				   frag_range.get_middle().begin());

		converter convert;
		unaligned_wideword_type result = 
			convert.to_unaligned_wideword_type(result_);

		CPPUNIT_ASSERT(result[0] == 256 - 1);
		CPPUNIT_ASSERT(result[1] == 0);
		CPPUNIT_ASSERT(result[2] == 256 - 1);
		CPPUNIT_ASSERT(result[3] == 0);

		CPPUNIT_ASSERT(result[4] == 256 - 2);
		CPPUNIT_ASSERT(result[5] == 0);
		CPPUNIT_ASSERT(result[6] == 256 - 2);
		CPPUNIT_ASSERT(result[7] == 0);

		CPPUNIT_ASSERT(result[8] == 256 - 3);
		CPPUNIT_ASSERT(result[9] == 0);
		CPPUNIT_ASSERT(result[10] == 256 - 3);
		CPPUNIT_ASSERT(result[11] == 0);

		CPPUNIT_ASSERT(result[12] == 256 - 4);
		CPPUNIT_ASSERT(result[13] == 0);
		CPPUNIT_ASSERT(result[14] == 256 - 4);
		CPPUNIT_ASSERT(result[15] == 0);
	}

	void alpha_getter_test()
	{
		typedef risa_gl::pixel_store<risa_gl::pixel> pixel_store_t;
		pixel_store_t src(640, 480);
		risa_gl::byte offset = 0;
		for (pixel_store_t::iterator itor = src.begin();
			 itor != src.end(); ++itor, ++offset)
			*itor = risa_gl::pixel(offset, offset, offset, offset + 1);

		alpha_getter<src_getter, alpha_bits_get_method<risa_gl::pixel> > getter;

		pixel_store_t::fragment_type fragment = src.get_fragment(0);
		typedef risa_gl::fragment_range<pixel_store_t> fragment_range_t;
		fragment_range_t frag_range(fragment.begin(), fragment.end());
				
		aligned_wideword_type result_ =
			getter(frag_range.get_middle().begin(),
				   frag_range.get_middle().begin());

		converter convert;
		unaligned_wideword_type result = 
			convert.to_unaligned_wideword_type(result_);

		CPPUNIT_ASSERT(result[0] == 0);
		CPPUNIT_ASSERT(result[1] == 0);
		CPPUNIT_ASSERT(result[2] == 0);
		CPPUNIT_ASSERT(result[3] == 0);

		CPPUNIT_ASSERT(result[4] == 1);
		CPPUNIT_ASSERT(result[5] == 0);
		CPPUNIT_ASSERT(result[6] == 1);
		CPPUNIT_ASSERT(result[7] == 0);

		CPPUNIT_ASSERT(result[8] == 2);
		CPPUNIT_ASSERT(result[9] == 0);
		CPPUNIT_ASSERT(result[10] == 2);
		CPPUNIT_ASSERT(result[11] == 0);

		CPPUNIT_ASSERT(result[12] == 3);
		CPPUNIT_ASSERT(result[13] == 0);
		CPPUNIT_ASSERT(result[14] == 3);
		CPPUNIT_ASSERT(result[15] == 0);
	}

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
		CPPUNIT_ASSERT(result[1] == 0);
		CPPUNIT_ASSERT(result[2] == 1);
		CPPUNIT_ASSERT(result[3] == 0);

		CPPUNIT_ASSERT(result[4] == 0);
		CPPUNIT_ASSERT(result[5] == 0);
		CPPUNIT_ASSERT(result[6] == 1);
		CPPUNIT_ASSERT(result[7] == 0);

		CPPUNIT_ASSERT(result[8] == 0);
		CPPUNIT_ASSERT(result[9] == 0);
		CPPUNIT_ASSERT(result[10] == 1);
		CPPUNIT_ASSERT(result[11] == 0);

		CPPUNIT_ASSERT(result[12] == 0);
		CPPUNIT_ASSERT(result[13] == 0);
		CPPUNIT_ASSERT(result[14] == 1);
		CPPUNIT_ASSERT(result[15] == 0);

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( alpha_factor_test );
