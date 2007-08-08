#ifndef RISA_PRIMITIVE_HPP_
#define RISA_PRIMITIVE_HPP_
#include <iterator.hpp>
#include <risa_types.hpp>
#include <operators/primitive/compute_factor.hpp>
#include <operators/primitive/selector.hpp>
#include <operators/primitive/alpha_factor.hpp>

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * 下位ビット側をマスクするファンクタ
		 */
		class lower_mask
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return value & 0x00ff00ffU;
			}
		};

		/**
		 * 上位ビット側をマスクするファンクタ
		 */
		class higher_mask
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return value & 0xff00ff00U;
			}
		};

		/**
		 * 除算ファクタ
		 */
		template <int divisor = 256>
		class divide_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				return value / divisor;
			}
		};

		/**
		 * 混合テンプレート
		 * 
		 * Porter-Diff color composite
		 * Cr = f(Cs*Fs + Cd*Fd)
		 * Ar = f(As*Fs + Ad*Fd)
		 *
		 * Cd演算はbit_representation()からのパック演算で処理
		 * 各種演算の違いはfactorで埋め合わせ
		 * f(): saturation, constant replacement
		 * Cs: source color
		 * Cd: destination color
		 * Cr: result color
		 * As: source alpha
		 * Ad: destination alpha
		 * Ar: result alpha
		 *
		 *
		 * @param src_pixel_getter
		 * src_itorからのピクセル値の取得抽象化
		 *
		 * @param dest_pixel_getter
		 * dest_itorからのピクセル値の取得抽象化
		 *
		 * @param result_pixel_setter
		 * 計算されたピクセル値の設定抽象化
		 * 
		 * @param compute_factor
		 *  saturationや定数項を導入するためのポイント
		 *  
		 * @param src_alpha_factor
		 *  src color演算時に適用するalpha値演算
		 * 
		 * @param dest_alpha_factor
		 *  dest color演算時に適用するalpha値演算
		 *  
		 * @param alpha_calculate_policy
		 *  nopかresultのalpha演算
		 *
		 * @param divisor
		 *  計算途中にある除算項のオペレータ
		 *  
		 * @note 各種テンプレートパラメータファンクタはデフォルトコン
		 * ストラクタを持つ必要があります。パラメータを受け取る必要が
		 * あるものに関してはその限りではありませんが、その場合、blend
		 * ファンクタのインスタンス時にコンストラクタにそのパラメータ
		 * を含めてやる必要があります。
		 * 
		 * @note 演算後の / 256 である >> 8部分は固定なので即値を返す
		 * 場合は * 256 した値を与えてください
		 */

		// {{{ trinomial_blend(三項演算)
		// }}}

		// {{{  binomial_blend (二項演算)
		template <typename src_pixel_getter_t,
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
			src_pixel_getter_t src_pixel_getter;
			dest_pixel_getter_t dest_pixel_getter;
			result_pixel_setter_t result_pixel_setter;
			compute_factor_t compute_factor;
			src_alpha_factor_t src_alpha_factor;
			dest_alpha_factor_t dest_alpha_factor;
			alpha_calculate_policy_t alpha_calculate_policy;
			divisor_factor_t divisor_factor;

		public:
			typedef src_pixel_getter_t src_getter_type;
			typedef dest_pixel_getter_t dest_getter_type;
			typedef result_pixel_setter_t result_setter_type;
			typedef compute_factor_t compute_type;
			typedef src_alpha_factor_t source_alpha_type;
			typedef dest_alpha_factor_t destination_alpha_type;
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
						   alpha_calculate_policy_t alpha_calculate_policy_ =
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

				const risa_gl::uint32 src_pixel =
					src_pixel_getter(src, dest);
				const risa_gl::uint32 dest_pixel =
					dest_pixel_getter(src, dest);

				/**
				 * pixelのパック演算
				 * @note 最適化なしの一番genericなバージョン。必要なら
				 * 部分特殊化などで必要なものを用意してください
				 */
				risa_gl::uint32 res_pixel =
					compute_factor(
						divisor_factor((lower_mask()(src_pixel) *
										src_alpha_factor(src, dest)) &
									   0xff00ff00) +
						divisor_factor((lower_mask()(dest_pixel) *
										dest_alpha_factor(src, dest)) &
									   0xff00ff00));
				assert (res_pixel & 0xff00ff00);

				const risa_gl::uint32 res_pixel2 =
					(compute_factor(
						divisor_factor(((higher_mask()(dest_pixel)>>8) *
										dest_alpha_factor(src, dest)) &
									   0xff00ff00) +
						divisor_factor(((higher_mask()(src_pixel)>>8) *
										src_alpha_factor(src, dest)) &
									   0xff00ff00)) << 8);
				assert (res_pixel2 & 0x00ff00ff);

				res_pixel |= res_pixel2;

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

		// {{{ monomial_predicate(単項演算)
		// }}}

		// {{{ stripped_predicate(無項演算)
		// }}}
	}
}

#endif /* RISA_PRIMITIVE_HPP_ */
