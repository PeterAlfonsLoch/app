#include "framework.h"
#include <math.h>

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


graphics_round_rect::graphics_round_rect(void)
{

}

graphics_round_rect::~graphics_round_rect(void)
{

}

//=============================================================================
//
// GetRoundRectPath()
//
// Purpose:     Defines a Rounded Rectangle and places it in the GraphicsPath
//
// Parameters:  ppath		- [out] pointer to GraphicsPath that will recieve the
//									path data
//				r			- [in]	Rect that defines the round rectangle boundaries
//				dia			- [in]	diameter of the rounded corners (2*radius)
//
// Returns:     None
//
void graphics_round_rect::GetRoundRectPath(ID2D1PathGeometry *ppath, RECT rect, int dia)
{

   // diameter can't exceed width or height
   if(dia > width(rect))	
      dia = width(rect);

   if(dia > height(rect))	
      dia = height(rect);

   D2D1_RECT_F r;
   r.left = (FLOAT) rect.left;
   r.top = (FLOAT) rect.top;
   r.right = (FLOAT) rect.right;
   r.bottom = (FLOAT) rect.bottom;

   // define a corner
   D2D1_RECT_F Corner;
   Corner.left    = (FLOAT) r.left;
   Corner.top     = (FLOAT) r.top;
   Corner.right   = (FLOAT) (Corner.left + dia);
   Corner.bottom  = (FLOAT) (Corner.top + dia);


   ID2D1GeometrySink * psink = NULL;

   // begin path
   ppath->Open(&psink);


   if(psink == NULL)
      return;

   D2D1_POINT_2F p;
   
   p.x = (FLOAT) r.left;
   p.y = (FLOAT) r.bottom;

   psink->BeginFigure(p, D2D1_FIGURE_BEGIN_FILLED);

   D2D1_ARC_SEGMENT arcseg;

   arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
   arcseg.size.width = (FLOAT) (dia / 2);
   arcseg.size.height = (FLOAT)  (dia / 2);
   arcseg.point.x = (FLOAT) Corner.right;
   arcseg.point.y = (FLOAT) Corner.top;
   arcseg.arcSize = D2D1_ARC_SIZE_SMALL;
   arcseg.rotationAngle = 90;


   // top left
   psink->AddArc(arcseg);

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
      //r.Height -=1; //r.Height -= 1;
   }

   Corner.right   = Corner.left + dia2;
   Corner.bottom  = Corner.top + dia2;


   // top right
   Corner.left    = r.right - dia - 1;
   Corner.right   = Corner.left + dia2;

   p.x = (FLOAT) Corner.left;
   p.y =(FLOAT)  Corner.top;
   psink->AddLine(p);

   arcseg.point.x    = (FLOAT) Corner.right;
   arcseg.point.y    = (FLOAT) Corner.bottom;
   psink->AddArc(arcseg);


   // bottom right
   Corner.top = (FLOAT) (r.bottom - dia - 1);
   Corner.bottom = (FLOAT) (Corner.top + dia2);

   p.x = (FLOAT) Corner.right;
   p.y = (FLOAT) Corner.top;
   psink->AddLine(p);

   arcseg.point.x = (FLOAT) Corner.left;
   arcseg.point.y = (FLOAT) Corner.bottom;
   psink->AddArc(arcseg);


   // bottom left
   Corner.left = (FLOAT) r.left;
   Corner.right = (FLOAT) (Corner.left + dia2);

   p.x = (FLOAT) Corner.right;
   p.y = (FLOAT) Corner.bottom;
   psink->AddLine(p);

   arcseg.point.x = (FLOAT) Corner.left;
   arcseg.point.y = (FLOAT) Corner.top;
   psink->AddArc(arcseg);

   // end path
   psink->Close();

   psink->Release();



}

