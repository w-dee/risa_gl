#ifndef RISA_ALPHA_POLICY_HPP_
#define RISA_ALPHA_POLICY_HPP_

#include <risa_types.hpp>

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * アルファ値非計算ポリシー
		 */
		class not_calculate_policy
		{
		public:
			not_calculate_policy()
			{}

			not_calculate_policy(const not_calculate_policy&)
			{}

			template <typename bit_t,
					  typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(bit_t bits,
									   result_itor_t result,
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
		template <typename calculator>
		class alpha_calculate_policy
		{
		public:
			alpha_calculate_policy()
			{}

			alpha_calculate_policy(const alpha_calculate_policy&)
			{}

			template <typename bit_t,
					  typename result_itor_t,
					  typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(bit_t bits,
									   result_itor_t result,
									   src_itor_t src,
									   dest_itor_t dest) const
			{
				return ((calculator()(src, dest)-1) <<
						(result->alpha_position * 8)) |
					(bits & ~(0xff << (result->alpha_position * 8)));
			}
		};
	}
}

#endif /* RISA_ALPHA_POLICY_HPP_ */
