#ifndef RISA_ALPHA_FACTOR_HPP_
#define RISA_ALPHA_FACTOR_HPP_

#include <risa_gl/risa_types.hpp>

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
			risa_gl::uint32 operator()(src_itor_t,
									   dest_itor_t) const
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
			risa_gl::uint32 operator()(src_itor_t,
									   dest_itor_t) const
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
		 * selectorを利用して対象からalpha値を取り出し、逆数を返す
		 * @param
		 */
		 template <typename selector,
				   typename method_selector>
		 class inverse_alpha_factor
		 {
		 public:
			 template <typename src_itor_t,
					   typename dest_itor_t>
			 risa_gl::uint32 operator()(src_itor_t src,
										dest_itor_t dest) const
			 {
				 return 256 / method_selector()(selector()(src, dest));
			 }
		 };

		template <int min, int max, int projection_min, int projection_max>
		class scale_factor
		{
		public:
			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
				const int range = max - min;
				const int projection_range = projection_max - projection_min;

				return (value - min) *
					projection_range / range + projection_min;
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
			typedef scale_factor<min, max, projection_min, projection_max>
			scaler;

		public:
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return scaler()(stub_type()(src, dest));
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
				return 257 - method_selector()(selector()(src, dest));
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
			typedef scale_factor<min, max, projection_min, projection_max>
			scaler;
		public:
			
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t src,
									   dest_itor_t dest) const
			{
				return scaler()(stub_type()(src, dest));
			}
		};

		class full_transparent_alpha_factor
		{
		public:
			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t,
									   dest_itor_t) const
			{
				return 1;
			}
		};			
			
		/**
		 * 実行時にセットされた定数を返すalpha factor
		 */
		// {{{ constant_alpha_factor
		class constant_alpha_factor
		{
		private:
			const int value;

		public:
			constant_alpha_factor():
				value(256)
			{}

			constant_alpha_factor(const int value_):
				value(value_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t,
									   dest_itor_t) const
			{
				return value;
			}
		};
		// }}}
	
		/**
		 * 実行時にセットされた定数の逆数を返すalpha factor
		 */
		// {{{ invert_constant_alpha_factor
		class invert_constant_alpha_factor
		{
		private:
			const int value;

		public:
			invert_constant_alpha_factor():
				value(1)
			{}

			invert_constant_alpha_factor(const int value_):
				value(257 - value_)
			{}

			template <typename src_itor_t,
					  typename dest_itor_t>
			risa_gl::uint32 operator()(src_itor_t,
									   dest_itor_t) const
			{
				return value;
			}
		};
		// }}}
	}
}

#endif /* RISA_ALPHA_FACTOR_HPP_ */

