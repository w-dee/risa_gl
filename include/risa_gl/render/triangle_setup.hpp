#ifndef RISA_RENDER_TRIANGLE_SETUP_HPP_
#define RISA_RENDER_TRIANGLE_SETUP_HPP_

#include <risa_gl/render/xyzw_st_coord.hpp>
#include <risa_gl/render/line.hpp>
#include <risa_gl/render/interpolator.hpp>
#include <algorithm>
#include <stdexcept>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class triangle_setup
		{
		public:
			typedef value_t value_type;
			typedef xyzw_st_coord<value_type> coord_type;

			typedef line<coord_type> line_type;

		private:
			const coord_type* top;
			const coord_type* center;
			const coord_type* bottom;

			line_type* major_line;
			int major_distance;

			line_type* up_line;
			int up_distance;

			line_type* down_line;
			int down_distance;

			bool is_major_left;

		public:
			triangle_setup(const coord_type& p0,
						   const coord_type& p1,
						   const coord_type& p2):
				top(), center(), bottom(),
				major_line(), major_distance(),
				up_line(), up_distance(),
				down_line(), down_distance(),
				is_major_left()
			{
				top = &p0;
				center = &p1;
				bottom = &p2;

				if (center->get_y() < top->get_y())
					std::swap(center, top);

				if (bottom->get_y() < center->get_y())
					std::swap(bottom, center);

				if (center->get_y() < top->get_y())
					std::swap(center, top);

				major_line = new line_type(*top, *bottom);
				up_line = new line_type(*top, *center);
				down_line = new line_type(*center, *bottom);

				major_distance =
					major_line->get_tail().get_y() - major_line->get_head().get_y();
				up_distance =
					up_line->get_tail().get_y() - up_line->get_head().get_y();
				down_distance =
					down_line->get_tail().get_y() - down_line->get_head().get_y();

				const value_type dx =
					major_line->get_tail().get_x() - major_line->get_head().get_x();
				const value_type dy =
					major_line->get_tail().get_y() - major_line->get_head().get_y();

				const value_type distance_y = top->get_y() - center->get_y();
				const value_type check =
					((float)distance_y / dy) * dx + major_line->get_head().get_x();
				is_major_left = check < center->get_x();
			}

			~triangle_setup()
			{
				delete major_line;
				delete up_line;
				delete down_line;
			}

			const int size() const
			{
				return major_distance;
			}

			const std::pair<coord_type, coord_type>
			operator[](value_type y_offset)
			{
				if (y_offset > major_distance)
					throw std::out_of_range("offset is out of range.");

				line_type& major_side = *major_line;
				line_type& minor_side =
					(y_offset < up_distance) ? *up_line : *down_line;
				int minor_distance =
					y_offset < up_distance ? up_distance : down_distance;
				int minor_offset =
					y_offset < up_distance ? y_offset : y_offset - up_distance;

				st_coord_interpolator<value_type>
					interp_major(major_side.get_head(),
								 major_side.get_tail(),
								 major_distance);
				st_coord_interpolator<value_type>
					interp_minor(minor_side.get_head(),
								 minor_side.get_tail(),
								 minor_distance);

				return
					std::make_pair(interp_major.interpolate_value(y_offset),
								   interp_minor.interpolate_value(minor_offset));
			}
		};
	}
}

#endif /* RISA_RENDER_TRIANGLE_SETUP_HPP_ */
