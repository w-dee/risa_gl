#ifndef RISA_DIV_BLEND_HPP_
#define RISA_DIV_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 除算ブレンディング(alphaは破壊)
		 */
		// {{{ div_blend_operator
		class div_blend_operator
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
				not_calculate_policy>
			div_blend_operator_type;

			div_blend_operator_type blender;
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
		 */
		// {{{ div_blend_save_source_alpha_operator
		class div_blend_save_source_alpha_operator
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
				alpha_calculate_policy<source_alpha_getter> >
			div_blend_save_source_alpha_operator_type;

			div_blend_save_source_alpha_operator_type blender;
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
		 */
		// {{{ div_blend_save_destination_alpha_operator
		class div_blend_save_destination_alpha_operator
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
			div_blend_save_destination_alpha_operator_type;

			div_blend_save_destination_alpha_operator_type blender;
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

#endif /* RISA_DIV_BLEND_HPP_ */
