#include "framework.h"

const int32_t XfplayerViewLine::AlignLeft = 1;
const int32_t XfplayerViewLine::AlignRight = 2;

XfplayerViewLine::XfplayerViewLine(sp(::axis::application) papp) :
   element(papp),
   m_dibMain(allocer()),
   m_dcextension(papp),
   m_font(allocer())
{
   m_pContainer                  = NULL;
   m_bEnhancedEmboss             = true;
   m_bCacheEmboss                = false;
   m_cr                          = ARGB(255, 255, 255, 255);
   m_crOutline                   = ARGB(255, 0, 0, 0);
   m_nFont                       = 0;
   m_lpBitmapData                = NULL;
   m_bAutoSizeX                  = false;
   m_bAutoSizeY                  = false;
   m_iAlign                      = AlignLeft;
   m_rect.left                       = 0;
   m_rect.top                        = 0;
   m_rect.right                      = 0;
   m_rect.bottom                     = 0;
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
   element(pContainer->get_app()),
   m_dibMain(pContainer->allocer()),
   m_dcextension(pContainer->get_app()),
   m_font(allocer())
{
   m_pContainer                  = pContainer;
   m_bEnhancedEmboss             = true;
   m_bCacheEmboss                = false;
   m_nFont                       = 0;
   m_lpBitmapData                = NULL;
   m_bAutoSizeX                  = false;
   m_bAutoSizeY                  = false;
   m_iAlign                      = AlignLeft;
   m_rect.left                       = 0;
   m_rect.top                        = 0;
   m_rect.right                      = 0;
   m_rect.bottom                     = 0;
   m_bVisible                    = false;
   m_iAnimateType                = AnimateNoAnimate;
   m_iTextEffect                 = EffectSimple;
   m_dAnimateProgress            = 0;
   m_dAnimateProgress            = 0;
   m_dAnimateProgressIncrement   = 1.0;
   m_iIndex                      = 0;
}

XfplayerViewLine::XfplayerViewLine(const XfplayerViewLine & line) :
   element(line.get_app()),
   m_dibMain(allocer()),
   m_dcextension(line.get_app()),
   m_font(allocer())
{
   operator = (line);
}

XfplayerViewLine::~XfplayerViewLine()
{
}


bool XfplayerViewLine::PrepareLine(::draw2d::graphics * pdc, const string & str, int32_t flags, const RECT & rect)
{
   UNREFERENCED_PARAMETER(flags);
   m_straLink.remove_all();
   m_iaLinkStart.remove_all();
   m_iaLinkEnd.remove_all();
   strsize               iChars;
   strsize               iStr;
   strsize               iStrLen;
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
   CalcCharsPositions(pdc, rect);
   return true;
}

/*bool XfplayerViewLine::PrepareLine(
   ::draw2d::graphics * pdc,
   const wchar_t * lpcsz,
   int32_t flags,
   visual::font *pFont,
   LPRECT pRect)
{
   m_bCacheEmboss = false;
   int32_t               iChars;
   int32_t               iStr;
   int32_t               iStrLen;
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

void XfplayerViewLine::AddChar(WCHAR wch, strsize & index)
{
   index++;
   if(m_iaPosition.get_size() < index + 2)
   {
        m_iaPosition.allocate(m_iaPosition.get_size() + 10);
   }

   m_str += wch;
    ASSERT(m_str.get_length() - 1 == index);


}

void XfplayerViewLine::AddChar(WCHAR wch, strsize & index, visual::font * pFont)
{
   UNREFERENCED_PARAMETER(pFont);
   index++;
   if(m_iaPosition.get_size() < index + 2)
   {
        m_iaPosition.allocate(m_iaPosition.get_size() + 10);
   }
   m_str += wch;
   ASSERT(m_str.get_length() - 1 == index);

}


void XfplayerViewLine::GetPlacement(LPRECT lprect)
{
   *lprect = m_rect;
}

bool XfplayerViewLine::to(::draw2d::graphics * pdc,bool bDraw,const RECT & rect,rect_array & rectaModified,bool bRecalcLayout)
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

//   pdc->SetBkMode(TRANSPARENT);

   point iMargin;
   iMargin.x = 3;
   iMargin.y = 3;

   if(!IsVisible())
   {
      return true;
   }
   if(bRecalcLayout || m_rectClient != rect)
   {
      m_bCacheEmboss = false;
      CalcCharsPositions(
         pdc,
         rect);
   }

   ::rect rectTextOut;
   GetPlacement(rectTextOut);

   switch(m_iAnimateType)
   {
   case AnimateNoAnimate:
      {
         if(bDraw)
         {
            strsize iLink = 0;
            strsize iChar = 0;
            while(true)
            {
               pdc->SelectObject(m_font);
               if(iChar >= strFinal.get_length())
                  break;
               if(iLink >= m_iaLinkStart.get_size())
               {
                  size size = pdc->GetTextExtent(strFinal.Left(iChar));
                  EmbossedTextOut(pdc, strFinal.Mid(iChar), rectTextOut.left + size.cx, rectTextOut.top, 0, m_cr, m_crOutline, strFinal.get_length() - iChar, dBlend);
                  break;
               }
               else if(m_iaLinkStart[iLink] > iChar)
               {
                  size size = pdc->GetTextExtent(strFinal.Left(iChar));
                  EmbossedTextOut(pdc, strFinal.Mid(iChar), rectTextOut.left + size.cx, rectTextOut.top, 0,m_cr,m_crOutline,m_iaLinkStart[iLink],dBlend);
               }
               pdc->SelectObject(m_fontLink);
               size size = pdc->GetTextExtent(strFinal.Left(m_iaLinkStart[iLink]));

               EmbossedTextOut(pdc,strFinal.Mid(m_iaLinkStart[iLink]),rectTextOut.left + size.cx,rectTextOut.top,0,m_cr,m_crOutline,m_iaLinkEnd[iLink] - m_iaLinkStart[iLink] + 1,dBlend);
               iChar = m_iaLinkEnd[iLink] + 1;
               iLink++;
            }
            if(GetSelection().m_iCharStartSource >= 0)
            {
               index iStart;
               index iLineStart;
               index iLineEnd;
               strsize iCharStart;
               strsize iCharEnd;
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
               index iEnd;
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
                  ::draw2d::dib_sp dib(allocer());
                  if(rect.area() > 0)
                  {
                     dib->create(rect.size());
                     dib->Fill(255, 255, 255, 255);
                     dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
                     pdc->flush();

                     point pt = pdc->GetViewportOrg();
                     dib->from(null_point(), pdc, pt + rect.top_left(), rect.size());
                     //dib->get_graphics()->FillSolidRect(0, 0, 16, 16, ARGB(255, 255, 0, 255));
                     dib->Invert();
                     //dib->fill_channel(0, ::visual::rgba::channel_blue);
                     dib->fill_channel(255, ::visual::rgba::channel_alpha);
                     dib->to(pdc, rect.top_left(), rect.size(), null_point());
                  }
               }
            }

         }
       }
       break;
   case AnimateRHL:
      {
         int32_t iLeft = m_iaPosition.element_at(0);
         int32_t iLeftDiff  = 0;
         int32_t iLastLeftDiff = 0;
         int32_t i;
         for(i = 0; i < m_iaPosition.get_size(); i++)
         {
            iLastLeftDiff = iLeftDiff;
            iLeftDiff = m_iaPosition.element_at(i) - iLeft;
            if((int32_t) m_dAnimateProgress <= iLeftDiff)
            {
               //i--;
               break;
            }
         }
         ::draw2d::region rgn;
         string strFinal(m_str);
         string strLeft = strFinal.Right(strFinal.get_length() - i);
         int32_t iLeftOffset;
         iLeftOffset = iLastLeftDiff - (int32_t) m_dAnimateProgress;
           ::rect rectTextOut;
           GetPlacement(rectTextOut);
           rectTextOut.left += iLeftOffset;
           if(bDraw)
           {
              EmbossedTextOut(pdc,strLeft,rectTextOut.left,rectTextOut.top,
               0,
               m_cr,
               m_crOutline,
               strFinal.get_length(),
               dBlend);
           }
           int32_t iMaxCounter = MAX((int32_t) m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_rect.right - m_rect.left);
           int32_t iRight = iMaxCounter - (int32_t) m_dAnimateProgress;
           if(iRight < m_rect.right)
           {
              int32_t iRightEnd;
              int32_t i;
              for(i = 0; i < m_iaPosition.get_size(); i++)
              {
                 iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                 if(iRightEnd >= m_rect.right)
                 {
                    break;
                 }
              }
              string strRight = strFinal.Left(i);
              rectTextOut.left = iRight;
              if(bDraw)
              {
                 EmbossedTextOut(pdc,strRight,rectTextOut.left,rectTextOut.top,0,m_cr,m_crOutline,strFinal.get_length(),dBlend);
              }
           }

           if(&rectaModified != NULL)
           {
              ::rect baserect;
              rgn.get_bounding_box(baserect);
              rectaModified.add(baserect);

           }
      }
      break;
   default:
      ASSERT(FALSE);
   }




   return true;

}

bool XfplayerViewLine::to(::draw2d::graphics * pdc,bool bDraw,const RECT & rect,rect_array & rectaModified,::count * count,bool bRecalcLayout,COLORREF crColor,::draw2d::pen_sp sppen)
{
   UNREFERENCED_PARAMETER(count);

   ::rect rectPlacement;
   GetPlacement(rectPlacement);

   pdc->set_font(m_font);

//   pdc->SetBkMode(TRANSPARENT);

   point iMargin;
   {
      iMargin.x = (LONG) (sppen->m_dWidth / 2.0);
      iMargin.y = (LONG) (sppen->m_dWidth / 2.0);
   }

   if(!IsVisible())
   {
      class rect rect(m_rectInvalidate);
      if(!is_null(rectaModified))
      {
         class rect baserect(rect);
         rectaModified.add(baserect);
      }

      Validate(rect);

      return true;
   }
   if(bRecalcLayout)
   {
      CalcCharsPositions(pdc, rect);
      pdc->SelectObject(m_font);
   }


   switch(m_iAnimateType)
   {
   case AnimateNoAnimate:
      {
         string strFinal;
         strFinal = m_str;
         pdc->SelectObject(sppen);

         ::draw2d::brush_sp brushText(allocer(), crColor);
         
         pdc->SelectObject(brushText);

         //pdc->set_text_color(crColor);

         ::rect rectTextOut;
         GetPlacement(rectTextOut);
         if(bDraw)
         {
            pdc->_DrawText(
               strFinal, strFinal.get_length(),
               rectTextOut,
               DT_LEFT | DT_BOTTOM);
         }
      }
      break;
   case AnimateRHL:
      {
         if(m_iaPosition.get_size() <= 0)
            break;
//         int32_t iLeft = m_iaPosition.element_at(0);
         int32_t iLeftDiff  = 0;
         //int32_t iLastLeftDiff = 0;
         int32_t i = 0;
/*            for(int32_t i = 0; i < m_iaPosition.get_size(); i++)
            {
                iLastLeftDiff = iLeftDiff;
                iLeftDiff = m_iaPosition.element_at(i) - iLeft;
                if(iLeftDiff >= (int32_t) m_dAnimateProgress)
                {
                    break;
                }
            }*/

            string strFinal(m_str);
            string strLeft = strFinal.Right(strFinal.get_length() - i);
            int32_t iLeftOffset;
            iLeftOffset = iLeftDiff - (int32_t) m_dAnimateProgress;

           pdc->SelectObject(sppen);
         ::draw2d::brush_sp brushText(allocer(), crColor);
         
         pdc->SelectObject(brushText);

           pdc->SelectObject(m_font);
         ::rect rectTextOut;
         GetPlacement(rectTextOut);
         rectTextOut.left += iLeftOffset;
         if(bDraw)
         {
            pdc->_DrawText(
               strLeft, strLeft.get_length(),
               rectTextOut,
               DT_LEFT | DT_BOTTOM);
         }
/*           pFont->TextOutEx(
                pdcForeground,
              rectTextOut,
            1.0,
            rectTextOut.height(),
              strLeft,
              m_iaPosition.get_data(),
                m_iaPosition.get_size(),
              0,
                MapToFontEffect(m_iTextEffect));   */
            int32_t iSpacing = 100;
            int32_t iMaxCounter = MAX(
               (int32_t) m_iaPosition.element_at(m_str.get_length())
                  - m_iaPosition.element_at(0) + iSpacing, m_rect.right - m_rect.left);
            int32_t iRight = iMaxCounter - (int32_t) m_dAnimateProgress;
            if(iRight < m_rect.right)
            {
            /*    int32_t iRightEnd;
                for(int32_t i = 0; i < m_iaPosition.get_size(); i++)
                {
                    iRightEnd = iRight + m_iaPosition.element_at(i) - iLeft;
                    if(iRightEnd >= m_rect.right)
                    {
                        break;
                    }
                }*/
                //string strRight = strFinal.Left(i);
                string strRight = strFinal;
            rectTextOut.left = iRight;
         if(bDraw)
         {

            pdc->_DrawText(
               strRight, strRight.get_length(),
               rectTextOut,
               DT_LEFT | DT_BOTTOM);
         }
/*               pFont->TextOutEx(
                    pdcForeground,
                  rectTextOut,
               1.0,
               rectTextOut.height(),
                  strRight,
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
::draw2d::graphics * pdcForeground,
   primitive_array < visual::font *> * pFonts,
   const RECT & rect)
{
   m_bCacheEmboss = false;
   //visual::font * pFont;
//    ::draw2d::graphics * pdcForeground = m_ptwi->TwiGetDC();
   if(m_str.get_length() <= 0)
      return;
   if(pFonts->get_size() > 0)
   {
      int32_t i, nFont, iFontFound, iMaxExtent, iLeft;
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
            if(size.cx + m_rect.left <= lpcrect->right)
            {
               iFontFound = nFont;
               break;
            }
         }
         else if((m_iAlign & AlignRight) > 0)
         {
            if(m_rect.right - size.cx >= 0)
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
         m_iaPosition[0] = m_rect.left + m_iIndent;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i,
               &size);
            m_iaPosition[i] = size.cx + m_rect.left  + m_iIndent;
         }
         if(m_bAutoSizeX)
         {
            m_rect.right = m_rect.left  + m_iIndent + size.cx;
            }
         if(m_bAutoSizeY)
         {
            m_rect.bottom = m_rect.top + size.cy;
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
         iLeft = m_rect.right - iMaxExtent;
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
            m_rect.left = m_rect.right - size.cx;
            }
            if(m_bAutoSizeY)
            {
            m_rect.bottom = m_rect.top + size.cy;
         }
      }

   }

   else
   {
      int32_t i; //, width;
      size size;
         m_iaPosition[0] = m_rect.left;
         for(i = 1; i <= m_str.get_length(); i++)
         {
            GetTextExtentPoint32W(
               pdcForeground->get_os_data(),
               m_str,
               i ,
               &size);
            m_iaPosition[i] = m_rect.left + size.cx;
         }
      if(m_bAutoSizeX)
      {
         m_rect.right = m_rect.left + size.cx;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
//    m_ptwi->TwiReleaseDC(pdcForeground);

}*/

void XfplayerViewLine::CalcCharsPositions(::draw2d::graphics *             pdc,const RECT & rect)
{
   m_bCacheEmboss = false;
   if(m_str.get_length() <= 0)
      return;

//   ::draw2d::font * pfontOld = pdc->get_current_font();

   int32_t i;
   size size;
   ::rect rectClient(rect);
   m_rectClient = rectClient;
   ::rect rectPlacement;
   GetPlacement(rectPlacement);
   string strMain = m_str;
//   pdc->SelectObject(fontOriginal);
   size = pdc->GetTextExtent(strMain);
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

//   pdc->SelectObject(fontOriginal);
   ::draw2d::text_metric tm;
   pdc->get_text_metrics(&tm);
  // lf.lfWidth = (long) (tm.tmAveCharWidth * m_floatRateX - 1);

  // if(m_font->get_os_data() != NULL)
//      m_font->delete_object();

   ///m_font->CreateFontIndirect(&lf);

   m_font.m_p->m_dFontWidth = m_floatRateX;
   m_font.m_p->m_bUpdated = false;


   if(m_straLink.get_size() > 0)
   {
      *m_fontLink.m_p = *m_font.m_p;
      m_fontLink.m_p->set_underline();
   }


   m_str.Truncate(MIN(84, m_str.length()));

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
      m_iaPosition[0] = m_rect.left + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            (HDC)pdc->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_rect.left + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rect.right = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
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
      iLeft = m_rect.right - iMaxExtent;
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
         m_rect.left = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
   pdc->SelectObject(pfontOld);*/
}

/*void XfplayerViewLine::CalcCharsPositions(
   ::draw2d::graphics *             pdcForeground,
   visual::font *     pFont,
   LPCRECT           lpcrect)
{
   m_bCacheEmboss = false;
   if(m_str.get_length() <= 0)
      return;
    ::draw2d::font * pfontOriginal = pdcForeground->get_current_font();
   pdcForeground->SelectObject(pFont->GetFont());
   int32_t i, iLeft, iRight, iMaxExtent;
   size size;
   rect rectClient(lpcrect);
   m_rectClient = rectClient;
   visual::font * pfont = pFont;
   ::draw2d::graphics * pdc = pdcForeground;
   ASSERT(pfont != NULL);
   rect rectPlacement;
   GetPlacement(rectPlacement);
   string strMain = m_str;
   GetTextExtentPoint32W(
      (HDC)pdc->get_os_data(),
      strMain,
      strMain.get_length(),
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
   LOGFONTW lf;
   pfont->GetFont()->GetLogFont(&lf);
   pdc->SelectObject(pfont->GetFont());
   TEXTMETRICW tm;
   pdc->GetTextMetrics(&tm);
   lf.lfWidth = (long) (tm.tmAveCharWidth * m_floatRateX - 1);
   m_font->CreateFontIndirect(&lf);





   pdc->SelectObject(m_font);
   if(m_iAlign == AlignLeft)
   {
      m_iaPosition[0] = m_rect.left + m_iIndent;
      iRight = 0;
      for(i = 1; i <= m_str.get_length(); i++)
      {
         GetTextExtentPoint32W(
            pdcForeground->get_os_data(),
            m_str,
            i,
            &size);
         m_iaPosition[i] = iRight = size.cx + m_rect.left + m_iIndent;
      }
      if(m_bAutoSizeX)
      {
         m_rect.right = iRight;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
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
      iLeft = m_rect.right - iMaxExtent;
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
         m_rect.left = iLeft;
        }
      if(m_bAutoSizeY)
      {
         m_rect.bottom = m_rect.top + size.cy;
      }
   }
   pdcForeground->SelectObject(pfontOriginal);
}*/

void XfplayerViewLine::SetAutoSize(bool bAutoSize)
{
   m_bAutoSizeX = bAutoSize;
    m_bAutoSizeY = bAutoSize;
}

void XfplayerViewLine::SetAlign(int32_t iAlign)
{
   m_iAlign = iAlign;
}

XfplayerViewLine & XfplayerViewLine::operator = (const XfplayerViewLine & src)
{
   m_pContainer                  = src.m_pContainer;
   m_bAutoSizeX                  = src.m_bAutoSizeX;
   m_bAutoSizeY                  = src.m_bAutoSizeY;
   m_str                         = src.m_str;
   m_iaPosition                  = src.m_iaPosition;
   m_iAlign                      = src.m_iAlign;
   m_rect.bottom                     = src.m_rect.bottom;
   m_rect.left                       = src.m_rect.left;
   m_rect.right                      = src.m_rect.right;
   m_rect.top                        = src.m_rect.top;
   m_lpBitmapData                = src.m_lpBitmapData;
   m_nFont                       = src.m_nFont;
   m_iAnimateType                = src.m_iAnimateType;
   m_iTextEffect                 = src.m_iTextEffect ;
   m_dAnimateProgress            = src.m_dAnimateProgress;
   m_dAnimateProgressIncrement   = src.m_dAnimateProgressIncrement;
   m_logfont                     = src.m_logfont;
   m_font                        = src.m_font;
   m_bEnhancedEmboss             = src.m_bEnhancedEmboss;
   m_bCacheEmboss                = false;
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
   ::draw2d::graphics *                  pdcForeground,
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
                    if((int32_t)m_dAnimateProgress > MAX(m_iaPosition.element_at(m_str.get_length()) - m_iaPosition.element_at(0) + 100, m_rect.right - m_rect.left))
                        m_dAnimateProgress = 0.0;
                    rect rect;
                    GetPlacement(rect);
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

void XfplayerViewLine::SetAnimateType(int32_t iAnimateType)
{
    m_iAnimateType = iAnimateType;
    m_dAnimateProgress = 0.0;

}

void XfplayerViewLine::SetTextEffect(int32_t iTextEffect)
{
    m_iTextEffect = iTextEffect;
}

void XfplayerViewLine::SetEmbossPen(::draw2d::pen *lpPen)
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
int32_t XfplayerViewLine::MapToFontEffect(int32_t iLineEffect)
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

//void XfplayerViewLine::SetRedrawMode(int32_t iMode)
//{
  //  m_iRedrawMode = iMode;
//}

//void XfplayerViewLine::SetRenderWindow(::window_sp pwindow)
//{
  //  m_pRenderWnd = pwindow;
//}

void XfplayerViewLine::SetRenderCriticalSection(critical_section * pcs)
{
   UNREFERENCED_PARAMETER(pcs);
//    m_pcsRender =   pcs;
}

int32_t XfplayerViewLine::SetLyricPens(::draw2d::pen * ppenLeft, ::draw2d::pen * ppenRight)
{
    m_ppenLyricLeft = ppenLeft;
    m_ppenLyricRight = ppenRight;
    return true;
}

int32_t XfplayerViewLine::SetLyricColors(COLORREF crLeft, COLORREF crRight)
{
    m_crLyricLeft = crLeft;
    m_crLyricRight = crRight;
    return true;

}


void XfplayerViewLine::SetPlacement(const RECT & rect)
{
   
   m_rect = rect;
   
   m_bPendingLayoutUpdate = true;

}


//int32_t XfplayerViewLine::GetVmsFontCount()
/*{
   return m_fonts.get_size();
}

void XfplayerViewLine::AddVmsFont(visual::font * pfont)
{
   m_fonts.add(pfont);
}*/

void XfplayerViewLine::Invalidate(const RECT & rectParam)
{

   rect rectPlacement;

   GetPlacement(rectPlacement);

   rect rectInvalidate;

   if(IsRectEmpty(&rectParam))
   {

      rectInvalidate = rectPlacement;

   }
   else
   {

      rectInvalidate = rectParam;

   }

   m_rectInvalidate.unite(m_rectInvalidate,rectInvalidate);

   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}


void XfplayerViewLine::Validate(const RECT & rectParam)
{
   
   rect rectPlacement;

   GetPlacement(rectPlacement);

   rect rectValidate;

   if(IsRectEmpty(&rectParam))
   {

      rectValidate = rectPlacement;

   }
   else
   {

      rectValidate = rectParam;

   }

   m_rectInvalidate -= rectValidate;

   m_rectInvalidate.intersect(m_rectInvalidate, rectPlacement);

}


bool XfplayerViewLine::IsVisible()
{
   return m_bVisible;
}

void XfplayerViewLine::EmbossedTextOut(::draw2d::graphics * pdc,const char * lpcsz,int32_t iLeft,int32_t iTop,int32_t iWidth,COLORREF cr,COLORREF crOutline,strsize iLen,double dBlend)
{
   EmbossedTextOut(
      pdc,
      m_dibMain,
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
   int32_t cx = 0;
   int32_t width;
   int32_t widthInt;
   int32_t widthExt;
   int32_t cxInt;
   int32_t cxExt;
   int32_t cyInt;
   int32_t cyExt;
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
   for(int32_t i = 0; i < iLen; i++)
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
   m_dc1.SelectObject(pdc->get_current_font());

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

   System.visual().imaging().channel_gray_blur(&m_dc1,0, 0, size.cx, size.cy,
      &m_dc1, 0, 0, 0, 2);

   System.visual().imaging().clip_color_blend(pdc, iLeft, iTop, size.cx, size.cy,
      crOutline, &m_dc1, 0, 0);


   pdc->BeginPath();
   ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop, lpcsz, iLen);
   pdc->EndPath();

   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = crOutline;
   //::draw2d::pen_sp pen(get_app(), PS_SOLID, iWidth * 2 + 2, crOutline);
   ::draw2d::pen_sp pen(get_app(),
      PS_SOLID
      | PS_GEOMETRIC
      | PS_ENDCAP_ROUND
      | PS_JOIN_ROUND,
      iWidth * 2,
      &lb);

   ::draw2d::pen * ppenOld = pdc->SelectObject(pen);
   pdc->StrokePath();
   pdc->SelectObject(ppenOld);*/

//   ::SetTextColor((HDC)pdc->get_os_data(), cr);
   //m_dc1.SetBkMode(TRANSPARENT);
  // ::TextOutW((HDC)pdc->get_os_data(), iLeft, iTop, lpcsz, iLen);


}

void XfplayerViewLine::EmbossedTextOut(::draw2d::graphics * pdc,::draw2d::dib * pdibCache,const char * lpcsz,int32_t iLeft,int32_t iTop,int32_t iWidth,COLORREF cr,COLORREF crOutline,strsize iLen,double dBlend)
{

   UNREFERENCED_PARAMETER(pdibCache);

   bool bSaveProcessing =  !m_bEnhancedEmboss;


   if(bSaveProcessing)
   {
      pdc->BeginPath();
      pdc->TextOut(iLeft, iTop, string(lpcsz, iLen));
      pdc->EndPath();

//      LOGBRUSH lb;
  //    lb.lbStyle = BS_SOLID;
    //  lb.lbColor = crOutline;
      ::draw2d::pen_sp pen;
/*      pen->construct(
         PS_SOLID
         | PS_GEOMETRIC
         | PS_ENDCAP_ROUND
         | PS_JOIN_ROUND,
         iWidth * 2,
         &lb);*/
      pen->create_solid(iWidth * 2, crOutline);


      ::draw2d::pen * ppenOld = pdc->SelectObject(pen);
      pdc->StrokePath();
      pdc->SelectObject(ppenOld);


         ::draw2d::brush_sp brushText(allocer(), cr);
         
         pdc->SelectObject(brushText);

      pdc->TextOut(iLeft, iTop, string(lpcsz, iLen));
   }
   else
   {

      if(m_bEnhancedEmboss)
      {

         if(!m_bCacheEmboss || m_strCache != lpcsz)
         {

            CacheEmboss(pdc, m_str, m_str.get_length(), m_dibMain);

         }

      }

      pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      System.visual().imaging().color_blend(pdc, point(iLeft - 1, iTop - 1), ::size(m_dibMain->m_size.cx, m_dibMain->m_size.cy), m_dibMain->get_graphics(), point(iLeft, 0), dBlend);

      System.visual().imaging().AlphaTextOut(pdc, iLeft, iTop, lpcsz, (int32_t) iLen, cr, dBlend);

   }


}



void XfplayerViewLine::SetColors(COLORREF cr, COLORREF crOutline)
{
   m_cr = cr;
   m_crOutline = crOutline;
}




void XfplayerViewLine::GetLogFont(LOGFONTW &lf)
{
   lf = m_logfont;
}


void XfplayerViewLine::CacheEmboss(::draw2d::graphics * pdc, const char * lpcsz, strsize iLen, ::draw2d::dib * pdibCache)
{
   if(!m_bEnhancedEmboss)
      return;

   if(m_bCacheEmboss && m_strCache == lpcsz)
      return;

   m_strCache = lpcsz;
   m_bCacheEmboss = true;

   TRACE("CLyricViewLine::CacheEmboss: %s\n", lpcsz);
   size size;
   pdc->select_font(m_font);
   m_dcextension.GetTextExtent(pdc, lpcsz, iLen, size);

   size.cx += (LONG) (2 * (MAX(2.0, m_floatRateX * 8.0)));
   size.cy += (LONG) (2 * (MAX(2.0, m_floatRateX * 8.0)));


   if(!pdibCache->create(size))
      return;
   ::draw2d::graphics * pdcCache = pdibCache->get_graphics();
   pdcCache->SelectObject(m_font);

   pdcCache->set_alpha_mode(::draw2d::alpha_mode_set);
   pdcCache->FillSolidRect(0, 0, size.cx,size.cy, ARGB(0, 0, 0, 0));
   pdcCache->set_alpha_mode(::draw2d::alpha_mode_blend);
   draw2d::brush_sp brushText(allocer());
   brushText->create_solid(ARGB(84, 84, 84, 84));
   pdcCache->SelectObject(brushText);
   //pdcCache->SetTextColor();

   m_dcextension.TextOut(pdcCache, (int32_t) (int32_t) ((MAX(2.0, m_floatRateX * 8.0)) / 2), (int32_t) 1 * (int32_t) ((MAX(2.0, m_floatRateX * 8.0)) / 2), lpcsz, iLen);

   System.visual().imaging().channel_spread_set_color(pdcCache, null_point(), size, pdcCache, null_point(), 0, int32_t (MAX(1.0, m_floatRateX * 2.0)), ARGB(23, 23, 23, 23));

   pdcCache->set_alpha_mode(::draw2d::alpha_mode_blend);
   System.visual().imaging().channel_alpha_gray_blur(pdcCache, null_point(), size, pdcCache, null_point(), 0, int32_t (MAX(1.0, m_floatRateX * 3.0)));
   System.visual().imaging().channel_alpha_gray_blur(pdcCache, null_point(), size, pdcCache, null_point(), 0, int32_t (MAX(1.0, m_floatRateX * 3.0)));

   /*pdibCache->fill_channel(92, ::visual::rgba::channel_blue);
   pdibCache->fill_channel(92, ::visual::rgba::channel_green);
   pdibCache->fill_channel(92, ::visual::rgba::channel_red);*/

   //System.visual().imaging().pre_color_blend(pdcCache, pdcCache, ARGB(92, 92, 92, 92));

   pdibCache->set(0, 0, 0);

}


void XfplayerViewLine::SetFont(::draw2d::font * pfont)
{
   ASSERT(pfont != NULL);
   if(m_font.m_p == NULL)
   {
      m_font.alloc(allocer());
   }
   m_font->operator=(*pfont);
}

void XfplayerViewLine::SetFont(visual::font * pfont)
{
   SetFont(pfont->GetFont());
}

void XfplayerViewLine::PrepareURLLinks()
{

   strsize iStart = 0;

   strsize iEnd = 0;

   string str;

   while(cregexp_util::find(m_str, "/^|\\s|([;\"()]+))(((((http|https)://))|(www\\.))[0-9a-zA-Z./\\-_?=]+)(([;\"()]+)|\\s|$/", 3, &iStart, &iEnd))
   {
      m_straLink.add(m_str.Mid(iStart, iEnd - iStart));
      m_iaLinkStart.add(iStart);
      m_iaLinkEnd.add(iEnd - 1);
   }


}

bool XfplayerViewLine::CharHasLink(strsize iChar)
{
   return GetCharLink(iChar) > -1;
}

bool XfplayerViewLine::GetCharLink(string & str, strsize iChar)
{
   index iLink = GetCharLink(iChar);
   if(iLink < 0)
      return false;
   str = m_straLink[iLink];
   return true;
}

user::e_line_hit XfplayerViewLine::GetLink(string & strUrl, point ptCursor)
{
   strsize iChar;
   user::e_line_hit etest = hit_test(ptCursor, iChar);
   if(etest == ::user::line_hit_link)
   {
      GetCharLink(strUrl, iChar);
   }
   return etest;
}

index XfplayerViewLine::GetCharLink(strsize iChar)
{
   for(index i = 0; i < m_iaLinkStart.get_size(); i++)
   {
      if(iChar >= m_iaLinkStart[i] &&
         iChar <= m_iaLinkEnd[i])
      {
         return i;
      }
   }
   return -1;
}

::user::e_line_hit XfplayerViewLine::hit_test(const POINT &ptCursorParam, strsize &iChar)
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

bool XfplayerViewLine::CalcChar(point pt, strsize &iChar)
{
   rect rectPlacement;
   GetPlacement(rectPlacement);
   bool bInside = rectPlacement.contains(pt) != 0;
   if(!bInside)
      return false;
   for(int32_t i = 0; i < m_iaPosition.get_size() - 1; i++)
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


void XfplayerViewLine::OnMouseMove(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   strsize iChar;
   if(CalcChar(pmouse->m_pt, iChar))
   {
      if(CharHasLink(iChar))
      {
         pmouse->m_ecursor = ::visual::cursor_hand;
      }
   }
   /*
   lyric_view_line_selection & selection = GetSelection();

   if(selection.GetState() == lyric_view_line_selection::StateTracking)
   {

      bool bInside;
      int32_t iToken;
      int32_t iChar;
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
         uint32_t fwKeys = user; // key flags
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
   if(GetSelection().OnMouseMove(*this, (UINT) pmouse->m_nFlags, pmouse->m_pt))
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

void XfplayerViewLine::OnSetCursor(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //if(IsInHover())
   //{
     // pmouse->m_ecursor = ::visual::cursor_hand;
      //return TRUE;
   //}

}

void XfplayerViewLine::OnLButtonDown(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj);
   if(GetSelection().OnLButtonDown(*this, (UINT) pmouse->m_nFlags, pmouse->m_pt))
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

void XfplayerViewLine::OnLButtonUp(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   strsize iChar;
   if(CalcChar(pmouse->m_pt, iChar))
   {
      if(CharHasLink(iChar))
      {
         string str;
         str = m_straLink[GetCharLink(iChar)];
         ASSERT(m_oswindow->IsWindow());
         System.open_link(str);
      }
   }
   if(GetSelection().OnLButtonUp(*this, (UINT) pmouse->m_nFlags, pmouse->m_pt))
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

void XfplayerViewLine::OnTimer(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //if(GetSelection().OnTimer(*this, user))
     // return true;
}

::draw2d::font * XfplayerViewLine::GetFont()
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
   ::index iLine = m_iIndex;
   strsize iChar;

   user::e_line_hit etest = hit_test(ptCursor, iChar);
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



index XfplayerViewLine::GetLinkIndex(index iLine, strsize iChar)
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

sp(::user::interaction) XfplayerViewLine::get_interaction()
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
