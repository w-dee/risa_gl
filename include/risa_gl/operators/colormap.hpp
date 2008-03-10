#ifndef RISA_OPERATORS_COLORMAP_HPP_
#define RISA_OPERATORS_COLORMAP_HPP_
#include <risa_gl/primitive/blend.hpp>
#include <risa_gl/operators/building_blocks.hpp>
#include <risa_gl/pixel.hpp>

namespace risa_gl
{
	namespace operators
	{
		// {{{ abstruct
		/**
		 * カラーマップオペレータ
		 * result = src.a * constant color を実行する
		 *
		 * * カラーマップ (8bppの不透明度入力を元に特定の色をその不透明
		 * 度で描画) (以下の2*2*4=16種類)
		 * * 65階調(文字描画用) と 256階調(通常用) 
		 * * opacity=255とopacity=255以外の2種類 
		 *  * alphaとは別にopacityを読み込んでそれを掛けるってこと？
		 *   
		 * * sourceを完全不透明であると見なし、sourceのアルファ値を保
         *         存して合成
		 *   r = (s.r * o, s.g * o, s.b * o, s.a)
		 *   
		 * * sourceを完全不透明であると見なし、sourceのアルファ値を破
         *    壊して合成 (上のやつより高速)
		 *   r = (s.r * o, s.g * o, s.b * o, ?)
		 *   
		 * * sourceのアルファ値をアルファ合成用のアルファ値と見なして合成
		 *   r = r* 1-s.a +
		 *     (s.r * s.a * o, s.g * s.a * o, s.b * s.a * o, s.a * o(?))
		 *     
		 * * sourceのアルファ値を加算アルファ合成用のアルファ値と見なして合成
		 *   r = sat(r +
		 *     (s.r * s.a * o, s.g * s.a * o, s.b * s.a * o, s.a * o(?)))
		 */
		// }}}

		/**
		 * destinationが65levelの透過性を持つカラーマップ処理。
		 * alphaは不定
		 * sourceはopaqueであること
		 * r = color.color * scale(source.opaque) +
		 *					 dest.color * (1-scale(source.opaque))
		 */
		// {{{ colormap_6bpp_transparency
		class colormap_6bpp_transparency
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				destination_getter,
				bit_setter,
				plus_function,
				scaled_source_opacity_getter<1, 65, 1, 256>,
				scaled_invert_source_opacity_getter<1, 65, 1, 256>,
				not_calculate_policy>
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_6bpp_transparency();