void graphics_round_rect::GetRoundTopLeft(ID2D1PathGeometry *ppath, RECT rect, int dia)
{
   // diameter can't exceed width or height
   if(dia > width(rect))	
      dia = width(rect);

   if(dia > height(rect))	
      dia = height(rect);

   D2D1_RECT_F r;
   r.left = (FLOAT) rect.left;
   r.top = (FLOAT) rect.top;
   r.right = (FLOAT) rect.right;
   r.bottom = (FLOAT) rect.bottom;

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
      //r.Height -=1; //r.Height -= 1;
   }

   // define a corner
   D2D1_RECT_F Corner;
   Corner.left    = r.left;
   Corner.top     = r.bottom - dia - 1;
   Corner.right   = Corner.left + dia2;
   Corner.bottom  = Corner.top + dia2;


   ID2D1GeometrySink * psink = NULL;

   // begin path
   ppath->Open(&psink);


   if(psink == NULL)
      return;

   D2D1_POINT_2F p;
   
   // bottom left
   p.x = ((FLOAT) r.right - ((FLOAT) dia / sqrt(2.0f)));
   p.y = ((FLOAT) r.bottom - ((FLOAT) dia / sqrt(2.0f));

   psink->BeginFigure(p, D2D1_FIGURE_BEGIN_FILLED);

   D2D1_ARC_SEGMENT arcseg;

   arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
   arcseg.size.width = dia / 2;
   arcseg.size.height = dia / 2;
   arcseg.arcSize = D2D1_ARC_SIZE_SMALL;
   arcseg.rotationAngle = 45;


   psink->AddArc(arcseg);


   // top left
   Corner.top    = r.top;
   Corner.bottom   = Corner.top + dia2;

   p.x = Corner.left;
   p.y = Corner.bottom;
   psink->AddLine(p);

   arcseg.point.x    = Corner.right;
   arcseg.point.y    = Corner.top;
   arcseg.rotationAngle = 90;
   psink->AddArc(arcseg);


   // top right
   Corner.left = r.right - dia - 1;
   Corner.right= Corner.left + dia2;

   p.x = Corner.left;
   p.y = Corner.top;
   psink->AddLine(p);

   arcseg.point.x = Corner.right;
   arcseg.point.y = Corner.bottom;
   arcseg.rotationAngle = 45;
   psink->AddArc(arcseg);


   // end path
   psink->Close();

   psink->Release();

}



void graphics_round_rect::GetRoundBottomRight(ID2D1PathGeometry *ppath, RECT rect, int dia)
{
   
   if(dia > width(rect))	
      dia = width(rect);

   if(dia > height(rect))	
      dia = height(rect);

   D2D1_RECT_F r;
   r.left = (FLOAT) rect.left;
   r.top = (FLOAT) rect.top;
   r.right = (FLOAT) rect.right;
   r.bottom = (FLOAT) rect.bottom;

   D2D1_RECT_F Corner;

   Corner.left    = r.right - dia - 1;
   Corner.top     = r.top;

   // tweak needed for radius of 10 (dia of 20)
   int dia2 = dia;
   if(dia % 2 == 0)
   {
      dia2++;
      //r.Height -=1; //r.Height -= 1;
   }

   Corner.right   = Corner.left + dia2;
   Corner.bottom  = Corner.top + dia2;

   ID2D1GeometrySink * psink = NULL;

   // begin path
   ppath->Open(&psink);


   if(psink == NULL)
      return;

   D2D1_POINT_2F p;
   
   p.x = (FLOAT) r.right + ((FLOAT) dia / sqrt(2.0));
   p.y = (FLOAT) r.top + ((FLOAT) dia / sqrt(2.0));

   psink->BeginFigure(p, D2D1_FIGURE_BEGIN_HOLLOW);

   D2D1_ARC_SEGMENT arcseg;

   arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
   arcseg.size.width = dia / 2;
   arcseg.size.height = dia / 2;
   arcseg.point.x = Corner.right;
   arcseg.point.y = Corner.bottom;
   arcseg.arcSize = D2D1_ARC_SIZE_SMALL;
   arcseg.rotationAngle = 45;

   psink->AddArc(arcseg);

   // bottom right
   Corner.top = r.bottom - dia - 1;
   Corner.bottom = Corner.top + dia2;

   p.x = Corner.right;
   p.y = Corner.top;
   psink->AddLine(p);

   arcseg.point.x = Corner.left;
   arcseg.point.y = Corner.bottom;
   arcseg.rotationAngle = 25;
   psink->AddArc(arcseg)90


   // bottom left
   Corner.left = r.left;
   Corner.right = Corner.left + dia2;

   p.x = Corner.right;
   p.y = Corner.bottom;
   psink->AddLine(p);

   arcseg.point.x = Corner.left;
   arcseg.point.y = Corner.top;
   arcseg.rotationAngle = 45;
   psink->AddArc(arcseg);

   // end path
   psink->Close();

   psink->Release();

}

