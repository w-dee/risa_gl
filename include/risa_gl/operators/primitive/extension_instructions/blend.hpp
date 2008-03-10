#ifndef RISA_PRIMITIVE_EXTENSION_INSTRUCTION_BLEND_HPP_
#define RISA_PRIMITIVE_EXTENSION_INSTRUCTION_BLEND_HPP_
#include <risa_gl/iterator.hpp>
#include <risa_gl/risa_types.hpp>

namespace risa_gl
{
	namespace primitive
	{
		// {{{ trinomial_blend(三項演算)
		// }}}

		// {{{  binomial_blend (二項演算)
		template <typename instruction_set_t,
				  typename src_pixel_getter_t,
				  typename dest_pixel_getter_t,
				  typename result_pixel_setter_t,
				  typename compute_factor_t,
				  typename src_alpha_factor_t,
				  typename dest_alpha_factor_t,
				  typename alpha_calculate_policy_t,
				  typename divisor_factor_t = divide_factor<256> >
		class binomial_blend
		{
		private:
			/*
			 * 実行時にパラメタを与えられるように各種メソッドをメンバ
			 * として保持。利用されない場合はインライン化と最適化で消
			 * えるはず
			 */
			instruction_set_t instruction_set;
			src_pixel_getter_t src_pixel_getter;
			dest_pixel_getter_t dest_pixel_getter;
			result_pixel_setter_t result_pixel_setter;
			compute_factor_t compute_factor;
			src_alpha_factor_t src_alpha_factor;
			dest_alpha_factor_t dest_alpha_factor;
			alpha_calculate_policy_t alpha_calculate_policy;
			divisor_factor_t divisor_factor;

		public:
			typedef instruction_set_t instruction_set_type;
			typedef src_pixel_getter_t src_getter_type;
			typedef dest_pixel_getter_t dest_getter_type;
			typedef result_pixel_setter_t result_setter_type;
			typedef compute_factor_t compute_type;
			typedef src_alpha_factor_t source_alpha_type;
			typedef dest_alpha_factor_t destination_alpha_type;
			typedef alpha_calculate_policy_t alpha_policy_type;
			typedef divisor_factor_t divisor_type;

			binomial_blend(const binomial_blend& source):
				instruction_set(source.instruction_set),
				src_pixel_getter(source.src_pixel_getter),
				dest_pixel_getter(source.dest_pixel_getter),
				result_pixel_setter(source.result_pixel_setter),
				compute_factor(source.compute_factor),
				src_alpha_factor(source.src_alpha_factor),
				dest_alpha_factor(source.dest_alpha_factor),
				alpha_calculate_policy(source.alpha_calculate_policy),
				divisor_factor(source.divisor_factor)
			{}
				
			binomial_blend(instruction_set_t instruction_set_ =
						   instruction_set_t(),
						   src_pixel_getter_t src_pixel_getter_ =
						   src_pixel_getter_t(),
						   dest_pixel_getter_t dest_pixel_getter_ =
						   dest_pixel_getter_t(),
						   result_pixel_setter_t result_pixel_setter_ =
						   result_pixel_setter_t(),
						   compute_factor_t compute_factor_ =
						   compute_factor_t(),
						   src_alpha_factor_t src_alpha_factor_ =
						   src_alpha_factor_t(),
						   dest_alpha_factor_t dest_alpha_factor_ =
						   dest_alpha_factor_t(),
						   alpha_calculate_policy_t alpha_calculate_policy_ =
						   alpha_calculate_policy_t(),
						   divisor_factor_t divisor_factor_ =
						   divisor_factor_t()):
				instruction_set(instruction_set_),
				src_pixel_getter(src_pixel_getter_),
				dest_pixel_getter(dest_pixel_getter_),
				result_pixel_setter(result_pixel_setter_),
				compute_factor(compute_factor_),
				src_alpha_factor(src_alpha_factor_),
				dest_alpha_factor(dest_alpha_factor_),
				alpha_calculate_policy(alpha_calculate_policy_),
				divisor_factor(divisor_factor_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{

				const instruction_set_type::word_type
					src_pixel =	src_pixel_getter(src, dest);
				const instruction_set_type::word_type
					dest_pixel = dest_pixel_getter(src, dest);

				risa_gl::uint32 res_pixel =
					compute_factor(
						divisor_factor(src_pixel *
										src_alpha_factor(src, dest)),
						divisor_factor(dest_pixel *
										dest_alpha_factor(src, dest)));

				// アルファ値の計算
				// 結果セット
				result_pixel_setter(result, 
									alpha_calculate_policy(
										res_pixel,
										result,
										src,
										dest));
			}
		};
		// }}}

