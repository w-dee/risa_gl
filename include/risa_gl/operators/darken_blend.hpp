#ifndef RISA_DARKEN_BLEND_HPP_
#define RISA_DARKEN_BLEND_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 比較(暗)ブレンディング(alphaは破壊)
		 * r.color = min(src.color, dest.color)
		 * r.a = ?
		 */
		// {{{ darken_blend_operator
		class darken_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				compare_lesser_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			darken_blend_operator_type;

			darken_blend_operator_type blender;
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
		 * 比較(暗)ブレンディング(alphaはsourceを保存)
		 * r.color = min(src.color, dest.color)
		 * r.a = src.a
		 */
		// {{{ darken_blend_save_source_alpha_operator
		class darken_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				compare_lesser_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			darken_blend_save_source_alpha_operator_type;

			darken_blend_save_source_alpha_operator_type blender;
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
		 * 比較(暗)ブレンディング(alphaはdestinationを保存)
		 * r.color = min(src.color, dest.color)
		 * r.a = dest.a
		 */
		// {{{ darken_blend_save_destination_alpha_operator
		class darken_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				compare_lesser_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			darken_blend_save_destination_alpha_operator_type;

			darken_blend_save_destination_alpha_operator_type blender;
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
#endif /* RISA_DARKEN_BLEND_HPP_ */
