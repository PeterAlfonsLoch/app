#pragma once

class CLASS_DECL_CA2_SYLLOMATTERCONSOLE syllomatter_console :
   public ca33::application_interface
{
public:
	DECLARE_DYNAMIC(syllomatter_console)
   syllomatter_console(void);
   virtual ~syllomatter_console(void);

   BOOL InitInstance();
   BOOL ExitInstance();

   void bergedge_start();

   Ex1FactoryImpl * Ex1AppGetFactoryImpl();
   virtual bergedge_application * get_app();

   BOOL syllomatter_console::OnCmdMsg(UINT nID, int nCode, void* pExtra,
		CAFX_CMDHANDLERINFO* pHandlerInfo);

};
