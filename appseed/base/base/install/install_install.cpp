#include "framework.h"


#if defined(LINUX)

#include <unistd.h>

#endif

namespace install
{


   install::install(sp(::base::application) papp) :
      element(papp),
      ::base::departament(papp),
      //m_mutex(papp, false, "Global\\spa_boot_install"),
      m_mutex(papp),
      m_trace(papp)
   {

         m_bAdmin = false;
         m_dwLatestBuildNumberLastFetch = 0;
         m_hmutexBoot = NULL;

         m_bCa2Installed = false;
         m_bCa2Updated = false;
         m_bSpaInstalled = false;
         m_bSpaUpdated = false;
         m_bUpdated = false;
         //m_strCa2Build = NULL;


         m_iProgressAppInstallStart = 0;
         m_iProgressAppInstallStep = 0;
         m_iProgressAppInstallEnd = 0;

#if CA2_PLATFORM_VERSION == CA2_BASIS

         m_strVersion = "basis";

#else

         m_strVersion = "stage";

#endif


      }

   install::~install()
   {

   }

   bool install::is_file_ok(const char * path1, const char * pszTemplate, const char * pszFormatBuild)
   {

      string strFormatBuild(pszFormatBuild);

      string strUrl;

      strUrl = "http://api.ca2.cc/spaignition/md5?authnone&version=basis&stage=";
      strUrl += pszTemplate;
      strUrl += "&build=";
      strUrl += strFormatBuild;

      property_set set(get_app());

      return file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), Application.http().get(strUrl, set));

   }


   int32_t install::spalib_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nCmdShow)
   {

      throw todo(get_app());

      /*      install::installer installer(get_app());

            installer.m_hinstance = hInstance;

            installer.m_nCmdShow = nCmdShow;

            return installer.spaadmin_main(lpCmdLine);*/



   }


   int32_t install::synch_install(const char * pszCommandLine, const char * pszBuild, bool bBackground)
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

      app_install_call_sync(strCommand, pszBuild);

      return 0;

   }


   void install::app_install_call_sync(const char * szParameters, const char * pszBuild)
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

      app_install_send_short_message(szParameters, bLaunch, pszBuild);

   }


   CLASS_DECL_BASE bool install::app_install_send_short_message(const char * psz, bool bLaunch, const char * pszBuild)
   {

#ifdef METROWIN

      throw "todo";

#else

      small_ipc_tx_channel txchannel;

      installer::launcher launcher(get_app(), m_strVersion, pszBuild);

      if (!txchannel.open("core/spaboot_install", bLaunch ? &launcher : NULL))
         return false;

      txchannel.send(psz, false);

#endif

      return true;

   }


   void install::app_install_send_response(const char * param, const char * pszBuild)
   {

#ifdef METROWIN

      throw "todo";

#else

      small_ipc_tx_channel txchannel;

      installer::launcher launcher(get_app(), m_strVersion, pszBuild);

      if (!txchannel.open("core/spaboot_install_callback"))
         return;

      txchannel.send(param, false);

#endif

   }



   int32_t install::asynch_install(const char * pszCommandLine, const char * pszBuild, bool bBackground)
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

      app_install_call_sync(strCommand, pszBuild);

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

      property_set set(get_app());

      strBuildNumber = Application.http().get(strSpaIgnitionBaseUrl + "/query?node=build", set);

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








   bool install::is_installing_ca2()
   {

#if 1

      sp(mutex) spmutex = ::mutex::open_mutex(get_app(), "Global\\::ca::fontopus::ca2_spaboot_install::7807e510-5579-11dd-ae16-0800200c7784");

      return spmutex.is_set();

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

         if (get_process_pid("app.install") < 0)
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }


#endif

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

      if (is_installing_ca2())
      {

         //m_bCa2Installed = false; in fact we cannot determine if ca2 is installed, 
         // because it may be installed but unusable (installation file is locked)
         return;

      }


      string strStage(dir::element("stage", get_platform()));

#ifdef WINDOWSEX
      ::SetDllDirectoryA(strStage);
