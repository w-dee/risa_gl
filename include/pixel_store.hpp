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

		enum 
		{
			pixel_size = sizeof(pixel_t);
		};

	private:
		const int width;
		const int height;
		const int allocate_width;

		std::vector<pixel_t> pixels;

		static size_t get_alignmented_bytes(const int width_)
		{
			return ((width_ * pixel_size) + (alignment - 1)) &
				~(alignment - 1);
		}

		static size_t get_allocate_width(const int width_)
		{
			return (get_alignmented_bytes(width_) + (pixel_size - 1)) &
				~(pixel_size - 1);
		}
	public:
		pixel_store(const int width_, const int height_):
				width(width_),
				height(height_),
				allocate_width(get_allocate_width(width_))
				pixels(get_allocate_width(width_) * height_)
		{}

		~pixel_store()
		{}

		const int width() const
		{
			return width;
		}

		const int height() const
		{
			return height;
		}
	};
}

#endif /* RISA_PIXEL_STORE_HPP_ */
