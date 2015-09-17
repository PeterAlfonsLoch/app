//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"
//#include "windows.h"

#define DISABLE_UPDATE_BUFFER 0

extern void _001DeferPaintLayeredWindowBackground(oswindow oswindow,::draw2d::graphics * pdc);


class keep_event_reset
{
public:


   event * m_pevent;


   keep_event_reset(event * pevent)
   {
      m_pevent = pevent;
      pevent->ResetEvent();
   }
   ~keep_event_reset()
   {
      m_pevent->SetEvent();
   }


};

extern bool g_bSuppressTwf;

namespace windows
{

   window_draw::window_draw(::aura::application * papp):
      ::object(papp),
      thread(papp),
      ::user::window_draw(papp),
      ::user::message_queue(papp)
   {
         m_dwLastRedrawRequest = ::get_tick_count();
         m_bRender = false;
         //         m_pbuffer = new user::buffer(papp);
         //       m_pbuffer->m_spdib.create(papp);
         m_dwLastUpdate = false;
      }


   window_draw::~window_draw()
   {

   }



   /*
   void window_draw::OnPaint(oswindow oswindow, CPaintDC & spgraphics)
   {
   UNREFERENCED_PARAMETER(oswindow);
   UNREFERENCED_PARAMETER(spgraphics);
   }
   */

   void window_draw::asynch_redraw()
   {
      DWORD dwTick = ::get_tick_count();
      if(m_iFramesPerSecond == 0)
      {
         if(dwTick - m_dwLastUpdate < 1000)
            return;
      }
      else
      {
         if(dwTick - m_dwLastUpdate < 1000 / m_iFramesPerSecond)
            return;
      }
      _asynch_redraw();
   }

   void window_draw::_asynch_redraw()
   {
      if(!m_bProDevianMode)
      {
         message_queue_post_message(WM_USER + 5000);
      }
   }

   void window_draw::synch_redraw()
   {
      if(!m_bProDevianMode && message_queue_is_initialized())
      {
         message_queue_send_message(WM_USER + 5000);
      }
   }

