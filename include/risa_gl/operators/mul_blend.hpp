#ifndef RISA_MUL_BLEND_HPP_
#define RISA_MUL_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 乗算ブレンディング(alphaは破壊)
		 * r.color = src.color * dest.color
		 * r.a = ?
		 */
		// {{{ mul_blend_operator
		class mul_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				multiply_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			mul_blend_operator_type;

			mul_blend_operator_type blender;
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
		 * 乗算ブレンディング(alphaはsourceを保存)
		 * r.color = src.color * dest.color
		 * r.a = src.a
		 */
		// {{{ mul_blend_save_source_alpha_operator
		class mul_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				multiply_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			mul_blend_save_source_alpha_operator_type;

			mul_blend_save_source_alpha_operator_type blender;
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
		 * 乗算ブレンディング(alphaはdestinationを保存)
		 * r.color = src.color * dest.color
		 * r.a = dest.a
		 */
		// {{{ mul_blend_save_destination_alpha_operator
		class mul_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				multiply_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			mul_blend_save_destination_alpha_operator_type;

			mul_blend_save_destination_alpha_operator_type blender;
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

#endif /* RISA_MUL_BLEND_HPP_ */
