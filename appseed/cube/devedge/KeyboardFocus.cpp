#include "StdAfx.h"
#include "Element2D.h"


namespace devedge
{

void KeyboardFocus::_001OnKeyboardFocusTimer(devedge_view * pview, int iTimer)
{
	
}

void KeyboardFocus::_001OnChar(devedge_view * pview, gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj)
}

void KeyboardFocus::_001OnSysChar(devedge_view * pview, gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj)
}

} // namespace devedge