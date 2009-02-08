#ifndef RISA_RENDER_LINE_HPP_
#define RISA_RENDER_LINE_HPP_

#include <risa_gl/math/point.hpp>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class line
		{
		public:
			typedef value_t value_type;
			typedef risa_gl::math::point<value_type> point_type;

		private:
			point_type head;
			point_type tail;

		public:
			line(const point_type& head_, const point_type& tail_):
				head(head_), tail(tail_)
			{}

			value_type get_length() const
			{
				return tail.get_distance(head);
			}

			value_type get_x_length() const
			{
				return tail.get_x() - head.get_x();
			}

			value_type get_y_length() const
			{
				return tail.get_y() - head.get_y();
			}

			value_type get_z_length() const
			{
				return tail.get_z() - head.get_z();
			}

			value_type get_dxdy() const
			{
				return get_x_length() / get_y_length();
			}

			value_type get_dzdy() const
			{
				return get_z_length() / get_y_length();
			}
		};
	}
}

#endif /* RISA_RENDER_LINE_HPP_ */
