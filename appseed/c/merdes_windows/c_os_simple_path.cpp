#include "framework.h"
#include <math.h>


simple_path::simple_path(bool bFill)
{

   m_bFill  = bFill;

   //m_ppath = new Gdiplus::GraphicsPath();

   m_ppath  = NULL;

   m_psink  = NULL;

}

simple_path::~simple_path()
{

   if(m_ppath != NULL)
   {
         
      m_ppath->Release();
         
      m_ppath = NULL;

   }


}


bool simple_path::add_arc(const RECT & rect, int iStart, int iAngle)
{

   D2D1_POINT_2F pt;

   D2D1_ARC_SEGMENT arcseg;

   get_arc(pt, arcseg, rect, iStart, iAngle);

   if(m_psink == NULL)
   {
      
      m_ppath->Open(&m_psink);

      m_psink->BeginFigure(pt, m_bFill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);

   }
   else
   {

      m_psink->AddLine(pt);

   }

   m_psink->AddArc(arcseg);

   return true;

}

bool simple_path::add_line(int x1, int y1, int x2, int y2)
{

   D2D1_POINT_2F pt;

   pt.x = x1;
   pt.y = y1;

   if(m_psink == NULL)
   {
      
      m_ppath->Open(&m_psink);

      m_psink->BeginFigure(pt, m_bFill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);

   }
   else
   {

      m_psink->AddLine(pt);

   }

   pt.x = x2;
   pt.y = y2;

   m_psink->AddLine(pt);

   return true;

}

bool simple_path::get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, int iStart, int iAngle)
{

   D2D1_POINT_2F ptCenter;
   
   ptCenter.x = ((FLOAT) rect.left + (FLOAT) rect.right) / 2.0f;
   ptCenter.y = ((FLOAT) rect.top + (FLOAT) rect.bottom) / 2.0f;

   float rx = (FLOAT) rect.right - ptCenter.X;

   float ry = (FLOAT) rect.bottom - ptCenter.Y;

   float pi = 3.1415927f;

   pt.x = ptCenter.X + cos(iStart * pi / 180.0f) * rx;
   pt.y = ptCenter.Y - sin(iStart * pi / 180.0f) * ry;

   arcSeg.point.X = ptCenter.X + cos((iStart + iAngle) * pi / 180.0f) * rx;
   arcSeg.point.Y = ptCenter.Y + sin((iStart + iAngle) * pi / 180.0f) * ry;

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


ID2D1PathGeometry * simple_path::get_os_data()
{
   
   if(m_psink != NULL)
   {
   
      m_psink->Close();

      m_psink->Release();

      m_psink = NULL;

   }

   return m_ppath;

}


bool simple_path::close_figure()
{

   if(m_psink != NULL)
   {
   
      m_psink->Close();

      m_psink->Release();

      m_psink = NULL;

   }

   if(FAILED(m_ppath->CloseFigure()))
   {

      return false;

   }

   return true;

}


bool simple_path::add_rect(const RECT & rect)
{
   
   D2D1_POINT_2F pt;

   pt.x = rect.left;
   pt.y = rect.top;

   if(m_psink == NULL)
   {
      
      m_ppath->Open(&m_psink);

      m_psink->BeginFigure(pt, m_bFill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);

   }
   else
   {

      m_psink->AddLine(pt);

   }

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

}