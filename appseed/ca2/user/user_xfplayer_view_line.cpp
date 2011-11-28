#include "StdAfx.h"

#include <math.h>

const int XfplayerViewLine::AlignLeft = 1;
const int XfplayerViewLine::AlignRight = 2;

XfplayerViewLine::XfplayerViewLine(::ca::application * papp) :
   ca(papp),
   m_dibMain(papp),
   m_dcextension(papp),
   m_font(papp)
{
   m_pContainer                  = NULL;
   m_bEnhancedEmboss             = true;
   m_bCacheEmboss                = false;
   m_cr                          = RGB(255, 255, 255);
   m_crOutline                   = RGB(0, 0, 0);
   m_nFont                       = 0;
   m_lpBitmapData                = NULL;
   m_bAutoSizeX                  = false;
   m_bAutoSizeY                  = false;
   m_iAlign                      = AlignLeft;
   m_iLeft                       = 0;
   m_iTop                        = 0;
   m_iRight                      = 0;
   m_iBottom                     = 0;
   m_bVisible                    = false;
   m_iAnimateType                = AnimateNoAnimate;
   m_iTextEffect                 = EffectSimple;
   m_dAnimateProgress            = 0;
   m_iIndent                     = 0;
   m_dAnimateProgressIncrement   = 1.0;
   m_dBlend                      = 1.0;
   m_iIndex                      = 0;
}

XfplayerViewLine::XfplayerViewLine(XfplayerViewLines * pContainer) :
   ::ca::ca(pContainer->get_app()),
   m_dibMain(pContainer->get_app()),
   m_dcextension(pContainer->get_app())
{
   m_pContainer                  = pContainer;
   m_bEnhancedEmboss             = true;
   m_bCacheEmboss                = false;
   m_nFont                       = 0;
   m_lpBitmapData                = NULL;
   m_bAutoSizeX                  = false;
   m_bAutoSizeY                  = false;
   m_iAlign                      = AlignLeft;
   m_iLeft                       = 0;
   m_iTop                        = 0;
   m_iRight                      = 0;
   m_iBottom                     = 0;
   m_bVisible                    = false;
   m_iAnimateType                = AnimateNoAnimate;
   m_iTextEffect                 = EffectSimple;
   m_dAnimateProgress            = 0;
   m_dAnimateProgress            = 0;
   m_dAnimateProgressIncrement   = 1.0;
   m_iIndex                      = 0;
}

XfplayerViewLine::XfplayerViewLine(const XfplayerViewLine & line) :
   m_dcextension(line.get_app())
{
   operator = (line);
}

XfplayerViewLine::~XfplayerViewLine()
{
}


bool XfplayerViewLine::PrepareLine(
   ::ca::graphics * pdc,
   const char * lpcsz,
   int flags,
   LPRECT pRect)
{
   UNREFERENCED_PARAMETER(flags);
   m_straLink.remove_all();
   m_iaLinkStart.remove_all();
   m_iaLinkEnd.remove_all();
   int               iChars;
   int               iStr;
   int               iStrLen;
   string str(lpcsz);
   ASSERT(pdc != NULL);
   iStrLen = str.get_length();
   iChars = -1;
   m_str.Empty();
   m_iIndent = 0;
   for(iStr = 0; iStr < iStrLen; iStr++)
   {
      AddChar(str[iStr], iChars);
   }
//   CalcCharsPositions(pdc, GetFonts(), pRect);
   CalcCharsPositions(pdc, pRect);
   return true;
}

/*bool XfplayerViewLine::PrepareLine(
   ::ca::graphics * pdc,
   const wchar_t * lpcsz,
   int flags,
   visual::font *pFont,
   LPRECT pRect)
{
   m_bCacheEmboss = false;
   int               iChars;
   int               iStr;
   int               iStrLen;
    m_iIndent = 0;
   string str(lpcsz);
   ASSERT(pdc != NULL);
   pdc->SelectObject(pFont->GetFont());
   pFont->GetFont()->GetLogFont(&m_logfont);
   iStrLen = str.get_length();
   iChars = -1;
   m_str.Empty();
   for(iStr = 0; iStr < iStrLen; iStr++)
   {
      AddChar(str[iStr], iChars, pFont);
   }
   CalcCharsPositions(pdc, pFont, pRect);
   //pFont->UnselectFont();
   //pFont->ClearDC();
   return true;
}*/

void XfplayerViewLine::AddChar(
   WCHAR wch,
   int &index)
{
   index++;
   if(m_iaPosition.get_size() < index + 2)
   {
        m_iaPosition.set_size(m_iaPosition.get_size() + 10);
   }

   m_str += wch;
    ASSERT(m_str.get_length() - 1 == index);


}

void XfplayerViewLine::AddChar(
   WCHAR wch,
   int &index,
   visual::font * pFont)
{
   UNREFERENCED_PARAMETER(pFont);
   index++;
   if(m_iaPosition.get_size() < index + 2)
   {
        m_iaPosition.set_size(m_iaPosition.get_size() + 10);
   }
   m_str += wch;
   ASSERT(m_str.get_length() - 1 == index);

}


void XfplayerViewLine::GetPlacement(LPRECT lprect)
{
   lprect->left = m_iLeft;
   lprect->top  = m_iTop;
   lprect->right = m_iRight;
   lprect->bottom = m_iBottom;
}

