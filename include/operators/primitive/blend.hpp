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
	};
};

#endif /* RISA_PRIMITIVE_BLEND_HPP_ */

