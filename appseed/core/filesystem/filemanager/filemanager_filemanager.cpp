#include "framework.h"


namespace filemanager
{


   filemanager::filemanager(::base::application * papp) :
      element(papp),
      ::base::departament(papp)
   {
      m_ptemplateStd       = NULL;

   }

   filemanager::~filemanager()
   {
   }

   bool filemanager::initialize()
   {

      set_data_server(Application.simpledb().get_data_server());

      if(!filemanager::file_list_callback::initialize())
         return false;

      InitializeFileManager("filemanager/filemanager");

      m_ptemplateStd->m_strLevelUp.Empty();
      m_ptemplateStd->m_strToolBar = "filemanager_toolbar.xml";
      m_ptemplateStd->m_dataidStatic = "FileManagerFavoritesList";
      //m_ptemplateStd->m_uiDialogBar = 0;
      //m_ptemplateStd->m_uiMenuBar = 0;
      m_ptemplateStd->m_strFilePopup = "filemanager\\file_popup.xml";
      //m_ptemplateStd->m_strFilePopupSubstId = 0;
      m_ptemplateStd->m_strFolderPopup = "filemanager\\folder_popup.xml";
      m_ptemplateStd->m_strPopup = "filemanager\\popup.xml";
      m_ptemplateStd->m_idExpandBox = 0;
      m_ptemplateStd->m_idCollapseBox = 0;
      m_ptemplateStd->m_pfilelistcallback = this;
      //m_ptemplateStd->m_pfilelistcallback->set_app(this);
      m_ptemplateStd->m_strDISection = Application.m_strAppName;



      m_ptemplateFs->m_strLevelUp.Empty();
      m_ptemplateFs->m_strToolBar = "filemanager_toolbar.xml";
      m_ptemplateFs->m_dataidStatic = "FileManagerFavoritesList";
      //m_ptemplateFs->m_uiDialogBar = 0;
      //m_ptemplateFs->m_uiMenuBar = 0;
      m_ptemplateFs->m_strFilePopup = "filemanager\\file_popup.xml";
      //m_ptemplateFs->m_strFilePopupSubstId = 0;
      m_ptemplateFs->m_strFolderPopup = "filemanager\\folder_popup.xml";
      m_ptemplateFs->m_strPopup = "filemanager\\popup.xml";
      m_ptemplateFs->m_idExpandBox = 0;
      m_ptemplateFs->m_idCollapseBox = 0;
      m_ptemplateFs->m_pfilelistcallback = this;
      //m_ptemplateFs->m_pfilelistcallback->set_app(this);
      m_ptemplateFs->m_strDISection = "fs." + Application.m_strAppName;


      m_idFileManager = Application.m_strAppName;

      return true;

   }



   void filemanager::InitializeFileManager(const char * pszMatter)
   {

      System.factory().creatable_small < document > ();
      System.factory().creatable_small < child_frame > ();
      System.factory().creatable_small < a_view > ();
      System.factory().creatable_small < path_view > ();
      System.factory().creatable_small < FileManagerSaveAsView > ();
      System.factory().creatable_small < left_view > ();
      System.factory().creatable_small < main_view > ();
      System.factory().creatable_small < document > ();
      System.factory().creatable_small < file_list > ();
      System.factory().creatable_small < preview > ();
      System.factory().creatable_small < main_frame > ();
      System.factory().creatable_small < tab_view > ();
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


      System.factory().creatable_small < fs::simple::view > ();
      System.factory().creatable_small < fs::simple::list_view > ();


      m_ptemplateStd = new schema(this);
      Application.userex()->shellimageset().initialize();
      m_ptemplateStd->Initialize(0, pszMatter);

      m_ptemplateFs = new schema(this);
      m_ptemplateFs->Initialize(0, string("fs.") + string(pszMatter));

      m_ptemplateForm = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < file_manager_form_document > (),
         System.type_info < file_manager_form_child_frame > (),
         System.type_info < file_manager_form_view > ());

      m_ptemplateOperation = new ::user::single_document_template(
         get_app(),
         pszMatter,
         System.type_info < file_manager_operation_document > (),
         System.type_info < file_manager_operation_child_frame > (),
         System.type_info < file_manager_operation_view > ());
   }



   void filemanager::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      item_action * pitemaction = dynamic_cast < item_action * > (this);
      if(pitemaction != NULL)
      {
         if(pitemaction->file_manager_open_file(pdata, itema))
            return;
      }


      sp(::create_context) cc(allocer());
      cc->m_spCommandLine->m_varFile = itema[0].m_strPath;
      request_create(cc);

   }



   bool filemanager::do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::impact_system) ptemplate, sp(::user::object) pdocument)
   {

      sp(::userex::pane_tab_view) ppanetabview = NULL;
      if(pdocument->get_view() != NULL && pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view > () != NULL)
      {
         ppanetabview = pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view > ();
         ppanetabview->set_cur_tab_by_id("file_manager");
         ppanetabview->get_pane_by_id("file_manager")->m_bPermanent = false;
         ppanetabview->layout();
         ppanetabview->get_filemanager_document()->FileManagerSaveAs(pdocument);
         if(ppanetabview->GetParentFrame()->RunModalLoop() != "yes")
            return FALSE;
         varFile = ppanetabview->get_filemanager_document()->get_filemanager_data()->m_pmanager->m_strTopic;
         return TRUE;
      }

      UNREFERENCED_PARAMETER(nIDSTitle);
      UNREFERENCED_PARAMETER(lFlags);
      UNREFERENCED_PARAMETER(ptemplate);
      ASSERT(bOpenFileDialog == FALSE);
      sp(document) pdoc =  (m_ptemplateStd->open());
      tab_view * pview = pdoc->get_typed_view < tab_view >();

#ifdef WINDOWSEX
      oswindow oswindowDesktop = ::GetDesktopWindow();
      rect rectOpen;
      ::GetWindowRect(oswindowDesktop, rectOpen);
      int32_t iWidth = rectOpen.width();
      int32_t iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);

#endif
      pview->set_cur_tab_by_id(1);
      pview->GetParentFrame()->RedrawWindow();
      pview->GetParentFrame()->RunModalLoop();
      varFile = pdoc->m_strTopic;
      pview->GetParentFrame()->DestroyWindow();
      return TRUE;

   }

   string filemanager::get_initial_browse_path(const char * pszDefault)
   {

      string strId;

      strId.Format("document(%s)", m_ptemplateStd->m_strDISection);

      database::id dataid = strId;

      string strPath;

      if(data_get(dataid, "InitialBrowsePath", ::base::system::idEmpty, strPath))
      {

         sess(get_app()).dir().mk(strPath);

         if(sess(get_app()).dir().is(strPath))
         {

            return strPath;

         }

      }

      if(pszDefault != NULL && strlen(pszDefault) > 0)
      {

         strPath = pszDefault;

      }
      else
      {

         strPath = session().dir().userdata();

      }

      if(data_set(dataid, "InitialBrowsePath", ::base::system::idEmpty, strPath))
      {

         return strPath;

      }

      return "";

   }


   void filemanager::on_request(sp(::create_context) pcreatecontext)
   {
      filemanager::callback::on_request(pcreatecontext);
   }



} // namespace filemanager


