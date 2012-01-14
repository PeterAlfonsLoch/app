#pragma once


namespace netnode
{


   class service;
   class socket;


   class CLASS_DECL_ca socket_thread : 
      public ::radix::thread
   {
   public:


      HANDLE                  m_hChildThreadId;
      PROCESS_INFORMATION     m_pi;
      service *               m_pservice;

      string                  m_strIp;
      int                     m_iPort;

      ::event                 m_evCanInit;
      ::event                 m_evInitialized;
      bool                    m_bInitialized;

      SOCKET                  m_hsocket;

      socket *                m_psocket;
      string                  m_strCat;


      socket_thread(::ca::application * papp);
      ~socket_thread(void);


      virtual bool initialize_instance();
      DECL_GEN_SIGNAL(OnApp)


      void install_message_handling(::gen::message::dispatch * pinterface);


   };


} // namespace netnode


