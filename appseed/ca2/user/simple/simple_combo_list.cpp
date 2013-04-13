#include "framework.h"


simple_combo_list::simple_combo_list(sp(::ca::application) papp) :
   ca(papp)
{

}

simple_combo_list::~simple_combo_list()
{
}


void simple_combo_list::install_message_handling(::ca::message::dispatch * pdispatch)
{

   ::user::combo_list::install_message_handling(pdispatch);

}


void simple_combo_list::_001OnDraw(::ca::graphics * pdc)
{

   ::user::combo_list::_001OnDraw(pdc);
   
}
