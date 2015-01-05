//#include "framework.h"


namespace aura
{


   assert_running_task::assert_running_task(::aura::application * papp,const string & strAppId):
      element(papp),
      thread(papp)
   {

      m_strAppId = strAppId;

      m_durationCheckPeriod = millis(184 + 1951 + 1977);

   }


   assert_running_task::~assert_running_task()
   {

   }


   int32_t assert_running_task::run()
   {

      while(get_run())
      {

         try
         {

            Session.assert_running(m_strAppId);

         }
         catch(::exit_exception &)
         {

            Application.post_to_all_threads(WM_QUIT,0,0);

         }
         catch(::exception::exception &)
         {

         }
         catch(...)
         {

         }

         Sleep(m_durationCheckPeriod);

      }

      return 0;

   }


} // namespace aura



















































