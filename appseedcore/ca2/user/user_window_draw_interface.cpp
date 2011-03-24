#include "StdAfx.h"


window_draw_interface::window_draw_interface()
{

}

window_draw_interface::~window_draw_interface()
{

}

void window_draw_interface::_001OnNcDraw(::ca::graphics *pdc)
{
   user::signal::cdc cdc(&m_signalOnNcDraw);
   cdc.m_pdc = pdc;
   m_signalOnNcDraw.emit(&cdc);
}

void window_draw_interface::_001OnDraw(::ca::graphics *pdc)
{
   user::signal::cdc cdc(&m_signalOnDraw);
   cdc.m_pdc = pdc;
   m_signalOnDraw.emit(&cdc);
}
