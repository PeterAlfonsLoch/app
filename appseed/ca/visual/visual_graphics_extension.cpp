#include "framework.h"


namespace visual
{


   void word_break(::ca::graphics * pdc, const char * lpcsz, LPCRECT lpcrect, string &str1, string & str2);


   graphics_extension::graphics_extension(::ca::application * papp) :
      ca(papp)
   {

   }

   graphics_extension::~graphics_extension()
   {

   }

   bool graphics_extension::TextOut(::ca::graphics * pdc, int32_t x, int32_t y, const char * lpcsz, strsize iCount)
   {
      return pdc->TextOut(x, y, string(lpcsz, iCount));
      //return ::TextOutU((HDC)pdc->get_os_data(), x, y, lpcsz, iCount);
   }

   void word_break(::ca::graphics * pdc, const char * lpcsz, LPCRECT lpcrect, string &str1, string & str2)
   {

      string str;

      rect rectClip(*lpcrect);

      wstring wstr = ::ca::international::utf8_to_unicode(lpcsz);

      const wchar_t * lpwsz = wstr;

      index iFind = str.find(L' ');

      if(iFind < 0)
      {

         size_t i = 1;

         size sz;

         while(i < wcslen(wstr))
         {

#ifdef WINDOWSEX

            ::GetTextExtentPoint32W((HDC)pdc->get_os_data(), lpwsz, (int32_t) i, &sz);

#else

            throw todo(::ca::get_thread_app());

            // ::GetTextExtentPoint32((HDC)pdc->get_os_data(), ::ca::international::unicode_to_utf8(lpwsz), (int32_t) ::ca::international::unicode_to_utf8(lpwsz).get_lengt(), &sz);

#endif

            if(sz.cx > rectClip.width())
            {

               if(i == 1)
                  break;

               i--;

               break;

            }

            i++;

         }

         ::ca::international::unicode_to_utf8(str1, lpwsz, i);

         ::ca::international::unicode_to_utf8(str2, &lpwsz[i]);

      }
      else
      {

         ::ca::international::unicode_to_utf8(str1, lpwsz, iFind);

         ::ca::international::unicode_to_utf8(str2, &lpwsz[iFind + 1]);

      }

   }


   void graphics_extension::GetTextExtent(::ca::graphics *pdc, const char * lpcsz, base_array < size > & sizea)
   {
      string str(lpcsz);
      strsize iLen = str.get_length();
      sizea.set_size(iLen);
      if(iLen > 0)
      {
         sizea[0] = (uint32_t) 0;
      }
      for(int32_t i = 1; i < iLen; i++)
      {
         ::GetTextExtentPoint32U(
            (HDC)pdc->get_os_data(),
            str,
            i,
            &sizea[i]);
      }

   }

   void graphics_extension::GetTextExtent(::ca::graphics *pdc, const char * lpsz, size & size)
   {
      /*string str(lpwsz);
      if(pdc == NULL)
         return;
      ::GetTextExtentPoint32U(
         (HDC)pdc->get_os_data(),
         (const char *) str,
         str.get_length(),
         &size);*/

      size = pdc->GetTextExtent(lpsz);

   }

   void graphics_extension::GetTextExtent(::ca::graphics *pdc, const char * lpcsz, strsize iCount, size & size)
   {
      /*::GetTextExtentPoint32U(
         (HDC)pdc->get_os_data(),
         lpcsz,
         iCount,
         &size);*/

      size = pdc->GetTextExtent(string(lpcsz, iCount));

   }

   strsize graphics_extension::_EncodeV033(string & str)
   {
      strsize iStart = 0;
      strsize iIndex;
      strsize iLen = str.get_length();
      while(true)
      {
         iIndex = str.find(L'&', iStart);
         if(iIndex < 0)
            break;
         if(iIndex + 1 >= iLen)
            break;
         if(str[iIndex + 1] == L'&')
         {
            iIndex++;
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
         }
         else
         {
            // Found !
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
            return iIndex;
         }

         if(iIndex >= str.get_length())
            break;
      }
      // Not Found
      return -1;
   }



