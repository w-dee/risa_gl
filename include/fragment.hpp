#ifndef RISA_FRAGMENT_HPP_
#define RISA_FRAGMENT_HPP_

#include "iterator.hpp"

namespace risa_gl
{
	template <typename pixel_store_t>
	class fragment
	{
	public:
		typedef pixel_store_t pixel_store_type;
		typedef typename pixel_store_type::pixel_type pixel_type;
		typedef typename pixel_store_type::iterator iterator;
		typedef typename pixel_store_type::const_iterator const_iterator;

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

		const_iterator begin() const
		{
			return head;
		}

		iterator end()
		{
			return tail;
		}

		const_iterator end() const
		{
			return tail;
		}
	};

	template <typename pixel_store_t>
	class aligned_fragment
	{
	public:
		typedef pixel_store_t pixel_store_type;
		typedef typename pixel_store_type::pixel_type pixel_type;
		typedef fragments_iterator<pixel_type, 
								   pixel_store_type::alignment_size>
		iterator;
		typedef fragments_iterator<const pixel_type,
								   pixel_store_type::alignment_size>
		const_iterator;

	private:
		iterator head;
		iterator tail;

	public:
		aligned_fragment(iterator head_, iterator tail_):
			head(head_), tail(tail_)
		{}

		~aligned_fragment()
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
