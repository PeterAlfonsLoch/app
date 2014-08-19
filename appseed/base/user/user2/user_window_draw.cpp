#include "framework.h"


namespace user
{


   window_draw::window_draw(sp(::axis::application) papp) :
      element(papp),
      thread(papp),
      m_eventFree(papp, TRUE, TRUE)
   {
      m_bProDevianMode                    = true;
      m_iFramesPerSecond                  = 20;
      m_bRunning                          = false;
      m_bRun                              = true;
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
      throw interface_only_exception(get_app());
   }

   bool window_draw::ScreenOutput()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::twf_stop()
   {

      m_bRun = false;

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



