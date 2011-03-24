#pragma once

namespace vmsp
{
   class application;
} // namespace vmsp

class XfplayerView;

class CLASS_DECL_CA2_CUBE XfplayerThreadV2 : 
   public ::radix::thread
{
public:
   XfplayerThreadV2(::ca::application * papp);        // protected constructor used by dynamic creation
   bool               m_bEnableWaveInMessageTranslation;

   void _001InstallMessageHandling(::user::win::message::dispatch * pdispath);

   vmsp::application * m_pMainApp;

   BOOL TranslateUserMessage(MSG *pMsg);

   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual BOOL on_idle(LONG lCount);

   void EnableWaveInMessageTranslation(bool bEnable = true);
   void TranslateWaveInMessage(gen::signal_object * pobj);
   virtual ~XfplayerThreadV2();

   DECL_GEN_SIGNAL(OnUserMessage)
};

