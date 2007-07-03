#ifndef RISA_PRIMITIVE_HPP_
#define RISA_PRIMITIVE_HPP_
#include "iterator.hpp"
#include "risa_types.hpp"
#include "saturation.hpp"

namespace risa_gl
{
	namespace primitive
	{
		/*
		 * ファクターテンプレート
		 */

		/**
		 * identity 変化させない値を返す
		 */
		class identity_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t dest)
			{
				return 256;
			}
		};

		/**
		 * zero 値をゼロにする
		 */
		class zero_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t dest)
			{
				return 0;
			}
		};

		/**
		 * ソースのアルファ値を返す
		 */
		class source_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t)
			{
				return src->get_alpha();
			}			
		};

		/**
		 * ソースのアルファ値を不透明値から引いて返す
		 */
		class one_minus_source_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t src,
							dest_itor_t)
			{
				return 256 - src->get_alpha();
			}			
		};

		/**
		 * デスティネーションのアルファ値を返す
		 */
		class destination_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t,
							dest_itor_t destination)
			{
				return destination->get_alpha();
			}
		};

		/**
		 * デスティネーションのアルファ値を不透明値から引いて返す
		 */
		class one_minus_destination_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			word operator()(src_itor_t,
							dest_itor_t destination)
			{
				return 256 - destination->get_alpha();
			}
		};

		/* セレクタ */
		/**
		 * sourceを選択するセレクタ
		 */
		class source_target_selecter
		{
		public:
			template <typename source_type, typename destination_type>
			source_type operator()(source_type src, destination_type)
			{
				return src;
			}
		};

		/**
		 * destinationを選択するセレクタ
		 */
		class destination_target_selecter
		{
		public:
			template <typename source_type, typename destination_type>
			destination_type operator()(source_type, destination_type dest)
			{
				return dest;
			}
		};

		class zero_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type) const
			{
				return 0;
			}
		};

		class one_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type) const
			{
				return 1;
			}
		};

		class saturate_color_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type) const
			{
				return 255;
			}
		};

		class saturate_alpha_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type) const
			{
				return 256;
			}
		};

		/**
		 * 対象のイテレータから赤色を取り出すセレクタ
		 */
		class get_red_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor) const
			{
				return itor->get_red();
			}
		};

		/**
		 * 対象のイテレータから緑色を取り出すセレクタ
		 */
		class get_green_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor)
			{
				return itor->get_green();
			}
		};

		/**
		 * 対象のイテレータから青色を取り出すセレクタ
		 */
		class get_blue_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor)
			{
				return itor->get_blue();
			}
		};

		/**
		 * 対象のイテレータからアルファ値を取り出すセレクタ
		 */
		class get_alpha_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor)
			{
				return itor->get_alpha();
			}
		};

		/**
		 * 対象のイテレータから明るさを取り出すセレクタ
		 */
		class get_brightness_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor)
			{
				return itor->get_luminance();
			}
		};

		/**
		 * スケーラ
		 *
		 */
		template <int min_value, int max_value,
				  int mapped_min = 1, int mapped_max = 256>
		class scaler
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor)
			{
				return (*itor  * (mapped_max - mapped_min)) /
					(max_value - min_value) + mapped_min;
			}
		};

		/**
		 * 
		 */
		template <typename target_selecter,
				  typename method_selecter>
		class alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			int operator()(src_itor_t src,
						   dest_itor_t dest) const
			{
				return method_selecter()(target_selecter()(src, dest));
			}
		};

		/**
		 * ブレンドテンプレート
		 */

		/**
		 * 混合テンプレート(サチュレーションなし)
		 */
		template <typename source_factor,
				  typename source_alpha_factor,
				  typename destination_factor,
				  typename destination_alpha_factor>
		class blend
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				result->set_red((src->get_red() *
								 source_factor()(src, dest) +
								 dest->get_red() *
								 destination_factor()(src, dest)) >> 8);
				result->set_green((src->get_green() *
								   source_factor()(src, dest) +
								   dest->get_green() *
								   destination_factor()(src, dest)) >> 8);
				result->set_blue((src->get_blue() *
								  source_factor()(src, dest) +
								  dest->get_blue() *
								  destination_factor()(src, dest)) >> 8);
				result->set_alpha((src->get_alpha() *
								   source_alpha_factor()(src, dest) +
								   dest->get_alpha() *
								   destination_alpha_factor()(src, dest)) >> 8);
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
				result->set_red((src->get_red() *
								 alpha->get_luminance()) >> 8);
				result->set_green((src->get_green() *
								 alpha->get_luminance()) >> 8);
				result->set_blue((src->get_blue() *
								 alpha->get_luminance()) >> 8);
				result->set_alpha((src->get_alpha() *
								   alpha_extract_factor()(src, alpha)) >> 8);
			}
		};

		template <typename channel1_selecter,
				  typename channel1_method_selecter,
				  typename channel2_selecter,
				  typename channel2_method_selecter,
				  typename channel3_selecter,
				  typename channel3_method_selecter,
				  typename channel4_selecter,
				  typename channel4_method_selecter>
		class channel_copy
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t src,
							dest_itor_t dest,
							result_itor_t result) const
			{
				result->set_red(channel1_method_selecter()(
									channel1_selecter()(src, dest)));
				result->set_green(channel2_method_selecter()(
									  channel2_selecter()(src, dest)));
				result->set_blue(channel3_method_selecter()(
									 channel3_selecter()(src, dest)));
				result->set_alpha(channel4_method_selecter()(
									  channel4_selecter()(src, dest)));
			}
		};

		class clear
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t,
					  typename result_itor_t>
			void operator()(src_itor_t,
							dest_itor_t,
							result_itor_t result) const
			{
				*result = typename result_itor_t::value_type(0, 0, 0, 1) ;
			}
		};
	};
};

#endif /* RISA_PRIMITIVE_HPP_ */
