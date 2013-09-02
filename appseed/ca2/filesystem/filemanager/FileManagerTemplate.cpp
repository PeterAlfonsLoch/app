#include "framework.h"



FileManagerTemplate::FileManagerTemplate(::filemanager::filemanager * pfilemanager) :
   element(pfilemanager->get_app())
{

   m_pfilemanager = pfilemanager;

   m_iTemplate = -1;

   m_pdialogbar = NULL;
   m_pfilelistcallback = NULL;

   //m_uiLevelUp       = 0xffffffff;
//   m_uiMenuBar       = 0xffffffff;
   m_iNextDocument   = 0;

   m_pdoctemplate = NULL;
   m_pdoctemplateChild = NULL;
   m_pdoctemplateChildList = NULL;
}

FileManagerTemplate::~FileManagerTemplate()
{
   if(m_pdoctemplate != NULL)
   {
      m_pdoctemplate.release();
   }
}

sp(::filemanager::document) FileManagerTemplate::open(sp(create_context) pcreatecontext, ::fs::data * pdata, ::filemanager::data * pfilemanagerdata)
{
   sp(::filemanager::document) pdoc =  (m_pdoctemplateMain->open_document_file(pcreatecontext));
   if(pdoc != NULL)
   {
      if(pfilemanagerdata == NULL)
      {
         pfilemanagerdata = new filemanager::data(get_app());
      }
      pdoc->set_filemanager_data(pfilemanagerdata);
      pdoc->get_filemanager_data()->m_pcallback = m_pfilemanager;
      pdoc->get_filemanager_data()->m_pmanager  = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain  = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate = this;
      pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;
      pdoc->get_filemanager_data()->m_bTransparentBackground = pcreatecontext == NULL ? true : pcreatecontext->m_bTransparentBackground;
      string strId;
      strId.Format("filemanager(%d)", pdoc->get_filemanager_data()->m_iDocument);
      pdoc->get_filemanager_data()->m_strDISection = m_strDISection + "." + strId;
      pdoc->get_filemanager_data()->m_bFileSize = true;
      pdoc->Initialize(pcreatecontext == NULL ? true : pcreatecontext->m_bMakeVisible);
      return pdoc;
   }
   return NULL;
}

sp(::filemanager::document) FileManagerTemplate::create_new_document(
   FileManagerCallbackInterface * pcallback)
{
   sp(::filemanager::document) pdoc =  (m_pdoctemplate->create_new_document());
   if(pdoc != NULL)
   {

      pdoc->get_filemanager_data()->m_pcallback       = pcallback;
      pdoc->get_filemanager_data()->m_pfilemanager    = pcallback;
      pdoc->get_filemanager_data()->m_pmanager        = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain    = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate       = this;
      pdoc->get_filemanager_data()->m_iTemplate       = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument       = m_iNextDocument++;

      return pdoc;
   }
   return NULL;
}


sp(::filemanager::document) FileManagerTemplate::OpenChild(bool bMakeVisible, bool bTransparentBackground, sp(::user::interaction) pwndParent, filemanager::data * pfilemanagerdata)
{
   sp(create_context) createcontext(allocer());
   createcontext->m_bMakeVisible = false;
   createcontext->m_puiParent = pwndParent;
   sp(::filemanager::document) pdoc =  (m_pdoctemplateChild->open_document_file(createcontext));
   if(pdoc != NULL)
   {
      if(pfilemanagerdata == NULL)
      {
         pfilemanagerdata = new ::filemanager::data(get_app());
      }
      pdoc->set_filemanager_data(pfilemanagerdata);
      pdoc->get_filemanager_data()->m_pcallback                = m_pfilemanager;
      pdoc->get_filemanager_data()->m_pfilemanager             = m_pfilemanager;
      pdoc->get_filemanager_data()->m_pmanager                 = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain             = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate                = this;
      pdoc->get_filemanager_data()->m_iTemplate                = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument                = m_iNextDocument++;
      pdoc->get_filemanager_data()->m_bTransparentBackground   = bTransparentBackground;
      string strId;
      strId.Format("filemanager::%s::(%d)", Application.filemanager().m_idFileManager.str(), pdoc->get_filemanager_data()->m_iDocument);
      pdoc->get_filemanager_data()->m_strDISection             = strId;
      pdoc->Initialize(bMakeVisible);
      return pdoc;
   }
   return NULL;
}


sp(::filemanager::document) FileManagerTemplate::open_child_list(bool bMakeVisible, bool bTransparentBackground, sp(::user::interaction) pwndParent, ::filemanager::data * pfilemanagerdata)
{
   UNREFERENCED_PARAMETER(bMakeVisible);
   sp(create_context) createcontext(allocer());
   createcontext->m_bMakeVisible = false;
   createcontext->m_puiParent = pwndParent;
   sp(::filemanager::document) pdoc =  (m_pdoctemplateChildList->open_document_file(createcontext));
   if(pdoc != NULL)
   {
//      pdoc->get_filemanager_data()->m_uiMenuBar = m_uiMenuBar;
//      pdoc->get_filemanager_data()->m_uiToolBar = m_uiToolBar;
      if(pfilemanagerdata == NULL)
      {
         pfilemanagerdata = new filemanager::data(get_app());
      }
      pdoc->set_filemanager_data(pfilemanagerdata);
      pdoc->get_filemanager_data()->m_pcallback = m_pfilemanager;
      pdoc->get_filemanager_data()->m_pfilemanager = m_pfilemanager;
      pdoc->get_filemanager_data()->m_pmanager  = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain  = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate = this;
      pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;
      pdoc->get_filemanager_data()->m_bTransparentBackground = bTransparentBackground;

      //pdoc->CreateViews();

      return pdoc;
   }
   return NULL;
}

void FileManagerTemplate::Initialize(int32_t iTemplate, const char * pszMatter)
{
   m_iTemplate       = iTemplate;
   m_pdoctemplateMain = new ::user::multiple_document_template(
      get_app(),
      pszMatter,
      System.type_info < ::filemanager::document > (),
      System.type_info < FileManagerMainFrame > (),       // main SDI frame ::ca2::window
      System.type_info < FileManagerTabView > ());

   m_pdoctemplate = new ::user::multiple_document_template(
      get_app(),
      pszMatter,
      System.type_info < ::filemanager::document > (),
      System.type_info < FileManagerFrame > (),
      System.type_info < FileManagerAView > ());

   m_pdoctemplateChild = new ::user::multiple_document_template(
      get_app(),
      pszMatter,
      System.type_info < ::filemanager::document > (),
      System.type_info < FileManagerChildFrame > (),
      System.type_info < FileManagerAView > ());

   m_pdoctemplateChildList = new ::user::multiple_document_template(
      get_app(),
      pszMatter,
      System.type_info < ::filemanager::document > (),
      System.type_info < FileManagerChildFrame > (),
      System.type_info < filemanager::SimpleFileListView > ());
}
