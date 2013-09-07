#include "framework.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListInterface.h"


FileManagerChildFrame::FileManagerChildFrame(sp(base_application) papp) :
   element(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
}

FileManagerChildFrame::~FileManagerChildFrame()
{
}

void FileManagerChildFrame::install_message_handling(message::dispatch * pinterface)
{
   simple_child_frame::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(application::APPM_LANGUAGE, pinterface, this, &FileManagerChildFrame::_001OnAppLanguage);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &FileManagerChildFrame::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &FileManagerChildFrame::_001OnCreate);
}

bool FileManagerChildFrame::CreateBars()
{
   sp(::filemanager::document) pdoc =  (GetActiveDocument());
   if(pdoc == NULL)
      return false;
   
   ASSERT(pdoc != NULL);
   ASSERT(base < ::filemanager::document >::bases(pdoc));

   DestroyBars();

   string strToolBar;

   if(pdoc->get_filemanager_data()->is_saving())
   {
      strToolBar = pdoc->get_filemanager_data()->m_ptemplate->m_strToolBarSave;
   }
   else
   {
      strToolBar = pdoc->get_filemanager_data()->m_ptemplate->m_strToolBar;
   }

   if(strToolBar.is_empty())
   {
      if(pdoc->get_filemanager_data()->is_saving())
      {
         strToolBar = pdoc->get_filemanager_data()->m_strToolBarSave;
      }
      else
      {
         strToolBar = pdoc->get_filemanager_data()->m_strToolBar;
      }
   }


   string str = Application.file().as_string(Application.dir().matter(strToolBar));


   if (!m_toolbar.CreateEx(this) ||
       !m_toolbar.LoadXmlToolBar(str))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }

   layout();

   return true;

}

bool FileManagerChildFrame::DestroyBars()
{
   m_toolbar.DestroyWindow();
   m_toolbar.RemoveAllTools();
   return true;
}

bool FileManagerChildFrame::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   
   //FileManagerFileListCallback * pcallback = GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;
   return simple_child_frame::_001OnCmdMsg(pcmdmsg);
}

void FileManagerChildFrame::OnChangeEditSearch()
{

   sp(::user::document_interface) pdoc = GetActiveDocument();

   if(pdoc != NULL)
   {
      FileManagerViewUpdateHint uh;
      uh.set_type(FileManagerViewUpdateHint::TypeFilter);
      string str;

   }

}

void FileManagerChildFrame::_001OnCreate(signal_details * pobj)
{
   if(pobj->m_bRet)
      return;
   

   m_hMenuDefault = NULL;
   
   
}


void FileManagerChildFrame::_001OnAppLanguage(signal_details * pobj)
{
   CreateBars();
   pobj->m_bRet = false;
}

void FileManagerChildFrame::GetSelected(::fs::item_array &itema)
{
   sp(::filemanager::SimpleFileListInterface) plistinterface = GetActiveView();
   if(plistinterface != NULL)
   {
      plistinterface->GetSelected(itema);
   }
}

void FileManagerChildFrame::_001OnShowWindow(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}




