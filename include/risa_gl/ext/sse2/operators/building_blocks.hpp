#ifndef RISA_EXT_SSE2_OPERATORS_BUILDING_BLOCKS_HPP_
#define RISA_EXT_SSE2_OPERATORS_BUILDING_BLOCKS_HPP_

#include <risa_gl/ext/sse2/risa_types.hpp>
#include <risa_gl/ext/sse2/primitive/functional.hpp>
#include <risa_gl/ext/sse2/primitive/alpha_factor.hpp>
#include <risa_gl/ext/sse2/primitive/pixel_property.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace operators
			{
				namespace primitive = risa_gl::ext::sse2::primitive;

				struct source_selector
				{
					template <typename src_itor_t,
							  typename dest_itor_t>
					src_itor_t operator()(src_itor_t src, dest_itor_t) const
					{
						return src;
					}
				};

				struct destination_selector
				{
					template <typename src_itor_t,
							  typename dest_itor_t>
					dest_itor_t operator()(src_itor_t, dest_itor_t dest) const
					{
						return dest;
					}
				};

				typedef primitive::bits_getter<source_selector>
				source_getter;

				typedef primitive::bits_getter<destination_selector> 
				destination_getter;

				typedef primitive::vertical_add plus_function;

				template <typename pixel_type>
				struct source_alpha_getter :
					primitive::alpha_getter<
					source_selector,
					primitive::alpha_bits_get_method<pixel_type> > 
				{};

				template <typename pixel_type>
				struct invert_source_alpha_getter :
					primitive::invert_alpha_getter<
					source_selector,
					primitive::alpha_bits_get_method<pixel_type> > 
				{};

				template <typename pixel_type>
				struct destination_alpha_getter :
					primitive::alpha_getter<
					destination_selector,
					primitive::alpha_bits_get_method<pixel_type> > 
				{};

				template <typename pixel_type>
				struct invert_destination_alpha_getter :
					primitive::invert_alpha_getter<
					destination_selector,
					primitive::alpha_bits_get_method<pixel_type> > 
				{};

			}
		}
	}
}

#endif /* RISA_EXT_SSE2_OPERATORS_BUILDING_BLOCKS_HPP_ */

