#ifndef RISA_PIXEL_GETTER_HPP_
#define RISA_PIXEL_GETTER_HPP_
#include "risa_types.hpp"
#include "selecter.hpp"

namespace risa_gl
{
	namespace primitive
	{
		class null_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t, dest_itor_t) const
			{
				return 0;
			}
		};

		template <typename selecter>
		class bits_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return selecter()(src, dest)->get_bits_representation();
			}
	};
};

#endif /* RISA_PIXEL_GETTER_HPP_ */
