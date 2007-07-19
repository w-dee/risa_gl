#ifndef RISA_COMPUTE_FACTOR_HPP_
#define RISA_COMPUTE_FACTOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	namespace primitive
	{
		class lower_mask_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return value & 0x00ff00ffU;
			}
		};

		class higher_mask_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return value & 0xff00ff00U;
			}
		};

		class saturation_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return
					(value & 0xff000000U) ? 0x00ff0000U : (value & 0x00ff0000U)|
					(value & 0x0000ff00U) ? 0x000000ffU : (value & 0x000000ffU);
			}
		};

		class nop_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return value;
			}
		};
	};
};

#endif /* RISA_COMPUTE_FACTOR_HPP_ */
