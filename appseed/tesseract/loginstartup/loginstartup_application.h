#pragma once

class CLASS_DECL_CA2_LOGINSTARTUPAPPLICATION loginstartup_application :
   public ca84::application
{
public:
   loginstartup_application();
   virtual ~loginstartup_application();

   BaseSingleDocumentTemplate * m_ptemplate_html;

   bool initialize_instance();
   BOOL exit_instance();

   void bergedge_start();

   void _001OnFileNew();

	virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
		

   virtual ::ca::application * get_app();
   void OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema);

   BOOL login_startup();

};
