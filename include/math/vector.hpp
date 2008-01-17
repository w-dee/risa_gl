#ifndef RISA_VECTOR_HPP_
#define RISA_VECTOR_HPP_

#include <ostream>
#include <cmath>
#include <cassert>

namespace risa_gl
{
	namespace math
	{
		struct vector2
		{
			vector2(const float x_, const float y_):
				x(x_), y(y_)
			{}

			float x;
			float y;

			vector2 operator+(const vector2& rhs) const
			{
				return vector2(x + rhs.x, y + rhs.y);
			}

			vector2 operator*(const float factor) const
			{
				return vector2(x * factor, y * factor);
			}

			vector2 operator-(const vector2& rhs) const
			{
				return vector2(x - rhs.x, y - rhs.y);
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
				float length = std::sqrt(x * x + y * y);
				return vector2(x/length, y/length);
			}
		};

		struct vector3 : public vector2
		{
			vector3(const float x_, const float y_, const float z_):
				vector2(x_, y_), z(z_)
			{}

			float z;

			vector3 operator+(const vector3& rhs) const
			{
				return vector3(x + rhs.x, y + rhs.y, z + rhs.z);
			}

			vector3 operator*(const float factor) const
			{
				return vector3(x * factor, y * factor, z * factor);
			}

			vector3 operator-(const vector3& rhs) const
			{
				return vector3(x - rhs.x, y - rhs.y, z - rhs.z);
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
				float length = std::sqrt(x * x + y * y + z * z);
				return vector3(x/length, y/length, z/length);
			}
		};

		struct vector4 : public vector3
		{
			vector4(const float x_, const float y_,
					const float z_, const float w_):
				vector3(x_, y_, z_), w(w_)
			{}

			float w;

			vector4 operator+(const vector4& rhs) const
			{
				return vector4(
					x/w + rhs.x/rhs.w,
					y/w + rhs.y/rhs.w,
					z/w + rhs.z/rhs.w,
					1.f);
			}

			vector4 operator*(const float factor) const
			{
				return vector4(x * factor,
							   y * factor,
							   z * factor,
							   w);
			}

			vector4 operator-(const vector4& rhs) const
			{
				return vector4(
					x/w - rhs.x/rhs.w,
					y/w - rhs.y/rhs.w,
					z/w - rhs.z/rhs.w,
					1.f);
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
				float length = std::sqrt(x * x + y * y + z * z);
				return vector4(x/length, y/length, z/length, w);
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
