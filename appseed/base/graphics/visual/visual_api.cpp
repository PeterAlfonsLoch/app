//#include "framework.h"


namespace visual
{


   api::api(::aura::application * papp) :
      ::object(papp)
   {

   }


   api::~api()
   {

   }


   void api::DrawBeziers(
      ::draw2d::graphics * pgraphics,
      LPPOINT             lppoints,
      int32_t                  iCount,
      double               dRateX,
      LPPOINT               lppointOffset)
   {

      rect clipRect;

      size viewportExt = pgraphics->GetViewportExt();
      point viewportOrg = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(
         lppointOffset->x,
         lppointOffset->y);

      pgraphics->ScaleViewportExt((int32_t)dRateX, 1, 1, 1);

      pgraphics->BeginPath();
      pgraphics->PolyBezier(lppoints, iCount);
      pgraphics->EndPath();
      pgraphics->StrokePath();

      pgraphics->SetWindowExt(viewportExt);
      pgraphics->SetViewportOrg(viewportOrg);

   }

   void api::DrawAndFillBeziers(
      ::draw2d::graphics * pgraphics,
      LPPOINT             lppoints,
      int32_t                  iCount,
      double               dRateX,
      LPPOINT               lppointOffset)
   {

      rect clipRect;

      size viewportExt = pgraphics->GetViewportExt();
      point viewportOrg = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(
         lppointOffset->x,
         lppointOffset->y);

      pgraphics->ScaleViewportExt((int32_t)dRateX, 1, 1, 1);

      pgraphics->BeginPath();
      pgraphics->PolyBezier(lppoints, iCount);
      pgraphics->EndPath();
      pgraphics->StrokeAndFillPath();

      pgraphics->SetWindowExt(viewportExt);
      pgraphics->SetViewportOrg(viewportOrg);

   }

   void api::DrawAndFillBeziers(
      ::draw2d::graphics * pgraphics,
      array<point_array, point_array &> *
      lpglyph,
      double               dRateX,
      LPPOINT               lppointOffset)
   {

      rect clipRect;

      size viewportExt = pgraphics->GetViewportExt();
      point viewportOrg = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(
         lppointOffset->x,
         lppointOffset->y);

      pgraphics->ScaleViewportExt((int32_t)(dRateX * 1000.0), 1, 1, 1);

      for (int32_t i = 0; i < lpglyph->get_size(); i++)
      {
         pgraphics->PolyBezier(lpglyph->element_at(i).get_data(), (int32_t)lpglyph->element_at(i).get_size());
      }

      pgraphics->SetWindowExt(viewportExt);
      pgraphics->SetViewportOrg(viewportOrg);

   }

   void api::EmbossedTextOut(
      ::draw2d::graphics * pgraphics,
      const RECT &            rect,
      double            dRateX,
      double            dHeight,
      const char *      psz,
      LPINT             lpiCharsPositions,
      int32_t               iCharsPositions,
      int32_t               iOffset)
   {
      ::rect clipRect;



      //      int32_t iOldMapMode = ::GetMapMode(pgraphics->m_hDC);
      //      point viewportOrg;
      //      ::draw2d::font * pfont = pgraphics->get_current_font();
      //      ASSERT(pfont != NULL);
      //      VERIFY(::GetViewportOrgEx(pgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetViewportOrgEx(
      //         pgraphics->m_hDC,
      //         rect.left,
      //         rect.top,
      //         NULL));
      //      VERIFY(::SetMapMode(pgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(floatRateX == 0.0)
      //         floatRateX = 1.0;
      //      VERIFY(::ScaleViewportExtEx(pgraphics->m_hDC, floatRateX * 30000.0, 10000, 1, 1, NULL));

      //      VERIFY(::SelectObject(pgraphics->m_hDC, pfont->m_hObject));

      pgraphics->TextOut(rect.left, rect.top, psz);
      pgraphics->BeginPath();
      pgraphics->TextOut(rect.left, rect.top, psz);
      pgraphics->EndPath();
      pgraphics->StrokePath();


      //      VERIFY(::SetMapMode(pgraphics->m_hDC, iOldMapMode));
      //      VERIFY(::SetViewportOrgEx(
      //         pgraphics->m_hDC,
      //         viewportOrg.x,
      //         viewportOrg.y,
      //         NULL));
   }


