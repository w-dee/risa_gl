#ifndef RISA_EXT_SSE2_PRIMITIVE_ALPHA_POLICY_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_ALPHA_POLICY_HPP_

#include <risa_gl/ext/sse2/risa_types.hpp>
#include <risa_gl/endian_traits.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace primitive
			{
				/**
				 * アルファ値非計算ポリシー
				 */
				class not_calculate_policy
				{
				public:
					template <typename bit_t,
							  typename result_itor_t,
							  typename src_itor_t,
							  typename dest_itor_t>
					bit_t operator()(bit_t bits,
									  result_itor_t,
									  src_itor_t,
									  dest_itor_t) const
					{
						return bits;
					}
				};

				/**
				 * アルファ値計算ポリシー
				 * @param calculator
				 */
				template <typename calculator_type>
				class alpha_calculate_policy
				{
				private:
					calculator_type calculator;

					template <int alpha_position>
					static int init_alpha_position()
					{
						typedef endian_traits<risa_gl::uint32>
							endian_traits_t;
						endian_traits_t converter;
						return converter.little_to_current_offset(
							alpha_position) * 8;
					}
			
				public:
					alpha_calculate_policy(
						calculator_type calculator_ = calculator_type()):
						calculator(calculator_)
					{}

					template <typename bit_t,
							  typename result_itor_t,
							  typename src_itor_t,
							  typename dest_itor_t>
					risa_gl::uint32 operator()(bit_t bits,
											   result_itor_t,
											   src_itor_t src,
											   dest_itor_t dest) const
					{
						const int alpha_mask_position =
							init_alpha_position<
							type_traits<result_itor_t>::
							value_type::alpha_position>();

						return ((calculator(src, dest)-1) <<
								alpha_mask_position) |
							(bits & ~(0xff << alpha_mask_position));
					}
				};
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_ALPHA_POLICY_HPP_ */
