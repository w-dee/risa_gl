#ifndef RISA_PIXEL_STORE_HPP_
#define RISA_PIXEL_STORE_HPP_

#include <risa_gl/iterator.hpp>
#include <risa_gl/iterator_adapter.hpp>
#include <risa_gl/fragment.hpp>
#include <risa_gl/allocator.hpp>
#include <risa_gl/math/lcm.hpp>
#include <vector>

#include <cassert>

namespace risa_gl
{
	template <typename pixel_t,
			  typename allocator_t =
			  risa_gl::aligned_allocator<pixel_t, 16> >
	class pixel_store
	{
		friend class pixel_store_test;
	public:
		typedef pixel_t pixel_type;
		typedef allocator_t allocator_type;

		enum {
			alignment_size = allocator_type::alignment_size,
			pixel_size = sizeof(pixel_type)
		};

	private:
		pixel_store(const pixel_store&);
		pixel_store& operator=(const pixel_store&);

		const int width;
		const int height;
		const size_t fragment_length;

		typedef std::vector<pixel_type,
							allocator_type > 
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
			const int adjusted_size =
				math::lcm<int>(pixel_size, alignment_size);
			return bytes + (adjusted_size - 1) -
				((bytes + (adjusted_size - 1)) % adjusted_size);
		}

	public:
		pixel_store(const int width_, const int height_):
				width(width_),
				height(height_),
				fragment_length(get_fragment_size(width_ * pixel_size)),
				pixels(fragment_length / pixel_size * height)
		{
			assert (fragment_length >=
					static_cast<size_t>(width_ * pixel_size));
			assert ((fragment_length % pixel_size) == 0);
			assert ((fragment_length % alignment_size) == 0);
		}

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
			assert (x < get_width());
			assert (y < get_height());

			return pixels[y * fragment_length / pixel_size + x];
		}

		const pixel_type& operator()(int x, int y) const
		{
			assert (x < get_width());
			assert (y < get_height());

			return pixels[y * fragment_length / pixel_size + x];
		}

		fragment_type get_fragment(size_t line)
		{
			assert (line < static_cast<size_t>(height));

			const size_t pitch = fragment_length / pixel_size;

			iterator head = this->begin() + pitch * static_cast<const int>(line);
			iterator tail =
				this->begin() + (pitch * (static_cast<const int>(line) + 1));
			return fragment_type(head, tail);
		}

		fragment_type get_fragment(size_t line, int left, int right)
		{
			assert (line < static_cast<size_t>(height));
			assert (left <= right);

			const size_t pitch = fragment_length / pixel_size;

			iterator head = this->begin() + pitch * line + left;
			iterator tail = this->begin() + pitch * line + right;
			return fragment_type(head, tail);
		}			

		const_fragment_type get_fragment(size_t line) const
		{
			assert (line < static_cast<size_t>(height));

			const size_t pitch = fragment_length / pixel_size;

			const_iterator head = this->begin() + pitch * line;
			const_iterator tail = this->begin() + (pitch * (line + 1));
			return const_fragment_type(head, tail);
		}

		const_fragment_type
		get_fragment(size_t line, int left, int right) const
		{
			assert (line < static_cast<size_t>(height));
			assert (left <= right);

			const size_t pitch = fragment_length / pixel_size;

			const_iterator head = this->begin() + pitch * line + left;
			const_iterator tail = this->begin() + pitch * line + right;
			return const_fragment_type(head, tail);
		}

		bool is_inside(int x, int y) const
		{
			if (x < 0 ||
				x >= get_width() ||
				y < 0 ||
				y >= get_height())
				return false;
			return true;
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
