#ifndef RISA_OPERATORS_COLORMAP_HPP_
#define RISA_OPERATORS_COLORMAP_HPP_
#include "operators/primitive/primitive.hpp"

namespace risa_gl
{
	namespace operators
	{
		namespace primitive = risa_gl::primitive;

		template <typename src_itor_t,
				  typename dest_itor_t,
				  typename result_itor_t>
		class colormap_operator
		{
		public:
			typedef alpha_factor<
				destination_target_selecter,
				get_brightness_method_selecter>
			dest_brightness_factor;
				
			typedef primitive::blend<dest_brightness_factor,
									 identity_factor,
									 zero_factor,
									 zero_factor>
			colormap;
		};
									 
	};
};

#endif /* RISA_OPERATORS_COLORMAP_HPP_ */
