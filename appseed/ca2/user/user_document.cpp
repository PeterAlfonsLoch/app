#include "StdAfx.h"


// // BEGIN_MESSAGE_MAP(document, command_target)
   //{{AFX_MSG_MAP(document)
/* xxx   ON_COMMAND(ID_FILE_CLOSE, &document::on_file_close)
   ON_COMMAND(ID_FILE_SAVE, &document::on_file_save)
   ON_COMMAND(ID_FILE_SAVE_AS, &document::on_file_save_as)
   //}}AFX_MSG_MAP */
// // END_MESSAGE_MAP()


document::document(::ca::application * papp) :
   ca(papp),
   data_container(papp)
{
   m_pdocumentemplate      = NULL;
   m_bModified             = FALSE;
   m_bAutoDelete           = TRUE;       // default to auto delete document
   m_bEmbedded             = FALSE;        // default to file-based document
   m_bNew                  = false;
   ASSERT(m_viewptra.is_empty());
}

document::~document()
{
   // do not call delete_contents here !
#ifdef _DEBUG
   if (is_modified())
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: destroying an unsaved document.\n");
#endif

   // there should be no views left!
   disconnect_views();
   ASSERT(m_viewptra.is_empty());

   if (m_pdocumentemplate != NULL)
      m_pdocumentemplate->remove_document(this);
   ASSERT(m_pdocumentemplate == NULL);     // must be detached
}

void document::on_final_release()
{
   ASSERT_VALID(this);

   on_close_document();  // may 'delete this'
}

void document::disconnect_views()
{
   for(index index = 0; index < m_viewptra.get_count(); index++)
   {
      ::view * pview = (::view *)m_viewptra[index];
      ASSERT_VALID(pview);
      ASSERT_KINDOF(::view, pview);
      pview->m_spdocument->release();
   }
   m_viewptra.remove_all();
}

void document::on_alloc(::ca::application * papp)
{
   set_app(papp);
}

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

/////////////////////////////////////////////////////////////////////////////
// Closing documents or views

void document::on_changed_view_list()
{
   // if no more views on the document, delete ourself
   // not called if directly closing the document or terminating the cast
   if (m_viewptra.is_empty() && m_bAutoDelete)
   {
      on_close_document();
      return;
   }

   // update the frame counts as needed
   update_frame_counts();
}

void document::update_frame_counts()
    // assumes 1 doc per frame
{
   // walk all frames of views (mark and sweep approach)
   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
// trans      ASSERT(::IsWindow(pview->get_handle()));
      if (pview->IsWindowVisible())   // Do not count invisible windows.
      {
         frame_window* pFrame = pview->GetParentFrame();
         if (pFrame != NULL)
            pFrame->m_nWindow = -1;     // unknown
      }
   }

   // now do it again counting the unique ones
   int nFrames = 0;
   count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
// trans      ASSERT(::IsWindow(pview->get_handle()));
      if (pview->IsWindowVisible())   // Do not count invisible windows.
      {
         frame_window* pFrame = pview->GetParentFrame();
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
   int iFrame = 1;
   count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
// trans      ASSERT(::IsWindow(pview->get_handle()));
      if (pview->IsWindowVisible())   // Do not count invisible windows.
      {
         frame_window* pFrame = pview->GetParentFrame();
         if (pFrame != NULL && pFrame->m_nWindow == iFrame)
         {
            ASSERT_VALID(pFrame);
            if (nFrames == 1)
               pFrame->m_nWindow = 0;      // the only one of its kind
            pFrame->on_update_frame_title(TRUE);
            iFrame++;
         }
      }
   }
   ASSERT(iFrame == nFrames + 1);
}

BOOL document::can_close_frame(frame_window* pFrameArg)
   // permission to close all views using this frame
   //  (at least one of our views must be in this frame)
{
   ASSERT_VALID(pFrameArg);
   UNUSED(pFrameArg);   // unused in release builds

   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
      frame_window* pFrame = pview->GetParentFrame();
      // assume frameless views are ok to close
      if (pFrame != NULL)
      {
         // assumes 1 document per frame
         ASSERT_VALID(pFrame);
         if (pFrame->m_nWindow > 0)
            return TRUE;        // more than one frame refering to us
      }
   }

   // otherwise only one frame that we know about
   return save_modified();
}

void document::pre_close_frame(frame_window* /*pFrameArg*/)
{
   // default does nothing
}

/////////////////////////////////////////////////////////////////////////////
// File/Path commands

