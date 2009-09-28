#ifndef RISA_RENDER_VIEWPORT_HPP_
#define RISA_RENDER_VIEWPORT_HPP_

#include <risa_gl/math/region.hpp>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class viewport
		{
		public:
			typedef value_t value_type;
			typedef risa_gl::math::coordinate<value_type> coord_type;

		private:
			value_type x_offset;
			value_type y_offset;
			value_type x_scale;
			value_type y_scale;

		public:
			viewport(const value_type& x_left,
					 const value_type& y_bottom,
					 const value_type& x_right,
					 const value_type& y_top):
				x_offset(x_left),
				y_offset(y_bottom),
				x_scale((x_right - x_left) / value_type(2)),
				y_scale((y_top - y_bottom) / value_type(2))
			{}

			const value_type& get_x_offset() const
			{
				return x_offset;
			}

			const value_type& get_y_offset() const
			{
				return y_offset;
			}

			const value_type& get_x_scale() const
			{
				return x_scale;
			}

			const value_type& get_y_scale() const
			{
				return y_scale;
			}

			coord_type project(const coord_type& source) const
			{
				return
					coord_type((source.get_x() + value_type(1)) *
								x_scale + x_offset,
							   (source.get_y() + value_type(1)) *
								y_scale + y_offset);
			}
		};
	}
}

#endif /* RISA_RENDER_VIEWPORT_HPP_ */
