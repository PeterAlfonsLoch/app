#include "framework.h"

namespace visual
{

   font::font(::ca::application * papp) :
      ca(papp),
      m_spfont(papp)
   {
      m_pDC       = NULL;
      m_pfontOld  = NULL;
   }

   font::~font()
   {
   }



   void font::clear()
   {
      m_glyphset.remove_all();
   }

   ::ca::font * font::GetFont()
   {
      return m_spfont;
   }

   void font::EmbossedTextOut(::ca::graphics * pdc, LPCRECT lpcrect, double dRateX, double dHeight, string & str)
   {
      
      ::visual::api::EmbossedTextOut(pdc, lpcrect, dRateX, dHeight, str);
      
      return;


      SetDC(pdc);
      SelectFont();

      rect rectOffset(lpcrect);
      point ptOffset(rectOffset.top_left());

      glyph * lpglyph;
      strsize iSize = str.get_length();
      for(int i = 0; i < iSize; i++)
      {
         lpglyph = GetGlyph(str[i]);
         if(lpglyph != NULL)
         {
            ptOffset.x += pdc->GetTextExtent(str.Left(i)).cx;
            lpglyph->DrawGlyph(
               pdc,
               true,
               (float) dRateX,
               &ptOffset);
         }
      }



      UnselectFont();
      ClearDC();

   /*   SetDC(pgraphics);
      SelectFont();

      pgraphics->TextOut(x, y, str);
      pgraphics->BeginPath();
      pgraphics->TextOut(x, y, str);
      pgraphics->EndPath();
      pgraphics->StrokePath();

      UnselectFont();
      ClearDC();*/

   }

   void font::EmbossedTextOut(::ca::graphics * pdc, LPCRECT lpcrect, double dRateX, double dHeight, string & str, LPINT lpiCharsPositions, int iCharsPositions, int iOffset)
   {
      ::visual::api::EmbossedTextOut(pdc, lpcrect, dRateX, dHeight, str, lpiCharsPositions, iCharsPositions, iOffset);
      return;

      SetDC(pdc);
      SelectFont();

      const rect rectOffset(lpcrect);
      point ptOffset;


      glyph * lpglyph;
      strsize iSize = str.get_length();
      for(strsize i = 0; i < iSize; i++)
      {
         lpglyph = GetGlyph(str[i]);
         if(lpglyph != NULL)
         {
            ptOffset = rectOffset.top_left();
            ptOffset.x += (long) ((lpiCharsPositions[iOffset + i] - lpiCharsPositions[iOffset]) * dRateX);
            lpglyph->DrawGlyph(
               pdc,
               true,
               (float) dRateX,
               &ptOffset);
         }
      }


   /*   visual::api::EmbossedTextOut(
         pdc,
         lpcrect,
         floatRateX,
         floatHeight,
         str,
         lpiCharsPositions,
         iCharsPositions,
         iOffset);*/

      UnselectFont();
      ClearDC();
   /*   SetDC(pgraphics);
      SelectFont();

      rect clipRect;

      int iOldMapMode = pgraphics->GetMapMode();
      pgraphics->SetMapMode(MM_TEXT);
      pgraphics->TextOut(x, y, str);
      pgraphics->BeginPath();
      pgraphics->TextOut(x, y, str);
      pgraphics->EndPath();
      pgraphics->StrokePath();

      pgraphics->SetMapMode(iOldMapMode);
      UnselectFont();
      ClearDC();*/
   }

   void font::SimpleTextOut(
       ::ca::graphics                     * pgraphics,
       int                     x,
       int                     y,
       string                 &str,
       LPINT                   lpiCharsPositions,
       int                     iCharsPositions)
   {
      UNREFERENCED_PARAMETER(lpiCharsPositions);
      UNREFERENCED_PARAMETER(iCharsPositions);
      SetDC(pgraphics);
      SelectFont();

      rect clipRect;
      int iOldMapMode = pgraphics->GetMapMode();
      pgraphics->SetMapMode(MM_TEXT);
      pgraphics->TextOut(x, y, str);

      pgraphics->SetMapMode(iOldMapMode);
      UnselectFont();
      ClearDC();
   }

   bool font::AddGlyph(WCHAR wchar)
   {
      return AddGlyph((UINT) wchar);
   }


   bool font::AddGlyph(CHAR tch)
   {
      return AddGlyph((UINT) tch);
   }

   bool font::AddGlyph(UINT user)
   {
   //   single_lock sl(&m_mutex);
   //   sl.lock(INFINITE);

      return TRUE;

      if(m_glyphset.find_first(user) >= 0)
         return TRUE;
      glyph glyph;
      glyph.m_ui = user;
      //m_glyphArray.add(pGlyph);
      MAT2 mat2;
      mat2.eM11.value = 1;
      mat2.eM11.fract = 0;
      mat2.eM12.value = 0;
      mat2.eM12.fract = 0;
      mat2.eM21.value = 0;
      mat2.eM21.fract = 0;
      mat2.eM22.value = 1;
      mat2.eM22.fract = 0;
      GLYPHMETRICS gm;

      DWORD cbBuffer = m_pDC->GetGlyphOutline(
         user,
         GGO_NATIVE,
         &glyph.m_gm,
         0,
         NULL,
         &mat2);
      if(cbBuffer == GDI_ERROR)
         return FALSE;
      if(cbBuffer == 0)
      {
         m_glyphset.add(glyph);
         return TRUE;
      }
      LPTTPOLYGONHEADER lpPH = (LPTTPOLYGONHEADER) malloc(cbBuffer);
      if(lpPH == NULL)
         return FALSE;

      m_pDC->GetGlyphOutline(
         user,
         GGO_NATIVE,
         &gm,
         cbBuffer,
         lpPH,
         &mat2);
      glyph.Initialize(lpPH, cbBuffer, m_iFontHiHeight);
      free(lpPH);
      m_glyphset.add(glyph);
      return TRUE;
   }

