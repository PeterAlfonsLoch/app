//#include "framework.h"


namespace filemanager
{


   manager_template::manager_template(::aura::application * papp) :
      object(papp)
   {

      m_iTemplate = -1;

      m_pfilelistcallback = NULL;

      m_iNextDocument = 0;

      m_pdoctemplate = NULL;
      m_pdoctemplateChild = NULL;
      m_pdoctemplateChildList = NULL;
      m_pdoctemplateFolderSelectionList = NULL;

   }

   manager_template::~manager_template()
   {
      if (m_pdoctemplate != NULL)
      {
         m_pdoctemplate.release();
      }
   }

   sp(manager) manager_template::open(sp(::create) pcreatecontext,::fs::data * pdata,::filemanager::data * pfilemanagerdataParam,callback * pcallback)
   {
      
      sp(::filemanager::data) pfilemanagerdata(pfilemanagerdataParam);

      if (pcreatecontext.is_null())
         pcreatecontext.alloc(allocer());

      if (pfilemanagerdata.is_null())
      {

         pfilemanagerdata = canew(::filemanager::data(get_app()));
         pfilemanagerdata->m_pcallback = pcallback != NULL ? pcallback : &Session.filemanager();
         pfilemanagerdata->m_iTemplate = m_iTemplate;
         pfilemanagerdata->m_iDocument = m_iNextDocument++;
         pfilemanagerdata->m_bTransparentBackground = pcreatecontext == NULL ? true : pcreatecontext->m_bTransparentBackground;
         string strId;
         strId.Format("filemanager(%d)", pfilemanagerdata->m_iDocument);
         pfilemanagerdata->m_strDISection = m_strDISection + "." + strId;
         pfilemanagerdata->m_bFileSize = true;


      }

      pfilemanagerdata->m_pmanagertemplate = this;

      pcreatecontext->oprop("filemanager::data") = pfilemanagerdata;

      sp(manager) pdoc = (m_pdoctemplateMain->open_document_file(pcreatecontext));

      if (pdoc != NULL)
      {

         pdoc->Initialize(pcreatecontext == NULL ? true : pcreatecontext->m_bMakeVisible);

         return pdoc;

      }

      return NULL;

   }

   sp(manager) manager_template::create_new_document(callback * pcallback, sp(::create) pcreatecontext)
   {

      sp(manager) pdoc = (m_pdoctemplate->create_new_document(pcreatecontext));

      if (pdoc != NULL)
      {

         pdoc->get_filemanager_data()->m_pcallback = pcallback;
         pdoc->get_filemanager_data()->m_pfilemanager = pcallback;
         pdoc->get_filemanager_data()->m_pmanager = pdoc;
         pdoc->get_filemanager_data()->m_pmanagerMain = pdoc;
         pdoc->get_filemanager_template() = this;
         pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
         pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;

         return pdoc;
      }
      return NULL;
   }


   sp(manager) manager_template::open_child(bool bMakeVisible,bool bTransparentBackground,sp(::user::interaction) pwndParent,::filemanager::data * pfilemanagerdata,callback * pcallback)
   {

      if(pfilemanagerdata == NULL)
      {

         pfilemanagerdata = canew(::filemanager::data(get_app()));

      }

      sp(::create) createcontext(pfilemanagerdata->allocer());
      
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = pwndParent;
      createcontext->oprop("filemanager::data") = pfilemanagerdata;

      pfilemanagerdata->m_pmanagertemplate = this;
      if(pfilemanagerdata->m_pcallback == NULL || pcallback != NULL)
      {
         pfilemanagerdata->m_pcallback = pcallback != NULL ? pcallback : &Session.filemanager();
      }
      pfilemanagerdata->m_pfilemanager = &Session.filemanager();
      pfilemanagerdata->m_iTemplate = m_iTemplate;
      pfilemanagerdata->m_iDocument = m_iNextDocument++;
      pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;

      sp(manager) pdoc = (m_pdoctemplateChild->open_document_file(createcontext));

      if(pdoc == NULL)
         return NULL;

      if(pdoc->get_filemanager_data()->m_strDISection.is_empty())
      {

         string strId;
         strId.Format("%s::(%d)",Session.filemanager().m_idFileManager.str(),pdoc->get_filemanager_data()->m_iDocument);
         pdoc->get_filemanager_data()->m_strDISection = strId;

      }

      pdoc->Initialize(bMakeVisible);

      return pdoc;
      
   }


