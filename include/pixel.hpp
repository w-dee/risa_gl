#ifndef RISA_PIXEL_HPP_
#define RISA_PIXEL_HPP_

#include "static_assert.hpp"
#include "risa_types.hpp"

namespace risa_gl 
{
	/**
	 * 明るさピクセルクラス
	 */
	class brightness
	{
	public:
		enum {
			brightness_position = 0,
		};

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

		byte get_luminance() const
		{
			return y;
		}

		void set_luminance(byte y_)
		{
			y = y_;
		}
	};

	/**
	 * ピクセルコンバータ
	 */
	template <typename SrcType, typename DestType>
	DestType pixel_convert(const SrcType& src)
	{
		return DestType(src.get_red(), src.get_green(), src.get_blue(), src.get_alpha());
	};

	/**
	 * RGBAピクセルクラス
	 */
	class pixel
	{
	public:
		enum {
			red_position = 0,
			green_position = 1,
			blue_position = 2,
			alpha_position = 3,
		};

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

		byte get_red() const
		{
			return r;
		}

		void set_red(byte r_)
		{
			r = r_;
		}

		byte get_green() const
		{
			return g;
		}
		
		void set_green(byte g_)
		{
			g = g_;
		}

		byte get_blue() const
		{
			return b;
		}

		void set_blue(byte b_)
		{
			b = b_;
		}

		byte get_alpha() const
		{
			return a;
		}

		void set_alpha(byte a_)
		{
			a = a_;
		}

		bool operator==(const pixel& rhs) const
		{
			return
				this->r == rhs.r &&
				this->g == rhs.g &&
				this->b == rhs.b &&
				this->a == rhs.a;
		}
	};

	/**
	 * BGRAピクセルクラス
	 */
	class pixel_bgra
	{
	public:
		enum {
			blue_position = 0,
			green_position = 1,
			red_position = 2,
			alpha_position = 3,
		};

	private:
		byte b;
		byte g;
		byte r;
		byte a;

	public:
		pixel_bgra():
			b(), g(), r(), a(255)
		{}

		pixel_bgra(byte r_, byte g_, byte b_, byte a_ = 255):
			b(b_), g(g_), r(r_), a(a_)
		{}

		pixel_bgra(const pixel_bgra& source):
			b(source.b), g(source.g), r(source.r), a(source.a)
		{}

		~pixel_bgra()
		{}

		pixel_bgra& operator=(const pixel_bgra& source)
		{
			if (this != &source)
			{
				this->b = source.b;
				this->g = source.g;
				this->r = source.r;
				this->a = source.a;
			}

			return *this;
		}

		byte get_red() const
		{
			return r;
		}

		void set_red(byte r_)
		{
			r = r_;
		}

		byte get_green() const
		{
			return g;
		}
		
		void set_green(byte g_)
		{
			g = g_;
		}

		byte get_blue() const
		{
			return b;
		}

		void set_blue(byte b_)
		{
			b = b_;
		}

		byte get_alpha() const
		{
			return a;
		}

		void set_alpha(byte a_)
		{
			a = a_;
		}
	};

	/**
	 * ABGRピクセルクラス
	 */
	class pixel_abgr
	{
	public:
		enum {
			alpha_position = 0,
			blue_position = 1,
			green_position = 2,
			red_position = 3,
		};

	private:
		byte a;
		byte b;
		byte g;
		byte r;

	public:
		pixel_abgr():
			a(255), b(), g(), r()
		{}

		pixel_abgr(byte r_, byte g_, byte b_, byte a_ = 255):
			a(a_), b(b_), g(g_), r(r_)
		{}

		pixel_abgr(const pixel_abgr& source):
			a(source.a), b(source.b), g(source.g), r(source.r)
		{}

		~pixel_abgr()
		{}

		pixel_abgr& operator=(const pixel_abgr& source)
		{
			if (this != &source)
			{
				this->a = source.a;
				this->b = source.b;
				this->g = source.g;
				this->r = source.r;
			}

			return *this;
		}

		byte get_red() const
		{
			return r;
		}

		void set_red(byte r_)
		{
			r = r_;
		}

		byte get_green() const
		{
			return g;
		}
		
		void set_green(byte g_)
		{
			g = g_;
		}

		byte get_blue() const
		{
			return b;
		}

		void set_blue(byte b_)
		{
			b = b_;
		}

		byte get_alpha() const
		{
			return a;
		}

		void set_alpha(byte a_)
		{
			a = a_;
		}
	};
};

#endif /* RISA_PIXEL_HPP_ */
