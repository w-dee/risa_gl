#include <risa_gl/render/triangle_setup.hpp>
#include <risa_gl/render/interpolator.hpp>

#include <risa_gl/math/matrix.hpp>
#include <risa_gl/render/projector.hpp>
#include <risa_gl/render/viewport.hpp>

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <algorithm>

#include <cassert>

const int height = 100;
const int width = 100;

using risa_gl::math::matrix;
using risa_gl::math::coordinate;

using risa_gl::render::projector;
using risa_gl::render::viewport;
using risa_gl::render::triangle_setup;
using risa_gl::render::xyzw_st_coord;
using risa_gl::render::st_coord_interpolator;

coordinate<float>
xyzw_st_to_coord(const xyzw_st_coord<float>& point)
{
	return coordinate<float>(point.get_x(), point.get_y());
}

xyzw_st_coord<float>
merge_coodinate_and_zwst(const coordinate<float>& coord,
						 const xyzw_st_coord<float>& zwst)
{
	return
		xyzw_st_coord<float>(coord.get_x(), coord.get_y(),
							 zwst.get_z(), zwst.get_w(),
							 zwst.get_s(), zwst.get_t());
}

typedef xyzw_st_coord<float> coord_type;
coord_type points[3] =
	{ coord_type(-1.f,-1.f,-2.f, 1.f, 0.f, 0.f),
	  coord_type( 1.f,-1.f,-2.f, 1.f, 1.f, 0.f),
	  coord_type( 1.f, 1.f,-2.f, 1.f, 1.f, 1.f) };

matrix<float, 4, 4> obj_matrix;
projector<float> project(-1, 1, 1, -1, 1, 100);
viewport<float> view(0, 0, width, height);




std::vector<std::vector<bool> > image;


struct resizer
{
	void operator()(std::vector<bool>& line) const
	{
		line.resize(width);
	} 
};

void init()
{
	image.resize(height);
	std::for_each(image.begin(), image.end(), resizer());

	assert(image.size() == static_cast<unsigned int>(height));
	for (std::vector<std::vector<bool> >::const_iterator itor = image.begin();
		 itor != image.end(); ++itor)
	{
		assert (itor->size() == static_cast<unsigned int>(width));
	}
}

struct positions
{
	int x;
	int y;
	int s;
	int t;
	int color;
	double org_s;
	double org_t;

public:
	positions(int x_, int y_, int s_, int t_, int color_,
			  double org_s_, double org_t_):
		x(x_), y(y_), s(s_), t(t_), color(color_),
		org_s(org_s_), org_t(org_t_)
	{}

	std::string to_string() const
	{
		std::stringstream ss;
		ss << "(" << x << ", " << y << ", " <<
			s << ", " << t << ", " << color << ", " <<
			std::setw(9) << org_s * 100 << ", " <<
			std::setw(9) << org_t * 100<< ")";

		return ss.str();
	}

	bool operator<(const positions& rhs) const
	{
		if (this->x < rhs.x)
			return true;

		if (this->x == rhs.x &&
			this->y < rhs.y)
			return true;

		return false;
	}
};

struct printer
{
	void operator()(const positions& pos) const
	{
		std::cout << pos.to_string() << std::endl;
	}
};


void drawImage()
{
	init();
	
	typedef matrix<float, 1, 4> vector_type;
	typedef vector_type::elements_type vector_source_type;

	vector_source_type vs0 = {{
			points[0].get_x(), points[0].get_y(),
			points[0].get_z(), points[0].get_w()
		}};
	vector_source_type vs1 = {{
			points[1].get_x(), points[1].get_y(),
			points[1].get_z(), points[1].get_w()
		}};
	vector_source_type vs2 = {{
			points[2].get_x(), points[2].get_y(),
			points[2].get_z(), points[2].get_w()
		}};

	vector_type v0 = vs0;
	vector_type v1 = vs1;
	vector_type v2 = vs2;

	vector_type t0 = project.project(v0 * obj_matrix);
	vector_type t1 = project.project(v1 * obj_matrix);
	vector_type t2 = project.project(v2 * obj_matrix);

	coord_type p0 = coord_type(t0[0], t0[1], t0[2], t0[3],
							   points[0].get_s(), points[0].get_t());
	coord_type p1 = coord_type(t1[0], t1[1], t1[2], t1[3],
							   points[1].get_s(), points[1].get_t());
	coord_type p2 = coord_type(t2[0], t2[1], t2[2], t2[3],
							   points[2].get_s(), points[2].get_t());

	p0 = merge_coodinate_and_zwst(view.project(xyzw_st_to_coord(p0)), p0);
	p1 = merge_coodinate_and_zwst(view.project(xyzw_st_to_coord(p1)), p1);
	p2 = merge_coodinate_and_zwst(view.project(xyzw_st_to_coord(p2)), p2);

	triangle_setup<float> setupper(p0, p1, p2);
	const int y_size = setupper.size();
	typedef std::pair<xyzw_st_coord<float>,xyzw_st_coord<float> > pair_t;
	std::vector<positions> pos;

	for (int offset = 0; offset < y_size && offset < height; ++offset)
	{
		pair_t head_and_tail = setupper[offset];

		const xyzw_st_coord<float>& head = head_and_tail.first;
		const xyzw_st_coord<float>& tail = head_and_tail.second;

		const int distance =
			std::max(head.get_x(), tail.get_x()) -
			std::min(head.get_x(), tail.get_x());
		assert(distance >= 0);

		std::cout << "head: (" << head.get_x() << ", " << head.get_y() <<
			"), tail: (" << tail.get_x() << ", " << tail.get_y() << ")" <<
			std::endl;
		st_coord_interpolator<float> interp(head, tail, distance-1);
		for (int x_offset = 0; x_offset < distance; ++x_offset)
		{
			bool odd_t_mark = false;
			xyzw_st_coord<float> value =
				interp.interpolate_value(x_offset);
			{
				static unsigned char previous_color = 255;
				const int x_ = static_cast<int>(value.get_x());
				const int y_ = static_cast<int>(value.get_y());
				const int s_ = static_cast<int>(value.get_s() * 64);
				const int t_ = static_cast<int>(value.get_t() * 64);
				const int mod_s = s_ / 8;
				const int mod_t = t_ / 8;
				const bool is_odd_s = mod_s & 1;
				const bool is_odd_t = mod_t & 1;
				odd_t_mark = is_odd_t;
				const unsigned char color = !(is_odd_s ^ is_odd_t) * 255;
				
				image[y_][x_] = static_cast<bool>(color);

				if (previous_color != color)
				{
					static int counter = 0;
					++counter;
					previous_color = color;
					if (color == 0 &&
						x_ % 8 != 0)
					{

						pos.push_back(
									  positions(x_, y_,
												s_, t_,
												color,
												value.get_s(),
												value.get_t()));

// 						std::cout <<
// 							std::setw(2) << x_ << ", " <<
// 							std::setw(2) << y_ << ", " <<
// 							std::setw(2) << s_ << ", " <<
// 							std::setw(2) << t_ << ", " <<
// 							static_cast<int>(color) << std::endl;

					}
				}
			}
		}
	}

	std::sort(pos.begin(), pos.end());

	std::for_each(pos.begin(), pos.end(), printer());
}



int main()
{
	drawImage();
	return 0;
}
