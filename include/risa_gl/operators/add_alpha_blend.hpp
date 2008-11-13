#ifndef RISA_ADD_ALPHA_BLEND_HPP_
#define RISA_ADD_ALPHA_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 加色アルファブレンディング(alphaは破壊)
		 * r.color = saturation(src.color * src.a +
		 *                      dest.color * dest.a * (1 - src.a))
		 * r.a = ?
		 */
		// {{{ add_alpha_blend_operator
		class add_alpha_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				invert_source_alpha_getter,
				not_calculate_policy>
			add_alpha_blend_operator_type;

			add_alpha_blend_operator_type blender;
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
		 * 加色アルファブレンディング(alphaはsourceを保存)
		 * r.color = saturation(src.color * src.a +
		 *                      dest.color * dest.a * (1 - src.a))
		 * r.a = src.a
		 */
		// {{{ add_alpha_blend_save_source_alpha_operator
		class add_alpha_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				invert_source_alpha_getter,
				alpha_calculate_policy<source_alpha_getter> >
			add_alpha_blend_save_source_alpha_operator_type;

			add_alpha_blend_save_source_alpha_operator_type blender;
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
		 * 加色アルファブレンディング(alphaはdestinationを保存)
		 * r.color = saturation(src.color * src.a +
		 *                      dest.color * dest.a * (1 - src.a))
		 * r.a = dest.a
		 */
		// {{{ add_alpha_blend_save_destination_alpha_operator
		class add_alpha_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				invert_source_alpha_getter,
				alpha_calculate_policy<destination_alpha_getter> >
			add_alpha_blend_save_destination_alpha_operator_type;

			add_alpha_blend_save_destination_alpha_operator_type blender;
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
		 * 加色アルファブレンディング(destinationが半透明用)
		 * r.color = saturation(src.color * src.a +
		 *                      dest.color * dest.a * (1 - src.a))
		 * r.a = src.a + dest.a * (1 - src.a)
		 */
		// {{{ add_alpha_blend_transmissive_destination_operator
		class add_alpha_blend_transmissive_destination_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				source_alpha_getter,
				multiply_invert_source_alpha_and_destination_alpha_getter,
				multiply_alpha_and_alpha_policy<
				source_alpha_getter,
				destination_alpha_getter> >
			add_alpha_blend_transmissive_destination_operator_type;

			add_alpha_blend_transmissive_destination_operator_type blender;
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

		/**
		 * 加色アルファブレンディング(destinationが加算用)
		 * r.color = saturation(src.color * src.a +
		 *                      dest.color * (1 - src.a))
		 * r.a = src.a + dest.a * (1 - src.a)
		 */
		// {{{ add_alpha_blend_additive_destination_operator
		class add_alpha_blend_additive_destination_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				source_alpha_getter,
				invert_source_alpha_getter,
				multiply_alpha_and_alpha_policy<
				source_alpha_getter,
				destination_alpha_getter> >
			add_alpha_blend_additive_destination_operator_type;

			add_alpha_blend_additive_destination_operator_type blender;
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

#endif /* RISA_ADD_ALPHA_BLEND_HPP_ */
