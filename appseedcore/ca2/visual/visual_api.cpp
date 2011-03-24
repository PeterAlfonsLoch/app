#include "StdAfx.h"

namespace visual
{

   HINSTANCE api::g_hinstanceGdipp = NULL;
   bool api::g_bGdipp = false;
   bool api::g_bGdiEnabled = false;

   void (* api::lpDrawAndFillBeziers1)(
      ::ca::graphics                     *pdc,
      LPPOINT             lppoints,
      int                  iCount,
      float               fRateX,
      LPPOINT               lppointOffset) = NULL;

   void (* api::lpDrawAndFillBeziers2)(
      ::ca::graphics                     *pdc,
      base_array<point_array, point_array &> *
                         lpglyph,
      float               fRateX,
      LPPOINT               lppointOffset) = NULL;


   void (* api::lpEmbossedTextOut1)(
      ::ca::graphics *          pdc,
      LPCRECT         lpcrect,
      float            fRateX,
      float            fHeight,
      const char *   psz) = NULL;

   void (* api::lpEmbossedTextOut2)(
      ::ca::graphics *          pdc,
      LPCRECT        lpcrect,
      float            lRateX,
      float            lHeight,
      const char *   psz,   
      LPINT          lpiCharsPositions,
      int            iCharsPositions,
      int            iOffset) = NULL;

   bool (* api::lpStartup)() = NULL;

   bool (* api::lpShutdown)() = NULL;

   api::api()
   {

   }

   api::~api()
   {

   }
   void api::DrawBeziers(
      ::ca::graphics                     *pdc,
      LPPOINT             lppoints,
      int                  iCount,
      double               dRateX,
      LPPOINT               lppointOffset)
   {
      if(IsGdippEnabled())
      {
         (*lpDrawAndFillBeziers1)(
            pdc,
            lppoints, 
            iCount,
            (float) dRateX,
            lppointOffset);
      }
      else
      {
         rect clipRect;

         size viewportExt = pdc->GetViewportExt();
         point viewportOrg = pdc->GetViewportOrg();

         pdc->OffsetViewportOrg(
            lppointOffset->x,
            lppointOffset->y);

         pdc->ScaleViewportExt((int) dRateX, 1, 1, 1);

         pdc->BeginPath();
         pdc->PolyBezier(lppoints, iCount);
         pdc->EndPath();
         pdc->StrokePath();

         pdc->SetWindowExt(viewportExt);
         pdc->SetViewportOrg(viewportOrg);
      }
   }

   void api::DrawAndFillBeziers(
      ::ca::graphics                     *pdc,
      LPPOINT             lppoints,
      int                  iCount,
      double               dRateX,
      LPPOINT               lppointOffset)
   {
      if(IsGdippEnabled())
      {
         (*lpDrawAndFillBeziers1)(
            pdc,
            lppoints, 
            iCount,
            (float) dRateX,
            lppointOffset);
      }
      else
      {
         rect clipRect;

         size viewportExt = pdc->GetViewportExt();
         point viewportOrg = pdc->GetViewportOrg();

         pdc->OffsetViewportOrg(
            lppointOffset->x,
            lppointOffset->y);

         pdc->ScaleViewportExt((int) dRateX, 1, 1, 1);

         pdc->BeginPath();
         pdc->PolyBezier(lppoints, iCount);
         pdc->EndPath();
         pdc->StrokeAndFillPath();

         pdc->SetWindowExt(viewportExt);
         pdc->SetViewportOrg(viewportOrg);
      }
   }

   void api::DrawAndFillBeziers(
      ::ca::graphics                     *pdc,
      base_array<point_array, point_array &> *
                            lpglyph,
      double               dRateX,
      LPPOINT               lppointOffset)
   {
      if(g_bGdipp)
      {
         (*lpDrawAndFillBeziers2)(
            pdc,
            lpglyph, 
            (float) dRateX,
            lppointOffset);
      }
      else
      {
         rect clipRect;

         size viewportExt = pdc->GetViewportExt();
         point viewportOrg = pdc->GetViewportOrg();

         pdc->OffsetViewportOrg(
            lppointOffset->x,
            lppointOffset->y);

         pdc->ScaleViewportExt((int)(dRateX * 1000.0), 1, 1, 1);

         for(int i = 0; i < lpglyph->get_size(); i++)
         {
            pdc->PolyBezier(lpglyph->element_at(i).get_data(),
               lpglyph->element_at(i).get_size());
         }

         pdc->SetWindowExt(viewportExt);
         pdc->SetViewportOrg(viewportOrg);
      }
   }

