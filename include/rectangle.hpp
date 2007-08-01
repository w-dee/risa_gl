#ifndef RISA_RECTANGLE_HPP_
#define RISA_RECTANGLE_HPP_

#include <fragment.hpp>
#include <fragment_set.hpp>

namespace risa_gl {

	class point
	{
	private:
		int x;
		int y;

	public:
		point():
			x(), y()
		{}

		point(const int x_, const int y_):
			x(x_), y(y_)
		{}

		point(const point& src):
			x(src.x), y(src.y)
		{}

		point& operator=(const point& src)
		{
			if (this != &src)
			{
				this->x = src.x;
				this->y = src.y;
			}

			return *this;
		}

		~point()
		{}

		point& operator+=(const point& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}

		point operator+(const point& rhs) const
		{
			return point(*this) += rhs;
		}
		
		point& operator-=(const point& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}

		point operator-(const point& rhs) const
		{
			return point(*this) -= rhs;
		}
		
		bool operator==(const point& rhs) const
		{
			if (this == &rhs)
				return true;

			return (this->x == rhs.x) && (this->y == rhs.y);
		}

		bool operator!=(const point& rhs) const
		{
			return !this->operator==(rhs);
		}

		int get_x() const
		{
			return x;
		}

		void set_x(const int x_)
		{
			x = x_;
		}

		int get_y() const
		{
			return y;
		}

		void set_y(const int y_)
		{
			y = y_;
		}
	};

	template <typename pixel_store_t, typename aligned_iterator_t>
	class rectangle
	{
	public:
		typedef pixel_store_t pixel_store_type;
		typedef typename pixel_store_type::fragment_type fragment_type;
		typedef aligned_iterator_t aligned_fragment_type;
		typedef fragment_set<pixel_store_type, fragment_type>
		fragment_set_type;
		typedef fragment_set<pixel_store_type, aligned_fragment_type>
		aligned_fragment_set_type;

	private:
		point top_left;
		point bottom_right;
		pixel_store_type& obj;

	public:
		rectangle(pixel_store_type& src):
			top_left(0, 0),
			bottom_right(src.get_width(), src.get_height()),
			obj(src)
		{}

		rectangle(pixel_store_type& src,
				 const point& top_left_,
				 const point& bottom_right_):
			top_left(top_left_), bottom_right(bottom_right_),
			obj(src)
		{}

		rectangle(const rectangle& src):
			top_left(src.top_left), bottom_right(src.bottom_right),
			obj(src.obj)
		{}

		rectangle& operator=(const rectangle& src)
		{
			if (this != &src)
			{
				this->top_left = src.top_left;
				this->bottom_right = src.bottom_right;
				this->obj = src.obj;
			}
			return *this;
		}

		~rectangle()
		{}

		int get_left() const
		{
			return top_left.get_x();
		}

		void set_left(int left)
		{
			top_left.set_x(left);
		}

		int get_top() const
		{
			return top_left.get_y();
		}

		void set_top(int top)
		{
			top_left.set_y(top);
		}

		int get_right() const
		{
			return bottom_right.get_x();
		}

		void set_right(int right)
		{
			bottom_right.set_x(right);
		}

		int get_bottom() const
		{
			return bottom_right.get_y();
		}

		void set_bottom(int bottom)
		{
			bottom_right.set_y(bottom);
		}

		fragment_set_type get_fragments()
		{
			point rect = bottom_right - top_left;
			assert(rect.get_x() >= 0 && rect.get_y() >= 0);

			typename fragment_set_type::fragment_collection_type fragments;
			fragments.reserve(rect.get_y());

			for (int lines = top_left.get_y();
				 lines < bottom_right.get_y(); ++lines)
				fragments.push_back(obj.get_fragment(lines,
													 top_left.get_x(),
													 bottom_right.get_x()));

			assert(fragments.size() == static_cast<size_t>(rect.get_y()));

			return fragments;
		}
	};
}

#endif /* RISA_RECTANGLE_HPP_ */
