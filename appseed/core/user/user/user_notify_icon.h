#pragma once


#ifdef LINUX
#include "basecore/basecore.h"
#elif defined (__APPLE__)
#include "user_notify_icon_mm_bridge.h"
#endif


namespace user
{


   class notify_icon_listener;


   class CLASS_DECL_CORE notify_icon :
   #ifdef WINDOWSEX
      virtual public ::user::interaction
      #else
      virtual public ::object
      #endif
      #ifdef LINUX
      , public i_close_quit
      #elif defined (MACOS)
      , public user_notify_icon_mm_bridge
      #endif
   {
   public:


      enum e_message
      {
         MessageNotifyIcon = WM_USER + 100,
      };


      UINT     m_uiId;
      bool     m_bCreated;
      string   m_strId;
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

      #ifdef WINDOWSEX
      using ::user::interaction::create;
      #endif
      bool create(UINT id, notify_icon_listener * plistener, sp(::visual::icon) picon);

      DECL_GEN_SIGNAL(_001OnNotifyIconMessage);

      void install_message_handling(::message::dispatch * pinterface);

      virtual void __close();
      virtual void __quit();
      virtual bool __close_is_closed();
      virtual void notify_icon_play(const char * action);
      virtual bool notify_icon_frame_is_opened();

   };


} // namespace user


