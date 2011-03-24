#pragma once

class MixerVisualCentral;

class CLASS_DECL_ca MixerVisualThread : 
   public ::radix::thread
{
public:

   class CInitialize
   {
   public:
      MixerVisualCentral * m_pvisualcentral;
   };

   enum e_message
   {
      MessageMain = WM_USER + 113,
   };

   enum EMessageMainWparam
   {
      MessageMainWparamInitialize,
      MessageMainWparamDisplayAMixer,
      
   };

public:
   MixerVisualThread(::ca::application * papp);


   CEvent                  m_event;
   MixerVisualCentral      *  m_pvisualcentral;

   MixerVisualCentral & GetVisualCentral();
   bool Initialize(MixerVisualCentral * pvisualcentral);

   virtual bool initialize_instance();
   virtual int exit_instance();

   void OnInitialize(CInitialize * pinitialize);
   virtual ~MixerVisualThread();

   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(OnMixerVisualMessage)
};
