#include <wx/wx.h>
#include <wx/image.h>
#include <risa_gl/render/triangle_setup.hpp>
#include <risa_gl/render/interpolator.hpp>

#include <risa_gl/math/matrix.hpp>
#include <risa_gl/render/projector.hpp>
#include <risa_gl/render/viewport.hpp>
#include <risa_gl/render/raster.hpp>

#include <iostream>
#include <typeinfo>

using risa_gl::math::matrix;
using risa_gl::math::coordinate;

using risa_gl::render::projector;
using risa_gl::render::viewport;
using risa_gl::render::triangle_setup;
using risa_gl::render::xyzw_st_coord;
using risa_gl::render::st_coord_interpolator;
using risa_gl::render::raster;

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

class MyWindow : public wxWindow
{
private:
	typedef xyzw_st_coord<float> coord_type;
	coord_type points[3];

	matrix<float, 4, 4> obj_matrix;
	projector<float> project;
	viewport<float> view;

	wxImage* image;

	wxImage* createImage(const wxSize& size)
	{
		return new wxImage(size.GetWidth(), size.GetHeight());
	}

	void point_reset()
	{
		points[0] = coord_type(0.f, 0.f,-2.f, 1.f, 0.f, 0.f);
		points[1] = coord_type(1.f, 0.f,-2.f, 1.f, 1.f, 0.f);
		points[2] = coord_type(1.f, 1.f,-2.f, 1.f, 1.f, 1.f);
	}

	void drawImage(wxImage* iamge)
	{
		const int height = image->GetHeight();
		const int width = image->GetWidth();

		typedef matrix<float, 1, 4> vector_type;
		typedef vector_type::elements_type vector_source_type;

		vector_source_type vs0 = {
			points[0].get_x(), points[0].get_y(),
			points[0].get_z(), points[0].get_w()
		};
		vector_source_type vs1 = {
			points[1].get_x(), points[1].get_y(),
			points[1].get_z(), points[1].get_w()
		};
		vector_source_type vs2 = {
			points[2].get_x(), points[2].get_y(),
			points[2].get_z(), points[2].get_w()
		};

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

		std::cout << "p0: " << p0 << std::endl;
		std::cout << "p1: " << p1 << std::endl;
		std::cout << "p2: " << p2 << std::endl;

		triangle_setup<float> setupper(p0, p1, p2);
		const int y_size = setupper.size();
		typedef std::pair<xyzw_st_coord<float>,xyzw_st_coord<float> > pair_t;
		for (int offset = 0; offset < y_size && offset < height; ++offset)
		{
			pair_t head_and_tail = setupper[offset];

			const xyzw_st_coord<float>& head = head_and_tail.first;
			const xyzw_st_coord<float>& tail = head_and_tail.second;
			raster<float> raster(head, tail);

			for (int x_offset = 0; x_offset < raster.get_distance(); ++x_offset)
			{
				bool odd_t_mark = false;
				xyzw_st_coord<float> value = raster[x_offset];

				if (0 <= value.get_x() &&
					width > value.get_x())
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

					if (previous_color != color)
					{
						static int counter = 0;
						++counter;
						previous_color = color;
						if (color == 0 &&
							x_ % 8 != 0)
						{
							std::cout << counter << ", " <<
							x_ << ", " << y_ << ", " <<
							s_ << ", " << t_ <<
							mod_s << ", " <<
							mod_t << ", " <<
							static_cast<int>(color) << std::endl;
						}
					}

					image->SetRGB(x_, y_, color, color, color);
				}
			}
		}
	}

public:
	MyWindow(wxFrame* parent, const wxSize& size = wxSize(640, 480)):
		wxWindow(parent, wxID_ANY, wxDefaultPosition, size,
				 wxRAISED_BORDER),
		points(),
		obj_matrix(),
		project(-1, 1, 1, -1, 1, 100),
		view(0, 0, size.GetWidth(), size.GetHeight()),
		image(createImage(size))
	{
		point_reset();

		SetBackgroundColour(*wxGREEN);
	}

protected:
	void OnKeyDown(wxKeyEvent& WXUNUSED(event))
	{
		std::cout << "on key down." << std::endl;
	}

	void OnKeyUp(wxKeyEvent& WXUNUSED(event))
	{
		std::cout << "on key Up." << std::endl;
	}

	void OnChar(wxKeyEvent& WXUNUSED(event))
	{
		std::cout << "on char." << std::endl;
	}

	void OnPaint(wxPaintEvent& WXUNUSED(event))
	{
		wxPaintDC paintContext(this);
		drawImage(image);

		wxSize rect = this->GetSize();
		wxBitmap bitmap(*image);

		wxMemoryDC backBuffer;
		backBuffer.SelectObject(bitmap);
		paintContext.Blit(0, 0, rect.GetWidth(), rect.GetHeight(),
						  &backBuffer, 0, 0);
	}

private:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyWindow, wxWindow)
EVT_KEY_DOWN(MyWindow::OnKeyDown)
EVT_KEY_UP(MyWindow::OnKeyUp)
EVT_CHAR(MyWindow::OnChar)
EVT_PAINT(MyWindow::OnPaint)
END_EVENT_TABLE()

class MyFrame : public wxFrame
{
private:

	enum {
		ID_Quit = 1,
		ID_About
	};

	wxWindow* window;

public:
	MyFrame(const wxString& title,
			const wxPoint& pos,
			const wxSize& size):
		wxFrame(static_cast<wxFrame*>(NULL),
				-1,
				title,
				pos,
				wxSize(644, 536),
				wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER),
		window(NULL)
	{
		window = new MyWindow(this, size);

		wxMenu* menuFile = new wxMenu();
		menuFile->Append(ID_About, _T("&About..."));
		menuFile->AppendSeparator();
		menuFile->Append(ID_Quit, _T("E&xit"));

		wxMenuBar* menuBar = new wxMenuBar();
		menuBar->Append(menuFile, _T("&File"));

		SetMenuBar(menuBar);
		CreateStatusBar();
		SetStatusText(_T("welcome to wxWidgets!"));

		this->SetAutoLayout(true);
	}

protected:

	void OnQuit(wxCommandEvent& WXUNUSED(event))
	{
		Close(TRUE);
	}

	void OnAbout(wxCommandEvent& WXUNUSED(event))
	{
		wxMessageBox(_T("This is a wxWidgets Hello world sample"),
					 _T("About Hello World"),
					 wxOK | wxICON_INFORMATION,
					 this);
	}

	void OnMouseMove(wxMouseEvent& event)
	{
		if (event.m_leftDown)
			this->Refresh(true);
	}

	void OnKeyDown(wxKeyEvent& event)
	{
		std::cout << "on key event." << std::endl;
	}

	void OnChar(wxKeyEvent& event)
	{
		std::cout << "on char event." << std::endl;
	}

	DECLARE_EVENT_TABLE();

};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Quit, MyFrame::OnQuit)
EVT_MENU(ID_About, MyFrame::OnAbout)
EVT_MOTION(MyFrame::OnMouseMove)
END_EVENT_TABLE();


class MyApp : public wxApp
{
	bool OnInit()
	{
		MyFrame* frame = new MyFrame(_T("Hello world."),
									 wxPoint(50, 50),
									 wxSize(640, 480));
		frame->Show(TRUE);
		SetTopWindow(frame);
		return true;
	}
};

IMPLEMENT_APP(MyApp);