void document::set_path_name(var varFile, BOOL bAddToMRU)
{
   UNREFERENCED_PARAMETER(bAddToMRU);
   string strPathName;
   if(varFile.get_type() == var::type_propset && varFile.propset()["url"].get_string().has_char())
   {
      strPathName = varFile.propset()["url"];
   }
   else if(varFile.ca2 < ::ex1::file > () != NULL)
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
      // ca2 API requires paths with length < _MAX_PATH
      // No other way to handle the error from a void function
   //   AfxThrowFileException(::ex1::file_exception::badPath);
   //}

//   if( AfxFullPath(szFullPath, lpszPathName) == FALSE )
//   {
//      ASSERT(FALSE);
      // ca2 API requires paths with length < _MAX_PATH
      // No other way to handle the error from a void function
//      AfxThrowFileException(::ex1::file_exception::badPath);
//   }

   // store the path fully qualified
   string strFullPath;
   System.file_system().FullPath(strFullPath, strPathName);
   m_strPathName = strFullPath;
   ASSERT(!m_strPathName.is_empty());       // must be set to something
   m_bEmbedded = FALSE;
   ASSERT_VALID(this);

   // set the document title based on path name
   string strTitle;
   strTitle = System.file().name_(strFullPath);
   set_title(strTitle);

   //string strPathName;
   //gen::international::Utf8ToAcp(strPathName, m_wstrPathName);
   // add it to the file MRU list
   /* xxx if (bAddToMRU)
      guserbase::get(get_app())->AddToRecentFileList(lpszPathName);*/

/*   ASSERT_VALID(this);
   m_bNew = false;


   m_strPathName = lpszPathName;
   ASSERT(!m_strPathName.is_empty());       // must be set to something
   m_bEmbedded = FALSE;
   ASSERT_VALID(this);

   // set the document title based on path name
   string strTitle = System.file().title_(m_strPathName);
   set_title(strTitle);


   ASSERT_VALID(this);

   m_bNew = false;*/
}

/////////////////////////////////////////////////////////////////////////////
// Standard file menu commands

void document::on_file_close()
{
   if (!save_modified())
      return;

   // shut it down
   on_close_document();
      // this should destroy the document
}

void document::on_file_save()
{
   do_file_save();
}

void document::on_file_save_as()
{
   if(!do_save(NULL))
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: File save-as failed.\n");
}

bool document::do_file_save()
{
   if(is_new_document() ||
      System.file_is_read_only(m_strPathName))
   {
      // we do not have read-write access or the file does not (now) exist
      if (!do_save(NULL))
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: File save with new name failed.\n");
         return FALSE;
      }
   }
   else
   {
      if (!do_save(m_strPathName))
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: File save failed.\n");
         return FALSE;
      }
   }
   return TRUE;
}

bool document::do_save(const char * pszPathName, bool bReplace)
   // Save the document data to a file
   // lpszPathName = path name where to save document file
   // if lpszPathName is NULL then the ::fontopus::user will be prompted (SaveAs)
   // note: lpszPathName can be different than 'm_strPathName'
   // if 'bReplace' is TRUE will change file name if successful (SaveAs)
   // if 'bReplace' is FALSE will not change path name (SaveCopyAs)
{
   string newName = pszPathName;
   if (newName.is_empty() || is_new_document())
   {
      document_template * ptemplate = get_document_template();
      ASSERT(ptemplate != NULL);

      newName = m_strPathName;
      if (bReplace && (newName.is_empty() || is_new_document()))
      {
         newName = m_strTitle;
         // check for dubious filename
         int iBad = newName.FindOneOf(":/\\");
         if (iBad != -1)
            newName.ReleaseBuffer(iBad);

         // append the default suffix if there is one
         string strExt;
         if (ptemplate->GetDocString(strExt, document_template::filterExt) &&
           !strExt.is_empty())
         {
            ASSERT(strExt[0] == '.');
            int iStart = 0;
            newName += strExt.Tokenize(";", iStart);
         }
      }

      ::userex::pane_tab_view * ppanetabview = NULL;
      if(get_view() != NULL && get_view()->GetTypedParent < ::userex::pane_tab_view > () != NULL)
      {
         ppanetabview = get_view()->GetTypedParent < ::userex::pane_tab_view > ();
         ppanetabview->set_cur_tab_by_id("file_manager");
         ppanetabview->get_pane_by_id("file_manager")->m_bPermanent = false;
         ppanetabview->layout();
         ppanetabview->get_filemanager_document()->FileManagerSaveAs(this);
         if(ppanetabview->GetParentFrame()->RunModalLoop() != "yes")
            return true;
         newName = ppanetabview->get_filemanager_document()->get_filemanager_data()->m_pmanager->m_strTopic;
      }
      else
      {
         if (!System.do_prompt_file_name(newName,
           bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
           0 /*OFN_HIDEREADONLY | OFN_PATHMUSTEXIST */, FALSE, ptemplate))
            return FALSE;       // don't even attempt to save
      }
   }

   wait_cursor wait(get_app());

   if(!on_save_document(newName))
   {
      if(pszPathName == NULL)
      {
         // be sure to delete the file
         try
         {
            System.file().del(newName);
         }
         catch(base_exception * pe)
         {
            TRACE(::radix::trace::category_AppMsg, 0, "Warning: failed to delete file after failed SaveAs.\n");
            pe->Delete();
         }

      }
      return FALSE;
   }

   // reset the title and change the document name
   if (bReplace)
      set_path_name(newName);

   return TRUE;        // success
}

