#pragma once


class device_context
{
public:


   Display *      m_display;
   Drawable       m_d;
   GC             m_gc;
   oswindow       m_hwnd;


   device_context()
   {
      m_display = NULL;
      m_d = 0;
      m_gc = NULL;
      m_hwnd = NULL;
   }

};


