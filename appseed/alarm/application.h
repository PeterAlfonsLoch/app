#pragma once

namespace alarm
{

   class CLASS_DECL_CA2_ALARM application :
      virtual public cube::application
   {
   public:
      application(void);
      virtual ~application(void);

      ::userbase::single_document_template *    m_ptemplateAlarm;
      ::userbase::single_document_template *    m_ptemplateAlatel;
      ::userbase::single_document_template *    m_ptemplateAlatelByWeekday;

      bool initialize_instance();
      int exit_instance();

      bool bergedge_start();

      void _001OnFileNew();

	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };

   inline CLASS_DECL_CA2_ALARM application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace alarm