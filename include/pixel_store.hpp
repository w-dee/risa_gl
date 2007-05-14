#ifndef RISA_PIXEL_STORE_HPP_
#define RISA_PIXEL_STORE_HPP_

#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "fragment.hpp"
#include "allocator.hpp"
#include <vector>

namespace risa_gl
{
	template <typename pixel_t, size_t alignment>
	class pixel_store
	{
		friend class pixel_store_test;

	public:
		typedef pixel_t pixel_type;
		enum {
			alignment_size = alignment,
			pixel_size = sizeof(pixel_type)
		};

	private:
		pixel_store(const pixel_store&);
		pixel_store& operator=(const pixel_store&);

		const int width;
		const int height;
		const int fragment_length;

		typedef std::vector<pixel_type,
							aligned_allocator<pixel_type, alignment> > 
		pixel_vector_type;
		pixel_vector_type pixels;

		typedef sequential_iterator<pixel_type> iterator;
		typedef sequential_iterator<const pixel_type> const_iterator;
		typedef alignment_iterator<pixel_type, alignment> align_iterator;
		typedef alignment_iterator<const pixel_type, alignment> const_align_iterator;

	public:
		typedef fragment<pixel_type, iterator> fragment_type;
		typedef fragment<const pixel_type, const_iterator> const_fragment_type;
		typedef fragment<pixel_type, align_iterator> aligned_fragment_type;
		typedef fragment<const pixel_type, const_align_iterator>
			const_aligned_fragment_type;

	private:

		static size_t get_fragment_size(const int bytes)
		{
			return (bytes + (alignment - 1)) & ~(alignment - 1);
		}

		iterator begin()
		{
			return &*pixels.begin();
		}

		const_iterator begin() const
		{
			return &*pixels.begin();
		}

		iterator end()
		{
			return &*pixels.end();
		}

		const_iterator end() const
		{
			return &*pixels.end();
		}

	public:
		pixel_store(const int width_, const int height_):
				width(width_),
				height(height_),
				fragment_length(get_fragment_size(width_ * pixel_size)),
				pixels(fragment_length / pixel_size * height)
		{}

		~pixel_store()
		{}

		int get_width() const
		{
			return width;
		}

		int get_height() const
		{
			return height;
		}

		int get_fragment_length() const
		{
			return fragment_length;
		}

		pixel_type& operator()(int x, int y)
		{
			return pixels[y * width + x];
		}

		const pixel_type& operator()(int x, int y) const
		{
			return pixels[y * width + x];
		}

		fragment_type get_fragment(size_t line)
		{
			assert (line < static_cast<size_t>(height));

			iterator head = this->begin() + width * line;
			iterator tail = this->begin() + (width * (line + 1));
			return fragment_type(head, tail);
		}

		const_fragment_type get_fragment(size_t line) const
		{
			assert (line < static_cast<size_t>(height));

			const_iterator head = this->begin() + width * line;
			const_iterator tail = this->begin() + (width * (line + 1));
			return const_fragment_type(head, tail);
		}

		aligned_fragment_type get_aligned_fragment(size_t line)
		{
			assert (line < static_cast<size_t>(height));

			typedef iterator_adapter<pixel_type, alignment> adapter_type;

			iterator head(this->begin() + width * line);
			iterator last(this->begin() + (width * (line + 1)));
			return aligned_fragment_type
				(adapter_type::to_alignment(head),
				 adapter_type::to_alignment(last));
		}

		const_aligned_fragment_type get_aligned_fragment(size_t line) const
		{
			assert (line < static_cast<const size_t>(height));

			typedef iterator_adapter<pixel_type, alignment> adapter_type;

			const_iterator head(this->begin() + width * line);
			const_iterator last(this->begin() + (width * (line+1)));
			return const_aligned_fragment_type
				(adapter_type::to_alignment(head),
				 adapter_type::to_alignment(last));
		}
	};
};

#endif /* RISA_PIXEL_STORE_HPP_ */
