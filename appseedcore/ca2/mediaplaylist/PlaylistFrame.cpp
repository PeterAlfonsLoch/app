#include "StdAfx.h"
#include "PlaylistFrame.h"
#include "PlaylistListView.h"

static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

PlaylistFrame::PlaylistFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp),
   m_toolbar(papp)
{
   m_etranslucency = TranslucencyTotal;
}

PlaylistFrame::~PlaylistFrame()
{
}

void PlaylistFrame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   simple_frame_window::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &PlaylistFrame::_001OnCreate); 
}

 
void PlaylistFrame::_001OnCreate(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   if(m_toolbar.CreateEx(this))
   {
      string str = Application.file().as_string(System.dir().matter("mplite\\playlist_toolbar.xml"));
      m_toolbar.LoadXmlToolBar(str);
   }
}

view * PlaylistFrame::GetParentLyricView()
{
   ::user::interaction * pParentWnd = GetParent();
   if(pParentWnd != NULL &&
      base < view >::bases(pParentWnd))
      return dynamic_cast < view * > (pParentWnd);
   return NULL;
}

