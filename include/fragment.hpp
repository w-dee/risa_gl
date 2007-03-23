#ifndef RISA_FRAGMENT_HPP_
#define RISA_FRAGMENT_HPP_

namespace risa_gl
{
	template <typename pixel_store_type>
	class fragment
	{
	public:
		typedef pixel_store_type pixel_store_t;
		typedef pixel_store_t::pixel_t pixel_t;
		typedef pixel_store_t::iterator iterator;

	private:
		iterator head;
		iterator tail;

	public:
		fragment(pixel_store_t::iterator head_,
				 pixel_store_t::iterator tail_):
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
