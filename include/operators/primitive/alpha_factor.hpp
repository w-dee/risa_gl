#ifndef RISA_ALPHA_FACTOR_HPP_
#define RISA_ALPHA_FACTOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	namespace primitive
	{
		class identity_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 256;
			}
		};

		class zero_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 0;
			}
		};

		template <typename selecter,
				  typename method_selecter>
		class alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return method_selecter()(selecter()(src, dest));
			}
		};

		template <typename selecter,
				  typename method_selecter>
		class one_minus_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 256 - method_selecter()(selecter()(src, dest));
			}
		};
	};
};

#endif /* RISA_ALPHA_FACTOR_HPP_ */

