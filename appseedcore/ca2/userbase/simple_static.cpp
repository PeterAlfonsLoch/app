#include "StdAfx.h"


simple_static::simple_static(::ca::application * papp) :
   ca(papp),
   ::userbase::base_static(papp),
   m_brushBkg(papp)
{
   m_pimagelist = NULL;
   m_bTransparent = false;
   m_brushBkg->CreateStockObject(NULL_BRUSH);
}

simple_static::~simple_static()
{
}

void simple_static::_001OnDraw(::ca::graphics *pdc)
{
   if(GetStyle() & SS_ICON)
   {
      HICON hicon = GetIcon();
      if(hicon != NULL)
      {
         if(m_pimagelist == NULL)
         {
            m_pimagelist = new image_list(get_app());
            rect rect;
            GetClientRect(rect);
            m_pimagelist->create(
               rect.width(),
               rect.height(),
               0,
               0, 0);
            m_pimagelist->add_icon_os_data(hicon);
         }
         m_pimagelist->draw(pdc, 0, point(0, 0), 0);
      }
   }
}

void simple_static::pre_subclass_window() 
{
   PreSubClassWindow();   
   
   ::userbase::base_static::pre_subclass_window();
}

LRESULT simple_static::OnSetIcon(WPARAM wparam, LPARAM lparam)
{
   if(m_pimagelist != NULL)
   {
      delete m_pimagelist;
   }
   return DefWindowProc(WM_SETICON, wparam, lparam);
}