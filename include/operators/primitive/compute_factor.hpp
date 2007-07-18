#ifndef RISA_COMPUTE_FACTOR_HPP_
#define RISA_COMPUTE_FACTOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * compute factorコンパイルassertion用基底
		 *
		 *
		 */
		struct compute_factor_base {};

		struct saturation_factor : public compute_factor_base
		{
		public:
			risa_gl::uint32 operator()(risa_gl::int32 value) const
			{
				
		};
	};
};

#endif /* RISA_COMPUTE_FACTOR_HPP_ */
