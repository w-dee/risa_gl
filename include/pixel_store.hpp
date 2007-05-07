#ifndef RISA_PIXEL_STORE_HPP_
#define RISA_PIXEL_STORE_HPP_

#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "fragment.hpp"
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

		typedef sequential_iterator<pixel_type> iterator;
		typedef sequential_iterator<const pixel_type> const_iterator;

	private:
		const int width;
		const int height;
		const int fragment_length;

		std::vector<pixel_type> pixels;

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

		fragment<pixel_store> get_fragment(size_t line)
		{
			assert (line < static_cast<size_t>(height));

			return fragment<pixel_store>(this->begin() + width * line,
										 this->begin() + (width * (line + 1)));
		}

		const_fragment<pixel_store> get_fragment(size_t line) const
		{
			assert (line < static_cast<size_t>(height));

			return fragment<pixel_store>(this->begin() + width * line,
										 this->begin() + (width * (line + 1)));
		}

		aligned_fragment<pixel_store> get_aligned_fragment(size_t line)
		{
			assert (line < height);

			typedef iterator_adapter<pixel_type, alignment> adapter_type;

			return aligned_fragment<pixel_store>
				(adapter_type::to_fragments(this->begin() + width * line),
				 adapter_type::to_fragments(this->begin() + (width*line + 1)));
		}

		const aligned_fragment<pixel_store>
		get_aligned_fragment(size_t line) const
		{
			assert (line < height);

			typedef iterator_adapter<pixel_type, alignment> adapter_type;

			return aligned_fragment<pixel_store>
				(adapter_type::to_fragments(this->begin() + width * line),
				 adapter_type::to_fragments(this->begin() + (width*(line+1))));
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
	};
};

#endif /* RISA_PIXEL_STORE_HPP_ */
