#include "StdAfx.h"
#include "mixeruserbase_thread.h"
#include "mixeruserbase_central.h"


namespace mixeruserbase
{


   thread::thread(::ca::application * papp) :
      m_event(FALSE, TRUE), 
      ::radix::thread(papp)
   {
   }

   thread::~thread()
   {
   }

   bool thread::initialize_instance()
   {
      m_event.SetEvent();
      return true;
   }

   int thread::exit_instance()
   {
      get_central().on_thread_exit_instance();
      return ::radix::thread::exit_instance();
   }

   void thread::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(thread::MessageMain, pinterface, this, &thread::OnMixerVisualMessage);
   }

   void thread::OnMixerVisualMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      switch(pbase->m_wparam)
      {
      case MessageMainWparamInitialize:
         {
            initialize * pinitialize = (initialize *) pbase->m_lparam;
            OnInitialize(pinitialize);
            delete pinitialize;
         }
         break;
      case MessageMainWparamDisplayAMixer:
         {
              // open a Mixer Window

            wait_cursor cwc(get_app());

            class central & central = get_central();

            ::userbase::multiple_document_template * pdoctemplate = central.get_document_template();

            //bool bDoShow = (lParam & 1) != 0;
            ASSERT(pdoctemplate != NULL);
            if(pdoctemplate != NULL)
            {
               ::document * pdoc = pdoctemplate->open_document_file(NULL);
               if(pdoc != NULL)
               {
                  pdoc->update_all_views(NULL, 17);
                  ::view * pview = pdoc->get_view(0);
                  if(pview != NULL)
                  {
                     ::user::interaction * pwnd = pview->GetParentFrame();
                     if(pwnd != NULL)
                     {
                        pwnd->SetFocus();
                        pwnd->SetForegroundWindow();
                        pwnd->BringWindowToTop();
                        pwnd->ShowWindow(SW_RESTORE);
                        if(GetMainWnd() == pwnd)
                           SetMainWnd(NULL);
                     
                     }
                  }
               }
            }

         }
         break;

      }
    

       if(pbase->m_wparam ==  23)
       {
       }
       else if(pbase->m_wparam ==  21)
       {
       }
       else if(pbase->m_wparam == 19)
       {
           ASSERT(FALSE);
   //        CDBCentral * pdc = (CDBCentral *) lParam;
     //      pdc->SongsCreateBuildAlbumThread(
       //        (CDataCentral::EBuildSongsAlbumOperation)
         //      (CDataCentral::eBuildSongsAlbumDeleteNotFound |
           //    CDataCentral::eBuildSongsAlbumAddNew |
             //  CDataCentral::eBuildSongsAlbumCreateSearchReferences),
               //false, this, this);
       }
       else if(pbase->m_wparam == 20)
       {
           ASSERT(FALSE);
   //        CDBCentral * pdc = (CDBCentral *) lParam;
     //      pdc->SongsCreateBuildAlbumThread(
       //        (CDataCentral::EBuildSongsAlbumOperation)
         //      (CDataCentral::eBuildSongsAlbumAddNew |
           //    CDataCentral::eBuildSongsAlbumCreateSearchReferences),
             //  true, this, this);
       }
       else if(pbase->m_wparam == 810)
       {
           ASSERT(FALSE);
   //        CDBCentral * pdc = (CDBCentral *) lParam;
     //      pdc->SongsCreateBuildAlbumThread(
       //        (CDataCentral::EBuildSongsAlbumOperation)
         //      CDataCentral::eBuildSongsAlbumDeleteNotFound,
           //    false, this, this);
       }
       else if(pbase->m_wparam == 20191817)
       {
         ASSERT(FALSE);
       }
       else if(pbase->m_wparam == 67985)
       {
         ASSERT(FALSE);
           //m_pMixerDocTemplate->close_all_documents(lParam != 0);
       }


   //    if(m_pMixerDocTemplate != NULL)
     //  {
       //    m_pMixerDocTemplate->open_document_file(NULL);
         //  if(GetMainWnd() != NULL)
           //{
             //  GetMainWnd()->SetForegroundWindow();
           //}
       //}
   }

   bool thread::Initialize(central *pvisualcentral)
   {
      m_pcentral = pvisualcentral;
      return true;
   }

   void thread::OnInitialize(initialize *pinitialize)
   {
      m_pcentral = pinitialize->m_pcentral;
   }

   central & thread::get_central()
   {
      return * m_pcentral;
   }


} // namespace mixeruserbase


