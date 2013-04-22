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

		template <risa_gl::uint32 min, risa_gl::uint32 max,
				  risa_gl::uint32 projection_min, risa_gl::uint32 projection_max>
		class scale_factor
		{
		private:
			const risa_gl::uint32 range;
			const risa_gl::uint32 projection_range;

		public:
			scale_factor():
				range(max - min),
				projection_range(projection_max - projection_min)
			{}

			risa_gl::uint32 operator()(risa_gl::uint32 value) const
			{
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
			typedef invert_alpha_factor<selector, method_selector> stub_type;
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
		 * 実行時にセットされた定数の補数を返すalpha factor
		 */
		// {{{ invert_constant_alpha_factor
		class invert_constant_alpha_factor :
			public constant_alpha_factor
		{
		public:
			invert_constant_alpha_factor():
				constant_alpha_factor(1)
			{}

			invert_constant_alpha_factor(const int value_):
			constant_alpha_factor(257 - value_)
			{}
		};
		// }}}
	}
}

#endif /* RISA_ALPHA_FACTOR_HPP_ */

