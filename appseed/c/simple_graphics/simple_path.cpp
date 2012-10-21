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
bool simple_path::add_round_rect(const RECT & r, int dia)
{

   // diameter can't exceed width or height
   if(dia > width(r))	dia = width(r);
   if(dia > height(r))	dia = height(r);

   // define a corner
   RECT Corner(rect_dim(r.left, r.top, dia, dia));

   // begin path
//   path.m_ppath->Reset();

   // top left
   add_arc(Corner, 180, 90);

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
   }

   // top right
   Corner.left += (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   add_arc(Corner, 270, 90);

   // bottom right
   Corner.top += (height(r) - dia - 1);
   Corner.bottom = Corner.top + dia2;
   add_arc(Corner,   0, 90);

   // bottom left
   Corner.left -= (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   add_arc(Corner,  90, 90);

}

void simple_path::get_round_top_left(const RECT & r, int dia)
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
   add_arc(Corner,  135, 45);

   add_line(r.left, r.top + height(r) - dia / 2, r.left, r.top + dia / 2);


   Corner.top -= (height(r) - dia - 1);
   Corner.bottom = Corner.top + dia2;
   add_arc(Corner, 180, 90);

   add_line(r.left + dia / 2, r.top , r.left + width(r) - dia / 2, r.top);

   Corner.left += (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   add_arc(Corner, 270, 45);


   // end path
   //path.m_ppath->CloseFigure();
}



void simple_path::get_round_bottom_right(const RECT & r, int dia)
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
   add_arc(Corner, 315, 45);

   add_line(r.left + width(r), r.top + dia / 2, r.left + width(r), r.top + height(r) - dia / 2);

   // bottom right
   Corner.top += (height(r) - dia - 1);
   Corner.bottom = Corner.top + dia2;
   add_arc(Corner,   0, 90);

   add_line(r.left + dia / 2, r.top + height(r) , r.left + width(r) - dia / 2, r.top + height(r));

   // bottom left
   Corner.left -= (width(r) - dia - 1);
   Corner.right = Corner.left + dia2;
   add_arc(Corner,  90, 45);

   


   //Corner.Y -= (height(r) - dia - 1);
   //path.m_ppath->AddArc(Corner, 180, 90);

   

   //Corner.X += (width(r) - dia - 1);
   //path.m_ppath->AddArc(Corner, 275, 45);


   // end path
   //path.m_ppath->CloseFigure();
}

