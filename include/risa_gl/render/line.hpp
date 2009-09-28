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

		private:
			value_type head;
			value_type tail;

		public:
			line(const value_type& head_, const value_type& tail_):
				head(head_), tail(tail_)
			{}

			const value_type& get_head() const
			{
				return head;
			}

			const value_type& get_tail() const
			{
				return tail;
			}
		};
	}
}

#endif /* RISA_RENDER_LINE_HPP_ */
