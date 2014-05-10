#pragma once


namespace simpledb
{


   class socket;
   class service;


   class CLASS_DECL_CORE socket_thread : 
      public thread,
      public ::sockets::socket_handler
   {
   public:


      HANDLE                  m_hChildThreadId;

#ifdef WINDOWSEX

      PROCESS_INFORMATION     m_pi;

#endif

      service *               m_pservice;

      string                  m_strIp;
      int32_t                     m_iPort;

      ::event                 m_evCanInit;
      ::event                 m_evInitialized;
      bool                    m_bInitialized;

#ifdef BSD_STYLE_SOCKETS

      SOCKET                  m_hsocket;

#endif

      socket *                m_psocket;


      socket_thread(sp(::base::application) papp);
      virtual ~socket_thread();


      virtual bool initialize_instance();


      void install_message_handling(::message::dispatch * pinterface);


      DECL_GEN_SIGNAL(OnApp);


   };


} // namespace simpledb


