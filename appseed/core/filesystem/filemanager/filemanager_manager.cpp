//#include "framework.h"



namespace filemanager
{

   
   int get_manager_id_byte_len()
   {

      return 16;

   }
   

   int get_manager_id_len()
   {

      return get_manager_id_byte_len() * 2;

   }


   string create_manager_id(::aura::application * papp)
   {

      memory mem;

      mem.allocate(get_manager_id_byte_len());

      Sys(papp).math().random_bytes(mem.get_data(), mem.get_size());

      return mem.to_hex().uppered();

   }


   bool is_valid_manager_id(const char * psz)
   {

      ::count c = 0;

      while(*psz != '\0')
      {

         if (*psz >= '0' && *psz <= '9')
         {
         }
         else if (*psz >= 'A' && *psz <= 'F')
         {
         }
         else
         {
            return false;
         }

         psz++;
         c++;
         if (c > get_manager_id_len())
         {
            return false;
         }
      }
      return c == get_manager_id_len();
   }

   bool is_valid_filemanager_project_entry(const char * psz)
   {

      ::count c = 0;

      while (*psz != '\0')
      {

         if (*psz >= '0' && *psz <= '9')
         {
         }
         else if (*psz >= 'A' && *psz <= 'F')
         {
         }
         else
         {
            return false;
         }

         psz++;
         c++;
         if (c >= get_manager_id_len())
         {
            if (*psz == ':')
            {
               return true;
            }
            else
            {
               return false;
            }
         }
      }
      return false;

   }
   
   
   ::file::path get_filemanager_project_entry(string & strManagerId, const char * psz, ::aura::application * papp)
   {

      if (is_valid_filemanager_project_entry(psz))
      {

         strManagerId = string(psz, get_manager_id_len());

         return psz + get_manager_id_len() + 1;

      }
      else
      {

         strManagerId = create_manager_id(papp);

         return psz;

      }

   }


   manager::manager(::aura::application * papp):
      object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      ::userfs::document(papp)
   {
      m_bFullBrowse = false;
      m_pfilewatcherlistenerthread = NULL;

         command_signalid id;

         connect_update_cmd_ui("levelup",&manager::_001OnUpdateLevelUp);
         connect_command("levelup",&manager::_001OnLevelUp);
         connect_update_cmd_ui("add_location",&manager::_001OnUpdateAddLocation);
         connect_command("add_location",&manager::_001OnAddLocation);
         connect_update_cmd_ui("replace_text_in_file_system",&manager::_001OnUpdateReplaceText);
         connect_command("replace_text_in_file_system",&manager::_001OnReplaceText);
         connect_update_cmd_ui("edit_paste",&manager::_001OnUpdateEditPaste);
         connect_command("edit_paste",&manager::_001OnEditPaste);
         connect_update_cmd_ui("file_save",&manager::_001OnUpdateFileSaveAs);
         connect_command("file_save",&manager::_001OnFileSaveAs);
         connect_update_cmd_ui("cancel",&manager::_001OnUpdateEditPaste);
         connect_command("cancel",&manager::_001OnEditPaste);
         connect_update_cmd_ui("new_manager", &manager::_001OnUpdateNewManager);
         connect_command("new_manager", &manager::_001OnNewManager);
         connect_update_cmd_ui("del_manager", &manager::_001OnUpdateDelManager);
         connect_command("del_manager", &manager::_001OnDelManager);
         connect_update_cmd_ui("new_folder", &manager::_001OnUpdateNewFolder);
         connect_command("new_folder", &manager::_001OnNewFolder);

//         m_bInitialBrowsePath = true;

      }

   manager::~manager()
   {
   }



