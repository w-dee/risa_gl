#ifndef RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_

#include <risa_gl/ext/sse2/risa_sse2_types.hpp>
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

				template <typename selector_type, typename pixel_type>
				class alpha_getter
				{
				private:
					selector_type selector;
					const int alpha_offset;

					static int init_alpha_offset()
					{
						risa_gl::endian_traits<pixel_type> endian;
						return 
							endian.to_big_to_current_offset(
								pixel_type::alpha_position);
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
						return _mm_srli_epi32(*selector(src, dest),
											  alpha_offset * 8);
					}
				};
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_ */
