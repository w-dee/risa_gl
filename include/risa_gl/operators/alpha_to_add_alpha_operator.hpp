#ifndef RISA_ALPHA_TO_ADD_ALPHA_HPP_
#define RISA_ALPHA_TO_ADD_ALPHA_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * アルファ画素から加算用アルファ画素への変換
		 */
		// {{{ alpha_to_add_alpha_operator
		class alpha_to_add_alpha_operator
		{
		private:
			typedef primitive::monomial_function<
				source_getter,
				zero_getter,
				bit_setter,
				plus_function,
				source_alpha_getter,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter>	>
			alpha_to_add_alpha_opeartor_type;

			alpha_to_add_alpha_opeartor_type blender;
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

#endif /* RISA_ALPHA_TO_ADD_ALPHA_HPP_ */
