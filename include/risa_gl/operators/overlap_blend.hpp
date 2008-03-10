#ifndef RISA_OVERLAP_BLEND_HPP_
#define RISA_OVERLAP_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		// {{{ overlap_blend_operator
		class overlap_blend_operator
		{
		private:
			typedef primitive::monomial_function<
				dynamic_constant_getter,
				source_getter,
				bit_setter,
				plus_function,
				constant_alpha_factor,
				constant_alpha_factor,
				not_calculate_policy>
			overlap_blend_operator_type;

			overlap_blend_operator_type blender;
		public:
			template <typename pixel_t>
			overlap_blend_operator(const pixel_t pixel):
				blender(
					dynamic_constant_getter(pixel.get_bit_representation()),
					source_getter(),
					bit_setter(),
					plus_function(),
					constant_alpha_factor(pixel.get_alpha()),
					constant_alpha_factor(256 - pixel.get_alpha()))
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

		// {{{ overlap_blend_save_source_alpha_operator
		class overlap_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::monomial_function<
				dynamic_constant_getter,
				source_getter,
				bit_setter,
				plus_function,
				constant_alpha_factor,
				constant_alpha_factor,
				alpha_calculate_policy<constant_alpha_factor> >
			overlap_blend_save_source_alpha_operator_type;

			overlap_blend_save_source_alpha_operator_type blender;
		public:
			template <typename pixel_t>
			overlap_blend_save_source_alpha_operator(const pixel_t pixel):
				blender(
					dynamic_constant_getter(pixel.get_bit_representation()),
					source_getter(),
					bit_setter(),
					plus_function(),
					constant_alpha_factor(pixel.get_alpha()),
					constant_alpha_factor(256 - pixel.get_alpha()),
					alpha_calculate_policy<constant_alpha_factor>(
						constant_alpha_factor(pixel.get_alpha())))
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

		// {{{ overlap_blend_save_destination_alpha_operator
		class overlap_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::monomial_function<
				dynamic_constant_getter,
				source_getter,
				bit_setter,
				plus_function,
				constant_alpha_factor,
				constant_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			overlap_blend_save_destination_alpha_operator_type;

			overlap_blend_save_destination_alpha_operator_type blender;
		public:
			template <typename pixel_t>
			overlap_blend_save_destination_alpha_operator(const pixel_t pixel):
				blender(
					dynamic_constant_getter(pixel.get_bit_representation()),
					source_getter(),
					bit_setter(),
					plus_function(),
					constant_alpha_factor(pixel.get_alpha()),
					constant_alpha_factor(256 - pixel.get_alpha()))
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

		// {{{ overlap_blend_transmissive_destination_operator
		class overlap_blend_transmissive_destination_operator
		{
		private:
			typedef primitive::monomial_function<
				dynamic_constant_getter,
				source_getter,
				bit_setter,
				plus_function,
				constant_alpha_factor,
				multiply_factor<constant_alpha_factor,
								multiply_type_factor<source_alpha_getter> >,
				multiply_alpha_and_alpha_policy<
				constant_alpha_factor,
				source_alpha_getter> >
			overlap_blend_transmissive_destination_operator_type;

			overlap_blend_transmissive_destination_operator_type blender;
		public:

			template <typename pixel_t>
			overlap_blend_transmissive_destination_operator(const pixel_t pixel):
				blender(
					dynamic_constant_getter(pixel.get_bit_representation()),
					source_getter(),
					bit_setter(),
					plus_function(),
					constant_alpha_factor(pixel.get_alpha()),
					constant_alpha_factor(256 - pixel.get_alpha()),
					multiply_alpha_and_alpha_policy<
					constant_alpha_factor, source_alpha_getter>(
						constant_alpha_factor(pixel.get_alpha())))
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

		// {{{ overlap_blend_additive_destination_operator
		class overlap_blend_additive_destination_operator
		{
		private:
			typedef primitive::monomial_function<
				dynamic_constant_getter,
				source_getter,
				bit_setter,
				add_saturation_function,
				constant_alpha_factor,
				constant_alpha_factor,
				multiply_alpha_and_alpha_policy<
				constant_alpha_factor,
				source_alpha_getter> >
			overlap_blend_additive_destination_operator_type;

			overlap_blend_additive_destination_operator_type blender;
		public:
			template <typename pixel_t>
			overlap_blend_additive_destination_operator(const pixel_t pixel):
				blender(
					dynamic_constant_getter(pixel.get_bit_representation()),
					source_getter(),
					bit_setter(),
					add_saturation_function(),
					constant_alpha_factor(pixel.get_alpha()),
					constant_alpha_factor(256 - pixel.get_alpha()),
					multiply_alpha_and_alpha_policy<
					constant_alpha_factor, source_alpha_getter>(
						constant_alpha_factor(pixel.get_alpha())))
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

#endif /* RISA_OVERLAP_BLEND_HPP_ */
