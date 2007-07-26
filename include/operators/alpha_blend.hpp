#ifndef RISA_ALPHA_BLEND_HPP_
#define RISA_ALPHA_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * アルファブレンディング
		 * alphaは破壊される
		 */
		class alpha_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				nop_factor,
				source_alpha_getter,
				invert_source_alpha_getter,
				not_calculate_policy>
			alpha_blend_opeartor_type;

			alpha_blend_opeartor_type blender;
		public:

			/**
			 * src.color * src.a + dest.color * (1-src.a)
			 */
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

		/**
		 * アルファブレンディング
		 * r.color = src.color * src.a + dest.color * (1 - src.a)
		 * r.a = src.a * src.a + dest.a * (1 - src.a)
		 */
		class alpha_blend_save_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				nop_factor,
				source_alpha_getter,
				invert_source_alpha_getter,
				multiply_alpha_and_alpha_policy<
				source_getter,
				source_alpha_getter,
				destination_getter,
				destination_alpha_getter> >
			alpha_blend_save_alpha_opeartor_type;

			alpha_blend_save_alpha_opeartor_type blender;
		public:

			/**
			 * src.color * src.a + dest.color * (1-src.a)
			 */
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

	};
};

#endif /* RISA_ALPHA_BLEND_HPP_ */
