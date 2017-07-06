//#include "framework.h"


namespace filemanager
{


   manager_template::manager_template(::aura::application * papp) :
      object(papp)
   {

      m_bRestoring = false;

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

   }


   sp(::filemanager::data) manager_template::create_file_manager_data(::create * pcreate)
   {

      sp(::filemanager::data) pfilemanagerdata(canew(data(get_app())));

      callback * pcallback = NULL;

      if (pcreate != NULL)
      {

         pcallback = pcreate->oprop("filemanager::callback").cast < callback > ();

      }

      pfilemanagerdata->m_pcallback = pcallback != NULL ? pcallback : &Session.filemanager();
      pfilemanagerdata->m_iTemplate = m_iTemplate;
      pfilemanagerdata->m_iDocument = m_iNextDocument++;
      pfilemanagerdata->m_bTransparentBackground = pcreate == NULL ? true : pcreate->m_bTransparentBackground;
      string strId;
      strId.Format("filemanager(%d)", pfilemanagerdata->m_iDocument);
      pfilemanagerdata->m_strDISection = m_strDISection + "." + strId;
      pfilemanagerdata->m_bFileSize = true;
      pfilemanagerdata->m_pmanagertemplate = this;

      return pfilemanagerdata;

   }


   void manager_template::load_filemanager_project(const ::file::path & pathFilemanagerProject, ::create * pcreate, ::fs::data * pdata, data * pfilemanagerdata, callback * pcallback)
   {

      {

         keep < bool > keepRestoring(&m_bRestoring, true, false, true);

         if (pathFilemanagerProject.is_empty() || Application.dir().is(pathFilemanagerProject) 
            || pathFilemanagerProject.extension().compare_ci("filemanager") != 0)
         {

            m_pathFilemanagerProject = ::dir::local() / "localconfig/user.filemanager";

         }
         else
         {

            m_pathFilemanagerProject = pathFilemanagerProject;

         }

         stringa stra;

         {

            mutex m(get_app(), "Local\\ca2-filemanagers");

            synch_lock sl(&m);

            stra.add_lines(Application.file().as_string(m_pathFilemanagerProject), true);

         }

         if (Application.dir().is(pathFilemanagerProject))
         {

            stra.add(create_manager_id(get_app()) + ":" + pathFilemanagerProject);

         }

         if (stra.is_empty())
         {

            stra.add(create_manager_id(get_app()) + ":");

         }

         string strManagerId;

         ::file::path path;

         for (auto str : stra)
         {

            restore_manager(str, pcreate, pdata, pfilemanagerdata, pcallback);

         }

      }

      save_filemanager_project();

   }


   void manager_template::save_filemanager_project()
   {

      if (m_bRestoring)
      {

         return;

      }

      stringa stra;

      sp(manager) pdoc;

      for (index i = 0; i < m_pdoctemplateMain->get_document_count(); i++)
      {

         pdoc = m_pdoctemplateMain->get_document(i);

         if (pdoc.is_null())
         {

            continue;

         }

         pdoc->defer_check_manager_id();

         pdoc = pdoc->get_main_manager();

         if (pdoc.is_null())
         {

            continue;

         }

         stra.add(pdoc->m_strManagerId + ":" + pdoc->get_filemanager_item().m_filepath);

      }

      {

         mutex m(get_app(), "Local\\ca2-filemanagers");

         synch_lock sl(&m);

         Application.file().put_contents(m_pathFilemanagerProject, stra.implode("\r\n"));

      }

   }


   sp(manager) manager_template::find_manager(var varFile)
   {

      sp(manager) pdoc;

      for (index i = 0; i < m_pdoctemplateMain->get_document_count(); i++)
      {

         pdoc = m_pdoctemplateMain->get_document(i);

         if (pdoc.is_null())
         {

            continue;

         }

         pdoc = pdoc->get_main_manager();

		   if (pdoc->m_strManagerId == varFile.get_string().Left(get_manager_id_len()))
		   {

			   return pdoc;

		   }

		   if (pdoc->get_filemanager_item().m_filepath.is_equal(varFile))
		   {

			   return pdoc;

		   }


		}

      return NULL;

   }


   sp(manager) manager_template::open_manager(var varFile, ::create * pcreate, ::fs::data * pdata, ::filemanager::data * pfilemanagerdata, callback * pcallback)
   {

      sp(manager) pdoc;

      if (pcreate == NULL)
      {

         pcreate = canew(::create(Application.creation(), varFile, true));

      }

      pcreate->oprop("filemanager::template") = this;

      pcreate->oprop("filemanager::data") = pfilemanagerdata;

      pcreate->oprop("filemanager::callback") = pcallback;

      pcreate->m_spCommandLine->m_varFile = varFile;

      m_pdoctemplateMain->m_bQueueDocumentOpening = false;

      pdoc = m_pdoctemplateMain->open_document_file(pcreate);

      if (pdoc.is_null())
      {

         return NULL;

      }

      pdoc->Initialize(pcreate == NULL ? true : pcreate->m_bMakeVisible, false);

      tab_view * ptabview = pdoc->get_typed_view < tab_view >();

      if (ptabview != NULL)
      {

         string strManagerId;

         ::file::path pathFolder = get_filemanager_project_entry(strManagerId, varFile, get_app());

         ptabview->set_cur_tab_by_id("verifile://" + pathFolder);

      }

      return pdoc;

   }


