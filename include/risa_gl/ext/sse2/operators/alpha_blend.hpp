#ifndef RISA_EXT_SSE2_OPERATORS_ALPHA_BLEND_HPP_
#define RISA_EXT_SSE2_OPERATORS_ALPHA_BLEND_HPP_

#include <risa_gl/ext/sse2/primitive/blend.hpp>
#include <risa_gl/ext/sse2/primitive/alpha_policy.hpp>
#include <risa_gl/ext/sse2/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace operators
			{
				namespace primitive = risa_gl::ext::sse2::primitive;
				/**
				 * アルファブレンディング
				 * alphaは破壊される
				 * 
				 * r.color = src.color * src.a + dest.color * (1-src.a)
				 * r.a = ?
				 */
				// {{{ alpha_blend_operator
				template <typename pixel_type>
				class alpha_blend_operator
				{
				private:
					typedef primitive::binomial_blend<
					source_getter,
					destination_getter,
					primitive::bit_setter,
					primitive::vertical_multiply,
					plus_function,
					source_alpha_getter<pixel_type>,
					invert_source_alpha_getter<pixel_type>,
					primitive::odd_and_even_mixer,
					primitive::not_calculate_policy,
					primitive::word_base_divisor<8> >
					alpha_blend_operator_type;

					alpha_blend_operator_type blender;
				public:

					template <typename src_itor_t,
							  typename dest_itor_t,
							  typename result_itor_t>
					void operator()(src_itor_t src,
									dest_itor_t dest,
									result_itor_t result) const
					{
						blender(src, dest, result);
					}
				};
				// }}}
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_OPERATORS_ALPHA_BLEND_HPP_ */
