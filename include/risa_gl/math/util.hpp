#ifndef RISA_MATH_UTIL_HPP_
#define RISA_MATH_UTIL_HPP_

#include <limits>
#include <stdexcept>

#include <cmath>
#include <cassert>

namespace risa_gl
{
	namespace math
	{
		class util
		{
		public:

			template <typename value_type>
			static int ceil(const value_type& value)
			{
				if (value < 0)
					return -floor(-value);

				assert(value >= 0);

				// TODO digitsとの比較がおかしい
				if (std::numeric_limits<int>::max() < value ||
					std::pow(
						10,
						std::numeric_limits<value_type>::digits) < value)
					throw std::overflow_error("overflow");

				const int int_value = static_cast<int>(value);
				const value_type distance = value - int_value;


				return static_cast<int>(value) +
 					(distance > 0 ? 1 : 0);

			}

			template <typename value_type>
			static int floor(const value_type& value)
			{
				if (value < 0)
					return -ceil(-value);

				assert(value >= 0);

				if (std::numeric_limits<int>::max() < value ||
					std::numeric_limits<value_type>::digits < value)
					throw std::overflow_error("overflow");

				return static_cast<int>(value);
			}
		};
	}
}

#endif /* RISA_MATH_UTIL_HPP_ */
