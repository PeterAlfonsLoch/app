#include "StdAfx.h"
#include "devedge_child_frame.h"

devedge_child_frame::devedge_child_frame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
}

void devedge_child_frame::install_message_handling(::user::win::message::dispatch * pinterface)
{
   simple_child_frame::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, this, this, &devedge_child_frame::_001OnAppLanguage);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &devedge_child_frame::_001OnCreate);
}

devedge_child_frame::~devedge_child_frame()
{
}

bool devedge_child_frame::CreateBars()
{
   DestroyBars();

   ex1::text_file_sp spfile(get_app());

   string strModuleFolder;
   strModuleFolder = System.get_module_folder();

   if(!spfile->open(Application.dir().matter("devedge\\devedge_toolbar.xml"), ::ex1::file::type_text | ::ex1::file::mode_read))
      return false;

   string str;
   spfile->read_full_string(str);

   if (!m_toolbar.CreateEx(this) ||
       !m_toolbar.LoadXmlToolBar(str))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }

   layout();

   return true;
}

bool devedge_child_frame::DestroyBars()
{

   m_toolbar.DestroyWindow();
   m_toolbar.RemoveAllTools();

   return true;
}



void devedge_child_frame::_001OnCreate(gen::signal_object * pobj) 
{
   pobj->previous();

   CreateBars();
   
}


void devedge_child_frame::_001OnAppLanguage(gen::signal_object * pobj)
{
   CreateBars();
   pobj->m_bRet = false;
}


FileManagerInterface * devedge_child_frame::GetFileManager()
{
   return dynamic_cast <FileManagerInterface *>(GetActiveDocument());
}

/*void devedge_child_frame::GetSelected(::fs::item_array &itema)
{
   filemanager::SimpleFileListInterface * plistinterface = dynamic_cast <filemanager::SimpleFileListInterface *>
      (GetActiveView());
   if(plistinterface != NULL)
   {
      plistinterface->GetSelected(itema);
   }
}*/
