#ifndef RISA_VECTOR_HPP_
#define RISA_VECTOR_HPP_

#include <ostream>
#include <cmath>
#include <cassert>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		struct vector2
		{
			typedef value_t value_type;

			vector2(const value_type x_, const value_type y_):
				x(x_), y(y_)
			{}

			vector2(const vector2& src):
				x(src.x), y(src.y)
			{}

			vector2():
				x(), y()
			{}

			value_type x;
			value_type y;

			vector2 operator+(const vector2& rhs) const
			{
				return vector2(x + rhs.x, y + rhs.y);
			}

			vector2 operator*(const value_type factor) const
			{
				return vector2(x * factor, y * factor);
			}

			vector2 operator-() const
			{
				return vector2(-x, -y);
			}

			vector2 operator-(const vector2& rhs) const
			{
				return vector2(x - rhs.x, y - rhs.y);
			}

			vector2 operator/(const value_type factor) const
			{
				return vector2(x / factor, y / factor);
			}

			bool operator==(const vector2& rhs) const
			{
				return x == rhs.x && y == rhs.y;
			}

			friend std::ostream& operator<<(std::ostream& out,
											const vector2& self)
			{
				return out << "(" <<
					self.x << ", " <<
					self.y << ")";
			}

			vector2 get_norm() const
			{
				value_type length = std::sqrt(x * x + y * y);
				return vector2(x/length, y/length);
			}
		};

		template <typename value_t>
		struct vector3 : public vector2<value_t>
		{
			typedef value_t value_type;
			typedef vector2<value_type> super_type;
			
			vector3(const value_type x_,
					const value_type y_,
					const value_type z_):
				vector2<value_t>(x_, y_), z(z_)
			{}

			value_type z;

			vector3 operator+(const vector3& rhs) const
			{
				return vector3(super_type::x + rhs.x,
							   super_type::y + rhs.y,
							   z + rhs.z);
			}

			vector3 operator*(const value_type factor) const
			{
				return vector3(super_type::x * factor,
							   super_type::y * factor,
							   z * factor);
			}

			vector3 operator-() const
			{
				return vector3(-super_type::x,
							   -super_type::y,
							   -z);
			}

			vector3 operator-(const vector3& rhs) const
			{
				return vector3(super_type::x - rhs.x,
							   super_type::y - rhs.y,
							   z - rhs.z);
			}

			vector3 operator/(const value_type factor) const
			{
				return vector3(super_type::x / factor,
							   super_type::y / factor,
							   z / factor);
			}

			bool operator==(const vector3& rhs) const
			{
				return super_type::x == rhs.x && 
					super_type::y == rhs.y && z == rhs.z;
			}

			friend std::ostream& operator<<(std::ostream& out,
											const vector3& self)
			{
				return out << "(" <<
					self.x << ", " <<
					self.y << ", " <<
					self.z << ")";
			}

			vector3 get_norm() const
			{
				value_type length =
					std::sqrt(super_type::x * super_type::x +
							  super_type::y * super_type::y +
							  z * z);
				return vector3(super_type::x/length,
							   super_type::y/length,
							   z/length);
			}
		};

		/**
		 * todo 名前がvector4なのに中身が同次座標系のvector4になってる
		 * ので要修正
		 */
		template <typename value_t>
		struct vector4 : public vector3<value_t>
		{
			typedef value_t value_type;
			typedef vector3<value_type> super_type;

			vector4(const value_type x_, const value_type y_,
					const value_type z_, const value_type w_):
				vector3<value_t>(x_, y_, z_), w(w_)
			{}

			value_type w;

			vector4 operator+(const vector4& rhs) const
			{
				return vector4(super_type::x/w + rhs.x/rhs.w,
							   super_type::y/w + rhs.y/rhs.w,
							   super_type::z/w + rhs.z/rhs.w,
							   value_type(1));
			}

			vector4 operator*(const value_type factor) const
			{
				return vector4(super_type::x * factor,
							   super_type::y * factor,
							   super_type::z * factor,
							   w);
			}

			vector4 operator-() const
			{
				return vector4(-super_type::x,
							   -super_type::y,
							   -super_type::z,
							   w);
			}

			vector4 operator-(const vector4& rhs) const
			{
				return vector4(super_type::x/w - rhs.x/rhs.w,
							   super_type::y/w - rhs.y/rhs.w,
							   super_type::z/w - rhs.z/rhs.w,
							   value_type(1));
			}

			vector4 operator/(const value_type factor) const
			{
				return vector4(super_type::x / factor,
							   super_type::y / factor,
							   super_type::z / factor,
							   w);
			}

			bool operator==(const vector4& rhs) const
			{
				return
					super_type::x/w == rhs.x/rhs.w &&
					super_type::y/w == rhs.y/rhs.w &&
					super_type::z/w == rhs.z/rhs.w;
			}

			friend std::ostream& operator<<(std::ostream& out,
											const vector4& self)
			{
				return out << "(" <<
					self.x << ", " <<
					self.y << ", " <<
					self.z << ", " <<
					self.w << ")";
			}

			vector4 get_norm() const
			{
				value_type length =
					std::sqrt(super_type::x * super_type::x +
							  super_type::y * super_type::y +
							  super_type::z * super_type::z);
				return vector4(super_type::x/length,
							   super_type::y/length,
							   super_type::z/length, w);
			}
		};

		template <typename VectorBase>
		class dividable_vector
		{
		public:
			typedef VectorBase value_type;
			typedef const VectorBase const_value_type;

		private:
			const value_type source;
			const value_type target;

		public:
			dividable_vector(const value_type src,
							 const value_type dest):
				source(src), target(dest)
			{}

			dividable_vector(const dividable_vector& src):
				source(src.source), target(src.target)
			{}

			value_type blend(const float blend_factor) const
			{
				assert(blend_factor >= 0.f);
				assert(blend_factor <= 1.f);

				const float opposite = 1.0f - blend_factor;
				return source * opposite + target * blend_factor;
			}

			value_type get_source() const
			{
				return source;
			}

			value_type get_target() const
			{
				return target;
			}
		};
	}
}
#endif /* RISA_VECTOR_HPP_ */
