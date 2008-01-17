#ifndef RISA_INTERPOLATE_HPP_
#define RISA_INTERPOLATE_HPP_

#include <math/vector.hpp>
#include <vector>
#include <cassert>

namespace risa_gl
{
	using math::dividable_vector;
	using math::vector2;

	template <typename PixelStoreType>
	class nearest
	{
	public:
		typedef PixelStoreType pixel_store_type;
		typedef typename pixel_store_type::pixel_type pixel_type;
		typedef vector2 value_type;
		typedef const vector2 const_value_type;
		typedef dividable_vector<vector2> interpolate_type;

	private:
		const pixel_store_type& pixels;
		interpolate_type coordinates;
		const int divides;

		vector2 get_nearest(const float value) const
		{
			value_type coord = coordinates.blend(value);
			return vector2(
				static_cast<float>(static_cast<int>(coord.x + 0.5)),
				static_cast<float>(static_cast<int>(coord.y + 0.5)));
		}
	public:
		nearest(const pixel_store_type& pixels_,
				const_value_type& head,
				const_value_type& tail,
				unsigned short divides_):
			pixels(pixels_),
			coordinates(head, tail),
			divides(divides_)
		{
			assert (divides >= 2);
		}

		nearest(const nearest& src):
			pixels(src.pixels),
			coordinates(src.coordinates),
			divides(src.divides)
		{}

		std::vector<pixel_type> interpolate() const
		{
			std::vector<pixel_type> result(divides);

			result[0] = pixels(static_cast<int>(coordinates.get_source().x),
							   static_cast<int>(coordinates.get_source().y));

			const float jitter = 1.f / (divides - 1);
			float value = jitter;
			for (int offset = 1; offset != divides; ++offset, value += jitter)
			{
				const vector2 axis = get_nearest(value);
				result[offset] = pixels(static_cast<const int>(axis.x),
										static_cast<const int>(axis.y));
			}
			result[divides-1] =
				pixels(static_cast<int>(coordinates.get_target().x),
					   static_cast<int>(coordinates.get_target().y));

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
		const int divides;

	public:
		bilinear(const pixel_store_type& pixels_,
			const_value_type& head,
			const_value_type& tail,
				 int divides_):
			pixels(pixels_),
			coordinates(head, tail),
			divides(divides_)
		{
			assert (divides > 1);
		}

		bilinear(const bilinear& src):
			pixels(src.pixels),
			coordinates(src.coordinates),
			divides(src.divides)
		{}

		pixel_type calculate(const float offset) const
		{
			const float threshold = 0.01f;

			const_value_type coord = coordinates.blend(offset);
			const int u_floor = static_cast<int>(coord.x);
			const int v_floor = static_cast<int>(coord.y);
			const float u_factor = coord.x - u_floor;
			const float v_factor = coord.y - v_floor;

			const float u_opposite = 1.f - u_factor;
			const float v_opposite = 1.f - v_factor;

			const int u_ceil = u_factor < threshold ? u_floor : u_floor + 1;
			const int v_ceil = v_factor < threshold ? v_floor : v_floor + 1;
			
			const pixel_type left_down = pixels(u_floor, v_floor);
			const pixel_type left_up = pixels(u_floor, v_ceil);
			const pixel_type right_down = pixels(u_ceil, v_floor);
			const pixel_type right_up = pixels(u_ceil, v_ceil);

			return 
				(left_up * u_opposite + right_up * u_factor) * v_opposite +
				(left_down * u_opposite + right_down * u_factor) * v_factor;
		}

		std::vector<pixel_type> interpolate() const
		{
			std::vector<pixel_type> result;
			for (int offset = 0.f; offset <= 1.f; offset += 1.f / divides)
				result.push_back(calculate(offset));

			return result;
		}
	};
}
#endif /* RISA_INTERPOLATE_HPP_ */
