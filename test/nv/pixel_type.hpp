typedef unsigned char byte;

struct pixel_type
{
	byte red;
	byte green;
	byte blue;
	byte alpha;

	enum {
		red_position = 0,
		green_position = 1,
		blue_position = 2,
		alpha_position = 3
	};

	pixel_type():
		red(), green(), blue(), alpha()
	{}

	pixel_type(byte r, byte g, byte b, byte a):
		red(r), green(g), blue(b), alpha(a)
	{}
};
