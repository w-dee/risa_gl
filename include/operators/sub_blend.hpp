#ifndef RISA_SUB_BLEND_HPP_
#define RISA_SUB_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 減色ブレンディング(alphaは破壊)
		 * r.color = saturation(src.color - dest.color)
		 * r.a = ?
		 */
		// {{{ sub_blend_operator
		class sub_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				complement_destination_getter,
				bit_setter,
				under_saturation_factor,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			sub_blend_opeartor_type;

			sub_blend_opeartor_type blender;
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
		 * 減色ブレンディング(alphaはdestinationを保存)
		 * r.color = saturation(src.color - dest.color)
		 * r.a = dest.a
		 */
		// {{{ sub_blend_save_destination_alpha_operator
		class sub_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				complement_destination_getter,
				bit_setter,
				under_saturation_factor,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			sub_blend_save_destination_alpha_opeartor_type;

			sub_blend_save_destination_alpha_opeartor_type blender;
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

#endif /* RISA_SUB_BLEND_HPP_ */
