#pragma once

class CLASS_DECL_CA2_WINSHELLLINK winshelllink_application :
   public ca84::application
{
public:
   
   
   ::userbase::single_document_template * m_ptemplate_html;


   winshelllink_application();
   virtual ~winshelllink_application();

   virtual bool initialize_instance();
   virtual int  exit_instance();

   virtual bool bergedge_start();

   virtual void _001OnFileNew();

	virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
		
   virtual ::ca::application * get_app() const;
   virtual void OnFileManagerOpenFile(
      ::filemanager::data * pdata, 
      ::fs::item_array & itema);

};
