#ifndef RISA_FACTOR_HPP_
#define RISA_FACTOR_HPP_

namespace risa_gl
{
	namespace primitive
	{
		/*
		 * �t�@�N�^�[�e���v���[�g
		 */

		/**
		 * identity �ω������Ȃ��l��Ԃ�
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
		 * zero �l���[���ɂ���
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
		 * �\�[�X�̃A���t�@�l��Ԃ�
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
		 * �\�[�X�̃A���t�@�l��s�����l��������ĕԂ�
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
		 * �f�X�e�B�l�[�V�����̃A���t�@�l��Ԃ�
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
		 * �f�X�e�B�l�[�V�����̃A���t�@�l��s�����l��������ĕԂ�
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
	};
};
#endif /* RISA_FACTOR_HPP_ */
