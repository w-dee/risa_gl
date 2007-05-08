#ifndef RISA_FRAGMENT_HPP_
#define RISA_FRAGMENT_HPP_

#include "iterator.hpp"
#include "pixel_store.hpp"

namespace risa_gl
{
	template <typename pixel_t, typename iterator_t>
	class fragment
	{
	public:
		typedef pixel_t pixel_type;
		typedef iterator_t iterator;

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
