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
		 * 写像スケールマップ
		 */
		template <int min_value, int max_value,
				  int mapped_min = 1, int mapped_max = 256>
		class scaler
		{
		public:
			int operator()(int value) const
			{
				return ((value - min_value) * (mapped_max - mapped_min)) /
					(max_value - min_value) + mapped_min;
			}
		};

		/**
		 * アルファ
		 */
		template <typename target_selecter,
				  typename method_selecter,
				  typename scale_factor>
		class alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			int operator()(src_itor_t src,
							dest_itor_t dest) const
			{
				return scale_factor()
					 (method_selecter()(target_selecter()(src, dest)));
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
				const int alpha_value = alpha_extract_factor()(src, alpha);
				result->set_red((src->get_red() * alpha_value) >> 8);
				result->set_green((src->get_green() * alpha_value) >> 8);
				result->set_blue((src->get_blue() * alpha_value) >> 8);
				result->set_alpha((src->get_alpha() * alpha_value) >> 8);
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