bool XfplayerViewLine::to(
   ::ca::application * papp,
   ::ca::graphics *               pdc,
   bool               bDraw,
   LPRECT            lpRect,
   rect_array &   rectaModified,
   bool               bRecalcLayout)
{
   string strFinal(m_str);
   double dBlend;
   if(m_dBlend <= 0.0)
      return true;
   if(m_dBlend >= 1.0)
      dBlend = 1.0;
   else
      dBlend = m_dBlend;

   pdc->SelectObject(m_font);

   pdc->SetBkMode(TRANSPARENT);

   point iMargin;
   iMargin.x = 3;
   iMargin.y = 3;

   if(!IsVisible())
   {
      return true;
   }
   if(bRecalcLayout || m_rectClient != *lpRect)
   {
      m_bCacheEmboss = false;
      CalcCharsPositions(
         pdc,
         lpRect);
   }

   rect rectTextOut;
   GetPlacement(rectTextOut);

   switch(m_iAnimateType)
   {
   case AnimateNoAnimate:
      {
         if(bDraw)
         {
            int iLink = 0;
            int iChar = 0;
            while(true)
            {
               pdc->SelectObject(m_font);
               if(iChar >= strFinal.get_length())
                  break;
               if(iLink >= m_iaLinkStart.get_size())
               {
                  size size = pdc->GetTextExtent(strFinal.Left(iChar));
                  EmbossedTextOut(papp, pdc,
                     strFinal.Mid(iChar),
                     rectTextOut.left + size.cx,
                     rectTextOut.top,
                     0,
                     m_cr,
                     m_crOutline,
                     strFinal.get_length() - iChar,
                     dBlend);
                  break;
               }
               else if(m_iaLinkStart[iLink] > iChar)
               {
                  size size = pdc->GetTextExtent(strFinal.Left(iChar));
                  EmbossedTextOut(papp, pdc,
                     strFinal.Mid(iChar),
                     rectTextOut.left + size.cx,
                     rectTextOut.top,
                     0,
                     m_cr,
                     m_crOutline,
                     m_iaLinkStart[iLink],
                     dBlend);
               }
               pdc->SelectObject(m_fontLink);
               size size = pdc->GetTextExtent(strFinal.Left(m_iaLinkStart[iLink]));

               EmbossedTextOut(papp, pdc,
                  strFinal.Mid(m_iaLinkStart[iLink]),
                  rectTextOut.left + size.cx,
                  rectTextOut.top,
                  0,
                  m_cr,
                  m_crOutline,
                  m_iaLinkEnd[iLink] - m_iaLinkStart[iLink] + 1,
                  dBlend);
               iChar = m_iaLinkEnd[iLink] + 1;
               iLink++;
            }
            if(GetSelection().m_iCharStartSource >= 0)
            {
               int iStart;
               int iLineStart;
               int iLineEnd;
               int iCharStart;
               int iCharEnd;
               GetSelection().GetNormalSelection(iLineStart, iCharStart, iLineEnd, iCharEnd);
               if(iLineStart < m_iIndex)
               {
                  iStart = 0;
               }
               else if(iLineStart > m_iIndex)
               {
                  iStart = m_iaPosition.get_count();
               }
               else
               {
                  iStart = iCharStart;
               }
               int iEnd;
               if(iLineEnd < m_iIndex)
               {
                  iEnd = -1;
               }
               else if(iLineEnd > m_iIndex)
               {
                  iEnd = m_iaPosition.get_upper_bound();
               }
               else
               {
                  iEnd = iCharEnd;
               }
               if(iStart < iEnd)
               {
                  class rect rectPlacement;
                  GetPlacement(rectPlacement);
                  class rect rect = rectPlacement;
                  size size1 = pdc->GetTextExtent(strFinal.Left(iStart));
                  size size2 = pdc->GetTextExtent(strFinal.Left(iEnd + 1));
                  rect.left = rectPlacement.left + size1.cx;
                  rect.right = rectPlacement.left + size2.cx;
                  ::ca::dib_sp dib(get_app());
                  if(rect.area() > 0)
                  {
                     dib->create(rect.size());
                     dib->from(null_point(), pdc, rect.top_left(), rect.size());
                     dib->Invert();
                     dib->to(pdc, rect.top_left(), rect.size(), null_point());
                  }
               }
            }

         }
       }
       break;
   case AnimateRHL:
      {
         int iLeft = m_iaPosition.element_at(0);
         int iLeftDiff  = 0;
         int iLastLeftDiff = 0;
         int i;
         for(i = 0; i < m_iaPosition.get_size(); i++)
         {
            iLastLeftDiff = iLeftDiff;
            iLeftDiff = m_iaPosition.element_at(i) - iLeft;
            if((int) m_dAnimateProgress <= iLeftDiff)
            {
               //i--;
               break;
            }
         }
         ::ca::region rgn;
         string strFinal(m_str);
         string wstrLeft = strFinal.Right(strFinal.get_length() - i);
         int iLeftOffset;
         iLeftOffset = iLastLeftDiff - (int) m_dAnimateProgress;
           rect rectTextOut;
           GetPlacement(rectTextOut);
           rectTextOut.left += iLeftOffset;
           if(bDraw)
           {
              EmbossedTextOut(papp, pdc,
               wstrLeft,
               rectTextOut.left,
               rectTextOut.top,
               0,
               m_cr,
               m_crOutline,
               strFinal.get_length(),
               dBlend);
           }
           int iMaxCounter = max((int) m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_iRight - m_iLeft);
           int iRight = iMaxCounter - (int) m_dAnimateProgress;
           if(iRight < m_iRight)
           {
              int iRightEnd;
              int i;
              for(i = 0; i < m_iaPosition.get_size(); i++)
              {
                 iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                 if(iRightEnd >= m_iRight)
                 {
                    break;
                 }
              }
              string wstrRight = strFinal.Left(i);
              rectTextOut.left = iRight;
              if(bDraw)
              {
                 EmbossedTextOut(papp, pdc,
                  wstrRight,
                  rectTextOut.left,
                  rectTextOut.top,
                  0,
                  m_cr,
                  m_crOutline,
                  strFinal.get_length(),
                  dBlend);
              }
           }

           if(&rectaModified != NULL)
           {
              rect baserect;
              rgn.GetRgnBox(baserect);
              rectaModified.add(baserect);

           }
      }
      break;
   default:
      ASSERT(FALSE);
   }




   return true;

}

