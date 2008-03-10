#ifndef RISA_LIGHTEN_BLEND_HPP_
#define RISA_LIGHTEN_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 比較(明)ブレンディング(alphaは破壊)
		 * r.color = max(src.color, dest.color)
		 * r.a = ?
		 */
		// {{{ lighten_blend_operator
		class lighten_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				compare_greater_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			lighten_blend_operator_type;

			lighten_blend_operator_type blender;
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
		 * 比較(明)ブレンディング(alphaはsourceを保存)
		 * r.color = max(src.color, dest.color)
		 * r.a = src.a
		 */
		// {{{ lighten_blend_save_source_alpha_operator
		class lighten_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				compare_greater_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			lighten_blend_save_source_alpha_operator_type;

			lighten_blend_save_source_alpha_operator_type blender;
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
		 * 比較(明)ブレンディング(alphaはdestinationを保存)
		 * r.color = max(src.color, dest.color)
		 * r.a = dest.a
		 */
		// {{{ lighten_blend_save_destination_alpha_operator
		class lighten_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				compare_greater_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			lighten_blend_save_destination_alpha_operator_type;

			lighten_blend_save_destination_alpha_operator_type blender;
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
#endif /* RISA_LIGHTEN_BLEND_HPP_ */
