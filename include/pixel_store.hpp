#ifndef RISA_PIXEL_STORE_HPP_
#define RISA_PIXEL_STORE_HPP_

#include <iterator.hpp>
#include <iterator_adapter.hpp>
#include <fragment.hpp>
#include <allocator.hpp>
#include <vector>

namespace risa_gl
{
	template <typename pixel_t, size_t alignment = 16>
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
		const size_t fragment_length;

		typedef std::vector<pixel_type,
							aligned_allocator<pixel_type, alignment> > 
		pixel_vector_type;
		pixel_vector_type pixels;

	public:
		typedef sequential_iterator<pixel_type> iterator;
		typedef sequential_iterator<const pixel_type> const_iterator;

		typedef fragment<pixel_type, iterator> fragment_type;
		typedef fragment<const pixel_type, const_iterator> const_fragment_type;

	private:

		static size_t get_fragment_size(const int bytes)
		{
			return (bytes + (alignment - 1)) & ~(alignment - 1);
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

			iterator head = this->begin() + width * static_cast<const int>(line);
			iterator tail =
				this->begin() + (width * (static_cast<const int>(line) + 1));
			return fragment_type(head, tail);
		}

		fragment_type get_fragment(size_t line, int left, int right)
		{
			assert (line < static_cast<size_t>(height));
			assert (left <= right);

			iterator head = this->begin() + width * line + left;
			iterator tail = this->begin() + width * line + right;
			return fragment_type(head, tail);
		}			

		const_fragment_type get_fragment(size_t line) const
		{
			assert (line < static_cast<size_t>(height));

			const_iterator head = this->begin() + width * line;
			const_iterator tail = this->begin() + (width * (line + 1));
			return const_fragment_type(head, tail);
		}

		const_fragment_type
		get_fragment(size_t line, int left, int right) const
		{
			assert (line < static_cast<size_t>(height));
			assert (left <= right);

			const_iterator head = this->begin() + width * line + left;
			const_iterator tail = this->begin() + width * line + right;
			return const_fragment_type(head, tail);
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
			return &*pixels.begin() + pixels.size();
		}

		const_iterator end() const
		{
			return &*pixels.begin() + pixels.size();
		}

	};
}

#endif /* RISA_PIXEL_STORE_HPP_ */
