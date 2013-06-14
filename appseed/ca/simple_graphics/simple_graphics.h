#pragma once


//
// CRoundRect.h : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//
//
// Description:
//     CRoundRect Draws or Fills rounded rectangles for GDI+.  It was implemented
//	   to overcome the asymmetric issues associated with GDI+ round rectangles
//
// History
//     Version 1.0 - 2008 June 24
//     - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////


class CLASS_DECL_c simple_graphics :
   public os_simple_graphics
{
public:

   
   simple_graphics();
   ~simple_graphics();


   
   using ::os_simple_graphics::draw_line;
   inline bool draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
   inline bool draw_line(POINT p1, POINT p2, simple_pen & pen);
   inline bool draw_line(POINT p1, POINT p2);

   using ::os_simple_graphics::rectangle;
   inline bool rectangle(const RECT & rect);

   using ::os_simple_graphics::draw_rect;
   inline bool draw_rect(const RECT & rect);
   inline bool draw_rect(const RECT & rect, simple_pen & pen);

   using ::os_simple_graphics::fill_rect;
   inline bool fill_rect(const RECT & rect);
   inline bool fill_rect(const RECT & rect, simple_brush & brush);

   using ::os_simple_graphics::fill_solid_rect;
   inline bool fill_solid_rect(const RECT & rect, COLORREF clr);


	//=============================================================================
	//
	// draw_round_rect()
	//
	// Purpose:     Draws a rounded rectangle with a solid pen
	//
	// Parameters:  pGraphics	- [in]	pointer to the Graphics device
	//				r			- [in]	Rect that defines the round rectangle boundaries
	//				color		- [in]	Color value for the brush
	//				radius		- [in]  radius of the rounded corner
	//				width		- [in]  width of the border
	//
	// Returns:     None
	//
	bool draw_round_rect(const RECT & r,  simple_pen & pen, int32_t radius);
   bool draw_round_top_left(const RECT & r,  simple_pen & pen, int32_t radius);
   bool draw_round_bottom_right(const RECT & r,  simple_pen & pen, int32_t radius);

	bool draw_round_rect(const RECT & r,  COLORREF color, int32_t radius, int32_t width);
   bool draw_round_top_left(const RECT & r,  COLORREF color, int32_t radius, int32_t width);
   bool draw_round_bottom_right(const RECT & r,  COLORREF color, int32_t radius, int32_t width);

	//=============================================================================
	//
	// fill_round_rect()
	//
	// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
	//				first then fills in the rectangle.
	//
	// Parameters:  pGraphics	- [in]	pointer to the Graphics device
	//				r			- [in]	Rect that defines the round rectangle boundaries
	//				color		- [in]	Color value for the brush
	//				radius		- [in]  radius of the rounded corner
	//
	// Returns:     None
	//
	bool fill_round_rect(const RECT & r,  COLORREF color, int32_t radius);

	//=============================================================================
	//
	// fill_round_rect()
	//
	// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
	//				first then fills in the rectangle.
	//
	// Parameters:  pGraphics	- [in]	pointer to the Graphics device
	//				pBrush		- [in]  pointer to a Brush
	//				r			- [in]	Rect that defines the round rectangle boundaries
	//				color		- [in]	Color value for the border (needed in case the
	//									brush is a type other than solid)
	//				radius		- [in]  radius of the rounded corner
	//
	// Returns:     None
	//
	bool fill_round_rect(const RECT & r, simple_brush & brush, int32_t radius);


   bool round_rect(const RECT & r, int32_t radius);




};




inline bool simple_graphics::draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
   
   return draw_line(x1, y1, x2, y2, m_pen);

}

inline bool simple_graphics::draw_line(POINT p1, POINT p2, simple_pen & pen)
{

   return draw_line(p1.x, p1.y, p2.x, p2.y, pen);

}

inline bool simple_graphics::draw_line(POINT p1, POINT p2)
{
   
   return draw_line(p1, p2, m_pen);

}




inline bool simple_graphics::draw_rect(const RECT & rect)
{

   return draw_rect(&rect, m_pen);

}

inline bool simple_graphics::draw_rect(const RECT & rect, simple_pen & pen)
{

   return draw_rect(&rect, pen);

}

inline bool simple_graphics::fill_rect(const RECT & rect)
{

   return fill_rect(&rect, m_brush);

}

inline bool simple_graphics::fill_rect(const RECT & rect, simple_brush & brush)
{

   return fill_rect(&rect, brush);

}

inline bool simple_graphics::rectangle(const RECT & rect)
{

   return rectangle(&rect);

}





