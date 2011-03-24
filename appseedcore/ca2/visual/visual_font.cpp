#include "StdAfx.h"

namespace visual
{

   //const DWORD font::m_dwAllocationAddUp = 4096;
   //mutex font::m_mutex;
   font::font(::ca::application * papp) :
      ca(papp)
   {
      //m_pFont = NULL;
   /////   m_lpData = NULL;
      m_pDC = NULL;
   //   m_iUsedGlyphs = 0;
   //   m_dwAllocation = 0;
   //   m_dwSize = 0;
   }

   font::~font()
   {
   }


   void font::SetFont(::ca::font *pFont)
   {
      if(m_pFont != NULL)
         clear();
      m_pFont = pFont;
      OnSetFont();
   }

   void font::clear()
   {
      m_glyphset.remove_all();
      //m_glyphArray.remove_all();
   //   m_iUsedGlyphs = 0;
   //   m_dwSize = 0;
   //   m_pFont = NULL;
   }

   ::ca::font * font::GetFont()
   {
      return m_pFont;
   }

   void font::EmbossedTextOut(
       ::ca::graphics                     *pdc,
       LPCRECT               lpcrect,
       double               dRateX,
      double               dHeight,
      string                 &str)
   {
      ::visual::api::EmbossedTextOut(
         pdc,
         lpcrect,
         dRateX,
         dHeight,
         str);
      return;
      SetDC(pdc);
      SelectFont();

      rect rectOffset(lpcrect);
      point ptOffset(rectOffset.top_left());

      glyph * lpglyph;
      int iSize = str.get_length();
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

   void font::EmbossedTextOut(
       ::ca::graphics                     *pdc,
       LPCRECT               lpcrect,
      double               dRateX,
      double               dHeight,
       string                 &str,   
       LPINT                lpiCharsPositions,
       int                     iCharsPositions,
      int                  iOffset)
   {
      ::visual::api::EmbossedTextOut(
         pdc,
         lpcrect,
         dRateX,
         dHeight,
         str,
         lpiCharsPositions,
         iCharsPositions,
         iOffset);
      return;

      SetDC(pdc);
      SelectFont();

      const rect rectOffset(lpcrect);
      point ptOffset;
      

      glyph * lpglyph;
      int iSize = str.get_length();
      for(int i = 0; i < iSize; i++)
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

   BOOL font::AddGlyph(WCHAR wchar)
   {
      return AddGlyph((UINT) wchar);
   }


   BOOL font::AddGlyph(CHAR tch)
   {
      return AddGlyph((UINT) tch);
   }

   BOOL font::AddGlyph(UINT user)
   {
   //   CSingleLock sl(&m_mutex);
   //   sl.Lock(INFINITE);
      
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
      m_pOldFont = m_pDC->SelectObject(m_pFont);
   }

   void font::ClearDC()
   {
      m_pDC = NULL;
   }

   void font::UnselectFont()
   {
      ASSERT(m_pOldFont != NULL);
      m_pDC->SelectObject(m_pOldFont);
      m_pOldFont = NULL;
   }

   //LPVOID font::Alloc(DWORD dwSize)
   //{
   //   LPVOID lpData = m_lpData;
   //   DWORD dwFree = GetFreeSize();
   /*   if(dwFree < dwSize)
      {
         m_dwAllocation += dwSize + m_dwAllocationAddUp;
         HANDLE hHeap = GetProcessHeap();
         if(m_lpData == NULL)
            lpData = HeapAlloc(hHeap, 0, m_dwAllocation);
         else
            lpData = HeapReAlloc(hHeap, 0, m_lpData, m_dwAllocation);
         if(lpData == NULL)
            return NULL;
         if(lpData != m_lpData)
         {
            OffsetDataPointers(lpData);
            m_lpData = lpData;
         }
      }
      lpData = (LPBYTE) lpData + m_dwSize;
      m_dwSize += dwSize;
      return lpData;*/
   //   return NULL;

   //}

   //DWORD font::GetFreeSize()
   //{
   //   return m_dwAllocation - m_dwSize;
   //}

   /*void font::OffsetDataPointers(LPVOID lpData)
   {
      glyph * pGlyph;
      bool bPlus;
      DWORD dwOffset;
      if(lpData > m_lpData)
      {
         bPlus = true;
         dwOffset = (LPBYTE) lpData - (LPBYTE) m_lpData;
      }
      else
      {
         bPlus = false;
         dwOffset = (LPBYTE) m_lpData - (LPBYTE) lpData;
      }
      int i, iSize;
      iSize = m_glyphArray.get_size();
      for(i = 0; i < iSize; i++)
      {
         pGlyph = m_glyphArray[i];
      }

   }*/



   /*glyph * font::GetNewGlyph()
   {
   //   glyph * pGlyph;
   //   if(m_iUsedGlyphs == m_glyphArray.get_size())
   //   {
         glyph glyph;
         m_glyphArray.add(glyph);
         return &m_glyphArray.element_at(m_glyphArray.get_upper_bound());
   /*   }
      else
      {
         ASSERT(m_iUsedGlyphs < m_glyphArray.get_size());
         pGlyph = m_glyphArray[m_iUsedGlyphs];
         pGlyph->clear();
         m_iUsedGlyphs++;
         return pGlyph;
      }*/
   //}



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
      BOOL             forceInsertion = FALSE;
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
      ::ca::font * pFontOld = spgraphics->SelectObject(m_pFont);
      spgraphics->GetTextMetrics(&m_tm);
      m_iFontHiHeight = m_tm.tmAscent + m_tm.tmDescent;
      spgraphics->SelectObject(pFontOld);
      spgraphics->DeleteDC();

   }

} // namespace visual



BOOL CLASS_DECL_ca TextOutU(HDC hdc, int x, int y, const char * lpString, int c)
{
   if(lpString == NULL)
   {
      return ::TextOutW(hdc, x, y, NULL, c);
   }
   wstring wstr = gen::international::utf8_to_unicode(lpString, c);
   BOOL bRet = ::TextOutW(hdc, x, y, wstr, wcslen(wstr));
   return bRet;
}

CLASS_DECL_ca BOOL GetTextExtentPoint32U(HDC hdc, const char * lpString, int c, LPSIZE psizl)
{
   if(lpString == NULL)
   {
      return ::GetTextExtentPoint32W(hdc, NULL, c, psizl);
   }
   wstring wstr = gen::international::utf8_to_unicode(lpString, c);
   BOOL bRet = ::GetTextExtentPoint32W(hdc, wstr, wcslen(wstr), psizl);
   return bRet;
}


CLASS_DECL_ca int  DrawTextU(HDC hdc, const char * lpchText, int cchText, LPRECT lprc, UINT format)
{
   if(lpchText == NULL)
   {
      return ::DrawTextW(hdc, NULL, cchText, lprc, format);
   }
   wstring wstr = gen::international::utf8_to_unicode(lpchText, cchText);
   BOOL bRet = ::DrawTextW(hdc, wstr, wcslen(wstr), lprc, format);
   return bRet;
}