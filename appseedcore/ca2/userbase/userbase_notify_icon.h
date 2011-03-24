#pragma once

namespace userbase
{

   class notify_icon_listener;


   class CLASS_DECL_ca notify_icon :
      virtual public ::ca::window_sp,
      virtual public gen::signalizable
   {
   public:


      enum e_message
      {
         MessageNotifyIcon = WM_USER + 100,
      };


      UINT     m_uiId;
      bool     m_bCreated;
      NOTIFYICONDATA m_nid;
      notify_icon_listener * m_plistener;


      notify_icon(::ca::application * papp);
      virtual ~notify_icon();


      bool Destroy();



      bool ModifyIcon(HICON hicon);
      bool create(UINT uiId, notify_icon_listener * plistener, HICON hicon);

      DECL_GEN_SIGNAL(_001OnNotifyIconMessage)

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   };

} // namespace userbase
