#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_

#include "pixel_traits.hpp"

/**
 * ��������I�����s���t�@���N�^
 */
namespace selector
{
	/**
	 * �\�[�X��I������Z���N�^
	 */
	struct source_selector
	{
		template <typename input_type>
		input_type operator()(input_type src, input_type) const
		{
			return src;
		}
	};

	/**
	 * �f�B�X�e�B�l�[�V������I������Z���N�^
	 */
	struct destination_selector
	{
		template <typename input_type>
		input_type operator()(input_type, input_type dest) const
		{
			return dest;
		}
	};
}

#endif /* SELECTOR_HPP_ */

