#ifndef RISA_WITH_OPACITY_HPP_
#define RISA_WITH_OPACITY_HPP_
#include <operators/primitive/blend.hpp>
#include <operators/building_blocks.hpp>

namespace risa_gl
{
	namespace operators
	{
		/**
		 * 各種blend関数にopacityつきバージョンの関数を生成する
		 * 
		 * result = blend(src, dest) * opacity + dest * (1 - opacity)
		 */
		// {{{ with_opacity
		template <typename base_operator_type>
		class with_opacity
		{
		private:
			/**
			 * 合成対象のオペレータ
			 */
			const base_operator_type base_operator;

			class apply_opacity_operator_type
			{
			private:
				typedef base_operator_type base_type;

				typedef risa_gl::primitive::binomial_blend<
					source_getter,
					destination_getter,
					bit_setter,
					nop_factor,
					dynamic_constant_getter,
					dynamic_constant_getter,
					not_calculate_policy>
				blender_type;

				blender_type blender;

			public:
				apply_opacity_operator_type(const int opacity):
					blender(
						source_getter(),
						destination_getter(),
						bit_setter(),
						nop_factor(),
						dynamic_constant_getter(opacity),
						dynamic_constant_getter(257 - opacity))
				{}

				apply_opacity_operator_type(
					const apply_opacity_operator_type& source):
					blender(source.blender)
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
			} apply_opacity_operator;

			const int opacity;
		public:
			with_opacity(const base_operator_type base_operator_ =
						 base_operator_type()):
				base_operator(base_operator_),
				apply_opacity_operator(),
				opacity(256)
			{}

			with_opacity(const with_opacity& source):
				base_operator(source.base_operator),
				apply_opacity_operator(source.apply_opacity_operator),
				opacity(source.opacity)
			{}

			with_opacity(const int opacity_,
						 const base_operator_type base_operator_ =
						 base_operator_type()):
				base_operator(base_operator_),
				apply_opacity_operator(opacity),
				opacity(opacity_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				// result = f(src, dest) * opacity + src * (1 - opacity)
				base_operator(src, dest, result);
				apply_opacity_operator(result, dest, result);
				typedef typename base_operator_type::alpha_policy_type
					policy_type;
				policy_type()(result, src, dest);
			}
		};
		// }}}
	}
}

#endif /* RISA_WITH_OPACITY_HPP_ */
