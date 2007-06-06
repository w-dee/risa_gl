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
			void operator()(const_sequential_iterator& src,
							sequential_iterator& dest)
			{
				*dest = *src;
			}
		};

		/**
		 * sourceからdestinationへ透明度のみコピーします。
		 */
		class copy_transparency
		{
		public:
			void operator()(const_sequential_iterator& src,
							sequential_iterator& dest)
			{
				dest->set_alpha(src->get_alpha());
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
			void operator()(aligned_iterator<const pixel, 16>& src,
							aligned_iterator<pixel, 16>& dest)
			{
					_mm_store_si128(&*dest,
									_mm_load_si128(&*src));
			}
		};
#endif /* __SSE2__ */
	};
};


#endif /* RISA_PRIMITIVE_COPY_HPP_ */
