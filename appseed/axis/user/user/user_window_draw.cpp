#include "framework.h" // from "axis/user/user.h"


namespace user
{


   window_draw::window_draw(sp(::aura::application) papp) :
      element(papp),
      thread(papp),
      m_eventFree(papp, TRUE, TRUE)
   {
      m_bProDevianMode                    = true;
      m_iFramesPerSecond                  = 24.0;
      m_bRunning                          = false;
      m_bRun                              = true;
      m_bRender                           = false;
   }


   bool window_draw::twf_start()
   {

      int iReturnCode;

      if(begin_synch(&iReturnCode))
         return false;

      return true;

   }


   bool window_draw::UpdateBuffer()
   {

      if(m_bRender)
         return false;

      keep<bool> keepRender(&m_bRender, true, false, true);

      //::user::interaction_spa wndpa(get_app());

      //wndpa = get_wnda();

      //rect rectWindow;

      //rect rect9;

      ::user::oswindow_array wndaApp;

      single_lock sl(&System.m_framea.m_mutex, true);

      ::user::interaction * pui;

      for(int32_t l = 0; l < System.m_framea.get_count();)
      {

         try
         {

            if(System.m_framea[l]->oprop("session").is_new())
            {

               if(System.m_framea[l]->m_bMayProDevian)
               {

                  pui = System.m_framea[l];

                  //sl.unlock();

                  pui->_001UpdateBuffer();

                  pui->_001UpdateScreen();

               }

            }

            l++;

         }
         catch(simple_exception & se)
         {

            if(se.m_strMessage == "no more a window")
            {

               TRACE("No more a window explicitly");
               System.frames().remove(System.m_framea[l]);
             //wndpa.remove_at(l);

            }
         }
         catch(...)
         {

            TRACE("No more a window implicitly");

            System.frames().remove(System.m_framea[l]);


            //wndpa.remove_at(l);

         }
         //if(!sl.m_bAcquired)
         {
           // sl.lock();
         }
      }

      return true;

   }


   bool window_draw::ScreenOutput()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::twf_stop()
   {

      set_end_thread();

      return true;

   }

   void window_draw::asynch_redraw()
   {
      throw interface_only_exception(get_app());
   }

   void window_draw::synch_redraw()
   {
      throw interface_only_exception(get_app());
   }


   ptr_array < ::user::interaction > window_draw::get_wnda()
   {

      return System.frames();

   }


} // namespace user