   void api::EmbossedTextOut(
      ::ca::graphics *             pdc,
      LPCRECT            lpcrect,
      double            dRateX,
      double            dHeight,
      const char *      psz,   
      LPINT             lpiCharsPositions,
      int               iCharsPositions,
      int               iOffset)
   {
      if(IsGdippEnabled())
      {
         (*lpEmbossedTextOut2)(pdc,
            lpcrect, 
            (float) dRateX,
            (float) dHeight,
            psz,
            lpiCharsPositions,
            iCharsPositions,
            iOffset);
      }
      else
      {
         rect clipRect;

   //      int iOldMapMode = ::GetMapMode(pdc->m_hDC);
   //      point viewportOrg;
   //      ::ca::font * pfont = pdc->GetCurrentFont();
   //      ASSERT(pfont != NULL);
   //      VERIFY(::GetViewportOrgEx(pdc->m_hDC, &viewportOrg));

   //      VERIFY(::OffsetViewportOrgEx(
   //         pdc->m_hDC,
   //         lpcrect->left,
   //         lpcrect->top,
   //         NULL));
   //      VERIFY(::SetMapMode(pdc->m_hDC, MM_ANISOTROPIC));
   //      if(floatRateX == 0.0)
   //         floatRateX = 1.0;
   //      VERIFY(::ScaleViewportExtEx(pdc->m_hDC, floatRateX * 30000.0, 10000, 1, 1, NULL));

   //      VERIFY(::SelectObject(pdc->m_hDC, pfont->m_hObject));

         pdc->TextOut(lpcrect->left, lpcrect->top, psz);
         pdc->BeginPath();
         pdc->TextOut(lpcrect->left, lpcrect->top, psz);
         pdc->EndPath();
         pdc->StrokePath();

         
   //      VERIFY(::SetMapMode(pdc->m_hDC, iOldMapMode));
   //      VERIFY(::SetViewportOrgEx(
   //         pdc->m_hDC,
   //         viewportOrg.x,
   //         viewportOrg.y,
   //         NULL));
      }
   }


