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
		class source_selecter
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
		class destination_selecter
		{
		public:
			template <typename source_type, typename destination_type>
			destination_type operator()(source_type, destination_type dest)
			{
				return dest;
			}
		};
	};
};

#endif /* RISA_SELECTER_HPP_ */
