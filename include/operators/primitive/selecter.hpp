#ifndef RISA_SELECTER_HPP_
#define RISA_SELECTER_HPP_

namespace risa_gl
{
	namespace primitive
	{
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
		 * 対象のイテレータから不透明度を取り出すセレクタ
		 */
		class get_opacity_method_selecter
		{
		public:
			template <typename iterator_type>
			int operator()(iterator_type itor)
			{
				return itor->get_opacity();
			}
		};
	};
};

#endif /* RISA_SELECTER_HPP_ */
