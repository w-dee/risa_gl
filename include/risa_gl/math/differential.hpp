#ifndef RISA_DIFFERENTIAL_HPP_
#define RISA_DIFFERENTIAL_HPP_

#include <risa_gl/math/region.hpp>
#include <vector>
#include <map>

namespace risa_gl
{
	namespace math
	{
		template <typename ValueType>
		class differential
		{
		public:
			typedef ValueType value_type;
			typedef coordinate<value_type> coordinate_type;
			typedef std::vector<coordinate_type> coordinates_type;
		private:
			value_type x_difference;
			value_type y_difference;

		public:
			differential(const value_type& x_diff,
						 const value_type& y_diff):
				x_difference(x_diff),
				y_difference(y_diff)
			{}

			differential(const coordinate_type& coord):
				x_difference(coord.get_x()),
				y_difference(coord.get_y())
			{}

			coordinates_type
			get_coordinates(const coordinate_type& base,
						   size_t quantum) const
			{
				coordinates_type result(quantum);
				
				for (int offset = 0; offset != quantum; ++offset)
					result[offset] =
						coordinate_type(base.get_x() + x_difference * offset,
										base.get_y() + y_difference * offset);

				return result;
			}

			coordinates_type
			get_half_adjust_coordinates(const coordinate_type& base,
										size_t quantum) const
			{
				coordinates_type result(quantum);
				
				for (int offset = 0; offset != quantum; ++offset)
					result[offset] =
						coordinate_type(
							static_cast<int>(
								base.get_x() + x_difference * offset + .5),
							static_cast<int>(
								base.get_y() + y_difference * offset + .5));

				return result;
			}
		};
	}
}
#endif /* RISA_DIFFERENTIAL_HPP_ */

