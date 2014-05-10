#include "framework.h"


namespace visual
{



   graphics_extension::graphics_extension(sp(::base::application) papp) :
      element(papp)
   {

   }

   graphics_extension::~graphics_extension()
   {

   }

   bool graphics_extension::TextOut(::draw2d::graphics * pdc, int32_t x, int32_t y, const char * lpcsz, strsize iCount)
   {
      return pdc->TextOut(x, y, string(lpcsz, iCount));
      //return ::TextOutU((HDC)pdc->get_os_data(), x, y, lpcsz, iCount);
   }



   void graphics_extension::GetTextExtent(::draw2d::graphics *pdc, const char * lpcsz, array < size > & sizea)
   {
      string str(lpcsz);
      strsize iLen = str.get_length();
      sizea.allocate(iLen);
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

   void graphics_extension::GetTextExtent(::draw2d::graphics *pdc, const char * lpsz, size & size)
   {

      synch_lock ml(&user_mutex());

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

   void graphics_extension::GetTextExtent(::draw2d::graphics *pdc, const char * lpcsz, strsize iCount, size & size)
   {
      /*::GetTextExtentPoint32U(
         (HDC)pdc->get_os_data(),
         lpcsz,
         iCount,
         &size);*/

      size = pdc->GetTextExtent(string(lpcsz, iCount));

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



