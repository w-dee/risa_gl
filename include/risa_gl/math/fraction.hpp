#ifndef RISA_MATH_FRACTION_HPP_
#define RISA_MATH_FRACTION_HPP_

#include <risa_gl/math/lcm.hpp>
#include <risa_gl/math/gcd.hpp>
#include <stdexcept>
#include <ostream>
#include <cassert>

namespace risa_gl
{
	namespace math
	{
		template <typename value_type>
		class fraction
		{
		private:
			value_type numerator;
			value_type denominator;

		public:
			fraction(const value_type& num_,
					 const value_type& deno_ = 1):
				numerator(num_),
				denominator(deno_)
			{
				if (denominator == 0)
					throw std::runtime_error("zero divide exception.");

				assert(denominator != 0);
			}

			fraction(const fraction& src):
				numerator(src.numerator),
				denominator(src.denominator)
			{
				assert(denominator != 0);
			}


			fraction& operator=(const fraction& src)
			{
				if (this != &src)
				{
					numerator = src.numerator;
					denominator = src.denominator;
				}

				assert(denominator != 0);
				return *this;
			}

			~fraction()
			{}

			value_type get_numerator() const
			{
				return numerator;
			}

			value_type get_denominator() const
			{
				return denominator;
			}

			fraction get_reduce() const
			{
				const value_type gcd_value =
					gcd(numerator, denominator);

				assert((denominator / gcd_value) != 0);

				return fraction(numerator / gcd_value,
								denominator / gcd_value);
			}

			fraction& reduce()
			{
				return *this = this->get_reduce();
			}

			fraction get_invert() const
			{
				if (numerator == 0)
					throw std::runtime_error("zero divide exception.");

				value_type sign_factor =
					numerator < 0 ? -1 : 1;

				assert((denominator * sign_factor) != 0);

				return fraction(denominator * sign_factor,
								numerator * sign_factor);
			}

			fraction& invert()
			{
				return *this = this->get_invert();
			}

			value_type get_value() const
			{
				assert(denominator != 0);
				return static_cast<value_type>(numerator / denominator);
			}

			double get_real_value() const
			{
				assert(denominator != 0);
				return static_cast<double>(numerator) / denominator;
			}

			bool is_zero() const
			{
				return (numerator == 0);
			}

			fraction& operator+=(const fraction& src)
			{
				const value_type lcm_value =
					lcm(this->denominator, src.denominator);

				numerator = numerator * lcm_value / this->denominator +
					src.numerator * lcm_value / src.denominator;
				denominator = lcm_value;

				assert(denominator != 0);

				return *this;
			}

			fraction operator+(const fraction& src) const
			{
				fraction result(*this);
				result += src;

				return result;
			}

			fraction& operator-=(const fraction& src)
			{
				const value_type lcm_value =
					lcm(this->denominator, src.denominator);

				numerator = numerator * lcm_value / this->denominator -
					src.numerator * lcm_value / src.denominator;
				denominator = lcm_value;

				assert(denominator != 0);

				return *this;
			}

			fraction operator-(const fraction& src) const
			{
				fraction result(*this);
				result -= src;

				return result;
			}

			fraction& operator*=(const fraction& src)
			{
				const fraction mult = src.get_reduce();
				this->reduce();

				numerator *= mult.numerator;
				denominator *= mult.denominator;

				this->reduce();
				assert(denominator != 0);

				return *this;
			}

			fraction operator*(const fraction& src) const
			{
				fraction result(*this);
				result *= src;

				return result;
			}

			fraction& operator/=(const fraction& src)
			{
				return (*this) *= src.get_invert();
			}

			fraction operator/(const fraction& src) const
			{
				fraction result(*this);
				result /= src;

				return result;
			}

			bool operator==(const fraction& src) const
			{
				const value_type lcm_value =
					lcm(denominator, src.denominator);

				return 
					(numerator * lcm_value / denominator) ==
					(src.numerator * lcm_value / src.denominator);
			}

			bool operator!=(const fraction& src) const
			{
				return !((*this) == src);
			}

			bool operator<(const fraction& src) const
			{
				const value_type lcm_value =
					lcm(denominator, src.denominator);

				return 
					(numerator * lcm_value / denominator) <
					(src.numerator * lcm_value / src.denominator);
			}

			bool operator<=(const fraction& src) const
			{
				return
					((*this) < src) || ((*this) == src);
			}

			bool operator>(const fraction& src) const
			{
				return !((*this) <= src);
			}

			bool operator>=(const fraction& src) const
			{
				return !((*this) < src);
			}

			friend std::ostream&
			operator<<(std::ostream& out, const fraction& self)
			{
				return out << self.numerator << "/" << self.denominator;
			}
		};
	}
}

#endif /* RISA_MATH_FRACTION_HPP_ */
