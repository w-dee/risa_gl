#ifndef RISA_COLOR_COPY_HPP_
#define RISA_COLOR_COPY_HPP_

#include "operators/primitive/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{

		class color_copy_operator
		{
		public:
			typedef primitive::channel_copy<
				primitive::source_target_selecter,
				primitive::source_target_selecter,
				primitive::source_target_selecter,
				primitive::destination_target_selecter>
			color_copy;

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				color_copy()(src, dest, result);
			}
		};
	};
};

#endif /* RISA_COLOR_COPY_HPP_ */
