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

				word_type zero() const
				{
					return _mm_setzero_si128();
				}

				word_type to_fill_value(risa_gl::byte value) const
				{
					return _mm_set1_epi8(value);
				}

				word_type to_fill_value(risa_gl::word value) const
				{
					return _mm_set1_epi16(value);
				}

				word_type to_fill_values(risa_gl::word value1,
										 risa_gl::word value2,
										 risa_gl::word value3,
										 risa_gl::word value4) const
				{
					return _mm_set_epi16(
						value4, value4,
						value3, value3,
						value2, value2,
						value1, value1);
				}

				word_type to_fill_values(risa_gl::byte value1,
										 risa_gl::byte value2,
										 risa_gl::byte value3,
										 risa_gl::byte value4) const
				{
					return _mm_set_epi8(
						value4, value4, value4, value4,
						value3, value3, value3, value3,
						value2, value2, value2, value2,
						value1, value1, value1, value1);
				}

				word_type odd_mask(const word_type& source) const
				{
					// source & 0x00ff00ff00ff00ff00ff00ff00ff00ff
					const word_type mask = to_fill_value(
						static_cast<const risa_gl::word>(0x00ff));
					return _mm_and_si128(source, mask);
				}

				word_type even_mask(const word_type& source) const
				{
					// source & 0xff00ff00ff00ff00ff00ff00ff00ff00
					const word_type mask = to_fill_value(
						static_cast<const risa_gl::word>(0xff00));
					return _mm_and_si128(source, mask);
				}

				template <int shift>
				word_type logical_left_byte_shift(const word_type& source) const
				{
					return _mm_slli_si128(source, shift);
				}

				word_type logical_left_32bit_packed_shift(
					const word_type& source, int shift) const
				{
					return _mm_slli_epi32(source, shift);
				}

				word_type logical_left_16bit_packed_shift(
					const word_type& source, int shift) const
				{
					return _mm_slli_epi16(source, shift);
				}

				template <int shift>
				word_type logical_right_byte_shift(const word_type& source) const
				{
					return _mm_srli_si128(source, shift);
				}

				word_type logical_right_32bit_packed_shift(
					const word_type& source, int shift) const
				{
					return _mm_srli_epi32(source, shift);
				}


				word_type logical_right_16bit_packed_shift(
					const word_type& source, int shift) const
				{
					return _mm_srli_epi16(source, shift);
				}
			};

			class vertical_add_saturation
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_adds_epu8(mem1, mem2);
				}
			};

			class vertical_add
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_add_epi8(mem1, mem2);
				}
			};

			class vertical_sub_saturation
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_subs_epu16(mem1, mem2);
				}
			};

			class vertical_sub
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_sub_epi8(mem1, mem2);
				}
			};

			class vertical_not
			{
			private:
				const word_type mask;

				word_type gen_mask() const
				{
					converter convert;
					return convert.to_fill_value(
						static_cast<risa_gl::byte>(0xff));
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

			class vertical_or
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_or_si128(mem1, mem2);
				}
			};

			class vertical_multiply
			{
			public:
				word_type operator()(const word_type& mem1,
									 const word_type& mem2) const
				{
					return _mm_mullo_epi16(mem1, mem2);
				}
			};

			class vertical_compare
			{
			public:
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
