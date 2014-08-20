#pragma once


namespace user
{


   class notify_icon_listener;


   class CLASS_DECL_CORE notify_icon :
      virtual public ::user::interaction
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
#endif
      notify_icon_listener * m_plistener;


      notify_icon(sp(::axis::application) papp);
      virtual ~notify_icon();


      bool Destroy();



      bool ModifyIcon(sp(::visual::icon)  picon);

      using ::user::interaction::create;
      bool create(UINT id, notify_icon_listener * plistener, sp(::visual::icon) picon);

      DECL_GEN_SIGNAL(_001OnNotifyIconMessage);

      void install_message_handling(::message::dispatch * pinterface);


   };


} // namespace user


