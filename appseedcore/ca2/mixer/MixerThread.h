#pragma once

// part of veriwell Musical Studio

class CMessageFilterMainHook;  

class db_server;

class CLASS_DECL_ca CMixerThread :
   public ::radix::thread,
   public ::database::client
{
public:
   CMixerThread(::ca::application * papp);

   enum e_message
   {
      MessageMixerThread = WM_USER + 113,
   };

   bool               m_bPendingShowCommand;

   MixerCentral * m_pcentral;
   virtual ::ca::application * get_app() const;

   static LRESULT CALLBACK MessageProc(
        int code,       // hook code
        WPARAM wParam,  // undefined
        LPARAM lParam   // address of structure with message data
        );


   void install_message_handling(::user::win::message::dispatch * pinterface);

   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual BOOL on_idle(LONG lCount);
   virtual void pre_translate_message(gen::signal_object * pobj);

   virtual ~CMixerThread();

    DECL_GEN_SIGNAL(OnMixerMessage)
    DECL_GEN_SIGNAL(OnVmsmException)
    DECL_GEN_SIGNAL(OnUserMessage)
};



