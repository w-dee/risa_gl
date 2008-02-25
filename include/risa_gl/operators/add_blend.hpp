#ifndef RISA_ADD_BLEND_HPP_
#define RISA_ADD_BLEND_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 加色ブレンディング(alphaは破壊)
		 * r.color = saturation(src.color + dest.color)
		 * r.a = ?
		 */
		// {{{ add_blend_operator
		class add_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			add_blend_operator_type;

			add_blend_operator_type blender;
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
		 * 加色ブレンディング(alphaはsourceを保存)
		 * r.color = saturation(src.color + dest.color)
		 * r.a = src.a
		 */
		// {{{ add_blend_save_source_alpha_operator
		class add_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			add_blend_save_source_alpha_operator_type;

			add_blend_save_source_alpha_operator_type blender;
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
		 * 加色ブレンディング(alphaはdestinationを保存)
		 * r.color = saturation(src.color + dest.color)
		 * r.a = dest.a
		 */
		// {{{ add_blend_save_destination_alpha_operator
		class add_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			add_blend_save_destination_alpha_operator_type;

			add_blend_save_destination_alpha_operator_type blender;
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

#endif /* RISA_ADD_BLEND_HPP_ */
