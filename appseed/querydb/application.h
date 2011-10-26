#pragma once


namespace querydb
{


   class CLASS_DECL_CA2_QUERYDB application :
      public ::cube::application
   {
   public:
      
      
      ::userbase::single_document_template *       m_ptemplateQueryDb;
      ::userbase::single_document_template *       m_ptemplateSql;


      application(void);
      virtual ~application(void);

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual bool initialize_instance();
      virtual int  exit_instance();

   };

   inline CLASS_DECL_CA2_QUERYDB application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace querydb
