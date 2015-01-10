#pragma once




namespace turboc
{




   class CLASS_DECL_TURBOC application:
      virtual public ::sphere::application
   {
   public:


//      prompt & console_prompt() { *m_spprompt; }

      context     * m_pcontext;

      ::turboc::main        * m_pmain;

      application();
      virtual ~application();


      virtual bool initialize_instance();

      bool start_main(PFN_MAIN pfnMain);


   };


} // namespace userstack



