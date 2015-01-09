#pragma once




namespace turboc
{




   class CLASS_DECL_TURBOC application:
      virtual public ::sphere::application
   {
   public:


//      prompt & console_prompt() { *m_spprompt; }

      context     * m_pcontext;

      application();
      virtual ~application();


      virtual bool initialize_instance();


   };


} // namespace userstack



