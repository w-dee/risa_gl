#ifndef RISA_PS_SOFTLIGHT_BLEND_HPP_
#define RISA_PS_SOFTLIGHT_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/primitive/alpha_policy.hpp>
#include <risa_gl/operators/building_blocks.hpp>
#include <risa_gl/operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		class softlight_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				softlight_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			softlight_blend_operator_type;

			softlight_blend_operator_type blender;
			
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				blender(src, dest, result);
			}
		};

		class softlight_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				softlight_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			softlight_blend_save_source_alpha_operator_type;

			softlight_blend_save_source_alpha_operator_type blender;
			
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				blender(src, dest, result);
			}
		};

		/**
		 * PS互換ソフトライトブレンディング(alphaは破壊)
		 */
		// {{{ ps_softlight_blend_operator
		class ps_softlight_blend_operator
		{
		private:
			typedef photoshop_blend<softlight_blend_save_source_alpha_operator,
									alpha_blend_operator>
			ps_softlight_blend_operator_type;
			ps_softlight_blend_operator_type blender;
		public:
			ps_softlight_blend_operator():
				blender()
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				blender(src, dest, result);
			}
		};
		// }}}

		/**
		 * PS互換ソフトライトブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_softlight_blend_save_destination_alpha_operator
		class ps_softlight_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				softlight_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_softlight_blend_operator_type;
			ps_softlight_blend_operator_type blender;
		public:
			ps_softlight_blend_save_destination_alpha_operator():
				blender()
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				blender(src, dest, result);
			}
		};
		// }}}
	}
}

#endif /* RISA_PS_SOFTLIGHT_BLEND_HPP_ */
