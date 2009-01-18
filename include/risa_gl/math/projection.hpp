#ifndef RISA_MATH_PRJECTIION_HPP_
#define RISA_MATH_PRJECTIION_HPP_

#include <risa_gl/math/matrix.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		class projection
		{
			typedef value_t value_type;

		public:
			typedef matrix<value_type, 1, 4> vector_type;
			typedef typename vector_type::elements_type vector_source_type;

		private:
			typedef matrix<value_type, 4, 4> matrix_type;
			typedef typename matrix_type::elements_type matrix_source_type;

			matrix_type projection_matrix;

			static matrix_source_type
			get_projection_source(const value_type& left,
								  const value_type& right,
								  const value_type& bottom,
								  const value_type& top,
								  const value_type& near,
								  const value_type& far)
			{
				const value_type wide_distance = right - left;
				const value_type wide_center = right + left;

				const value_type height_distance = top - bottom;
				const value_type height_center = top + bottom;

				const value_type depth_distance = far - near;
				const value_type depth_center = far + near;

				const value_type wide_ratio = wide_center / wide_distance;
				const value_type height_ratio = height_center / height_distance;
				const value_type depth_ratio = depth_center / depth_distance;
				
				matrix_source_type result = {{
						2.f * near / wide_distance, 0.f, 0.f, 0.f,
						0.f, 2.f * near / height_distance, 0.f, 0.f,
						wide_ratio, height_ratio, - depth_ratio, -1.f,
						0.f, 0.f, -2.f * far * near / depth_distance, 0.f }};

				return result;
			}

		public:
			projection(const value_type& left, const value_type& right,
					   const value_type& bottom, const value_type& top,
					   const value_type& near, const value_type& far):
				projection_matrix(get_projection_source(left, right,
														bottom, top,
														near, far))
			{}

			~projection()
			{}

			matrix_type get_projection_matrix() const
			{
				return projection_matrix;
			}

		};

		template <typename projection_type>
		static typename projection_type::vector_type
		operator*(const typename projection_type::vector_type& lhs,
				  const projection_type& rhs)
		{
			return lhs * rhs.get_projection_matrix();
		}
	}
}

#endif /* RISA_MATH_PRJECTIION_HPP_ */