   void api::EmbossedTextOut(
      ::ca::graphics *          pdc,
      const char *   psz, 
      int            iLeft,
      int            iTop,
      int            iWidth,
      COLORREF       crText,
      COLORREF       crOutline, 
      int            iLen)
   {
      if(IsGdippEnabled())
      {
         ASSERT(FALSE);
   /*      (*lpEmbossedTextOut2)(pdc,
            lpcrect, 
            floatRateX,
            floatHeight,
            str,
            lpiCharsPositions,
            iCharsPositions,
            iOffset);*/
      }
      else
      {
         rect clipRect;

   //      int iOldMapMode = ::GetMapMode(pdc->m_hDC);
   //      point viewportOrg;
   //      ::ca::font * pfont = pdc->GetCurrentFont();
   //      ASSERT(pfont != NULL);
   //      VERIFY(::GetViewportOrgEx(pdc->m_hDC, &viewportOrg));

   //      VERIFY(::OffsetViewportOrgEx(
   //         pdc->m_hDC,
   //         lpcrect->left,
   //         lpcrect->top,
   //         NULL));
   //      VERIFY(::SetMapMode(pdc->m_hDC, MM_ANISOTROPIC));
   //      if(floatRateX == 0.0)
   //         floatRateX = 1.0;
   //      VERIFY(::ScaleViewportExtEx(pdc->m_hDC, floatRateX * 30000.0, 10000, 1, 1, NULL));

   //      VERIFY(::SelectObject(pdc->m_hDC, pfont->m_hObject));

         string str;
         str = gen::international::utf8_to_unicode(psz);

         ::SetTextColor((HDC)pdc->get_os_data(), crOutline);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft - iWidth, iTop, str, iLen);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft, iTop - iWidth, str, iLen);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft + iWidth, iTop, str, iLen);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft, iTop + iWidth, str, iLen);

         ::SetTextColor((HDC)pdc->get_os_data(), crText);
         ::TextOutU((HDC)pdc->get_os_data(), iLeft, iTop, str, iLen);

         //pdc->TextOut(lpcrect->left, lpcrect->top, str);
   //      pdc->BeginPath();
   //      ::TextOutW((HDC)pdc->get_os_data(), lpcrect->left, lpcrect->top, lpcsz, iLen);
         //pdc->TextOut(lpcrect->left, lpcrect->top, str);
   //      pdc->EndPath();
   //      pdc->StrokePath();

         
   //      VERIFY(::SetMapMode(pdc->m_hDC, iOldMapMode));
   //      VERIFY(::SetViewportOrgEx(
   //         pdc->m_hDC,
   //         viewportOrg.x,
   //         viewportOrg.y,
   //         NULL));
      }
   }

   void api::SimpleTextOut(
      ::ca::graphics *          pdc,
      LPCRECT        lpcrect,
      double         dRateX,
      double         dHeight,
      const char *   psz,   
      LPINT          lpiCharsPositions,
      int            iCharsPositions,
      int            iOffset)
   {
      UNREFERENCED_PARAMETER(dRateX);
      UNREFERENCED_PARAMETER(dHeight);
      UNREFERENCED_PARAMETER(iOffset);
      UNREFERENCED_PARAMETER(iCharsPositions);
      UNREFERENCED_PARAMETER(lpiCharsPositions);
   

      if(IsGdippEnabled())
      {
         ASSERT(FALSE);
      }
      else
      {
         string str;
         str = gen::international::utf8_to_unicode(psz);
         ::TextOutU((HDC)pdc->get_os_data(), lpcrect->left, lpcrect->top, str, str.get_length());
      }
   }


   void api::EmbossedTextOut(
      ::ca::graphics *          pdc,
      LPCRECT        lpcrect,
      double         dHeight,
      double         dRateX,
      const char *   psz)
   {
      if(IsGdippEnabled())
      {
         (*lpEmbossedTextOut1)(
            pdc,
            lpcrect,
            (float) dRateX,
            (float) dHeight,
            psz);
      }
      else
      {   
         pdc->TextOut(lpcrect->left, lpcrect->top, psz);
         pdc->BeginPath();
         pdc->TextOut(lpcrect->left, lpcrect->top, psz);
         pdc->EndPath();
         pdc->StrokePath();
      }

   }

   bool api::GetProcsAddress()
   {
      if((lpDrawAndFillBeziers1 = 
         (void (*)(
            ::ca::graphics                     *pdc,
            LPPOINT             lppoints,
            int                  iCount,
            float               fRateX,
            LPPOINT               lppointOffset))
         ::GetProcAddress(
         g_hinstanceGdipp,
         "DrawAndFillBeziers1")) == NULL)
         return false;
      if((lpDrawAndFillBeziers2 = 
         (void(*)(
         ::ca::graphics                     *pdc,
         base_array<point_array, point_array &> *
                            lpglyph,
         float               fRateX,
         LPPOINT               lppointOffset))
         ::GetProcAddress(
         g_hinstanceGdipp,
         "DrawAndFillBeziers2")) == NULL)
         return false;   

      if((lpEmbossedTextOut1 = 
         (void (*)(
            ::ca::graphics         * pgraphics,
            LPCRECT               lpcrect,
            float               floatRateX,
            float               floatHeight,
            const char * psz))
         ::GetProcAddress(
         g_hinstanceGdipp,
         "EmbossedTextOut1")) == NULL)
         return false;

      if((lpEmbossedTextOut2 = 
         (void (*)(
         ::ca::graphics                     * pgraphics,
         LPCRECT               lpcrect,
         float               floatRateX,
         float               floatHeight,
         const char *         psz,   
         LPINT                lpiCharsPositions,
         int                     iCharsPositions,
         int                  iOffset))
         ::GetProcAddress(
         g_hinstanceGdipp,
         "EmbossedTextOut2")) == NULL)
         return false;

      if((lpStartup = 
         (bool (*)())
         ::GetProcAddress(
         g_hinstanceGdipp,
         "Startup")) == NULL)
         return false;

      if((lpShutdown = 
         (bool (*)())
         ::GetProcAddress(
         g_hinstanceGdipp,
         "Shutdown")) == NULL)
         return false;


      return true;
   }

   bool api::open()
   {
      if(g_hinstanceGdipp != NULL)
      {
         if((*lpStartup)())
         {
            g_bGdipp = true;

         }
      }
      return true;   
   }
   bool api::close()
   {
      if(g_hinstanceGdipp != NULL)
      {
         if((*lpShutdown)())
         {
            g_bGdipp = false;
         }
      }
      return true;
   }

   // Enable OpenGL



   void api::EnableOpenGL(HWND hWnd, HDC & hDC, HGLRC & hRC)
   {
      PIXELFORMATDESCRIPTOR pfd;
      int format;
      
      // get the device context (DC)
      hDC = GetDC( hWnd );
      
      // set the pixel format for the DC
      ZeroMemory( &pfd, sizeof( pfd ) );
      pfd.nSize = sizeof( pfd );
      pfd.nVersion = 1;
      pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
   //   pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
      pfd.iPixelType = PFD_TYPE_RGBA;
      pfd.cColorBits = 24;
      pfd.cDepthBits = 32;
      pfd.iLayerType = PFD_MAIN_PLANE;
      format = ChoosePixelFormat( hDC, &pfd );
      SetPixelFormat( hDC, format, &pfd );
      
      // create and enable the to context (RC)
      hRC = wglCreateContext( hDC );
      wglMakeCurrent( hDC, hRC );
      
   }

   // Disable OpenGL

   void api::DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
   {
      wglMakeCurrent( NULL, NULL );
      wglDeleteContext( hRC );
      ReleaseDC( hWnd, hDC );
   }


} // namespace visual
