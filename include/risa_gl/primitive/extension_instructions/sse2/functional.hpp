#ifndef RISA_PRIMITIVE_EXT_INST_SSE2_FUNCTIONAL_HPP_
#define RISA_PRIMITIVE_EXT_INST_SSE2_FUNCTIONAL_HPP_

#include <risa_gl/risa_types.hpp>
#include <risa_gl/primitive/extension_instructions/sse2/risa_sse2_types.hpp>

namespace risa_gl
{
	namespace ext_instruction 
	{
		namespace sse2
		{
			struct odd_mask
			{
				word_type operator()(const word_type& source) const
				{
					// source & 0x00ff00ff00ff00ff00ff00ff00ff00ff
					const word_type mask = _mm_set1_epi16(0x00ff);
					return _mm_and_si128(source, mask);
				}
			};

			struct even_mask
			{
				word_type operator()(const word_type& source) const
				{
					// source & 0xff00ff00ff00ff00ff00ff00ff00ff00
					const word_type mask = _mm_set1_epi16(0xff00);
					return _mm_and_si128(source, mask);
				}
			};

			class converter
			{
			public:
				native_word_type to_native_word_type(
					const word_type& src) const
				{
					native_word_type result;
					_mm_storeu_si128(
						reinterpret_cast<word_type*>(&result[0]),
						src);
					return result;
				}

				word_type to_word_type(
					native_word_type& src) const
				{
					return _mm_loadu_si128(
						reinterpret_cast<const word_type*>(&src));
				}

				native_word_type
				to_native_word_type_on_alignment(
					native_word_type* result,
					const word_type& src) const
				{
					_mm_storeu_si128(
						reinterpret_cast<word_type*>(&(result[0])),
						src);
					return *result;
				}

				word_type
				to_word_type_on_alignment(native_word_type& src) const
				{
					return _mm_load_si128(
						reinterpret_cast<const word_type*>(&src));
				}
			};

			struct zero_getter
			{
				template <typename lhs_type, typename rhs_type>
				word_type operator()(lhs_type, rhs_type) const
				{
					return _mm_setzero_si128();
				}
			};

			template <typename selector_type, typename alpha_getter_type>
			struct fill_getter
			{
				selector_type selector;
				alpha_getter_type alpha_getter;

				template <typename lhs_type, typename rhs_type>
				word_type operator()(lhs_type lhs, rhs_type rhs) const
				{
					risa_gl::word value = alpha_getter(selector(lhs, rhs));
					return _mm_set1_epi16(value);
				}
			};

			template <int shift>
			struct logical_left_byte_shift
			{
				word_type operator()(const word_type& source) const
				{
					return _mm_slli_si128(source, shift);
				}
			};

			struct logical_left_32bit_packed_shift
			{
				word_type operator()(const word_type& source, int shift) const
				{
					return _mm_slli_epi32(source, shift);
				}
			};

			struct logical_left_16bit_packed_shift
			{
				word_type operator()(const word_type& source, int shift) const
				{
					return _mm_slli_epi16(source, shift);
				}
			};

			template <int shift>
			struct logical_right_byte_shift
			{
				word_type operator()(const word_type& source) const
				{
					return _mm_srli_si128(source, shift);
				}
			};

			template <int shift>
			struct logical_right_32bit_packed_shift
			{
				word_type operator()(word_type source) const
				{
					return _mm_srli_epi32(source, shift);
				}
			};

			template <int shift>
			struct logical_right_16bit_packed_shift
			{
				word_type operator()(word_type source) const
				{
					return _mm_srli_epi16(source, shift);
				}
			};

			struct vertical_add_saturation
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_adds_epu8(mem1, mem2);
				}
			};

			struct vertical_add
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_add_epi8(mem1, mem2);
				}
			};

			struct vertical_sub_saturation
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_subs_epu16(mem1, mem2);
				}
			};

			struct vertical_sub
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_sub_epi8(mem1, mem2);
				}
			};

			struct vertical_not
			{
			private:
				const word_type mask;

				word_type gen_mask() const
				{
					return _mm_set1_epi8(0xff);
				}

			public:
				vertical_not():
					mask(gen_mask())
				{}

				vertical_not(const vertical_not& src):
					mask(src.mask)
				{}

				word_type operator()(const word_type& mem) const
				{
					return _mm_xor_si128(mem, mask);
				}
			};

			struct vertical_or
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_or_si128(mem1, mem2);
				}
			};

			struct vertical_multiply
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_mullo_epi16(mem1, mem2);
				}
			};

			struct vertical_compare
			{
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_cmpeq_epi8(mem1, mem2);
				}
			};
		}
	}
}
#endif /* RISA_PRIMITIVE_EXT_INST_SSE2_FUNCTIONAL_HPP_ */