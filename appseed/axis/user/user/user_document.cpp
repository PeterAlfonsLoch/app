#include "framework.h"


namespace user
{


   document::document(sp(::axis::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      m_mutex(NULL)
   {

         m_pdocumentemplate = NULL;
         m_bModified = FALSE;
         m_bAutoDelete = TRUE;       // default to auto delete document
         m_bEmbedded = FALSE;        // default to file-based document
         ASSERT(m_viewptra.is_empty());

         m_documentptra.add(this);

   }

   document::~document()
   {
      // do not call delete_contents here !
#ifdef DEBUG
      if (is_modified())
         TRACE(::axis::trace::category_AppMsg, 0, "Warning: destroying an unsaved document.\n");
#endif

      // there should be no views left!
      disconnect_views();
      ASSERT(m_viewptra.is_empty());

      if (m_pdocumentemplate != NULL)
         m_pdocumentemplate->remove_document(this);
      ASSERT(m_pdocumentemplate == NULL);     // must be detached
   }



   bool document::_001OnCmdMsg(::axis::cmd_msg * pcmdmsg)
   {
      if (command_target::_001OnCmdMsg(pcmdmsg))
         return TRUE;

      // otherwise check template
      if (m_pdocumentemplate != NULL &&
         m_pdocumentemplate->_001OnCmdMsg(pcmdmsg))
         return TRUE;

      return FALSE;
   }


   void document::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

      dumpcontext << "m_wstrTitle = " << m_strTitle;
      dumpcontext << "\nm_wstrPathName = " << m_strPathName;
      dumpcontext << "\nm_bModified = " << m_bModified;
      dumpcontext << "\nm_pDocTemplate = " << (void *)m_pdocumentemplate;

      if (dumpcontext.GetDepth() > 0)
      {
         ::count count = get_view_count();
         for (index index = 0; index < count; index++)
         {
            sp(::user::impact) pview = get_view(index);
            dumpcontext << "\nwith ::user::impact " << (void *)pview;
         }
      }

      dumpcontext << "\n";


   }

   void document::assert_valid() const
   {
      ::object::assert_valid();

      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
      }
   }


   void document::on_create(sp(::create_context) pcreatecontext)
   {

      //::user::document::on_alloc(papp);
      ::database::client::initialize_data_client(&Application.dataserver());

   }


   void document::update_title()
   {

      string str = Application.m_strAppName;

      str += " : ";

      str+= m_strPathName;

      sp(frame_window) pframe = get_view(0)->GetParentFrame();

      while(pframe.is_set())
      {
         pframe->SetWindowText(str);
         pframe = pframe->GetParentFrame();
         
      }

   }





   void document::on_final_release()
   {
      on_close_document();  // may 'delete this'
   }

   void document::disconnect_views()
   {
      single_lock sl(&m_mutex, true);
      for (index index = 0; index < m_viewptra.get_count(); index++)
      {
         sp(::user::impact) pview = m_viewptra(index);
         ASSERT_VALID(pview);
         ASSERT_KINDOF(::user::impact, pview);
         pview->m_spdocument->release();
      }
      m_viewptra.remove_all();
   }

