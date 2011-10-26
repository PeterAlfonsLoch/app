#pragma once

class CLASS_DECL_CA2_TESSERACT devedgeFrontThread : 
   public ::radix::thread
{
public:
   // // DECLARE_DYNCREATE(devedgeFrontThread);
   devedgeFrontThread(::ca::application * papp);
   virtual ~devedgeFrontThread();

   HANDLE m_hChildThreadId;
   PROCESS_INFORMATION m_pi;

   ::event m_evInitialized;
   bool m_bInitialized;
   devedgeFrontThread * m_pnext;

   void install_message_handling(::user::win::message::dispatch * pinterface);

   virtual bool initialize_instance();
   DECL_GEN_SIGNAL(OnApp)

   ();

};
