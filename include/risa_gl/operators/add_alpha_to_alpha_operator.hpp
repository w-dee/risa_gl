#ifndef RISA_ADD_ALPHA_TO_ALPHA_HPP_
#define RISA_ADD_ALPHA_TO_ALPHA_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 加算用アルファ画素からアルファ画素への変換
		 */
		// {{{ add_alpha_to_alpha_operator
		class add_alpha_to_alpha_operator
		{
		private:
			typedef primitive::monomial_function<
				source_getter,
				zero_getter,
				bit_setter,
				plus_function,
				inverse_source_alpha_getter,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter>,
				divide_factor<1> >
			add_alpha_to_alpha_operator_type;

			add_alpha_to_alpha_operator_type blender;
		public:
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

#endif /* RISA_ADD_ALPHA_TO_ALPHA_HPP_ */
