#ifndef RISA_MATH_POINT_HPP_
#define RISA_MATH_POINT_HPP_

namespace risa_gl
{
	namespace math
	{
		template <typename value_t>
		class point
		{
		public:
			typedef value_t value_type;

		private:
			value_type x;
			value_type y;
			value_type z;

		public:
			point(const value_type& x_,
				  const value_type& y_,
				  const value_type& z_):
				x(x_), y(y_), z(z_)
			{}

			value_type get_x()
			{
				return x;
			}

			const value_type get_x() const
			{
				return x;
			}

			void set_x(const value_type& x_)
			{
				x = x_;
			}

			value_type get_y()
			{
				return y;
			}

			const value_type get_y() const
			{
				return y;
			}

			void set_y(const value_type& y_)
			{
				y = y_;
			}

			value_type get_z()
			{
				return z;
			}

			const value_type get_z() const
			{
				return z;
			}

			void set_z(const value_type& z_)
			{
				z = z_;
			}

			value_type get_distance(const point& rhs) const
			{
				const value_type x_diff = x - rhs.x;
				const value_type y_diff = y - rhs.y;
				const value_type z_diff = z - rhs.z;
				
				return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
			}
		};
	}
}

#endif /* RISA_MATH_POINT_HPP_ */
