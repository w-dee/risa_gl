#ifndef RISA_MAT_BLEND_HPP_
#define RISA_MAT_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * マット合成(alphaは合成)
		 */
		// {{{ mat_blend_save_calculate_alpha_operator
		class mat_blend_save_calculate_alpha_operator
		{
		private:
			typedef primitive::monomial_function<
				source_getter,
				dynamic_constant_getter,
				bit_setter,
				plus_function,
				source_alpha_getter,
				invert_source_alpha_getter,
				multiply_alpha_and_alpha_policy<
				source_alpha_getter,
				constant_alpha_factor> >
			mat_blend_operator_type;

			mat_blend_operator_type blender;
		public:
			template <typename pixel_type>
			mat_blend_save_calculate_alpha_operator(
				const pixel_type& pixel_):
				blender(
					source_getter(),
					dynamic_constant_getter(pixel_.get_bit_representation()),
					bit_setter(),
					plus_function(),
					source_alpha_getter(),
					invert_source_alpha_getter(),
					multiply_alpha_and_alpha_policy<
					source_alpha_getter,
					constant_alpha_factor>(
						source_alpha_getter(),
						constant_alpha_factor(pixel_.get_alpha())))
			{}

			template <typename src_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							result_itor_t result) const
			{
				blender(src, result);
			}
		};
		// }}}

		/**
		 * マット合成(alphaは加算用として合成)
		 */
		// {{{ mat_additive_blend_save_calculate_alpha_operator
		class mat_additive_blend_save_calculate_alpha_operator
		{
		private:
			typedef primitive::monomial_function<
				source_getter,
				dynamic_constant_getter,
				bit_setter,
				plus_function,
				identity_alpha_factor,
				invert_source_alpha_getter,
				multiply_alpha_and_alpha_policy<
				source_alpha_getter,
				constant_alpha_factor> >
			mat_additive_blend_save_calculate_alpha_operator_type;

			mat_additive_blend_save_calculate_alpha_operator_type blender;
		public:
			template <typename pixel_type>
			mat_additive_blend_save_calculate_alpha_operator(
				const pixel_type& pixel_):
				blender(
					source_getter(),
					dynamic_constant_getter(pixel_.get_bit_representation()),
					bit_setter(),
					plus_function(),
					identity_alpha_factor(),
					invert_source_alpha_getter(),
					multiply_alpha_and_alpha_policy<
					source_alpha_getter,
					constant_alpha_factor>(
						source_alpha_getter(),
						constant_alpha_factor(pixel_.get_alpha())))
			{}

			template <typename src_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							result_itor_t result) const
			{
				blender(src, result);
			}
		};
		// }}}

	}
}

#endif /* RISA_MAT_BLEND_HPP_ */
