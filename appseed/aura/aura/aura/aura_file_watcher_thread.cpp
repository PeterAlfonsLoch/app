#include "framework.h"


namespace file_watcher
{


//   bool listener_thread::file_watcher_initialize_thread(::aura::application * papp)
//   {
//
//      set_app(papp);
//
////      m_pthreadimpl.alloc(allocer());
////
////      if(m_pthreadimpl.is_null())
////         return false;
//
//      return true;
//
//   }

   void listener_thread::install_message_handling(::message::dispatch * pdispatch)
   {

      ::thread::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(message_add_watch, pdispatch, this, &listener_thread::_001OnAddWatch);

   }

   void listener_thread::_001OnAddWatch(signal_details * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);

      sp(listener_thread::add) padd(pbase->m_lparam);

      try
      {

         try
         {

            padd->m_id = add_watch(padd->m_str, padd->m_plistener, padd->m_bRecursive, padd->m_bOwn);

         }
         catch (...)
         {

            try
            {

               padd->m_id = -1;

            }
            catch (...)
            {

            }

         }

         padd->m_event.set_event();

      }
      catch (...)
      {

      }

   }

   

   int32_t listener_thread::run()
   {

      try
      {

         MESSAGE msg;

         while(get_run_thread())
         {

            if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
            {
             
               if (!defer_pump_message())
               {

                  break;

               }

            }

            try
            {

               update();

            }
            catch(::file_watcher::exception &)
            {

            }




         }

      }
      catch(...)
      {

      }

      return 0;

   }


} // namespace file_watcher




