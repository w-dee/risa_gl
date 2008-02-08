#ifndef RISA_PS_LIGHTEN_BLEND_HPP_
#define RISA_PS_LIGHTEN_BLEND_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/primitive/alpha_policy.hpp>
#include <risa_gl/operators/building_blocks.hpp>
#include <risa_gl/operators/alpha_blend.hpp>
#include <risa_gl/operators/lighten_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * PS互換比較(暗)ブレンディング(alphaは破壊)
		 */
		// {{{ ps_lighten_blend_operator
		class ps_lighten_blend_operator
		{
		private:
			typedef photoshop_blend<lighten_blend_save_source_alpha_operator,
									alpha_blend_operator>
			ps_lighten_blend_operator_type;
			ps_lighten_blend_operator_type blender;
		public:
			ps_lighten_blend_operator():
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
		 * PS互換比較(暗)ブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_lighten_blend_save_destination_alpha_operator
		class ps_lighten_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				lighten_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_lighten_blend_operator_type;
			ps_lighten_blend_operator_type blender;
		public:
			ps_lighten_blend_save_destination_alpha_operator():
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

#endif /* RISA_PS_LIGHTEN_BLEND_HPP_ */
