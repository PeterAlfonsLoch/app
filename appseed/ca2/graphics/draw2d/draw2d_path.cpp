#include "framework.h"


namespace draw2d
{


   path::path()
   {

      m_bUpdated     = false;
      m_bFill        = false;
      m_efillmode    = ::draw2d::fill_mode_winding;
      m_bHasPoint    = false;

   }

   path::path(::ca2::application * papp) :
      element(papp)
   {

      m_bUpdated     = false;
      m_bFill        = false;
      m_efillmode    = ::draw2d::fill_mode_winding;
      m_bHasPoint    = false;

   }

   path::~path()
   {

   }


   bool path::has_current_point()
   {

      return m_bHasPoint;

   }

   point path::last_point()
   {

      if(!m_bHasPoint)
         throw "there is no point";

      return m_pt;

   }



   bool path::add_arc(const RECT & rect, int32_t iStart, int32_t iAngle)
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

      m_bHasPoint = true;
      m_pt.x = (LONG) (e.m_arc.m_xCenter + e.m_arc.m_dRadiusX * cos(e.m_arc.m_dAngle2));
      m_pt.y = (LONG) (e.m_arc.m_yCenter + e.m_arc.m_dRadiusY * sin(e.m_arc.m_dAngle2));

      m_bUpdated = false;