bool XfplayerViewLine::to(
   ::ca::application *  papp,
   ::ca::graphics *     pdc,
   bool                 bDraw,
   LPRECT               lpRect,
   rect_array &         rectaModified,
   int *                count,
   bool                 bRecalcLayout,
   COLORREF               crColor,
   ::ca::pen &          pen)
{
   UNREFERENCED_PARAMETER(papp);
   UNREFERENCED_PARAMETER(count);

   rect rectPlacement;
   GetPlacement(rectPlacement);

   pdc->set_font(m_font);

   pdc->SetBkMode(TRANSPARENT);

   point iMargin;
   {
      iMargin.x = pen.m_dPenWidth / 2.0;
      iMargin.y = pen.m_dPenWidth / 2.0;
   }

   if(!IsVisible())
   {
      class rect rect(m_rectInvalidate);
      if(!IsRefNull(rectaModified))
      {
         class rect baserect(rect);
         rectaModified.add(baserect);
      }

      Validate(rect);

      return true;
   }
   if(bRecalcLayout)
   {
      CalcCharsPositions(
         pdc,
         lpRect);
      pdc->SelectObject(m_font);
   }


   switch(m_iAnimateType)
   {
   case AnimateNoAnimate:
      {
         string strFinal;
         strFinal = m_str;
         pdc->SelectObject(&pen);
         pdc->SetTextColor(crColor);
         rect rectTextOut;
         GetPlacement(rectTextOut);
         if(bDraw)
         {
            m_dcextension._DrawText(
               pdc,
               strFinal,
               rectTextOut,
               DT_LEFT | DT_BOTTOM);
         }
      }
      break;
   case AnimateRHL:
      {
         if(m_iaPosition.get_size() <= 0)
            break;
//         int iLeft = m_iaPosition.element_at(0);
         int iLeftDiff  = 0;
         //int iLastLeftDiff = 0;
         int i = 0;
/*            for(int i = 0; i < m_iaPosition.get_size(); i++)
            {
                iLastLeftDiff = iLeftDiff;
                iLeftDiff = m_iaPosition.element_at(i) - iLeft;
                if(iLeftDiff >= (int) m_dAnimateProgress)
                {
                    break;
                }
            }*/

            string strFinal(m_str);
            string wstrLeft = strFinal.Right(strFinal.get_length() - i);
            int iLeftOffset;
            iLeftOffset = iLeftDiff - (int) m_dAnimateProgress;

           pdc->SelectObject(&pen);
           pdc->SetTextColor(crColor);
           pdc->SelectObject(m_font);
         rect rectTextOut;
         GetPlacement(rectTextOut);
         rectTextOut.left += iLeftOffset;
         if(bDraw)
         {
            m_dcextension._DrawText(
               pdc,
               wstrLeft,
               rectTextOut,
               DT_LEFT | DT_BOTTOM);
         }
/*           pFont->TextOutEx(
                pdcForeground,
              rectTextOut,
            1.0,
            rectTextOut.height(),
              wstrLeft,
              m_iaPosition.get_data(),
                m_iaPosition.get_size(),
              0,
                MapToFontEffect(m_iTextEffect));   */
            int iSpacing = 100;
            int iMaxCounter = max(
               (int) m_iaPosition.element_at(m_str.get_length())
                  - m_iaPosition.element_at(0) + iSpacing, m_iRight - m_iLeft);
            int iRight = iMaxCounter - (int) m_dAnimateProgress;
            if(iRight < m_iRight)
            {
            /*    int iRightEnd;
                for(int i = 0; i < m_iaPosition.get_size(); i++)
                {
                    iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                    if(iRightEnd >= m_iRight)
                    {
                        break;
                    }
                }*/
                //string wstrRight = strFinal.Left(i);
                string wstrRight = strFinal;
            rectTextOut.left = iRight;
         if(bDraw)
         {
            m_dcextension._DrawText(
               pdc,
               wstrRight,
               rectTextOut,
               DT_LEFT | DT_BOTTOM);
         }
/*               pFont->TextOutEx(
                    pdcForeground,
                  rectTextOut,
               1.0,
               rectTextOut.height(),
                  wstrRight,
                  m_iaPosition.get_data(),
                    m_iaPosition.get_size(),
                  0,
                    MapToFontEffect(m_iTextEffect));   */
                }

        }
        break;
    default:
        ASSERT(FALSE);
    }

   return true;

}



/*void XfplayerViewLine::CalcCharsPositions(
::ca::graphics * pdcForeground,
   primitive_array < visual::font *> * pFonts,
   LPCRECT lpcrect)
{
   m_bCacheEmboss = false;
   //visual::font * pFont;
//    ::ca::graphics * pdcForeground = m_ptwi->TwiGetDC();
   if(m_str.get_length() <= 0)
      return;
   if(pFonts->get_size() > 0)
   {
      int i, nFont, iFontFound, iMaxExtent, iLeft;
      size size;
      rect clientRect;
      nFont = 0;
      iFontFound = -1;
      for(nFont = 0; nFont < pFonts->get_size(); nFont++)
      {
         pdcForeground->SelectObject(pFonts->get_at(nFont)->GetFont());
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.get_length(),
            &size);
         if((m_iAlign & AlignLeft) > 0)
         {
            if(size.cx + m_iLeft <= lpcrect->right)
            {
               iFontFound = nFont;
               break;
            }
         }
         else if((m_iAlign & AlignRight) > 0)
         {
            if(m_iRight - size.cx >= 0)
            {
               iFontFound = nFont;
               break;
            }
         }
      }
      if(iFontFound < 0)
      {
         m_nFont = pFonts->get_size() - 1;
      }
      else
      {
         m_nFont = iFontFound;
      }
      pdcForeground->SelectObject(pFonts->get_at(m_nFont)->GetFont());
      if(m_iAlign == AlignLeft)
      {
         m_iaPosition[0] = m_iLeft + m_iIndent;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + m_iLeft  + m_iIndent;
         }
         if(m_bAutoSizeX)
         {
            m_iRight = m_iLeft  + m_iIndent + size.cx;
            }
         if(m_bAutoSizeY)
         {
            m_iBottom = m_iTop + size.cy;
         }
      }
      else if(m_iAlign == AlignRight)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            m_str.get_length(),
            &size);
         iMaxExtent = size.cx;
         iLeft = m_iRight - iMaxExtent;
         m_iaPosition[0] = iLeft;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + iLeft;
         }
         if(m_bAutoSizeX)
         {
            m_iLeft = m_iRight - size.cx;
            }
            if(m_bAutoSizeY)
            {
            m_iBottom = m_iTop + size.cy;
         }
      }

   }

   else
   {
      int i; //, width;
      size size;
         m_iaPosition[0] = m_iLeft;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i ,
               &size);
            m_iaPosition[i] = m_iLeft + size.cx;
         }
      if(m_bAutoSizeX)
      {
         m_iRight = m_iLeft + size.cx;
        }
      if(m_bAutoSizeY)
      {
         m_iBottom = m_iTop + size.cy;
      }
   }
//    m_ptwi->TwiReleaseDC(pdcForeground);

}*/

