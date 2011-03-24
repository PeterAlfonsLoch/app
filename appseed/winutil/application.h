#pragma once

namespace winutil
{

   class CLASS_DECL_CA2_WINUTIL application :
      public ::cube::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;


      application(void);
      virtual ~application(void);

      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   		

      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };

} // namespace winutil