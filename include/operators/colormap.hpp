#ifndef RISA_OPERATORS_COLORMAP_HPP_
#define RISA_OPERATORS_COLORMAP_HPP_
#include "operators/primitive/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 65階調透明度を拡張して適用するオペレータ
		 */
		class colormap_65level_operator
		{
		public:
			typedef primitive::alpha_factor<
				primitive::destination_target_selecter,
				primitive::get_opacity_method_selecter,
				primitive::scaler<1, 65> >
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

		/**
		 * 透明度を適用するオペレータ
		 */
		class colormap_operator
		{
		public:
			typedef primitive::alpha_factor<
				primitive::destination_target_selecter,
				primitive::get_opacity_method_selecter,
				primitive::scaler<1, 256> >
			colormap;

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				colormap()(src, dest, result);
			}
		};									 
	};
};

#endif /* RISA_OPERATORS_COLORMAP_HPP_ */
