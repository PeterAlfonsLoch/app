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

   //void listener_thread::install_message_handling(::message::dispatch * pdispatch)
   //{

   //   ::thread::install_message_handling(pdispatch);

   //   IGUI_WIN_MSG_LINK(WM_USER + 123, pdispatch, this, &listener_thread::_001OnUser123);

   //}

   //void listener_thread::_001OnUser123(signal_details * pobj)
   //{

   //   SCAST_PTR(::message::base, pbase, pobj);

   //   sp(listener_thread::op) pop(pbase->m_lparam);

   //   try
   //   {

   //      try
   //      {

   //         pop->m_id = add_watch(pop->m_str, pop->m_plistener, pop->m_bRecursive, pop->m_bOwn);

   //      }
   //      catch (...)
   //      {

   //         try
   //         {

   //            pop->m_id = -1;

   //         }
   //         catch (...)
   //         {

   //         }

   //      }

   //      pop->m_event.set_event();

   //   }
   //   catch (...)
   //   {

   //   }

   //}

   

   int32_t listener_thread::run()
   {



//#ifndef METROWIN


      try
      {

//         MESSAGE msg;

         while(get_run_thread())
         {

            //if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
            //{
            // 
            //   if (!defer_pump_message())
            //   {

            //      break;

            //   }

            //}

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
//#endif

      return 0;

   }


} // namespace file_watcher




