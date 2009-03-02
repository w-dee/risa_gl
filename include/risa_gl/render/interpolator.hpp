#ifndef RISA_RENDER_INTERPOLATOR_HPP_
#define RISA_RENDER_INTERPOLATOR_HPP_

#include <cassert>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t, typename scalar_t = int>
		class interpolator
		{
		public:
			typedef value_t value_type;
			typedef scalar_t scalar_type;

		private:
			const value_type& head;
			const value_type& tail;
			const scalar_type& division;

			value_type stepping;
			
		public:
			interpolator(const value_type& head_,
						 const value_type& tail_,
						 const scalar_type& division_):
				head(head_), tail(tail_),
				division(division_),
				stepping((tail_ - head_) / division_)
			{}

			scalar_type get_division() const
			{
				return division;
			}
				

			value_type interpolate(const scalar_type& step) const
			{
				assert (step < division);

				return head + stepping * step;
			}

			value_type get_stepping() const
			{
				return stepping;
			}
		};
	}
}

#endif /* RISA_RENDER_INTERPOLATOR_HPP_ */