   /*int32_t graphics_extension::_FindPrefixV1(const wchar_t * lpcsz)
   {
      int32_t iStart = 0;
      int32_t iIndex;
      int32_t iLen = wcslen(lpcsz);
      wchar_t * lpszFind;
      while(true)
      {
         lpszFind = wcschr(lpcsz + iStart, L'&');
         if(lpszFind == NULL)
            break;
         iIndex = (int32_t)(lpsz - m_pchData);
         if(iIndex + 1 >= iLen)
            break;
         if(lpcsz[iIndex + 1] == L'&')
         {
            iIndex++;
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
         }
         else
         {
            // Found !
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
            return iIndex;
         }

         if(iIndex >= str.get_length())
            break;
      }
      // Not Found
      return -1;
   }*/

   void graphics_extension::FillSolidRect(HDC hdc, const __rect64 * lpRect, COLORREF clr)
   {

#ifdef WINDOWSEX

      ::SetBkColor(hdc, clr);

      rect rect;

      if(::copy(rect, lpRect))
      {

         ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);

      }

#else

      throw todo(get_app());

#endif

   }


   void graphics_extension::FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF clr)
   {

#ifdef WINDOWSEX

      ::SetBkColor(hdc, clr);

      ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);

#else

      throw todo(get_app());

#endif

   }


   void graphics_extension::FillSolidRect(HDC hdc, int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr)
   {

#ifdef WINDOWSEX

      ::SetBkColor(hdc, clr);

      rect rect(x, y, x + cx, y + cy);

      ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);

#else

      throw todo(get_app());

#endif

   }


} // namespace visual


namespace visual
{

