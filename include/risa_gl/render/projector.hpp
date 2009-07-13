#ifndef RISA_RENDER_PROJECTOR_HPP_
#define RISA_RENDER_PROJECTOR_HPP_

#include <risa_gl/math/projection.hpp>

namespace risa_gl
{
	namespace render
	{
		using risa_gl::math::projection;

		template <typename value_t>
		class projector
		{
		public:
			typedef value_t value_type;
			typedef projection<value_type> projection_type;
			typedef typename projection_type::vector_type vector_type;
			typedef typename projection_type::vector_source_type vector_source_type;

		private:
			projection_type matrix;

		public:
			projector(const value_type& left,
					  const value_type& right,
					  const value_type& top,
					  const value_type& bottom,
					  const value_type& near,
					  const value_type& far):
				matrix(left, right, top, bottom, near, far)
			{}

			vector_type project(const vector_type& vertex) const
			{
				return vertex * matrix;
			}
		};
	}
}

#endif /* RISA_RENDER_PROJECTOR_HPP_ */

