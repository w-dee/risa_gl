#ifndef RISA_COLOR_COPY_HPP_
#define RISA_COLOR_COPY_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		class color_copy_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				zero_getter,
				bit_setter,
				plus_function,
				identity_alpha_factor,
				zero_alpha_factor,
				alpha_calculate_policy<
				destination_alpha_getter> >
			color_copy_operator_type;

			color_copy_operator_type blender;
		public:

			/**
			 * srcのもつcolor値をdestのalpha値とマージしてresultにセットする
			 */
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
	}
}

#endif /* RISA_COLOR_COPY_HPP_ */
