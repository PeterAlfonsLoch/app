#pragma once


class CLASS_DECL_BASE window_android_anative :
   public window_graphics
{
public:


   window_android_anative();
   virtual ~window_android_anative();


   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window(oswindow interaction_impl, COLORREF * pOsBitmapData, const RECT & rect, int iStride = -1);

};
