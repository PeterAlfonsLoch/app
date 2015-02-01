#include "framework.h"
#include "aura/graphics/graphics.h"


namespace visual
{

   cursor::cursor(::aura::application * papp) :
      element(papp),
      m_dib(allocer())
      //,m_dibWork(allocer())
   {

#ifdef WINDOWSEX

      m_hcursor = NULL;

#endif

   }


   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->BitBlt(pt - m_szHotspotOffset, m_dib->m_size, m_dib->get_graphics());

   }


#ifdef WINDOWSEX

   HCURSOR cursor::get_HCURSOR()
   {

      if(m_hcursor == NULL)
      {

         m_hcursor = ::CreateAlphaCursor(m_dib,m_szHotspotOffset.cx,m_szHotspotOffset.cy);

      }

      return m_hcursor;

   }

#endif


   void cursor_alloc(::aura::application * papp,cursor * & pdib,int xHotspot,int yHotspot)
   {

      pdib = new cursor(papp);

      pdib->m_szHotspotOffset.cx = xHotspot;
      pdib->m_szHotspotOffset.cy = yHotspot;

   }


   ::draw2d::dib * cursor_get_dib(cursor * pcursor)
   {

      return pcursor->m_dib;

   }


} // namespace visual










#ifdef WINDOWSEX


#undef new
#define min MIN
#define max MAX
#include <gdiplus.h>
#undef min
#undef max
#define new AURA_NEW

int GetEncoderClsid(const WCHAR* format,CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num,&size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num,size,pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if(wcscmp(pImageCodecInfo[j].MimeType,format) == 0)
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


#endif


