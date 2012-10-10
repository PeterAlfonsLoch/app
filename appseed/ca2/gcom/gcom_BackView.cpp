#include "framework.h"


namespace gcom
{


   namespace backview
   {


      Main::Main(::ca::application * papp, Interface * pinterface) :
         ca(papp),
         m_pinterface(pinterface),
         m_mutexStateMachine(papp)
      {


         m_iRefCount = 0;

         m_bEnabled = false;
         m_estate = StateTiming;
         m_bInitialized = false;

         m_pimagechange          = new ImageChange(*this);
         m_pgraphics             = new Graphics(*this);
         m_ptransitioneffect     = new TransitionEffect(*this);
         m_pvisualeffect         = new VisualEffect(*this);

         m_pthreadIdlePriority = __begin_thread < thread > (
            get_app(),
            ::ca::thread_priority_normal,
            0,
            CREATE_SUSPENDED);
         m_pthreadIdlePriority->SetMain(this);
         m_pthreadIdlePriority->ResumeThread();

         m_pthreadHighestPriority = __begin_thread < thread > (
            get_app(),
            ::ca::thread_priority_highest,
            0,
            CREATE_SUSPENDED);
         m_pthreadHighestPriority->SetMain(this);
         m_pthreadHighestPriority->ResumeThread();
         m_bPendingLayout = true;

      }

      void Main::Shutdown()
      {
         m_pthreadIdlePriority->post_thread_message(WM_QUIT, 0, 0);
         m_pthreadHighestPriority->post_thread_message(WM_QUIT, 0, 0);
      }

      Main::~Main()
      {
         if(m_ptransitioneffect != NULL)
         {
            if(m_ptransitioneffect->m_bRun)
            {
               m_ptransitioneffect->m_bRun = false;
            }
            else
            {
               delete m_ptransitioneffect;
            }
            m_ptransitioneffect = NULL;
         }
         if(m_pvisualeffect != NULL)
         {
            delete m_pvisualeffect;
            m_pvisualeffect = NULL;
         }
      }

      void Main::AddRef()
      {
         m_iRefCount++;
      }
      void Main::Release()
      {
         m_iRefCount--;
         if(m_iRefCount <= 0)
            delete this;
      }

      bool Main::IsFullScreen()
      {
         return false;
      }

      void Main::UpdateDrawingObjects()
      {
         //gen::savings & savings = System.savings();
         Graphics & graphics = GetGraphics();

         graphics.UpdateObjects();
         graphics.RenderBufferLevel2();
         graphics.BufferToBack();
         graphics.BackToTransfer();
         //GetWndInterface().BackViewUpdateScreen();

         m_bInitialized = true;

      }

      /*      void Main::RunTransitionEffectStep()
      {
      GetTransitionEffect().RunStep_();
      }*/

      bool Main::UpdateBuffer(LPCRECT lpcrect)
      {
         UNREFERENCED_PARAMETER(lpcrect);
         //         GetTransitionEffect().RenderBuffer((rect &) *lpcrect);
         return true;
      }

      bool Main::LoadNextImage(bool bSynch)
      {
         return GetImageChange().LoadNextImage(bSynch);
      }
      void Main::_001OnImageLoaded(gen::signal_object * pobj)
      {
         OnImageLoaded((*pobj)()["dib"].ca2 < ::ca::dib > ());
      }

      void Main::OnImageLoaded(::ca::dib * pdib)
      {

         InterfaceData data;
         data.signalize(InterfaceDataCurrentImagePath);
         GetCurrentImagePath(data.m_wstrCurrentImagePath);
         GetInterface().BackViewSetData(data);
         Graphics & graphics = GetGraphics();

         try
         {
            graphics.OnImageLoaded(pdib);
         }
         catch(...)
         {
         }
      }

      void Main::OnAfterImageLoaded()
      {

         //         thread * pbackviewthreadIdle = GetIdleThread();
         ImageChange & imagechange = GetImageChange();
         Graphics & graphics = GetGraphics();
         EImagePlacement eplacement;
         //gen::savings & savings = System.savings();

         TRACE("\nCXfplayerView::OnAfterImageLoaded\n");

         if(GetInterface().BackViewGetImagePlacement(imagechange.m_wstrCurrentImagePath, eplacement))
         {
            imagechange.m_eplacement = (EImagePlacement) eplacement;
         }
         else
         {
            imagechange.m_eplacement = graphics.GetDefaultPlacement();
         }

      }

      bool Main::RenderBuffer()
      {
         if(!m_bInitialized)
            return false;

         ::ca::application * papp = &System;
         if(papp == NULL)
         {
            // if main application is null, there's no reason
            // for painting anything...
            return false;
         }

         ASSERT(papp != NULL);

         //         gen::savings & savings = System.savings();

         Graphics & graphics = GetGraphics();

         graphics.RenderBufferLevel2();

         return true;

      }

