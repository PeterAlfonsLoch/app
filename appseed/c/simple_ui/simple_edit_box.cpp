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



char to_upper(int ch)
{
   if(ch >= 'a' && ch <= 'z')
   {
      ch = ch - 'a' + 'A';
   }
   return ch;
}


char * to_upper(char * pchParam)
{
   char * pch = pchParam;
   while(*pch == '\0')
   {
      *pch = to_upper(*pch);
      pch++;
   }
   return pchParam;
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
