#ifndef RISA_PIXEL_GETTER_HPP_
#define RISA_PIXEL_GETTER_HPP_
#include "risa_types.hpp"
#include "selecter.hpp"

namespace risa_gl
{
	namespace primitive
	{
		class nop_setter
		{
		public:
			template <typename result_itor_t>
			void operator()(result_itor_t, risa_gl::uint32) const
			{
			}
		};

		template <risa_gl::uint32 value>
		class constant_setter
		{
		public:
			template <typename result_itor_t>
			void operator()(result_itor_t result, risa_gl::uint32) const
			{
				result->set_bit_representation(value);
			}
		};

		class bit_setter
		{
		public:
			template <typename result_itor_t>
			void operator()(result_itor_t result,
							risa_gl::uint32 value) const
			{
				result->set_bit_representation(value);
			}
		};

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

		template <risa_gl::uint32 pixel_bits>
		class constant_getter
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t, dest_itor_t) const
			{
				return pixel_bits;
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
};

#endif /* RISA_PIXEL_GETTER_HPP_ */
