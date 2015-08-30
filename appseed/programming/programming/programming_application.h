#pragma once


namespace programming
{


   class CLASS_DECL_PROGRAMMING application:
      virtual public ::core::application
   {
   public:



      semaphore                                 m_semCompiler;

      //      script_manager *                            m_pmanager;


      application();
      virtual ~application();


      DECL_GEN_SIGNAL(on_application_signal);


   };


} // namespace html