void XfplayerViewLine::CalcCharsPositions(
   ::ca::graphics *             pdc,
   LPCRECT           lpcrect)
{
   m_bCacheEmboss = false;
   if(m_str.get_length() <= 0)
      return;

//   ::ca::font * pfontOld = pdc->GetCurrentFont();

   ::ca::font_sp fontOriginal(get_app());
   LOGFONT lf;
   GetLogFont(lf);
   fontOriginal->CreateFontIndirect(&lf);

   int i;
   size size;
   rect rectClient(lpcrect);
   m_rectClient = rectClient;
   rect rectPlacement;
   GetPlacement(rectPlacement);
   string wstrMain = m_str;
   pdc->SelectObject(fontOriginal);
   size = pdc->GetTextExtent(wstrMain);
   if(size.cx > rectClient.width())
   {
      m_floatRateX =
         (float)
         rectClient.width()/
         size.cx;
   }
   else
   {
      m_floatRateX = 1.0;
   }

   pdc->SelectObject(fontOriginal);
   TEXTMETRIC tm;
   pdc->GetTextMetrics(&tm);
   lf.lfWidth = (long) (tm.tmAveCharWidth * m_floatRateX - 1);

  // if(m_font->get_os_data() != NULL)
//      m_font->delete_object();

   m_font->CreateFontIndirect(&lf);


   if(m_straLink.get_size() > 0)
   {
      lf.lfUnderline = TRUE;
      m_fontLink->CreateFontIndirect(&lf);
   }



   pdc->SelectObject(m_font);

   m_iaPosition[0] = 0;
   for(i = 1; i <= m_str.get_length(); i++)
   {
      m_dcextension.GetTextExtent(
         pdc,
         m_str,
         i,
         size);
      m_iaPosition[i] = size.cx;
   }

   /*if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_iLeft + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pdc->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_iLeft + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_iRight = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_iBottom = m_iTop + size.cy;
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         (HDC)pdc->get_os_data(),
         m_str,
         m_str.get_length(),
         &size);
      iMaxExtent = size.cx;
      iLeft = m_iRight - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pdc->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_iLeft = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_iBottom = m_iTop + size.cy;
      }
   }
   pdc->SelectObject(pfontOld);*/
}

/*void XfplayerViewLine::CalcCharsPositions(
   ::ca::graphics *             pdcForeground,
   visual::font *     pFont,
   LPCRECT           lpcrect)
{
   m_bCacheEmboss = false;
   if(m_str.get_length() <= 0)
      return;
    ::ca::font * pfontOriginal = pdcForeground->GetCurrentFont();
   pdcForeground->SelectObject(pFont->GetFont());
   int i, iLeft, iRight, iMaxExtent;
   size size;
   rect rectClient(lpcrect);
   m_rectClient = rectClient;
   visual::font * pfont = pFont;
   ::ca::graphics * pdc = pdcForeground;
   ASSERT(pfont != NULL);
   rect rectPlacement;
   GetPlacement(rectPlacement);
   string wstrMain = m_str;
   GetTextExtentPoint32W(
      (HDC)pdc->get_os_data(),
      wstrMain,
      wstrMain.get_length(),
      &size);
   pdc->SelectObject(pfont->GetFont());
   if(size.cx > rectClient.width())
   {
      m_floatRateX =
         (float)
         rectClient.width()/
         size.cx;
   }
   else
   {
      m_floatRateX = 1.0;
   }

   m_font->delete_object();
   LOGFONT lf;
   pfont->GetFont()->GetLogFont(&lf);
   pdc->SelectObject(pfont->GetFont());
   TEXTMETRIC tm;
   pdc->GetTextMetrics(&tm);
   lf.lfWidth = (long) (tm.tmAveCharWidth * m_floatRateX - 1);
   m_font->CreateFontIndirect(&lf);





   pdc->SelectObject(m_font);
   if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_iLeft + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_iLeft + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_iRight = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_iBottom = m_iTop + size.cy;
      }
   }
   else if(m_iAlign == AlignRight)
   {
      GetTextExtentPoint32W(
         pdcForeground->get_os_data(),
         m_str,
         m_str.get_length(),
         &size);
      iMaxExtent = size.cx;
      iLeft = m_iRight - iMaxExtent;
      m_iaPosition[0] = iLeft;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = size.cx + iLeft;
      }
      if(m_bAutoSizeX)
      {
         m_iLeft = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_iBottom = m_iTop + size.cy;
      }
   }
   pdcForeground->SelectObject(pfontOriginal);
}*/

void XfplayerViewLine::SetAutoSize(bool bAutoSize)
{
   m_bAutoSizeX = bAutoSize;
    m_bAutoSizeY = bAutoSize;
}

void XfplayerViewLine::SetAlign(int iAlign)
{
   m_iAlign = iAlign;
}

void XfplayerViewLine::set(LPRECT lpRect)
{
    m_iLeft     = lpRect->left;
    m_iTop      = lpRect->top;
    m_iRight    = lpRect->right;
    m_iBottom   = lpRect->bottom;
}

void XfplayerViewLine::GetRect(LPRECT lpRect)
{
    lpRect->left    = m_iLeft;
    lpRect->top     = m_iTop;
    lpRect->right   = m_iRight;
    lpRect->bottom  = m_iBottom;
}

XfplayerViewLine & XfplayerViewLine::operator = (const XfplayerViewLine & src)
{
   m_pContainer                  = src.m_pContainer;
   m_bAutoSizeX                  = src.m_bAutoSizeX;
   m_bAutoSizeY                  = src.m_bAutoSizeY;
   m_str                         = src.m_str;
   m_iaPosition                  = src.m_iaPosition;
   m_iAlign                      = src.m_iAlign;
   m_iBottom                     = src.m_iBottom;
   m_iLeft                       = src.m_iLeft;
   m_iRight                      = src.m_iRight;
   m_iTop                        = src.m_iTop;
   m_lpBitmapData                = src.m_lpBitmapData;
   m_nFont                       = src.m_nFont;
   m_iAnimateType                = src.m_iAnimateType;
   m_iTextEffect                 = src.m_iTextEffect ;
   m_dAnimateProgress            = src.m_dAnimateProgress;
   m_dAnimateProgressIncrement   = src.m_dAnimateProgressIncrement;
   m_logfont                     = src.m_logfont;
   m_font                        = src.m_font;
   m_bEnhancedEmboss             = src.m_bEnhancedEmboss;
   m_bCacheEmboss                = src.m_bCacheEmboss;
   m_dBlend                      = src.m_dBlend;
   m_iIndex                      = src.m_iIndex;
   return *this;
}

