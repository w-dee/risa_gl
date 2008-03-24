#ifndef RISA_EXT_SSE2_PRIMITIVE_BLEND_HPP_
#define RISA_EXT_SSE2_PRIMITIVE_BLEND_HPP_
#include <risa_gl/iterator.hpp>
#include <risa_gl/risa_types.hpp>

namespace risa_gl
{
	namespace ext
	{
		namespace sse2
		{
			namespace primitive
			{
				struct odd_mask
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& source) const
					{
						// source & 0x00ff00ff00ff00ff00ff00ff00ff00ff
						const aligned_wideword_type mask =
							_mm_set1_epi16(0x00ff);
						return _mm_and_si128(source, mask);
					}
				};

				struct even_mask
				{
					aligned_wideword_type operator()(
						const aligned_wideword_type& source) const
					{
						// source & 0xff00ff00ff00ff00ff00ff00ff00ff00
						const aligned_wideword_type mask =
							_mm_set1_epi16(0xff00);
						return _mm_and_si128(source, mask);
					}
				};

				// {{{ trinomial_blend(三項演算)
				// }}}

				// {{{  binomial_blend (二項演算)
				template <typename src_pixel_getter_t,
						  typename dest_pixel_getter_t,
						  typename result_pixel_setter_t,
						  typename compute_factor_t,
						  typename src_alpha_factor_t,
						  typename dest_alpha_factor_t,
						  typename mixer_t,
						  typename alpha_calculate_policy_t,
						  typename divisor_factor_t>
				class binomial_blend
				{
				private:
					/*
					 * 実行時にパラメタを与えられるように各種メソッドをメンバ
					 * として保持。利用されない場合はインライン化と最適化で消
					 * えるはず
					 */
					src_pixel_getter_t src_pixel_getter;
					dest_pixel_getter_t dest_pixel_getter;
					result_pixel_setter_t result_pixel_setter;
					compute_factor_t compute_factor;
					src_alpha_factor_t src_alpha_factor;
					dest_alpha_factor_t dest_alpha_factor;
					mixer_t mixer;
					alpha_calculate_policy_t alpha_calculate_policy;
					divisor_factor_t divisor_factor;

				public:
					typedef src_pixel_getter_t src_getter_type;
					typedef dest_pixel_getter_t dest_getter_type;
					typedef result_pixel_setter_t result_setter_type;
					typedef compute_factor_t compute_type;
					typedef src_alpha_factor_t source_alpha_type;
					typedef dest_alpha_factor_t destination_alpha_type;
					typedef mixer_t mixer_type;
					typedef alpha_calculate_policy_t alpha_policy_type;
					typedef divisor_factor_t divisor_type;

					binomial_blend(const binomial_blend& source):
						src_pixel_getter(source.src_pixel_getter),
						dest_pixel_getter(source.dest_pixel_getter),
						result_pixel_setter(source.result_pixel_setter),
						compute_factor(source.compute_factor),
						src_alpha_factor(source.src_alpha_factor),
						dest_alpha_factor(source.dest_alpha_factor),
						alpha_calculate_policy(source.alpha_calculate_policy),
						divisor_factor(source.divisor_factor)
					{}
				
					binomial_blend(src_pixel_getter_t src_pixel_getter_ =
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
								   alpha_calculate_policy_t
								   alpha_calculate_policy_ =
								   alpha_calculate_policy_t(),
								   divisor_factor_t divisor_factor_ =
								   divisor_factor_t()):
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

						const aligned_wideword_type
							src_pixel =	src_pixel_getter(src, dest);
						const aligned_wideword_type
							dest_pixel = dest_pixel_getter(src, dest);


						/**
						 * result = src (*) src_factor (+) dest (*) dest_factor;
						 *        = comp_func(op(src(), src_factor()),
						 *                    op(dest(), dest_factor()));
						 *
						 *          op() == operator(*);
						 *          comp_func() == operator(+);
						 */
						aligned_wideword_type res_pixel =
							odd_shifter(
								compute_factor(
									divisor_factor(
										multiplier(
											odd_mask(src_pixel),
											src_alpha_factor(src, dest))),
									divisor_factor(
										multiplier(
											odd_mask(dest_pixel),
											dest_alpha_factor(src, dest)))));
						const aligned_wideword_type res_pixel2 =
							even_shifter(
								compute_factor(
									divisor_factor(
										multiplier(
											even_mask(src_pixel),
											src_alpha_factor(src, dest))),
									divisor_factor(
										multiplier(
											even_mask(dest_pixel),
											dest_alpha_factor(src, dest)))));

						res_pixel = mixer(res_pixel, res_pixel2);
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
				// }}}

				// {{{ stripped_predicate(無項演算)
				// }}}
			}
		}
	}
}

#endif /* RISA_EXT_SSE2_PRIMITIVE_BLEND_HPP_ */
