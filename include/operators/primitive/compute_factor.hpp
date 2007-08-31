#ifndef RISA_COMPUTE_FACTOR_HPP_
#define RISA_COMPUTE_FACTOR_HPP_

#include <risa_types.hpp>

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * 飽和加算ファンタ
		 */
		class saturation_factor
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

		class under_saturation_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				const risa_gl::uint32 borrow_bits =
					((((lhs ^ ~rhs) << 1) & 0x7f7f7f7f) -
					 (lhs & ~rhs)) &
					0x80808080;
				const risa_gl::uint32 mask =
					(borrow_bits << 1) - (borrow_bits >> 7);
				return (lhs + rhs - mask) & mask;
			}
		};

		/**
		 * 加算ファクタ
		 */
		class plus_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 rhs,
									   risa_gl::uint32 lhs) const
			{
				return rhs + lhs;
			}
		};
	}
}

#endif /* RISA_COMPUTE_FACTOR_HPP_ */
