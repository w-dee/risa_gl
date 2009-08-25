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
		class xyzw_st_coord_interpolator
		{
		public:
			typedef value_t value_type;

		private:
			const xyzw_st_coord<value_type>& head;
			const xyzw_st_coord<value_type>& tail;

			const value_type& division;
			const value_type inv_division;

			const value_type s0z0; // S[0] / Z[0]
			const value_type s1z1; // S[1] / Z[1]
			const value_type distance_s0z0_s1z1; // S[1] / Z[1] - S[0] / Z[0]
			const value_type t0z0; // T[0] / Z[0]
			const value_type t1z1; // T[1] / Z[1]
			const value_type distance_t0z0_t1z1; // T[1] / Z[1] - T[0] / Z[0]
			const value_type inv_z0; // 1 / Z[0]
			const value_type inv_z1; // 1 / Z[1]
			const value_type distance_inv_z0_inv_z1; // 1/Z[1] - 1/Z[0]
			
		public:
			xyzw_st_coord_interpolator(const xyzw_st_coord<value_type>& head_,
									   const xyzw_st_coord<value_type>& tail_,
									   const value_type& division_):
				head(head_), tail(tail_),

				division(division_),
				inv_division(1 / division_),

				s0z0(head_.get_s() / head_.get_z()),
				s1z1(tail_.get_s() / tail_.get_z()),
				distance_s0z0_s1z1(tail_.get_s() / tail_.get_z() -
								   head_.get_s() / head_.get_z()),

				t0z0(head_.get_t() / head_.get_z()),
				t1z1(tail_.get_t() / tail_.get_z()),
				distance_t0z0_t1z1(tail_.get_t() / tail_.get_z() -
								   head_.get_t() / head_.get_z()),

				inv_z0(1 / head_.get_z()),
				inv_z1(1 / tail_.get_z()),
				distance_inv_z0_inv_z1(1 / tail_.get_z() - 1 / head_.get_z())
			{}

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
		};
	}
}

#endif /* RISA_RENDER_INTERPOLATOR_HPP_ */

