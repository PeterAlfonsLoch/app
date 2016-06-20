#include <android/log.h>
#include <android/bitmap.h>

// fazer o que, por enquanto global....
::android::view_bitmap * g_pandroidbitmapview = NULL;

//#include "framework.h"
//#include "windows_window_gdi.h"
namespace android
{



   view_bitmap::view_bitmap(::aura::application * papp) :
      object(papp),
      window_graphics(papp),
      m_spdibBuffer(allocer()),
      m_mutex(papp)
   {

      ::g_pandroidbitmapview = this;

   }


   view_bitmap::~view_bitmap()
   {

   }


   void view_bitmap::create_window_graphics(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStrideParam)
   {

      synch_lock sl(&m_mutex);

      m_spdibBuffer->create(cxParam, cyParam);

      window_graphics::create_window_graphics(interaction_impl, cxParam, cyParam, m_dib->m_iScan);

   }




   void view_bitmap::destroy_window_graphics()
   {

      m_spdibBuffer->destroy();

      window_graphics::destroy_window_graphics();


   }


   void view_bitmap::update_window(COLORREF * pcolorref, const RECT & rect, int cxParam, int cyParam, int iStride, bool bTransferBuffer)
   {

      if (width(rect) <= 0 || height(rect) <= 0)
         return;

      synch_lock sl(&m_mutex);

      ::draw2d::copy_colorref(
         MIN(cxParam, m_spdibBuffer->m_size.cx),
         MIN(cyParam, m_spdibBuffer->m_size.cy), 
         m_spdibBuffer->m_pcolorref,
         m_spdibBuffer->m_iScan, pcolorref, iStride);

   }


} // namespace android


extern "C"
void android_fill_plasma(AndroidBitmapInfo * info, void * pixels, double  t)
{

   if (g_pandroidbitmapview == NULL)
   {
      
      return;

   }

   synch_lock sl(&g_pandroidbitmapview->m_mutex);

   ::draw2d::copy_colorref(
      MIN(g_pandroidbitmapview->m_spdibBuffer->m_size.cx, info->width),
      MIN(g_pandroidbitmapview->m_spdibBuffer->m_size.cy, info->height),
      (COLORREF *) pixels, 
      info->stride, 
      g_pandroidbitmapview->m_spdibBuffer->m_pcolorref,
      g_pandroidbitmapview->m_spdibBuffer->m_iScan);
   


}