		// {{{ monomial_function(単項演算)
		template <typename src_pixel_getter_t,
				  typename constant_pixel_getter_t,
				  typename result_pixel_setter_t,
				  typename compute_factor_t,
				  typename src_alpha_factor_t,
				  typename constant_alpha_factor_t,
				  typename alpha_calculate_policy_t,
				  typename divisor_factor_t = divide_factor<256> >
		class monomial_function
		{
		private:
			/*
			 * 実行時にパラメタを与えられるように各種メソッドをメンバ
			 * として保持。利用されない場合はインライン化と最適化で消
			 * えるはず
			 */
			src_pixel_getter_t src_pixel_getter;
			constant_pixel_getter_t constant_pixel_getter;
			result_pixel_setter_t result_pixel_setter;
			compute_factor_t compute_factor;
			src_alpha_factor_t src_alpha_factor;
			constant_alpha_factor_t constant_alpha_factor;
			alpha_calculate_policy_t alpha_calculate_policy;
			divisor_factor_t divisor_factor;

		public:
			typedef src_pixel_getter_t src_getter_type;
			typedef constant_pixel_getter_t constant_getter_type;
			typedef result_pixel_setter_t result_setter_type;
			typedef compute_factor_t compute_type;
			typedef src_alpha_factor_t source_alpha_type;
			typedef constant_alpha_factor_t constant_alpha_type;
			typedef alpha_calculate_policy_t alpha_policy_type;
			typedef divisor_factor_t divisor_type;

			monomial_function(const monomial_function& source):
				src_pixel_getter(source.src_pixel_getter),
				constant_pixel_getter(source.constant_pixel_getter),
				result_pixel_setter(source.result_pixel_setter),
				compute_factor(source.compute_factor),
				src_alpha_factor(source.src_alpha_factor),
				constant_alpha_factor(source.constant_alpha_factor),
				alpha_calculate_policy(source.alpha_calculate_policy),
				divisor_factor(source.divisor_factor)
			{}
				
			monomial_function(src_pixel_getter_t src_pixel_getter_ =
							  src_pixel_getter_t(),
							  constant_pixel_getter_t constant_pixel_getter_ =
							  constant_pixel_getter_t(),
							  result_pixel_setter_t result_pixel_setter_ =
							  result_pixel_setter_t(),
							  compute_factor_t compute_factor_ =
							  compute_factor_t(),
							  src_alpha_factor_t src_alpha_factor_ =
							  src_alpha_factor_t(),
							  constant_alpha_factor_t constant_alpha_factor_ =
							  constant_alpha_factor_t(),
							  alpha_calculate_policy_t alpha_calculate_policy_ =
							  alpha_calculate_policy_t(),
							  divisor_factor_t divisor_factor_ =
							  divisor_factor_t()):
				src_pixel_getter(src_pixel_getter_),
				constant_pixel_getter(constant_pixel_getter_),
				result_pixel_setter(result_pixel_setter_),
				compute_factor(compute_factor_),
				src_alpha_factor(src_alpha_factor_),
				constant_alpha_factor(constant_alpha_factor_),
				alpha_calculate_policy(alpha_calculate_policy_),
				divisor_factor(divisor_factor_)
			{}

			template <typename src_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							result_itor_t result) const
			{
				risa_gl::uint32 src_pixel = src_pixel_getter(src, result);
				risa_gl::uint32 const_pixel = constant_pixel_getter(src, result);

				risa_gl::uint32 res_pixel =
					compute_factor(
						divisor_factor((lower_mask()(src_pixel) *
										src_alpha_factor(src, result))) &
						0x00ff00ff,
						divisor_factor((lower_mask()(const_pixel) *
										constant_alpha_factor(src, result))) &
									   0x00ff00ff);
				assert((res_pixel | 0x00ff00ff) == 0x00ff00ff);

				const risa_gl::uint32 res_pixel2 =
					(compute_factor(
						divisor_factor(((higher_mask()(src_pixel)>>8) *
										src_alpha_factor(src, result))) &
									   0x00ff00ff,
						divisor_factor(((higher_mask()(const_pixel)>>8) *
										constant_alpha_factor(src, result))) &
									   0x00ff00ff) << 8);

				assert((res_pixel2 | 0xff00ff00) == 0xff00ff00);

				res_pixel |= res_pixel2;

				// アルファ値の計算
				// 結果セット
				result_pixel_setter(result, 
									alpha_calculate_policy(
										res_pixel,
										result,
										src,
										0));
			}
		};
		// }}}

		// {{{ stripped_predicate(無項演算)
		// }}}
	}
}

#endif /* RISA_PRIMITIVE_EXTENSION_INSTRUCTION_BLEND_HPP_ */
