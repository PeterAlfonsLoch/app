#pragma once


namespace whiteboard
{

   class CLASS_DECL_CA2_CUBE http_window : 
      public ::user::interaction
   {
   public:


      ::radix::thread * m_pthread;


      http_window(::ca::application * papp);
      virtual ~http_window();


      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      using ::user::interaction::create;
      BOOL create(::radix::thread * pthread);

      DECL_GEN_SIGNAL(_001OnTimer)
   };


} // namespace whiteboard