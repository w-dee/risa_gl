#ifndef RISA_RENDER_TRIANGLE_SETUP_HPP_
#define RISA_RENDER_TRIANGLE_SETUP_HPP_

#include <risa_gl/render/xyzw_st_coord.hpp>
#include <risa_gl/render/line.hpp>
#include <risa_gl/math/linear_interpolator.hpp>
#include <risa_gl/utility/compose.hpp>
#include <algorithm>
#include <functional>
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
			const coord_type top;
			const coord_type center;
			const coord_type bottom;

			line_type major_line;
			int major_distance;

			line_type up_line;
			int up_distance;

			line_type down_line;
			int down_distance;


			struct y_picker
			{
				typename coord_type::value_type
				operator()(const coord_type& obj) const
				{
					return obj.get_y();
				}
			};

			const std::vector<coord_type>
			sorted_points(const coord_type& p0,
						  const coord_type& p1,
						  const coord_type& p2) const
			{
				std::vector<coord_type> coords;
				coords.push_back(p0);
				coords.push_back(p1);
				coords.push_back(p2);

				using risa_gl::utility::compose;
				std::sort(coords.begin(),
						  coords.end(),
						  compose::compose2<
							  typename coord_type::value_type>
						  (std::less<typename coord_type::value_type>(),
						   y_picker(), y_picker()));
				return coords;
			}

			coord_type get_top(const coord_type& p0,
									 const coord_type& p1,
									 const coord_type& p2) const
			{
				return sorted_points(p0, p1, p2)[0];
			}

			coord_type get_center(const coord_type& p0,
									 const coord_type& p1,
									 const coord_type& p2) const
			{
				return sorted_points(p0, p1, p2)[1];
			}

			coord_type get_bottom(const coord_type& p0,
										const coord_type& p1,
										const coord_type& p2) const
			{
				return sorted_points(p0, p1, p2)[2];
			}


		public:
			triangle_setup(const coord_type& p0,
						   const coord_type& p1,
						   const coord_type& p2):
				top(get_top(p0, p1, p2)),
				center(get_center(p0, p1, p2)),
				bottom(get_bottom(p0, p1, p2)),

				major_line(top, center),
				major_distance(),

				up_line(top, center),
				up_distance(),

				down_line(top, center),
				down_distance()
			{
				major_line = line_type(top, bottom);
				up_line = line_type(top, center);
				down_line = line_type(center, bottom);

				y_picker picker;
				up_distance = picker(top) - picker(center);
				down_distance = picker(center) - picker(bottom);
				major_distance = picker(top) - picker(bottom);

				assert(major_distance == up_distance + down_distance);
			}

			~triangle_setup()
			{
			}

			const int size() const
			{
				return major_distance;
			}

			const std::pair<coord_type, coord_type>
			operator[](value_type y_offset)
			{
				return
					std::make_pair(coord_type(), coord_type());
								   
			}
		};
	}
}

#endif /* RISA_RENDER_TRIANGLE_SETUP_HPP_ */
