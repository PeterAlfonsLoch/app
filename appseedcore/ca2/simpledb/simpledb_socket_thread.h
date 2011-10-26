#pragma once


namespace simpledb
{


   class socket;
   class service;

   class CLASS_DECL_ca socket_thread : 
      public ::radix::thread,
      public ::sockets::socket_handler
   {
   public:


      HANDLE                  m_hChildThreadId;
      PROCESS_INFORMATION     m_pi;
      service *               m_pservice;

      string                  m_strIp;
      int                     m_iPort;

      ::event                m_evCanInit;
      ::event                m_evInitialized;
      bool                    m_bInitialized;

      SOCKET                  m_hsocket;

      socket *                m_psocket;


      socket_thread(::ca::application * papp);
      virtual ~socket_thread(void);


      virtual bool initialize_instance();


      void install_message_handling(::user::win::message::dispatch * pinterface);


      DECL_GEN_SIGNAL(OnApp)


   };


} // namespace simpledb


