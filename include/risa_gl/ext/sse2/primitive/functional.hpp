#ifndef RISA_EXT_SSE2_PRIMITIVE_FUNCTIONAL_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_FUNCTIONAL_HPP_

#include <risa_gl/risa_types.hpp>
#include <risa_gl/ext/sse2/risa_types.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace primitive
			{
				class converter
				{
				public:
					/**
					 * 非アライメントメモリに対してsrcをコピー
					 */
					unaligned_wideword_type to_unaligned_wideword_type(
						const aligned_wideword_type& src) const
					{
						unaligned_wideword_type result;
						_mm_storeu_si128(
							reinterpret_cast<aligned_wideword_type*>(
								&result[0]), src);
						return result;
					}

					aligned_wideword_type to_aligned_wideword_type(
						unaligned_wideword_type& src) const
					{
						return _mm_loadu_si128(
							reinterpret_cast<const aligned_wideword_type*>(
								&src));
					}

					unaligned_wideword_type
					to_unaligned_wideword_type_on_alignment(
						unaligned_wideword_type* result,
						const aligned_wideword_type& src) const
					{
						_mm_storeu_si128(
							reinterpret_cast<aligned_wideword_type*>(
								&(result[0])), src);
						return *result;
					}

					aligned_wideword_type
					to_aligned_wideword_type_from_alignment(
						unaligned_wideword_type& src) const
					{
						return _mm_load_si128(
							reinterpret_cast<const aligned_wideword_type*>(
								&src));
					}
				};

				template <typename selector_type, typename alpha_getter_type>
				struct fill_getter
				{
					selector_type selector;
					alpha_getter_type alpha_getter;

					template <typename lhs_type, typename rhs_type>
					aligned_wideword_type operator()(
						lhs_type lhs, rhs_type rhs) const
					{
						risa_gl::word value = alpha_getter(selector(lhs, rhs));
						return _mm_set1_epi16(value);
					}
				};

				template <int shift>
				struct logical_left_byte_shift
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& source) const
					{
						return _mm_slli_si128(source, shift);
					}
				};

				struct logical_left_32bit_packed_shift
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& source, int shift) const
					{
						return _mm_slli_epi32(source, shift);
					}
				};

				struct logical_left_16bit_packed_shift
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& source, int shift) const
					{
						return _mm_slli_epi16(source, shift);
					}
				};

				template <int shift>
				struct logical_right_byte_shift
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& source) const
					{
						return _mm_srli_si128(source, shift);
					}
				};

				template <int shift>
				struct logical_right_32bit_packed_shift
				{
					aligned_wideword_type operator()(
						aligned_wideword_type source) const
					{
						return _mm_srli_epi32(source, shift);
					}
				};

				template <int shift>
				struct logical_right_16bit_packed_shift
				{
					aligned_wideword_type operator()(
						aligned_wideword_type source) const
					{
						return _mm_srli_epi16(source, shift);
					}
				};

				struct vertical_add_saturation
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_adds_epu8(mem1, mem2);
					}
				};

				struct vertical_add
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_add_epi8(mem1, mem2);
					}
				};

				struct vertical_sub_saturation
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_subs_epu16(mem1, mem2);
					}
				};

				struct vertical_sub
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_sub_epi8(mem1, mem2);
					}
				};

				struct vertical_not
				{
				private:
					const aligned_wideword_type mask;

					aligned_wideword_type gen_mask() const
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

					aligned_wideword_type operator()(
						const aligned_wideword_type& mem) const
					{
						return _mm_xor_si128(mem, mask);
					}
				};

				struct vertical_or
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_or_si128(mem1, mem2);
					}
				};

				struct vertical_and
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_and_si128(mem1, mem2);
					}
				};

				struct vertical_multiply
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_mullo_epi16(mem1, mem2);
					}
				};

				struct vertical_compare
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& mem1,
						const aligned_wideword_type& mem2) const
					{
						return _mm_cmpeq_epi8(mem1, mem2);
					}
				};
			}
		}
	}
}
#endif /* RISA_EXT_SSE2_PRIMITIVE_FUNCTIONAL_HPP_ */
