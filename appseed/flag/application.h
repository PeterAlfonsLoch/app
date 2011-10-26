#pragma once

namespace flag
{

   class CLASS_DECL_CA2_FLAG application :
      public ::cube::application
   {
   public:
      
      
      ::userbase::single_document_template *  m_ptemplate_html;


      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);


   };

   inline CLASS_DECL_CA2_FLAG application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace flag
