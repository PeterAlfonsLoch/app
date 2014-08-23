#include "framework.h"


simple_static::simple_static(sp(::aura::application) papp) :
   element(papp),
   
   ::user::static_control(papp),
   m_brushBkg(allocer())
{
   m_pimagelist = NULL;
   m_bTransparent = false;
   m_brushBkg->m_etype = ::draw2d::brush::type_null;
   m_brushBkg->m_bUpdated = false;
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
   else if(get_type() == type_text)
   {

      select_font(pdc);

      ::draw2d::brush_sp brush(allocer(), Application.userex()->GetUfeSchema()->m_crTextNormal);

      pdc->SelectObject(brush);

      string str;

      GetWindowText(str);

      pdc->TextOut(0, 0, str);

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
