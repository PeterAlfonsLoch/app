#include "StdAfx.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "syllomatter_pane_view.h"

#include "filemanager/filemanager_form_update_hint.h"
#include "filemanager/filemanager_form_child_frame.h"
#include "filemanager/filemanager_form_document.h"
#include "filemanager/filemanager_form_view.h"


namespace syllomatter
{

   application::application()
   {
   }

   void application::construct()
   {
      m_strAppName = "syllomatter";
      m_strLicense = "";
      m_strBaseSupportId = "votagus_ca2_syllomatter";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < main_document >();
      System.factory().creatable_small < main_frame >();
      System.factory().creatable_small < syllomatter_pane_view >();
      System.factory().creatable_small < syllomatter_document >();
      System.factory().creatable_small < syllomatter_frame >();
      System.factory().creatable_small < syllomatter_view >();
      System.factory().creatable_small < syllomatter::filemanager_document >();
      System.factory().creatable_small < syllomatter::filemanager_frame >();
      System.factory().creatable_small < syllomatter::filemanager_template >();
      System.factory().creatable_small < syllomatter_list_view >();
      System.factory().creatable_small < svn_view >();

      if(!cube2::application::initialize_instance())
         return FALSE;

      InitializeFileManager("syllomatter/frame");
      GetStdFileManagerTemplate()->m_strLevelUp.Empty();
      GetStdFileManagerTemplate()->m_strToolBar = "syllomatter_filemanager_toolbar.xml";
      GetStdFileManagerTemplate()->m_dataidStatic = "FileManagerFavoritesList";
      //GetStdFileManagerTemplate()->m_uiDialogBar = 0;
      //GetStdFileManagerTemplate()->m_uiMenuBar = 0;
      GetStdFileManagerTemplate()->m_strFilePopup = "filemanager\\file_popup.xml";
      //GetStdFileManagerTemplate()->m_uiFilePopupSubstId = 0;
      GetStdFileManagerTemplate()->m_strFolderPopup = "filemanager\\folder_popup.xml";
      GetStdFileManagerTemplate()->m_strPopup = "filemanager\\popup.xml";
      //GetStdFileManagerTemplate()->m_uiExpandBox = 0;
      //GetStdFileManagerTemplate()->m_uiCollapseBox = 0;
   //   GetStdFileManagerTemplate()->m_pfilelistcallback = this;
     // GetStdFileManagerTemplate()->m_pfilelistcallback->set_app(this);


      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "filemanager/frame",
         ::ca::get_type_info < main_document > (),
         ::ca::get_type_info < main_frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < syllomatter_pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;


      connect_command("add_working_copy", &::syllomatter::application::_001OnAddWorkingCopy);

      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      m_ptemplate_html->open_document_file(pcreatecontext);
   }

   void application::InitializeFileManager(const char * pszMatter)
   {
      m_ptemplateStd = new syllomatter::filemanager_template(this);
      shellimageset().initialize();
      m_ptemplateStd->Initialize(dynamic_cast < ::ca::application * > (this), 0, pszMatter);

      filemanager::application::m_ptemplateForm = new ::userbase::multiple_document_template(
         this,
         "system/form",
         ::ca::get_type_info < file_manager_form_document > (),
         ::ca::get_type_info < file_manager_form_child_frame > (),
         ::ca::get_type_info < file_manager_form_view > ());

      m_ptemplateOperation = new ::userbase::single_document_template(
         this,
         "system/form",
         ::ca::get_type_info < file_manager_operation_document > (),
         ::ca::get_type_info < file_manager_operation_child_frame > (),
         ::ca::get_type_info < file_manager_operation_view > ());
   }

   void application::create(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void application::commit(const char * pszDescriptor, const char * pszWorkingCopy)
   {
      UNREFERENCED_PARAMETER(pszDescriptor);
      UNREFERENCED_PARAMETER(pszWorkingCopy);
   }

   void application::checkout(const char * pszRepos, const char * pszWorkingCopy)
   {
      string strHead = Application.http().get("https://syllomatter.api.veriterse.net/head");
      string strFileList = Application.http().get("https://syllomatter.api.veriterse.net/checkout_list?revision=" + strHead + "repos=" + string(pszRepos));
      stringa stra;
      stra.explode(strFileList, "\n");
      string strSrcBase = System.dir().appdata("syllomatter", pszWorkingCopy);
      string strDstBase = System.dir().ca2("syllomatter", pszWorkingCopy);
      string strFileSrc;
      string strFileDst;
      for(int i = 0; i < stra.get_size(); i++)
      {
         strFileSrc = System.dir().path(strSrcBase, stra[i]);
         System.http().download("https://syllomatter.api.veriterse.net/get?revision=" + strHead + "repos=" + string(pszRepos) + "&file=" + System.url().url_encode(stra[i]), strFileSrc);
         strFileDst = System.dir().path(strDstBase, stra[i]);
         System.file().copy(strFileDst, strFileSrc);
      }
   }

   void application::update(const char * pszWorkingCopy)
   {
      UNREFERENCED_PARAMETER(pszWorkingCopy);
   }


   void application::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, const ::fs::item & item, stringa & straCommand, stringa & straCommandTitle)
   {
      straCommand.add("add_working_copy");
      straCommandTitle.add("Add Working Copy");
   }


   void application::_001OnAddWorkingCopy(gen::signal_object * pobj)
   {
      simple_message_box(NULL, "GoingToAddWorkingCopy", 0);
   }


   

} // namespace syllomatter



CLASS_DECL_CA2_TESSERACT ::ca::application * syllomatter_get_new_app()
{
   return new ::syllomatter::application;
}
