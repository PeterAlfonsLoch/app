#include "framework.h"


#if defined(LINUX)

#include <unistd.h>

#endif

namespace install
{


   install::install(sp(base_application) papp) :
      element(papp),
      ::base_departament(papp),
      //m_mutex(papp, false, "Global\\spa_boot_install"),
      m_mutex(papp),
      m_trace(papp)
   {

         m_bAdmin = false;
         m_dwLatestBuildNumberLastFetch = 0;
         m_hmutexBoot = NULL;

         g_bCa2Installed = false;
         g_bCa2Updated = false;
         g_bInstallingCa2 = false;
         g_bSpaInstalled = false;
         g_bSpaUpdated = false;
         g_bUpdated = false;
         g_pszCa2Build = NULL;


      }

   install::~install()
   {

   }

   bool install::is_file_ok(const char * path1, const char * pszTemplate)
   {
      return true;
      string strUrl;
#if CA2_PLATFORM_VERSION == CA2_BASIS
      strUrl = "http://basis.spaignition.api.server.ca2.cc/md5?authnone&version=basis&stage=";
#else
      strUrl = "http://stage.spaignition.api.server.ca2.cc/md5?authnone&version=stage&stage=";
#endif
      strUrl += pszTemplate;

      return file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), Application.http().get(strUrl));

   }


   int32_t install::spalib_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nCmdShow)
   {

      throw todo(get_app());

      /*      install::installer installer(get_app());

            installer.m_hinstance = hInstance;

            installer.m_nCmdShow = nCmdShow;

            return installer.spaadmin_main(lpCmdLine);*/



   }


   int32_t install::synch_install(const char * pszCommandLine, bool bBackground)
   {

      wait_until_mutex_does_not_exist("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");

      string strCommand;

      strCommand = "synch_spaadmin:";

      strCommand += "starter_start:";

      strCommand += pszCommandLine;

      if (bBackground)
      {

         strCommand += " background";

      }

      app_install_call_sync(strCommand);

      return 0;

   }


   void install::app_install_call_sync(const char * szParameters)
   {
      bool bLaunch;

      if (stricmp_dup(szParameters, "exit") == 0
         || stricmp_dup(szParameters, "quit") == 0)
      {
         bLaunch = false;
      }
      else
      {
         bLaunch = true;
      }

      app_install_send_short_message(szParameters, bLaunch);

   }


   CLASS_DECL_BASE bool install::app_install_send_short_message(const char * psz, bool bLaunch)
   {



#ifdef METROWIN

      throw "todo";

#else

      small_ipc_tx_channel txchannel;

      installer::launcher launcher(get_app());

      if (!txchannel.open("core/spaboot_install", bLaunch ? &launcher : NULL))
         return false;

      txchannel.send(psz, false);

#endif

      return true;

   }


   void install::app_install_send_response(const char * param)
   {

#ifdef METROWIN

      throw "todo";

#else

      small_ipc_tx_channel txchannel;

      installer::launcher launcher(get_app());

      if (!txchannel.open("core/spaboot_install_callback"))
         return;

      txchannel.send(param, false);

#endif

   }



   int32_t install::asynch_install(const char * pszCommandLine, bool bBackground)
   {

      wait_until_mutex_does_not_exist("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");

      string strCommand;

      strCommand = "spaadmin:";

      strCommand += "starter_start:";

      strCommand += pszCommandLine;

      if (bBackground)
      {
         strCommand += " background";
      }

      app_install_call_sync(strCommand);

      return 0;

   }


   bool install::is_admin()
   {
      return m_bAdmin;
   }

   void install::set_admin(bool bSet)
   {
      m_bAdmin = bSet;
   }

   string install::get_id()
   {
      return m_strId;
   }

   void install::set_id(const char * psz)
   {
      m_strId = psz;
   }


   string install::get_platform()
   {
#ifdef X86
      return "x86";
#else
      return "x64";
#endif
   }


   bool install::is_installed(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
   {

      return is(pszVersion, pszBuild, pszType, pszId, pszLocale, pszSchema);

/*      if (psz == NULL)
         return true;

      if (*psz == '\0')
         return true;

      if (pszType == NULL || *pszType == '\0')
         pszType = "application";

      if (pszVersion == NULL || *pszVersion == '\0')
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         pszVersion = "basis";

#else

         pszVersion = "stage";

#endif

      }

      string strLatestBuildNumber;

      if (pszBuild == NULL || *pszBuild == '\0')
      {

         strLatestBuildNumber = get_latest_build_number(pszVersion);

         pszBuild = strLatestBuildNumber;

      }

      if (stricmp_dup(pszVersion, "basis") && stricmp_dup(pszVersion, "stage"))
         return false;

      ::xml::document nodeInstall;

      nodeInstall.load(file_as_string_dup(dir::appdata("spa_install.xml")));

      ::xml::node * lpnodeVersion = nodeInstall.get_child(pszVersion);

      if (lpnodeVersion == NULL)
         return false;

      ::xml::node * lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", pszBuild);

      if (lpnodeInstalled == NULL)
         return false;

      ::xml::node * lpnodeType = lpnodeInstalled->get_child(pszType);

      if (lpnodeType == NULL)
         return false;

      ::xml::node * lpnodeId = NULL;

      for (int32_t ui = 0; ui < lpnodeType->get_children_count(); ui++)
      {

         lpnodeId = lpnodeType->child_at(ui);

         string strId = lpnodeId->attr("id");

         if (!strcmp(lpnodeId->get_name(), pszType) && strId == psz)
         {

            goto found_id;

         }

      }

      return false;

   found_id:

      ::xml::node * lpnodeLocalization = NULL;

      for (int32_t ui = 0; ui < lpnodeId->get_children_count(); ui++)
      {

         lpnodeLocalization = lpnodeId->child_at(ui);

         string strLocale = lpnodeLocalization->attr("locale");
         string strSchema = lpnodeLocalization->attr("schema");

         if (!strcmp(lpnodeLocalization->get_name(), "localization") && strLocale == pszLocale && strSchema == pszSchema)
         {

            return true;

         }

      }

      return false;*/

   }

   string install::get_latest_build_number(const char * pszVersion)
   {

      string strLatestBuildNumber = m_strmapLatestBuildNumber[pszVersion];

      if (!strLatestBuildNumber.is_empty() && (get_tick_count() - m_dwLatestBuildNumberLastFetch) < ((1984 + 1977) * 3))
         return strLatestBuildNumber;

      strLatestBuildNumber = fetch_latest_build_number(pszVersion);

      m_strmapLatestBuildNumber.set_at(pszVersion, strLatestBuildNumber);

      m_dwLatestBuildNumberLastFetch = get_tick_count();

      return strLatestBuildNumber;

   }

   string install::fetch_latest_build_number(const char * pszVersion)
   {

      string strBuildNumber;

      string strSpaIgnitionBaseUrl;

      if (pszVersion != NULL && !strcmp(pszVersion, "basis"))
      {

         strSpaIgnitionBaseUrl = "http://basis.spaignition.api.server.ca2.cc";

      }
      else if (pszVersion != NULL && !strcmp(pszVersion, "stage"))
      {

         strSpaIgnitionBaseUrl = "http://stage.spaignition.api.server.ca2.cc";

      }
      else
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         strSpaIgnitionBaseUrl = "http://basis.spaignition.api.server.ca2.cc";

#else

         strSpaIgnitionBaseUrl = "http://stage.spaignition.api.server.ca2.cc";

#endif

      }

      int32_t iRetry = 0;

   RetryBuildNumber:

      if (iRetry > 10)
      {

         return "";

      }

      iRetry++;

      strBuildNumber = Application.http().get(strSpaIgnitionBaseUrl + "/query?node=build");

      strBuildNumber.trim();

      if (strBuildNumber.length() != 19)
      {

         Sleep(184 * iRetry);

         goto RetryBuildNumber;

      }

      return strBuildNumber;

   }

   int32_t install::start_app(const char * id)
   {

      string strDir;
      string strFile;

#ifdef X86

      strDir = dir::element("\\stage\\x86");

#else

      strDir = dir::element("\\stage\\x64");

#endif

      strFile = strDir;
      strFile += "\\app.exe";

      string strParam;

      strParam = ": app=";
      strParam += id;

#ifdef METROWIN

      throw "todo";

#else

      call_async(strFile, strParam, strDir, SW_SHOW);

#endif

      return 0;

   }






   string install::get_installation_lock_file_path()
   {

      string strPath;

      strPath = dir::path(dir::afterca2(), "install.lock");

      return strPath;

   }


   void install::installation_file_lock(bool bLock)
   {

      string strPath;

      strPath = get_installation_lock_file_path();

      int32_t iRetry = 84;

      if (bLock)
      {
         while (!file_exists_dup(strPath) && iRetry > 0)
         {
            file_put_contents_dup(strPath, "installing...");
            Sleep(184);
            iRetry--;
         }
      }
      else
      {
         while (file_exists_dup(strPath) && iRetry > 0)
         {
#ifdef WINDOWS
            ::DeleteFileW(wstring(strPath));
#else
            unlink(strPath);
#endif
            Sleep(184);
            iRetry--;
         }
      }

   }


   bool install::is_lock_file_locked()
   {

#if 1

      sp(mutex) spmutex = ::mutex::open_mutex(get_app(), "Global\\::ca::fontopus::ca2_spaboot_install::7807e510-5579-11dd-ae16-0800200c7784");

      single_lock sl(spmutex);

#elif defined(WINDOWS)

      // more deterministic, with process lifetime determined by process hold mutex

      try
      {

         simple_hold_handle hold_handle(::OpenMutexW(SYNCHRONIZE, FALSE, L"Global\\::ca::fontopus::ca2_spaboot_install::7807e510-5579-11dd-ae16-0800200c7784"));

         if (hold_handle.m_handle == NULL)
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

#else

      // more heuristical, and if there is a process with the same name

      try
      {

         if (get_process_pid("app-install") < 0)
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }


#endif

      string strPath;

      strPath = get_installation_lock_file_path();

      if (file_exists_dup(strPath))
         return true;

      return false;

   }



   uint32_t _ca2_starter_start(void * pvoid);

   const char * install::get_starter_version()
   {
      return ca2_get_build();
   }

   const char * install::get_version()
   {
      return file_as_string_dup(dir::element("appdata", get_platform(), "build.txt"));
   }

   const char * install::get_ca2_version()
   {
      return file_as_string_dup(dir::element("appdata", get_platform(), "ca2_build.txt"));
   }

   void install::update_ca2_installed(bool bUnloadIfNotInstalled)
   {

      if (is_lock_file_locked())
      {

         g_bCa2Installed = false;
         return;

      }


      string strStage(dir::element("stage", get_platform()));

#ifdef WINDOWSEX
      ::SetDllDirectoryA(strStage);
#endif

      g_bCa2Installed = true;
      if (g_bCa2Installed)
      {
         base_library libraryOs(get_app());
         g_bCa2Installed = libraryOs.open(dir::path(strStage, "os"));
         if (g_bCa2Installed)
         {
            base_library libraryCa2(get_app());
            g_bCa2Installed = libraryCa2.open(dir::path(strStage, "core"));
            if (!bUnloadIfNotInstalled && g_bCa2Installed)
            {
               libraryCa2.m_bAutoClose = false;
               libraryOs.m_bAutoClose = false;
               return;
            }

         }
      }

   }



   bool install::is_ca2_installed()
   {
      return g_bCa2Installed;
   }


   void install::update_ca2_updated()
   {
      g_bCa2Updated = !strcmp_dup(get_starter_version(), get_ca2_version());
   }

   // ca files in store updated only in store but may not be yet transferred to the stage
   bool install::is_ca2_updated()
   {
      return g_bCa2Updated;
   }

   bool install::is_installing_ca2()
   {
      return g_bInstallingCa2;
   }

   void install::set_installing_ca2(bool bSet)
   {
      g_bInstallingCa2 = bSet;
   }

   // ca files in store updated and transferred to the stage
   void install::update_updated()
   {
      g_bUpdated = !strcmp_dup(get_starter_version(), get_version());
   }


   bool install::is_updated()
   {
      return g_bUpdated;
   }















#ifdef WINDOWS

   void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
   {
      UNREFERENCED_PARAMETER(uiCode);
      UNREFERENCED_PARAMETER(ppointers);
   }

#endif






   void install::update_ca2_build()
   {
      if (g_pszCa2Build != NULL)
         memory_free_dbg(g_pszCa2Build, 0);
      g_pszCa2Build = (char *)strdup_dup(Application.http().get("http://spaignition.api.server.ca2.cc/ca2_get_build?authnone"));
   }


   const char * install::ca2_get_build()
   {
      update_ca2_build();
      return g_pszCa2Build;
   }


   void install::set_ca2_updated(const char * pszBuild)
   {
      dir::mk(dir::element() + "\\appdata\\" + get_platform());
      file_put_contents_dup(dir::element() + "\\appdata\\" + get_platform() + "\\ca2_build.txt", pszBuild);
   }


   void install::set_updated(const char * pszBuild)
   {
      dir::mk(dir::element() + "\\appdata\\" + get_platform());
      file_put_contents_dup(dir::element() + "\\appdata\\" + get_platform() + "\\build.txt", pszBuild);
   }



   void install::add_spa_start(const char * pszType, const char * pszId)
   {

      string strPath;

      strPath = System.dir().appdata("spa_start.xml");

      string strContents;

      strContents = Application.file().as_string(strPath);

      ::xml::document doc(get_app());

      doc.load(strContents);

      doc.get_root()->set_name("spa");

      stringa straName;
      stringa straValue;

      straName.add("type");
      straValue.add(pszType);

      straName.add("id");
      straValue.add(pszId);

      sp(::xml::node) lpnode = doc.get_root()->GetChildByAllAttr("start", straName, straValue);

      if (lpnode == NULL)
      {

         lpnode = doc.get_root()->add_child("start");

         lpnode->add_attr("type", pszType);

         lpnode->add_attr("id", pszId);

         Application.file().put_contents(strPath, doc.get_xml());

      }

   }

   void install::remove_spa_start(const char * pszType, const char * pszId)
   {

      string strPath;

      strPath = System.dir().appdata("spa_start.xml");

      string strContents;

      strContents = Application.file().as_string(strPath);

      ::xml::document doc(get_app());

      doc.load(strContents);

      doc.get_root()->set_name("spa");

      stringa straName;
      stringa straValue;

      straName.add("type");
      straValue.add(pszType);

      straName.add("id");
      straValue.add(pszId);

      sp(::xml::node) lpnode = doc.get_root()->GetChildByAllAttr("start", straName, straValue);

      if (lpnode != NULL)
      {

         doc.get_root()->remove_child(lpnode);

         Application.file().put_contents(strPath, doc.get_xml());

      }

   }

   void install::add_app_install(const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
   {

      synch_lock sl(&m_mutex);

      string strPath;

      strPath = System.dir().appdata("spa_install.xml");

      System.dir().mk(System.dir().name(strPath), get_app());

      ::xml::document doc(get_app());

      doc.load(Application.file().as_string(strPath));

      if (doc.get_root()->get_name().is_empty())
      {

         doc.get_root()->set_name("install");

      }

      string strBuild(pszBuild);

#if CA2_PLATFORM_VERSION == CA2_BASIS

      sp(::xml::node) lpnodeVersion = doc.get_root()->get_child("basis");

#else

      sp(::xml::node) lpnodeVersion = doc.get_root()->get_child("stage");

#endif

      if (lpnodeVersion == NULL)
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         lpnodeVersion = doc.get_root()->add_child("basis");

#else

         lpnodeVersion = doc.get_root()->add_child("stage");

#endif

      }

      sp(::xml::node) lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", strBuild);

      if (lpnodeInstalled == NULL)
      {

         lpnodeInstalled = lpnodeVersion->add_child("installed");

         lpnodeInstalled->add_attr("build", pszBuild);

      }

      sp(::xml::node) lpnodeType = lpnodeInstalled->get_child(pszType);

      if (lpnodeType == NULL)
      {

         lpnodeType = lpnodeInstalled->add_child(pszType);

      }

      sp(::xml::node) lpnode = lpnodeType->GetChildByAttr(pszType, "id", pszId);

      if (lpnode == NULL)
      {

         lpnode = lpnodeType->add_child(pszType);

         lpnode->add_attr("id", pszId);

      }

      stringa straName;
      stringa straValue;

      straName.add("locale");
      straValue.add(pszLocale);


      straName.add("schema");
      straValue.add(pszSchema);

      sp(::xml::node) lpnodeLocalization = lpnode->GetChildByAllAttr("localization", straName, straValue);

      if (lpnodeLocalization == NULL)
      {

         lpnodeLocalization = lpnode->add_child("localization");

         lpnodeLocalization->add_attr("locale", pszLocale);

         lpnodeLocalization->add_attr("schema", pszSchema);

      }

      ::xml::disp_option opt = *System.xml().m_poptionDefault;

      opt.newline = true;

      Application.file().put_contents(strPath, doc.get_xml(&opt));

   }

   bool install::is(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
   {

      synch_lock sl(&m_mutex);

      string strPath;

      strPath = System.dir().appdata("spa_install.xml");

      string strContents;

      strContents = Application.file().as_string(strPath);

      ::xml::document doc(get_app());

      if (strContents.is_empty())
         return false;

      try
      {

         if (!doc.load(strContents))
            return false;

      }
      catch (...)
      {

         return false;

      }

      if (doc.get_root() == NULL)
         return false;


      if (string(pszVersion).is_empty())
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         pszVersion = "basis";


#else

         pszVersion = "basis";

#endif

      }

      sp(::xml::node) lpnodeVersion = doc.get_root()->get_child(pszVersion);

      if (lpnodeVersion == NULL)
         return false;

      string strBuildNumber(pszBuild);

      if (strBuildNumber == "latest")
      {

         strBuildNumber = get_latest_build_number(pszVersion);

      }

      sp(::xml::node) lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", strBuildNumber);

      if (lpnodeInstalled == NULL)
         return false;

      sp(::xml::node) lpnodeType = lpnodeInstalled->get_child(pszType);

      if (lpnodeType == NULL)
         return false;

      sp(::xml::node) lpnode = lpnodeType->GetChildByAttr(pszType, "id", pszId);

      if (lpnode == NULL)
         return false;

      stringa straName;
      stringa straValue;

      straName.add("locale");
      straValue.add(pszLocale);


      straName.add("schema");
      straValue.add(pszSchema);

      sp(::xml::node) lpnodeLocalization = lpnode->GetChildByAllAttr("localization", straName, straValue);

      if (lpnodeLocalization == NULL)
         return false;

      return true;

   }












   int32_t install::start(const char * pszCommandLine)
   {
      return System.install().asynch_install(pszCommandLine);
   }


   int32_t install::synch(const char * pszCommandLine)
   {

      return System.install().synch_install(pszCommandLine);

   }


   void install::on_set_scalar(e_scalar escalar, int64_t iValue)
   {

      if (escalar == scalar_app_install_progress)
      {

         m_iProgressStepApp = iValue;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         m_iProgressCountApp = iValue;

      }
      else
      {

         return ::int_scalar_source::on_set_scalar(escalar, iValue);

      }

   }


   void install::get_scalar_minimum(e_scalar escalar, int64_t & i)
   {

      if (escalar == scalar_app_install_progress)
      {

         i = 0;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         i = m_iProgressCountApp;

      }
      else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }

   void install::get_scalar(e_scalar escalar, int64_t & i)
   {

      if (escalar == scalar_app_install_progress)
      {

         i = m_iProgressStepApp;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         i = m_iProgressCountApp;

      }
      else
      {

         ::int_scalar_source::get_scalar(escalar, i);

      }

   }

   void install::get_scalar_maximum(e_scalar escalar, int64_t & i)
   {

      if (escalar == scalar_app_install_progress)
      {

         i = m_iProgressCountApp;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         i = m_iProgressStepApp;

      }
      else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }


   bool install::app_install_ensure_executable(string & strPath)
   {

      bool bPrivileged = false;

      int32_t iSpabootInstallStrSize = MAX_PATH * 16;

   #ifdef WINDOWSEX

      debug_box("installer::launcher::ensure_executable", "installer::launcher::ensure_executable", 0);

      HINSTANCE hinstanceAppInstall = (HINSTANCE) ::GetModuleHandleA("app-install.exe");

      bPrivileged = hinstanceAppInstall == ::GetModuleHandleA(NULL);

      if (bPrivileged)
      {

         string strPlatform = System.install().get_platform();

         strPath = ::dir::element("stage\\" + strPlatform + "\\app-install.exe");

      }
      else
      {

         HINSTANCE hinstancePlugin = (HINSTANCE) ::GetModuleHandleA("npca2.dll");

         if (hinstancePlugin == NULL)
            hinstancePlugin = (HINSTANCE) ::GetModuleHandleA("iexca2.dll");

         if (hinstancePlugin != NULL)
         {

            char szModulePath[MAX_PATH * 3];

            ::GetModuleFileNameA((HINSTANCE)hinstancePlugin, szModulePath, sizeof(szModulePath));

            char * file = NULL;

            LPSTR psz = strPath.GetBufferSetLength(iSpabootInstallStrSize);

            ::GetFullPathNameA(szModulePath, iSpabootInstallStrSize, psz, &file);

            file[0] = '\0';

            strcat_dup(psz, "app-install.exe");

            strPath.ReleaseBuffer();

         }
         else
         {

            string strPlatform = System.install().get_platform();

            strPath = ::dir::element("stage\\" + strPlatform + "\\app-install.exe");

         }

      }

   #else

      throw "TODO";

   #endif

      if (!file_exists_dup(strPath) || !System.install().is_file_ok(strPath, "app-install.exe"))
      {

         int32_t iRetry = 0;

         while (iRetry < 8)
         {

            if (!bPrivileged)
            {

               LPSTR psz = strPath.GetBufferSetLength(iSpabootInstallStrSize);

               if (!System.get_temp_file_name(psz, iSpabootInstallStrSize, "app-install", "exe"))
               {

                  strPath.ReleaseBuffer();

                  return false;

               }

               strPath.ReleaseBuffer();

            }

            string strUrl;

   #if CA2_PLATFORM_VERSION == CA2_BASIS

            strUrl = "http://warehouse.ca2.cc/spa?download=app-install.exe";

   #else

            strUrl = "http://store.ca2.cc/spa?download=app-install.exe";

   #endif

            property_set set;

            set["disable_ca2_sessid"] = true;

            if (Application.http().download(strUrl, strPath, set))
            {

               if (System.install().is_file_ok(strPath, "app-install.exe"))
               {

                  break;

               }

            }

            iRetry++;

         }

      }

      strPath.ReleaseBuffer();

      if (!System.install().is_file_ok(strPath, "app-install.exe"))
      {

         return false;

      }

      return true;

   }


} // namespace install







