#ifndef SELECTOR_HPP_
#define SELECTOR_HPP_

#include "pixel_traits.hpp"

/**
 * 引数から選択を行うファンクタ
 */
namespace selector
{
	/**
	 * ソースを選択するセレクタ
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
	 * ディスティネーションを選択するセレクタ
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

