#pragma once


namespace turboc
{


   class CLASS_DECL_sphere application:
      virtual public ::sphere::application
   {
   public:


      prompt & console_prompt() { *m_spprompt; }


   };


} // namespace userstack