#endif

      m_bCa2Installed = true;
      if (m_bCa2Installed)
      {
         // this function (update_ca2_installed) calculates is_ca2_installed and 
         // is used at browser plugins like npca2.dll and iexca2.dll which now is 
         // linked with os.dll and that are shipped during browser plugin installation
         // with its own version of os.dll. Testing if ca2 is installed by using this
         // os.dll, is not a good indicator anymore, and worst, can potentially make
         // os.dll to be unloaded and make the dependant instatiated browser plugins
         // to malfunction. Using only core.dll test only by now.
         //::base::library libraryOs(get_app());
         //m_bCa2Installed = libraryOs.open(dir::path(strStage, "os")); 
         //if (m_bCa2Installed)
         //{
         ::base::library libraryCa2(get_app());
         m_bCa2Installed = libraryCa2.open(dir::path(strStage, "core"));
         if (m_bCa2Installed)
         {

            // hey !! 
            // now ca2 is installed!!
            // great event!!
            // let's celebrate!!
            // but to celebrate we need some planning, preparation...
            // humm, let's think....
            // is m_strCa2 in win_dir initialized correctly now that there is a ca2 module?
            // (reversed enginereed frustation and anger into flowers garden...)

            System.update_module_paths();

            System.dir().initialize();

            if (!bUnloadIfNotInstalled)
            {

               libraryCa2.m_bAutoClose = false;

               //    libraryOs.m_bAutoClose = false;

               return;

            }

         }

         //}
      }

   }



   bool install::is_ca2_installed()
   {
      return m_bCa2Installed;
   }


   void install::update_ca2_updated()
   {
      m_bCa2Updated = !strcmp_dup(get_starter_version(), get_ca2_version());
   }

   // ca files in store updated only in store but may not be yet transferred to the stage
   bool install::is_ca2_updated()
   {
      return m_bCa2Updated;
   }

   // ca files in store updated and transferred to the stage
   void install::update_updated()
   {
      m_bUpdated = !strcmp_dup(get_starter_version(), get_version());
   }


   bool install::is_updated()
   {
      return m_bUpdated;
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

      property_set set(get_app());

      m_strCa2Build = Application.http().get("http://spaignition.api.server.ca2.cc/ca2_get_build?authnone", set);

   }


   const char * install::ca2_get_build()
   {
      update_ca2_build();
      return m_strCa2Build;
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

         pszVersion = "stage";

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












   int32_t install::start(const char * pszCommandLine, const char * pszBuild)
   {

      return System.install().asynch_install(pszCommandLine, pszBuild);

   }


   int32_t install::synch(const char * pszCommandLine, const char * pszBuild)
   {

      return System.install().synch_install(pszCommandLine, pszBuild);

   }


   void install::on_set_scalar(e_scalar escalar, int64_t iValue)
   {

      if (escalar == scalar_app_install_progress)
      {

         m_iProgressAppInstallStep = iValue;

      }
      else if (escalar == scalar_app_install_progress_min)
      {

         m_iProgressAppInstallStart = iValue;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         m_iProgressAppInstallEnd = iValue;

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

         i = m_iProgressAppInstallStart;

      }
      else if (escalar == scalar_app_install_progress_min)
      {

         i = 0;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         i = 0;

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

         i = m_iProgressAppInstallStep;

      }
      else if (escalar == scalar_app_install_progress_min)
      {

         i = m_iProgressAppInstallStart;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         i = m_iProgressAppInstallEnd;

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

         i = m_iProgressAppInstallEnd;

      }
      else if (escalar == scalar_app_install_progress_min)
      {

         i = 0x7fffffff;

      }
      else if (escalar == scalar_app_install_progress_max)
      {

         i = 0x7fffffff;

      }
      else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }




   string install::app_install_get_extern_executable_path(const char * pszVersion, const char * pszBuild, ::install::installer * pinstaller)
   {

      string strVersion(pszVersion);

      string strBuild(pszBuild);

      string strFormatBuild;

      strFormatBuild = ::str::replace(" ", "_", strBuild);

      bool bPrivileged = false;

      string strPath;

#ifdef WINDOWSEX

      xxdebug_box("installer::launcher::ensure_executable", "installer::launcher::ensure_executable", 0);

      HINSTANCE hinstanceAppInstall = (HINSTANCE) ::GetModuleHandleA("app.install.exe");

      bPrivileged = hinstanceAppInstall != NULL && hinstanceAppInstall == ::GetModuleHandleA(NULL);

      HINSTANCE hinstancePlugin = (HINSTANCE) ::GetModuleHandleA("npca2.dll");

      if (hinstancePlugin == NULL)
         hinstancePlugin = (HINSTANCE) ::GetModuleHandleA("iexca2.dll");

      if (hinstancePlugin != NULL)
      {

         char szModulePath[MAX_PATH * 3];

         ::GetModuleFileNameA((HINSTANCE)hinstancePlugin, szModulePath, sizeof(szModulePath));

         char * file = NULL;

         int iSpabootInstallStrSize = MAX_PATH * 16;

         LPSTR psz = strPath.GetBufferSetLength(iSpabootInstallStrSize);

         ::GetFullPathNameA(szModulePath, iSpabootInstallStrSize, psz, &file);

         file[0] = '\0';

         strcat_dup(psz, "app.install.exe");

         strPath.ReleaseBuffer();

      }
      else
      {

         string strPlatform = System.install().get_platform();

         strPath = ::dir::element("install\\stage\\" + strPlatform + "\\app.install.exe");

      }

#else

      throw "TODO";

#endif

      if (!file_exists_dup("C:\\ca2\\config\\do_not_download_file_list.txt") && bPrivileged)
      {

         trace().rich_trace("***Verifying installer");

         string strPathA(System.dir().path(System.dir().name(strPath), "base.dll"));
         string strPathB(System.dir().path(System.dir().name(strPath), "msvcp120d.dll"));
         string strPathC(System.dir().path(System.dir().name(strPath), "msvcr120d.dll"));
         string strPathD(System.dir().path(System.dir().name(strPath), "draw2d_gdiplus.dll"));
         string strPathE(System.dir().path(System.dir().name(strPath), "os.dll"));

         if (!file_exists_dup(strPath)
            || !System.install().is_file_ok(strPath, "app.install.exe", strFormatBuild)
            || !System.install().is_file_ok(strPathA, "base.dll", strFormatBuild)
            || !System.install().is_file_ok(strPathB, "msvcp120d.dll", strFormatBuild)
            || !System.install().is_file_ok(strPathC, "msvcr120d.dll", strFormatBuild)
            || !System.install().is_file_ok(strPathD, "draw2d_gdiplus.dll", strFormatBuild)
            || !System.install().is_file_ok(strPathE, "os.dll", strFormatBuild))
         {

            trace().rich_trace("***Downloading installer");

            stringa straFile;

            straFile.add("app.install.exe");
            straFile.add("base.dll");
            straFile.add("msvcp120d.dll");
            straFile.add("msvcr120d.dll");
            straFile.add("draw2d_gdiplus.dll");
            straFile.add("os.dll");

            string strFile;

            string strUrlPrefix = "http://ca2.cc/ccvotagus/" + strVersion + "/" + strFormatBuild + "/install/x86/";

            string strUrl;

            property_set set;

            string strDownload;

            set["disable_ca2_sessid"] = true;

            set["raw_http"] = true;

            double dRate = 1.0 / (straFile.get_count() * 3.0);

            if (pinstaller != NULL)
            {

               set["int_scalar_source_listener"] = pinstaller;

            }

            int32_t iRetry;

            bool bFileNice;

            for (index iFile = 0; iFile < straFile.get_count(); iFile++)
            {

               iRetry = 0;

               strFile = straFile[iFile];

               strUrl = strUrlPrefix + strFile + ".bz";

               strDownload = System.dir().path(System.dir().name(strPath), strFile);

               bFileNice = false;

               while (iRetry < 8)
               {

                  //if (!bPrivileged)
                  //{

                  //   if (!System.get_temp_file_name(strPath, "app.install", "exe"))
                  //   {

                  //      strPath.ReleaseBuffer();

                  //      return "";

                  //   }

                  //}


                  if (pinstaller != NULL)
                  {

                     pinstaller->m_dAppInstallProgressStart = iFile * (dRate  * 3.0);
                     pinstaller->m_dAppInstallProgressEnd = iFile * (dRate * 3.0) + dRate;

                  }

                  if (Application.http().download(strUrl, strDownload + ".bz", set))
                  {

                     System.compress().unbz(get_app(), strDownload, strDownload + ".bz");

                     if (pinstaller != NULL)
                     {

                        pinstaller->set_progress(iFile * (dRate * 3.0) + (dRate * 2.0));

                     }

                     if (System.install().is_file_ok(strDownload, strFile, strFormatBuild))
                     {

                        if (pinstaller != NULL)
                        {

                           pinstaller->set_progress(iFile * (dRate * 3.0) + (dRate * 2.0));

                           bFileNice = true;

                           break;



                        }

                     }


                  }

                  iRetry++;

               }

               if (!bFileNice)
               {
                  
                  // failed by too much retry in any number of the files already downloaded :
                  // so, return failure (no eligible app.install.exe file).
                  return "";

               }

            }

         }


         if (!System.install().is_file_ok(strPath, "app.install.exe", strFormatBuild))
         {

            return "";

         }

      }

      return strPath;

   }


   string install::app_install_get_intern_executable_path(const char * pszVersion, const char * pszBuild)
   {

      string strVersion(pszVersion);

      string strBuild(pszBuild);

      string strFormatBuild;

      strFormatBuild = ::str::replace(" ", "_", strBuild);

      string strPath;

#ifdef WINDOWSEX

      xxdebug_box("installer::launcher::ensure_executable", "installer::launcher::ensure_executable", 0);

      string strPlatform = System.install().get_platform();

      strPath = ::dir::element("stage\\" + strPlatform + "\\app.install.exe");

#else

      throw "TODO";

#endif

      return strPath;

   }

   bool install::reference_is_file_ok(const char * path1, const char * pszTemplate, const char * pszVersion, const char * pszFormatBuild)
   {

      string strVersion(pszVersion);

      string strFormatBuild(pszFormatBuild);

      string strUrl;

      strUrl = "http://" + strVersion + ".spaignition.api.server.ca2.cc/md5?version=" + strVersion + "&stage=";
      strUrl += pszTemplate;
      strUrl += "&build=";
      strUrl += strFormatBuild;

      property_set set(get_app());

      set["raw_http"] = true;

      bool bOk = file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), Application.http().get(strUrl, set));

      return bOk;

   }


} // namespace install







