#ifndef RISA_COMPUTE_FUNCTION_HPP_
#define RISA_COMPUTE_FUNCTION_HPP_

#include <risa_gl/risa_types.hpp>
#include <risa_gl/primitive/selector.hpp>
#include <cmath>
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
					(256 - (rhs & 0x000000ffU));

				const risa_gl::uint32 high =
					((lhs & 0x00ff0000U) >> 8) /
					(256 - ((rhs & 0x00ff0000U) >> 16));

				return
					(low > 0xff ? 0xff : low) |
					(high > 0xff ? 0x00ff0000 : (high << 16));
			}
		};

		/**
		 * 除算ファンクタ
		 * result = min(1, lhs / (1 - rhs * alpha));
		 */
		template <typename source_selector_type,
				  typename destination_selector_type>
		class version5_divide_saturation_function
		{
		private:
			source_selector_type src_select;
			destination_selector_type dest_select;

		public:
			/**
			 * min(1, dest / (1 - src))
			 */
			risa_gl::uint32 operator()(risa_gl::uint32 lhs_,
									   risa_gl::uint32 rhs_) const
			{
				assert((lhs_ & 0xff00ff00) == 0);
				assert((rhs_ & 0xff00ff00) == 0);

				const risa_gl::uint32 lhs = dest_select(lhs_, rhs_);
				const risa_gl::uint32 rhs = src_select(lhs_, rhs_);
				
				const risa_gl::uint32 low = 
					((lhs & 0x000000ffU) << 8) /
					(256 - (rhs & 0x000000ffU));

				const risa_gl::uint32 high =
					((lhs & 0x00ff0000U) >> 8) /
					(256 - ((rhs & 0x00ff0000U) >> 16));

				return
					(low > 0xff ? 0xff : low) |
					(high > 0xff ? 0x00ff0000 : (high << 16));
			}
		};

		/**
		 * 比較(大)ファンクタ
		 * result = max(lhs, rhs);
		 */
		class compare_greater_function
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				assert((lhs & 0xff00ff00) == 0);
				assert((rhs & 0xff00ff00) == 0);

				const risa_gl::uint32 lhs_high = lhs & 0x00ff0000;
				const risa_gl::uint32 lhs_low = lhs & 0x000000ff;
				const risa_gl::uint32 rhs_high = rhs & 0x00ff0000;
				const risa_gl::uint32 rhs_low = rhs & 0x000000ff;

				return
					(lhs_high > rhs_high ? lhs_high : rhs_high) |
					(lhs_low > rhs_low ? lhs_low : rhs_low);
			}
		};

		/**
		 * 比較(小)ファンクタ
		 * result = min(lhs, rhs);
		 */
		class compare_lesser_function
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				assert((lhs & 0xff00ff00) == 0);
				assert((rhs & 0xff00ff00) == 0);

				const risa_gl::uint32 lhs_high = lhs & 0x00ff0000;
				const risa_gl::uint32 lhs_low = lhs & 0x000000ff;
				const risa_gl::uint32 rhs_high = rhs & 0x00ff0000;
				const risa_gl::uint32 rhs_low = rhs & 0x000000ff;

				return
					(lhs_high < rhs_high ? lhs_high : rhs_high) |
					(lhs_low < rhs_low ? lhs_low : rhs_low);
			}
		};

		/**
		 * 
		 * result = 1 - (lhs * rhs);
		 */
		class invert_multiply_function
		{
		private:
			multiply_function multiplier;

		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				return 0x00ff00ff - multiplier(lhs, rhs);
			}
		};

		/**
		 * オーバーレイ、ハードライト用ブレンド関数
		 */
		template <typename lhs_selector_type,
				  typename rhs_selector_type>
		class overlay_function
		{
		private:
			lhs_selector_type lhs_selector;
			rhs_selector_type rhs_selector;

			risa_gl::uint8 compute_overlay(risa_gl::uint8 rhs,
										   risa_gl::uint8 lhs) const
			{
				if (rhs > 127)
					return 255 - ((((256 - rhs) * (256 - lhs)) * 2) / 256);
				else
					return (((rhs * lhs) * 2) / 256);
			}

		public:
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				risa_gl::uint8 lhs_high =
					static_cast<risa_gl::uint8>((lhs_selector(lhs, rhs) &
												 0x00ff0000) >> 16);
				risa_gl::uint8 lhs_low  = 
					static_cast<risa_gl::uint8>(lhs_selector(lhs, rhs) &
												0x000000ff);
				risa_gl::uint8 rhs_high =
					static_cast<risa_gl::uint8>((rhs_selector(lhs, rhs) &
												 0x00ff0000) >> 16);
				risa_gl::uint8 rhs_low =
					static_cast<risa_gl::uint8>(rhs_selector(lhs, rhs) &
												0x000000ff);

				return
					(compute_overlay(rhs_high, lhs_high) << 16) | 
					compute_overlay(rhs_low, lhs_low);
			}
		};

		/**
		 *
		 */
		class softlight_function
		{
		private:
			risa_gl::uint8 compute_softlight(risa_gl::uint8 src,
											 risa_gl::uint8 dest) const
			{
				if (src < 128)
					return static_cast<risa_gl::uint8>
						(255 * 
						 powf(dest / 255.0f,
							  (255 - src) / 128.0f));
				return static_cast<risa_gl::uint8>
					(255 *
					 powf(dest / 255.0f,
						  128.0f / src));
			}

		public:
			risa_gl::uint32 operator()(risa_gl::uint32 src,
									   risa_gl::uint32 dest) const
			{
				const risa_gl::uint8 src_high = (src & 0x00ff0000) >> 16;
				const risa_gl::uint8 src_low = src & 0x000000ff;
				const risa_gl::uint8 dest_high = (dest & 0x00ff0000) >> 16;
				const risa_gl::uint8 dest_low = dest & 0x000000ff;

				return
					(compute_softlight(src_high, dest_high) << 16) |
					compute_softlight(src_low, dest_low);
			}
		};

		template <typename source_selector_type,
				  typename destination_selector_type>
		class color_burn_function
		{
		private:
			typedef source_selector_type src_select_t;
			typedef destination_selector_type dest_select_t;

			src_select_t src_select;
			dest_select_t dest_select;

		public:
			color_burn_function(const src_select_t& src_ = src_select_t(),
								const dest_select_t& dest_ = dest_select_t()):
				src_select(src_), dest_select(dest_)
			{}


			/**
			 * dest / (1 - src)
			 */
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				const risa_gl::uint32 src = src_select(lhs, rhs);
				const risa_gl::uint32 dest = dest_select(lhs, rhs);

				const risa_gl::uint8 src_high = (src & 0x00ff0000) >> 16;
				const risa_gl::uint8 src_low = (src & 0x000000ff);
				const risa_gl::uint16 dest_high = (dest & 0x00ff0000) >> 8;
				const risa_gl::uint16 dest_low = (dest & 0x000000ff) << 8;

				const risa_gl::uint16 res_high = 
					((65535 - dest_high) / (src_high+1));
				const risa_gl::uint16 res_low = 
					((65535 - dest_low) / (src_low+1));
				
				return
					(res_high > 255 ? 0x00000000 : (255 - res_high) << 16) |
					(res_low > 255 ? 0x00000000 : (255 - res_low));
			}
		};

		class exclusion_function
		{
		public:
			/**
			 * r = lhs + rhs - 2 * lhs * rhs
			 */
			risa_gl::uint32 operator()(risa_gl::uint32 lhs,
									   risa_gl::uint32 rhs) const
			{
				const risa_gl::uint8 lhs_high = (lhs & 0x00ff0000) >> 16;
				const risa_gl::uint8 lhs_low = (lhs & 0x000000ff);
				const risa_gl::uint8 rhs_high = (rhs & 0x00ff0000) >> 16;
				const risa_gl::uint8 rhs_low = (rhs & 0x000000ff);

					
				return lhs + rhs -
					((((lhs_high * rhs_high) << 9) & 0x01fe0000) |
					 (((lhs_low * rhs_low) >>7) & 0x000001fe));
			}

		};
	}
}

#endif /* RISA_COMPUTE_FUNCTION_HPP_ */
