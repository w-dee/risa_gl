#ifndef RISA_ITERATOR_ADAPTER_HPP_
#define RISA_ITERATOR_ADAPTER_HPP_

#include <iterator.hpp>
#include <memory_chunk.hpp>

namespace risa_gl
{
	template <typename pixel_t, size_t alignment>
	class iterator_adapter
	{
	public:
		typedef pixel_t pixel_type;
		typedef sequential_iterator<pixel_type> iterator_type;
		typedef sequential_iterator<const pixel_type> const_iterator_type;
		typedef memory_chunk<alignment> chunk_type;
		typedef alignment_iterator<chunk_type, alignment>
		alignment_iterator_type;
		typedef alignment_iterator<const chunk_type, alignment>
		const_alignment_iterator_type;

		static bool is_alignment(const void* ptr)
		{
			return (reinterpret_cast<size_t>(ptr) % alignment) == 0;
		}

		static iterator_type to_sequential(alignment_iterator_type itor)
		{
			return iterator_type(
				reinterpret_cast<typename iterator_type::pointer_type>(
					itor->get()));
		}

		static const_iterator_type
		to_sequential(const_alignment_iterator_type itor)
		{
			return const_iterator_type(
				reinterpret_cast<typename const_iterator_type::pointer_type>(
					itor->get()));
		}

		static alignment_iterator_type to_alignment(iterator_type itor)
		{
			return alignment_iterator_type(
				reinterpret_cast
				<typename alignment_iterator_type::pointer_type>(&*itor));
		}

		static const_alignment_iterator_type
		to_alignment(const_iterator_type itor)
		{
			return const_alignment_iterator_type(
				reinterpret_cast
				<typename const_alignment_iterator_type::pointer_type>(
					const_alignment_iterator_type(&*itor)));
		}
	};
};
#endif /* RISA_ITERATOR_ADAPTER_HPP_ */
