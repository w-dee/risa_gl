#ifndef RISA_PS_DIV_BLEND_HPP_
#define RISA_PS_DIV_BLEND_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>
#include <risa_gl/operators/div_blend.hpp>
#include <risa_gl/operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * PS互換覆い焼きカラーブレンディング(alphaは破壊)
		 */
		// {{{ ps_div_blend_operator
		class ps_div_blend_operator
		{
		private:
			typedef photoshop_blend<
				div_blend_save_source_alpha_operator,
				alpha_blend_operator>
			ps_div_blend_operator_type;
			ps_div_blend_operator_type blender;
		public:
			ps_div_blend_operator():
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
		 * PS互換覆い焼きカラーブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_div_blend_save_destination_alpha_operator
		class ps_div_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				div_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_div_blend_operator_type;
			ps_div_blend_operator_type blender;
		public:
			ps_div_blend_save_destination_alpha_operator():
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
		 * PS5互換覆い焼きカラーブレンディング
		 */
		// {{{ ps5_div_blend_operator
		class ps5_div_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				version5_divide_saturation_function<
						source_selector,
						destination_selector>,
				source_alpha_getter,
				identity_alpha_factor,
				not_calculate_policy>
			ps5_div_blend_operator_type;
			ps5_div_blend_operator_type blender;
		public:
			ps5_div_blend_operator():
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
		 * PS5互換覆い焼きカラーブレンディング(destination alphaを保存)
		 */
		// {{{ ps5_div_blend_save_destination_alpha_operator
		class ps5_div_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				version5_divide_saturation_function<
						source_selector,
						destination_selector>,
				source_alpha_getter,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			ps5_div_blend_operator_type;
			ps5_div_blend_operator_type blender;
		public:
			ps5_div_blend_save_destination_alpha_operator():
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

#endif /* RISA_PS_DIV_BLEND_HPP_ */
