#ifndef RISA_ITERATOR_TRAITS_HPP_
#define RISA_ITERATOR_TRAITS_HPP_

namespace risa_gl
{
	template <typename iterator_type>
	class iterator_traits
	{
	public:
		typedef iterator_type iterator_t;
		typedef iterator_t::pointer_t pointer_t;

	};
};

#endif /* RISA_ITERATOR_TRAITS_HPP_ */
