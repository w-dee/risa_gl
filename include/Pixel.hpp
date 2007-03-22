#ifndef RISA_PIXEL_HPP_
#define RISA_PIXEL_HPP_

namespace risa_gl 
{
	typedef unsigned char byte;

	class pixel
	{
	private:
		byte r;
		byte g;
		byte b;
		byte a;

	public:
		pixel():
			r(), g(), b(), a()
		{}

		~pixel()
		{}

	};
}

#endif /* RISA_PIXEL_HPP_ */
