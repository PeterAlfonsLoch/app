#include "framework.h"


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

//=============================================================================
//
// get_round_rect()
//
// Purpose:     Defines a Rounded Rectangle and places it in the GraphicsPath
//
// Parameters:  path.m_ppath		- [out] pointer to GraphicsPath that will recieve the
//									path data
//				r			- [in]	Rect that defines the round rectangle boundaries
//				dia			- [in]	diameter of the rounded corners (2*radius)
//
// Returns:     None
//
void graphics_round_rect::get_round_rect(simple_path & path, const RECT & r, int dia)
{
   // diameter can't exceed width or height
   if(dia > width(r))	dia = width(r);
   if(dia > height(r))	dia = height(r);

   // define a corner
   RECT Corner(rect_dim(r.left, r.top, dia, dia));

   // begin path
//   path.m_ppath->Reset();

   // top left
   path.add_arc(Corner, 180, 90);

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
   }

   // top right
   Corner.left += (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   path.add_arc(Corner, 270, 90);

   // bottom right
   Corner.top += (height(r) - dia - 1);
   Corner.bottom = Corner.top + dia2;
   path.add_arc(Corner,   0, 90);

   // bottom left
   Corner.left -= (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   path.add_arc(Corner,  90, 90);

   // end path
   path.close_figure();
}

void graphics_round_rect::get_round_top_left(simple_path & path, const RECT & r, int dia)
{
   // diameter can't exceed width or height
   if(dia > width(r))	dia = width(r);
   if(dia > height(r))	dia = height(r);

   // define a corner
   RECT Corner(rect_dim(r.left, r.top, dia, dia));

   // begin path
   //path.m_ppath->Reset();


   // top left
//   path.m_ppath->AddArc(Corner, 180, 90);

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
      //Corner.Height += 1;
      //height(r) -=1; //height(r) -= 1;
   }

   // top right
   Corner.left += (width(r) - dia - 1);
   //path.m_ppath->AddArc(Corner, 270, 90);

   // bottom right
   Corner.top += (height(r) - dia - 1);
   //path.m_ppath->AddArc(Corner,   0, 90);

   // bottom left
   Corner.left -= (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   path.add_arc(Corner,  135, 45);

   path.add_line(r.left, r.top + height(r) - dia / 2, r.left, r.top + dia / 2);


   Corner.top -= (height(r) - dia - 1);
   Corner.bottom = Corner.top + dia2;
   path.add_arc(Corner, 180, 90);

   path.add_line(r.left + dia / 2, r.top , r.left + width(r) - dia / 2, r.top);

   Corner.left += (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   path.add_arc(Corner, 270, 45);


   // end path
   //path.m_ppath->CloseFigure();
}



void graphics_round_rect::get_round_bottom_right(simple_path & path, const RECT & r, int dia)
{
   // diameter can't exceed width or height
   if(dia > width(r))	dia = width(r);
   if(dia > height(r))	dia = height(r);

   // define a corner
   RECT Corner(rect_dim(r.left, r.top, dia, dia));

   // begin path
   //path.m_ppath->Reset();


   // top left
//   path.m_ppath->AddArc(Corner, 180, 90);

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
      //Corner.Height += 1;
      //height(r) -=1; //height(r) -= 1;
   }

   // top right
   Corner.left += (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   path.add_arc(Corner, 315, 45);

   path.add_line(r.left + width(r), r.top + dia / 2, r.left + width(r), r.top + height(r) - dia / 2);

   // bottom right
   Corner.top += (height(r) - dia - 1);
   Corner.bottom = Corner.top + dia2;
   path.add_arc(Corner,   0, 90);

   path.add_line(r.left + dia / 2, r.top + height(r) , r.left + width(r) - dia / 2, r.top + height(r));

   // bottom left
   Corner.left -= (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   path.add_arc(Corner,  90, 45);

   


   //Corner.Y -= (height(r) - dia - 1);
   //path.m_ppath->AddArc(Corner, 180, 90);

   

   //Corner.X += (width(r) - dia - 1);
   //path.m_ppath->AddArc(Corner, 275, 45);


   // end path
   //path.m_ppath->CloseFigure();
}

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
void graphics_round_rect::draw_round_rect(simple_graphics & g, const RECT & rect, COLORREF cr, int radius, int width)
{

   RECT r = rect;

   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = g.m_pgraphics->SetPageUnit(UnitPixel);

   // define the pen
   simple_solid_pen pen(g, cr);
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   simple_path path(true);

   // get path
   get_round_rect(path, r, dia);

   // draw the round rect
   g.draw_path(path, pen);

   // if width > 1
   for(int i=1; i<width; i++)
   {
      dia++;
      // left stroke
      deflate_rect(r, 1, 0);

      // get the path
      get_round_rect(path, r, dia);

      // draw the round rect
      g.draw_path(path, pen);

      // up stroke
      deflate_rect(r, 0, 1);

      // get the path
      get_round_rect(path, r, dia);

      // draw the round rect
      g.draw_path(path, pen);
   }

   // restore page unit
   //g.m_pgraphics->SetPageUnit((Unit)oldPageUnit);
}

void graphics_round_rect::draw_top_left(simple_graphics & g, const RECT & rect, COLORREF cr, int radius, int width)
{

   RECT r = rect;

   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = g.m_pgraphics->SetPageUnit(UnitPixel);

   // define the pen
   simple_solid_pen pen(g, cr);
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   simple_path path(false);

   // get path
   get_round_top_left(path, r, dia);

   // draw the round rect
   g.draw_path(path, pen);

   // if width > 1
   for(int i=1; i<width; i++)
   {
      dia++;
      // left stroke
      deflate_rect(r, 1, 0);

      // get the path
      get_round_top_left(path, r, dia);

      // draw the round rect
      g.draw_path(path, pen);

      // up stroke
      deflate_rect(r, 0, 1);

      // get the path
      get_round_top_left(path, r, dia);

      // draw the round rect
      g.draw_path(path, pen);
   }

   // restore page unit
//   g.m_pgraphics->SetPageUnit((Unit)oldPageUnit);
}

void graphics_round_rect::draw_bottom_right(simple_graphics & g, const RECT & rect, COLORREF cr, int radius, int width)
{

   RECT r = rect;

   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = g.m_pgraphics->SetPageUnit(UnitPixel);

   // define the pen
   simple_solid_pen pen(g, cr);
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   simple_path path(false);

   // get path
   get_round_bottom_right(path, r, dia);

   // draw the round rect
   g.draw_path(path, pen);

   // if width > 1
   for(int i=1; i<width; i++)
   {
      dia++;
      // left stroke
      deflate_rect(r, 1, 0);

      // get the path
      get_round_bottom_right(path, r, dia);

      // draw the round rect
      g.draw_path(path, pen);

      // up stroke
      deflate_rect(r, 0, 1);

      // get the path
      get_round_bottom_right(path, r, dia);

      // draw the round rect
      g.draw_path(path, pen);
   }

   // restore page unit
//   g.m_pgraphics->SetPageUnit((Unit)oldPageUnit);
}

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
void graphics_round_rect::fill_round_rect(simple_graphics & g, const RECT & r, COLORREF cr, int radius)
{

   simple_solid_brush br(g, cr);

   fill_round_rect(g, br, r, cr, radius);

}

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
void graphics_round_rect::fill_round_rect(simple_graphics & g, simple_brush & br, const RECT & r, COLORREF border, int radius)
{
   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = g.m_pgraphics->SetPageUnit(UnitPixel);

   // define the pen
   simple_solid_pen pen(g, border);
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   simple_path path(true);

   // get path
   get_round_rect(path, r, dia);

   // fill
   g.fill_path(path, br);

   // draw the border last so it will be on top in case the color is different
   g.draw_path(path, pen);

   // restore page unit
   //g.m_pgraphics->SetPageUnit((Unit)oldPageUnit);
}
