#ifndef RISA_RENDER_RASTER_HPP_
#define RISA_RENDER_RASTER_HPP_

#include <risa_gl/render/interpolator.hpp>
#include <risa_gl/math/util.hpp>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class raster
		{
		public:
			typedef value_t value_type;
			typedef xyzw_st_coord<value_type> coord_type;
			typedef st_coord_interpolator<value_type> interpolator_type;

		private:
			coord_type head;
			coord_type tail;
			interpolator_type interpolator;
			value_type least_min;

			value_type get_least_min(const value_type& value) const
			{
				using risa_gl::math::util;
				const int ceil_value = util::ceil(value);
				const value_type distance = ceil_value - value;

				const value_type offset = static_cast<value_type>(0.5);
				return ceil_value + ((distance * 2 > 1) ? -offset : offset);

			}

		public:
			raster(const coord_type& head_, const coord_type& tail_):
				head(head_), tail(tail_),
				interpolator(head_, tail_, tail_.get_x() - head_.get_x()),
				least_min(get_least_min(head_.get_x()))
			{
				assert (head.get_x() <= tail.get_x());
			}

			raster(const raster& src):
				head(src.head), tail(src.tail),
				interpolator(src.interpolator),
				least_min(src.least_min)
			{}

			value_type get_start() const
			{
				return least_min;
			}

			value_type get_limit() const
			{
				return tail.get_x();
			}

			int get_distance() const
			{
				return static_cast<int>(get_limit() - get_start());
			}



			coord_type operator[](int offset) const
			{
				assert (offset < interpolator.get_division());

				const value_type pos = offset + get_start() - head.get_x();
				assert (pos < get_limit() - head.get_x());

				return interpolator.interpolate_value(pos);
			}
		};
	}
}


#endif /* RISA_RENDER_RASTER_HPP_ */
