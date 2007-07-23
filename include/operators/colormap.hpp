#ifndef RISA_OPERATORS_COLORMAP_HPP_
#define RISA_OPERATORS_COLORMAP_HPP_
#include "operators/primitive/primitive.hpp"
#include "operators/building_blocks.hpp"
#include "pixel.hpp"

namespace risa_gl
{
	namespace operators
	{
		/**
		 * カラーマップオペレータ
		 * result = src.a * constant color を実行する
		 *
		 * * カラーマップ (8bppの不透明度入力を元に特定の色をその不透明
		 * 度で描画) (以下の2*2*4=16種類)
		 * * 65階調(文字描画用) と 256階調(通常用) 
		 * * opacity=255とopacity=255以外の2種類 
		 *   ? これ、opacity=255だとcolor copyと変わらんのでは?
		 * * sourceを完全不透明であると見なし、sourceのアルファ値を保
         *         存して合成
		 *   r = (s.r * o, s.g * o, s.b * o, s.a)
		 * * sourceを完全不透明であると見なし、sourceのアルファ値を破
         *    壊して合成 (上のやつより高速)
		 *   r = (s.r * o, s.g * o, s.b * o, ?)
		 * * sourceのアルファ値をアルファ合成用のアルファ値と見なして合成
		 *   r = r* 1-s.a +
		 *     (s.r * s.a * o, s.g * s.a * o, s.b * s.a * o, s.a * o(?))
		 * * sourceのアルファ値を加算アルファ合成用のアルファ値と見なして合成
		 *   r = sat(r +
		 *     (s.r * s.a * o, s.g * s.a * o, s.b * s.a * o, s.a * o(?)))
		 */

		/**
		 * sourceが65levelの透過性を持つカラーマップ処理。
		 * destは考慮されない
		 */
		class color_copy_65level_colormap
		{
		private:
			typedef blend<dynamic_constant_getter,
						  zero_getter,
						  bit_setter,
						  nop_factor,
						  scaled_destination_opacity_getter<1, 65, 1, 256>,
						  zero_alpha_factor,
						  not_calculate_policy>
			colormap_operator_type;
			colormap_operator_type blender;

			color_copy_65level_colormap();
		public:
			color_copy_65level_colormap(const pixel& color):
				blender(dynamic_constant_getter(color.get_bit_representation()))
			{}
			
			/**
			 * @param src 混合ソース
			 * @param dest opaque値
			 * @param result 結果
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
	};
};

#endif /* RISA_OPERATORS_COLORMAP_HPP_ */
