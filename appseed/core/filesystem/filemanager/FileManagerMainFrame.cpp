#include "framework.h"
#include "FileManagerMainFrame.h"


FileManagerMainFrame::FileManagerMainFrame(sp(base_application) papp) :
   element(papp),
   simple_frame_window(papp),
   m_menubar(papp),
   m_toolbar(papp)
{
}

FileManagerMainFrame::~FileManagerMainFrame()
{
}



void FileManagerMainFrame::_001OnCreate(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   
}


bool FileManagerMainFrame::CreateBars()
{
   sp(::filemanager::document) pdoc =  (GetActiveDocument());
   
   ASSERT(pdoc != NULL);
   ASSERT(base < ::filemanager::document >::bases(pdoc));

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
      !m_toolbar.LoadXmlToolBar(Application.file().as_string(Application.dir().matter(strToolBar))))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }

   return true;

}