   bool manager::FileManagerBrowse(sp(::fs::item) item, ::action::context actioncontext)
   {

      if (m_fsset->m_spafsdata.is_empty())
      {

         m_fsset->m_spafsdata.remove_all();

         m_fsset->m_spafsdata.add(Session.fs());

         ::file::listing listing(m_fsset);

         m_fsset->root_ones(listing);

      }

      string strOldPath;


      if (m_item.is_set())
      {
         
         strOldPath = m_item->m_filepath;

      }

      try
      {

         m_item = canew(::fs::item(*item));

         if(get_fs_data()->is_link(m_item->m_filepath))
         {

            string strFolder;

            string strParams;
            
            System.file().resolve_link(m_item->m_filepath, strFolder, strParams, m_item->m_filepath);

         }

         OnFileManagerBrowse(::action::source::sync(actioncontext));

      }
      catch (string & str)
      {

         if (str == "uifs:// You have not logged in!")
         {

            Application.simple_message_box(NULL, "You have not logged in! Cannot access your User Intelligent File System - uifs://");

            // assume can resume at least from this exception one time

            m_item = canew(::fs::item(strOldPath));

            OnFileManagerBrowse(::action::source::sync(actioncontext));

         }

         return false;

      }

      if (m_pfilewatcherlistenerthread != NULL)
      {

         ::multithreading::post_quit(m_pfilewatcherlistenerthread);

      }

      if (m_item->m_filepath.has_char())
      {

         m_pfilewatcherlistenerthread = new ::file_watcher::listener_thread(get_app());

         try
         {

            m_pfilewatcherlistenerthread->add_file_watch(m_item->m_filepath, this, false);

         }
         catch (...)
         {

         }



      }

      return true;

   }

   bool manager::FileManagerBrowse(const char * lpcszPath, ::action::context actioncontext)
   {

      FileManagerBrowse(canew(::fs::item(lpcszPath)), actioncontext);

      return false;

   }

   void manager::FileManagerOneLevelUp(::action::context actioncontext)
   {

      if (get_filemanager_item().m_filepath.is_empty())
         return;

      string strParent = get_filemanager_item().m_filepath.up();

      FileManagerBrowse(strParent, ::action::source::sync(actioncontext));

   }


   ::fs::item & manager::get_filemanager_item()
   {

      return *m_item;

   }


   sp(manager_template) manager::get_filemanager_template()
   {

      return get_filemanager_data()->get_filemanager_template();

   }


   sp(::filemanager::data) manager::get_filemanager_data()
   {


      return m_spfilemanagerdata;


   }


   sp(::fs::data) manager::get_fs_data()
   {


      return m_fsset;


   }


   sp(manager) manager::get_main_manager()
   {

	   sp(tab_view) ptabview = get_typed_view < tab_view >();

	   if (ptabview.is_set())
	   {

         for (index i = 0; i < ptabview->get_pane_count(); i++)
         {

            ::user::tab_pane * ptabpane = ptabview->get_pane(i);

            if (ptabpane != NULL && ptabpane->m_pholder != NULL)
            {

               sp(child_frame) pchildframe = ptabpane->m_pholder->first_child();

               if (pchildframe.is_set())
               {

                  sp(manager) pdoc = pchildframe->GetActiveDocument();

                  if (pdoc.is_set())
                  {

                     return pdoc;

                  }

               }

            }

         }

	   }

	   return this;

   }


   bool manager::set_filemanager_data(::filemanager::data * pdata)
   {


      m_spfilemanagerdata = pdata;


      return true;


   }

   void manager::defer_check_manager_id(string strManagerId)
   {

      if (Session.filemanager().std().m_pathFilemanagerProject.has_char())
      {

         if (!is_valid_manager_id(m_strManagerId) || is_valid_manager_id(strManagerId))
         {

            if (is_valid_manager_id(strManagerId))
            {

               m_strManagerId = strManagerId;

            }
            else
            {

               m_strManagerId = create_manager_id(get_app());

            }

            m_dataid = string(Application.m_dataid.m_id.m_psz) + "/filemanager/document/" + m_strManagerId;

            sp(main_frame) pframe = get_view()->GetTypedParent < main_frame >();

            if (pframe.is_set())
            {

               pframe->m_dataid = string(Application.m_dataid.m_id.m_psz) + "/filemanager/main_frame/" + m_strManagerId;

            }


         }

         sp(manager) pdoc = get_main_manager();

         if (pdoc.is_set() && pdoc.m_p != this && pdoc->m_strManagerId != m_strManagerId)
         {

            pdoc->defer_check_manager_id(m_strManagerId);

         }

      }

   }


   critical_section * manager::GetItemIdListCriticalSection()
   {
      return &m_csItemIdListAbsolute;
   }


   void manager::FileManagerTopicOK()
   {
   }

   void manager::FileManagerTopicCancel()
   {
   }


