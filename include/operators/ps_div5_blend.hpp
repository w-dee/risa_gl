#ifndef RISA_PS_DIV5_BLEND_HPP_
#define RISA_PS_DIV5_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>
#include <operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 除算ブレンディング(alphaは破壊)
		 * r.color = min(1, dest.color / (1 - src.color * src.alpha))
		 * r.a = ?
		 */
		// {{{ ps_div5_blend_operator
		class ps_div5_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				divide_saturation_function<
				source_selector,
				destination_selector>,
				source_alpha_getter,
				identity_alpha_factor,
				not_calculate_policy>
			div5_blend_opeartor_type;

			div5_blend_opeartor_type blender;
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
		 * 除算ブレンディング(alphaはsourceを保存)
		 * r.color = src.color * dest.color
		 * r.a = src.a
		 */
		// {{{ ps_div5_blend_save_source_alpha_operator
		class ps_div5_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				divide_saturation_function<
				source_selector,
				destination_selector>,
				source_alpha_getter,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			div5_blend_save_source_alpha_opeartor_type;

			div5_blend_save_source_alpha_opeartor_type blender;
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
		 * 除算ブレンディング(alphaはdestinationを保存)
		 * r.color = src.color * dest.color
		 * r.a = dest.a
		 */
		// {{{ ps_div5_blend_save_destination_alpha_operator
		class ps_div5_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				divide_saturation_function<
				source_selector,
				destination_selector>,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			div5_blend_save_destination_alpha_opeartor_type;

			div5_blend_save_destination_alpha_opeartor_type blender;
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

#endif /* RISA_PS_DIV5_BLEND_HPP_ */
