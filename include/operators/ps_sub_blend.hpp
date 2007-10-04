#ifndef RISA_PS_SUB_BLEND_HPP_
#define RISA_PS_SUB_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>
#include <operators/sub_blend.hpp>
#include <operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * PS互換減色ブレンディング(alphaは破壊)
		 * r.color =
		 *  alpha_blend(sub_blend_save_destination_alpha(src, dest),
		 *              dest, result);
		 * r.a = ?
		 */
		// {{{ ps_sub_blend_operator
		class ps_sub_blend_operator
		{
		private:
			typedef photoshop_blend<sub_blend_save_destination_alpha_operator,
									alpha_blend_operator>
			ps_sub_blend_operator_type;
			ps_sub_blend_operator_type blender;
		public:
			ps_sub_blend_operator():
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
		 * PS互換減色ブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_sub_blend_save_destination_alpha_operator
		class ps_sub_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				sub_blend_save_destination_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_sub_blend_operator_type;
			ps_sub_blend_operator_type blender;
		public:
			ps_sub_blend_save_destination_alpha_operator():
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

#endif /* RISA_PS_SUB_BLEND_HPP_ */
