#include "StdAfx.h"
#include "winshelllink\winshelllink_frame.h"


winshelllink_application::winshelllink_application()
{
   m_strAppName = _strdup("winshelllink");
   m_strBaseSupportId = "votagus_ca2_winshelllink";
}

winshelllink_application::~winshelllink_application(void)
{
}

bool winshelllink_application::initialize_instance()
{
   ::CreateMutex(NULL, TRUE, "ca2_fontopus_votagus_winshelllink_application");
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
      return false;



//	window_frame::FrameSchema::ButtonIdSpace idspace;
/*	SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
	SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);*/

   if(!ca84::application::initialize_instance())
      return false;

   GetStdFileManagerTemplate()->m_strLevelUp = "1000";


   gen::command_line cmdInfo;
   _001ParseCommandLine(cmdInfo);

   SetRegistryKey("ca2core");

	::userbase::single_document_template* pDocTemplate;
	pDocTemplate = new ::userbase::single_document_template(
      this,
		"system/form",
		&typeid(winshelllink_document),
		&typeid(winshelllink_frame),
		&typeid(userex::pane_view));
   userbase::application::add_document_template(pDocTemplate);
   m_ptemplate_html = pDocTemplate;


   win::registry::Key key(HKEY_CLASSES_ROOT, ".link", true);
   key.SetValue(NULL, "ca2link");

   win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "ca2link\\shell", true);
   keyLink3.SetValue(NULL, "open");

   win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "ca2link\\shell\\open", true);
   keyLink2.SetValue(NULL, "&Abrir");

   win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "ca2link\\shell\\open\\command", true);

   string strFormat;
   strFormat.Format("\"%s\" \"%%L\" : usehostlogin", m_strModulePath);
   keyLink1.SetValue(NULL, strFormat);



   gen::command_line cmdinfo;
   _001ParseCommandLine(cmdinfo);

   

   //InitializeDataCentral(cmdinfo);

   CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);


   string str = Application.file().as_string(cmdinfo.m_varFile);

   //Application.simple_message_box(str);

   xml::node node(get_app());
   node.load(str);
   if(node.m_strName == "link")
   {
      if(node.attr("location").has_char())
      {
         string strLocation = node.attr("location");
         string strParameters = node.attr("parameters");
         string strDirectory = node.attr("directory");
         ::ShellExecute(NULL, NULL, 
            strLocation, 
            strParameters.is_empty() ? (const char *) NULL : strParameters,
            strDirectory.is_empty() ?  (const char *) NULL : strDirectory,
            SW_SHOWNORMAL);
      }
   }
   if(node.m_strName == "service")
   {
      if(node.attr("name").has_char())
      {
         string strName = node.attr("name");
         if(node.attr("control").has_char())
         {
            string strControl = node.attr("control");
            if(strControl == "start")
            {
               System.service().start(strName);
            }
            else if(strControl == "stop")
            {
               System.service().stop(strName);
            }
         }
      }
   }



   return false;
}

int winshelllink_application::exit_instance()
{
   return 0;
}

bool winshelllink_application::bergedge_start()
{
   return true;
}

void winshelllink_application::_001OnFileNew()
{
   userbase::application::m_pdocmanager->_001OnFileNew();
}


bool winshelllink_application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
		
{
   return gen::application::_001OnCmdMsg(pcmdmsg);
}



CLASS_DECL_CA2_WINSHELLLINK ::ca::application * get_new_app()
{
   return new winshelllink_application;
}


::ca::application * winshelllink_application::get_app() const
{
   return m_papp;
}

void winshelllink_application::OnFileManagerOpenFile(
      ::filemanager::data * pdata, 
      ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(pdata);
   if(itema.get_size() > 0)
   {
      ::ShellExecuteW(
         NULL, 
         L"open", 
         gen::international::utf8_to_unicode(itema[0].m_strPath),
         NULL,
         gen::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)),
         SW_SHOW);
   }
   
}


