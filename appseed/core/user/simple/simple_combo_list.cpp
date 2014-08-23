#include "framework.h"


simple_combo_list::simple_combo_list(sp(::aura::application) papp) :
   element(papp)
{

}

simple_combo_list::~simple_combo_list()
{
}


void simple_combo_list::install_message_handling(::message::dispatch * pdispatch)
{

   ::user::combo_list::install_message_handling(pdispatch);

}


void simple_combo_list::_001OnDraw(::draw2d::graphics * pdc)
{

   ::user::combo_list::_001OnDraw(pdc);

}
