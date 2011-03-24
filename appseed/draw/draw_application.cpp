#include "StdAfx.h"
#include "html_application.h"
#include "win\win.h"
#include "resource.h"
#include "gen/CommandLineInfo.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"
#include "wndfrm/FrameSchema.h"


	IMPLEMENT_DYNAMIC(html_application, app )

html_application::html_application(void)
{
   m_pszAppName = (char * )malloc(100);
   strcpy((char *) m_pszAppName, "NetShareClient");
}

html_application::~html_application(void)
{
}

BOOL html_application::InitInstance()
{
	window_frame::FrameSchema::ButtonIdSpace idspace;
/*	SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

   if(!app::InitInstance())
      return FALSE;

   Ex1AppInitialize();

   if(!ca36::application_interface::initialize())
      return FALSE;


   if(!FontCentral::AppGetFontCentral()->IsInitialized())
      FontCentral::AppGetFontCentral()->Initialize();

   filemanager::application_interface::Initialize(129);
   filemanager::application_interface::m_ptemplateStd->m_uiLevelUp = 1000;


   gen::CommandLineInfo cmdInfo;
   Ex1::GetApp()->_001ParseCommandLine(cmdInfo);

   SetRegistryKey("ca2core");

	SingleDocTemplate* pDocTemplate;
	pDocTemplate = new SingleDocTemplate(
      this,
		IDR_MAINFRAME,
		RUNTIME_CLASS(html_document),
		RUNTIME_CLASS(html_frame),       // main SDI frame window
		RUNTIME_CLASS(pane_view));
   guibase::AppInterface::AddDocTemplate(pDocTemplate);
   m_ptemplate_html = pDocTemplate;


   gen::CommandLineInfo cmdinfo;

   InitializeDataCentral(cmdinfo);



	if (!_001ProcessShellCommand(cmdInfo))
		return FALSE;

   return TRUE;
}

BOOL html_application::ExitInstance()
{
   return TRUE;
}

void html_application::bergedge_start()
{
   m_ptemplate_html->OpenDocumentFile(NULL);
}

Ex1FactoryImpl * html_application::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}

void html_application::_001OnFileNew()
{
   guibase::AppInterface::m_pdocmanager->OnFileNew();
}


BOOL html_application::OnCmdMsg(UINT nID, int nCode, void* pExtra,
		CAFX_CMDHANDLERINFO* pHandlerInfo)
{
   return gen::app::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



CLASS_DECL_CA2_HTMLAPPLICATION bergedge_app * get_new_app()
{
   html_application * papp = new html_application;
   papp->m_hInstance = AfxGetApp()->m_hInstance;
   return papp;
}


bergedge_app * html_application::get_app()
{
   return this;
}

void html_application::OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema)
{
   m_ptemplate_html->OpenDocumentFile(itema[0].m_strPath);
}


