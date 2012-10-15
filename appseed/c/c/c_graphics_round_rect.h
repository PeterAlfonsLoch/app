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

namespace graphics_round_rect
{


	//=============================================================================
	//
	// get_round_rect()
	//
	// Purpose:     Defines a Rounded Rectangle and places it in the GraphicsPath
	//
	// Parameters:  pPath		- [out] pointer to GraphicsPath that will recieve the
	//									path data
	//				r			- [in]	Rect that defines the round rectangle boundaries
	//				dia			- [in]	diameter of the rounded corners (2*radius)
	//
	// Returns:     None
	//
	CLASS_DECL_c void get_round_rect(simple_path & path, const RECT & rect, int dia);
   CLASS_DECL_c void get_round_top_left(simple_path & path, const RECT & rect, int dia);
   CLASS_DECL_c void get_round_bottom_right(simple_path & path, const RECT & rect, int dia);

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
	CLASS_DECL_c void draw_round_rect(simple_graphics & pGraphics, const RECT & r,  COLORREF color, int radius, int width);
   CLASS_DECL_c void draw_top_left(simple_graphics & pGraphics, const RECT & r,  COLORREF color, int radius, int width);
   CLASS_DECL_c void draw_bottom_right(simple_graphics & pGraphics, const RECT & r,  COLORREF color, int radius, int width);

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
	CLASS_DECL_c void fill_round_rect(simple_graphics & pGraphics, const RECT & r,  COLORREF color, int radius);

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
	CLASS_DECL_c void fill_round_rect(simple_graphics & pGraphics, simple_brush & brush, const RECT & r, COLORREF border, int radius);


} // namespace graphics_round_rect


