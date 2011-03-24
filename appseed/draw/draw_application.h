#pragma once

class CLASS_DECL_CA2_HTMLAPPLICATION html_application :
   virtual public filemanager::application_interface,
   virtual public ca36::application_interface
{
public:
	DECLARE_DYNAMIC(html_application)
   html_application(void);
   virtual ~html_application(void);

   SingleDocTemplate * m_ptemplate_html;

   BOOL InitInstance();
   BOOL ExitInstance();

   void bergedge_start();

   void _001OnFileNew();

   Ex1FactoryImpl * Ex1AppGetFactoryImpl();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		CAFX_CMDHANDLERINFO* pHandlerInfo);

   virtual bergedge_app * get_app();
   void OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema);

};
