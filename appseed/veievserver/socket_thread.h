#pragma once


namespace veievserver
{


   class socket;
   class service;


   class CLASS_DECL_VEIEVSERVER socket_thread : 
      public ::radix::thread
   {
   public:

      
	   HANDLE                  m_hChildThreadId;
	   PROCESS_INFORMATION     m_pi;
      service *               m_pservice;

      string                  m_strIp;
      int                     m_iPort;

      event                   m_evCanInit;
	   event                   m_evInitialized;
	   bool                    m_bInitialized;

      socket *                m_psocket;

      
      socket_thread(::ca::application * papp);
	   virtual ~socket_thread(void);


	   virtual bool initialize_instance();
	   DECL_GEN_SIGNAL(OnApp)

      void install_message_handling(::user::win::message::dispatch * pinterface);


   };


} // namespace veievserver