      void Main::OnDestroy()
      {
         GetGraphics().OnDestroy();
         m_pthreadIdlePriority->post_thread_message(WM_QUIT, 0 , 0);
         m_pthreadHighestPriority->post_thread_message(WM_QUIT, 0 , 0);


      }

      int Main::SetState(e_state estate)
      {
         m_estate = estate;
         switch(estate)
         {
         case StateFinish:
            {
               GetImageChange().m_evImageChangeFinish.SetEvent();
            }
            break;
         }
         return 1;
      }






#define ONRESIZEDELAY 5000

      int Main::PulseEvent(e_event eevent)
      {

         if(!IsEnabled())
            return 1;

         if(!m_bInitialized)
            return 1;


         thread * pbackviewthreadIdle = GetIdleThread();

         DWORD dwTime = GetTickCount();

         if(eevent == event_timer)
         {
            if(dwTime - GetImageChange().m_noprecisiontimer.m_dwHundredCounter > 100)
            {
               GetImageChange().m_noprecisiontimer.m_dwHundredCounter = dwTime;
               if(dwTime - GetImageChange().m_noprecisiontimer.m_dwThousandCounter > 1000)
               {
                  GetImageChange().m_noprecisiontimer.m_dwThousandCounter = dwTime;
                  GetTransitionEffect().OnNoPrecisionThousandMillisTimer();
               }
            }
         }

         single_lock sl(&m_mutexStateMachine, true);
         switch(m_estate)
         {
         case StateTiming:
            switch(eevent)
            {
            case EventResize:
               {
                  OnResize();
               }
               break;
            case EventFlagChanged:
               {
                  GetInterface().BackViewPostMessage(Interface::MessageBackViewDequeue, 18, 3);
               }
               break;
            case event_timer:
               {
                  if(dwTime - GetImageChange().m_dwBackgroundLastUpdateTime
                     >= GetImageChange().GetBackgroundUpdateMillis())
                  {
                     if(LoadNextImage(false))
                     {
                        SetState(StateLoading);
                     }
                  }
               }
               break;
            case EventLoadNow:
               GetImageChange().OnEventLoadNow();
               break;
            default:;
            }
            break;
         case StateLoading:
            switch(eevent)
            {
            case EventResize:
               {
                  OnResize();
               }
               break;
            case EventFlagChanged:
               {
                  GetInterface().BackViewPostMessage(Interface::MessageBackViewDequeue, 18, 3);
               }
               break;
            case EventLoaded:
               {
                  if(GetInterface().BackViewGetDestroy())
                  {
                     SetState(StateFinish);
                     break;
                  }
                  OnAfterImageLoaded();
                  SetState(StatePreTransition);
                  GetImageChange().m_dwBackgroundPreTransitionStartTime = GetTickCount();
                  pbackviewthreadIdle->PreTransitionImageAsync(this);
               }
               break;
            case EventLoadNow:
            case EventLoadFailed:
               {
                  TRACE("ImageChange::ChangeStateMachine case 120");
                  SetState(StateTiming);
                  GetImageChange().m_dwBackgroundLastUpdateTime = dwTime;
                  //               GetImageChange().LoadNextImage(GetImageChange().m_bLastLoadImageSynch);
               }
               break;
            case event_timer:
               {
                  GetImageChange().m_dwLoadCounter++;
                  //  TRACE("ImageChange::ChangeStateMachine case 130");
                  if(GetImageChange().m_dwLoadCounter > 1000) // Espera 10 segundos para carregar imagem
                  {
                     GetImageChange().m_dwLoadCounter = 0;
                     GetImageChange().LoadImageAsync();
                  }
                  break;
               }
            }
            break;
         case StatePreTransition:
            switch(eevent)
            {
            case EventLoadNow:
               GetImageChange().OnEventLoadNow();
               break;
            case EventResize:
               {
                  SetState(StatePreTransitionResize);
               }
               break;
            case event_timer:
               break;
            case EventPreTransitionFinished:
               GetTransitionEffect().Initialize();
               TRACE("ImageChange::ChangeStateMachine case 110");
               SetState(StateInTransitionEffect);
               break;
            default:;
            }
            break;
         case StatePreTransitionResize:
            switch(eevent)
            {
            case EventLoadNow:
               {
                  GetImageChange().OnEventLoadNow();
               }
               break;
            case EventResize:
               {
               }
               break;
            case event_timer:
               break;
            case EventPreTransitionFinished:
               {
                  SetState(StatePreTransition);
                  GetImageChange().m_dwBackgroundPreTransitionStartTime = GetTickCount();
                  pbackviewthreadIdle->PreTransitionImageAsync(this);
               }
               break;
            default:;
            }
            break;
         case StateInTransitionEffect:
            {
               switch(eevent)
               {
               case EventResize:
                  {
                     SetState(StatePreTransition);
                     GetImageChange().m_dwBackgroundPreTransitionStartTime = GetTickCount();
                     pbackviewthreadIdle->PreTransitionImageAsync(this);
                  }
                  break;
               case EventFlagChanged:
                  {
                     GetTransitionEffect().Restart();
                  }
                  break;
               case event_timer:
                  {
                     GetTransitionEffect().OnTimer();
                  }
                  break;
               case EventTransitionEffectFinished:
                  GetImageChange().m_dwBackgroundLastUpdateTime = GetTickCount();
                  SetState(StateTiming);
                  break;
               case EventLoadNow:;
                  GetImageChange().OnEventLoadNow();
                  break;
               default:;
               }
               break;
         default:;
            }
         }
         return 1;
      }

