#pragma once


namespace mixeruserbase
{


   class central;


   class CLASS_DECL_ca thread : 
      public ::radix::thread
   {
   public:

      class initialize
      {
      public:
         central *   m_pcentral;
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

      
      event                  m_event;
      central *               m_pcentral;


      thread(::ca::application * papp);
      virtual ~thread();


      central & get_central();
      bool Initialize(central * pvisualcentral);

      virtual bool initialize_instance();
      virtual int exit_instance();

      void OnInitialize(initialize * pinitialize);

      void install_message_handling(::user::win::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(OnMixerVisualMessage)
   };

} // namespace mixeruserbase