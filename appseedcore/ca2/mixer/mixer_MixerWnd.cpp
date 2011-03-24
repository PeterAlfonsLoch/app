#include "StdAfx.h"
#include "MixerWnd.h"


MixerWnd::MixerWnd(::ca::application * papp) :
   ca(papp)
{
   create_message_window("");
}

MixerWnd::~MixerWnd()
{
}

void MixerWnd::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::user::interaction::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(MM_MIXM_CONTROL_CHANGE, pinterface, this, &MixerWnd::_001OnMixerControlChange);
   IGUI_WIN_MSG_LINK(MM_MIXM_LINE_CHANGE, pinterface, this, &MixerWnd::_001OnMixerLineChange);
}

void MixerWnd::_001OnMixerControlChange(gen::signal_object * pobj)
{
   IGUI_WIN_CST(base);
   m_pmixer->OnMixerControlChange((HMIXER) pbase->m_wparam, pbase->m_lparam);
   pbase->set_lresult(0);
}

void MixerWnd::_001OnMixerLineChange(gen::signal_object * pobj)
{
   IGUI_WIN_CST(base);
   m_pmixer->OnMixerLineChange((HMIXER) pbase->m_wparam, pbase->m_lparam);
   pbase->set_lresult(0);
}
