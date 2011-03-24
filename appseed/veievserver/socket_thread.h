#pragma once

namespace veievserver
{

   class socket;
   class service;

   class CLASS_DECL_VEIEVSERVER socket_thread : 
      public ::radix::thread
   {
   public:
	   socket_thread(::ca::application * papp);
	   ~socket_thread(void);

	   HANDLE m_hChildThreadId;
	   PROCESS_INFORMATION m_pi;
      service * m_pservice;

      string   m_strIp;
      int      m_iPort;

      ::CEvent m_evCanInit;
	   ::CEvent m_evInitialized;
	   bool m_bInitialized;

      socket *    m_psocket;

	   virtual bool initialize_instance();
	   DECL_GEN_SIGNAL(OnApp)

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   };

} // namespace veievserver