   void api::EmbossedTextOut(
      ::draw2d::graphics * pgraphics,
      const char *   psz,
      int32_t            iLeft,
      int32_t            iTop,
      int32_t            iWidth,
      COLORREF       crText,
      COLORREF       crOutline,
      int32_t            iLen)
   {
      rect clipRect;

      //      int32_t iOldMapMode = ::GetMapMode(pgraphics->m_hDC);
      //      point viewportOrg;
      //      ::draw2d::font * pfont = pgraphics->get_current_font();
      //      ASSERT(pfont != NULL);
      //      VERIFY(::GetViewportOrgEx(pgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetViewportOrgEx(
      //         pgraphics->m_hDC,
      //         rect.left,
      //         rect.top,
      //         NULL));
      //      VERIFY(::SetMapMode(pgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(floatRateX == 0.0)
      //         floatRateX = 1.0;
      //      VERIFY(::ScaleViewportExtEx(pgraphics->m_hDC, floatRateX * 30000.0, 10000, 1, 1, NULL));

      //      VERIFY(::SelectObject(pgraphics->m_hDC, pfont->m_hObject));

      string str;
      str = ::str::international::utf8_to_unicode(psz);

#ifdef WINDOWSEX
      ::SetTextColor((HDC)pgraphics->get_os_data(), crOutline);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft - iWidth, iTop, str, iLen);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop - iWidth, str, iLen);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft + iWidth, iTop, str, iLen);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop + iWidth, str, iLen);

      ::SetTextColor((HDC)pgraphics->get_os_data(), crText);
      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop, str, iLen);
#endif

      //pgraphics->TextOut(rect.left, rect.top, str);
//      pgraphics->BeginPath();
//      ::TextOutW((HDC)pgraphics->get_os_data(), rect.left, rect.top, lpcsz, iLen);
      //pgraphics->TextOut(rect.left, rect.top, str);
//      pgraphics->EndPath();
//      pgraphics->StrokePath();


//      VERIFY(::SetMapMode(pgraphics->m_hDC, iOldMapMode));
//      VERIFY(::SetViewportOrgEx(
//         pgraphics->m_hDC,
//         viewportOrg.x,
//         viewportOrg.y,
//         NULL));
   }

   void api::SimpleTextOut(
      ::draw2d::graphics * pgraphics,
      const RECT &        lpcrect,
      double         dRateX,
      double         dHeight,
      const char *   psz,
      LPINT          lpiCharsPositions,
      int32_t            iCharsPositions,
      int32_t            iOffset)
   {
      UNREFERENCED_PARAMETER(dRateX);
      UNREFERENCED_PARAMETER(dHeight);
      UNREFERENCED_PARAMETER(iOffset);
      UNREFERENCED_PARAMETER(iCharsPositions);
      UNREFERENCED_PARAMETER(lpiCharsPositions);

      pgraphics->TextOut(lpcrect.left, lpcrect.top, psz);
      return;

      string str;
      str = ::str::international::utf8_to_unicode(psz);
      ::TextOutU((HDC)pgraphics->get_os_data(), lpcrect.left, lpcrect.top, str, (int32_t)str.get_length());
   }


   void api::EmbossedTextOut(::draw2d::graphics * pgraphics, const RECT & rect, double dHeight, double dRateX, const char * psz)
   {

      pgraphics->TextOut(rect.left, rect.top, psz);
      pgraphics->BeginPath();
      pgraphics->TextOut(rect.left, rect.top, psz);
      pgraphics->EndPath();
      pgraphics->StrokePath();

   }


   bool api::open()
   {

      return true;

   }


   bool api::close()
   {

      return true;

   }


} // namespace visual




