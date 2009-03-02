#ifndef RISA_RENDER_XYZ_ST_COORD_HPP_
#define RISA_RENDER_XYZ_ST_COORD_HPP_

#include <risa_gl/math/point.hpp>
#include <ostream>

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class xyz_st_coord
		{
		public:
			typedef value_t value_type;

		private:
			value_type x;
			value_type y;
			value_type z;
			value_type s;
			value_type t;

		public:
			xyz_st_coord():
				x(), y(), z(),
				s(), t()
			{}

			xyz_st_coord(const value_type& x_,
						 const value_type& y_,
						 const value_type& z_,
						 const value_type& s_,
						 const value_type& t_):
				x(x_), y(y_), z(z_),
				s(s_), t(t_)
			{}

			xyz_st_coord(const xyz_st_coord& src):
				x(src.x), y(src.y), z(src.z),
				s(src.s), t(src.t)
			{}


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

			const value_type& get_s() const
			{
				return s;
			}

			const value_type& get_t() const
			{
				return t;
			}

			xyz_st_coord& operator+=(const xyz_st_coord& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				s += rhs.s;
				t += rhs.t;
				return *this;
			}

			xyz_st_coord operator+(const xyz_st_coord& rhs) const
			{
				return xyz_st_coord(*this) += rhs;
			}

			xyz_st_coord& operator-=(const xyz_st_coord& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				s -= rhs.s;
				t -= rhs.t;
				return *this;
			}

			xyz_st_coord& operator-(const xyz_st_coord& rhs) const
			{
				return xyz_st_coord(*this) -= rhs;
			}

			xyz_st_coord& operator*=(const value_type& rhs)
			{
				x *= rhs.x;
				y *= rhs.y;
				z *= rhs.z;
				s *= rhs.s;
				t *= rhs.t;
				return *this;
			}

			xyz_st_coord& operator*(const value_type& rhs) const
			{
				return xyz_st_coord(*this) *= rhs;
			}

			xyz_st_coord& operator/=(const value_type& rhs)
			{
				x /= rhs.x;
				y /= rhs.y;
				z /= rhs.z;
				s /= rhs.s;
				t /= rhs.t;
				return *this;
			}

			xyz_st_coord& operator/(const value_type& rhs) const
			{
				return xyz_st_coord(*this) /= rhs;
			}

			bool operator==(const xyz_st_coord& rhs) const
			{
				return
					x == rhs.x &&
					y == rhs.y &&
					z == rhs.z &&
					s == rhs.s &&
					t == rhs.t;
			}

			bool operator!=(const xyz_st_coord& rhs) const
			{
				return !(*this == rhs);
			}

			friend std::ostream&
			operator<<(std::ostream& out, const xyz_st_coord& rhs)
			{
				out << "(" <<
					rhs.get_x() << ", " <<
					rhs.get_y() << ", " <<
					rhs.get_z() << ", " <<
					rhs.get_s() << ", " <<
					rhs.get_t() << ")";

				return out;
			}
		};
	}
}
#endif /* RISA_RENDER_XYZ_ST_COORD_HPP_ */