      return true;

   }

   bool path::add_move(int32_t x, int32_t y)
   {

      element e;

      e.m_etype               = element::type_move;
      e.m_move.m_x            = x;
      e.m_move.m_y            = y;

      m_elementa.add(e);

      m_bHasPoint = true;
      m_pt.x = x;
      m_pt.y = y;

      m_bUpdated = false;


      return true;

   }

   bool path::add_line(int32_t x, int32_t y)
   {

      if(!has_current_point())
      {
         return add_move(x, y);
      }

      element e;

      e.m_etype               = element::type_line;
      e.m_line.m_x            = x;
      e.m_line.m_y            = y;

      m_elementa.add(e);

      m_bHasPoint = true;
      m_pt.x = x;
      m_pt.y = y;

      m_bUpdated = false;

      return true;

   }

   bool path::add_line(int32_t x, int32_t y, int32_t x2, int32_t y2)
   {

      bool bOk1 = add_line(x, y);
      
      bool bOk2 = add_line(x2, y2);

      return bOk1 && bOk2;

   }


   bool path::begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {

      m_bFill = bFill;

      m_efillmode = efillmode;

      m_bHasPoint = false;

      m_bUpdated = false;

      return true;

   }

   bool path::end_figure(bool bClose)
   {


      element e;

      e.m_etype               = element::type_end;
      
      e.m_end.m_bClose        = bClose;

      m_elementa.add(e);

      m_bUpdated = false;

      return true;

   }







   bool path::add_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {
      
      rect rect;

      rect.left      = x1;
      rect.top       = y1;
      rect.right     = x2;
      rect.bottom    = y2;

      return add_rect(rect);

   }

   bool path::add_rect(LPCRECT lpcrect)
   {

      return add_rect(lpcrect->left, lpcrect->top, lpcrect->right, lpcrect->bottom);

   }

   bool path::add_line(point p1, point p2)
   {

      return add_line(p1.x, p1.y, p2.x, p2.y);

   }

   bool path::add_line(point p)
   {

      return add_line(p.x, p.y);

   }

   bool path::add_lines(const POINT * lppoint, int32_t nCount)
   {

      bool bOk = true;

      for(int32_t i = 0; i < nCount; i++)
      {

         if(!add_line(lppoint[i]))
            bOk = false;
      }

      return bOk;

   }

   bool path::add_move(point p)
   {

      return add_move(p.x, p.y);

   }

   void * path::detach()
   {

      throw interface_only_exception(get_app());

   }


   void path::get_bounding_rect(LPRECT lprect)
   {

      lprect->right     = 0x80000000;
      lprect->left      = 0x7fffffff;
      lprect->bottom    = 0x80000000;
      lprect->top       = 0x7fffffff;


      for(int i = 0; i < m_elementa.get_count(); i++)
      {
         get_bounding_rect(lprect, m_elementa[i]);
      }

   }

   void path::get_bounding_rect(LPRECT lprect, element & e)
   {

      switch(e.m_etype)
      {
      case ::draw2d::path::element::type_arc:
         get_bounding_rect(lprect, e.m_arc);
         break;
      case ::draw2d::path::element::type_line:
         get_bounding_rect(lprect, e.m_line);
         break;
      case ::draw2d::path::element::type_move:
         get_bounding_rect(lprect, e.m_move);
         break;
      case ::draw2d::path::element::type_end:
         {

         }
         break;
      default:
         throw "unexpected simple os graphics element type";
      }




   }

   void path::get_bounding_rect(LPRECT lprect, arc & a)
   {

      rect r;

      r.left         = (LONG) (a.m_xCenter - a.m_dRadiusX);

      r.right        = (LONG) (a.m_xCenter + a.m_dRadiusX);

      r.top          = (LONG) (a.m_yCenter - a.m_dRadiusY);

      r.bottom       = (LONG) (a.m_yCenter + a.m_dRadiusY);

      POINT pt1;
      
      POINT pt2;

      lprect->left   = (LONG) min(a.m_xCenter, lprect->left);

      lprect->top    = (LONG) min(a.m_yCenter, lprect->top);

      lprect->right  = (LONG) max(a.m_xCenter, lprect->right);

      lprect->bottom = (LONG) max(a.m_yCenter, lprect->bottom);

//      double e = a.m_dRadiusY / a.m_dRadiusX;

      double f1 = a.m_dAngle1;
      
      double f2 = a.m_dAngle2;
      
      pt1.x          = (LONG) (a.m_xCenter + a.m_dRadiusX * cos(f1));

      pt1.y          = (LONG) (a.m_yCenter - a.m_dRadiusY * sin(f1));

      pt2.x          = (LONG) (a.m_xCenter + a.m_dRadiusX * cos(f2));

      pt2.y          = (LONG) (a.m_yCenter - a.m_dRadiusY * sin(f2));

      lprect->left   = (LONG) min(pt1.x       , lprect->left);

      lprect->top    = (LONG) min(pt1.y       , lprect->top);

      lprect->right  = (LONG) max(pt1.x       , lprect->right);

      lprect->bottom = (LONG) max(pt1.y       , lprect->bottom);

      lprect->left   = (LONG) min(pt2.x       , lprect->left);

      lprect->top    = (LONG) min(pt2.y       , lprect->top);

      lprect->right  = (LONG) max(pt2.x       , lprect->right);

      lprect->bottom = (LONG) max(pt2.y       , lprect->bottom);

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         lprect->left   = (LONG) min(r.right        , lprect->left);

         lprect->right  = (LONG) max(r.right        , lprect->right);

      }

      f1 -= System.math().GetPi() / 2.0;

      f2 -= System.math().GetPi() / 2.0;

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         lprect->top    = (LONG) min(r.top        , lprect->top);

         lprect->bottom = (LONG) max(r.top        , lprect->bottom);

      }

      f1 -= System.math().GetPi() / 2.0;

      f2 -= System.math().GetPi() / 2.0;

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         lprect->left   = (LONG) min(r.left        , lprect->left);

         lprect->right  = (LONG) max(r.left        , lprect->right);

      }

      f1 -= System.math().GetPi() / 2.0;

      f2 -= System.math().GetPi() / 2.0;

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         lprect->top    = (LONG) min(r.bottom        , lprect->top);

         lprect->bottom = (LONG) max(r.bottom        , lprect->bottom);

      }

   }

   void path::get_bounding_rect(LPRECT lprect, move & m)
   {
      
      lprect->left   = (LONG) min(m.m_x, lprect->left);

      lprect->top    = (LONG) min(m.m_y, lprect->top);

      lprect->right  = (LONG) max(m.m_x, lprect->right);

      lprect->bottom = (LONG) max(m.m_y, lprect->bottom);

   }


   void path::get_bounding_rect(LPRECT lprect, line & l)
   {

      lprect->left   = (LONG) min(l.m_x, lprect->left);

      lprect->top    = (LONG) min(l.m_y, lprect->top);

      lprect->right  = (LONG) max(l.m_x, lprect->right);

      lprect->bottom = (LONG) max(l.m_y, lprect->bottom);

   }


   
} // namespace draw2d






