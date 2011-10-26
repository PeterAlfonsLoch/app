#include "StdAfx.h"
#include "loginstartup_application.h"
#include "loginstartup\loginstartup_frame.h"
#include "resource.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

loginstartup_application::loginstartup_application()
{
   m_strAppName         = "loginstartup";
   m_strBaseSupportId   = "votagus_ca2_loginstartup";

}

loginstartup_application::~loginstartup_application(void)
{
}

bool loginstartup_application::initialize_instance()
{
   factory().set < loginstartup::pane_view >();
   factory().set < loginstartup_view >();
   factory().set < loginstartup_document >();
   factory().set < loginstartup_frame >();
   ::CreateMutex(NULL, TRUE, "ca2_fontopus_votagus_loginstartup_application");
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
      return false;


   set_locale("pt-br");
   set_style("pt-br");

   if(!ca84::application::initialize_instance())
      return false;



//	window_frame::FrameSchema::ButtonIdSpace idspace;
/*	SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

   GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

   gen::CommandLineInfo cmdinfo;
   _001ParseCommandLine(cmdinfo);

   SetRegistryKey("ca2core");

	BaseSingleDocumentTemplate* pDocTemplate;
	pDocTemplate = new BaseSingleDocumentTemplate(
      this,
		"system/form",
		&typeid(loginstartup_document),
		&typeid(loginstartup_frame),
		&typeid(pane_view));
   guibase::application::AddDocTemplate(pDocTemplate);
   m_ptemplate_html = pDocTemplate;

   if(cmdinfo.m_propertysetParameters.has_property("loginstartup"))
   {
      return login_startup();
   }

   m_ptemplate_html->OpenDocumentFile(NULL, TRUE);

   return true;
}

BOOL loginstartup_application::exit_instance()
{
   return TRUE;
}

void loginstartup_application::bergedge_start()
{
   m_ptemplate_html->OpenDocumentFile(NULL);
}

void loginstartup_application::_001OnFileNew()
{
   guibase::application::m_pdocmanager->OnFileNew();
}


bool loginstartup_application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
		
{
   return gen::application::_001OnCmdMsg(pcmdmsg);
}



CLASS_DECL_CA2_LOGINSTARTUPAPPLICATION ::ca::application * get_new_app()
{
   loginstartup_application * papp = new loginstartup_application;
   papp->m_hInstance = Application.m_hInstance;
   return papp;
}


::ca::application * loginstartup_application::get_app()
{
   return this;
}

void loginstartup_application::OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema)
{
   if(itema.get_size() > 0)
   {
      ::ShellExecuteW(
         NULL, 
         L"open", 
         gen::international::utf8_to_unicode(itema[0].m_strPath),
         NULL,
         gen::international::utf8_to_unicode(dir().name(itema[0].m_strPath)),
         SW_SHOW);
   }
   
}


BOOL loginstartup_application::login_startup()
{
   string strLoginStartupRun;

   strLoginStartupRun = Application.dir().appdata("loginstartup\\run");

   AStrArray stra;

   Application.dir().ls(strLoginStartupRun, &stra);


   for(int i = 0; i < stra.get_size(); i++)
   {
      string strPath = stra[i];
      ::ShellExecute(NULL, NULL, strPath, NULL, strLoginStartupRun, SW_SHOW);
      Sleep(1984);
   }

   Sleep(30000);

   return FALSE;
}
