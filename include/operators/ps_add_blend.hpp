#ifndef RISA_PS_ADD_BLEND_HPP_
#define RISA_PS_ADD_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>
#include <operators/add_blend.hpp>
#include <operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * PS互換加色ブレンディング(alphaは破壊)
		 * r.color =
		 *  alpha_blend(add_blend_save_source_alpha(src, dest),
		 *              dest, result);
		 * r.a = ?
		 *
		 * src  R:213 G:213 B:213 A:128
		 * dest R:182 G: 41 B: 41 A:128
		 * res  R:219 G:148 B:148
		 *
		 * src  R:255 G:255 B:255 A:128
		 * dest R:255 G:  0 B:  0 A:128
		 * res  R:255 G:128 B:128
		 */
		// {{{ ps_add_blend_operator
		class ps_add_blend_operator
		{
		private:
			typedef photoshop_blend<
				add_blend_save_source_alpha_operator,
				alpha_blend_operator>
			ps_add_blend_operator_type;
			ps_add_blend_operator_type blender;
		public:
			ps_add_blend_operator():
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
		 * PS互換加色ブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_add_blend_save_destination_alpha_operator
		class ps_add_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				add_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_add_blend_operator_type;
			ps_add_blend_operator_type blender;
		public:
			ps_add_blend_save_destination_alpha_operator():
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

#endif /* RISA_PS_ADD_BLEND_HPP_ */
