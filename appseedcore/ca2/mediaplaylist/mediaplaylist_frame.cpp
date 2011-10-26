#include "StdAfx.h"


namespace mediaplaylist
{


   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      m_toolbar(papp)
   {
      m_etranslucency = TranslucencyTotal;
   }

   frame::~frame()
   {
   }

   void frame::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate); 
   }

 
   void frame::_001OnCreate(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      if(m_toolbar.CreateEx(this))
      {
         string str = Application.file().as_string(Application.dir().matter("mplite\\playlist_toolbar.xml"));
         m_toolbar.LoadXmlToolBar(str);
      }
   }

   ::view * frame::GetParentLyricView()
   {
      ::user::interaction * pParentWnd = GetParent();
      if(pParentWnd != NULL && base < ::view >::bases(pParentWnd))
         return dynamic_cast < ::view * > (pParentWnd);
      return NULL;
   }


} // namespace mediaplaylist

