#ifndef RISA_INTERPOLATE_HPP_
#define RISA_INTERPOLATE_HPP_

#include <math/vector.hpp>
#include <vector>

namespace risa_gl
{
	using math::dividable_vector;

	template <typename PixelStoreType>
	class nearest
	{
	public:
		typedef typename PixelStoreType::pixel_type pixel_type;
		typedef math::vector2 value_type;
		typedef const math::vector2 const_value_type;
		typedef dividable_vector<math::vector2> interpolate_type;

	private:
		const pixel_type& pixels;
		interpolate_type coordinates;

		math::vector2 get_nearest(const math::vector2& coord) const
		{
			return math::vector2(
				static_cast<float>(static_cast<int>(coord.x + 0.5)),
				static_cast<float>(static_cast<int>(coord.y + 0.5)));
		}
	public:
		nearest(const pixel_type& pixels_,
				const_value_type& head,
				const_value_type& tail,
				int divides):
			pxiels(pixels_),
			coordinates(head, tail)
		{}

		nearest(const nearest& src):
			pixels(src.pixels)
			coordinates(src.coordinates)
		{}

		std::vector<pixel_type> interpolate() const
		{
			std::vector<pixel_type> result(divides);

			for (int offset = 0; offset != divides; ++offset)
				result.push_back(
					get_nearest(static_cast<float>(offset) / divides));

			return result;
		}
	};

	template <typename PixelStoreType>
	class bilinear
	{
	public:
		typedef PixelStoreType pixel_store_type;
		typedef typename PixelStoreType::pixel_type pixel_type;
		typedef vector2 value_type;
		typedef const vector2 const_value_type;
		typedef dividable_vector<vector2> interpolate_type;

	private:
		const pixel_store_type& pixels;
		interpolate_type coordinates;

	public:
		bilinear(const pixel_store_type& pixels_,
			const_value_type& head,
			const_value_type& tail,
				 int divides):
			pixels(pixels_),
			coordinates(head, tail)
		{}

		bilinear(const bilinear& src):
			pixels(pixels_),
			coordinates(src.coordinates)
		{}


		pixel_type calculate(const pixel_type& left_up,
							 const pixel_type& right_up,
							 const pixel_type& left_down,
							 const pixel_type& right_down,
							 const float u_wait,
							 const float v_wait) const
		{
			const float u_opposite = 1.f - u_wait;
			const float v_opposite = 1.f - v_wait;

			return 
				(left_up * u_opposite + right_up * u_wait) * v_opposite +
				(left_down * u_opposite + right_down * u_wait) * v_wait;
		}

		/**
		 * out of rangeなpixelを参照しなければならない補間をどう扱う？
		 */
		std::vector<pixel_type> interpolate() const
		{
			std::vector<pixel_type> result;
			for (int offset = 0; offset != divides; ++offset)
			{
				const_value_type coord =
					coordinates.blend(static_cast<float>(offset) / divides);

				typedef math::coordinate<int> coordinate_t;
				const coordinate_t left_up = coordinate_t(coord.x, coord.y);
				
				result.push_back(
					calculate(pixels(left_up.get_x(), left_up.get_y()),
							  pixels(left_up.get_x()+1, left_up.get_y()),
							  pixels(left_up.get_x(), left_up.get_y()+1),
							  pixels(left_up.get_x()+1, left_up.get_y()+1),
							  coord.x - static_cast<float>(left_up.get_x()),
							  coord.y - static_cast<float>(left_up.get_y())));
			}

			return result;
		}
	
	};
}
#endif /* RISA_INTERPOLATE_HPP_ */