void XfplayerViewLine::Show(bool bShow)
{
    if(bShow && !m_bVisible)
    {
        m_bVisible = true;
        Invalidate();
        if(m_pContainer != NULL)
        {
            m_pContainer->OnChildSetVisible(this, m_bVisible);
        }

    }
    else if(!bShow && m_bVisible)
    {
        m_bVisible = false;
        Invalidate();
        if(m_pContainer != NULL)
        {
            m_pContainer->OnChildSetVisible(this, m_bVisible);
        }
    }
}


void XfplayerViewLine::OnTimerAnimate(
   ::ca::graphics *                  pdcForeground,
   rect_array &      rectaModified)
{
   UNREFERENCED_PARAMETER(pdcForeground);
    if(IsVisible())
    {
        switch(m_iAnimateType)
        {
        case AnimateNoAnimate:
            break;
        case AnimateRHL:
            {
                m_dAnimateProgress+= m_dAnimateProgressIncrement;
                if(m_iaPosition.get_size() > 0)
                {
                    if((int)m_dAnimateProgress > max(m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_iRight - m_iLeft))
                        m_dAnimateProgress = 0.0;
                    rect rect;
                    GetRect(rect);
                    Invalidate();
                    rectaModified.add(rect);
                    /*to(
                        pdcForeground,
                        false,
                        rect, rectaModified,
                        false);*/
                }
            }
            break;
        default:
            ASSERT(FALSE);
        }
    }
}

void XfplayerViewLine::SetAnimateType(int iAnimateType)
{
    m_iAnimateType = iAnimateType;
    m_dAnimateProgress = 0.0;

}

void XfplayerViewLine::SetTextEffect(int iTextEffect)
{
    m_iTextEffect = iTextEffect;
}

void XfplayerViewLine::SetEmbossPen(::ca::pen *lpPen)
{
    m_lpPenEmboss = lpPen;

}

void XfplayerViewLine::SetForegroundColor(COLORREF cr)
{
    m_crForeground = cr;
}

/*primitive_array < visual::font *> * XfplayerViewLine::GetFonts()
{
    return &m_fonts;
}
*/
int XfplayerViewLine::MapToFontEffect(int iLineEffect)
{
    switch(iLineEffect)
    {
    case EffectSimple:
        return visual::font::EffectSimple;
    case EffectEmbossed:
        return visual::font::EffectEmbossed;
    }
    ASSERT(FALSE);
    return -1;
}

void XfplayerViewLine::SetAnimateIncrement(double dIncrement)
{
    m_dAnimateProgressIncrement = dIncrement;
}

//void XfplayerViewLine::SetRedrawMode(int iMode)
//{
  //  m_iRedrawMode = iMode;
//}

//void XfplayerViewLine::SetRenderWindow(::ca::window *pWnd)
//{
  //  m_pRenderWnd = pWnd;
//}

void XfplayerViewLine::SetRenderCriticalSection(critical_section * pcs)
{
   UNREFERENCED_PARAMETER(pcs);
//    m_pcsRender =   pcs;
}

int XfplayerViewLine::SetLyricPens(::ca::pen * ppenLeft, ::ca::pen * ppenRight)
{
    m_ppenLyricLeft = ppenLeft;
    m_ppenLyricRight = ppenRight;
    return true;
}

int XfplayerViewLine::SetLyricColors(COLORREF crLeft, COLORREF crRight)
{
    m_crLyricLeft = crLeft;
    m_crLyricRight = crRight;
    return true;

}

void XfplayerViewLine::SetPlacement(LPCRECT lpcrect)
{
   m_iLeft        = lpcrect->left;
   m_iTop         = lpcrect->top;
   m_iRight       = lpcrect->right;
   m_iBottom      = lpcrect->bottom;
   m_bPendingLayoutUpdate = true;
}

//int XfplayerViewLine::GetVmsFontCount()
/*{
   return m_fonts.get_size();
}

void XfplayerViewLine::AddVmsFont(visual::font * pfont)
{
   m_fonts.add(pfont);
}*/

void XfplayerViewLine::Invalidate(LPCRECT lpcrect)
{
   rect rectPlacement;
   GetPlacement(rectPlacement);
   rect rect;
   if(lpcrect == NULL)
   {
      rect = rectPlacement;
   }
   else
   {
      rect = *lpcrect;
   }
   m_rectInvalidate.unite(m_rectInvalidate, rect);
   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}

void XfplayerViewLine::Validate(LPCRECT lpcrect)
{
   rect rectPlacement;
   GetPlacement(rectPlacement);
   rect rect;
   if(lpcrect == NULL)
   {
      rect = rectPlacement;
   }
   else
   {
      rect = *lpcrect;
   }
   m_rectInvalidate -= rect;
   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}

bool XfplayerViewLine::IsVisible()
{
   return m_bVisible;
}

