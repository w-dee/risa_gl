#ifndef RISA_REGION_HPP_
#define RISA_REGION_HPP_

#include <ostream>

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

			friend std::ostream& operator<<(std::ostream& out,
											const coordinate& self)
			{
				return out << "(" << self.x << ", " << self.y << ")";
			}
		};

		/**
		 * 座標系はデカルト座標系のy軸を上下反転したものを使用するつもり
		 */
		template <typename BaseType>
		class rectangle_region
		{
		public:
			typedef BaseType value_type;
			typedef coordinate<value_type> coord_type;

		private:
			coord_type left_up;
			coord_type right_up;
			coord_type left_down;
			coord_type right_down;

		public:
			rectangle_region():
				left_up(), right_down()
			{}

			rectangle_region(value_type left_, value_type up_,
							 value_type right_, value_type down_):
				left_up(left_, up_),
				right_up(right_, up_),
				left_down(left_, down_),
				right_down(right_, down_)
			{}

			rectangle_region(const coord_type& left_up_,
							 const coord_type& right_up_,
							 const coord_type& left_down_,
							 const coord_type& right_down_):
				left_up(left_up_),
				right_up(right_up_),
				left_down(left_down_),
				right_down(right_down_)
			{}

			rectangle_region(const rectangle_region& src):
				left_up(src.left_up),
				right_up(src.right_up),
				left_down(src.left_down),
				right_down(src.right_down)
			{}

			rectangle_region& operator=(const rectangle_region& src)
			{
				if (this != &src)
				{
					this->left_up = src.left_up;
					this->right_up = src.right_up;
					this->left_down = src.left_down;
					this->right_down = src.right_down;
				}
			
				return *this;
			}

			coord_type get_left_up() const
			{
				return left_up;
			}

			coord_type get_right_up() const
			{
				return right_up;
			}

			coord_type get_left_down() const
			{
				return left_down;
			}

			coord_type get_right_down() const
			{
				return right_down;
			}
		
			void set_left_up(const coord_type& new_coord) const
			{
				left_up = new_coord;
			}

			void set_right_up(const coord_type& new_coord) const
			{
				right_up = new_coord;
			}

			void set_left_down(const coord_type& new_coord) const
			{
				left_down = new_coord;
			}
		
			void set_right_down(const coord_type& new_coord) const
			{
				right_down = new_coord;
			}

			friend std::ostream& operator<<(std::ostream& out,
										   const rectangle_region& self)
			{
				return out << "(" <<
					self.left_up << ", " <<
					self.right_up << ", " <<
					self.left_down << ", " <<
					self.right_down << ")";
			}
		};
	}
}

#endif /* RISA_REGION_HPP_ */