BOOL document::save_modified()
{
   if (!is_modified())
      return TRUE;        // ok to continue

   // get name/title of document
   string name;
   if (m_strPathName.is_empty())
   {
      name = m_strTitle;
      if(name.is_empty())
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
   switch (Application.simple_message_box(NULL, MB_YESNOCANCEL, prompt))
   {
   case IDCANCEL:
      return FALSE;       // don't continue

   case IDYES:
      // If so, either Save or Update, as appropriate
      if (!do_file_save())
         return FALSE;       // don't continue
      break;

   case IDNO:
      // If not saving changes, revert the document
      break;

   default:
      ASSERT(FALSE);
      break;
   }
   return TRUE;    // keep going
}

HMENU document::GetDefaultMenu()
{
   return NULL;    // just use original default
}

HACCEL document::GetDefaultAccelerator()
{
   return NULL;    // just use original default
}

void document::report_save_load_exception(const char * lpszPathName,
   base_exception* e, BOOL bSaving, UINT nIDPDefault)
{

   UNREFERENCED_PARAMETER(bSaving);
   UNREFERENCED_PARAMETER(nIDPDefault);
//   UINT nIDP = nIDPDefault;
//   UINT nHelpContext = nIDPDefault;
   string prompt;

   if (e != NULL)
   {
      if (base < user_exception >::bases(e))
         return; // already reported

      /*if (base < CArchiveException >::bases(e))
      {
         switch (((CArchiveException*)e)->m_cause)
         {
         case CArchiveException::badSchema:
         case CArchiveException::badClass:
         case CArchiveException::badIndex:
         case CArchiveException::endOfFile:
            nIDP = AFX_IDP_FAILED_INVALID_FORMAT;
            break;
         default:
            break;
         }
      }
      else */if (base < ex1::file_exception_sp >::bases(e))
      {
         throw not_implemented_exception();
         /*TRACE(::radix::trace::category_AppMsg, 0, "Reporting file I/O exception on Save/Load with lOsError = $%lX.\n",
            ((ex1::file_exception_sp*)e)->m_lOsError);

         ex1::file_exception_sp* pFileException = (ex1::file_exception_sp*)e;
         if (pFileException->m_strFileName.is_empty())
            pFileException->m_strFileName = lpszPathName;

         if (!e->GetErrorMessage(prompt))
         {
            switch (((ex1::file_exception_sp*)e)->m_cause)
            {
               case ::ex1::file_exception::fileNotFound:
               case ::ex1::file_exception::badPath:
                  nIDP = AFX_IDP_FAILED_INVALID_PATH;
                  break;
               case ::ex1::file_exception::diskFull:
                  nIDP = AFX_IDP_FAILED_DISK_FULL;
                  break;
               case ::ex1::file_exception::accessDenied:
                  nIDP = bSaving ? AFX_IDP_FAILED_ACCESS_WRITE :
                        AFX_IDP_FAILED_ACCESS_READ;
                  break;

               case ::ex1::file_exception::badSeek:
               case ::ex1::file_exception::generic:
               case ::ex1::file_exception::tooManyOpenFiles:
               case ::ex1::file_exception::invalidFile:
               case ::ex1::file_exception::hardIO:
               case ::ex1::file_exception::directoryFull:
                  break;

               default:
                  break;
            }
         }
         prompt.ReleaseBuffer();*/
      }
   }

   if (prompt.is_empty())
   {
      string strTitle = System.file().title_(lpszPathName);
      throw not_implemented_exception();
      /*
      AfxFormatString1(prompt, nIDP, strTitle);*/
   }

   //System.simple_message_box(prompt, MB_ICONEXCLAMATION, nHelpContext);
   System.simple_message_box(NULL, prompt, MB_ICONEXCLAMATION);
}


BOOL document::on_new_document()
{
#ifdef _DEBUG
   if(is_modified())
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: on_new_document replaces an unsaved document.\n");
#endif

   delete_contents();
   m_strPathName.Empty();      // no path name yet
   set_modified_flag(FALSE);     // make clean
   m_bNew = true;
   return TRUE;
}

bool document::on_open_document(var varFile)
{
#ifdef _DEBUG
   if (is_modified())
      TRACE(::radix::trace::category_AppMsg, 0, "Warning: on_open_document replaces an unsaved document.\n");
#endif

   ::ex1::byte_stream spfile;
   ex1::file_exception_sp fe(get_app());
   spfile = Application.get_byte_stream(varFile, ::ex1::file::mode_read | ::ex1::file::shareDenyWrite | ::ex1::file::type_binary, &fe);
   /*if(gen::str::begins_ci(varFile, "uifs://"))
   {
      spfile = ifs(get_app(), "").get_file(varFile, ::ex1::file::mode_read | ::ex1::file::shareDenyWrite | ::ex1::file::type_binary, &fe);
   }
   else
   {
      spfile = System.fs()->get_file(varFile, ::ex1::file::mode_read | ::ex1::file::shareDenyWrite | ::ex1::file::type_binary, &fe);
   }*/
   if(spfile.is_reader_null())
   {
      report_save_load_exception(varFile, fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
      return FALSE;
   }

   delete_contents();
   set_modified_flag();  // dirty during de-serialize

   try
   {
      wait_cursor wait(get_app());
      read(spfile);     // load me
      spfile.close();
   }
   catch(base_exception * pe)
   {
      spfile.close();
      delete_contents();   // remove failed contents

      try
      {
         report_save_load_exception(varFile, pe,
            FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
      }
      catch(...)
      {
      }
      pe->Delete();
      return FALSE;
   }

   set_modified_flag(FALSE);     // start off with unmodified

   return TRUE;
}

BOOL document::on_save_document(const char * lpszPathName)
{

   ::ex1::byte_stream spfile;
   ex1::file_exception_sp fe(get_app());
   spfile = Application.get_byte_stream(lpszPathName, ::ex1::file::defer_create_directory | ::ex1::file::mode_create | ::ex1::file::mode_write | ::ex1::file::shareExclusive, &fe);
   if(spfile.is_writer_null())
   {
      report_save_load_exception(lpszPathName, fe, TRUE, AFX_IDP_INVALID_FILENAME);
      return FALSE;
   }

   try
   {
      wait_cursor wait(get_app());
      write(spfile);
      spfile.close();
   }
   catch(base_exception * pe)
   {
      spfile.close();

      try
      {
         report_save_load_exception(lpszPathName, pe, TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
      }
      catch(...)
      {
      }
      pe->Delete();
      return FALSE;
   }


   set_modified_flag(FALSE);     // back to unmodified

   return TRUE;        // success
}

void document::on_close_document()
   // must close all views now (no prompting) - usually destroys this
{
   // destroy all frames viewing this document
   // the last destroy may destroy us
   BOOL bAutoDelete = m_bAutoDelete;
   m_bAutoDelete = FALSE;  // don't destroy document while closing views
   for(index index = 0; index < m_viewptra.get_count(); index++)
   {
      // get frame attached to the ::view
      ::view * pview = m_viewptra[index];
      ASSERT_VALID(pview);
      frame_window* pFrame = pview->GetParentFrame();

      if(pFrame != NULL)
      {
         // and close it
         pre_close_frame(pFrame);
         pFrame->DestroyWindow();
            // will destroy the ::view as well
      }
   }
   m_viewptra.remove_all();
   m_bAutoDelete = bAutoDelete;

   // clean up contents of document before destroying the document itself
   delete_contents();

   release();
}

void document::on_idle()
{
   // default does nothing
}

/////////////////////////////////////////////////////////////////////////////
// ::view operations

void document::add_view(::view * pview)
{
   ASSERT_VALID(pview);
   ASSERT(pview->::view::get_document() == NULL); // must not be already attached
   if(m_viewptra.add_unique(pview))
   {
      pview->m_spdocument = this;
      on_changed_view_list();    // must be the last thing done to the document
   }
}

void document::remove_view(::view * pview)
{
   ASSERT_VALID(pview);
   ASSERT(pview->::view::get_document() == this); // must be attached to us
   if(m_viewptra.remove(pview) > 0)
   {
      pview->m_spdocument = NULL;
      on_changed_view_list();    // must be the last thing done to the document
   }
}

count document::get_view_count() const
{
   return m_viewptra.get_count();
}

::view * document::get_view(index index) const
{
   if(index < 0 || index >= m_viewptra.get_count())
      return NULL;
   ::view * pview = (::view *) m_viewptra[index];
   ASSERT_KINDOF(::view, pview);
   return pview;
}

void document::update_all_views(::view * pSender, LPARAM lHint, ::radix::object* pHint)
   // walk through all views
{
   ASSERT(pSender == NULL || !m_viewptra.is_empty());
      // must have views if sent by one of them

   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
      if (pview != pSender)
         pview->on_update(pSender, lHint, pHint);
   }
}

void document::send_update(::view * pSender, LPARAM lHint, ::radix::object* pHint)
   // walk through all views
{
   ASSERT(pSender == NULL || !m_viewptra.is_empty());
      // must have views if sent by one of them

   update * pupdate;
   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      pupdate = new update;
      pupdate->m_pSender = pSender;
      pupdate->m_lHint = lHint;
      pupdate->m_pHint = pHint;
      if (pview != pSender)
         pview->SendMessage(WM_VIEW, 0, (LPARAM) pupdate);
   }
}

void document::send_initial_update()
   // walk through all views and call OnInitialUpdate
{
   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
      pview->_001OnInitialUpdate(NULL);
   }
}

/////////////////////////////////////////////////////////////////////////////
// command routing

bool document::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
{
   if (command_target::_001OnCmdMsg(pcmdmsg))
      return TRUE;

   // otherwise check template
   if (m_pdocumentemplate != NULL &&
     m_pdocumentemplate->_001OnCmdMsg(pcmdmsg))
      return TRUE;

   return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// document diagnostics

#ifdef _DEBUG
void document::dump(dump_context & dumpcontext) const
{
   ::radix::object::dump(dumpcontext);

   dumpcontext << "m_strTitle = " << m_strTitle;
   dumpcontext << "\nm_strPathName = " << m_strPathName;
   dumpcontext << "\nm_bModified = " << m_bModified;
   dumpcontext << "\nm_pDocTemplate = " << (void *)m_pdocumentemplate;

   if (dumpcontext.GetDepth() > 0)
   {
      count count = get_view_count();
      for(index index = 0; index < count; index++)
      {
         ::view * pview = get_view(index);
         dumpcontext << "\nwith ::view " << (void *)pview;
      }
   }

   dumpcontext << "\n";
}

void document::assert_valid() const
{
   ::radix::object::assert_valid();

   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      ASSERT_VALID(pview);
   }
}
#endif //_DEBUG


bool document::is_new_document()
{
   return m_bNew;
}

void document::write(ex1::byte_output_stream & ostream)
{
   UNREFERENCED_PARAMETER(ostream);
}

void document::read(ex1::byte_input_stream & istream)
{
   UNREFERENCED_PARAMETER(istream);
}


::view * document::get_view(const ::ca::type_info info, index indexFind)
{
   count countView = get_view_count();
   count countFind = 0;
   ::view * pview;
   for(index index = 0; index < countView; index++)
   {
      pview = get_view(index);
      if(info == typeid(*pview))
      {
         if(indexFind == countFind)
            return pview;
         else
            countFind++;
      }
   }
   return NULL;
}


void document::show_all_frames(UINT nCmdShow)
{
   count count = get_view_count();
   for(index index = 0; index < count; index++)
   {
      ::view * pview = get_view(index);
      pview->GetParentFrame()->ShowWindow(nCmdShow);
   }
}


// document
 const string & document::get_title() const
   { ASSERT(this != NULL); return m_strTitle; }
 const string & document::get_path_name() const
   { ASSERT(this != NULL); return m_strPathName; }
 document_template * document::get_document_template() const
   { ASSERT(this != NULL); return m_pdocumentemplate; }
 BOOL document::is_modified()
   { ASSERT(this != NULL); return m_bModified; }
 void document::set_modified_flag(BOOL bModified)
   { ASSERT(this != NULL); m_bModified = bModified; }
 void document::set_new(bool bNew)
{
   ASSERT(this != NULL);
   m_bNew = bNew;
}


