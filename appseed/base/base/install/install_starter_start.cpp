#include "framework.h"


namespace install
{


   starter_start::starter_start(sp(::base::application) papp) :
      element(papp)
   {

   }


   UINT starter_start::start()
   {

      static bool s_bStarting = false;

      if (s_bStarting)
         return -1;

#if CA2_PLATFORM_VERSION == CA2_BASIS

      string strVersion = "basis";

#else

      string strVersion = "stage";

#endif

      ::set_thread(m_pplugin);

      string strId = get_command_line_param(m_strCommandLine, "app", "session", "session_start").trimmed();

      string strType = get_command_line_param(m_strCommandLine, "app_type").trimmed();

      string strLocale = get_command_line_param(m_strCommandLine, "locale").trimmed();

      string strSchema = get_command_line_param(m_strCommandLine, "schema").trimmed();

      if (strId.is_empty())
         return -1;

      if (strType.is_empty())
         strType = "application";

      keep_true keepStarting(s_bStarting);

      int32_t i = 0;

      string strBuildNumber;

      System.install().set_admin(false);

      while (true)
      {

         if ((i % 5) == 0 || strBuildNumber.is_empty())
         {

            strBuildNumber = System.install().get_latest_build_number(NULL);

         }

         if (System.install().is_installing_ca2())
         {
            
            Sleep((5000) * 2);

            continue;

         }

         System.install().update_ca2_installed(true);

         if (System.install().is_ca2_installed() && System.install().is_installed(strVersion, strBuildNumber, strType, strId, strLocale, strSchema))
         {

            break;

            //update_ca2_updated();
            //if(is_ca2_updated())
            // break;

         }

         System.install().synch_install(m_strCommandLine, strBuildNumber);

         prepare_small_bell(true);

         

      }

      //set_installing_ca2(false);

      //if(is_ca2_installed() && is_installed("application", m_strId) && is_ca2_updated())
      if (System.install().is_ca2_installed() && System.install().is_installed(strVersion, strBuildNumber, strType, strId, strLocale, strSchema) && m_pplugin != NULL)
      {
         defer_play_small_bell();
         m_pplugin->set_ca2_installation_ready();
      }

      // sentinel is not ready neither spa entire concept of passive installation is ready yet.
      // recap:  wait for a required installation. But upgrades are passive installation,  done when it all can be done hot or when there is no use, except when it is requested explicitly.

      /*string strPlatform = spa_get_platform();

      string strSentinelPath = dir::path(dir::beforeca2(), ("core\\stage\\" + strPlatform + "\\app.sentinel.exe"));

      call_sync(strSentinelPath, "");*/

      return 0;
   }

   uint32_t _ca2_starter_start(void * pvoid)
   {


      starter_start * pstart = (starter_start *)pvoid;


      UINT uiRet = pstart->start();


      if (uiRet != 0)
         return uiRet;


      delete pstart;


      return uiRet;


   }




} // namespace install




