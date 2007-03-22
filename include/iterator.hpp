#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

namespace risa_gl
{
	template <typename pixel_type>
	class forward_iterator
	{
	public:
		typedef pixel_type pixel_t;

	private:
		const pixel_t* pointer;

	public:
		forward_iterator():
			pointer()
		{}

		forward_iterator(const forward_iterator& source):
			pointer(source.pointer)
		{}

		forward_iterator(const pixel_t* source):
			pointer(source)
		{}

		~forward_iterator()
		{}

		const pixel_t& operator*() const
		{
			return *pointer;
		}

		pixel_t& operator*()
		{
			return *pointer;
		}
	};
}

#endif /* RISA_ITERATOR_HPP_ */
