#ifndef RISA_PRIMITIVE_EXT_INST_SSE2_ALPHA_FACTOR_HPP_
#define RISA_PRIMITIVE_EXT_INST_SSE2_ALPHA_FACTOR_HPP_

#include <risa_gl/primitive/extension_instructions/sse2/risa_sse2_types.hpp>
#include <risa_gl/primitive/extension_instructions/sse2/functional.hpp>

namespace risa_gl {
	namespace ext_instruction 
	{
		namespace sse2
		{
			class identity_alpha_factor
			{
			private:
				const word_type identity_value;
				
				static word_type identity_init()
				{
					unsigned int init_value = 256;
					return _mm_load_ss(reinterpret_cast<float*>(&init_value));
				}
			public:
				identity_alpha_factor():
					identity_value(identity_init())
				{}

				template <typename src_itor_t,
						  typename dest_itor_t>
				word_type operator()(src_itor_t src,
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
				word_type operator()(src_itor_t src,
									 dest_itor_t dest) const
				{
					return converter().zero();
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
					endian_trait endian;
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
				word_type_ operator()(src_itor_t src,
									  dest_itor_t dest) const
				{
					return __mm_srli_epi32(*selector(src, dest),
										   alpha_offset * 8);
				}
			};
		}
	}
}

#endif /* RISA_PRIMITIVE_EXT_INST_SSE2_ALPHA_FACTOR_HPP_ */
