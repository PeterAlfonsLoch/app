#include "framework.h"


namespace backview
{


   const UINT thread::MESSAGE_BACKVIEW = WM_APP + 123;
   const WPARAM thread::WPARAM_BACKVIEW_IMAGELOADED = 0;

   thread::thread(sp(::base::application) papp) :
      element(papp),
      ::thread(papp),
      m_evInitialized(papp, FALSE, TRUE),
      m_mutexBitmap(papp)
   {

      m_pbackviewinterface = NULL;

   }


   thread::~thread()
   {

   }


   bool thread::initialize_instance()
   {

      m_evInitialized.SetEvent();

      return true;

   }


   int32_t thread::exit_instance()
   {

      m_evInitialized.SetEvent();

//      m_pbackviewinterface->Release();

      return ::thread::exit_instance();

   }


   void thread::install_message_handling(::message::dispatch * pinterface)
   {

      IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &thread::OnUserMessage);
      IGUI_WIN_MSG_LINK(MESSAGE_BACKVIEW, pinterface, this, &thread::OnBackViewMessage);
      IGUI_WIN_MSG_LINK(MessageCommand, pinterface, this, &thread::OnCommandMessage);

   }

   void thread::PreTransitionImageAsync(backview::Main * pview)
   {

      post_thread_message(
         MessageCommand,
         CommandPreTransitionImage,
         (LPARAM) pview);
   /*   uint32_t dwThreadID = 0;
      __begin_thread(
         ThreadProcPreTransitionImage,
         pview,
         THREAD_PRIORITY_IDLE,
         0,
         0,
         NULL);*/
   }

   /*void thread::OnImageLoaded(HBITMAP hbitmap)
   {
      backview::Main * pinterface = m_pbackviewinterface;
      backview::Main::CGraphics & graphics = pinterface->BackViewGetGraphics();
       TRACE("\nCXfplayerThreadV1::OnImageLoaded before lock %X\n", m_nThreadID);
       single_lock slGdi(pinterface->BackViewGetSourceBitmapCriticalSection(), true);
       //TRACE("\nCXfplayerThreadV1::OnImageLoaded after lock %X\n", m_nThreadID);
      HBITMAP hBitmapOld = (HBITMAP) graphics.m_bmpBackViewSource.detach();
      graphics.m_bmpBackViewSource.attach(hbitmap);
      CSavings & savings = CSavings::AppGetSavings();
   //    if(iEconoMode != CVMSApp::SaveMemory)
     //  {
      ::draw2d::bitmap * pbmpOld = graphics.m_dcBackViewSource.SelectObject(graphics.m_bmpBackViewSource);
       if(pbmpOld != NULL)
       {
           if(hBitmapOld != NULL)
           {
              // ASSERT(pbmpOld->GetSafeHandle() == hBitmapOld);
           }
       }
       else
       {
         graphics.m_bmpBackViewSource.delete_object();
           TRACE("CXfplayerThreadV1::OnImageLoaded:Bitmap not selected\n");
       }
       //}
       if(hBitmapOld != NULL)
       {
           if(hBitmapOld != graphics.m_bmpBackViewSourceOld.GetSafeHandle())
           {
              if(!delete_object(hBitmapOld))
               {
                   ASSERT(FALSE);
                   TRACE("CXfplayerThreadV1::OnImageLoaded : Atenção! Bitmap não deletado\n");
               }
           }
       }
      slGdi.unlock();

      if(pbmpOld == NULL)
      {
         delete_object(hbitmap);
           pinterface->BackViewImageChangePostEvent(backview::Main::CImageChange::EventLoadFailed);
         return;
      }
       //TRACE("CXfplayerThreadV1::TranslateUserMessage 3 slGdi.UnLock\n");

       if(pinterface == NULL)
           return;
      if(hbitmap != NULL)
         //pview->PostMessage(WM_USER, 17, pview->BkImageChangeEventLoaded);
           pinterface->BackViewImageChangePostEvent(backview::Main::CImageChange::EventLoaded);
           //pview->BackgroundImageChangeStateMachine(pview->BkImageChangeEventLoaded);
      else
         //pview->BackgroundImageChangeStateMachine(pview->BkImageChangeEventLoadFailed);
           pinterface->BackViewImageChangePostEvent(backview::Main::CImageChange::EventLoadFailed);
       return;
   }*/

   long thread::OnImageStretched(
      ::draw2d::bitmap * pbitmap,
      long cx,
      long cy,
      long iUserData)
   {
      UNREFERENCED_PARAMETER(pbitmap);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(iUserData);
       ASSERT(GetMainWnd() == NULL);
       ASSERT(FALSE);

       /*
   try
   {
      backview::Main * pinterface = m_pbackviewinterface;
   try
   {

        RECT rect;
      pinterface->get_window().GetClientRect(&rect);
       TRACE("CXfplayerThreadV1::OnImageStretched slGdi.lock\n");


      pinterface->BackViewUpdateBuffer(false);
       pinterface->GetBackViewWndInterface().BackViewUpdateScreen();
      if(iUserData == 2)
      {
         pinterface->BackViewGetMain().GetImageChange().m_dwBackgroundLastUpdateTime = get_tick_count();
         pinterface->BackViewGetMain().SetState(backview::Main::CImageChange::StateTiming);
      ¨{
       }
   catch(...)
   {
   }
      if(iUserData == 2)
      {
         pinterface->BackViewGetMain().GetImageChange().m_dwBackgroundLastUpdateTime = get_tick_count();
         pinterface->BackViewGetMain().SetState(backview::Main::CImageChange::StateTiming);
      }
   }
   catch(...)
   {
   }*/
      return true;
    }


   UINT c_cdecl thread::ThreadProcPreTransitionImage(LPVOID lpParameter)
   {
       backview::Main * pview = (backview::Main *) lpParameter;
      try
      {
         pview->RenderBuffer();
         pview->ImageChangePostEvent(backview::EventPreTransitionFinished);
      }
      catch(...)
      {
      }
      return 0;
   }

   /*::draw2d::bitmap & thread::GetBitmap()
   {
      return m_bitmap;
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // thread message handlers

   void thread::OnBackViewMessage(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      switch(pbase->m_wparam)
      {
      case WPARAM_BACKVIEW_IMAGELOADED:
         {
            ASSERT(FALSE);
            return;
              TRACE("thread::OnBackViewMessage WPARAM_BACKVIEW_IMAGELOADED\n");
            load_image  * lploadimage = (load_image *) pbase->m_lparam.m_lparam;
            if(lploadimage != NULL)
            {
               lploadimage->OnImageLoaded();
            }
            delete lploadimage;
         }
         break;
      }
   }
   void thread::OnUserMessage(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
       ASSERT(GetMainWnd() == NULL);
      if(pbase->m_wparam == 1) //&& m_pImageLoader != NULL)
      {
         ASSERT(FALSE);
   //      _bstr_t * pBstr = (_bstr_t *) lparam;
   //      m_pImageLoader->load_image(*pBstr, (int32_t) NULL);
   //      delete pBstr;
      }
      else if(pbase->m_wparam == 2)
      {
   //      OnLyricViewSize(lparam);
      }
      else if(pbase->m_wparam == 3)
      {
   //      if((QS_POSTMESSAGE & GetQueueStatus(QS_POSTMESSAGE)) > 0)
   //      {
   //         return;
   //      }
         ASSERT(FALSE);
   //      CVMSApp * pApp = (CVMSApp *) &System;
   //      CXfplayerDoc * pDoc = pApp->GetOnlyDocument();
   //      CXfplayerView * pview = pDoc->GetLyricView();
   //      //pview->PostMessage(WM_USER, lparam, 0);
   //      single_lock slGdi(&pview->m_mutexGdi, TRUE);
   //      pview->m_voiceSpectrum.to(&pview->m_dcBuffer, &pview->m_dcBack, pApp->get_wave_in()->GetFormatEx(), 0.0, 0.0);
   //      RECT rect;
   //      pview->m_voiceSpectrum.GetPlacement(&rect);
   //      //InvalidateRect(&rect, FALSE);
   //      pview->to(&rect, TRUE);
   //      slGdi.unlock();
   //
      }
      else if(pbase->m_wparam == 4)
      {
   //      if((QS_POSTMESSAGE & GetQueueStatus(QS_POSTMESSAGE)) > 0)
   //      {
   //         return;
   //      }
   //      LPSCOREUPDATEMESSAGE lpSum = (LPSCOREUPDATEMESSAGE) lparam ;
   //      CVMSApp * pApp = (CVMSApp *) &System;
   //      CXfplayerDoc * pDoc = pApp->GetOnlyDocument();
   //      CXfplayerView * pview = pDoc->GetLyricView();
   //      //pview->PostMessage(WM_USER, lparam, 0);
   //      single_lock slGdi(&pview->m_mutexGdi, TRUE);
   //      pview->m_voiceSpectrum.to(&pview->m_dcBuffer, &pview->m_dcBack, pApp->get_wave_in()->GetFormatEx(), lpSum->dDeltaScore, lpSum->dScoreAddUp);
   //      RECT rect;
   //      pview->m_voiceSpectrum.GetPlacement(&rect);
   //      //InvalidateRect(&rect, FALSE);
   //      pview->to(&rect, TRUE);
   //      slGdi.unlock();
   //      delete lpSum;

      }
      else if(pbase->m_wparam == 5)
      {
         ASSERT(FALSE);
   /*      LPLOADIMAGESTRUCTURE lpli = (LPLOADIMAGESTRUCTURE) lparam;
           LoadImageAsync(lpli);
         free((void *) lpli->m_lpImagePath);
         delete lpli;*/
      }
      else if(pbase->m_wparam == 6)
      {
         LPONSTRETCHIMAGESTRUCTURE lpsi = (LPONSTRETCHIMAGESTRUCTURE) pbase->m_lparam.m_lparam;
           StretchImageAsync(lpsi, false);
         delete lpsi;
      }
       else if(pbase->m_wparam == 17)
       {
   //        ASSERT(FALSE);
   //        HRESULT hr = CoMarshalInterThreadInterfaceInStream(
     //      _uuidof(VMSIdleLib::IVMSIdle),
      //         m_spIdle,
      //         &m_lpstreamIdle);
         //  m_evGotIdleStream.SetEvent();
       }
       else if(pbase->m_wparam == 23)
       {
         ASSERT(FALSE);
   /*        TRACE("\nCXfplayerThreadV3::TranslateUserMessage 23\n");
           LPONLOADIMAGESTRUCTURE lpoli = (LPONLOADIMAGESTRUCTURE) lparam;
           if(lpoli == NULL)
               OnImageLoaded(NULL);
           else
               OnImageLoaded(lpoli->m_hbitmap);
           delete lpoli;*/
       }
       else if(pbase->m_wparam == 24)
       {
           LPONSTRETCHIMAGESTRUCTURE lposi = (LPONSTRETCHIMAGESTRUCTURE) pbase->m_lparam.m_lparam;
           OnImageStretched(lposi->m_spbitmap,
               lposi->m_iUserData,
               lposi->m_cx,
               lposi->m_cy );
           delete lposi;
       }

   }

   void thread::OnCommandMessage(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      switch(pbase->m_wparam)
      {
      case CommandLoadImage:
         {
            try
            {
               ThreadProcLoadImage((LPVOID) pbase->m_lparam.m_lparam);
            }
            catch(...)
            {
            }
         }
         break;
      case CommandPreTransitionImage:
         {
            ThreadProcPreTransitionImage((LPVOID) pbase->m_lparam.m_lparam);
         }
         break;
      }
   }


   /*void thread::OnLyricViewSize(int32_t iType)
   {
      backview::Main * pmain = m_pbackviewinterface;

      Interface & iface = pmain->GetInterface();
      rect rect;
      iface.BackViewGetClientRect(&rect);
      int32_t cx = rect.right;
      int32_t cy = rect.bottom;

      if(cx <= 0)
         cx = 1;
      if(cy <= 0)
         cy = 1;
      single_lock sl(&m_mutexBitmap, TRUE);
      if(m_bitmap.m_hObject == NULL)
          return;*/
      /*double horizRate, vertRate, rate;
       BITMAP bm;
       //m_bitmap.GetBitmap(&bm);
      if(bm.bmWidth)
         horizRate = ((double) cx) / bm.bmWidth;
      else
         horizRate = 1.0;
      if(bm.bmHeight)
         vertRate = ((double) cy) / bm.bmHeight;
      else
         vertRate = 1.0;
      if(horizRate < vertRate)
         rate = horizRate;
      else
         rate = vertRate;
      int32_t finalWidth, finalHeight; //, finalX, finalY;
      finalWidth = (int32_t) ((double) bm.bmWidth * rate);
      finalHeight = (int32_t) ((double)bm.bmHeight * rate);

      LPSTRETCHIMAGESTRUCTURE lpSi = new STRETCHIMAGESTRUCTURE;
   //   lpSi->m_hbitmap = (HBITMAP) m_bitmap.m_hObject ;
      lpSi->cx = finalWidth;
      lpSi->cy = finalHeight;
      lpSi->m_iUserData = iType;
      //m_spIdle->StretchImageAsync(lpSi, true);
   //   delete lpSi;
   //   pApp->GetThreadV3()->post_thread_message(WM_USER, 6, (LPARAM) lpSi);
       post_thread_message(WM_USER, 6, (LPARAM) lpSi);
   }*/

   void thread::LoadImageAsync(const load_image & loadimage)
   {
      load_image * lploadimage = new load_image(loadimage);
      ::connect(lploadimage->m_signalImageLoaded,  m_pbackviewinterface, &backview::Main::_001OnImageLoaded);

      post_thread_message(
         MessageCommand,
         CommandLoadImage,
         (LPARAM) lploadimage);

      /*uint32_t dwThreadID = 0;
      load_image * lploadimage = new load_image(loadimage);
      __begin_thread(
         ThreadProcLoadImage,
         lploadimage,
         THREAD_PRIORITY_IDLE,
         0,
         0,
         NULL);*/
   }

   void thread::StretchImageAsync(LPONSTRETCHIMAGESTRUCTURE lpSi, bool bBitmapLocked)
   {
      UNREFERENCED_PARAMETER(bBitmapLocked);
      uint32_t dwThreadID = 0;
       ::create_thread(NULL, 0, ThreadProcStretchImage, lpSi, 0, &dwThreadID);
   }

   UINT c_cdecl thread::ThreadProcLoadImage(LPVOID lpParameter)
   {
//         TRACE("thread::ThreadProcLoadImage (no initialize_instance) %X\n", GetCurrentThreadId());

      load_image * lploadimage = (load_image *) lpParameter;


      if(!Sys(lploadimage->GetThread()->get_app()).visual().imaging().LoadImageSync(lploadimage->m_spdib, lploadimage->m_strImagePath, lploadimage->GetThread()->get_app()))
         lploadimage->m_spdib.release();

      lploadimage->OnImageLoaded();

      //lploadimage->PostBackViewThreadMessage(WPARAM_BACKVIEW_IMAGELOADED, (LPARAM) lploadimage);

      return 0;
   }

   void thread::SetMain(backview::Main * pmain)
   {
//      pmain->AddRef();
      m_pbackviewinterface = pmain;
   }

   uint32_t thread::ThreadProcStretchImage(void * lpParameter)
   {
      UNREFERENCED_PARAMETER(lpParameter);
      ASSERT(FALSE);
      return (uint32_t) -1;
   }

   thread_dispatch::thread_dispatch(thread * pbackviewthread)
   {
      m_pbackviewthread = pbackviewthread;
   }

   thread_dispatch & thread_dispatch::operator =(const thread_dispatch & dispatch)
   {
      m_pbackviewthread = dispatch.m_pbackviewthread;
      return *this;
   }

   thread * thread_dispatch::GetThread()
   {
      return m_pbackviewthread;
   }

   void thread_dispatch::PostBackViewThreadMessage(WPARAM wparam, LPARAM lparam)
   {
      GetThread()->post_thread_message(::backview::thread::MESSAGE_BACKVIEW, wparam, lparam);
   }


   load_image::load_image(::draw2d::dib * pdib, thread * pbackviewthread, backview::Main * pbackviewinterface, const char * lpcwszImagePath) :
      m_spdib(pdib),
      thread_dispatch(pbackviewthread),
      m_strImagePath(lpcwszImagePath),
      m_pbackviewinterface(pbackviewinterface)
   {
   }

   load_image::load_image(const load_image & loadimage) :
      thread_dispatch(loadimage.m_pbackviewthread)
   {
      operator =(loadimage);
   }

   load_image & load_image::operator =(const load_image & loadimage)
   {

      thread_dispatch::operator     = (loadimage);
      m_strImagePath                = loadimage.m_strImagePath;
      m_pbackviewinterface          = loadimage.m_pbackviewinterface;
      m_spdib                       = loadimage.m_spdib;

      return *this;

   }

   void load_image::OnImageLoaded()
   {
      signal_details obj(&m_signalImageLoaded);
      obj()["dib"] = m_spdib;
      m_signalImageLoaded.emit(&obj);
   }

} // namespace backview


