#ifndef RISA_ALPHA_COPY_HPP_
#define RISA_ALPHA_COPY_HPP_

#include "operators/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{
		class alpha_copy_operator
		{
		public:
			typedef primitive::channel_copy<
				source_target_selecter,
				source_target_selecter,
				source_target_selecter,
				destination_target_selecter>
			color_copy;

			
			
		};
	};
};
class 

#endif /* RISA_ALPHA_COPY_HPP_ */
