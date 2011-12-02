#include "StdAfx.h"
#include "SimpleFileListView.h"
#include "SimpleFolderTreeView.h"
#include "SimplePreview.h"
#include "filemanager_folder_selection_list_view.h"
#include "filemanager_folder_list_view.h"


namespace filemanager
{


   application::application()
   {
      m_ptemplateStd       = NULL;
      m_pfilemanager       = this;
   }

   application::~application(void)
   {
   }

   bool application::initialize()
   {

      if(!::fs::application::initialize())
         return false;

      if(!file_manager_interface::initialize(this))
         return false;

      if(!FileManagerFileListCallback::initialize())
         return false;

      filemanager::application::InitializeFileManager("filemanager/filemanager");
      GetStdFileManagerTemplate()->m_strLevelUp.Empty();
      GetStdFileManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetStdFileManagerTemplate()->m_dataidStatic = "FileManagerFavoritesList";
      //GetStdFileManagerTemplate()->m_uiDialogBar = 0;
      //GetStdFileManagerTemplate()->m_uiMenuBar = 0;
      GetStdFileManagerTemplate()->m_strFilePopup = "filemanager\\file_popup.xml";
      //GetStdFileManagerTemplate()->m_strFilePopupSubstId = 0;
      GetStdFileManagerTemplate()->m_strFolderPopup = "filemanager\\folder_popup.xml";
      GetStdFileManagerTemplate()->m_strPopup = "filemanager\\popup.xml";
      GetStdFileManagerTemplate()->m_idExpandBox = 0;
      GetStdFileManagerTemplate()->m_idCollapseBox = 0;
      GetStdFileManagerTemplate()->m_pfilelistcallback = this;
      //GetStdFileManagerTemplate()->m_pfilelistcallback->set_app(this);
      GetStdFileManagerTemplate()->m_strDISection = m_strAppName;



      GetFsManagerTemplate()->m_strLevelUp.Empty();
      GetFsManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetFsManagerTemplate()->m_dataidStatic = "FileManagerFavoritesList";
      //GetFsManagerTemplate()->m_uiDialogBar = 0;
      //GetFsManagerTemplate()->m_uiMenuBar = 0;
      GetFsManagerTemplate()->m_strFilePopup = "filemanager\\file_popup.xml";
      //GetFsManagerTemplate()->m_strFilePopupSubstId = 0;
      GetFsManagerTemplate()->m_strFolderPopup = "filemanager\\folder_popup.xml";
      GetFsManagerTemplate()->m_strPopup = "filemanager\\popup.xml";
      GetFsManagerTemplate()->m_idExpandBox = 0;
      GetFsManagerTemplate()->m_idCollapseBox = 0;
      GetFsManagerTemplate()->m_pfilelistcallback = this;
      //GetFsManagerTemplate()->m_pfilelistcallback->set_app(this);
      GetFsManagerTemplate()->m_strDISection = "fs." + m_strAppName;
      return true;
   }
 

   void application::on_request(::ax::create_context * pcreatecontext)
   {
      FileManagerCallbackInterface::on_request(pcreatecontext);
   }

   FileManagerTemplate * application::GetStdFileManagerTemplate(void)
   {
      return m_ptemplateStd;
   }

   FileManagerTemplate * application::GetFsManagerTemplate(void)
   {
      return m_ptemplateFs;
   }