   /*void document::on_alloc(sp(::axis::application) papp)
   {
      set_app(papp);
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // document attributes, general services



   void document::set_title(const char * lpszTitle)
   {
      m_strTitle = lpszTitle;
      update_frame_counts();        // will cause name change in views
   }

   void document::delete_contents()
   {
   }


   sp(::user::impact) document::get_view(index index) const
   {
      single_lock sl(&((document *) this)->m_mutex, true);
      if (index < 0 || index >= m_viewptra.get_count())
         return NULL;
      sp(::user::impact) pview = m_viewptra(index);
      ASSERT_KINDOF(::user::impact, pview);
      return pview;
   }

   void document::update_all_views(sp(::user::impact) pSender, LPARAM lHint, ::object * pHint)
      // walk through all views
   {
      ASSERT(pSender == NULL || !m_viewptra.is_empty());
      // must have views if sent by one of them

      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
         if (pview != pSender)
            pview->on_update(pSender, lHint, pHint);
      }
   }

   void document::send_update(sp(::user::impact) pSender, LPARAM lHint, ::object * pHint)
      // walk through all views
   {
      ASSERT(pSender == NULL || !m_viewptra.is_empty());
      // must have views if sent by one of them

      update * pupdate;
      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);

         pupdate = new update;
         pupdate->m_pSender = pSender;
         pupdate->m_lHint = lHint;
         pupdate->m_pHint = pHint;
         if (pview != pSender)
            pview->send_message(WM_VIEW, 0, (LPARAM)pupdate);
      }
   }

   void document::send_initial_update()
      // walk through all views and call OnInitialUpdate
   {
      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
         pview->_001OnInitialUpdate(NULL);
      }
   }

   bool document::is_new_document()
   {
      return m_bNew;
   }

   void document::write(::file::output_stream & ostream)
   {
      UNREFERENCED_PARAMETER(ostream);
   }

   void document::read(::file::input_stream & istream)
   {
      UNREFERENCED_PARAMETER(istream);
   }


   sp(::user::impact) document::get_typed_view(sp(type) info, index indexFind)
   {
      single_lock sl(&m_mutex, true);
      ::count countView = get_view_count();
      ::count countFind = 0;
      sp(::user::impact) pview;
      for (index index = 0; index < countView; index++)
      {
         pview = get_view(index);
         if (*info == typeid(*pview))
         {
            if (indexFind == countFind)
               return pview;
            else
               countFind++;
         }
      }
      return NULL;
   }


   void document::show_all_frames(UINT nCmdShow)
   {
      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         pview->GetParentFrame()->ShowWindow(nCmdShow);
      }
   }


   // document
   const string & document::get_title() const
   {
      ASSERT(this != NULL); return m_strTitle;
   }
   const string & document::get_path_name() const
   {
      ASSERT(this != NULL); return m_strPathName;
   }
   sp(impact_system) document::get_document_template() const
   {
      ASSERT(this != NULL); return m_pdocumentemplate;
   }
   bool document::is_modified()
   {
      ASSERT(this != NULL); return m_bModified;
   }
   void document::set_modified_flag(bool bModified)
   {
      ASSERT(this != NULL); m_bModified = bModified;
   }
   void document::set_new(bool bNew)
   {
      ASSERT(this != NULL);
      m_bNew = bNew;
   }

   /////////////////////////////////////////////////////////////////////////////
   // File/Path commands

   void document::set_path_name(var varFile, bool bAddToMRU)
   {
      UNREFERENCED_PARAMETER(bAddToMRU);
      string strPathName;
      if (varFile.get_type() == var::type_propset && varFile.propset()["url"].get_string().has_char())
      {
         strPathName = varFile.propset()["url"];
      }
      else if (varFile.cast < ::file::binary_buffer >() != NULL)
      {
         strPathName = System.datetime().international().get_gmt_date_time() + "." + get_document_template()->m_set["default_extension"];
      }
      else
      {
         strPathName = varFile;
      }
      // store the path fully qualified
      //char szFullPath[_MAX_PATH];
      //if ( lstrlen(lpszPathName) >= _MAX_PATH )
      //{
      //   ASSERT(FALSE);
      // core API requires paths with length < _MAX_PATH
      // No other way to handle the error from a void function
      //   ::core::ThrowFileException(::file::exception::badPath);
      //}

      //   if( ::core::FullPath(szFullPath, lpszPathName) == FALSE )
      //   {
      //      ASSERT(FALSE);
      // core API requires paths with length < _MAX_PATH
      // No other way to handle the error from a void function
      //      ::core::ThrowFileException(::file::exception::badPath);
      //   }

      // store the path fully qualified
      string strFullPath;
      //      System.file_system().FullPath(strFullPath, strPathName);
      strFullPath = strPathName;
      m_strPathName = strFullPath;
      //!m_strPathName.is_empty());       // must be set to something
      m_bEmbedded = FALSE;

      // set the document_interface title based on path name
      string strTitle;
      strTitle = System.file().name_(strFullPath);
      set_title(strTitle);

      //string strPathName;
      //::str::international::Utf8ToAcp(strPathName, m_wstrPathName);
      // add it to the file MRU list
      /* xxx if (bAddToMRU)
      guserbase::get(get_app())->AddToRecentFileList(lpszPathName);*/

