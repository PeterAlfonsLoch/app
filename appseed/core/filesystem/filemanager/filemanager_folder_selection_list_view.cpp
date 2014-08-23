#include "framework.h"


namespace filemanager
{


   folder_selection_list_view::folder_selection_list_view(sp(::aura::application) papp):
      element(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

      }


   folder_selection_list_view::~folder_selection_list_view()
   {

   }


   void folder_selection_list_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::split_view::install_message_handling(pinterface);
   }



   void folder_selection_list_view::Initialize(manager_template * ptemplate,const char * lpcszSection,::database::id datakey,bool bRecursive)
   {

      get_filemanager_template() = ptemplate;
      get_filemanager_data()->m_iTemplate = ptemplate->m_iTemplate;
      get_filemanager_data()->m_iDocument = 0;

      string str;
      str.Format("folder_selection_list_view(%s,%s)",get_filemanager_template()->m_strDISection,lpcszSection);
      m_dataid = str;

      CreateViews();

      m_plistview->Initialize(datakey,bRecursive);
      str.Format("folder_selection_list_view.ListView(%s,%s)",get_filemanager_template()->m_strDISection,lpcszSection);
      m_plistview->m_dataid = str;

      m_plistview->_001UpdateColumns();

      if(data_get(".local://InitialBrowsePath",::base::system::idEmpty,str))
      {
         get_filemanager_manager()->FileManagerBrowse(str,::action::source::database_default());
      }
      else
      {
         get_filemanager_manager()->FileManagerBrowse("",::action::source::system_default());
      }

      m_plistview->_001OnUpdateItemCount();
   }

   void folder_selection_list_view::CreateViews()
   {

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0,0.30);

      initialize_split_layout();

      m_pusertree = create_view  < ::user::tree >();

      if(m_pusertree == NULL)
      {
         System.simple_message_box(NULL,"Could not create folder tree ::user::impact");
      }

      m_ptree = canew(tree(get_app()));

      if(m_ptree == NULL)
      {
         System.simple_message_box(NULL,"Could not create folder tree ::user::impact");
      }

      m_ptree->m_pmanager = get_filemanager_manager();

      m_pusertree->merge(m_ptree, true);

      SetPane(0,m_pusertree,false);

      m_plistview = create_view < folder_list_view >();

      if(m_plistview == NULL)
      {
         System.simple_message_box(NULL,"Could not create file list ::user::impact");
      }

      m_plistview->m_pmanager = get_filemanager_manager();

      SetPane(1,m_plistview,false);

   }

   void folder_selection_list_view::OnFileManagerBrowse(::action::context actioncontext)
   {
      {
         update_hint uh;
         uh.set_type(update_hint::TypeSynchronizeFolderSelection);
         uh.m_actioncontext = actioncontext + ::action::source_selection;
         get_document()->update_all_views(NULL,0,&uh);
      }
   }


   void folder_selection_list_view::FolderAdd()
   {
      stringa straSel;
      m_ptree->GetSelectedFilePath(straSel);
      if(m_plistview->m_bRecursive)
      {
         bool_array ba;
         m_plistview->add_unique(straSel,ba);
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


   void folder_selection_list_view::_001OnAdd(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      FolderAdd();
   }

   void folder_selection_list_view::_001OnRemove(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      FolderRemove();
   }

   sp(data) folder_selection_list_view::get_filemanager_data()
   {
      return m_pdata;
   }


} // namespace filemanager