void XfplayerViewLine::EmbossedTextOut(
      ::ca::application * papp,
      ::ca::graphics * pdc,
      const char * lpcsz,
      int iLeft,
      int iTop,
      int iWidth,
      COLORREF cr,
      COLORREF crOutline,
      int iLen,
      double dBlend)
{
   EmbossedTextOut(
      papp,
      pdc,
      m_dibMain->get_graphics(),
      lpcsz,
      iLeft,
      iTop,
      iWidth,
      cr,
      crOutline,
      iLen,
      dBlend);

/*   rect rect;
   size size;
   size sizeInt;
   size sizeExt;
   pdc->SelectObject(m_font);
   int cx = 0;
   int width;
   int widthInt;
   int widthExt;
   int cxInt;
   int cxExt;
   int cyInt;
   int cyExt;
   ::GetTextExtentPoint32W(
      (HDC)pdc->get_os_data(),
      lpcsz,
      iLen,
      &size);
   pdc->SelectObject(m_fontInt);
   ::GetTextExtentPoint32W(
      (HDC)pdc->get_os_data(),
      lpcsz,
      iLen,
      &sizeInt);
   //cyInt = (size.cy - sizeInt.cy) / 2;
   cyInt = (size.cy * 1000 / 1200) / 2;

   pdc->SelectObject(m_fontExt);
   ::GetTextExtentPoint32W(
      (HDC)pdc->get_os_data(),
      lpcsz,
      iLen,
      &sizeExt);
   //cyExt = (size.cy - sizeExt.cy) / 2;
   cyExt = -(size.cy * 1200 / 1000) / 2;

   //XFORM xform;

   //pdc->GetWorldTransform(&xform);

   ::SetTextColor((HDC)pdc->get_os_data(), crOutline);
   for(int i = 0; i < iLen; i++)
   {
      WCHAR wch = lpcsz[i];


      pdc->SelectObject(m_font);
      ::GetTextExtentPoint32W(
         (HDC)pdc->get_os_data(),
         lpcsz,
         i + 1,
         &size);

      pdc->SetMapMode( MM_ANISOTROPIC);
      cxInt = (size.cx * 1000 / 1200) / 2;
      ::ScaleViewportExtEx(
         (HDC)pdc->get_os_data(),
         1000,
         1200,
         1000,
         1200,
         NULL);
      ::OffsetViewportOrgEx(
         (HDC)pdc->get_os_data(),
         iLeft + cx,
         iTop * cyInt,
         NULL);
      ::TextOutW((HDC)pdc->get_os_data(), 0, 0, &wch, 1);

      cxInt = -(size.cx * 1000 / 1200) / 2;
      ::ScaleViewportExtEx(
         (HDC)pdc->get_os_data(),
         1000,
         1200,
         1000,
         1200,
         NULL);
      ::OffsetViewportOrgEx(
         (HDC)pdc->get_os_data(),
         iLeft + cx,
         iTop  + cyExt,
         NULL);
      ::TextOutW((HDC)pdc->get_os_data(), 0, 0, &wch, 1);

      //pdc->SelectObject(m_fontInt);
      ::GetTextExtentPoint32W(
         (HDC)pdc->get_os_data(),
         &wch,
         1,
         &sizeInt);
      ::TextOutW((HDC)pdc->get_os_data(), 0, 0, &wch, 1);

      //pdc->SelectObject(m_fontExt);
      ::GetTextExtentPoint32W(
         (HDC)pdc->get_os_data(),
         &wch,
         1,
         &sizeExt);
      cxExt = (size.cx * 1200 / 1000);
      cyExt = (size.cy - sizeExt.cy) / 2;
      ::TextOutW((HDC)pdc->get_os_data(), iLeft + cx + cxExt, iTop + cyExt, &wch, 1);



      cx = size.cx;
   }
   pdc->SetMapMode(MM_TEXT);
   ::SetTextColor((HDC)pdc->get_os_data(), cr);
   pdc->SelectObject(m_font);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop, lpcsz, iLen);*/


/*   ::SetTextColor((HDC)pdc->get_os_data(), crOutline);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft - iWidth, iTop - iWidth, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft - iWidth, iTop, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft - iWidth, iTop + iWidth, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop - iWidth, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft + iWidth, iTop, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft + iWidth, iTop - iWidth, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop + iWidth, lpcsz, iLen);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft + iWidth, iTop + iWidth, lpcsz, iLen);

   ::SetTextColor((HDC)pdc->get_os_data(), cr);
   ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop, lpcsz, iLen);

   return;

   size size;
   ::GetTextExtentPoint32W(
      (HDC)pdc->get_os_data(),
      lpcsz,
      iLen,
      &size);

   if(m_dc1.get_os_data() == NULL)
   {
      m_dc1.CreateCompatibleDC(pdc);

   }
   m_dc1.SelectObject(pdc->GetCurrentFont());

   if(m_bmp1.get_os_data() == NULL)
   {
      m_bmp1.CreateCompatibleBitmap(pdc, size.cx, size.cy);
      m_dc1.SelectObject(m_bmp1);
   }
   else
   {
      BITMAP bm;
      m_bmp1.GetBitmap(&bm);
      if(bm.bmHeight < size.cx ||
         bm.bmWidth < size.cy)
      {
         m_bmp1.delete_object();
         m_bmp1.CreateCompatibleBitmap(pdc, size.cx, size.cy);
      }
      m_dc1.SelectObject(m_bmp1);
   }


   m_dc1.FillSolidRect(0, 0, size.cx,size.cy, RGB(0, 0, 0));
   m_dc1.SetTextColor(RGB(255, 255, 255));
   ::TextOutW(m_dc1.get_os_data(), 0, 0, lpcsz, iLen);

   System.imaging().channel_gray_blur(&m_dc1,0, 0, size.cx, size.cy,
      &m_dc1, 0, 0, 0, 2);

   System.imaging().clip_color_blend(pdc, iLeft, iTop, size.cx, size.cy,
      crOutline, &m_dc1, 0, 0);


/*   pdc->BeginPath();
   ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop, lpcsz, iLen);
   pdc->EndPath();

   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = crOutline;
   //::ca::pen_sp pen(get_app(), PS_SOLID, iWidth * 2 + 2, crOutline);
   ::ca::pen_sp pen(get_app(),
      PS_SOLID
      | PS_GEOMETRIC
      | PS_ENDCAP_ROUND
      | PS_JOIN_ROUND,
      iWidth * 2,
      &lb);

   ::ca::pen * ppenOld = pdc->SelectObject(pen);
   pdc->StrokePath();
   pdc->SelectObject(ppenOld);*/

//   ::SetTextColor((HDC)pdc->get_os_data(), cr);
   //m_dc1.SetBkMode(TRANSPARENT);
  // ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop, lpcsz, iLen);


}

