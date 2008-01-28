#ifndef RISA_MAT_BLEND_HPP_
#define RISA_MAT_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * マット合成(alphaは破壊)
		 */
		// {{{ mat_blend_operator
		class mat_blend_operator
		{
		private:
			typedef primitive::monomial_function<
				source_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			mat_blend_opeartor_type;

			mat_blend_opeartor_type blender;
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
		 * マット合成(alphaはsourceを保存)
		 */
		// {{{ mat_blend_save_source_alpha_operator
		class mat_blend_save_source_alpha_operator
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
			mat_blend_save_source_alpha_opeartor_type;

			mat_blend_save_source_alpha_opeartor_type blender;
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
		 * マット合成(alphaはdestinationを保存)
		 */
		// {{{ mat_blend_save_destination_alpha_operator
		class mat_blend_save_destination_alpha_operator
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
			mat_blend_save_destination_alpha_opeartor_type;

			mat_blend_save_destination_alpha_opeartor_type blender;
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

#endif /* RISA_MAT_BLEND_HPP_ */
