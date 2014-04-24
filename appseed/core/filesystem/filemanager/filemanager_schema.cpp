#include "framework.h"


namespace filemanager
{


   schema::schema(filemanager * pfilemanager) :
      element(pfilemanager->get_app())
   {

      m_pfilemanager = pfilemanager;

      m_iTemplate = -1;

//      m_pdialogbar = NULL;
      m_pfilelistcallback = NULL;

      //m_uiLevelUp       = 0xffffffff;
      //   m_uiMenuBar       = 0xffffffff;
      m_iNextDocument = 0;

      m_pdoctemplate = NULL;
      m_pdoctemplateChild = NULL;
      m_pdoctemplateChildList = NULL;
   }

   schema::~schema()
   {
      if (m_pdoctemplate != NULL)
      {
         m_pdoctemplate.release();
      }
   }

   sp(document) schema::open(sp(::create_context) pcreatecontext, ::fs::data * pdata, ::filemanager::data * pfilemanagerdataParam)
   {
      
      sp(::filemanager::data) pfilemanagerdata(pfilemanagerdataParam);

      if (pcreatecontext.is_null())
         pcreatecontext.create(allocer());

      if (pfilemanagerdata.is_null())
      {

         pfilemanagerdata = canew(::filemanager::data(get_app()));
         pfilemanagerdata->m_pcallback = m_pfilemanager;
         pfilemanagerdata->m_pschema = this;
         pfilemanagerdata->m_iTemplate = m_iTemplate;
         pfilemanagerdata->m_iDocument = m_iNextDocument++;
         pfilemanagerdata->m_bTransparentBackground = pcreatecontext == NULL ? true : pcreatecontext->m_bTransparentBackground;
         string strId;
         strId.Format("filemanager(%d)", pfilemanagerdata->m_iDocument);
         pfilemanagerdata->m_strDISection = m_strDISection + "." + strId;
         pfilemanagerdata->m_bFileSize = true;

      }

      pcreatecontext->oprop("filemanager::data") = pfilemanagerdata;

      sp(document) pdoc = (m_pdoctemplateMain->open_document_file(pcreatecontext));

      if (pdoc != NULL)
      {

         pdoc->Initialize(pcreatecontext == NULL ? true : pcreatecontext->m_bMakeVisible);

         return pdoc;

      }

      return NULL;

   }

   sp(document) schema::create_new_document(callback * pcallback, sp(::create_context) pcreatecontext)
   {

      sp(document) pdoc = (m_pdoctemplate->create_new_document(pcreatecontext));

      if (pdoc != NULL)
      {

         pdoc->get_filemanager_data()->m_pcallback = pcallback;
         pdoc->get_filemanager_data()->m_pfilemanager = pcallback;
         pdoc->get_filemanager_data()->m_pmanager = pdoc;
         pdoc->get_filemanager_data()->m_pmanagerMain = pdoc;
         pdoc->get_filemanager_data()->m_pschema = this;
         pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
         pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;

         return pdoc;
      }
      return NULL;
   }


   sp(document) schema::open_child(bool bMakeVisible, bool bTransparentBackground, sp(::user::interaction) pwndParent, ::filemanager::data * pfilemanagerdata)
   {
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = pwndParent;
      sp(document) pdoc = (m_pdoctemplateChild->open_document_file(createcontext));
      if (pdoc != NULL)
      {
         if (pfilemanagerdata == NULL)
         {
            pfilemanagerdata = new ::filemanager::data(get_app());
         }
         pdoc->set_filemanager_data(pfilemanagerdata);
         pdoc->get_filemanager_data()->m_pcallback = m_pfilemanager;
         pdoc->get_filemanager_data()->m_pfilemanager = m_pfilemanager;
         pdoc->get_filemanager_data()->m_pmanager = pdoc;
         pdoc->get_filemanager_data()->m_pmanagerMain = pdoc;
         pdoc->get_filemanager_data()->m_pschema = this;
         pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
         pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;
         pdoc->get_filemanager_data()->m_bTransparentBackground = bTransparentBackground;
         string strId;
         strId.Format("%s::(%d)", Session.filemanager().m_idFileManager.str(), pdoc->get_filemanager_data()->m_iDocument);
         pdoc->get_filemanager_data()->m_strDISection = strId;
         pdoc->Initialize(bMakeVisible);
         return pdoc;
      }
      return NULL;
   }


   sp(document) schema::open_child_list(bool bMakeVisible, bool bTransparentBackground, sp(::user::interaction) pwndParent, ::filemanager::data * pfilemanagerdata)
   {
      UNREFERENCED_PARAMETER(bMakeVisible);
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = pwndParent;
      sp(document) pdoc = (m_pdoctemplateChildList->open_document_file(createcontext));
      if (pdoc != NULL)
      {
         //      pdoc->get_filemanager_data()->m_uiMenuBar = m_uiMenuBar;
         //      pdoc->get_filemanager_data()->m_uiToolBar = m_uiToolBar;
         if (pfilemanagerdata == NULL)
         {
            pfilemanagerdata = new ::filemanager::data(get_app());
         }
         pdoc->set_filemanager_data(pfilemanagerdata);
         pdoc->get_filemanager_data()->m_pcallback = m_pfilemanager;
         pdoc->get_filemanager_data()->m_pfilemanager = m_pfilemanager;
         pdoc->get_filemanager_data()->m_pmanager = pdoc;
         pdoc->get_filemanager_data()->m_pmanagerMain = pdoc;
         pdoc->get_filemanager_data()->m_pschema = this;
         pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
         pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;
         pdoc->get_filemanager_data()->m_bTransparentBackground = bTransparentBackground;

         //pdoc->CreateViews();

         return pdoc;
      }
      return NULL;
   }

   void schema::Initialize(int32_t iTemplate, const char * pszMatter)
   {
      m_iTemplate = iTemplate;
      m_pdoctemplateMain = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < document >(),
         System.type_info < main_frame >(),       // main SDI frame window
         System.type_info < tab_view >());

      m_pdoctemplate = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < document >(),
         System.type_info < frame >(),
         System.type_info < a_view >());

      m_pdoctemplateChild = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < document >(),
         System.type_info < child_frame >(),
         System.type_info < a_view >());

      m_pdoctemplateChildList = new ::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < document >(),
         System.type_info < child_frame >(),
         System.type_info < file_list >());
   }



} // namespace filemanager




