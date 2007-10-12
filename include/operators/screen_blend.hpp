#ifndef RISA_SCREEN_BLEND_HPP_
#define RISA_SCREEN_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * スクリーン乗算ブレンディング(alphaは破壊)
		 * r.color = 1 - (1 - src.color) * (1 - dest.color)
		 * r.a = ?
		 */
		// {{{ screen_blend_operator
		class screen_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				invert_source_getter,
				invert_destination_getter,
				bit_setter,
				invert_multiply_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			screen_blend_opeartor_type;

			screen_blend_opeartor_type blender;
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
		// }}}

		/**
		 * スクリーン乗算ブレンディング(alphaはsourceを保存)
		 * r.color = 1 - (1 - src.color) * (1 - dest.color)
		 * r.a = src.a
		 */
		// {{{ screen_blend_save_source_alpha_operator
		class screen_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				invert_source_getter,
				invert_destination_getter,
				bit_setter,
				invert_multiply_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			screen_blend_save_source_alpha_opeartor_type;

			screen_blend_save_source_alpha_opeartor_type blender;
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
		// }}}

		/**
		 * スクリーン乗算ブレンディング(alphaはdestinationを保存)
		 * r.color = 1 - (1 - src.color) * (1 - dest.color)
		 * r.a = dest.a
		 */
		// {{{ screen_blend_save_destination_alpha_operator
		class screen_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				invert_source_getter,
				invert_destination_getter,
				bit_setter,
				invert_multiply_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			screen_blend_save_destination_alpha_opeartor_type;

			screen_blend_save_destination_alpha_opeartor_type blender;
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
		// }}}
	}
}
#endif /* RISA_SCREEN_BLEND_HPP_ */
