#ifndef RISA_ALPHA_COPY_HPP_
#define RISA_ALPHA_COPY_HPP_

#include "operators/primitive/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{
		class alpha_copy_operator
		{
		public:
			typedef primitive::channel_copy<
				primitive::destination_target_selecter,
				primitive::get_red_method_selecter,
				primitive::destination_target_selecter,
				primitive::get_green_method_selecter,
				primitive::destination_target_selecter,
				primitive::get_blue_method_selecter,
				primitive::source_target_selecter,
				primitive::get_alpha_method_selecter>
			alpha_copy;

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				alpha_copy()(src, dest, result);
			}
		};

		class opaque_copy_operator
		{
		public:
			typedef primitive::channel_copy<
				primitive::source_target_selecter,
				primitive::get_red_method_selecter,
				primitive::source_target_selecter,
				primitive::get_green_method_selecter,
				primitive::source_target_selecter,
				primitive::get_blue_method_selecter,
				primitive::destination_target_selecter,
				primitive::get_opacity_method_selecter>
			brightness_copy;

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				brightness_copy()(src, dest, result);
			}
		};
	};
};

#endif /* RISA_ALPHA_COPY_HPP_ */
