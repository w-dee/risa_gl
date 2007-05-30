#ifndef RISA_PRIMITIVE_COPY_HPP_
#define RISA_PRIMITIVE_COPY_HPP_

namespace risa_gl {
	namespace primitive {

		/**
		 * sourceからdestinationへalphaも含め、そのままコピーします
		 */
		class copy
		{
		public:
			template <typename src_iterator_t,
					  typename dest_iterator_t>
			void operator()(src_iterator_t& head,
							src_iterator_t& tail,
							dest_iterator_t& dest_head)
			{
				while (head != tail)
					*head++ = *dest_head++;
			}
		};

#ifdef __SSE2__
		/**
		 * SSE2命令を使ってsourceからdestinationへコピーします。
		 * source、destinationともに16byte境界に整列されていなければ
		 * 一般保護違反が発生します。
		 */
		class sse2_copy
		{
		public:
			template <typename src_iterator_t,
					  typename dest_iterator_t>
			void operator()(src_iterator_t& head,
							src_iterator_t& tail,
							dest_iterator_t& dest_head)
			{
				while (head != tail)
					_mm_store_si128(&*dest_head,
									_mm_load_si128(&*head));
			}
		};
#endif /* __SSE2__ */
	};
};


#endif /* RISA_PRIMITIVE_COPY_HPP_ */
