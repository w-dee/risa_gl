#ifndef RISA_OPERATORS_COLORMAP_HPP_
#define RISA_OPERATORS_COLORMAP_HPP_
#include "operators/primitive/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{
		class colormap_operator
		{
		public:
			typedef primitive::alpha_factor<
				primitive::destination_target_selecter,
				primitive::get_brightness_method_selecter>
			dest_brightness_factor;
				
			typedef primitive::alternate_alpha_channel_blend<
				dest_brightness_factor>
			colormap;

			template <typename src_itor_t,
					  typename alpha_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							alpha_itor_t alpha,
							result_itor_t result) const
			{
				colormap()(src, alpha, result);
			}
		};
									 
	};
};

#endif /* RISA_OPERATORS_COLORMAP_HPP_ */
