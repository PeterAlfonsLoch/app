#include "framework.h"
#include "filemanager_folder_list_view.h"
#include "filemanager_folder_selection_list_view.h"
#include "SimpleFolderTreeView.h"
#include "FileManagerViewUpdateHint.h"


folder_selection_list_view::folder_selection_list_view(sp(::ca2::application) papp) :
   ca2(papp),
   ::user::split_layout(papp),
   
   ::user::split_view(papp),
   place_holder_container(papp),
   m_pdata(new filemanager::data(papp))
{
}

folder_selection_list_view::~folder_selection_list_view()
{
}

void folder_selection_list_view::install_message_handling(::ca2::message::dispatch * pinterface)
{
   ::user::split_view::install_message_handling(pinterface);
}



void folder_selection_list_view::Initialize(FileManagerTemplate * ptemplate, const char * lpcszSection, ::database::id datakey, bool bRecursive)
{
   get_filemanager_data()->m_pmanager  = this;
   get_filemanager_data()->m_ptemplate = ptemplate;
   get_filemanager_data()->m_iTemplate = ptemplate->m_iTemplate;
   get_filemanager_data()->m_iDocument = 0;

   string str;
   str.Format("folder_selection_list_view(%s,%s)", get_filemanager_data()->m_ptemplate->m_strDISection, lpcszSection);
   m_dataid = str;

   CreateViews();
   
   m_plistview->Initialize(datakey, bRecursive);
   str.Format("folder_selection_list_view.ListView(%s,%s)", get_filemanager_data()->m_ptemplate->m_strDISection, lpcszSection);
   m_plistview->m_dataid = str;

   m_plistview->_001UpdateColumns();

   if(data_get("InitialBrowsePath", ::ca2::system::idEmpty, str))
   {
      FileManagerBrowse(str);
   }
   else
   {
      FileManagerBrowse("");
   }

   m_plistview->_001OnUpdateItemCount();
}

void folder_selection_list_view::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(orientation_vertical);
  
   set_position_rate(0, 0.30);

   m_ptreeview = create_view  < filemanager::SimpleFolderTreeView > ();

   if(m_ptreeview == NULL)
   {
      System.simple_message_box(NULL, "Could not create folder tree ::user::view");
   }

   m_ptreeview->m_pfilemanagerinterface = this;

   SetPane(0, m_ptreeview, false);

   m_plistview = create_view < folder_list_view > ();

   if(m_plistview == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::user::view");
   }

   m_plistview->m_pfilemanagerinterface = this;

   SetPane(1, m_plistview, false);

}

void folder_selection_list_view::OnFileManagerBrowse()
{
   {
      FileManagerViewUpdateHint uh;
      uh.set_type(FileManagerViewUpdateHint::TypeSynchronizeFolderSelection);
      get_document()->update_all_views(NULL, 0, &uh);
   }
}


void folder_selection_list_view::FolderAdd()
{
   stringa straSel;
   m_ptreeview->GetSelectedFilePath(straSel);
   if(m_plistview->m_bRecursive)
   {
      bool_array ba;
      m_plistview->add_unique(straSel, ba);
   }
   else
   {
      m_plistview->add_unique(straSel);
   }
}

void folder_selection_list_view::FolderRemove()
{
   stringa wstraSel;
   m_plistview->GetSel(wstraSel);
   m_plistview->remove(wstraSel);
}


void folder_selection_list_view::_001OnAdd(::ca2::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   FolderAdd();
}

void folder_selection_list_view::_001OnRemove(::ca2::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   FolderRemove();
}

filemanager::data * folder_selection_list_view::get_filemanager_data()
{
   return m_pdata;
}