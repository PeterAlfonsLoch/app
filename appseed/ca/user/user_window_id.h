#pragma once


class CLASS_DECL_ca window_id
{
public:

   window_id(const oswindow & oswindow);

   oswindow m_oswindow;

   operator oswindow();
};


inline window_id::window_id(const oswindow & oswindow)
{
   m_oswindow = oswindow;
}


inline window_id::operator oswindow()
{
   return m_oswindow;
}



