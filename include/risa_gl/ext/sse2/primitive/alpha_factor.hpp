#ifndef RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_

#include <risa_gl/ext/sse2/risa_types.hpp>
#include <risa_gl/ext/sse2/primitive/functional.hpp>
#include <risa_gl/endian_traits.hpp>
#include <risa_gl/endian_reverser.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace primitive
			{
				class identity_alpha_factor
				{
				private:
					const aligned_wideword_type identity_value;
				
					static aligned_wideword_type identity_init()
					{
						
						int init_value = byte_endian_reverser<256>::value;
						return _mm_set1_epi32(init_value);
					}
				public:
					identity_alpha_factor():
						identity_value(identity_init())
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return identity_value;
					}
				};

				class zero_alpha_factor
				{
				public:
					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return _mm_setzero_si128();
					}
				};

				template <typename selector_type, typename bit_get_method>
				class alpha_getter
				{
				public:
					typedef typename bit_get_method::pixel_type pixel_type;

				private:
					selector_type selector;
					const int alpha_offset;

					static int init_alpha_offset()
					{
						risa_gl::endian_traits<pixel_type> endian;
						return 
							endian.big_to_current_offset(
								bit_get_method::pixel_type::alpha_position);
					}
				public:
					alpha_getter():
						selector(),
						alpha_offset(init_alpha_offset())
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						aligned_wideword_type value =
							_mm_load_si128(
								reinterpret_cast<aligned_wideword_type*>(
									&*selector(src, dest)));
						return _mm_srli_epi32(value, alpha_offset * 8);
					}
				};

				template <typename selector_type, typename bit_get_method>
				class invert_alpha_getter
				{
				public:
					typedef typename bit_get_method::pixel_type pixel_type;

				private:
					selector_type selector;
					const vertical_not oper;
					const int alpha_offset;

					static int init_alpha_offset()
					{
						risa_gl::endian_traits<pixel_type> endian;
						return 
							endian.big_to_current_offset(
								pixel_type::alpha_position);
					}
				public:
					invert_alpha_getter():
						selector(),
						oper(),
						alpha_offset(init_alpha_offset())
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return oper(
							_mm_srli_epi32(
								*reinterpret_cast<aligned_wideword_type*>(
									&*selector(src, dest)),
								alpha_offset * 8));
					}
				};

				template <typename pixel_t>
				struct alpha_bits_get_method
				{
				public:
					typedef pixel_t pixel_type;

				private:
					primitive::vertical_and oper;
					aligned_wideword_type alpha_mask;

					static aligned_wideword_type get_mask() 
					{
						const int mask =
							0xff << (pixel_type::alpha_position * 8);
						return _mm_set1_epi32(mask);
					}

				public:
					alpha_bits_get_method():
						oper(),
						alpha_mask(get_mask())
					{}

					template <typename src_type,
							  typename result_type>
					result_type operator()(src_type value) const
					{
						return oper(value, alpha_mask);
					}
				};
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_ */