   void window_draw::_synch_redraw()
   {
      
      if(g_bSuppressTwf)
         return;

      keep_event_reset keepeventreset(&m_eventFree);

      static DWORD s_dwLastAnalysisFrame = 0;
      static DWORD s_dwLastFrameFrame = 0;
      static DWORD s_iAnalysisFrameFailureCount = 0;
      static DWORD s_iFrameFailureCount = 0;
      DWORD iFailureTime;
      if(m_iFramesPerSecond == 0)
      {
         iFailureTime = 1000 / 12;
      }
      else
      {
         iFailureTime = 1000 / m_iFramesPerSecond;
      }
      m_dwLastUpdate = ::get_tick_count();
      UpdateBuffer();
      return;
      //      if(m_pbuffer->GetBuffer()->get_os_data() != NULL)
      //    {
      //m_pbuffer->m_spdib->fill_channel(255, visual::rgba::channel_alpha);
      //ScreenOutput();
      //  }
      DWORD dwTakeTime = ::get_tick_count() - m_dwLastUpdate;
      m_dwLastDelay = dwTakeTime;
      if(dwTakeTime > iFailureTime)
      {
         s_dwLastAnalysisFrame += dwTakeTime;
         s_dwLastFrameFrame += dwTakeTime;
         TRACE("window_draw::_synch_redraw :: System has exceeded prodevian performance failure time - %d milliseconds",iFailureTime);
         TRACE("window_draw::_synch_redraw :: took - %d milliseconds",dwTakeTime);
         s_iAnalysisFrameFailureCount++;
         DWORD iTimeFrame = 2000;
         DWORD iMaxFailureCount = 3;
         if(s_dwLastAnalysisFrame > iTimeFrame ||
            dwTakeTime > (iFailureTime * iMaxFailureCount))
         {
            s_dwLastAnalysisFrame = 0;
            if(s_iAnalysisFrameFailureCount > iMaxFailureCount
               || (dwTakeTime > (iFailureTime * iMaxFailureCount)))
            {
               s_iFrameFailureCount++;
            }
            s_iAnalysisFrameFailureCount = 0;
         }
         DWORD iMaxFrameFailureCount = 3;
         DWORD iFrameTimeFrame = iTimeFrame * iMaxFrameFailureCount;
         if(s_dwLastFrameFrame > iFrameTimeFrame)
         {
            s_dwLastFrameFrame = 0;
            if(s_iFrameFailureCount > iMaxFailureCount)
            {
               TRACE("window_draw::_synch_redraw :: during prodevian Performance Analysis Time Frame - %d milliseconds -,",iTimeFrame);
               TRACE("window_draw::_synch_redraw :: failure ::count has exceeded the maximum count - %d",iMaxFailureCount);
               TRACE("window_draw::_synch_redraw :: Going to try to save some resource that may favor drawing perfomance");
               if(!Session.savings().is_trying_to_save(::aura::resource_blur_background))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blur background\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blur background\" resource");
                  Session.savings().try_to_save(::aura::resource_blur_background);
               }
               else if(!Session.savings().is_trying_to_save(::aura::resource_blurred_text_embossing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blurred text embossing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blurred text embossing\" resource");
                  Session.savings().try_to_save(::aura::resource_blurred_text_embossing);
               }
               else if(!Session.savings().is_warning(::aura::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not warning to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to warn to save \"processing\" resource");
                  Session.savings().warn(::aura::resource_processing);
               }
               else if(!Session.savings().is_trying_to_save(::aura::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"processing\" resource");
                  Session.savings().try_to_save(::aura::resource_blur_background);
               }
            }
            s_iFrameFailureCount = 0;
         }

      }
   }


   bool window_draw::finalize()
   {

      message_queue_destroy();

      ::user::window_draw::finalize();

      return true;

   }


   bool window_draw::pre_run()
   {

      if(!create_message_queue("::core::twf - core Transparent Window Framework"))
      {

         m_iReturnCode = -1000;

         TRACE("Could not initialize ::core::twf - core Transparent Window Framework!");

         return false;

      }

      ::AttachThreadInput(::GetCurrentThreadId(),get_os_int(),TRUE);


      if(!::user::window_draw::pre_run())
      {

         return false;

      }

      return true;

   }


   void window_draw::do_events()
   {

      ::thread::do_events();
      try
      {
         if(m_bProDevianMode)
         {
            uint32_t ui1 = ::get_tick_count();
            _synch_redraw();
            uint32_t ui2 = ::get_tick_count();
            m_dwLastDelay = ui2 - ui1;
         }
      }
      catch(...)
      {
      }

      int32_t iUiDataWriteWindowTimeForTheApplicationInThisMachine = 8;
      if(m_iFramesPerSecond == 0)
      {
         Sleep(1000);
      }
      else if((1000 / m_iFramesPerSecond) > m_dwLastDelay)
      {
         Sleep(MAX((DWORD)MAX(0,iUiDataWriteWindowTimeForTheApplicationInThisMachine),(1000 / m_iFramesPerSecond) - m_dwLastDelay));
      }
      else
      {
         Sleep(iUiDataWriteWindowTimeForTheApplicationInThisMachine);
      }


   }


   UINT window_draw::RedrawProc()
   {

      
      try
      {

         m_bRunning = true;

         MSG msg;
         uint32_t ui1;
         uint32_t ui2;
         while(m_bRun)
         {
            try
            {
               if(m_bProDevianMode)
               {
                  ui1 = ::get_tick_count();
                  _synch_redraw();
                  ui2 = ::get_tick_count();
                  m_dwLastDelay = ui2 - ui1;
               }
            }
            catch(...)
            {
            }
            //while(::PeekMessageA(&msg,NULL,0,0,PM_NOREMOVE))
            //{
            //   if(!get_thread()->pump_message())
            //      goto exit;
            //}
            //if(msg.message == WM_QUIT)
            //   break;
            //int32_t iUiDataWriteWindowTimeForTheApplicationInThisMachine = 1;
            //if(m_iFramesPerSecond > 0)
            //{
            //   Sleep(1000);
            //}
            //else if((1000 / m_iFramesPerSecond) > m_dwLastDelay)
            //{
            //   DWORD dw = MAX((DWORD)MAX(0,iUiDataWriteWindowTimeForTheApplicationInThisMachine),(1000 / m_iFramesPerSecond) - m_dwLastDelay);
            //   Sleep(dw);
            //}
            //            else
            if(m_iFramesPerSecond <= 0)
            {
               Sleep(1000);
            }
            else
            {
               
               UINT uiFrameMillis = 1000 / m_iFramesPerSecond;

               if(uiFrameMillis > m_dwLastDelay)
               {

                  Sleep(uiFrameMillis - m_dwLastDelay);

               }

            }

         }
      exit:;

      }
      catch(...)
      {

      }

      m_bRunning = false;

      return 0;

   }

   int32_t window_draw::run()
   {
      return RedrawProc();
   }


   DWORD g_dwLastWindowDraw;
   // lprect should be in screen coordinates
   bool window_draw::UpdateBuffer()
   {

#if DISABLE_UPDATE_BUFFER

      return false;

#endif

      if(m_bRender)
         return false;

      rect rectWindow;

      ::user::interaction * pui = NULL;

      while(System.get_frame(pui))
      {

         bool bOk = true;

         try
         {

            //if(pui->m_bRedraw && ::get_tick_count() - pui->m_dwLastRedraw < 1000)
            //{

            //   continue;

            //}

            //keep < bool > keepRedraw(&pui->m_bRedraw,true,false,true);

            //pui->m_dwLastRedraw = ::get_tick_count();

            if(pui->IsWindowVisible() && pui->m_bMayProDevian && pui->m_psession.is_null())
            {

               //if(get_tick_count() - pui->m_dwLastFullUpdate < 25)
               //{

               //   continue;

               //}



               try
               {

                  pui->defer_check_layout();

               }
               catch(...)
               {

               }



               try
               {

                  pui->_001UpdateBuffer();

               }
               catch(...)
               {

               }


               try
               {

                  pui->_001UpdateScreen();

               }
               catch(...)
               {

               }

            }

         }
         catch(simple_exception & se)
         {

            if(se.m_strMessage == "no more a window")
            {

               bOk = false;

            }

         }
         catch(...)
         {

            bOk = false;

         }

         if(!bOk)
         {

            System.remove_frame(pui);

         }

      }
      return true;

   }





} // namespace windows