   void font::SetDC(::ca::graphics * pgraphics)
   {
      ASSERT(m_pDC == NULL);
      ASSERT(pgraphics != NULL);
      m_pDC = pgraphics;
   }

   void font::SelectFont()
   {
      m_pfontOld = m_pDC->SelectObject(m_spfont);
   }

   void font::ClearDC()
   {
      m_pDC = NULL;
   }

   void font::UnselectFont()
   {
      ASSERT(m_pfontOld != NULL);
      m_pDC->SelectObject(m_pfontOld);
      m_pfontOld = NULL;
   }



   glyph * font::GetGlyph(CHAR ch)
   {
      return GetGlyph((UINT) ch);
   }

   glyph * font::GetGlyph(WCHAR wch)
   {
      return GetGlyph((UINT) wch);
   }

   glyph * font::GetGlyph(UINT user)
   {
      return m_glyphset.GetGlyph(user);
   }


   void font::AddXFGlyphs(string2a *p2DTokens)
   {
      char            ch;
      string            str;
      int               i, j, k;
      bool             forceInsertion = FALSE;
      stringa *   p1DTokens;

      ASSERT(p2DTokens != NULL);
      SelectFont();
      for(i = 0; i < p2DTokens->get_size(); i++)
      {
         p1DTokens  = &p2DTokens->operator [](i);
         ASSERT(p1DTokens != NULL);
         for(j = 0; j < p1DTokens->get_size(); j++)
         {
            str = p1DTokens->operator [](j);
            for(k = 0; k < str.get_length(); k++)
            {
               ch = str.operator[](k);
               if(forceInsertion)
               {
                  forceInsertion = FALSE;
                  AddGlyph(ch);
               }
               else if(ch == '\\')
               {
                  forceInsertion = TRUE;
               }
               else if(ch == '^')
               {
                  AddGlyph(' ');
               }
               else if(ch == '/')
               {
               }
               else if(ch == '%')
               {
               }
               else if(ch == '<')
               {
               }
               else if(ch == '>')
               {
               }
               else
               {
                  AddGlyph(ch);
               }
            }
         }
      }
      UnselectFont();
   }

   void font::AddGlyphs(const char * lpStr)
   {
      string str(lpStr);
      SelectFont();
      for(int i = 0; i < str.get_length(); i++)
      {
         AddGlyph(str[i]);
      }

   }

   void font::TextOutEx(
      ::ca::graphics                     * pgraphics,
       LPCRECT               lpcrect,
      double               dRateX,
      double               dHeight,
      string                 &str,
      LPINT                lpiCharsPositions,
       int                     iCharsPositions,
      int                  iOffset,
       int                     iEffect)
   {
       switch(iEffect)
       {
       case EffectSimple:
           SimpleTextOut(pgraphics, lpcrect->left, lpcrect->top, str, lpiCharsPositions, iCharsPositions);
           break;
       case EffectEmbossed:
           EmbossedTextOut(
            pgraphics,
            lpcrect,
            dRateX,
            dHeight,
            str,
            lpiCharsPositions,
            iCharsPositions,
            iOffset);
           break;
       default:
           ASSERT(FALSE);

       }
   }

   int font::GetMegaHeight()
   {

      return
         m_tm.tmHeight +
         m_tm.tmInternalLeading +
         m_tm.tmExternalLeading;
   }



   void font::OnSetFont()
   {
      OnUpdateFont();
   }

   void font::OnUpdateFont()
   {
      ::ca::graphics_sp spgraphics(&System);
      spgraphics->CreateCompatibleDC(NULL);
      ::ca::font * pFontOld = spgraphics->SelectObject(m_spfont);
      spgraphics->get_text_metrics(&m_tm);
      m_iFontHiHeight = m_tm.tmAscent + m_tm.tmDescent;
      spgraphics->SelectObject(pFontOld);
      spgraphics->DeleteDC();

   }

} // namespace visual



bool CLASS_DECL_ca TextOutU(HDC hdc, int x, int y, const char * lpString, int c)
{
   if(lpString == NULL)
   {
      return ::TextOutW(hdc, x, y, NULL, c) != FALSE;
   }
   wstring wstr = gen::international::utf8_to_unicode(lpString, c);
   bool bRet = ::TextOutW(hdc, x, y, wstr, (int) wstr.get_length()) != FALSE;
   return bRet;
}

CLASS_DECL_ca bool GetTextExtentPoint32U(HDC hdc, const char * lpString, int c, LPSIZE psizl)
{
   if(lpString == NULL)
   {
      return ::GetTextExtentPoint32W(hdc, NULL, c, psizl) != FALSE;
   }
   wstring wstr = gen::international::utf8_to_unicode(lpString, c);
   bool bRet = ::GetTextExtentPoint32W(hdc, wstr, (int) wstr.get_length(), psizl) != FALSE;
   return bRet;
}


CLASS_DECL_ca int  DrawTextU(HDC hdc, const char * lpchText, int cchText, LPRECT lprc, UINT format)
{
   if(lpchText == NULL)
   {
      return ::DrawTextW(hdc, NULL, cchText, lprc, format);
   }
   wstring wstr = gen::international::utf8_to_unicode(lpchText, cchText);
   bool bRet = ::DrawTextW(hdc, wstr, (int) wcslen(wstr), lprc, format) != FALSE;
   return bRet;
}
