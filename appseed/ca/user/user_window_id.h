#pragma once


class CLASS_DECL_ca window_id
{
public:

   window_id(const oswindow_ & hwnd);

   oswindow_ m_hwnd;

   operator oswindow_();
};


inline window_id::window_id(const oswindow_ & hwnd)
{
   m_hwnd = hwnd;
}


inline window_id::operator oswindow_()
{
   return m_hwnd;
}



