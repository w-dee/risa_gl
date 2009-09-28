#ifndef RISA_RENDER_INTERPOLATOR_HPP_
#define RISA_RENDER_INTERPOLATOR_HPP_

#include <cassert>
#include <risa_gl/render/xyzw_st_coord.hpp>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		struct interpolated_values
		{
			value_t s;
			value_t t;
			value_t z;

			interpolated_values(const value_t& s_,
								const value_t& t_,
								const value_t& z_):
				s(s_), t(t_), z(z_)
			{}
		};

		template <typename value_t>
		class st_coord_interpolator
		{
		public:
			typedef value_t value_type;

		private:
			const value_type head_x;
			const value_type head_y;
			value_type delta_x;
			value_type delta_y;

			const value_type& head_s;
			const value_type& head_t;
			const value_type& head_z;
			const value_type& tail_s;
			const value_type& tail_t;
			const value_type& tail_z;

			const value_type& division;
			const value_type inv_division;

			value_type s0z0; // S[0] / Z[0]
			value_type s1z1; // S[1] / Z[1]
			value_type distance_s0z0_s1z1; // S[1] / Z[1] - S[0] / Z[0]
			
			value_type t0z0; // T[0] / Z[0]
			value_type t1z1; // T[1] / Z[1]
			value_type distance_t0z0_t1z1; // T[1] / Z[1] - T[0] / Z[0]
			
			value_type inv_z0; // 1 / Z[0]
			value_type inv_z1; // 1 / Z[1]
			value_type distance_inv_z0_inv_z1; // 1/Z[1] - 1/Z[0]
			
		public:
			st_coord_interpolator(const xyzw_st_coord<value_type>& head,
								  const xyzw_st_coord<value_type>& tail,
								  const value_type& division_):
				head_x(head.get_x()),
				head_y(head.get_y()),

				delta_x((tail.get_x() - head.get_x()) / division_),
				delta_y((tail.get_y() - head.get_y()) / division_),

				head_s(head.get_s()),
				head_t(head.get_t()),
				head_z(head.get_z()),

				tail_s(tail.get_s()),
				tail_t(tail.get_t()),
				tail_z(tail.get_z()),

				division(division_),
				inv_division(1 / division_),

				s0z0(),
				s1z1(),
				distance_s0z0_s1z1(),

				t0z0(),
				t1z1(),
				distance_t0z0_t1z1(),

				inv_z0(),
				inv_z1(),
				distance_inv_z0_inv_z1()
			{
				inv_z0 = 1 / head_z;
				inv_z1 = 1 / tail_z;
				distance_inv_z0_inv_z1 = inv_z1 - inv_z0;

				s0z0 = head_s * inv_z0;
				s1z1 = tail_s * inv_z1;
				distance_s0z0_s1z1 = s1z1 - s0z0;

				t0z0 = head_t * inv_z0;
				t1z1 = tail_t * inv_z1;
				distance_t0z0_t1z1 = t1z1 - t0z0;
			}

			value_type get_division() const
			{
				return division;
			}
				

			interpolated_values<value_type>
			interpolate(const value_type& step) const
			{
				assert (step <= division);

				const value_type s = step * inv_division;

				const value_type z_s =
					1 / (inv_z0 + s * distance_inv_z0_inv_z1);

				return
					interpolated_values<value_type>
					((s0z0 + s * distance_s0z0_s1z1) * z_s,
					 (t0z0 + s * distance_t0z0_t1z1) * z_s,
					 z_s);
			}

			xyzw_st_coord<value_type>
			interpolate_value(const value_type& step) const
			{
				interpolated_values<value_type> stz = interpolate(step);

				return xyzw_st_coord<value_type>(head_x + step * delta_x,
												 head_y + step * delta_y,
												 stz.z,
												 1,
												 stz.s,
												 stz.t);
			}
		};
	}
}

#endif /* RISA_RENDER_INTERPOLATOR_HPP_ */

