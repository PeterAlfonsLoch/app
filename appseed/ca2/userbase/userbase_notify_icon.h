#pragma once


namespace userbase
{


   class notify_icon_listener;


   class CLASS_DECL_ca notify_icon :
      virtual public ::user::interaction
   {
   public:


      enum e_message
      {
         MessageNotifyIcon = WM_USER + 100,
      };


      UINT     m_uiId;
      bool     m_bCreated;
#ifdef WINDOWS
      NOTIFYICONDATA m_nid;
#endif
      notify_icon_listener * m_plistener;


      notify_icon(::ax::application * papp);
      virtual ~notify_icon();


      bool Destroy();



      bool ModifyIcon(HICON hicon);

      using ::user::interaction::create;
      bool create(UINT id, notify_icon_listener * plistener, HICON hicon);

      DECL_GEN_SIGNAL(_001OnNotifyIconMessage)

      void install_message_handling(::gen::message::dispatch * pinterface);


   };


} // namespace userbase


