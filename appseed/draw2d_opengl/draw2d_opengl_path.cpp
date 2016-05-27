#include "framework.h"


#undef new


namespace draw2d_opengl
{



   path::path(::aura::application * papp)
   {

//      m_ppath = NULL;


   }


   path::~path()
   {

      destroy();

   }


   //plusplus::GraphicsPath * path::get_os_path(plusplus::Graphics * pgraphics)
   //{

   //   if(m_bUpdated)
   //      return m_ppath;

   //   destroy();

   //   create(pgraphics);

   //   return m_ppath;

   //}


   pointd path::internal_last_point()
   {

      if(m_bHasPointInternal)
      {

         //return pointd((LONG) m_ptInternal.X, (LONG) m_ptInternal.Y);

         return pointd(0, 0);

      }
      else
      {

         throw simple_exception(get_app(), "path does not have last point");

      }

   }


   bool path::internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {

      //return m_ppath->StartFigure() == plusplus::Status::Ok;

      return true;

   }

   bool path::internal_end_figure(bool bClose)
   {

      //if(bClose)
      //{

      //   m_bHasPointInternal = false;
      //   return m_ppath->CloseFigure() == plusplus::Status::Ok;

      //}
      //else
      //{
      //   m_bHasPointInternal = false;
      //   return true;

      //}

      return true;
   }

   bool path::internal_add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      ////bool bOk1 = true;

      ////if(m_bHasPointInternal)
      ////{

      ////   bOk1 = m_ppath->AddLine(m_ptInternal.X, m_ptInternal.Y, (FLOAT) x1, (FLOAT) y1) == plusplus::Status::Ok;

      ////}

      ////bool bOk2 = m_ppath->AddLine(x1, y1, x2, y2) == plusplus::Status::Ok;

      ////m_ptInternal.X = (plusplus::REAL) x2;
      ////m_ptInternal.Y = (plusplus::REAL) y2;

      ////m_bHasPointInternal = true;

      //return bOk1 && bOk2;

      return true;
   }


   bool path::internal_add_rect(int32_t x,int32_t y,int32_t cx,int32_t cy)
   {

      //plusplus::Rect rect(x,y,cx,cy);

      //bool bOk2 = m_ppath->AddRectangle(rect) == plusplus::Status::Ok;


      //return bOk2;

      return true;
   }

   bool path::internal_add_line(int32_t x, int32_t y)
   {

      //bool bOk1 = true;

      //if(m_bHasPointInternal)
      //{

      //   bOk1 = m_ppath->AddLine(m_ptInternal.X, m_ptInternal.Y, (FLOAT) x, (FLOAT) y) == plusplus::Status::Ok;

      //}

      //m_bHasPointInternal = true;

      //m_ptInternal.X = (plusplus::REAL) x;
      //m_ptInternal.Y = (plusplus::REAL) y;

      //return bOk1;

      return true;
   }

   pointd path::internal_current_point()
   {

      return last_point();

   }


   bool path::internal_add_move(int32_t x, int32_t y)
   {

      //if(!m_bHasPointInternal)
      //{
      //   internal_begin_figure(m_bFill,m_efillmode);
      //}

      //m_ptInternal.X   = (plusplus::REAL) x;
      //m_ptInternal.Y   = (plusplus::REAL) y;
      //m_bHasPointInternal     = true;


      return true;

   }

   bool path::internal_add_rect(double x,double y,double cx,double cy)
   {

      //plusplus::RectF rectf((plusplus::REAL)x,(plusplus::REAL)y,(plusplus::REAL)cx,(plusplus::REAL)cy);

      //bool bOk2 = m_ppath->AddRectangle(rectf) == plusplus::Status::Ok;


//      return bOk2;

      return true;

   }


   bool path::internal_add_move(double x,double y)
   {

      if(!m_bHasPointInternal)
      {
         internal_begin_figure(m_bFill,m_efillmode);
      }

      ////m_ptInternal.X   = (plusplus::REAL) x;
      ////m_ptInternal.Y   = (plusplus::REAL) y;
      //m_bHasPointInternal     = true;


      return true;

   }


   //bool path::create(plusplus::Graphics * pgraphics)
   //{

   //   //if(m_efillmode == ::draw2d::fill_mode_winding)
   //   //{

   //   //   m_ppath = new plusplus::GraphicsPath(plusplus::FillModeWinding);

   //   //}
   //   //else
   //   //{

   //   //   m_ppath = new plusplus::GraphicsPath(plusplus::FillModeAlternate);

   //   //}

   //   //m_bHasPoint = false;

   //   //m_ptInternal.X = 69;

   //   //m_ptInternal.Y = 69;

   //   //m_bHasPointInternal = false;

   //   ////if(m_elementa.get_count() != 1 && m_elementa[0].m_etype != element::type_string)
   //   //{
   //   //   //internal_begin_figure(m_bFill,m_efillmode);
   //   //}

   //   //for(int32_t i = 0; i < m_elementa.get_count(); i++)
   //   //{

   //   //   set(pgraphics, m_elementa(i));

   //   //}

   //   return true;

   //}


   bool path::destroy()
   {

      //if(m_ppath != NULL)
      //{

      //   delete m_ppath;

      //   m_ppath = NULL;

      //}

      return true;

   }


   //bool path::set(plusplus::Graphics * pgraphics, const ::draw2d::path::element & e)
   //{

   //   switch(e.m_etype)
   //   {
   //   case ::draw2d::path::element::type_arc:
   //      set(e.u.m_arc);
   //      break;
   //   case ::draw2d::path::element::type_move:
   //      set(e.u.m_move);
   //      break;
   //   case ::draw2d::path::element::type_line:
   //      set(e.u.m_line);
   //      break;
   //   case ::draw2d::path::element::type_rect:
   //      set(e.u.m_rect);
   //      break;
   //   //case ::draw2d::path::element::type_string:
   //   //   set(pgraphics,e.m_stringpath);
   //   //   break;
   //   case ::draw2d::path::element::type_end:
   //      internal_end_figure(e.u.m_end.m_bClose);
   //      break;
   //   default:
   //      throw "unexpected simple os graphics element type";
   //   }

   //   return false;

   //}

   bool path::internal_add_arc(const RECT & rect, double iStart, double iAngle)
   {

      //::plusplus::RectF rectf((plusplus::REAL) rect.left, (plusplus::REAL) rect.top, (plusplus::REAL) width(rect), (plusplus::REAL) height(rect));


      //m_ppath->AddArc(rectf, (plusplus::REAL) iStart, (plusplus::REAL) iAngle);



      return true;

   }


