#include "framework.h"


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
   if(get_type() == type_icon)
   {
      ::visual::icon * picon = get_icon();
      if(picon != NULL)
      {
         pdc->DrawIcon(null_point(), picon);
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