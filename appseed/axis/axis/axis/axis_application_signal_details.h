#pragma once



namespace base

{


   enum e_application_signal
   {

      application_signal_initialize1, // first initialization
      application_signal_initialize2, // second initialization
      application_signal_initialize3, // third initialization and so on...
      application_signal_initialize, // last initialization
      application_signal_start,
      application_signal_process_initialize,
      application_signal_finalize,
      application_signal_exit_instance,
      application_signal_init_application,
      application_signal_none

   };

   class CLASS_DECL_AXIS application_signal_details:
      public signal_details
   {
   public:


      e_application_signal             m_esignal;
      int32_t                          m_iRet;
      bool                             m_bOk;


      application_signal_details(sp(application) papp,class ::signal * psignal,e_application_signal esignal);


   };


} // namespace base