   sp(manager) manager_template::restore_manager(var varFile, ::create * pcreate, ::fs::data * pdata, ::filemanager::data * pfilemanagerdata, callback * pcallback)
   {

      sp(manager) pdoc;
      
      pdoc = open_manager(varFile, pcreate, pdata, pfilemanagerdata, pcallback);

      return pdoc;

   }


   sp(manager) manager_template::add_manager(const ::file::path & pathFolder, ::create * pcreate, ::fs::data * pdata, ::filemanager::data * pfilemanagerdata, callback * pcallback)
   {

      sp(manager) pdoc;
      
      pdoc = open_manager(pathFolder, pcreate, pdata, pfilemanagerdata, pcallback);

      if (pdoc == NULL)
      {

         return NULL;

      }

      save_filemanager_project();

      return pdoc;

   }


   bool manager_template::remove_manager(var varFile)
   {

      sp(manager) pdoc = find_manager(varFile);

      m_pdoctemplateMain->remove_document(pdoc);

      save_filemanager_project();

      return pdoc.is_set();

   }


   bool manager_template::remove_manager(manager * pdoc)
   {

      pdoc->close_document();

      //m_pdoctemplateMain->remove_document(pdoc);

      save_filemanager_project();

      return pdoc != NULL;

   }


   sp(manager) manager_template::open_main(::id id, ::create * pcreate,::fs::data * pdata,::filemanager::data * pfilemanagerdata,callback * pcallback)
   {

      ::file::path pathFolder;

      if (pcreate == NULL)
      {

         pcreate = canew(::create(Application.creation()));

      }

      if (pcreate->m_spCommandLine->m_ecommand == ::command_line::command_file_open)
      {

         pathFolder = pcreate->m_spCommandLine->m_varFile;

         if (Application.dir().is(pathFolder))
         {

            pathFolder.m_iDir = 1;

         }
         else
         {

            pathFolder.Empty();

         }

      }


      
      sp(manager) pdoc;

      if (id.int64() < -1 || id.int64() == m_pdoctemplateMain->get_document_count())
      {

         pcreate->oprop("filemanager::template") = this;

         pcreate->oprop("filemanager::data") = pfilemanagerdata;

         pcreate->oprop("filemanager::callback") = pcallback;

         pdoc = m_pdoctemplateMain->open_document_file(pcreate);

         if (pdoc != NULL)
         {

            bool bInitialBrowsePath = true;

            if (pathFolder.m_iDir == 1)
            {

               bInitialBrowsePath = false;

            }

            pdoc->Initialize(pcreate == NULL ? true : pcreate->m_bMakeVisible, bInitialBrowsePath);

         }

      }
      else if (id.int64() < m_pdoctemplateMain->get_document_count())
      {

         pdoc = m_pdoctemplateMain->get_document((index) id);

      }

      if (pdoc != NULL)
      {

         tab_view * ptabview = pdoc->get_typed_view < tab_view >();

         if (pathFolder.m_iDir == 1)
         {

            if (ptabview != NULL)
            {

               ptabview->set_cur_tab_by_id("verifile://" + pathFolder);

            }

         }
         else
         {

            if (ptabview->get_tab_count() <= 0)
            {

               ptabview->set_cur_tab_by_id("0");

            }

         }

      }

      return pdoc;

   }


   sp(manager) manager_template::open(id id, ::create * pcreate, ::fs::data * pdata, ::filemanager::data * pfilemanagerdata, callback * pcallback)
   {

      ::file::path pathFolder;

      if (pcreate == NULL)
      {

         pcreate = canew(::create(Application.creation()));

      }

      if (pcreate->m_spCommandLine->m_ecommand == ::command_line::command_file_open)
      {

         pathFolder = pcreate->m_spCommandLine->m_varFile;

         if (Application.dir().is(pathFolder))
         {

            pathFolder.m_iDir = 1;

         }
         else
         {

            pathFolder.Empty();

         }

      }



      sp(manager) pdoc;

      if (id.int64() < -1 || id.int64() == m_pdoctemplate->get_document_count())
      {

         pcreate->oprop("filemanager::template") = this;

         pcreate->oprop("filemanager::data") = pfilemanagerdata;

         pcreate->oprop("filemanager::callback") = pcallback;

         pdoc = m_pdoctemplate->open_document_file(pcreate);

         if (pdoc != NULL)
         {

            bool bInitialBrowsePath = true;

            if (pathFolder.m_iDir == 1)
            {

               bInitialBrowsePath = false;

            }

            pdoc->Initialize(pcreate == NULL ? true : pcreate->m_bMakeVisible, bInitialBrowsePath);

         }

      }
      else if (id.int64() < m_pdoctemplate->get_document_count())
      {

         pdoc = m_pdoctemplate->get_document((index) id);

      }

      if (pdoc != NULL)
      {

         if (pathFolder.m_iDir == 1)
         {

            pdoc->FileManagerBrowse(pathFolder, ::action::source_user);

         }

      }

      return pdoc;

   }

   sp(manager) manager_template::create_new_document(callback * pcallback, ::create * pcreate)
   {

      sp(manager) pdoc = (m_pdoctemplate->create_new_document(pcreate));

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
         System.type_info < main_frame >(),
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




