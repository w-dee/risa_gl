#ifndef RISA_PRIMITIVE_EXT_INST_SSE2_FUNCTIONAL_HPP_
#define RISA_PRIMITIVE_EXT_INST_SSE2_FUNCTIONAL_HPP_

#include <risa_gl/primitive/extension_instructions/sse2/risa_sse2_types.hpp>

namespace risa_gl
{
	namespace ext_instruction 
	{
		namespace sse2
		{
			class converter
			{
			public:
				native_word_type to_native_word_type(
					const word_type& src) const
				{
					native_word_type result;
					_mm_store_si128(
						reinterpret_cast<word_type*>(&result[0]),
						src);
					return result;
				}

				word_type to_word_type(
					native_word_type& src) const
				{
					return _mm_load_si128(
						reinterpret_cast<const word_type*>(&src));
				}
			};

			class vertical_add_saturation
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_adds_epu16(mem1, mem2);
				}
			};

			class vertical_add
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_add_epi16(mem1, mem2);
				}
			};

			class vertical_mulutiply_high
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_mulhi_epu16(mem1, mem2);
				}
			};
		}
	}
}
#endif /* RISA_PRIMITIVE_EXT_INST_SSE2_FUNCTIONAL_HPP_ */
