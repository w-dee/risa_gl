#ifndef RISA_MATH_RATIONAL_HPP_
#define RISA_MATH_RATIONAL_HPP_

#include <risa_gl/math/lcm.hpp>
#include <risa_gl/math/gcd.hpp>
#include <stdexcept>

namespace risa_gl
{
	namespace math
	{
		template <typename value_type>
		class rational
		{
		private:
			value_type numerator;
			value_type denominator;

		public:
			rational(const value_type& num_,
					 const value_type& deno_):
				numerator(num_),
				denominator(deno_)
			{
				if (denominator == 0)
					throw std::runtime_error("zero divide exception.");
			}

			rational(const rational& src):
				numerator(src.numerator),
				denominator(src.denominator)
			{}


			rational& operator=(const rational& src)
			{
				if (this != &src)
				{
					numerator = src.numerator;
					denominator = src.denominator;
				}

				return *this;
			}

			~rational()
			{}

			value_type get_numerator() const
			{
				return numerator;
			}

			value_type get_denominator() const
			{
				return denominator;
			}

			rational get_reduce() const
			{
				const value_type gcd_value =
					gcd(numerator, denominator);

				return rational(numerator / gcd_value,
								denominator / gcd_value);
			}

			rational& reduce()
			{
				return *this = this->get_reduce();
			}

			rational get_invert() const
			{
				if (numerator == 0)
					throw std::runtime_error("zero divide exception.");

				value_type sign_factor =
					numerator < 0 ? -1 : 1;

				return rational(denominator * sign_factor,
								numerator * sign_factor);
			}

			rational& invert()
			{
				return *this = this->get_invert();
			}

			value_type get_value() const
			{
				return static_cast<value_type>(numerator / denominator);
			}

			rational& operator+=(const rational& src)
			{
				const value_type lcm_value =
					lcm(this->denominator, src.denominator);

				numerator = numerator * lcm_value / this->denominator +
					src.numerator * lcm_value / src.denominator;
				denominator = lcm_value;

				return *this;
			}

			rational operator+(const rational& src) const
			{
				rational result(*this);
				result += src;

				return result;
			}

			rational& operator-=(const rational& src)
			{
				const value_type lcm_value =
					lcm(this->denominator, src.denominator);

				numerator = numerator * lcm_value / this->denominator -
					src.numerator * lcm_value / src.denominator;
				denominator = lcm_value;

				return *this;
			}

			rational operator-(const rational& src) const
			{
				rational result(*this);
				result -= src;

				return result;
			}

			rational& operator*=(const rational& src)
			{
				numerator *= src.numerator;
				denominator *= src.denominator;

				return *this;
			}

			rational operator*(const rational& src) const
			{
				rational result(*this);
				result *= src;

				return result;
			}

			rational& operator/=(const rational& src)
			{
				return (*this) *= src.get_invert();
			}

			rational operator/(const rational& src) const
			{
				rational result(*this);
				result /= src;

				return result;
			}

			bool operator==(const rational& src) const
			{
				const value_type lcm_value =
					lcm(denominator, src.denominator);

				return 
					(numerator * lcm_value / denominator) ==
					(src.numerator * lcm_value / src.denominator);
			}

			bool operator!=(const rational& src) const
			{
				return !((*this) == src);
			}

			bool operator<(const rational& src) const
			{
				const value_type lcm_value =
					lcm(denominator, src.denominator);

				return 
					(numerator * lcm_value / denominator) <
					(src.numerator * lcm_value / src.denominator);
			}

			bool operator<=(const rational& src) const
			{
				return
					((*this) < src) || ((*this) == src);
			}

			bool operator>(const rational& src) const
			{
				return !((*this) <= src);
			}

			bool operator>=(const rational& src) const
			{
				return !((*this) < src);
			}
		};
	}
}

#endif /* RISA_MATH_RATIONAL_HPP_ */
