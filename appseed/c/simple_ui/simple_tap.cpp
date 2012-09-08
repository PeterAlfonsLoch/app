#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_tap::simple_tap()
{

   m_strId        = "submit";
   m_bDown        = false;
   m_bMouseMove   = false;

}


simple_tap::~simple_tap()
{
}


void simple_tap::draw_this(HDC hdc)
{

   //draw_simple(hdc);

   draw_volume(hdc);

}



void simple_tap::on_lbutton_down(int x, int y)
{

   set_focus(this);

   m_bDown = true;

}

void simple_tap::on_lbutton_up(int x, int y)
{

   if(m_bDown)
   {

      m_bDown = false;

      on_action(m_strId);

   }

}

void simple_tap::on_mouse_move(int x, int y)
{

   m_bMouseMove = true;

   //m_pplugin->redraw();

}

bool simple_tap::is_focusable()
{
   return true;
}

bool simple_tap::is_hover()
{

   RECT rectWindow = m_rect;

   ::hotplugin::plugin * pplugin = get_plugin();

   int dx = pplugin->m_phost->m_rect.left;

   int dy = pplugin->m_phost->m_rect.top;

   rectWindow.left      += dx;
   rectWindow.right     += dx;
   rectWindow.top       += dy;
   rectWindow.bottom    += dy;

   POINT ptCursor;

   ::GetCursorPos(&ptCursor);

   ptCursor.x += pplugin->m_ptCursorPhase.x;

   ptCursor.y += pplugin->m_ptCursorPhase.y;

   bool bHover = ptCursor.x >= rectWindow.left
              && ptCursor.x <= rectWindow.right
              && ptCursor.y >= rectWindow.top
              && ptCursor.y <= rectWindow.bottom;

   if(!bHover)
      m_bMouseMove = false;

   return bHover;


}