void XfplayerViewLine::EmbossedTextOut(
      ::ca::application * papp,
      ::ca::graphics * pdc,
      ::ca::graphics * pdcCache,
      const char * lpcsz,
      int iLeft,
      int iTop,
      int iWidth,
      COLORREF cr,
      COLORREF crOutline,
      int iLen,
      double dBlend)
{
   bool bSaveProcessing =  !m_bEnhancedEmboss;


   if(bSaveProcessing)
   {
      pdc->BeginPath();
      pdc->TextOut(iLeft, iTop, string(lpcsz, iLen));
      pdc->EndPath();

      LOGBRUSH lb;
      lb.lbStyle = BS_SOLID;
      lb.lbColor = crOutline;
      ::ca::pen_sp pen;
      pen->construct(
         PS_SOLID
         | PS_GEOMETRIC
         | PS_ENDCAP_ROUND
         | PS_JOIN_ROUND,
         iWidth * 2,
         &lb);

      ::ca::pen * ppenOld = pdc->SelectObject(pen);
      pdc->StrokePath();
      pdc->SelectObject(ppenOld);

      ::SetTextColor((HDC)pdc->get_os_data(), cr);
      pdc->TextOut(iLeft, iTop, string(lpcsz, iLen));
   }
   else
   {
      if(m_bEnhancedEmboss)
      {
         if(!m_bCacheEmboss || m_wstrCache != lpcsz)
         {
            CacheEmboss(
               papp,
               pdc,
               m_str,
               m_str.get_length(),
               m_dibMain);
         }


      }

      size size = pdc->GetTextExtent(string(lpcsz, iLen));

      size.cx += (long) (max(1.0, m_floatRateX * 5.0) * 2.0);
      size.cy += (long) (max(1.0, m_floatRateX * 5.0) * 2.0);

      System.imaging().color_blend(pdc, point(iLeft - 1, iTop - 1), size,
         pdcCache, point(iLeft, 0), dBlend);


      System.imaging().AlphaTextOut(
         pdc,
         iLeft, iTop,
         lpcsz, iLen,
         cr,
         dBlend);
   }


}



void XfplayerViewLine::SetColors(COLORREF cr, COLORREF crOutline)
{
   m_cr = cr;
   m_crOutline = crOutline;
}




void XfplayerViewLine::GetLogFont(LOGFONT &lf)
{
   lf = m_logfont;
}


void XfplayerViewLine::CacheEmboss(
   ::ca::application * papp,
   ::ca::graphics * pdc,
   const char * lpcsz,
   int iLen,
   ::ca::dib * pdibCache)
{
   UNREFERENCED_PARAMETER(papp);
   if(!m_bEnhancedEmboss)
      return;

   if(m_bCacheEmboss && m_wstrCache == lpcsz)
      return;

   m_wstrCache = lpcsz;
   m_bCacheEmboss = true;

   TRACE("CLyricViewLine::CacheEmboss: %s\n", lpcsz);
   size size;
   m_dcextension.GetTextExtent(
      pdc,
      lpcsz,
      iLen,
      size);

   size.cx += (long) (max(1.0, m_floatRateX * 5.0) * 2.0);
   size.cy += (long) (max(1.0, m_floatRateX * 5.0) * 2.0);


   pdibCache->create(size);
   ::ca::graphics * pdcCache = pdibCache->get_graphics();
   ::ca::font * pfontOld = pdcCache->SelectObject(m_font);

   pdcCache->FillSolidRect(0, 0, size.cx,size.cy, RGB(0, 0, 0));
   pdcCache->SetTextColor(RGB(255, 255, 255));
   m_dcextension.TextOut(
      pdcCache,
      (int) (max(1.0, m_floatRateX * 5.0)),
      (int) (max(1.0, m_floatRateX * 5.0)),
      lpcsz, iLen);

/*   BYTE b[5 * 5] =
      {
         8, 8, 8, 8, 8,
         8, 4, 4, 4, 8,
         8, 4, 0, 4, 8,
         8, 4, 4, 4, 8,
         8, 8, 8, 8, 8,
      };*/
   System.imaging().channel_spread(pdcCache, null_point(), size, pdcCache, null_point(), 0,
      long (max(1.0, m_floatRateX * 2.3)));
   System.imaging().channel_alpha_gray_blur(pdcCache, null_point(), size, pdcCache, null_point(), 0, 5);
   System.imaging().pre_color_blend(pdcCache, pdcCache, RGB(92, 92, 92));
   pdibCache->channel_multiply(::visual::rgba::channel_alpha, 1.1);



   pdc->SelectObject(pfontOld);
}


void XfplayerViewLine::SetFont(::ca::font * pfont)
{
   ASSERT(pfont != NULL);
   if(m_font.m_p == NULL)
   {
      m_font.create(get_app());
   }
   m_font->operator=(*pfont);
}

void XfplayerViewLine::SetFont(visual::font * pfont)
{
   SetFont(pfont->GetFont());
}

void XfplayerViewLine::PrepareURLLinks()
{
   int iStart = 0;
   int iEnd = 0;
   string str;
   while(PcreUtil::find(m_str, "(^|\\s|([;\"()]+))(((((http|https)://))|(www\\.))[0-9a-zA-Z./\\-_?=]+)(([;\"()]+)|\\s|$)", 3, iStart, iEnd))
   {
      m_straLink.add(m_str.Mid(iStart, iEnd - iStart));
      m_iaLinkStart.add(iStart);
      m_iaLinkEnd.add(iEnd - 1);
   }


}

bool XfplayerViewLine::CharHasLink(int iChar)
{
   return GetCharLink(iChar) > -1;
}

bool XfplayerViewLine::GetCharLink(string & str, int iChar)
{
   int iLink = GetCharLink(iChar);
   if(iLink < 0)
      return false;
   str = m_straLink[iLink];
   return true;
}

user::e_line_hit XfplayerViewLine::GetLink(string & strUrl, point ptCursor)
{
   int iChar;
   user::e_line_hit etest = hit_test(ptCursor, iChar);
   if(etest == ::user::line_hit_link)
   {
      GetLink(strUrl, iChar);
   }
   return etest;
}

int XfplayerViewLine::GetCharLink(int iChar)
{
   for(int i = 0; i < m_iaLinkStart.get_size(); i++)
   {
      if(iChar >= m_iaLinkStart[i] &&
         iChar <= m_iaLinkEnd[i])
      {
         return i;
      }
   }
   return -1;
}

