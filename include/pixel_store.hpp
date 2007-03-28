#ifndef RISA_PIXEL_STORE_HPP_
#define RISA_PIXEL_STORE_HPP_

#include <vector>

namespace risa_gl
{
	template <typename pixel_type, size_t alignment = 8>
	class pixel_store
	{
	public:
		typedef pixel_type pixel_t;
		enum {
			alignment_size = alignment,
			pixel_size = sizeof(pixel_type)
		};

	private:
		const int width;
		const int height;
		const int fragment_length;

		std::vector<pixel_t> pixels;

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

		pixel_t& operator()(int x, int y)
		{
			return pixels[y * fragment_length / pixel_size + x];
		}

		const pixel_t& operator()(int x, int y) const
		{
			return pixels[y * fragment_length / pixel_size + x];
		}

	};
};

#endif /* RISA_PIXEL_STORE_HPP_ */