      void Main::OnResize()
      {
         //GetWnd().SetTimer(10001234, 100, NULL);
         GetInterface().BackViewPostMessage(Interface::MessageBackViewDequeue, 18, 4);

      }
      void Main::OnDequeueMessage(WPARAM wparam, LPARAM lparam)
      {
         //         MSG msg;

         bool bRunStep =
            wparam == 18
            && lparam == 0;

         /*while(PeekMessage(
         &msg,
         (HWND) INVALID_HANDLE_VALUE,
         Interface::MessageBackViewDequeue,
         Interface::MessageBackViewDequeue,
         PM_REMOVE))
         {
         if(
         msg.wParam == 18
         && msg.lParam == 0)
         {
         bRunStep = true;
         }
         }*/

         if(bRunStep)
         {
            ASSERT(FALSE);
            //RunTransitionEffectStep();
         }
         else if(wparam == 18)
         {
            if(lparam == 3)
            {
               rect rect;
               UpdateBuffer(rect);
               GetInterface().BackViewUpdateScreen(rect, RDW_INVALIDATE);
            }
            else if(lparam == 4)
            {
               // Resize
               //BITMAP bm;
               //GetGraphics().LayoutBackBitmap(&bm);

               rect rect;

               UpdateBuffer(rect);
               GetInterface().BackViewUpdateScreen(rect, RDW_INVALIDATE);
            }
         }
      }

      void Main::ImageChangePostEvent(e_event eevent)
      {
         GetInterface().BackViewPostMessage(Interface::BackViewWparamImageChangeEvent, (LPARAM) eevent);
      }

      void Main::SetBackgroundImageChangeInterval(DWORD dwMillis)
      {
         UNREFERENCED_PARAMETER(dwMillis);
         GetImageChange().SetBackgroundUpdateMillis(1000);
      }

      ::ca::graphics & Main::GetTransferDC()
      {
         return GetGraphics().GetTransferDC();
      }

      mutex & Main::GetTransferMutex()
      {
         return GetGraphics().m_mutex4Transfer;
      }

      bool Main::GetNextImagePath(string &str)
      {
         InterfaceData data;
         data.signalize(InterfaceDataNextImagePath);
         GetInterface().BackViewGetData(data);
         str = data.m_wstrNextImagePath;
         return true;
      }

      EImagePlacement Main::GetCurrentImagePlacement()
      {
         return GetImageChange().m_eplacement;
      }

      void Main::SetCurrentImagePlacement(EImagePlacement eplacement)
      {
         GetImageChange().m_eplacement = eplacement;
      }

      void Main::GetCurrentImagePath(string &str)
      {
         str = GetImageChange().m_wstrCurrentImagePath;
      }
      bool Main::IsEnabled()
      {
         return m_bEnabled;
      }

      void Main::Enable(bool bEnable)
      {
         m_bEnabled = bEnable;
      }

      bool Main::IsInitialized()
      {
         return m_bInitialized;
      }

      void Main::DeferCheckLayout()
      {

         if(m_bPendingLayout)
         {
            m_bPendingLayout = false;
            UpdateDrawingObjects();
            PulseEvent((e_event) EventResize);
         }

      }

      Graphics & Main::GetGraphics()
      {
         return * m_pgraphics;
      }

      thread * Main::GetIdleThread()
      {
         return m_pthreadIdlePriority;
      }

      thread * Main::GetHighestThread()
      {
         return m_pthreadHighestPriority;
      }

      ImageChange & Main::GetImageChange()
      {
         return *m_pimagechange;
      }

      TransitionEffect & Main::GetTransitionEffect()
      {
         return *m_ptransitioneffect;
      }

      VisualEffect & Main::GetVisualEffect()
      {
         return *m_pvisualeffect;
      }

      Interface & Main::GetInterface()
      {
         return * m_pinterface;
      }


   } // namespace backview


} // namespace gcom



