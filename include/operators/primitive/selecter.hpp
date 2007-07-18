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
		 * destination��I������Z���N�^
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
