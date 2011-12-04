#pragma once

class CLASS_DECL_ca2 window_id
{
public:

   window_id(const HWND & hwnd);

   HWND m_hwnd;

   operator HWND();
};

inline window_id::window_id(const HWND & hwnd)
{
   m_hwnd = hwnd;
}

inline window_id::operator HWND()
{
   return m_hwnd;
}
