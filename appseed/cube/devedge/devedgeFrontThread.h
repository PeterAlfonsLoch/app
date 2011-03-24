#pragma once

class CLASS_DECL_CA2_CUBE devedgeFrontThread : 
   public ::radix::thread
{
public:
   // // DECLARE_DYNCREATE(devedgeFrontThread);
   devedgeFrontThread(::ca::application * papp);
   virtual ~devedgeFrontThread();

   HANDLE m_hChildThreadId;
   PROCESS_INFORMATION m_pi;

   ::CEvent m_evInitialized;
   bool m_bInitialized;
   devedgeFrontThread * m_pnext;

   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   virtual bool initialize_instance();
   DECL_GEN_SIGNAL(OnApp)

   ();

};
