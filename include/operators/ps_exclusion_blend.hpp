#ifndef RISA_PS_EXCLUSION_BLEND_HPP_
#define RISA_PS_EXCLUSION_BLEND_HPP_

#include <operators/primitive/blend.hpp>
#include <operators/primitive/alpha_factor.hpp>
#include <operators/building_blocks.hpp>
#include <operators/alpha_blend.hpp>

namespace risa_gl
{
	namespace operators
	{
		class exclusion_blend
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				exclusion_function,
				identity_alpha_factor,
				identity_alpha_factor,
				not_calculate_policy>
			exclusion_blend_operator_type;

			exclusion_blend_operator_type blender;
			
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

		class exclusion_blend_save_source_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				exclusion_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<source_alpha_getter> >
			exclusion_blend_save_source_operator_type;

			exclusion_blend_save_source_operator_type blender;
			
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

		class exclusion_blend_save_destination_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				exclusion_function,
				identity_alpha_factor,
				identity_alpha_factor,
				alpha_calculate_policy<destination_alpha_getter> >
			exclusion_blend_save_destination_operator_type;

			exclusion_blend_save_destination_operator_type blender;
			
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

		// {{{ ps_exclusion_blend_operator
		class ps_exclusion_blend_operator
		{
		private:
			typedef photoshop_blend<
				exclusion_blend_save_source_alpha_operator,
				alpha_blend_operator>
			ps_exclusion_blend_operator_type;
			ps_exclusion_blend_operator_type blender;
		public:
			ps_exclusion_blend_operator():
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

		// {{{ ps_exclusion_blend_save_destination_alpha_operator
		class ps_exclusion_blend_save_destination_alpha_operator
		{
		private:
			typedef photoshop_blend<
				exclusion_blend_save_source_alpha_operator,
				alpha_blend_save_destination_alpha_operator>
			ps_exclusion_blend_operator_type;
			ps_exclusion_blend_operator_type blender;
		public:
			ps_exclusion_blend_save_destination_alpha_operator():
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
	}
}

#endif /* RISA_PS_EXCLUSION_BLEND_HPP_ */