::user::e_line_hit XfplayerViewLine::hit_test(const POINT &ptCursorParam, int &iChar)
{
   bool bInside;
   point ptCursor = ptCursorParam;
   rect rectPlacement;
   GetPlacement(rectPlacement);
   bInside = rectPlacement.contains(ptCursor) != 0;
   if(!bInside)
   {
      iChar =  -1;
      return user::line_hit_none;
   }
   else
   {
      if(CalcChar(ptCursor, iChar))
      {
         if(CharHasLink(iChar))
         {
            return user::line_hit_link;
         }
         else
         {
            return user::line_hit_normal;
         }
      }
      else
      {
         iChar =  -1;
         return user::line_hit_none;
      }
   }

}

bool XfplayerViewLine::CalcChar(point pt, int &iChar)
{
   rect rectPlacement;
   GetPlacement(rectPlacement);
   bool bInside = rectPlacement.contains(pt) != 0;
   if(!bInside)
      return false;
   for(int i = 0; i < m_iaPosition.get_size() - 1; i++)
   {
      if(pt.x >= m_iaPosition[i] &&
         pt.x < m_iaPosition[i + 1])
      {
         iChar = i;
         return true;
      }
   }
   return false;
}


void XfplayerViewLine::OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   int iChar;
   if(CalcChar(pmouse->m_pt, iChar))
   {
      if(CharHasLink(iChar))
      {
         //::SetCursor(get_interaction()->KaraokeGetHandCursor());
      }
   }
   /*
   LyricViewLineSelection & selection = GetSelection();

   if(selection.GetState() == LyricViewLineSelection::StateTracking)
   {

      bool bInside;
      int iToken;
      int iChar;
      rect rectPlacement;

      GetPlacement(rectPlacement);
      bInside = rectPlacement.contains(pt) != 0;

      if(!bInside)
      {
         if(pt.y < rectPlacement.top
            || (pt.y <= rectPlacement.bottom &&
            pt.x < rectPlacement.left))
         {
            selection.SetSelBefore(*this);
            GetWndRender()->Redraw(rectPlacement);
         }
         else
         {
            selection.SetSelAfter(*this);
            GetWndRender()->Redraw(rectPlacement);
         }
         return false;
      }
      else // bInside == true
      {
         DWORD fwKeys = user; // key flags
         if(m_tokenaMain.get_size() <= 0)
            return false;
         if(CalcChar(pt, iToken, iChar))
         {
            selection.m_item.SetTokenEnd(iToken);
            selection.m_item.SetCharEnd(iChar);
            GetWndRender()->Redraw(rectPlacement);
         }
         else
         {
            if(pt.x < m_tokenaMain.element_at(0).get_position())
            {
               selection.SetSelBefore(*this);
            }
            else
            {
               selection.SetSelAfter(*this);
            }
            GetWndRender()->Redraw(rectPlacement);
         }
         return true;
      }
   }
   else
   {
      if(IsInHover())
      {
         UpdateHover(pt);
      }
      else
      {
         bool bInside;
         rect rectPlacement;

         GetPlacement(rectPlacement);
         bInside = rectPlacement.contains(pt);
         if(bInside)
         {
            UpdateHover(pt);
         }
      }

   }*/
   if(GetSelection().OnMouseMove(*this, pmouse->m_nFlags, pmouse->m_pt))
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

void XfplayerViewLine::OnSetCursor(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //if(IsInHover())
   //{
     // ::SetCursor(get_interaction()->KaraokeGetHandCursor());
      //return TRUE;
   //}

}

void XfplayerViewLine::OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::mouse, pmouse, pobj);
   if(GetSelection().OnLButtonDown(*this, pmouse->m_nFlags, pmouse->m_pt))
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

void XfplayerViewLine::OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   int iChar;
   if(CalcChar(pmouse->m_pt, iChar))
   {
      if(CharHasLink(iChar))
      {
         string str;
         str = m_straLink[GetCharLink(iChar)];
         ASSERT(m_hwnd->IsWindow());
         System.open_link(str);
      }
   }
   if(GetSelection().OnLButtonUp(*this, pmouse->m_nFlags, pmouse->m_pt))
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

void XfplayerViewLine::OnTimer(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //if(GetSelection().OnTimer(*this, user))
     // return true;
}

::ca::font * XfplayerViewLine::GetFont()
{
   return m_font;
}

void XfplayerViewLine::SetBlend(double d)
{
   ASSERT(d >= 0.0);
   ASSERT(d <= 1.0);
   if(d < 0.0 || d > 1.0)
      return;
   m_dBlend = d;
}


void XfplayerViewLine::UpdateHover(point &ptCursor)
{
   int iLine = m_iIndex;
   int iChar;

   user::e_line_hit etest = hit_test(
      ptCursor, iChar);
   if(etest == ::user::line_hit_link)
   {
      if(m_iLinkHoverIndex !=
         GetLinkIndex(iLine, iChar))
      {
         m_iLinkHoverIndex = GetLinkIndex(iLine, iChar);
         rect rect;
         GetPlacement(rect);
//         get_interaction()->_001RedrawWindow();
      }
   }
   else
   {
      if(m_iLinkHoverIndex != -1)
      {
         m_iLinkHoverIndex = -1;
         rect rect;
         GetPlacement(rect);
         //get_interaction()->_001RedrawWindow();
      }
   }

}


bool XfplayerViewLine::IsInHover()
{
   if(m_iLinkHoverIndex >= 0)
      return true;
   else
      return false;
}



int XfplayerViewLine::GetLinkIndex(int iLine, int iChar)
{
   if(!HasLink())
      return -1;
   if(iLine != m_iIndex)
      return -1;
   return GetCharLink(iChar);
}


bool XfplayerViewLine::HasLink()
{
   return m_iaLinkStart.get_count() > 0;
}

::user::interaction * XfplayerViewLine::get_interaction()
{
   return m_pContainer->m_pinteraction;
}

inline XfplayerViewLineSelection & XfplayerViewLine::GetSelection()
{
   if(m_pContainer == NULL)
      return m_selection;
   else
      return m_pContainer->GetSelection();
}
