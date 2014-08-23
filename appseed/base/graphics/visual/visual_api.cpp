#include "framework.h"


namespace visual
{


   api::api(sp(::aura::application) papp) :
      element(papp)
   {

   }


   api::~api()
   {

   }


   void api::DrawBeziers(
      ::draw2d::graphics                     *pdc,
      LPPOINT             lppoints,
      int32_t                  iCount,
      double               dRateX,
      LPPOINT               lppointOffset)
   {

      rect clipRect;

      size viewportExt = pdc->GetViewportExt();
      point viewportOrg = pdc->GetViewportOrg();

      pdc->OffsetViewportOrg(
         lppointOffset->x,
         lppointOffset->y);

      pdc->ScaleViewportExt((int32_t) dRateX, 1, 1, 1);

      pdc->BeginPath();
      pdc->PolyBezier(lppoints, iCount);
      pdc->EndPath();
      pdc->StrokePath();

      pdc->SetWindowExt(viewportExt);
      pdc->SetViewportOrg(viewportOrg);

   }

   void api::DrawAndFillBeziers(
      ::draw2d::graphics                     *pdc,
      LPPOINT             lppoints,
      int32_t                  iCount,
      double               dRateX,
      LPPOINT               lppointOffset)
   {

      rect clipRect;

      size viewportExt = pdc->GetViewportExt();
      point viewportOrg = pdc->GetViewportOrg();

      pdc->OffsetViewportOrg(
         lppointOffset->x,
         lppointOffset->y);

      pdc->ScaleViewportExt((int32_t) dRateX, 1, 1, 1);

      pdc->BeginPath();
      pdc->PolyBezier(lppoints, iCount);
      pdc->EndPath();
      pdc->StrokeAndFillPath();

      pdc->SetWindowExt(viewportExt);
      pdc->SetViewportOrg(viewportOrg);

   }

   void api::DrawAndFillBeziers(
      ::draw2d::graphics                     *pdc,
      array<point_array, point_array &> *
                            lpglyph,
      double               dRateX,
      LPPOINT               lppointOffset)
   {

      rect clipRect;

      size viewportExt = pdc->GetViewportExt();
      point viewportOrg = pdc->GetViewportOrg();

      pdc->OffsetViewportOrg(
         lppointOffset->x,
         lppointOffset->y);

      pdc->ScaleViewportExt((int32_t)(dRateX * 1000.0), 1, 1, 1);

      for(int32_t i = 0; i < lpglyph->get_size(); i++)
      {
         pdc->PolyBezier(lpglyph->element_at(i).get_data(), (int32_t) lpglyph->element_at(i).get_size());
      }

      pdc->SetWindowExt(viewportExt);
      pdc->SetViewportOrg(viewportOrg);

   }

   void api::EmbossedTextOut(
      ::draw2d::graphics *             pdc,
      const RECT &            rect,
      double            dRateX,
      double            dHeight,
      const char *      psz,
      LPINT             lpiCharsPositions,
      int32_t               iCharsPositions,
      int32_t               iOffset)
   {
         ::rect clipRect;

   //      int32_t iOldMapMode = ::GetMapMode(pdc->m_hDC);
   //      point viewportOrg;
   //      ::draw2d::font * pfont = pdc->get_current_font();
   //      ASSERT(pfont != NULL);
   //      VERIFY(::GetViewportOrgEx(pdc->m_hDC, &viewportOrg));

   //      VERIFY(::OffsetViewportOrgEx(
   //         pdc->m_hDC,
   //         rect.left,
   //         rect.top,
   //         NULL));
   //      VERIFY(::SetMapMode(pdc->m_hDC, MM_ANISOTROPIC));
   //      if(floatRateX == 0.0)
   //         floatRateX = 1.0;
   //      VERIFY(::ScaleViewportExtEx(pdc->m_hDC, floatRateX * 30000.0, 10000, 1, 1, NULL));

   //      VERIFY(::SelectObject(pdc->m_hDC, pfont->m_hObject));

         pdc->TextOut(rect.left, rect.top, psz);
         pdc->BeginPath();
         pdc->TextOut(rect.left, rect.top, psz);
         pdc->EndPath();
         pdc->StrokePath();


   //      VERIFY(::SetMapMode(pdc->m_hDC, iOldMapMode));
   //      VERIFY(::SetViewportOrgEx(
   //         pdc->m_hDC,
   //         viewportOrg.x,
   //         viewportOrg.y,
   //         NULL));
   }


   void api::EmbossedTextOut(
      ::draw2d::graphics *          pdc,
      const char *   psz,
      int32_t            iLeft,
      int32_t            iTop,
      int32_t            iWidth,
      COLORREF       crText,
      COLORREF       crOutline,
      int32_t            iLen)
   {
         rect clipRect;

   //      int32_t iOldMapMode = ::GetMapMode(pdc->m_hDC);
   //      point viewportOrg;
   //      ::draw2d::font * pfont = pdc->get_current_font();
   //      ASSERT(pfont != NULL);
   //      VERIFY(::GetViewportOrgEx(pdc->m_hDC, &viewportOrg));

   //      VERIFY(::OffsetViewportOrgEx(
   //         pdc->m_hDC,
   //         rect.left,
   //         rect.top,
   //         NULL));
   //      VERIFY(::SetMapMode(pdc->m_hDC, MM_ANISOTROPIC));
   //      if(floatRateX == 0.0)
   //         floatRateX = 1.0;
   //      VERIFY(::ScaleViewportExtEx(pdc->m_hDC, floatRateX * 30000.0, 10000, 1, 1, NULL));

   //      VERIFY(::SelectObject(pdc->m_hDC, pfont->m_hObject));

         string str;
         str = ::str::international::utf8_to_unicode(psz);

#ifdef WINDOWSEX
         ::SetTextColor((HDC)pdc->get_os_data(), crOutline);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft - iWidth, iTop, str, iLen);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft, iTop - iWidth, str, iLen);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft + iWidth, iTop, str, iLen);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft, iTop + iWidth, str, iLen);

         ::SetTextColor((HDC)pdc->get_os_data(), crText);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft, iTop, str, iLen);
#endif

         //pdc->TextOut(rect.left, rect.top, str);
   //      pdc->BeginPath();
   //      ::TextOutW((HDC)pdc->get_os_data(), rect.left, rect.top, lpcsz, iLen);
         //pdc->TextOut(rect.left, rect.top, str);
   //      pdc->EndPath();
   //      pdc->StrokePath();


   //      VERIFY(::SetMapMode(pdc->m_hDC, iOldMapMode));
   //      VERIFY(::SetViewportOrgEx(
   //         pdc->m_hDC,
   //         viewportOrg.x,
   //         viewportOrg.y,
   //         NULL));
   }

   void api::SimpleTextOut(
      ::draw2d::graphics *          pdc,
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

      pdc->TextOut(lpcrect.left, lpcrect.top, psz);
      return;

      string str;
      str = ::str::international::utf8_to_unicode(psz);
      ::TextOutU((HDC)pdc->get_os_data(), lpcrect.left, lpcrect.top, str, (int32_t) str.get_length());
   }


   void api::EmbossedTextOut(::draw2d::graphics * pdc, const RECT & rect, double dHeight, double dRateX, const char * psz)
   {
         pdc->TextOut(rect.left, rect.top, psz);
         pdc->BeginPath();
         pdc->TextOut(rect.left, rect.top, psz);
         pdc->EndPath();
         pdc->StrokePath();

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




