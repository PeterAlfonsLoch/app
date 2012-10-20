#include "framework.h"
#undef new   
#include <gdiplus.h>


simple_path::simple_path(bool bFill)
{

   m_bFill = bFill;
   m_ppath = new Gdiplus::GraphicsPath();

}

simple_path::~simple_path()
{

   if(m_ppath != NULL)
   {
         
      delete m_ppath;
         
      m_ppath = NULL;

   }


}


bool simple_path::add_arc(const RECT & rect, int iStart, int iAngle)
{

   Gdiplus::Rect rectBound;

   rectBound.X       = rect.left;
   rectBound.Y       = rect.top;
   rectBound.Width   = width(rect);
   rectBound.Height  = height(rect);
   
   return m_ppath->AddArc(rectBound, iStart, iAngle) == Gdiplus::Ok;

}

bool simple_path::add_line(int x1, int y1, int x2, int y2)
{

   return m_ppath->AddLine(x1, y1, x2, y2) == Gdiplus::Ok;

}

bool simple_path::close_figure()
{
   
   if(!m_bFill)
      return true;

   return m_ppath->CloseFigure() == Gdiplus::Ok;

}