   void application::InitializeFileManager(const char * pszMatter)
   {
      if(is_system())
      {
         System.factory().creatable_small < ::filemanager::document > ();
         System.factory().creatable_small < FileManagerChildFrame > ();
         System.factory().creatable_small < FileManagerAView > ();
         System.factory().creatable_small < FileManagerPathView > ();
         System.factory().creatable_small < FileManagerSaveAsView > ();
         System.factory().creatable_small < FileManagerLeftView > ();
         System.factory().creatable_small < FileManagerView > ();
         System.factory().creatable_small < ::filemanager::document > ();
         System.factory().creatable_small < filemanager::SimpleFileListView > ();
         System.factory().creatable_small < filemanager::SimpleFolderTreeView > ();
         System.factory().creatable_small < filemanager::SimplePreview > ();
         System.factory().creatable_small < FileManagerMainFrame > ();
         System.factory().creatable_small < FileManagerTabView > ();
         System.factory().creatable_small < file_manager_form_document > ();
         System.factory().creatable_small < file_manager_form_child_frame > ();
         System.factory().creatable_small < file_manager_form_view > ();
         System.factory().creatable_small < folder_selection_list_view > ();
         System.factory().creatable_small < folder_list_view > ();
         System.factory().creatable_small < file_manager_operation_document > ();
         System.factory().creatable_small < file_manager_operation_child_frame > ();
         System.factory().creatable_small < file_manager_operation_view > ();
         System.factory().creatable_small < file_manager_operation_info_view > ();
         System.factory().creatable_small < file_manager_operation_list_view > ();


         System.factory().creatable_small < ::filemanager::fs::simple::view > ();
         System.factory().creatable_small < ::filemanager::fs::simple::tree_view > ();
         System.factory().creatable_small < ::filemanager::fs::simple::list_view > ();
      }


      m_ptemplateStd = new FileManagerTemplate(this);
      shellimageset().initialize();
      m_ptemplateStd->Initialize(this, 0, pszMatter);

      m_ptemplateFs = new FileManagerTemplate(this);
      m_ptemplateFs->Initialize(this, 0, string("fs.") + string(pszMatter));

      m_ptemplateForm = new ::userbase::multiple_document_template(
         this,
         pszMatter,
         ::ax::get_type_info < file_manager_form_document > (),
         ::ax::get_type_info < file_manager_form_child_frame > (),
         ::ax::get_type_info < file_manager_form_view > ());

      m_ptemplateOperation = new ::userbase::single_document_template(
         this,
         pszMatter,
         ::ax::get_type_info < file_manager_operation_document > (),
         ::ax::get_type_info < file_manager_operation_child_frame > (),
         ::ax::get_type_info < file_manager_operation_view > ());
   }



   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      item_action * pitemaction = dynamic_cast < item_action * > (this);
      if(pitemaction != NULL)
      {
         if(pitemaction->file_manager_open_file(pdata, itema))
            return;
      }


      ::ax::create_context_sp cc(get_app());
      cc->m_spCommandLine->m_varFile = itema[0].m_strPath;
      request(cc);

   }



   BOOL application::do_prompt_file_name(string & fileName, UINT nIDSTitle, DWORD lFlags,
         BOOL bOpenFileDialog, document_template * ptemplate)
   {
      UNREFERENCED_PARAMETER(nIDSTitle);
      UNREFERENCED_PARAMETER(lFlags);
      UNREFERENCED_PARAMETER(ptemplate);
      ASSERT(bOpenFileDialog == FALSE);
      ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_ptemplateStd->open(this));
      FileManagerTabView * pview = pdoc->get_typed_view < FileManagerTabView >();
      HWND hwndDesktop = ::GetDesktopWindow();
      rect rectOpen;
      ::GetWindowRect(hwndDesktop, rectOpen);
      int iWidth = rectOpen.width();
      int iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);
      pview->set_cur_tab_by_id(1);
      pview->GetParentFrame()->RedrawWindow();
      pview->GetParentFrame()->RunModalLoop();
      fileName = pdoc->m_strTopic;
      pview->GetParentFrame()->DestroyWindow();
      return TRUE;

   }

   string application::get_file_manager_initial_browse_path(const char * pszDefault)
   {
      string strId;
      strId.Format("::filemanager::document(%s)", GetStdFileManagerTemplate()->m_strDISection);
      database::id dataid = strId;
      string strPath;
      if(data_get(dataid, "InitialBrowsePath", ::radix::system::idEmpty, strPath))
      {
         return strPath;
      }
      if(pszDefault != NULL && strlen(pszDefault) > 0)
      {
         strPath = pszDefault;
      }      
      else
      {
         strPath = Application.dir().userdata();
      }
      if(data_set(dataid, "InitialBrowsePath", ::radix::system::idEmpty, strPath))
      {
         return strPath;
      }
      return "";
   }
} // namespace filemanager


