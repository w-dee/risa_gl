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
					saturation((src->get_red() *
								source_factor()(src, dest) +
								dest->get_red() *
								destination_factor()(src, dest)) >> 8));
				result->set_green(
					saturation((src->get_green() *
								source_factor()(src, dest) +
								dest->get_green() *
								destination_factor()(src, dest)) >> 8));
				result->set_blue(
					saturation((src->get_blue() *
								source_factor()(src, dest) +
								dest->get_blue() *
								destination_factor()(src, dest)) >> 8));
				result->set_alpha(
					saturation((src->get_alpha() *
								source_alpha_factor()(src, dest) +
								dest->get_alpha() *
								destination_alpha_factor()(src, dest)) >> 8));
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
