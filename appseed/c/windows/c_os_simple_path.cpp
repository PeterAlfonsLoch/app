#include "framework.h"
#undef new   
#include <gdiplus.h>


os_simple_path::os_simple_path()
{

   m_bFill        = false;
   m_efillmode    = ::ca::fill_mode_winding;
   m_ppath        = new Gdiplus::GraphicsPath();

}

os_simple_path::~os_simple_path()
{

   if(m_ppath != NULL)
   {
         
      delete m_ppath;
         
      m_ppath = NULL;

   }


}


bool os_simple_path::add_arc(const RECT & rect, int iStart, int iAngle)
{

   Gdiplus::Rect rectBound;

   rectBound.X       = rect.left;
   rectBound.Y       = rect.top;
   rectBound.Width   = width(rect);
   rectBound.Height  = height(rect);
   
   return m_ppath->AddArc(rectBound, iStart, iAngle) == Gdiplus::Ok;

}

bool os_simple_path::add_line(int x1, int y1, int x2, int y2)
{

   return m_ppath->AddLine(x1, y1, x2, y2) == Gdiplus::Ok;

}

bool os_simple_path::begin_figure(bool bFill, ::ca::e_fill_mode efillmode)
{
   
   m_bFill = bFill;

   m_efillmode = efillmode;

   if(efillmode == ::ca::fill_mode_alternate)
   {
      
      return m_ppath->SetFillMode(Gdiplus::FillModeAlternate) == Gdiplus::Ok;
   
   }
   else
   {

      return m_ppath->SetFillMode(Gdiplus::FillModeWinding) == Gdiplus::Ok;

   }

}

bool os_simple_path::end_figure(bool bClose)
{
   
   if(bClose)
   {
      return m_ppath->CloseFigure() == Gdiplus::Ok;
   }

   return true;

}