   string manager::calc_data_key(::database::id & id)
   {
      string str;
      str += m_dataid.m_id;
      str += ".";
      str += id.m_id;
      return str;
   }


   bool manager::on_new_document()
   {

      if(!::user::document::on_new_document())
         return FALSE;

      defer_check_manager_id();

      return TRUE;

   }


   bool manager::on_open_document(var varFile)
   {

      string strManagerId;

      m_filepath = get_filemanager_project_entry(strManagerId, varFile.get_string(), get_app());

      defer_check_manager_id(strManagerId);

      return true;

   }


   void manager::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void manager::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }

   /////////////////////////////////////////////////////////////////////////////
   // manager serialization
   /*
   void manager::Serialize(CArchive& ar)
   {
   if (ar.IsStoring())
   {
   // TODO: add storing code here
   }
   else
   {
   // TODO: add loading code here
   }
   }
   */
   /////////////////////////////////////////////////////////////////////////////
   // manager commands


   void manager::start_full_browse(string strPath, ::action::context actioncontext)
   {

      if(!get_fs_data()->is_zero_latency(strPath))
      {

         update_hint uh;
         uh.set_type(update_hint::TypeSynchronizePath);
         uh.m_actioncontext = ::action::source::system(::action::source::sync(actioncontext));
         uh.m_filepath = strPath;
         update_all_views(NULL,0,&uh);

      }

      ::fork(get_app(), [=]()
      {

         full_browse(strPath, actioncontext);

      });

   }


   void manager::full_browse(string strPath, ::action::context actioncontext)
   {

      if (m_bFullBrowse)
      {

         return;

      }

      keep <bool> keepFullBrowse(&m_bFullBrowse, true, false, true);

      browse(strPath, actioncontext);

      update_hint uh;
      uh.set_type(update_hint::TypeSynchronizePath);
      uh.m_actioncontext = ::action::source::sync(actioncontext);
      uh.m_filepath = strPath;
      update_all_views(NULL,0,&uh);

   }

   void manager::OnFileManagerBrowse(::action::context actioncontext)
   {

      string strPath = m_item->m_filepath;

      start_full_browse(strPath, actioncontext);

      if(actioncontext.is_user_source())
      {

         if(::str::begins(strPath,astr.strUifsProtocol)
            || ::str::begins(strPath,astr.strFsProtocol))
         {
            
            if (Session.filemanager().std().m_pathFilemanagerProject.is_empty())
            {

               data_set(".local://InitialBrowsePath", strPath);

            }
            else
            {

               Session.filemanager().std().save_filemanager_project();

            }

         }
         else
         {


            if (Session.filemanager().std().m_pathFilemanagerProject.is_empty())
            {

               id idMachine;

#ifdef LINUX
               idMachine = "Linux";
#elif defined(WINDOWSEX)
               idMachine = "Windows Desktop";
#endif

               data_set(".local://InitialBrowsePath", "machinefs://");
               data_set(".local://InitialBrowsePath." + idMachine, strPath);
//               data_set(".local://InitialBrowsePath", strPath);

            }
            else
            {

               Session.filemanager().std().save_filemanager_project();

            }


         }

      }

   }


   void manager::OpenSelectionProperties()
   {
      {
         update_hint uh;
         uh.set_type(update_hint::TypeOpenSelectionProperties);
         update_all_views(NULL,0,&uh);
      }

   }


   bool manager::on_simple_action(id id)
   {

      if(get_filemanager_data() != NULL
         && get_filemanager_template() != NULL)
      {
         //         ::schema * ptemplate = get_filemanager_template();
         if(id == get_filemanager_template()->m_strLevelUp)
         {
            FileManagerOneLevelUp(::action::source_user);
            return true;
         }
      }
      return ::user::document::on_simple_action(id);
   }

   bool manager::on_simple_update(cmd_ui * pcmdui)
   {
      /*if(pcmdui->m_id == get_filemanager_template()->m_strLevelUp)
      {
      FileManagerOnUpdateLevelUp(pcmdui);
      return true;
      }*/
      return ::user::document::on_simple_update(pcmdui);
   }


   /*bool manager::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)
   {
   if (nCode == CN_UPDATE_COMMAND_UI)
   {
   cmd_ui * pcmdui = (cmd_ui *) pExtra;
   if(nID == get_filemanager_template()->m_uiLevelUp)
   {
   FileManagerOnUpdateLevelUp(pcmdui);
   return TRUE;
   }
   }
   else
   {
   int32_t nMsg = HIWORD(nCode);
   nCode = LOWORD(nCode);

   // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
   if (nMsg == 0)
   nMsg = WM_COMMAND;

   if(nMsg == WM_COMMAND)
   {
   if(nID == get_filemanager_template()->m_uiLevelUp)
   {
   FileManagerOnLevelUp();
   return TRUE;
   }
   }
   }*/
   /*   return ::user::document::_001OnCmdMsg(pcmdmsg);
   }
   */

   void manager::_001OnUpdateNewManager(signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);

      pcmdui->m_pcmdui->Enable(TRUE);

      pobj->m_bRet = true;

   }


   void manager::_001OnNewManager(signal_details * pobj)
   {

      Session.filemanager().std().add_manager("", canew(::create(Application.creation())));

      pobj->m_bRet = true;

   }


   void manager::_001OnUpdateDelManager(signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);

      pcmdui->m_pcmdui->Enable(TRUE);

      pobj->m_bRet = true;

   }


   void manager::_001OnDelManager(signal_details * pobj)
   {

      sp(manager) pdoc = this;

      sp(view) pview = get_typed_view<view>();

      if (pview.is_set())
      {

         sp(tab_view) ptabview = pview->GetTypedParent <tab_view>();

         if (ptabview.is_set())
         {

            pdoc = ptabview->get_document();

         }

      }

      Session.filemanager().std().remove_manager(pdoc.m_p);

      pobj->m_bRet = true;

   }


   void manager::_001OnUpdateLevelUp(signal_details * pobj)
   {
      
      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);

      if(m_item.is_null() || m_item->m_filepath.is_empty())
      {

         pcmdui->m_pcmdui->Enable(FALSE);

      }
      else
      {

         pcmdui->m_pcmdui->Enable(TRUE);

      }

      pobj->m_bRet = true;

   }


   void manager::_001OnLevelUp(signal_details * pobj)
   {
      FileManagerOneLevelUp(::action::source_user);
      pobj->m_bRet = true;
   }


   void manager::_001OnUpdateAddLocation(signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);

         pcmdui->m_pcmdui->Enable(TRUE);

      pobj->m_bRet = true;

   }


   void manager::_001OnAddLocation(signal_details * pobj)
   {

      update_all_views(NULL,::user::impact::hint_add_location,NULL);

      pobj->m_bRet = true;

   }


   void manager::_001OnUpdateReplaceText(signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);

      pcmdui->m_pcmdui->Enable(TRUE);

      pobj->m_bRet = true;

   }


   void manager::_001OnReplaceText(signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
      update_all_views(NULL,hint_replace_name,NULL);

      pobj->m_bRet = true;

   }


   void manager::_001OnUpdateNewFolder(signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);

      pcmdui->m_pcmdui->Enable(TRUE);

      pobj->m_bRet = true;

   }


   void manager::_001OnNewFolder(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      update_all_views(NULL, hint_new_folder, NULL);

      pobj->m_bRet = true;

   }


   void manager::_001OnUpdateEditPaste(signal_details * pobj)
   {
      //      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);

      //         pcmdui->m_pcmdui->Enable(System.m_strCopy.is_empty());
      pobj->m_bRet = true;
   }

   void manager::_001OnEditPaste(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //System.file().paste(get_filemanager_data()->get_filemanager_item().m_strPath, System.m_strCopy);
      //update_all_views(NULL, 123, NULL);
      //pobj->m_bRet = true;
   }

   void manager::_001OnUpdateFileSaveAs(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj);
         pcmdui->m_pcmdui->Enable(TRUE);
   }

   void manager::_001OnUpdateFileImport(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void manager::_001OnUpdateFileExport(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj);
      pcmdui->m_pcmdui->Enable(TRUE);
   }


   void manager::_001OnFileSaveAs(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if(m_emode == mode_saving || m_emode == mode_export)
      {
         update_hint uh;
         uh.m_pmanager = this;
         uh.set_type(update_hint::TypeTopicOK);
         update_all_views(NULL,0,&uh);
      }
      pobj->m_bRet = true;
   }

   void manager::_001OnFileImport(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if (m_emode == mode_import)
      {
         update_hint uh;
         uh.m_pmanager = this;
         uh.set_type(update_hint::TypeTopicOK);
         update_all_views(NULL, 0, &uh);
      }

   }


   void manager::_001OnFileExport(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if (m_emode == mode_saving)
      {
         update_hint uh;
         uh.m_pmanager = this;
         uh.set_type(update_hint::TypeTopicOK);
         update_all_views(NULL, 0, &uh);
      }

   }

   void manager::Initialize(bool bMakeVisible, const ::file::path & path)
   {

      CreateViews();

      update_hint uh;

      uh.m_pmanager = this;

      FileManagerBrowse(path, ::action::source::database_default());

      uh.set_type(update_hint::TypeCreateBars);

      update_all_views(NULL, 0, &uh);

      if (bMakeVisible)
      {

         uh.set_type(update_hint::TypePop);

         update_all_views(NULL, 0, &uh);

      }

   }


   void manager::Initialize(bool bMakeVisible, bool bInitialBrowsePath)
   {

      //m_bInitialBrowsePath = true;

      string str;
      
      str.Format("manager(%s)",get_filemanager_data()->m_strDISection);
      
      m_dataid = str;

      CreateViews();

      update_hint uh;

      uh.m_pmanager = this;

      if (bInitialBrowsePath)
      {

         if (data_get(".local://InitialBrowsePath", str))
         {

            if (str == "machinefs://")
            {

               id idMachine;

#ifdef LINUX
               idMachine = "Linux";
#elif defined(WINDOWSEX)
               idMachine = "Windows Desktop";
#endif

               if (data_get(".local://InitialBrowsePath." + idMachine, str))
               {
                  
                  FileManagerBrowse(str, ::action::source::database_default());

               }
               else
               {

                  FileManagerBrowse("", ::action::source::system_default());

               }

            }
            else
            {
            
               FileManagerBrowse(str, ::action::source::database_default());

            }

         }
         else if (get_filemanager_template()->m_pathDefault.has_char())
         {

            FileManagerBrowse(get_filemanager_template()->m_pathDefault, ::action::source_initialize);

         }
         else
         {
            
            FileManagerBrowse("", ::action::source::system_default());

         }

      }

      uh.set_type(update_hint::TypeCreateBars);
      update_all_views(NULL,0,&uh);

      if(bMakeVisible)
      {
         uh.set_type(update_hint::TypePop);
         update_all_views(NULL,0,&uh);
      }

   }


   void manager::OpenFolder(sp(::fs::item) item,::action::context actioncontext)
   {
      
      FileManagerBrowse(item,actioncontext);

   }


   void manager::CreateViews()
   {

      /*{

      ::user::view_update_hint uh(get_app());

      uh.oprop("manager") = this;
      uh.m_ehint = ::user::view_update_hint::hint_create_views;
      update_all_views(NULL, 0, &uh);

      }*/

      update_hint uh;

      uh.set_type(update_hint::TypeInitialize);
      uh.m_uiId = get_filemanager_data()->m_iDocument;
      uh.m_pmanager = this;
      update_all_views(NULL,0,&uh);

      uh.set_type(update_hint::TypeSynchronizeLocations);
      uh.m_uiId = get_filemanager_data()->m_iDocument;
      uh.m_pmanager = this;
      uh.m_actioncontext = ::action::source_sync;
      update_all_views(NULL,0,&uh);


   }

   void manager::PopViews()
   {
      update_hint uh;
      uh.m_uiId = get_filemanager_data()->m_iDocument;
      uh.m_pmanager = this;
      uh.set_type(update_hint::TypeCreateBars);
      update_all_views(NULL,0,&uh);

      uh.set_type(update_hint::TypePop);

      update_all_views(NULL,0,&uh);
   }

   bool manager::HandleDefaultFileManagerItemCmdMsg(::aura::cmd_msg * pcmdmsg,::fs::item_array & itema)
   {
      if(pcmdmsg->m_etype == ::aura::cmd_msg::type_cmdui)
      {
         if(get_filemanager_data()->m_pcallback->GetFileManagerItemCallback(
            get_filemanager_data(),pcmdmsg->m_pcmdui->m_id,itema))
         {
            get_filemanager_data()->m_pcallback->OnFileManagerItemUpdate(
               get_filemanager_data(),pcmdmsg->m_pcmdui,itema);
            return TRUE;
         }
      }
      else
      {
         if(get_filemanager_data()->m_pcallback->GetFileManagerItemCallback(
            get_filemanager_data(),pcmdmsg->m_id,itema))
         {
            get_filemanager_data()->m_pcallback->OnFileManagerItemCommand(
               get_filemanager_data(),pcmdmsg->m_id,itema);
            return true;
         }
      }
      return false;
   }


   sp(operation_document) manager::get_operation_doc(bool bSwitch)
   {

      ::filemanager::tab_view * ptabview = Session.filemanager().std().m_pdoctemplateMain->get_document(0)->get_typed_view < ::filemanager::tab_view >();

      if(ptabview == NULL)
         return NULL;

      ASSERT(ptabview != NULL);

      if(ptabview != NULL)
      {

         if(bSwitch)
         {

            ptabview->set_cur_tab_by_id("filemanager::operation");

         }
         else
         {

            ptabview->create_tab_by_id("filemanager::operation");

         }

         return ptabview->get("filemanager::operation")->m_pdoc;

      }

      return NULL;

   }


   void manager::GetActiveViewSelection(::fs::item_array & itema)
   {
      update_hint uh;
      uh.set_type(update_hint::TypeGetActiveViewSelection);
      update_all_views(NULL,0,&uh);
      itema = uh.m_itemaSelected;
   }


   void manager::FileManagerSaveAs(::user::document * pdocument)
   {

      get_filemanager_data()->m_pdocumentTopic = pdocument;

      m_emode = mode_saving;

      update_hint uh;
      uh.m_pmanager = this;
      uh.set_type(update_hint::TypeTopicStart);
      update_all_views(NULL,0,&uh);
      uh.set_type(update_hint::TypeCreateBars);
      update_all_views(NULL,0,&uh);

   }


   void manager::FileManagerImport(::user::document * pdocument)
   {

      get_filemanager_data()->m_pdocumentTopic = pdocument;

      m_emode = mode_import;

      update_hint uh;
      uh.m_pmanager = this;
      uh.set_type(update_hint::TypeTopicStart);
      update_all_views(NULL, 0, &uh);
      uh.set_type(update_hint::TypeCreateBars);
      update_all_views(NULL, 0, &uh);

   }


   void manager::FileManagerExport(::user::document * pdocument)
   {

      get_filemanager_data()->m_pdocumentTopic = pdocument;

      m_emode = mode_export;

      update_hint uh;
      uh.m_pmanager = this;
      uh.set_type(update_hint::TypeTopicStart);
      update_all_views(NULL, 0, &uh);
      uh.set_type(update_hint::TypeCreateBars);
      update_all_views(NULL, 0, &uh);

   }



   void manager::on_create(sp(::create) pcreatecontext)
   {

      ::user::document::on_create(pcreatecontext);

      m_spfilemanagerdata = pcreatecontext->oprop("filemanager::data").cast < ::filemanager::data >();

      if(m_spfilemanagerdata.is_null())
      {

         sp(manager_template) ptemplate = pcreatecontext->oprop("filemanager::template").cast < manager_template >();

         if (ptemplate.is_null())
         {

            m_spfilemanagerdata = canew(data(get_app()));

         }
         else
         {

            m_spfilemanagerdata = ptemplate->create_file_manager_data(pcreatecontext);

         }

      }

      m_spfilemanagerdata->m_pmanager = this;

      m_spfilemanagerdata->m_pmanagerMain = this;

   }


   bool manager::on_create_bars(simple_frame_window * pframe)
   {

      string strToolbar;

      strToolbar = get_filemanager_template()->m_setToolbar[m_emode];

      if(!pframe->LoadToolBar("filemanager", strToolbar))
      {
         
         TRACE0("Failed to create filemanager toolbar\n");

         return false;      // fail to create

      }

      return true;

   }

   
   void manager::handle_file_action(::file_watcher::file_watch_id watchid, const char * dir, const char * filename, ::file_watcher::e_action action)
   {

      OnFileManagerBrowse(::action::source_sync);

   }


} // namespace filemanager




