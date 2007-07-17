#ifndef RISA_PRIMITIVE_HPP_
#define RISA_PRIMITIVE_HPP_
#include "iterator.hpp"
#include "risa_types.hpp"
#include "saturation.hpp"
#include "selecter.hpp"
#include "factor.hpp"

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * ブレンドテンプレート
		 */

		/**
		 * 混合テンプレート
		 *
		 * @param alpha_policy
		 *  nopかresultのalpha演算
		 *  
		 * @param compute_factor
		 *  saturationや定数項
		 *  
		 * @param src_alpha_factor
		 *  src color演算時に適用するalpha値演算
		 * 
		 * @param dest_alpha_factor
		 *  dest color演算時に適用するalpha値演算
		 *  
		 */
		template <typename alpha_policy,
				  typename compute_factor,
				  typename src_alpha_factor,
				  typename dest_alpha_factor>
		class alpha_blend
		{
		public:
			/**
			 * Porter-Diff color composite
			 * Cr = f(Cs*Fs + Cd*Fd)
			 * Ar = f(As*Fs + Ad*Fd)
			 *
			 * Cd演算はbit_representation()からのパック演算で処理
			 * 各種演算の違いはfactorで埋め合わせ
			 * f(): saturation, 定数置換
			 * Cs: source color
			 * Cd: destination color
			 * Cr: result color
			 * As: source alpha
			 * Ad: destination alpha
			 * Ar: result alpha
			 *
			 *
			 */

			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{

				const risa_gl::uint32 src_pixel =
					src->get_bit_representaion();
				const risa_gl::uint32 dest_pixel =
					dest->get_bit_representaion();

				// pixelのパック演算
				risa_gl::uint32 res_pixel =
					compute_factor()((((src_pixel & 0x00ff00ff) *
									   src_alpha_factor()(src, dest)) >> 8) +
									 (((dest_pixel & 0x00ff00ff) *
									   dest_alpha_factor()(src, dest)) >> 8)) |
					compute_factor()(((((dest_pixel & 0xff00ff00) >> 8) *
									   dest_alpha_factor()(src, dest)) >> 8) +
									 ((((src_pixel & 0xff00ff00) >> 8) *
									   src_alpha_factor()(src, dest)) >> 8))
																	  << 8;

				// 結果セット
				result->set_bit_representation(res_pixel);

				// alpha値をpolicyに従いセット
				policy

			}
		};

		/**
		 * 混合テンプレート(サチュレーションあり)
		 */
		template <typename source_factor,
				  typename source_alpha_factor,
				  typename destination_factor,
				  typename destination_alpha_factor>
		class saturation_blend
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				result->set_red(
					saturate()((src->get_red() *
								source_factor()(src, dest) +
								dest->get_red() *
								destination_factor()(src, dest)) >> 8));
				result->set_green(
					saturate()((src->get_green() *
								source_factor()(src, dest) +
								dest->get_green() *
								destination_factor()(src, dest)) >> 8));
				result->set_blue(
					saturate()((src->get_blue() *
								source_factor()(src, dest) +
								dest->get_blue() *
								destination_factor()(src, dest)) >> 8));
				result->set_alpha(
					saturate()((src->get_alpha() *
								source_alpha_factor()(src, dest) +
								dest->get_alpha() *
								destination_alpha_factor()(src, dest)) >> 8));
			}
		};

		/**
		 * 別アルファチャネル混合テンプレート
		 */
		template <typename alpha_extract_factor>
		class alternate_alpha_channel_blend
		{
		public:
			template <typename src_itor_t,
					  typename alpha_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							alpha_itor_t alpha,
							result_itor_t result) const
			{
				const int alpha_value = alpha_extract_factor()(src, alpha);
				result->set_red((src->get_red() * alpha_value) >> 8);
				result->set_green((src->get_green() * alpha_value) >> 8);
				result->set_blue((src->get_blue() * alpha_value) >> 8);
				result->set_alpha((src->get_alpha() * alpha_value) >> 8);
			}
		};
	};
};

#endif /* RISA_PRIMITIVE_HPP_ */
