#ifndef RISA_ALPHA_FACTOR_HPP_
#define RISA_ALPHA_FACTOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * 値をそのまま適用するアルファファクタ
		 */
		class identity_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 256;
			}
		};

		/**
		 * アルファ値がゼロとして適用するアルファファクタ
		 */
		class zero_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 0;
			}
		};

		/**
		 * 選択型アルファファクタ
		 * @param selector srcかdestを指定するselector
		 * @param method_selector アルファ値を取り出すmethod_selector
		 */
		template <typename selector,
				  typename method_selector>
		class alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return method_selector()(selector()(src, dest));
			}
		};

		/**
		 * 対象のアルファ値の補値をアルファ値として扱うアルファファクタ
		 * @param selector srcかdestを指定するselector
		 * @param method_selector アルファ値を取り出すmethod_selector
		 */
		template <typename selector,
				  typename method_selector>
		class one_minus_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return 256 - method_selector()(selector()(src, dest));
			}
		};
	};
};

#endif /* RISA_ALPHA_FACTOR_HPP_ */

