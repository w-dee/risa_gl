#ifndef RISA_PRIMITIVE_BLEND_HPP_
#define RISA_PRIMITIVE_BLEND_HPP_

namespace risa_gl {
	namespace primitive {

		/**
		 * 色混合ポリシーの基底クラス
		 */
		struct blend_policy {};

		/**
		 * 被演算側を完全不透明とみなし、アルファ値を破壊してブレンド
		 */
		struct unclearly_u_with_destruction_alpha : public blend_policy {};

		/**
		 * 被演算側を完全不透明とみなし、アルファ値を保存してブレンド
		 */
		struct unclearly_u_with_save_alpha : public blend_policy {};

		/**
		 * Uのアルファ値をアルファ合成用のアルファ値と見なしてブレンド
		 */
		struct using_u_alpha : public blend_policy {};

		/**
		 * Uのアルファ値を加算アルファ合成用のアルファ値と見なしてブレンド
		 */
		struct using_u_alpha_with_addition : public blend_policy {};

		/**
		 *
		 */
		class blend
		{
		public:
			template <typename src_iterator_t,
					  typename dest_iterator_t>
			operator()(src_iterator_t& head,
					   src_iterator_t& tail,
					   dest_iterator_t& dest_head)
			{
				while (head != tail)
				{
					
				}
			}
		};
	
	};
};

#endif /* RISA_PRIMITIVE_BLEND_HPP_ */

