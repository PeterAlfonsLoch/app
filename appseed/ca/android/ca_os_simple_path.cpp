#include "framework.h"



os_simple_path::os_simple_path()
{

   m_bFill        = false;
   m_efillmode    = ::ca2::fill_mode_winding;

}

os_simple_path::~os_simple_path()
{

}


bool os_simple_path::add_arc(const RECT & rect, int32_t iStart, int32_t iAngle)
{

   if(width(rect) <= 0 || height(rect) <= 0)
      return true;

   element e;

   e.m_etype               = element::type_arc;
   e.m_arc.m_xCenter       = ((double) rect.right + (double) rect.left) / 2.0;
   e.m_arc.m_yCenter       = ((double) rect.bottom + (double) rect.top) / 2.0;
   e.m_arc.m_dRadiusX      = (double) rect.right - e.m_arc.m_xCenter;
   e.m_arc.m_dRadiusY      = (double) rect.bottom - e.m_arc.m_yCenter;
   e.m_arc.m_dAngle1        = iStart * 3.1415 / 180.0;
   e.m_arc.m_dAngle2        = e.m_arc.m_dAngle1 + iAngle * 3.1415 / 180.0;

   m_elementa.add(e);

   return true;

}

bool os_simple_path::add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{

   element e;

   e.m_etype               = element::type_line;
   e.m_line.m_x1           = x1;
   e.m_line.m_y1           = y1;
   e.m_line.m_x2           = x2;
   e.m_line.m_y2           = y2;

   m_elementa.add(e);

   return true;

}

bool os_simple_path::begin_figure(bool bFill, ::ca2::e_fill_mode efillmode)
{

   m_bFill = bFill;

   m_efillmode = efillmode;


}

bool os_simple_path::end_figure(bool bClose)
{

   if(bClose)
   {

      element e;

      e.m_etype               = element::type_close;

      m_elementa.add(e);

   }

   return true;

}
