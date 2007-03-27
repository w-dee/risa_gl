#ifndef RISA_FRAGMENT_HPP_
#define RISA_FRAGMENT_HPP_

#include "iterator.hpp"

namespace risa_gl
{
	template <typename pixel_store_type>
	class fragment
	{
	public:
		typedef pixel_store_type pixel_store_t;
		typedef pixel_store_t::pixel_t pixel_t;
		typedef sequencial_iterator iterator;

	private:
		iterator head;
		iterator tail;

	public:
		fragment(iterator head_, iterator tail_):
			head(head_), tail(tail_)
		{}

		~fragment()
		{}

		iterator begin()
		{
			return head;
		}

		iterator end()
		{
			return tail;
		}
	};

	template <typename pixel_store_type>
	class aligned_fragment
	{
	public:
		typedef pixel_store_type pixel_store_t;
		typedef pixel_store_t::pixel_t pixel_t;
		typedef aligned_iterator<pixel_store_t::alignment_size> iterator;

	private:
		iterator head;
		iterator tail;

	public:
		fragment(iterator head_, iterator tail_):
			head(head_), tail(tail_)
		{}

		~fragment()
		{}

		iterator begin()
		{
			return head;
		}

		iterator end()
		{
			return tail;
		}
	};
};

#endif /* RISA_FRAGMENT_HPP_ */