//=============================================================================
//
// DrawRoundRect()
//
// Purpose:     Draws a rounded rectangle with a solid pen
//
// Parameters:  pdc	- [in]	pointer to the Graphics device
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the brush
//				radius		- [in]  radius of the rounded corner
//				width		- [in]  width of the border
//
// Returns:     None
//
void graphics_round_rect::DrawRoundRect(ID2D1RenderTarget * pdc, RECT r,  COLORREF color, int radius, int width)
{
   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = pdc->SetPageUnit(UnitPixel);

   // define the pen
   ID2D1SolidColorBrush * ppen = NULL;
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   //GraphicsPath path;

   // get path

   ID2D1PathGeometry * ppath = NULL;

   ID2D1Factory * pfactory = NULL;
      
   pdc->GetFactory(&pfactory);
   
   pfactory->CreatePathGeometry(&ppath);

   GetRoundRectPath(ppath, r, dia);

   D2D1_COLOR_F c;

   c.a = GetAValue(color) / 255.0f;
   c.r = GetRValue(color) / 255.0f;
   c.g = GetGValue(color) / 255.0f;
   c.b = GetBValue(color) / 255.0f;

   pdc->CreateSolidColorBrush(c, &ppen);

   // draw the round rect
   pdc->DrawGeometry(ppath, ppen);

   ppath->Release();

   // if width > 1
   for(int i=1; i<width; i++)
   {
      dia++;
      // left stroke
      r.left++;
      r.right--;

      // get the path
      ppath = NULL;
      pfactory->CreatePathGeometry(&ppath);
      GetRoundRectPath(ppath, r, dia);

      // draw the round rect
      pdc->DrawGeometry(ppath, ppen);
      ppath->Release();

      // up stroke
      r.top++;
      r.bottom--;

      // get the path
      ppath = NULL;
      pfactory->CreatePathGeometry(&ppath);
      GetRoundRectPath(ppath, r, dia);

      // draw the round rect
      pdc->DrawGeometry(ppath, ppen);
      ppath->Release();
   }

   ppen->Release();

   pfactory->Release();

   // restore page unit
   //pdc->SetPageUnit((Unit)oldPageUnit);
}

void graphics_round_rect::DrawTopLeft(ID2D1RenderTarget* pdc, RECT r,  COLORREF color, int radius, int width)
{
   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = pdc->SetPageUnit(UnitPixel);

   // define the pen
   ID2D1SolidColorBrush * ppen = NULL;
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   //GraphicsPath path;

   // get path

   ID2D1PathGeometry * ppath = NULL;

   ID2D1Factory * pfactory = NULL;
      
   pdc->GetFactory(&pfactory);
   
   pfactory->CreatePathGeometry(&ppath);

   GetRoundTopLeft(ppath, r, dia);

   D2D1_COLOR_F c;

   c.a = GetAValue(color) / 255.0f;
   c.r = GetRValue(color) / 255.0f;
   c.g = GetGValue(color) / 255.0f;
   c.b = GetBValue(color) / 255.0f;

   pdc->CreateSolidColorBrush(c, &ppen);

   // draw the round rect
   pdc->DrawGeometry(ppath, ppen);

   ppath->Release();

   // if width > 1
   for(int i=1; i<width; i++)
   {
      dia++;
      // left stroke
      r.left++;
      r.right--;

      // get the path
      ppath = NULL;
      pfactory->CreatePathGeometry(&ppath);
      GetRoundTopLeft(ppath, r, dia);

      // draw the round rect
      pdc->DrawGeometry(ppath, ppen);
      ppath->Release();

      // up stroke
      r.top++;
      r.bottom--;

      // get the path
      ppath = NULL;
      pfactory->CreatePathGeometry(&ppath);
      GetRoundTopLeft(ppath, r, dia);

      // draw the round rect
      pdc->DrawGeometry(ppath, ppen);
      ppath->Release();
   }

   ppen->Release();

   pfactory->Release();

   // restore page unit
   //pdc->SetPageUnit((Unit)oldPageUnit);
}

