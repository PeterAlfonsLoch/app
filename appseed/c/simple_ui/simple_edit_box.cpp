#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_edit_box::simple_edit_box()
{

   m_iPos = 0;

}

simple_edit_box::~simple_edit_box()
{
}







void simple_edit_box::on_lbutton_down(int x, int y)
{

   set_focus(this);

}

void simple_edit_box::on_lbutton_up(int x, int y)
{
}



bool simple_edit_box::is_focusable()
{

   return true;

}
