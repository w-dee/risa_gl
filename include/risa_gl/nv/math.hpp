#ifndef MATH_HPP_
#define MATH_HPP_

#include <cassert>

namespace math
{
	template <typename base_t, base_t min_val, base_t max_val> 
	struct range
	{
		typedef base_t value_type;

		static value_type min()
		{
			return min_val;
		}

		static value_type max()
		{
			return max_val;
		}

		static value_type distance()
		{
			return max() - min();
		}
	};

	template <typename src_range_t, typename dest_range_t>
	struct projector
	{
		typedef typename dest_range_t::value_type result_type;
		typedef typename src_range_t::value_type source_type;

		result_type operator()(source_type value) const
		{
			assert(value >= src_range_t::min());
			assert(value <= src_range_t::max());

			return
				dest_range_t::distance() *
				(value - src_range_t::min()) /
				src_range_t::distance() +
				dest_range_t::min();
		}
	};
}
#endif /* MATH_HPP_ */
