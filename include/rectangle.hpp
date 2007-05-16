#ifndef RISA_RECTANGLE_HPP_
#define RISA_RECTANGLE_HPP_

#include "fragment.hpp"
#include "fragment_set.hpp"

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

		point& operator=(cosnt point& src)
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

	template <typename pixel_store_t>
	class rectangle
	{
	public:
		typedef pixel_store_t pixel_store_type;
		typedef pixel_store_type::fragment_type fragment_type;
		typedef pixel_store_type::aligned_fragment_type aligned_fragment_type;
		typedef fragment_set<pixel_store_type, fragment_type>
		fragment_set_type;
		typedef fragment_set<pixel_store_type, aligned_fragment_type>
		aligned_fragment_set_type;

	private:
		point up_left;
		point down_right;
		pixel_store_type& obj;

	public:
		rectangle(pixel_store_type& src):
			up_left(0, 0),
			down_right(src.get_width(), src.get_height()),
			obj(src)
		{}

		rectangle(pixel_store_type& src,
				 const point& up_left_,
				 const point& down_right_):
			up_left(up_left_), down_right(down_right_),
			obj(src)
		{}

		rectangle(const rectable& src):
			up_left(src.up_left), down_right(src.down_right),
			obj(src.obj)
		{}

		fragment_set_type get_fragments()
		{
			point rect = down_right - up_left;
			assert(rect.get_x() >= 0 && rect.get_y() >= 0);

			fragment_set_type::fragment_collection_type
				fragments(rect.get_y());

			for (int lines = 0; lines < rect.get_y(); ++lines)
				fragments.push_back(obj.get_fragment);
			
			return fragments;
		}
	}
};

#endif /* RISA_RECTANGLE_HPP_ */
