#ifndef RISA_MATH_LINEAR_INTERPOLATOR_HPP_
#define RISA_MATH_LINEAR_INTERPOLATOR_HPP_

#include <cassert>

namespace risa_gl
{
	namespace math
	{
		/**
		 * see also
		 * http://bit.ly/f09wKb
		 */
		template <typename value_t>
		class linear_interpolator
		{
		public:
			typedef value_t value_type;

		private:
			const value_type head;
			const value_type inv_head_divisor;
			const value_type head_value;
			const value_type tail;
			const value_type inv_tail_divisor;
			const value_type tail_value;

			value_type compute_center_divisor(const value_type center,
											  const value_type s) const
			{
				assert(head <= center);
				assert(center <= tail);

				/**
				 * 1/(1/z_0+s*(1/z_1-1/z_0))
				 */
				const value_type z_t =
					static_cast<value_type>(1) / 
					(inv_head_divisor +
					 s * (inv_tail_divisor - inv_head_divisor));

				return z_t;
			}
		public:
			linear_interpolator(const value_type head_,
								const value_type head_divisor_,
								const value_type head_value_,
								const value_type tail_,
								const value_type tail_divisor_,
								const value_type tail_value_):
				head(head_),
				inv_head_divisor(static_cast<value_type>(1) / head_divisor_),
				head_value(head_value_),
				tail(tail_),
				inv_tail_divisor(static_cast<value_type>(1) / tail_divisor_),
				tail_value(tail_value_)
			{}

			value_type interpolate(const value_type center) const
			{
				assert(head <= center);
				assert(center <= tail);

				const value_type s =
					(center - head) / (tail - head);

				const value_type center_divisor =
					compute_center_divisor(center, s);

				/**
				 * (i_0/z_0+s*(i_1/z_1-i_0/z_0)) * z_t
				 */
				const value_type result_value =
					((head_value * inv_head_divisor) + 
					s * (tail_value * inv_tail_divisor -
						 head_value * inv_head_divisor)) *
					center_divisor;

				return result_value;
			}
		};
	}
}

#endif /* RISA_MATH_LINEAR_INTERPOLATOR_HPP_ */
