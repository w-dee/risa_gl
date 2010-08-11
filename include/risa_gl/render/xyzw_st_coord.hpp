#ifndef RISA_RENDER_XYZW_ST_COORD_HPP_
#define RISA_RENDER_XYZW_ST_COORD_HPP_

#include <risa_gl/math/point.hpp>
#include <ostream>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class xyzw_st_coord
		{
		public:
			typedef value_t value_type;

		private:
			value_type x;
			value_type y;
			value_type z;
			value_type w;
			value_type s;
			value_type t;

		public:
			xyzw_st_coord():
				x(), y(), z(), w(1),
				s(), t()
			{}

			xyzw_st_coord(const value_type& x_,
						  const value_type& y_,
						  const value_type& z_,
						  const value_type& w_,
						  const value_type& s_,
						  const value_type& t_):
				x(x_), y(y_), z(z_), w(w_),
				s(s_), t(t_)
			{}

			xyzw_st_coord(const xyzw_st_coord& src):
				x(src.x), y(src.y), z(src.z), w(src.w),
				s(src.s), t(src.t)
			{}

			xyzw_st_coord& operator=(const xyzw_st_coord& rhs)
			{
				this->x = rhs.x;
				this->y = rhs.y;
				this->z = rhs.z;
				this->w = rhs.w;
				this->s = rhs.s;
				this->t = rhs.t;

				return *this;
			}


			const value_type& get_x() const
			{
				return x;
			}

			const value_type& get_y() const
			{
				return y;
			}

			const value_type& get_z() const
			{
				return z;
			}

			const value_type& get_w() const
			{
				return w;
			}

			const value_type& get_s() const
			{
				return s;
			}

			const value_type& get_t() const
			{
				return t;
			}

			bool is_w_zero() const
			{
				return w == 0;
			}

			xyzw_st_coord& normalize()
			{
				if (!is_w_zero())
				{
					this->x /= w;
					this->y /= w;
					this->z /= w;
					this->s /= w;
					this->t /= w;
					this->w = 1;
				}

				return *this;
			}

			xyzw_st_coord to_normalize() const
			{
				xyzw_st_coord result(*this);
				result.normalize();
				return result;
			}

			xyzw_st_coord& operator+=(const xyzw_st_coord& rhs)
			{
				const value_type lhs_w = this->w;
				const value_type rhs_w = rhs.w;

				(*this) *= rhs_w;

				x += rhs.x * lhs_w;
				y += rhs.y * lhs_w;
				z += rhs.z * lhs_w;
				s += rhs.s * lhs_w;
				t += rhs.t * lhs_w;
				w = lhs_w * rhs_w;

				return *this;
			}

			xyzw_st_coord operator+(const xyzw_st_coord& rhs) const
			{
				return xyzw_st_coord(*this) += rhs;
			}

			xyzw_st_coord& operator-=(const xyzw_st_coord& rhs)
			{
				const value_type lhs_w = this->w;
				const value_type rhs_w = rhs.w;

				(*this) *= rhs_w;

				x -= rhs.x * lhs_w;
				y -= rhs.y * lhs_w;
				z -= rhs.z * lhs_w;
				s -= rhs.s * lhs_w;
				t -= rhs.t * lhs_w;
				w = lhs_w * rhs_w;

				return *this;
			}

			xyzw_st_coord operator-(const xyzw_st_coord& rhs) const
			{
				return xyzw_st_coord(*this) -= rhs;
			}

			xyzw_st_coord& operator*=(const value_type& rhs)
			{
				x *= rhs;
				y *= rhs;
				z *= rhs;
				s *= rhs;
				t *= rhs;
				return *this;
			}

			xyzw_st_coord operator*(const value_type& rhs) const
			{
				return xyzw_st_coord(*this) *= rhs;
			}

			xyzw_st_coord& operator/=(const value_type& rhs)
			{
				x /= rhs.x;
				y /= rhs.y;
				z /= rhs.z;
				s /= rhs.s;
				t /= rhs.t;
				return *this;
			}

			xyzw_st_coord operator/(const value_type& rhs) const
			{
				return xyzw_st_coord(*this) /= rhs;
			}

			bool operator==(const xyzw_st_coord& rhs_) const
			{
				const xyzw_st_coord lhs = this->to_normalize();
				const xyzw_st_coord rhs = rhs_.to_normalize();

				return
					lhs.x == rhs.x &&
					lhs.y == rhs.y &&
					lhs.z == rhs.z &&
					lhs.s == rhs.s &&
					lhs.t == rhs.t;
			}

			bool operator!=(const xyzw_st_coord& rhs) const
			{
				return !(*this == rhs);
			}

			friend std::ostream&
			operator<<(std::ostream& out, const xyzw_st_coord& rhs)
			{
				out << "(" <<
					rhs.get_x() << ", " <<
					rhs.get_y() << ", " <<
					rhs.get_z() << ", " <<
					rhs.get_w() << ", " <<
					rhs.get_s() << ", " <<
					rhs.get_t() << ")";

				return out;
			}
		};
	}
}
#endif /* RISA_RENDER_XYZW_ST_COORD_HPP_ */
