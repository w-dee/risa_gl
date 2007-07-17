#ifndef RISA_SELECTER_HPP_
#define RISA_SELECTER_HPP_

namespace risa_gl
{
	namespace primitive
	{
		/* �Z���N�^ */
		/**
		 * source��I������Z���N�^
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
		 * destination��I������Z���N�^
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
		 * �Ώۂ̃C�e���[�^����ԐF�����o���Z���N�^
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
		 * �Ώۂ̃C�e���[�^����ΐF�����o���Z���N�^
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
		 * �Ώۂ̃C�e���[�^����F�����o���Z���N�^
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
		 * �Ώۂ̃C�e���[�^����A���t�@�l�����o���Z���N�^
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
		 * �Ώۂ̃C�e���[�^����s�����x�����o���Z���N�^
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
