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

class CLASS_DECL_c graphics_round_rect
{
public:


	graphics_round_rect();
	~graphics_round_rect();

	//=============================================================================
	//
	// GetRoundRectPath()
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
	static void GetRoundRectPath(simple_path & path, const RECT & rect, int dia);
   static void GetRoundTopLeft(simple_path & path, const RECT & rect, int dia);
   static void GetRoundBottomRight(simple_path & path, const RECT & rect, int dia);

	//=============================================================================
	//
	// DrawRoundRect()
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
	void DrawRoundRect(simple_path & pGraphics, const RECT & r,  COLORREF color, int radius, int width);
   void DrawTopLeft(simple_path & pGraphics, const RECT & r,  COLORREF color, int radius, int width);
   void DrawBottomRight(simple_path & pGraphics, const RECT & r,  COLORREF color, int radius, int width);

	//=============================================================================
	//
	// FillRoundRect()
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
	void FillRoundRect(simple_path & pGraphics, const RECT & r,  COLORREF color, int radius);

	//=============================================================================
	//
	// FillRoundRect()
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
	void FillRoundRect(simple_path & pGraphics, simple_brush & brush, const RECT & r, COLORREF border, int radius);


};


