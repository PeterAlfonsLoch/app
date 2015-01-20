#pragma once


namespace console
{


   class CLASS_DECL_sphere application:
      virtual public ::userstack::application
   {
   public:


      sp(prompt) m_spprompt;


      application();
      virtual ~application();

      virtual bool initialize_instance();


      inline prompt & console_prompt() { return *m_spprompt; }


      void pre_translate_message(::signal_details * pobj);


   };


} // namespace userstack