      /*   ASSERT_VALID(this);
      m_bNew = false;


      m_strPathName = lpszPathName;
      ASSERT(!m_strPathName.is_empty());       // must be set to something
      m_bEmbedded = FALSE;
      ASSERT_VALID(this);

      // set the document_interface title based on path name
      string strTitle = System.file().title_(m_strPathName);
      set_title(strTitle);


      ASSERT_VALID(this);

      m_bNew = false;*/
   }

   ::count document::get_view_count() const
   {
      return m_viewptra.get_count();
   }

   /////////////////////////////////////////////////////////////////////////////
   // Closing documents or views

   void document::on_changed_view_list(single_lock * psl)
   {
      single_lock sl(&m_mutex, false);
      if (psl == NULL || psl->m_psyncobject != &m_mutex)
         psl = &sl;
      psl->lock();
      // if no more views on the document_interface, delete ourself
      // not called if directly closing the document_interface or terminating the cast
      if (m_viewptra.is_empty() && m_bAutoDelete)
      {
         on_close_document(psl);
         return;
      }

      // update the frame counts as needed
      update_frame_counts(psl);
   }


   bool document::on_new_document()
   {
#ifdef DEBUG
      if (is_modified())
         TRACE(::axis::trace::category_AppMsg, 0, "Warning: on_new_document replaces an unsaved document_interface.\n");
#endif

      delete_contents();
      m_strPathName.Empty();      // no path name yet
      set_modified_flag(FALSE);     // make clean
      m_bNew = true;
      return true;
   }

   bool document::on_open_document(var varFile)
   {
#ifdef DEBUG
      if (is_modified())
         TRACE(::axis::trace::category_AppMsg, 0, "Warning: on_open_document replaces an unsaved document_interface.\n");
#endif

      ::file::buffer_sp spfile;

      try
      {

         spfile = Application.file_get_file(varFile, ::file::mode_read | ::file::share_deny_write | ::file::type_binary);

         /*if(::str::begins_ci(varFile, "uifs://"))
         {
         spfile = ifs(get_app(), "").get_file(varFile, ::file::mode_read | ::file::share_deny_write | ::file::type_binary, &fe);
         }
         else
         {
         spfile = System.fs()->get_file(varFile, ::file::mode_read | ::file::share_deny_write | ::file::type_binary, &fe);
         }*/
      }
      catch (::exception::axis & e)
      {
         report_save_load_exception(varFile, &e, FALSE, "__IDP_FAILED_TO_OPEN_DOC");
         return FALSE;
      }

      delete_contents();
      set_modified_flag();  // dirty during de-serialize
      ::file::input_stream is(spfile);
      try
      {
         wait_cursor wait(get_app());
         read(is);     // load me
         spfile->close();
      }
      catch (::exception::axis & e)
      {
         spfile->close();
         delete_contents();   // remove failed contents

         try
         {
            report_save_load_exception(varFile, &e, FALSE, "__IDP_FAILED_TO_OPEN_DOC");
         }
         catch (...)
         {
         }
         return FALSE;
      }

      set_modified_flag(FALSE);     // start off with unmodified

      return TRUE;
   }


   bool document::on_save_document(var varFile)
   {

      ::file::buffer_sp spfile;

      try
      {

         spfile = Application.file_get_file(varFile, ::file::defer_create_directory | ::file::mode_create | ::file::mode_write | ::file::share_exclusive);

      }
      catch (::exception::axis & e)
      {

         report_save_load_exception(varFile, &e, TRUE, "__IDP_INVALID_FILENAME");

         return false;

      }

      if (spfile.is_null())
      {

         report_save_load_exception(varFile, NULL, TRUE, "__IDP_FAILED_TO_SAVE_DOC");

         return false;

      }


      ::file::output_stream os(spfile);

      try
      {

         wait_cursor wait(get_app());

         if (varFile["xmledit"].cast < ::file::memory_buffer >() != NULL)
         {

         }
         else
         {

            write(os);

         }

         spfile->close();

      }
      catch (::exception::axis & e)
      {

         report_save_load_exception(varFile, &e, TRUE, "__IDP_FAILED_TO_SAVE_DOC");

         return false;

      }
      catch (...)
      {

         report_save_load_exception(varFile, NULL, TRUE, "__IDP_FAILED_TO_SAVE_DOC");

         return false;

      }


      set_modified_flag(FALSE);     // back to unmodified

      return true;        // success
   }


   void document::on_close_document(single_lock * psl)
      // must close all views now (no prompting) - usually destroys this
   {
      single_lock sl(&m_mutex, false);
      if (psl == NULL || psl->m_psyncobject != &m_mutex)
         psl = &sl;
      psl->lock();
      // destroy all frames viewing this document_interface
      // the last destroy may destroy us
      bool bAutoDelete = m_bAutoDelete;
      m_bAutoDelete = FALSE;  // don't destroy document_interface while closing views
      for (index index = 0; index < m_viewptra.get_count(); index++)
      {
         // get frame attached to the ::user::impact
         sp(::user::impact) pview = m_viewptra(index);
         ASSERT_VALID(pview);
         sp(::user::frame_window) pFrame = pview->GetParentFrame();

         if (pFrame != NULL)
         {
            // and close it
            pre_close_frame(pFrame);
            pFrame->DestroyWindow();
            // will destroy the ::user::impact as well
         }
      }
      m_viewptra.remove_all();
      m_bAutoDelete = bAutoDelete;
      psl->unlock();

      // clean up contents of document_interface before destroying the document_interface itself
      delete_contents();

      release();
   }

   void document::report_save_load_exception(const char * lpszPathName, ::exception::axis* e, bool bSaving, const char * nIDPDefault)
   {

      try
      {

         UNREFERENCED_PARAMETER(bSaving);
         UNREFERENCED_PARAMETER(nIDPDefault);
         //   UINT nIDP = nIDPDefault;
         //   UINT nHelpContext = nIDPDefault;
         string prompt;

         if (e != NULL)
         {
            if (base_class < user_exception >::bases(e))
               return; // already reported

            /*if (base_class < CArchiveException >::bases(e))
            {
            switch (((CArchiveException*)e)->m_cause)
            {
            case CArchiveException::badSchema:
            case CArchiveException::badClass:
            case CArchiveException::badIndex:
            case CArchiveException::endOfFile:
            nIDP = __IDP_FAILED_INVALID_FORMAT;
            break;
            default:
            break;
            }
            }
            else*/ if (base_class < ::file::exception >::bases(e))
            {
               ::file::exception * pfe = dynamic_cast < ::file::exception * > (e);
               // throw not_implemented(get_app());
               TRACE(::axis::trace::category_AppMsg, 0, "Reporting file I/O exception on Save/Load with lOsError = $%lX.\n",
                  pfe->m_lOsError);


               if (pfe->m_strFileName.is_empty())
                  pfe->m_strFileName = lpszPathName;

               if (!pfe->get_error_message(prompt))
               {
                  /*               switch (((::core::file_exception_sp*)e)->m_cause)
                  {
                  case ::file::exception::fileNotFound:
                  case ::file::exception::badPath:
                  nIDP = __IDP_FAILED_INVALID_PATH;
                  break;
                  case ::file::exception::diskFull:
                  nIDP = __IDP_FAILED_DISK_FULL;
                  break;
                  case ::file::exception::accessDenied:
                  nIDP = bSaving ? __IDP_FAILED_ACCESS_WRITE :
                  __IDP_FAILED_ACCESS_READ;
                  break;

                  case ::file::exception::badSeek:
                  case ::file::exception::generic:
                  case ::file::exception::tooManyOpenFiles:
                  case ::file::exception::invalidFile:
                  case ::file::exception::hardIO:
                  case ::file::exception::directoryFull:
                  break;

                  default:
                  break;*/
                  //     }
               }
               prompt.ReleaseBuffer();
            }
         }

         if (prompt.is_empty())
         {
            string strTitle = System.file().title_(lpszPathName);
            //throw not_implemented(get_app());
            /*
            ::core::FormatString1(prompt, nIDP, strTitle);*/
         }

         //System.simple_message_box(prompt, MB_ICONEXCLAMATION, nHelpContext);
         System.simple_message_box(NULL, prompt, MB_ICONEXCLAMATION);

      }
      catch (...)
      {

      }

   }


   bool document::can_close_frame(sp(::user::frame_window) pFrameArg)
      // permission to close all views using this frame
      //  (at least one of our views must be in this frame)
   {
      single_lock sl(&m_mutex, true);
      ASSERT_VALID(pFrameArg);
      UNUSED(pFrameArg);   // unused in release builds

      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
         sp(::user::frame_window) pFrame = pview->GetParentFrame();
         // assume frameless views are ok to close
         if (pFrame != NULL)
         {
            // assumes 1 document_interface per frame
            ASSERT_VALID(pFrame);
            if (pFrame->m_nWindow > 0)
               return TRUE;        // more than one frame refering to us
         }
      }
      sl.unlock();
      // otherwise only one frame that we know about
      return save_modified();
   }


   bool document::save_modified()
   {
      if (!is_modified())
         return TRUE;        // ok to continue

      // get name/title of document_interface
      string name;
      if (m_strPathName.is_empty())
      {
         name = m_strTitle;
         if (name.is_empty())
         {
            name = System.load_string("Untitled");
         }
      }
      else
      {
         // get name based on file title of path name
         name = System.file().name_(m_strPathName);
      }

      string prompt;
      prompt = System.load_string("MessageBoxChangedFileAskToSave");
      prompt.replace("%1", name);
      switch (Application.simple_message_box(NULL, prompt, MB_YESNOCANCEL))
      {
      case IDCANCEL:
         return FALSE;       // don't continue

      case IDYES:
         // If so, either Save or Update, as appropriate
         if (!do_file_save())
            return FALSE;       // don't continue
         break;

      case IDNO:
         // If not saving changes, revert the document_interface
         break;

      default:
         ASSERT(FALSE);
         break;
      }
      return TRUE;    // keep going
   }


   void document::pre_close_frame(sp(::user::frame_window) /*pFrameArg*/)
   {
      // default does nothing
   }

   bool document::do_save(var varFile, bool bReplace)
      // Save the document_interface data to a file
      // lpszPathName = path name where to save document_interface file
      // if lpszPathName is NULL then the ::fontopus::user will be prompted (SaveAs)
      // note: lpszPathName can be different than 'm_strPathName'
      // if 'bReplace' is TRUE will change file name if successful (SaveAs)
      // if 'bReplace' is FALSE will not change path name (SaveCopyAs)
   {

      var newName = varFile;

      //if (newName.is_empty() || is_new_document())
      if (newName.is_empty())
      {
         
         sp(impact_system) ptemplate = get_document_template();
         
         ASSERT(ptemplate != NULL);

         newName = m_strPathName;
         
         //if (bReplace && (newName.is_empty() || is_new_document()))

         if (bReplace && newName.is_empty())
         {
           
            newName = m_strTitle;
            // check for dubious filename
            strsize iBad = newName.get_string().FindOneOf(":/\\");
            if (iBad != -1)
               newName = newName.get_string().Left(iBad);

            // append the default suffix if there is one
            string strExt;
            if (ptemplate->GetDocString(strExt, impact_system::filterExt) &&
               !strExt.is_empty())
            {
               ASSERT(strExt[0] == '.');
               strsize iStart = 0;
               newName += strExt.Tokenize(";", iStart);
            }
         }

         if (!System.do_prompt_file_name(newName, 0 /*bReplace ? __IDS_SAVEFILE : __IDS_SAVEFILECOPY*/, 0 /*OFN_HIDEREADONLY | OFN_PATHMUSTEXIST */, FALSE, ptemplate, this))
            return FALSE;       // don't even attempt to save

      }

      wait_cursor wait(get_app());

      if (!on_save_document(newName))
      {
         if (varFile.is_empty())
         {
            // be sure to delete the file
            try
            {
               System.file().del(newName);
            }
            catch (::exception::axis * pe)
            {
               TRACE(::axis::trace::category_AppMsg, 0, "Warning: failed to delete file after failed SaveAs.\n");
               pe->Delete();
            }

         }
         return FALSE;
      }

      // reset the title and change the document_interface name
      if (bReplace)
         set_path_name(newName);

      return TRUE;        // success
   }


   bool document::do_file_save()
   {

      if (is_new_document() || session().file_is_read_only(m_strPathName))
      {

         // we do not have read-write access or the file does not (now) exist

         if (!do_save(var(var::type_empty)))
         {

            TRACE(::axis::trace::category_AppMsg, 0, "Warning: File save with new name failed.\n");

            return FALSE;

         }

      }
      else
      {

         if (!do_save(m_strPathName))
         {

            TRACE(::axis::trace::category_AppMsg, 0, "Warning: File save failed.\n");

            return FALSE;

         }

      }

      return TRUE;

   }

   void document::update_frame_counts(single_lock * psl)
      // assumes 1 doc per frame
   {
      single_lock sl(&m_mutex, false);
      if (psl == NULL || psl->m_psyncobject != &m_mutex)
         psl = &sl;
      psl->lock();
      // walk all frames of views (mark and sweep approach)
      ::count count = get_view_count();
      index index;
      for (index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
         // trans      ASSERT(::IsWindow(pview->get_handle()));
         if (pview->IsWindowVisible())   // Do not ::count invisible windows.
         {
            sp(::user::frame_window) pFrame = pview->GetParentFrame();
            if (pFrame != NULL)
               pFrame->m_nWindow = -1;     // unknown
         }
      }

      // now do it again counting the unique ones
      int32_t nFrames = 0;
      count = get_view_count();
      for (index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
         // trans      ASSERT(::IsWindow(pview->get_handle()));
         if (pview->IsWindowVisible())   // Do not ::count invisible windows.
         {
            sp(::user::frame_window) pFrame = pview->GetParentFrame();
            if (pFrame != NULL && pFrame->m_nWindow == -1)
            {
               ASSERT_VALID(pFrame);
               // not yet counted (give it a 1 based number)
               pFrame->m_nWindow = ++nFrames;
            }
         }
      }

      // lastly walk the frames and update titles (assume same order)
      // go through frames updating the appropriate one
      int32_t iFrame = 1;
      count = get_view_count();
      for (index = 0; index < count; index++)
      {
         sp(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
         // trans      ASSERT(::IsWindow(pview->get_handle()));
         if (pview->IsWindowVisible())   // Do not ::count invisible windows.
         {
            sp(::user::frame_window) pFrame = pview->GetParentFrame();
            if (pFrame != NULL && pFrame->m_nWindow == iFrame)
            {
               ASSERT_VALID(pFrame);
               if (nFrames == 1)
                  pFrame->m_nWindow = 0;      // the only one of its kind
               pFrame->post_simple_command(::user::interaction::simple_command_update_frame_title, TRUE);
               iFrame++;
            }
         }
      }
   }

   HMENU document::GetDefaultMenu()
   {
      return NULL;    // just use original default
   }

   HACCEL document::GetDefaultAccelerator()
   {
      return NULL;    // just use original default
   }

   void document::on_idle()
   {
      // default does nothing
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact operations

   void document::add_view(sp(::user::impact) pview)
   {
      single_lock sl(&m_mutex, true);
      ASSERT_VALID(pview);
      ASSERT(pview->::user::impact::get_document() == NULL); // must not be already attached
      if (m_viewptra.add_unique(pview))
      {
         pview->m_spdocument = this;
         on_changed_view_list();    // must be the last thing done to the document_interface
      }
   }

   void document::remove_view(sp(::user::impact) pview)
   {
      single_lock sl(&m_mutex, true);
      ASSERT_VALID(pview);
      ASSERT(pview->::user::impact::get_document() == this); // must be attached to us
      if (m_viewptra.remove(pview) > 0)
      {
         pview->m_spdocument = NULL;
         on_changed_view_list();    // must be the last thing done to the document_interface
      }
   }


   void document::on_file_save()
   {
      do_file_save();
   }

} // namespace user


