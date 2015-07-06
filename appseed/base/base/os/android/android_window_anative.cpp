#include "framework.h"
#include "android.h"
#include "android_window_anative.h"



window_android_anative::window_android_anative()
{

   //m_cairoSource = NULL;
   //m_cairosurfaceSource = NULL;

}


window_android_anative::~window_android_anative()
{

}


void window_android_anative::create_window_graphics(oswindow interaction_impl,int64_t cxParam,int64_t cyParam,int iStrideParam)
{



   destroy_window_graphics();



   synch_lock sl(&user_mutex());

   int w;

   int h;

   w = ANativeWindow_getWidth(interaction_impl->m_engine.app->window);

   h = ANativeWindow_getHeight(interaction_impl->m_engine.app->window);

   ANativeWindow_setBuffersGeometry(interaction_impl->m_engine.app->window, w, h, WINDOW_FORMAT_RGBA_8888);


   ::window_graphics::create_window_graphics(interaction_impl, cxParam, cyParam, w * 4);

}





void window_android_anative::destroy_window_graphics()
{

   ::window_graphics::destroy_window_graphics();


}


void window_android_anative::update_window(oswindow interaction_impl, COLORREF * pOsBitmapData, const RECT & rect, int iStride)
{

   ANativeWindow_Buffer buffer;

   ARect r;

   r.left = rect.left;
   r.top = rect.top;
   r.right = rect.right;
   r.bottom = rect.bottom;

   ZERO(buffer);

   ANativeWindow_lock(interaction_impl->m_engine.app->window, &buffer, &r);

   /**
   * Unlock the window's drawing surface after previously locking it,
   * posting the new buffer to the display.
   */


   ::draw2d::copy_colorref(width(rect), height(rect), (COLORREF *)buffer.bits, width(rect) * sizeof(COLORREF),  pOsBitmapData, iStride);

   ANativeWindow_unlockAndPost(interaction_impl->m_engine.app->window);

}



