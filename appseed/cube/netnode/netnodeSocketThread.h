#pragma once



class CLASS_DECL_CA2_CUBE netnodeSocketThread : 
   public ::radix::thread
{
public:
   netnodeSocketThread(::ca::application * papp);
   ~netnodeSocketThread(void);

   HANDLE m_hChildThreadId;
   PROCESS_INFORMATION m_pi;
   netnodeService * m_pservice;

   string   m_strIp;
   int      m_iPort;

   ::CEvent m_evCanInit;
   ::CEvent m_evInitialized;
   bool m_bInitialized;

   SOCKET m_hsocket;

   netnodeSocket *    m_psocket;

   virtual bool initialize_instance();
   DECL_GEN_SIGNAL(OnApp)

   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

};
