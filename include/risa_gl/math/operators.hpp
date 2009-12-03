#ifndef RISA_MATH_OPERATORS_HPP_
#define RISA_MATH_OPERATORS_HPP_

#include <risa_gl/math/vector.hpp>

namespace risa_gl
{
	namespace math
	{
		template <typename value_type>
		vector2<value_type> to_vector2(const vector3<value_type>& value)
		{
			return vector2<value_type>(value.x, value.y);
		}

		template <typename value_type>
		vector2<value_type> to_vector2(const vector4<value_type>& value)
		{
			return vector2<value_type>(value.x, value.y);
		}

		template <typename value_type>
		vector3<value_type> to_vector3(const vector2<value_type>& value)
		{
			return vector3<value_type>(value.x, value.y, value_type(0));
		}

		template <typename value_type>
		vector3<value_type> to_vector3(const vector4<value_type>& value)
		{
			return vector3<value_type>(value.x, value.y, value.z);
		}

		template <typename value_type>
		vector4<value_type> to_vector4(const vector2<value_type>& value)
		{
			return vector4<value_type>(value.x, value.y, 0, 0);
		}

		template <typename value_type>
		vector4<value_type> to_vector4(const vector3<value_type>& value)
		{
			return vector4<value_type>(value.x, value.y, value.z, 0);
		}

		template <typename value_type>
		value_type
		dot_product(const vector2<value_type>& lhs,
					  const vector2<value_type>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		template <typename value_type>
		value_type
		dot_product(const vector3<value_type>& lhs,
					  const vector3<value_type>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		template <typename value_type>
		value_type
		dot_product(const vector4<value_type>& lhs,
					  const vector4<value_type>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w + rhs.w;
		}

		template <typename value_type>
		vector3<value_type>
		cross_product(const vector3<value_type>& lhs,
					  const vector3<value_type>& rhs)
		{
			return vector3<value_type>(lhs.y * rhs.z - lhs.z * rhs.x,
									   lhs.z * rhs.x - lhs.x * rhs.z,
									   lhs.x * rhs.y - lhs.y * rhs.x);
		}
	}
}

#endif /* RISA_MATH_OPERATORS_HPP_ */

