#include "framework.h"
#undef new   
#include <gdiplus.h>


simple_path::simple_path()
{

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