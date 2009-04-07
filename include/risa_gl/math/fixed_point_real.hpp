#ifndef RISA_MATH_FIXED_POINT_REAL_HPP_
#define RISA_MATH_FIXED_POINT_REAL_HPP_

#include <limits>
#include <stdexcept>
#include <ostream>

namespace risa_gl
{
	namespace math
	{
		template <typename value_t = int,
				  typename mult_calc_t = long long int,
				  typename real_t = float>
		class fixed_point_real
		{
		public:
			typedef value_t value_type;
			typedef mult_calc_t multiply_result_type;
			typedef real_t real_type;

			enum
			{
				integer_position = sizeof(value_type) * 8 / 2
			};

		private:
			typedef value_type internal_type;

			internal_type value;

			static internal_type
			value_type_to_internal_type(const value_type& src)
			{
				return static_cast<value_type>(src << integer_position);
			}

			static value_type
			internal_type_to_value_type(const internal_type& src)
			{
				return static_cast<internal_type>(src >> integer_position);
			}

			static real_type
			internal_type_to_real_type(const internal_type& src)
			{
				return static_cast<real_type>(src) / (1 << integer_position);
			}

			static internal_type
			real_type_to_internal_type(const real_type& src)
			{
				real_type real_value = src;
				const value_type internal_offset = 1 << integer_position;
				real_value *= internal_offset;

				if (std::numeric_limits<internal_type>::max() < real_value)
					throw std::overflow_error("overflow to multiply "
											  "operation.");
			
				return static_cast<internal_type>(real_value);
			}

			value_type get_integer_part() const
			{
				return internal_type_to_value_type(value);
			}

			real_type get_real_part() const
			{
				return internal_type_to_real_type(value) - get_integer_part();
			}

		public:
			fixed_point_real():
				value()
			{}

			fixed_point_real(const value_type& src):
				value(value_type_to_internal_type(src))
			{}

			fixed_point_real(const real_type& src):
				value(real_type_to_internal_type(src))
			{}

			fixed_point_real(const fixed_point_real& src):
				value(src.value)
			{}

			value_type floor() const
			{
				const real_type real_value = get_real_part();
				if (real_value == real_type())
					return get_integer_part();

				const value_type result_base = get_integer_part();
				if (result_base >= value_type())
					return result_base;
				return result_base - static_cast<value_type>(1);
			}

			value_type ceil() const
			{
				const real_type real_value = get_real_part();
				if (real_value == real_type())
					return get_integer_part();

				const value_type result_base = get_integer_part();
				if (result_base >= value_type())
					return result_base + 1;
				return result_base;
			}

			fixed_point_real operator-() const
			{
				return fixed_point_real(-value);
			}

			fixed_point_real& operator=(const fixed_point_real& src)
			{
				if (this != &src)
					value = src.value;

				return *this;
			}

			bool operator==(const fixed_point_real& src) const
			{
				return value == src.value;
			}

			bool operator!=(const fixed_point_real& src) const
			{
				return !((*this) == src);
			}

			bool operator<(const fixed_point_real& src) const
			{
				return value < src.value;
			}

			bool operator<=(const fixed_point_real& src) const
			{
				return (*this) < src || (*this) == src;
			}

			bool operator>(const fixed_point_real& src) const
			{
				return !((*this) <= src);
			}

			bool operator>=(const fixed_point_real& src) const
			{
				return !((*this) < src);
			}

			fixed_point_real& operator+=(const fixed_point_real& src)
			{
				value += src.value;
				return *this;
			}

			fixed_point_real operator+(const fixed_point_real& src) const
			{
				return fixed_point_real(*this) += src;
			}

			fixed_point_real& operator-=(const fixed_point_real& src)
			{
				value -= src.value;
				return *this;
			}

			fixed_point_real operator-(const fixed_point_real& src) const
			{
				return fixed_point_real(*this) -= src;
			}

			fixed_point_real operator*=(const fixed_point_real& src)
			{
				this->value = static_cast<internal_type>(
					(static_cast<multiply_result_type>(value) * 
					 static_cast<multiply_result_type>(src.value)) >>
					(integer_position));

				return *this;
			}

			fixed_point_real operator*(const fixed_point_real& src) const
			{
				return fixed_point_real(*this) *= src;
			}

			fixed_point_real operator/=(const fixed_point_real& src)
			{
				this->value = static_cast<internal_type>(
					(static_cast<multiply_result_type>(value) <<
					 integer_position) / src.value);

				return *this;
			}

			fixed_point_real operator/(const fixed_point_real& src) const
			{
				return fixed_point_real(*this) /= src;
			}

			friend std::ostream&
			operator<<(std::ostream& out, const fixed_point_real& val)
			{
				out << internal_type_to_real_type(val.value) << std::endl;

				return out;
			}
		};
	}
}
#endif /* RISA_MATH_FIXED_POINT_REAL_HPP_ */
