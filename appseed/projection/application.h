#pragma once

namespace projection
{

   class CLASS_DECL_CA2_PROJECTION application :
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

   inline CLASS_DECL_CA2_PROJECTION application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace projection
