#include "StdAfx.h"
#include "MixerVisualThread.h"
#include "MixerVisualCentral.h"

MixerVisualThread::MixerVisualThread(::ca::application * papp) :
   m_event(FALSE, TRUE), 
   thread(papp)
{
}

MixerVisualThread::~MixerVisualThread()
{
}

bool MixerVisualThread::initialize_instance()
{
   m_event.SetEvent();
   return true;
}

int MixerVisualThread::exit_instance()
{
   GetVisualCentral().OnVisualThreadExitInstance();
   return thread::exit_instance();
}

void MixerVisualThread::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(MixerVisualThread::MessageMain, pinterface, this, &MixerVisualThread::OnMixerVisualMessage);
}

void MixerVisualThread::OnMixerVisualMessage(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   switch(pbase->m_wparam)
   {
   case MessageMainWparamInitialize:
      {
         CInitialize * pinitialize = (CInitialize *) pbase->m_lparam;
         OnInitialize(pinitialize);
         delete pinitialize;
      }
      break;
   case MessageMainWparamDisplayAMixer:
      {
           // open a Mixer Window

         wait_cursor cwc(get_app());

         MixerVisualCentral & visualcentral = GetVisualCentral();

         ::userbase::multiple_document_template * pdoctemplate = visualcentral.get_document_template();

         //bool bDoShow = (lParam & 1) != 0;
         ASSERT(pdoctemplate != NULL);
         if(pdoctemplate != NULL)
         {
            document * pdoc = pdoctemplate->open_document_file(NULL);
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

bool MixerVisualThread::Initialize(MixerVisualCentral *pvisualcentral)
{
   m_pvisualcentral = pvisualcentral;
   return true;
}

void MixerVisualThread::OnInitialize(CInitialize *pinitialize)
{
   m_pvisualcentral = pinitialize->m_pvisualcentral;
}

MixerVisualCentral & MixerVisualThread::GetVisualCentral()
{
   return * m_pvisualcentral;
}
