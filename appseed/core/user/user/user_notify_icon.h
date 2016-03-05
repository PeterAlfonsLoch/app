#pragma once


#ifdef LINUX
#include "basecore/basecore.h"
#endif // LINUX


namespace user
{


   class notify_icon_listener;


   class CLASS_DECL_CORE notify_icon :
      virtual public ::user::interaction
      #ifdef LINUX
      , public i_close_quit
      #endif
   {
   public:


      enum e_message
      {
         MessageNotifyIcon = WM_USER + 100,
      };


      UINT     m_uiId;
      bool     m_bCreated;
#ifdef WINDOWSEX
      NOTIFYICONDATA m_nid;
#elif defined(LINUX)
      void *    m_pindicator;
#endif
      notify_icon_listener * m_plistener;


      notify_icon(::aura::application * papp);
      virtual ~notify_icon();


      bool Destroy();



      bool ModifyIcon(sp(::visual::icon)  picon);

      using ::user::interaction::create;
      bool create(UINT id, notify_icon_listener * plistener, sp(::visual::icon) picon);

      DECL_GEN_SIGNAL(_001OnNotifyIconMessage);

      void install_message_handling(::message::dispatch * pinterface);

      virtual void __close();
      virtual void __quit();
      virtual bool __close_is_closed();

   };


} // namespace user


