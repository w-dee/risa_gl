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
			public:
				template <typename src_itor_t,
						  typename dest_itor_t>
				word_type operator()(src_itor_t src,
									 dest_itor_t dest) const
				{
					return converter().to_fill_values(
						static_cast<risa_gl::word>(256),
						static_cast<risa_gl::word>(256),
						static_cast<risa_gl::word>(256),
						static_cast<risa_gl::word>(256));
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


		}
	}
}

#endif /* RISA_PRIMITIVE_EXT_INST_SSE2_ALPHA_FACTOR_HPP_ */
