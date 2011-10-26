#pragma once

namespace md5
{

   class CLASS_DECL_CA2_MD5 application :
      virtual public cube::application
   {
   public:


      ::userbase::single_document_template *       m_ptemplatePaneView;
      ::userbase::single_document_template *       m_ptemplateMd5;


      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);


   };

   inline CLASS_DECL_CA2_MD5 application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace md5