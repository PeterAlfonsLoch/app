#include "framework.h"
#include <math.h>


os_simple_path::os_simple_path()
{

   m_bFill  = false;

   //m_ppath = new Gdiplus::GraphicsPath();

   m_ppath  = NULL;

   m_psink  = NULL;

}

os_simple_path::~os_simple_path()
{

   if(m_ppath != NULL)
   {
         
      m_ppath->Release();
         
      m_ppath = NULL;

   }


}

bool os_simple_path::prepare(D2D1_POINT_2F pt)
{

   if(m_psink == NULL)
   {
      
      m_ppath->Open(&m_psink);

      m_psink->BeginFigure(pt, m_bFill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);

      if(m_efillmode == ::ca::fill_mode_winding)
      {

         m_psink->SetFillMode(D2D1_FILL_MODE_WINDING);

      }
      else if(m_efillmode == ::ca::fill_mode_alternate)
      {

         m_psink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);

      }

   }
   else
   {

      m_psink->AddLine(pt);

   }

   return true;

}

bool os_simple_path::add_arc(const RECT & rect, int iStart, int iAngle)
{

   D2D1_POINT_2F pt;

   D2D1_ARC_SEGMENT arcseg;

   get_arc(pt, arcseg, rect, iStart, iAngle);

   if(!prepare(pt))
      return false;

   m_psink->AddArc(arcseg);

   return true;

}

bool os_simple_path::add_line(int x1, int y1, int x2, int y2)
{

   D2D1_POINT_2F pt;

   pt.x = x1;
   pt.y = y1;

   if(!prepare(pt))
      return false;

   pt.x = x2;
   pt.y = y2;

   m_psink->AddLine(pt);

   return true;

}

bool os_simple_path::add_lines(LPPOINT lpa, int iCount)
{

   if(lpa == NULL || iCount <= 0)
      return true;

   
   D2D1_POINT_2F pt;

   pt.x = lpa[0].x;
   pt.y = lpa[0].y;

   if(!prepare(pt))
      return false;

   iCount--;

   if(iCount <= 0)
      return true;

   D2D1_POINT_2F * points = new D2D1_POINT_2F[iCount];

   for(int i = 0; i < iCount; i++)
   {
      
      points[i].x = lpa[i].x;
   
      points[i].y = lpa[i].y;

   }

   m_psink->AddLines(points, iCount);

   delete points;

   return true;

}

bool os_simple_path::get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, int iStart, int iAngle)
{

   float pi = 3.1415927f;

   D2D1_POINT_2F ptCenter;
   
   ptCenter.x = ((FLOAT) rect.left + (FLOAT) rect.right) / 2.0f;
   ptCenter.y = ((FLOAT) rect.top + (FLOAT) rect.bottom) / 2.0f;

   float rx = (FLOAT) rect.right    - ptCenter.x;
   float ry = (FLOAT) rect.bottom   - ptCenter.y;

   pt.x = ptCenter.x + cos(iStart * pi / 180.0f) * rx;
   pt.y = ptCenter.y - sin(iStart * pi / 180.0f) * ry;

   arcseg.point.x = ptCenter.x + cos((iStart + iAngle) * pi / 180.0f) * rx;
   arcseg.point.y = ptCenter.y + sin((iStart + iAngle) * pi / 180.0f) * ry;

   if(iAngle > 0)
   {
      arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;
   }
   else
   {
      arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
   }

   if(abs(iAngle) < 180)
   {
      arcseg.arcSize = D2D1_ARC_SIZE_SMALL;
   }
   else
   {
      arcseg.arcSize = D2D1_ARC_SIZE_LARGE;
   }
   
   arcseg.rotationAngle = abs(iAngle);
      
   arcseg.size.width    = rx;

   arcseg.size.height   = ry;

   return true;

}

bool os_simple_path::begin_figure(bool bFill, ::ca::e_fill_mode efillmode)
{

   m_bFill        = true;

   m_efillmode    = efillmode;

   return true;

}

bool os_simple_path::end_figure(bool bClose)
{

   if(bClose)
   {

      m_psink->EndFigure(D2D1_FIGURE_END_CLOSED);

   }
   else
   {

      m_psink->EndFigure(D2D1_FIGURE_END_OPEN);

   }

   m_bFill = true;

   return true;

}


ID2D1PathGeometry * os_simple_path::get_os_data()
{
   
   if(m_psink != NULL)
   {
   
      m_psink->Close();

      m_psink->Release();

      m_psink = NULL;

   }

   return m_ppath;

}


bool os_simple_path::add_rect(const RECT & rect)
{
   
   D2D1_POINT_2F pt;

   pt.x = rect.left;
   pt.y = rect.top;

   if(!prepare(pt))
      return false;

   pt.x = rect.right;
   pt.y = rect.top;

   m_psink->AddLine(pt);

   pt.x = rect.right;
   pt.y = rect.bottom;

   m_psink->AddLine(pt);

   pt.x = rect.left;
   pt.y = rect.bottom;

   m_psink->AddLine(pt);

   pt.x = rect.left;
   pt.y = rect.top;

   m_psink->AddLine(pt);

   return true;

}




