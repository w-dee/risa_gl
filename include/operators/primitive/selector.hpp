#ifndef RISA_SELECTOR_HPP_
#define RISA_SELECTOR_HPP_

namespace risa_gl
{
	namespace primitive
	{
		/**
		 * sourceを選択するセレクタ
		 */
		class source_selector
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
		class destination_selector
		{
		public:
			template <typename source_type, typename destination_type>
			destination_type operator()(source_type, destination_type dest)
			{
				return dest;
			}
		};
	}
}

#endif /* RISA_SELECTOR_HPP_ */