   sp(manager) manager_template::open_child_list(bool bMakeVisible,bool bTransparentBackground,sp(::user::interaction) pwndParent,::filemanager::data * pfilemanagerdata,callback * pcallback)
   {
      
      UNREFERENCED_PARAMETER(bMakeVisible);

      sp(::create) createcontext(allocer());

      createcontext->m_bMakeVisible = false;

      createcontext->m_puiParent = pwndParent;

      if(pfilemanagerdata == NULL)
      {

         pfilemanagerdata = canew(::filemanager::data(get_app()));

      }

      createcontext->oprop("filemanager::data") = pfilemanagerdata;


      pfilemanagerdata->m_pmanagertemplate = this;
      pfilemanagerdata->m_pcallback = pcallback != NULL ? pcallback : &Session.filemanager();
      pfilemanagerdata->m_pfilemanager = &Session.filemanager();
      pfilemanagerdata->m_iTemplate = m_iTemplate;
      pfilemanagerdata->m_iDocument = m_iNextDocument++;
      pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;


      sp(manager) pdoc = (m_pdoctemplateChildList->open_document_file(createcontext));

      if(pdoc == NULL)
      {

         return NULL;

      }

      if(pdoc == NULL)
         return NULL;

      pdoc->get_filemanager_data()->m_pmanager = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain = pdoc;

      if(pdoc->get_filemanager_data()->m_strDISection.is_empty())
      {

         string strId;
         strId.Format("%s::(%d)",Session.filemanager().m_idFileManager.str(),pdoc->get_filemanager_data()->m_iDocument);
         pdoc->get_filemanager_data()->m_strDISection = strId;

      }

      pdoc->Initialize(bMakeVisible);

      return pdoc;

   }


   sp(manager) manager_template::open_folder_selection_list(bool bMakeVisible,bool bTransparentBackground,sp(::user::interaction) pwndParent,::filemanager::data * pfilemanagerdata,callback * pcallback)
   {

      UNREFERENCED_PARAMETER(bMakeVisible);

      sp(::create) createcontext(allocer());

      createcontext->m_bMakeVisible = false;

      createcontext->m_puiParent = pwndParent;

      if(pfilemanagerdata == NULL)
      {

         pfilemanagerdata = canew(::filemanager::data(get_app()));

      }

      createcontext->oprop("filemanager::data") = pfilemanagerdata;


      pfilemanagerdata->m_pmanagertemplate = this;
      pfilemanagerdata->m_pcallback = pcallback != NULL ? pcallback : &Session.filemanager();
      pfilemanagerdata->m_pfilemanager = &Session.filemanager();
      pfilemanagerdata->m_iTemplate = m_iTemplate;
      pfilemanagerdata->m_iDocument = m_iNextDocument++;
      pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;

      sp(manager) pdoc = (m_pdoctemplateFolderSelectionList->open_document_file(createcontext));

      if(pdoc == NULL)
         return NULL;

      pdoc->get_filemanager_data()->m_pmanager = pdoc;

      pdoc->get_filemanager_data()->m_pmanagerMain = pdoc;

      if(pdoc->get_filemanager_data()->m_strDISection.is_empty())
      {

         string strId;

         strId.Format("%s::(%d)",Session.filemanager().m_idFileManager.str(),pdoc->get_filemanager_data()->m_iDocument);

         pdoc->get_filemanager_data()->m_strDISection = strId;

      }

      pdoc->Initialize(bMakeVisible);

      return pdoc;

   }


   void manager_template::Initialize(int32_t iTemplate, const char * pszMatter)
   {

      if (m_pdoctemplateMain.is_set())
         return;
      
      m_iTemplate = iTemplate;

      m_pdoctemplateMain = canew(::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < manager >(),
         System.type_info < main_frame >(),       // main SDI frame window
         System.type_info < tab_view >()));

      Application.add_document_template(m_pdoctemplateMain);

      m_pdoctemplate = canew(::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < manager >(),
         System.type_info < frame >(),
         System.type_info < view >()));

      Application.add_document_template(m_pdoctemplate);

      m_pdoctemplateChild = canew(::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < manager >(),
         System.type_info < child_frame >(),
         System.type_info < view >()));

      Application.add_document_template(m_pdoctemplateChild);

      m_pdoctemplateChildList = canew(::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < manager >(),
         System.type_info < child_frame >(),
         System.type_info < file_list >()));

      Application.add_document_template(m_pdoctemplateChildList);

      m_pdoctemplateFolderSelectionList = canew(::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < manager >(),
         System.type_info < child_frame >(),
         System.type_info < folder_selection_list_view >()));

      Application.add_document_template(m_pdoctemplateFolderSelectionList);

   }



} // namespace filemanager




