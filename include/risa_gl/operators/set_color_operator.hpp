#ifndef RISA_SET_COLOR_HPP_
#define RISA_SET_COLOR_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 
		 */
		// {{{ set_color_operator
		class set_color_operator
		{
		private:
			typedef primitive::monomial_function<
				dynamic_constant_getter,
				zero_getter,
				bit_setter,
				plus_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			set_color_operator_type;

			set_color_operator_type blender;
		public:
			template <typename pixel_type>
			set_color_operator(const pixel_type& pixel_value):
				blender(dynamic_constant_getter(
							pixel_value.get_bit_representation()))
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

#endif /* RISA_SET_COLOR_HPP_ */
