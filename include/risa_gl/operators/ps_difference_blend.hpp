#ifndef RISA_PS_DIFFERENCE_BLEND_HPP_
#define RISA_PS_DIFFERENCE_BLEND_HPP_

#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/primitive/alpha_factor.hpp>
#include <risa_gl/primitive/alpha_policy.hpp>
#include <risa_gl/operators/building_blocks.hpp>
#include <risa_gl/operators/alpha_blend.hpp>
#include <risa_gl/operators/lighten_blend.hpp>
#include <risa_gl/operators/darken_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		class difference_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				subtract_saturation_function<
						compare_lesser_function,
						compare_greater_function>,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			difference_blend_operator_type;
			difference_blend_operator_type blender;

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

		class difference_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				subtract_saturation_function<
						compare_lesser_function,
						compare_greater_function>,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
				difference_blend_save_source_alpha_operator_type;
			difference_blend_save_source_alpha_operator_type blender;

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

		class difference_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				subtract_saturation_function<
						compare_lesser_function,
						compare_greater_function>,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			difference_blend_save_destination_alpha_operator_type;
			difference_blend_save_destination_alpha_operator_type blender;

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

		/**
		 * PS互換差の絶対値ブレンディング(alphaは破壊)
		 */
		// {{{ ps_difference_blend_operator
		class ps_difference_blend_operator
		{
		private:
			typedef photoshop_blend<
				difference_blend_save_source_alpha_operator,
				alpha_blend_operator>
			ps_difference_blend_operator_type;
			ps_difference_blend_operator_type blender;
		public:
			ps_difference_blend_operator():
				blender()
			{}

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

		/**
		 * PS互換差の絶対値ブレンディング(alphaはdestinationを保存)
		 */
		// {{{ ps_difference_blend_save_destination_alpha_operator
		class ps_difference_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				difference_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_difference_blend_operator_type;
			ps_difference_blend_operator_type blender;
		public:
			ps_difference_blend_save_destination_alpha_operator():
				blender()
			{}

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

		class ps5_difference_blend_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				subtract_saturation_function<
						compare_lesser_function,
						compare_greater_function>,
				source_alpha_getter,
				identity_alpha_factor,
				not_calculate_policy>
			ps5_difference_blend_operator_type;
			ps5_difference_blend_operator_type blender;

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

		class ps5_difference_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				subtract_saturation_function<
						compare_lesser_function,
						compare_greater_function>,
				source_alpha_getter,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
				ps5_difference_blend_save_source_alpha_operator_type;
			ps5_difference_blend_save_source_alpha_operator_type blender;

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

		class ps5_difference_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				subtract_saturation_function<
						compare_lesser_function,
						compare_greater_function>,
				source_alpha_getter,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			ps5_difference_blend_save_destination_alpha_operator_type;
			ps5_difference_blend_save_destination_alpha_operator_type blender;

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
	}
}

#endif /* RISA_PS_DIFFERENCE_BLEND_HPP_ */