		public:
			colormap_6bpp_transparency(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src opaque値へのイテレータ
			 * @param dest 下敷きとなるピクセルイテレータ
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * destinationが65levelの透過性を持つカラーマップ処理。
		 * alphaは保存
		 * sourceはopaqueであること
		 * r = color.color * scale(source.opaque) +
		 *					 dest.color * (1-scale(source.opaque))
		 * r.a = dest.a
		 */
		// {{{ colormap_6bpp_transparency_save_destination_alpha
		class colormap_6bpp_transparency_save_destination_alpha
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				destination_getter,
				bit_setter,
				plus_function,
				scaled_source_opacity_getter<1, 65, 1, 256>,
				scaled_invert_source_opacity_getter<1, 65, 1, 256>,
				alpha_calculate_policy<
				destination_alpha_getter> >
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_6bpp_transparency_save_destination_alpha();
		public:
			colormap_6bpp_transparency_save_destination_alpha(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 設定する透過度を持つイテレータ
			 * @param dest opaque値
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * destinationが65levelの透過性を持つカラーマップ-アルファブレンド処理。
		 * alphaは今のところ破壊される
		 * r = color.rgb * scale(source.opaque) +
		 *     destination.rgb * (1-scale(source.opaque))
		 */
		// {{{ colormap_6bpp_alpha_blend
		class colormap_6bpp_alpha_blend
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				destination_getter,
				bit_setter,
				plus_function,
				scaled_source_opacity_getter<1, 65, 1, 256>,
				scaled_invert_source_opacity_getter<1, 65, 1, 256>,
				not_calculate_policy>
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_6bpp_alpha_blend();

		public:
			colormap_6bpp_alpha_blend(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 設定する透過度を持つイテレータ
			 * @param dest opaque値
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * sourceが65levelの透過性を持つカラーマップ-加色混合処理。
		 * r = saturation(color.rgb * scale(source.opaque) +
		 *                destination.rgb * scale(source.opaque))
		 */
		// {{{ colormap_6bpp_add_blend
		class colormap_6bpp_add_blend
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				identity_alpha_factor,
				scaled_invert_source_opacity_getter<1, 65, 1, 256>,
				alpha_calculate_policy<
				scaled_source_opacity_getter<1, 65, 1, 256> > >
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_6bpp_add_blend();

		public:
			colormap_6bpp_add_blend(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 設定する透過度を持つイテレータ
			 * @param dest opaque値
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * destinationを透過性としてカラーマップ処理。
		 * alphaは不定
		 * r = color.rgba * scale(dest.a)
		 */
		// {{{ colormap_transparency
		class colormap_transparency
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				zero_getter,
				bit_setter,
				plus_function,
				source_opacity_getter,
				zero_alpha_factor,
				not_calculate_policy>
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_transparency();

		public:
			colormap_transparency(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 無視される
			 * @param dest alpha値をもつイテレータ
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * destinationがアルファとしてカラーマップ処理。
		 * alphaは保存
		 * r = color.rgb * scale(dest.a)
		 */
		// {{{ colormap_transparency_save_alpha
		class colormap_transparency_save_alpha
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				zero_getter,
				bit_setter,
				plus_function,
				source_opacity_getter,
				zero_alpha_factor,
				alpha_calculate_policy<
				destination_alpha_getter> >
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_transparency_save_alpha();

		public:
			colormap_transparency_save_alpha(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 設定する透過度を持つイテレータ
			 * @param dest alpha値をもつイテレータ
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * destinationをアルファ値としてカラーマップ-アルファブレンド処理。
		 * alphaは今のところ破壊される
		 * r = color.rgb * scale(dest.a) +
		 *     source.rgb * (1-scale(dest.a))
		 */
		// {{{ colormap_alpha_blend
		class colormap_alpha_blend
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				destination_getter,
				bit_setter,
				plus_function,
				multiply_constant_and_source_opacity_getter,
				multiply_invert_constant_and_source_opacity_getter,
				not_calculate_policy>
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_alpha_blend();

		public:
			colormap_alpha_blend(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()),
						destination_getter(),
						bit_setter(),
						plus_function(),
						multiply_constant_and_source_opacity_getter(
							color.get_alpha()),
						multiply_invert_constant_and_source_opacity_getter(
							color.get_alpha()))
			{}
			
			/**
			 * @param src 設定する透過度を持つイテレータ
			 * @param dest alpha値を持つイテレータ
			 * @param result 結果を受け取るイテレータ
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
		// }}}

		/**
		 * destinationをアルファ値としてカラーマップ-加色混合処理。
		 * r = saturation(color.rgb * scale(dest.a) +
		 *                source.rgb * scale(dest.a))
		 */
		// {{{ colormap_add_blend
		class colormap_add_blend
		{
		private:
			typedef binomial_blend<
				dynamic_constant_getter,
				destination_getter,
				bit_setter,
				add_saturation_function,
				source_opacity_getter,
				source_opacity_getter,
				alpha_calculate_policy<
				destination_alpha_getter > >
			colormap_operator_type;
			colormap_operator_type blender;

			colormap_add_blend();

		public:
			colormap_add_blend(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 加色合成対象のイテレータ
			 * @param dest alpha値をもつイテレータ
			 * @param result 結果を受け取るイテレータ
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
		// }}}

	}
}
#endif /* RISA_OPERATORS_COLORMAP_HPP_ */