void graphics_round_rect::DrawBottomRight(ID2D1RenderTarget* pdc, RECT r,  COLORREF color, int radius, int width)
{
   int dia	= 2*radius;

   // set to pixel mode
   //int oldPageUnit = pdc->SetPageUnit(UnitPixel);

   // define the pen
   ID2D1SolidColorBrush * ppen = NULL;
   //pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   //GraphicsPath path;

   // get path

   ID2D1PathGeometry * ppath = NULL;

   ID2D1Factory * pfactory = NULL;
      
   pdc->GetFactory(&pfactory);
   
   pfactory->CreatePathGeometry(&ppath);

   GetRoundRectPath(ppath, r, dia);

   D2D1_COLOR_F c;

   c.a = GetAValue(color) / 255.0f;
   c.r = GetRValue(color) / 255.0f;
   c.g = GetGValue(color) / 255.0f;
   c.b = GetBValue(color) / 255.0f;

   pdc->CreateSolidColorBrush(c, &ppen);

   // draw the round rect
   pdc->GetRoundBottomRight(ppath, ppen);

   ppath->Release();

   // if width > 1
   for(int i=1; i<width; i++)
   {
      dia++;
      // left stroke
      r.left++;
      r.right--;

      // get the path
      ppath = NULL;
      pfactory->CreatePathGeometry(&ppath);
      GetRoundBottomRight(ppath, r, dia);

      // draw the round rect
      pdc->DrawGeometry(ppath, ppen);
      ppath->Release();

      // up stroke
      r.top++;
      r.bottom--;

      // get the path
      ppath = NULL;
      pfactory->CreatePathGeometry(&ppath);
      GetRoundBottomRight(ppath, r, dia);

      // draw the round rect
      pdc->DrawGeometry(ppath, ppen);
      ppath->Release();
   }

   ppen->Release();

   pfactory->Release();

   // restore page unit
   //pdc->SetPageUnit((Unit)oldPageUnit);
}

//=============================================================================
//
// FillRoundRect()
//
// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
//				first then fills in the rectangle.
//
// Parameters:  pdc	- [in]	pointer to the Graphics device
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the brush
//				radius		- [in]  radius of the rounded corner
//
// Returns:     None
//
void graphics_round_rect::FillRoundRect(Graphics* pdc, Rect r,  Color color, int radius)
{
   SolidBrush sbr(color);
   FillRoundRect(pdc, &sbr, r, color, radius);
}

//=============================================================================
//
// FillRoundRect()
//
// Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
//				first then fills in the rectangle.
//
// Parameters:  pdc	- [in]	pointer to the Graphics device
//				pBrush		- [in]  pointer to a Brush
//				r			- [in]	Rect that defines the round rectangle boundaries
//				color		- [in]	Color value for the border (needed in case the
//									brush is a type other than solid)
//				radius		- [in]  radius of the rounded corner
//
// Returns:     None
//
void graphics_round_rect::FillRoundRect(Graphics* pdc, Brush* pBrush, Rect r, Color border, int radius)
{
   int dia	= 2*radius;

   // set to pixel mode
   int oldPageUnit = pdc->SetPageUnit(UnitPixel);

   // define the pen
   Pen pen(border, 1);
   pen.SetAlignment(PenAlignmentCenter);

   // get the corner path
   GraphicsPath path;

   // get path
   GetRoundRectPath(&path, r, dia);

   // fill
   pdc->FillPath(pBrush, &path);

   // draw the border last so it will be on top in case the color is different
   pdc->DrawPath(&pen, &path);

   // restore page unit
   pdc->SetPageUnit((Unit)oldPageUnit);
}
