#ifndef RISA_VECTOR_HPP_
#define RISA_VECTOR_HPP_

#include <ostream>

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

			friend std::ostream& operator<<(std::ostream& out,
											const vector2& self)
			{
				return out << "(" <<
					self.x << ", " <<
					self.y << ")";
			}
		};

		struct vector3 : public vector2
		{
			vector3(const float x_, const float y_, const float z_):
				vector2(x_, y_), z(z_)
			{}

			float z;

			friend std::ostream& operator<<(std::ostream& out,
											const vector3& self)
			{
				return out << "(" <<
					self.x << ", " <<
					self.y << ", " <<
					self.z << ")";
			}

		};

		struct vector4 : public vector3
		{
			vector4(const float x_, const float y_,
					const float z_, const float w_):
				vector3(x_, y_, z_), w(w_)
			{}

			float w;
			friend std::ostream& operator<<(std::ostream& out,
											const vector4& self)
			{
				return out << "(" <<
					self.x << ", " <<
					self.y << ", " <<
					self.z << ", " <<
					self.w << ")";
			}
		};

	}
}
#endif /* RISA_VECTOR_HPP_ */
