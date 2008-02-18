#ifndef RISA_TO_TRANSPARENCY_HPP_
#define RISA_TO_TRANSPARENCY_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 透明画素に変換
		 */
		// {{{ to_transparency_operator
		class to_transparency_operator
		{
		private:
			typedef primitive::monomial_function<
				source_getter,
				zero_getter,
				bit_setter,
				plus_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<full_transparent_alpha_factor> >
			to_transparency_opeartor_type;

			to_transparency_opeartor_type blender;
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

#endif /* RISA_TO_TRANSPARENCY_HPP_ */
