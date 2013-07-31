#include "framework.h"


simple_static::simple_static(sp(::ca2::application) papp) :
   ca2(papp),
   
   ::user::static_control(papp),
   m_brushBkg(allocer())
{
   m_pimagelist = NULL;
   m_bTransparent = false;
   m_brushBkg->CreateStockObject(NULL_BRUSH);
}

simple_static::~simple_static()
{
}

void simple_static::_001OnDraw(::draw2d::graphics *pdc)
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

   ::user::static_control::pre_subclass_window();
}

LRESULT simple_static::OnSetIcon(WPARAM wparam, LPARAM lparam)
{
   if(m_pimagelist != NULL)
   {
      m_pimagelist.release();
   }
   return DefWindowProc(WM_SETICON, wparam, lparam);
}
