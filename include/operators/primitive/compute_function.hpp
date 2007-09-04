#ifndef RISA_COMPUTE_FUNCTION_HPP_
#define RISA_COMPUTE_FUNCTION_HPP_

#include <risa_types.hpp>

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * 飽和加算ファンクタ
		 */
		class saturation_function
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				const risa_gl::uint32 carry_bits =
					((lhs & rhs) +
					 (((lhs ^ rhs) >> 1) & 0x7f7f7f7f)) &
					0x80808080;
				const risa_gl::uint32 mask =
					(carry_bits << 1) - (carry_bits >> 7);
				return  (lhs + rhs - mask) | mask;
			}
		};

		/**
		 * 飽和減算ファンクタ
		 */
		class under_saturation_function
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				assert((lhs & 0xff00ff00) == 0);
				assert((rhs & 0xff00ff00) == 0);

				const risa_gl::uint32 not_use_borrow =
					((lhs | 0x01000100) - rhs) & 0x01000100;

				const risa_gl::uint32 mask = 
					not_use_borrow - (not_use_borrow >> 8);

				return ((lhs | 0x01000100) - rhs) & mask;
			}
		};

		/**
		 * 加算ファンクタ
		 */
		class plus_function
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				return lhs + rhs;
			}
		};

		/**
		 * 乗算ファンクタ
		 */
		class multiply_function
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				assert((lhs & 0xff00ff00) == 0);
				assert((rhs & 0xff00ff00) == 0);

				return 
					((((lhs & 0x000000ff) * (rhs & 0x000000ff)) |
					  ((lhs & 0x00ff0000) * ((rhs & 0x00ff0000) >> 16))) &
					 0xff00ff00) >> 8;
			}
		};

	}
}

#endif /* RISA_COMPUTE_FUNCTION_HPP_ */