//   bool path::internal_add_string(plusplus::Graphics * pgraphics,int32_t x,int32_t y,const string & strText,::draw2d::font_sp spfont)
//   {
//
//      plusplus::FontFamily fontFamily;
//
//      plusplus::StringFormat format(plusplus::StringFormat::GenericTypographic());
//
//      wstring wstr(strText);
//
//      plusplus::REAL dSize = (plusplus::REAL) spfont->m_dFontSize;
//
//      plusplus::Unit unit = pgraphics->GetPageUnit();
//
//      switch(unit)
//
//      {
//
//      case plusplus::UnitMillimeter:
//         dSize = dSize * 25.4f / pgraphics->GetDpiY();
//         break;
//
//      case plusplus::UnitInch:
//
//         dSize = dSize / pgraphics->GetDpiY();
//         break;
//      case plusplus::UnitPoint:
//
//         dSize = dSize * 72.0f / pgraphics->GetDpiY();
//         break;
//
//      }
//
//      INT iStyle = ((plusplus::Font *) spfont->get_os_data())->GetStyle();
//      ((plusplus::Font *) spfont->get_os_data())->GetFamily(&fontFamily);
////      plusplus::Status status;
//
//      //plusplus::StringFormat format();
//
//      format.SetFormatFlags(format.GetFormatFlags()
//                            | plusplus::StringFormatFlagsNoClip | plusplus::StringFormatFlagsMeasureTrailingSpaces
//                            | plusplus::StringFormatFlagsLineLimit | plusplus::StringFormatFlagsNoWrap
//                            | plusplus::StringFormatFlagsNoFitBlackBox);
//
//
//      format.SetLineAlignment(plusplus::StringAlignmentNear);
//
//
//      m_ppath->AddString(wstr, (INT) wstr.get_length(),&fontFamily,iStyle,dSize,plusplus::Point(x,y),&format);
//
//      return true;
//
//   }


   bool path::set( const ::draw2d::path::arc & arc)
   {

      ::rect rect;

      rect.left = (LONG)(arc.m_xCenter - arc.m_dRadiusX);
      rect.right = (LONG)(arc.m_xCenter + arc.m_dRadiusX);
      rect.top = (LONG)(arc.m_yCenter - arc.m_dRadiusY);
      rect.bottom = (LONG)(arc.m_yCenter + arc.m_dRadiusY);
      //if(!m_bHasPointInternal)
      //{

      //   internal_add_move(arc.m_ptEnd.x,arc.m_ptEnd.y);

      //}

      bool bOk = internal_add_arc(rect,(int)(arc.m_dAngle1 * 180.0 / 3.1415),(int)(arc.m_dAngle* 180.0 / 3.1415));


      return bOk;

   }

   bool path::set(const ::draw2d::path::rect & rect)
   {


      return internal_add_rect(rect.m_x, rect.m_y, rect.m_cx, rect.m_cy);

   }

   bool path::set(const ::draw2d::path::line & l)
   {

      internal_add_line((int32_t) l.m_x, (int32_t) l.m_y);

      return true;

   }


   bool path::set(const ::draw2d::path::move & p)
   {

      internal_add_move((int32_t) p.m_x, (int32_t) p.m_y);


      return true;

   }

   //bool path::set(plusplus::Graphics * pgraphics, const ::draw2d::path::string_path & s)
   //{

   //   internal_add_string(pgraphics,(int32_t)s.m_x,(int32_t)s.m_y,s.m_strText,s.m_spfont);

   //   return true;

   //}


} // namespace draw2d_opengl


#define new AURA_NEW