#ifndef RISA_INTERPOLATE_HPP_
#define RISA_INTERPOLATE_HPP_

#include <math/vector.hpp>
#include <risa_types.hpp>
#include <allocator.hpp>
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
		typedef std::vector<pixel_type,
							aligned_allocator<
								pixel_type,
								pixel_store_type::alignment_size> >
		pixel_vector_type;

	private:
		const pixel_store_type& pixels;
		interpolate_type coordinates;
		const int divides;
		const pixel_type default_color;

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
				unsigned short divides_,
				const pixel_type& default_color_ = pixel_type()):
			pixels(pixels_),
			coordinates(head, tail),
			divides(divides_),
			default_color(default_color_)
		{
			assert (divides >= 2);
		}

		nearest(const nearest& src):
			pixels(src.pixels),
			coordinates(src.coordinates),
			divides(src.divides),
			default_color(src.default_color)
		{}

		pixel_vector_type interpolate() const
		{
			pixel_vector_type result(divides);

			const float jitter = 1.f / (divides - 1);
			float value = 0.f;
			for (int offset = 0; offset != (divides - 1);
				 ++offset, value += jitter)
			{
				const vector2 axis = get_nearest(value);
				if (pixels.is_inside(static_cast<const int>(axis.x),
									 static_cast<const int>(axis.y)))
					result[offset] = pixels(static_cast<const int>(axis.x),
											static_cast<const int>(axis.y));
				else
					result[offset] = default_color;
			}
			if (pixels.is_inside(static_cast<int>(coordinates.get_target().x),
								 static_cast<int>(coordinates.get_target().y)))
				result[divides-1] =
					pixels(static_cast<int>(coordinates.get_target().x),
						   static_cast<int>(coordinates.get_target().y));
			else
				result[divides-1] = default_color;

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
		typedef std::vector<pixel_type,
							aligned_allocator<
								pixel_type,
								pixel_store_type::alignment_size> > 
		pixel_vector_type;

	private:
		const pixel_store_type& pixels;
		interpolate_type coordinates;
		const int divides;
		pixel_type default_color;

		float channel_blend(const float channel1,
							const float factor,
							const float channel2,
							const float opposite) const
		{
			return channel1 * factor + channel2 * opposite;
		}

		pixel_type blend(const pixel_type& left_down,
						 const pixel_type& left_up,
						 const pixel_type& right_down,
						 const pixel_type& right_up,
						 const float u_factor,
						 const float v_factor) const
		{
			const float u_opposite = 1.f - u_factor;
			const float v_opposite = 1.f - v_factor;
			assert (u_factor + u_opposite <= 1.f);
			assert (v_factor + v_opposite <= 1.f);

			return pixel_type(
				static_cast<risa_gl::byte>(
					channel_blend(left_up.get_red(),
								  u_opposite,
								  right_up.get_red(),
								  u_factor) * v_factor +
					channel_blend(left_down.get_red(),
								  u_opposite,
								  right_down.get_red(),
								  u_factor) * v_opposite),
				static_cast<risa_gl::byte>(
					channel_blend(left_up.get_green(),
								  u_opposite,
								  right_up.get_green(),
								  u_factor) * v_factor +
					channel_blend(left_down.get_green(),
								  u_opposite,
								  right_down.get_green(),
								  u_factor) * v_opposite),
				static_cast<risa_gl::byte>(
					channel_blend(left_up.get_blue(),
								  u_opposite,
								  right_up.get_blue(),
								  u_factor) * v_factor +
					channel_blend(left_down.get_blue(),
								  u_opposite,
								  right_down.get_blue(),
								  u_factor) * v_opposite),
				static_cast<risa_gl::byte>(
					channel_blend(left_up.get_alpha(),
								  u_opposite,
								  right_up.get_alpha(),
								  u_factor) * v_factor +
					channel_blend(left_down.get_alpha(),
								  u_opposite,
								  right_down.get_alpha(),
								  u_factor) * v_opposite));
		}

		pixel_type calculate(const float offset) const
		{
			const float threshold = 0.0001f;

			const_value_type coord = coordinates.blend(offset);
			const int u_floor = static_cast<int>(coord.x);
			const int v_floor = static_cast<int>(coord.y);
			const float u_factor = coord.x - u_floor;
			const float v_factor = coord.y - v_floor;
			const int u_ceil = u_factor < threshold ? u_floor : u_floor + 1;
			const int v_ceil = v_factor < threshold ? v_floor : v_floor + 1;
			
			const pixel_type left_down =
				pixels.is_inside(u_floor, v_floor) ?
				pixels(u_floor, v_floor) : default_color;
			const pixel_type left_up =
				pixels.is_inside(u_floor, v_ceil) ?
				pixels(u_floor, v_ceil) : default_color;
			const pixel_type right_down =
				pixels.is_inside(u_ceil, v_floor) ?
				pixels(u_ceil, v_floor) : default_color;
			const pixel_type right_up =
				pixels.is_inside(u_ceil, v_ceil) ?
				pixels(u_ceil, v_ceil) : default_color;

			return blend(left_down, left_up,
						 right_down, right_up,
						 u_factor, v_factor);
		}

	public:
		bilinear(const pixel_store_type& pixels_,
				 const_value_type& head,
				 const_value_type& tail,
				 int divides_,
				 const pixel_type& default_color_ = pixel_type()):
			pixels(pixels_),
			coordinates(head, tail),
			divides(divides_),
			default_color(default_color_)
		{
			assert (divides >= 2);
		}

		bilinear(const bilinear& src):
			pixels(src.pixels),
			coordinates(src.coordinates),
			divides(src.divides),
			default_color(src.default_color)
		{}

		pixel_vector_type interpolate() const
		{
			pixel_vector_type result(divides);

			const float jitter = 1.f / divides;
			float index = 0.f;

			for (int offset = 0; offset != (divides - 1);
				 ++offset, index += jitter)
				result[offset] = calculate(index);

			result[divides-1] =
				pixels(static_cast<const int>(coordinates.get_target().x),
					   static_cast<const int>(coordinates.get_target().y));

			return result;
		}
	};
}

#endif /* RISA_INTERPOLATE_HPP_ */
