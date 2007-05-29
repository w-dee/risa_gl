#ifndef RISA_FRAGMENT_RANGE_HPP_
#define RISA_FRAGMENT_RANGE_HPP_

#include "fragment.hpp"
#include "iterator_adapter.hpp"

namespace risa_gl {

	/**
	 * @todo l.c.m. g.c.d.を使ったより効率的なアライメント位置の取得
	 */
	template <typename pixel_store_t, size_t fragment_size>
	class fragment_range
	{
	public:
		typedef pixel_store_t pixel_store_type;
		typedef typename pixel_store_type::fragment_type fragment_type;
		typedef typename fragment_type::iterator sequential_iterator_type;
		typedef iterator_adapter<typename pixel_store_type::pixel_type,
								 pixel_store_type::alignment_size>
		iterator_adapter_type;
		typedef  alignment_iterator<
			memory_chunk<pixel_store_type::alignment_size>,
			pixel_store_type::alignment_size> aligned_iterator_type;


		template <typename itor_type>
		class range
		{
		public:
			typedef itor_type iterator_type;

		private:
			iterator_type head;
			iterator_type tail;

		public:
			range(iterator_type head_, iterator_type tail_):
				head(head_), tail(tail_)
			{}

			range(const range& rhs):
				head(rhs.head), tail(rhs.tail)
			{}

			~range()
			{}

			range& operator=(const range& rhs)
			{
				if (this != &rhs)
				{
					this->head = rhs.head;
					this->tail = rhs.tail;
				}

				return *this;
			}

			iterator_type begin()
			{
				return head;
			}

			iterator_type end()
			{
				return tail;
			}
		};

		typedef range<sequential_iterator_type> iterator_range;
		typedef range<aligned_iterator_type> aligned_range;

		
	private:
		sequential_iterator_type head;
		sequential_iterator_type tail;
	
	public:
		fragment_range(sequential_iterator_type head_,
					   sequential_iterator_type tail_):
			head(head_), tail(tail_)
		{}

		~fragment_range()
		{}

		iterator_range get_front()
		{
			sequential_iterator_type front_end = head;
			while (!iterator_adapter_type::is_alignment(&*front_end))
				++front_end;
			
			return iterator_range(head, front_end);
		}

		aligned_range get_middle()
		{
			sequential_iterator_type front_end = head;
			while (!iterator_adapter_type::is_alignment(&*front_end))
				++front_end;

			sequential_iterator_type back_begin = tail;
			while (!iterator_adapter_type::is_alignment(&*back_begin))
				--back_begin;

			return
				aligned_range(iterator_adapter_type::to_alignment(front_end),
							  iterator_adapter_type::to_alignment(back_begin));
		}

		iterator_range get_back()
		{
			sequential_iterator_type back_begin = tail;
			while (!iterator_adapter_type::is_alignment(&*back_begin))
				--back_begin;

			return iterator_range(back_begin, tail);
		}
	};
};
#endif /* RISA_FRAGMENT_RANGE_HPP_ */
