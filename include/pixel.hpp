#ifndef RISA_PIXEL_HPP_
#define RISA_PIXEL_HPP_

#include "static_assert.hpp"
#include "risa_types.hpp"

namespace risa_gl 
{
	/**
	 * ピクセルクラス
	 * @todo PixelFormatを抽象化できる構成にする
	 */
	class pixel
	{
	private:
		byte r;
		byte g;
		byte b;
		byte a;

	public:
		pixel():
			r(), g(), b(), a(255)
		{}

		pixel(byte r_, byte g_, byte b_, byte a_ = 255):
			r(r_), g(g_), b(b_), a(a_)
		{}

		pixel(const pixel& source):
			r(source.r), g(source.g), b(source.b), a(source.a)
		{}

		~pixel()
		{}

		pixel& operator=(const pixel& source)
		{
			if (this != &source)
			{
				this->r = source.r;
				this->g = source.g;
				this->b = source.b;
				this->a = source.a;
			}

			return *this;
		}

		byte get_r() const
		{
			return r;
		}

		void set_r(byte r_)
		{
			r = r_;
		}

		byte get_g() const
		{
			return g;
		}
		
		void set_g(byte g_)
		{
			g = g_;
		}

		byte get_b() const
		{
			return b;
		}

		void set_b(byte b_)
		{
			b = b_;
		}

		byte get_a() const
		{
			return a;
		}

		void set_a(byte a_)
		{
			a = a_;
		}
	};


	/**
	 * モノトーンピクセルクラス
	 */
	class brightness
	{
	private:
		byte y;

	public:
		brightness():
			y()
		{}

		brightness(byte y_):
			y(y_)
		{}

		brightness(const brightness& source):
			y(source.y)
		{}

		~brightness()
		{}

		brightness& operator=(const brightness& source)
		{
			if (this != &source)
				this->y = source.y;

			return *this;
		}

		byte get_y() const
		{
			return y;
		}

		void set_y(byte y_)
		{
			y = y_;
		}
	};
};

#endif /* RISA_PIXEL_HPP_ */
