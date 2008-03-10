#ifndef RISA_TO_GRAYSCALE_HPP_
#define RISA_TO_GRAYSCALE_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 
		 */
		// {{{ to_grayscale_operator
		class to_grayscale_operator
		{
		private:
			struct to_grayscale
			{
			public:
				template <typename pixel_t>
				risa_gl::uint32 operator()(pixel_t pix) const
				{
					const risa_gl::byte brightness =
						static_cast<risa_gl::byte>(
							0.298912 * pix.get_red() +
							0.586611 * pix.get_green() +
							0.114478 * pix.get_blue());
					return pixel_t(brightness,
								   brightness,
								   brightness,
								   pix.get_alpha()).get_bit_representation();
				}
			};

			typedef primitive::monomial_function<
				functional_getter<to_grayscale, source_getter>,
				zero_getter,
				bit_setter,
				plus_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			to_grayscale_operator_type;

			to_grayscale_operator_type blender;
		public:
			to_grayscale_operator():
				blender()
			{}

			template <typename src_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							result_itor_t result) const
			{
				blender(src, result);
			}
		};
		// }}}

	}
}

#endif /* RISA_TO_GRAYSCALE_HPP_ */
