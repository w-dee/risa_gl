#ifndef RISA_REGION_HPP_
#define RISA_REGION_HPP_

namespace risa_gl
{
	namespace math
	{
		template <typename BaseType>
		class coordinate
		{
		public:
			typedef BaseType value_type;

		private:
		
			value_type x;
			value_type y;

		public:
			coordinate(value_type x_ = static_cast<value_type>(0),
					   value_type y_ = static_cast<value_type>(0)):
				x(x_), y(y_)
			{}

			coordinate(const coordinate& src):
				x(src.x), y(src.y)
			{}

			~coordinate()
			{}

			coordinate& operator=(const coordinate& lhs)
			{
				if (this != &lhs)
				{
					this->x = lhs.x;
					this->y = lhs.y;
				}

				return *this;
			}

			value_type get_x() const
			{
				return x;
			}

			value_type get_y() const
			{
				return y;
			}

			void set_x(value_type newX)
			{
				x = newX;
			}

			void set_y(value_type newY)
			{
				y = newY;
			}

			bool operator==(const coordinate& rhs) const
			{
				return 
					(this->get_x() == rhs.get_x() &&
					 this->get_y() == rhs.get_y()) ?
					true : false;
			}

			bool operator!=(const coordinate& rhs) const
			{
				return !this->operator==(rhs);
			}
		};

		/**
		 * 座標系はデカルト座標系のy軸を上下反転したものを使用するつもり
		 */
		template <typename BaseType>
		class region
		{
		public:
			typedef BaseType value_type;
			typedef coordinate<value_type> coord_type;

		private:
			coord_type left_up;
			coord_type right_down;

		public:
			region():
				left_up(), right_down()
			{}

			region(value_type left_, value_type up_,
				   value_type right_, value_type down_):
				left_up(left_, up_),
				right_down(right_, down_)
			{}

			region(const region& src):
				left_up(src.left_up),
				right_down(src.right_down)
			{}

			region& operator=(const region& src)
			{
				if (this != &src)
				{
					this->left_up = src.left_up;
					this->right_down = src.right_down;
				}
			
				return *this;
			}

			value_type get_left() const
			{
				return left_up.get_x();
			}

			value_type get_top() const
			{
				return left_up.get_y();
			}

			value_type get_right() const
			{
				return right_down.get_x();
			}
		
			value_type get_bottom() const
			{
				return right_down.get_y();
			}

			value_type get_width() const
			{
				return right_down.get_x() - left_up.get_x();
			}

			value_type get_height() const
			{
				return right_down.get_y() - left_up.get_y();
			}

			void set_left(value_type new_left) const
			{
				left_up.set_x(new_left);
			}

			void set_up(value_type new_up) const
			{
				left_up.set_y(new_up);
			}

			void set_right(value_type new_right) const
			{
				right_down.set_x(new_right);
			}
		
			void set_down(value_type new_down) const
			{
				right_down.set_y(new_down);
			}
		};
	}
}

#endif /* RISA_REGION_HPP_ */
