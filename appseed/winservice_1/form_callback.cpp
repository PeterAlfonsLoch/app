#include "StdAfx.h"

namespace command
{

form_callback::form_callback()
{
}

form_callback::~form_callback()
{
}

void form_callback::OnUpdate(ex1::form_interface * pview, BaseView* pSender, LPARAM lHint, base_object* phint) 
{
}


bool form_callback::BaseOnControlEvent(ex1::form_interface * pview, BaseControlEvent * pevent)
{
   return false;
}

} // namespace command