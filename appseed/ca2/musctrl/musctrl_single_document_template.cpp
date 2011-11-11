#include "StdAfx.h"

namespace musctrl
{

   single_document_template::single_document_template(
      ::ca::application * papp, 
      const char * pszMatter, 
      ::ca::type_info pDocClass,
      ::ca::type_info pFrameClass, 
      ::ca::type_info pViewClass ) :

      ca(papp),
      m_pActivePlaylistDoc(NULL),
      ::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
      ::single_document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
      ::userbase::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
      ::userbase::single_document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass)
   {

      load_template();


   }

   single_document_template::~single_document_template()
   {
   #ifdef _DEBUG
      if(m_pdocument != NULL)
         TRACE0("Warning: destroying single_document_template with live document.\n");
   #endif
   }



   void single_document_template::request(::ca::create_context * pcreatecontext)
   {
      pcreatecontext->m_spCommandLine->m_varQuery["document"] = (::ca::ca *) NULL;
      bool bMakeVisible = pcreatecontext->m_spCommandLine->m_varQuery["make_visible_boolean"];
//      ::user::interaction * puiParent = pcreatecontext->m_spCommandLine->m_varQuery["parent_user_interaction"].ca2 < ::user::interaction > ();
//      ::view * pviewAlloc = pcreatecontext->m_varQuery["allocation_view"].ca2 < ::view > ();
      if(pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         pcreatecontext->m_spCommandLine->m_varQuery["document"] = OpenDocumentFileNoReserve(NULL, pcreatecontext);
      }
      else
      {
         OpenDocumentFileNoReserve(NULL, pcreatecontext);
         ReserveSong(pcreatecontext->m_spCommandLine->m_varFile, true, bMakeVisible != 0);
         pcreatecontext->m_spCommandLine->m_varQuery["document"] = m_pdocument;
      }
   }

   document * single_document_template::OpenDocumentFileNoReserve(var varFile, ::ca::create_context * pcreatecontext)
   {

      document * pdocument = NULL;
      frame_window * pFrame = NULL;
      BOOL bCreated = FALSE;      // => doc and frame created
      BOOL bWasModified = FALSE;

      if (m_pdocument != NULL)
      {
         // already have a document - reinit it
         pdocument = dynamic_cast < ::userbase::document * > (m_pdocument);
         if (!pdocument->save_modified())
            return NULL;        // leave the original one

         ::view * pview = pdocument->get_view(0);

         if(pview != NULL)
         {
            pFrame = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
         }

   //      pFrame = (m_pdocument)->GetLyricView()->GetParentFrame();
   //      ASSERT(pFrame != NULL);
   //      ASSERT_KINDOF(userbase::frame_window, pFrame);
   //      ASSERT_VALID(pFrame);
      }
      else
      {
         // create a new document
         pdocument = create_new_document();
         ASSERT(pFrame == NULL);     // will be created below
         bCreated = TRUE;
      }

      if (pdocument == NULL)
      {
         // linux System.simple_message_box(AFX_IDP_FAILED_TO_CREATE_DOC);
         System.simple_message_box(NULL, "Failed to create document");
         return NULL;
      }

      ASSERT(pdocument == m_pdocument);

      bool bCreatedNewFrame = false;

      if (pFrame == NULL && bCreated)
      {
         ASSERT(bCreated);

         // create frame - set as main document frame
         BOOL bAutoDelete = pdocument->m_bAutoDelete;
         pdocument->m_bAutoDelete = FALSE;
                  // don't destroy if something goes wrong
         pFrame = create_new_frame(pdocument, NULL, pcreatecontext);
         pdocument->m_bAutoDelete = bAutoDelete;
         if (pFrame == NULL)
         {
            // linux System.simple_message_box(AFX_IDP_FAILED_TO_CREATE_DOC);
            System.simple_message_box(NULL, "Failed to create document");
            delete pdocument;       // explicit delete on error
            return NULL;
         }
         bCreatedNewFrame = true;
      }

      if(varFile.is_empty())
      {
         // create a new document
         set_default_title(pdocument);

         // avoid creating temporary compound file when starting up invisible
         if (!pcreatecontext->m_bMakeVisible)
            pdocument->m_bEmbedded = TRUE;

         if (!pdocument->on_new_document())
         {
            // user has been alerted to what failed in on_new_document
            TRACE0("::userbase::document::on_new_document returned FALSE.\n");
            if (bCreated)
               pFrame->DestroyWindow();    // will destroy document
            return NULL;
         }
      }
      else
      {
         wait_cursor wait(get_app());

         // open an existing document
         bWasModified = pdocument->is_modified();
         pdocument->set_modified_flag(FALSE);  // not dirty for open

         if (!pdocument->on_open_document(varFile))
           //if(VMS_FAILED(ReserveSong(lpszPathName, true)))
         {
            // user has been alerted to what failed in on_open_document
            TRACE0("::userbase::document::on_open_document returned FALSE.\n");
            if (bCreated)
            {
               pFrame->DestroyWindow();    // will destroy document
            }
            else if (!pdocument->is_modified())
            {
               // original document is untouched
               pdocument->set_modified_flag(bWasModified);
            }
            else
            {
               // we corrupted the original document
               set_default_title(pdocument);

               if (!pdocument->on_new_document())
               {
                  TRACE0("Error: on_new_document failed after trying to open a document - trying to continue.\n");
                  // assume we can continue
               }
            }
            return NULL;        // open failed
         }
         pdocument->set_path_name(varFile);
      }

      ::radix::thread* pThread = System.GetThread();
      if (bCreated)
      {
         if(pThread->GetMainWnd() == NULL || (dynamic_cast<userbase::frame_window*>(pThread->GetMainWnd()) == NULL))
         {
            // set as main frame (InitialUpdateFrame will show the ::ca::window)
            pThread->SetMainWnd(pFrame);
         }
         if(Application.m_puiMain == NULL)
         {
            Application.m_puiMain = pFrame;
         }
      }
      if(bCreatedNewFrame)
      {
         InitialUpdateFrame(pFrame, pdocument, pcreatecontext->m_bMakeVisible);
      }

      return pdocument;
   }

   /////////////////////////////////////////////////////////////////////////////
   // single_document_template diagnostics

   #ifdef _DEBUG
   void single_document_template::dump(dump_context & dumpcontext) const
   {
      ::userbase::document_template::dump(dumpcontext);

      if (m_pdocument)
         dumpcontext << "with document: " << (void *)m_pdocument;
      else
         dumpcontext << "with no document";

      dumpcontext << "\n";
   }

   void single_document_template::assert_valid() const
   {
      ::userbase::document_template::assert_valid();
      if (m_pdocument)
         ASSERT_VALID(dynamic_cast < document * > (m_pdocument));
   }
   #endif //_DEBUG



   VMSRESULT single_document_template::ReserveSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible)
   {
      mediaplaylist::central & playlistcentral = mediaplaylist::central_container::AppGetPlaylistCentral(get_app());
      ::mediaplaylist::document * pdoc = playlistcentral.GetCurrentPlaylist(bMakeVisible);
      pdoc->AddSong(lpiaSongs, iSongCount, bDoPlay, bMakeVisible);
      return VMSR_SUCCESS;
   }


   VMSRESULT single_document_template::ReserveSong(int iSongCode, bool bDoPlay, bool bMakeVisible)
   {
      mediaplaylist::central & playlistcentral = mediaplaylist::central_container::AppGetPlaylistCentral(get_app());
      ::mediaplaylist::document * pdoc = playlistcentral.GetCurrentPlaylist(bMakeVisible);
      pdoc->AddSong(iSongCode, bDoPlay, bMakeVisible, true);
      return VMSR_SUCCESS;
   }

   VMSRESULT single_document_template::ReserveSong(var varFile, bool bDoPlay, bool bMakeVisible)
   {
      mediaplaylist::central & playlistcentral = mediaplaylist::central_container::AppGetPlaylistCentral(get_app());
      ::mediaplaylist::document * pdoc = playlistcentral.GetCurrentPlaylist(bMakeVisible);
      //string str;
      //str.SetACP(lpcszPath); // ACP here is very important.
      pdoc->AddSong(varFile, bDoPlay ? ::mediaplaylist::document::AddSongAndPlay : ::mediaplaylist::document::AddSongAndPlayIfNotPlaying, bMakeVisible, true);
      return VMSR_SUCCESS;
   }


   VMSRESULT single_document_template::ReserveSong(stringa & stra, bool bDoPlay, bool bMakeVisible)
   {
      mediaplaylist::central & playlistcentral = mediaplaylist::central_container::AppGetPlaylistCentral(get_app());
      ::mediaplaylist::document * pdoc = playlistcentral.GetCurrentPlaylist(bMakeVisible);
      pdoc->AddSong(stra, bDoPlay, bMakeVisible);
      return VMSR_SUCCESS;
   }

} // namespace musctrl