#ifndef RISA_COMPUTE_FUNCTION_HPP_
#define RISA_COMPUTE_FUNCTION_HPP_

#include <risa_types.hpp>
#include <operators/primitive/selector.hpp>
#include <cassert>

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * 飽和加算ファンクタ
		 */
		class add_saturation_function
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

		template <typename selector_type>
		class invert
		{
		private:
			selector_type selector;

		public:
			template <typename lhs_type,
					  typename rhs_type>
			risa_gl::uint32 operator()(lhs_type lhs,
									   rhs_type rhs) const
			{
				return 0x00ff00ff - selector(lhs, rhs);
			}
		};
		
		/**
		 * 飽和減算ファンクタ
		 */
		template <typename source_selector_type,
				  typename destination_selector_type>
		class subtract_saturation_function
		{
		private:
			source_selector_type src_select;
			destination_selector_type dest_select;

		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs_,
									   risa_gl::uint32 rhs_) const
			{
				assert((lhs_ & 0xff00ff00) == 0);
				assert((rhs_ & 0xff00ff00) == 0);

				const risa_gl::uint32 lhs = dest_select(lhs_, rhs_);
				const risa_gl::uint32 rhs = src_select(lhs_, rhs_);

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

		/**
		 * 除算ファンクタ
		 * result = lhs / rhs;
		 */
		template <typename source_selector_type,
				  typename destination_selector_type>
		class divide_saturation_function
		{
		private:
			source_selector_type src_select;
			destination_selector_type dest_select;

		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs_,
									   risa_gl::uint32 rhs_) const
			{
				assert((lhs_ & 0xff00ff00) == 0);
				assert((rhs_ & 0xff00ff00) == 0);

				const risa_gl::uint32 lhs = dest_select(lhs_, rhs_);
				const risa_gl::uint32 rhs = src_select(lhs_, rhs_);
				
				const risa_gl::uint32 low = 
					((lhs & 0x000000ffU) << 8) /
					((rhs & 0x000000ffU)+1);

				const risa_gl::uint32 high =
					((lhs & 0x00ff0000U) >> 8) /
					(((rhs & 0x00ff0000U) >> 16)+1);

				return
					(low > 0xff ? 0xff : low) |
					(high > 0xff ? 0x00ff0000 : (high << 16));
			}
		};
	}
}

#endif /* RISA_COMPUTE_FUNCTION_HPP_ */
