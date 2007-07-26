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
		 * 
		 * r.color = src.color * src.a + dest.color * (1-src.a)
		 * r.a = ?
		 */
		// {{{ alpha_blend_operator		class alpha_blend_operator		{		private:			typedef primitive::binomial_blend<				source_getter,				destination_getter,				bit_setter,				nop_factor,				source_alpha_getter,				invert_source_alpha_getter,				not_calculate_policy>			alpha_blend_opeartor_type;			alpha_blend_opeartor_type blender;		public:			template <typename src_itor_t,					  typename dest_itor_t,					  typename result_itor_t>			void operator()(src_itor_t src,							dest_itor_t dest,							result_itor_t result) const			{				blender(src, dest, result);			}		};		// }}}

		/**
		 * アルファブレンディング
		 * destination alphaが保存される
		 * 
		 * r.color = src.color * src.a + dest.color * (1-src.a)
		 * r.a = dest.a
		 */
		// {{{ alpha_blend_save_destination_alpha_operator		class alpha_blend_save_destination_alpha_operator		{		private:			typedef primitive::binomial_blend<				source_getter,				destination_getter,				bit_setter,				nop_factor,				source_alpha_getter,				invert_source_alpha_getter,				alpha_calculate_policy<destination_alpha_getter> >			alpha_blend_save_destination_alpha_opeartor_type;			alpha_blend_save_destination_alpha_opeartor_type blender;		public:			template <typename src_itor_t,					  typename dest_itor_t,					  typename result_itor_t>			void operator()(src_itor_t src,							dest_itor_t dest,							result_itor_t result) const			{				blender(src, dest, result);			}		};		// }}}

		/**
		 * アルファブレンディング
		 * r.color = src.color * src.a + dest.color * (1 - src.a)
		 * r.a = src.a * src.a + dest.a * (1 - src.a)
		 */
		// {{{ alpha_blend_calculate_alpha_operator		class alpha_blend_calculate_alpha_operator		{		private:			typedef primitive::binomial_blend<				source_getter,				destination_getter,				bit_setter,				nop_factor,				source_alpha_getter,				invert_source_alpha_getter,				multiply_alpha_and_alpha_policy<				source_alpha_getter,				destination_alpha_getter> >			alpha_blend_calculate_alpha_opeartor_type;			alpha_blend_calculate_alpha_opeartor_type blender;		public:			template <typename src_itor_t,					  typename dest_itor_t,					  typename result_itor_t>			void operator()(src_itor_t src,							dest_itor_t dest,							result_itor_t result) const			{				blender(src, dest, result);			}		};		// }}}

		/**
		 * アルファブレンディング
		 * destinationをalpha加算用としてブレンド
		 * r.color = sat(src.color * src.a + dest.color * dest.a * (1 - src.a))
		 * r.a = src.a * src.a + dest.a * (1 - src.a)
		 */
		// {{{ alpha_blend_additive_calculate_alpha_operator
		class alpha_blend_additive_calculate_alpha_operator
		{
		private:
			typedef primitive::binomial_blend<
				source_getter,
				destination_getter,
				bit_setter,
				nop_factor,
				source_alpha_getter,
				multiply_invert_source_alpha_and_destination_alpha_getter,
				multiply_alpha_and_alpha_policy<
				source_alpha_getter,
				destination_alpha_getter> >
			alpha_blend_additive_calculate_alpha_opeartor_type;

			alpha_blend_additive_calculate_alpha_opeartor_type blender;
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

	};
};

#endif /* RISA_ALPHA_BLEND_HPP_ */
