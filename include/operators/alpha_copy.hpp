#ifndef RISA_ALPHA_COPY_HPP_
#define RISA_ALPHA_COPY_HPP_

#include <risa_gl/operators/primitive/blend.hpp>
#include <risa_gl/operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		class alpha_copy_operator
		{
		private:
			typedef primitive::binomial_blend<
				zero_getter,
				destination_getter,
				bit_setter,
				plus_function,
				zero_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<
				source_alpha_getter> >
			alpha_copy_opeartor_type;

			alpha_copy_opeartor_type blender;
		public:

			/**
			 * srcのもつalpha値をdestのcolor要素とマージしてresultにセットする
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

		class opacity_copy_operator
		{
		private:
			typedef primitive::binomial_blend<
				zero_getter,
				destination_getter,
				bit_setter,
				plus_function,
				zero_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<
				source_opacity_getter> >
			alpha_copy_opeartor_type;

			alpha_copy_opeartor_type blender;
		public:

			/**
			 * srcのもつopacity値をdestのcolor要素とマージしてresultにセットする
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
	}
}

#endif /* RISA_ALPHA_COPY_HPP_ */
