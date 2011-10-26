#pragma once

namespace alatel
{

   class CLASS_DECL_CA2_ALARM application :
      virtual public cube::application
   {
   public:


      ::userbase::single_document_template *       m_ptemplateAlarm;
      ::userbase::multiple_document_template *     m_ptemplateAlatel;
      ::userbase::single_document_template *       m_ptemplateAlatelByWeekday;


      application(void);
      virtual ~application(void);


      bool initialize_instance();
      int exit_instance();

      void on_request(::ca::create_context * pcreatecontext);

   };

   inline CLASS_DECL_CA2_ALARM application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace alatel