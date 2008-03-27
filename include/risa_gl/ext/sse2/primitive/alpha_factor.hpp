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

				template <typename selector_type,
						  typename bit_get_method_type>
				class alpha_getter
				{
				private:
					selector_type selector;
					bit_get_method_type bit_get_method;

				public:
					alpha_getter():
						selector(),
						bit_get_method()
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
						return bit_get_method(value);
					}
				};

				template <typename selector_type, typename bit_get_method>
				class invert_alpha_getter
				{
				public:
					typedef typename bit_get_method::pixel_type pixel_type;
					typedef
					alpha_getter<selector_type, bit_get_method>
					alpha_getter_type;

				private:
					alpha_getter_type getter;

				public:
					invert_alpha_getter():
						getter()
					{}

					template <typename src_itor_t,
							  typename dest_itor_t>
					aligned_wideword_type operator()(src_itor_t src,
													 dest_itor_t dest) const
					{
						return _mm_sub_epi8(_mm_setzero_si128(),
											getter(src, dest));
					}
				};

				template <typename pixel_t>
				struct alpha_bits_get_method
				{
				public:
					typedef pixel_t pixel_type;

				private:
					aligned_wideword_type alpha_mask;

					static aligned_wideword_type get_mask() 
					{
						const int mask =
							0xff << (pixel_type::alpha_position * 8);
						return _mm_set1_epi32(mask);
					}

				public:
					alpha_bits_get_method():
						alpha_mask(get_mask())
					{}

					aligned_wideword_type operator()(
						aligned_wideword_type value) const
					{
						return _mm_and_si128(value, alpha_mask);
					}
				};
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_ALPHA_FACTOR_HPP_ */