   int32_t graphics_extension::_DrawText(::ca::graphics * pdc, const char * lpcsz, LPCRECT lpcrect, UINT uiFormat, ::ca::font * pfontUnderline)
   {


//      ::

  //    if(pdc->GetBkMode() == TRANSPARENT

      wstring wstr = ::ca::international::utf8_to_unicode(lpcsz);

      string str(lpcsz);
      string str2;
      rect rectClip(lpcrect);


      if(rectClip.area() <= 0)
         return 0;

      size sz;
      sz.cx = 0;
      sz.cy = 0;

      strsize iUnderline = _EncodeV033(str);

      strsize iLen = str.get_length();

      if((uiFormat & DT_END_ELLIPSIS) != 0 || (uiFormat & DT_WORDBREAK) != 0)
      {
         sz = pdc->GetTextExtent(str, (int32_t) iLen);
         if(sz.cx > rectClip.width())
         {
            if((uiFormat & DT_WORDBREAK) != 0 && sz.cy * 2 <= rectClip.height())
            {
               string str1;
               string str2;
               word_break(pdc, lpcsz, rectClip, str1, str2);
               iLen = str.get_length();
               sz = pdc->GetTextExtent(str, (int32_t) iLen);
               if(sz.cx <= rectClip.width())
               {
                  goto skip1;
               }
            }
            iLen += 3;
            char * lpsz = str.GetBuffer(iLen + 1);
            strsize i = sz.cx == 0 ? iLen : (iLen * rectClip.width()) / sz.cx;
            if(i > iLen)
               i = iLen;
            if(i < 4)
               i = 4;

            while(true)
            {
               lpsz[i - 4] = '.';
               lpsz[i - 3] = '.';
               lpsz[i - 2] = '.';
               lpsz[i - 1] = '\0';
               sz = pdc->GetTextExtent(lpsz, (int32_t) i);
               if(sz.cx < rectClip.width())
               {
                  if(i >= iLen)
                     break;
                  i++;
               }
               else
               {
                  break;
               }
               strncpy(lpsz, str, i);
            }
            while(true)
            {
               if(i <= 4)
                  break;
               lpsz[i - 4] = L'.';
               lpsz[i - 3] = L'.';
               lpsz[i - 2] = L'.';
               lpsz[i - 1] = L'\0';
               sz = pdc->GetTextExtent(lpsz, (int32_t) i);
               if(sz.cx > rectClip.width())
               {
                  i--;
               }
               else
               {
                  break;
               }
            }
            str.ReleaseBuffer();
            iLen = str.get_length();
         }
   skip1:;
      }
      else
      {
         sz = pdc->GetTextExtent(str, (int32_t) iLen);
         /*::GetTextExtentPoint32U(
            (HDC) pdc->get_os_data(),
            str,
            iLen,
            &sz);*/
//         uint32_t dw = ::GetLastError();
         if(sz.cx > rectClip.width())
         {
            strsize i = iLen;
            if(i < 0)
               i = 0;
            char * lpsz = str.GetBuffer(max(0, i) + 1);
            while(i > 0)
            {
               sz = pdc->GetTextExtent(str, (int32_t) i);
               if(sz.cx > rectClip.width())
               {
                  i--;
                  if(i <= 0)
                     break;
               }
               else
               {
                  break;
               }
            }
            lpsz[i] = L'\0';
            str.ReleaseBuffer();
         }
      }

      if(str.is_empty())
         return 0;


      ::ca::font_sp fontUnderline;
//      ::ca::font * pfont;


      if(iUnderline >= 0)
      {
         if(pfontUnderline == NULL)
         {
            fontUnderline.create(get_app());
            pfontUnderline = fontUnderline;
            fontUnderline ->operator=(pdc->GetCurrentFont());
            fontUnderline->set_bold();
         }
      }

      rect rect;
      rect.left = 0;
      rect.top = 0;
      rect.right = sz.cx;
      rect.bottom = sz.cy;

      int32_t align = 0;
      if(uiFormat & DT_BOTTOM)
      {
         align |= ::ca::AlignBottom;
      }
      else if(uiFormat & DT_VCENTER)
      {
         align |= ::ca::AlignVerticalCenter;
      }
      else
      {
         align |= ::ca::AlignTop;
      }
      if(uiFormat & DT_RIGHT)
      {
         align |= ::ca::AlignRight;
      }
      else if(uiFormat & DT_CENTER)
      {
         align |= ::ca::AlignHorizontalCenter;
      }
      else
      {
         align |= ::ca::AlignLeft;
      }

      rect.Align(align, lpcrect);

      if(iUnderline >= 0 && iUnderline < str.get_length())
      {

         ::ca::font * pfontOld;

         pdc->TextOut(rect.left, rect.top, str, (int32_t) min(iUnderline, str.get_length()));
         /*::TextOutU(
            (HDC)pdc->get_os_data(),
            rect.left,
            rect.top,
            str,
            min(iUnderline, str.get_length()));*/
         if(iUnderline <= str.get_length())
         {
            ::ca::font fPrevious = pdc->GetCurrentFont();
            pfontOld = pdc->SelectObject(pfontUnderline);
            /*::GetTextExtentPoint32U(
               (HDC)pdc->get_os_data(),
               str,
               iUnderline,
               &sz);*/
            sz = pdc->GetTextExtent(str, (int32_t) iUnderline);
            char wch = str[iUnderline];
            /*::TextOutU(
               (HDC)pdc->get_os_data(),
               rect.left + sz.cx,
               rect.top,
               &wch,
               1);*/
            pdc->TextOut(rect.left + sz.cx, rect.top, &wch, 1);
            pdc->SelectObject(&fPrevious);
            if(iUnderline + 1 <= str.get_length())
            {
               sz = pdc->GetTextExtent(str, (int32_t) (iUnderline + 1));
               /*::GetTextExtentPoint32U(
                  (HDC)pdc->get_os_data(),
                  str,
                  iUnderline + 1,
                  &sz);*/
               strsize iCount = str.get_length() - iUnderline - 1;
               pdc->TextOut(rect.left + sz.cx, rect.top, str.Right(iCount), (int32_t) iCount);
               /*::TextOutU(
                  (HDC)pdc->get_os_data(),
                  rect.left + sz.cx,
                  rect.top,
                  str.Right(iCount),
                  iCount);*/
            }
            pdc->SelectObject(pfontOld);
         }
      }
      else
      {
         pdc->TextOut(rect.left, rect.top, str);
         /*::TextOutU(
            (HDC)pdc->get_os_data(),
            rect.left,
            rect.top,
            str,
            iLen);*/
      }
      if(str2.get_length() > 0)
      {
         rectClip.top += sz.cy;
         _DrawText(pdc, str2, rectClip, uiFormat);
      }
      return 1;
   }


} // namespace visual


