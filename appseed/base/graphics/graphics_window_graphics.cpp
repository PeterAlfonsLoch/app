#include "framework.h"
//#include "fiasco_finder.h"


#ifdef WINDOWSEX
#include "base/os/windows/windows_window_gdi.h"
#elif defined (LINUX)
#include "base/os/linux/linux_window_xlib.h"
#elif defined (VSNORD)
#include "base/os/android/android_window_anative.h"
#elif defined (ANDROID)
#include "base/os/android/android_window_android.h"
#endif


window_graphics::window_graphics(::aura::application * papp) :
   object(papp)
{

   cx = 0;
   cy = 0;

}


window_graphics::~window_graphics()
{

   destroy_window_graphics();

}


void window_graphics::on_create_window(oswindow wnd)
{

}


void window_graphics::create_window_graphics(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStride)
{

   cx = (int32_t)cxParam;
   cy = (int32_t)cyParam;
   scan = (int32_t)iStride;

}


void window_graphics::destroy_window_graphics()
{

   cx = 0;
   cy = 0;

}


void window_graphics::update_window(oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride,bool bTransferBuffer)
{


//   window_graphics * & pdata = *ppdata;
//
//
   //if(pdata == NULL || ((pdata->cx != cxParam || pdata->cy != cyParam)))
   if (cx != cxParam || cy != cyParam)
   {

//      if (pdata == NULL)
//      {
//
//#ifdef WINDOWSEX
//
//         pdata = new window_gdi();
//
//#elif defined(LINUX)
//
//         pdata = new window_xlib();
//
//#elif defined(VSNORD)
//
//         //pdata = new window_android_anative();
//         pdata = new ::android::view_bitmap(interaction_impl->m_pui->get_app());
//
//#elif defined(ANDROID)
//
//         pdata = new window_android();
//
//#endif
//
//      }

      //if (pdata != NULL)
      {

        // pdata->create_window_graphics(interaction_impl, cxParam, cyParam, iStride);
         create_window_graphics(interaction_impl, cxParam, cyParam, iStride);

      }

   }


   //if (pdata != NULL)
   {

      //pdata->update_window(pOsBitmapData, rect, cxParam, cyParam, iStride, bTransferBuffer);

      update_window(pOsBitmapData, rect, cxParam, cyParam, iStride, bTransferBuffer);

   }

}


void window_graphics::update_window(COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride,bool bTransferBuffer)
{

   UNREFERENCED_PARAMETER(pOsBitmapData);
   UNREFERENCED_PARAMETER(rect);
   UNREFERENCED_PARAMETER(iStride);
   UNREFERENCED_PARAMETER(cxParam);
   UNREFERENCED_PARAMETER(cyParam);

}


