#ifndef RISA_ALPHA_FACTOR_HPP_
#define RISA_ALPHA_FACTOR_HPP_

#include <risa_types.hpp>

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
		 * 写像スケーリングつきalpha_selector
		 * @param min 元のalpha値の最小値
		 * @param max 元のalpha値の最大値
		 * @param projection_min alpha値の最小値
		 * @param projection_max alpha値の最大値
		 */
		template <int min, int max, int projection_min, int projection_max,
				  typename selector, typename method_selector>
		class scaled_alpha_selector
		{
			typedef alpha_factor<selector, method_selector> stub_type;

		public:
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				const int range = max - min;
				const int projection_range = projection_max - projection_min;

				return (stub_type()(src, dest) - min) *
					projection_range / range + projection_min;
			}
		};

		/**
		 * 対象の補値をアルファ値として扱うアルファファクタ
		 * @param selector srcかdestを指定するselector
		 * @param method_selector アルファ値を取り出すmethod_selector
		 */
		template <typename selector,
				  typename method_selector>
		class invert_alpha_factor
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

		/**
		 * 写像スケーリングつきinvert_alpha_selector
		 * @param min 元のalpha値の最小値
		 * @param max 元のalpha値の最大値
		 * @param projection_min alpha値の最小値
		 * @param projection_max alpha値の最大値
		 */
		template <int min, int max, int projection_min, int projection_max,
				  typename selector, typename method_selector>
		class scaled_invert_alpha_selector
		{
			typedef alpha_factor<selector, method_selector> stub_type;

		public:
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				const int range = max - min;
				const int projection_range = projection_max - projection_min;

				return projection_max -
					((stub_type()(src, dest) - min) *
					 projection_range / range + projection_min);
			}
		};
	};
};

#endif /* RISA_ALPHA_FACTOR_HPP_ */

