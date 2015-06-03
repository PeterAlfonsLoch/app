//#include "framework.h"

//#if defined(LINUX) || defined(WINDOWS)
////#include <omp.h>
//#else
//int omp_get_thread_num()
//{
//   return 0;
//}
//#endif
//
//#if defined(LINUX)
//
////#include <unistd.h>
//
//#endif

namespace install
{


   install::install(::aura::application * papp) :
      ::object(papp),
      ::aura::departament(papp),
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

#ifdef X86

         m_strPlatform = "x86";

#else

         m_strPlatform = "x64";

#endif


      }

   install::~install()
   {

   }

   bool install::is_file_ok(const ::file::path & path1,const char * pszTemplate,const char * pszFormatBuild)
   {

      string strFormatBuild(pszFormatBuild);

      string strUrl;

      strUrl = "http://"+m_strVersion+"-server.ca2.cc/api/spaignition/md5?authnone&version="+m_strVersion+"&stage=";
      strUrl += pszTemplate;
      strUrl += "&build=";
      strUrl += strFormatBuild;

      property_set set(get_app());

      set["raw_http"] = true;

      return file_exists_dup(path1) && !stricmp_dup(System.file().md5(path1), Application.http().get(strUrl, set));

   }

   bool install::is_file_ok(const ::file::patha & patha,const ::file::patha & straTemplate,stringa & straMd5,int_array & iaLen, const string & strFormatBuild,int iMd5Retry)
   {

      bool bOk = true;

      if(patha.get_count() != straTemplate.get_count())
         return false;

      if(bOk)
      {

         for(index i = 0; i < patha.get_count(); i++)
         {

            if(!file_exists_dup(patha[i]))
            {

               bOk = false;

               break;

            }

         }

      }

      if(iMd5Retry > 0 || straMd5.get_count() != patha.get_count())
      {

         string strUrl;

         strUrl = "http://" + m_strVersion + "-server.ca2.cc/api/spaignition/md5a_and_lena?authnone&version=" + m_strVersion + "&stage=";
         strUrl += straTemplate.implode(",");
         strUrl += "&build=";
         strUrl += strFormatBuild;

         property_set set(get_app());

         set["raw_http"] = true;

         string strMd5List = Application.http().get(strUrl,set);

         straMd5.remove_all();

         straMd5.add_tokens(strMd5List,",",false);

         if(straMd5.get_count() != patha.get_count())
         {
            straMd5.remove_all();
            return false;
         }

         iaLen.set_size(straMd5.get_size());

         for(index i = 0; i < straMd5.get_size(); i++)
         {

            string strMd5AndLen = straMd5[i];
            int iFind =strMd5AndLen.find('|');
            if(iFind < 0)
            {
               iaLen.remove_all();
               straMd5.remove_all();
               return false;
            }
            string strMd5 = strMd5AndLen.Left(iFind);
            straMd5[i] = strMd5;
            straMd5[i].trim();
            if(straMd5[i].get_length() != 32)
            {
               iaLen.remove_all();
               straMd5.remove_all();
               return false;
            }
            iaLen[i] = atoi(strMd5AndLen.Mid(iFind + 1));
         }


         if(!bOk)
            return false;

      }

      for(index i = 0; i < straMd5.get_count(); i++)
      {

         if(System.file().md5(patha[i]).CompareNoCase(straMd5[i]) != 0)
            return false;

      }

      return true;

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


   CLASS_DECL_AXIS bool install::app_install_send_short_message(const char * psz, bool bLaunch, const char * pszBuild)
   {

#ifdef METROWIN

      throw "todo";

#else

      small_ipc_tx_channel txchannel;

      installer::launcher launcher(get_app(), m_strVersion, pszBuild);

      if (!txchannel.open(::small_ipc_channel::app_install(m_strPlatform), bLaunch ? &launcher : NULL))
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

      return m_strPlatform;

   }


   void install::set_platform(const string & strPlatform)
   {

      m_strPlatform = strPlatform;

   }


   bool install::is_installed(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
   {

      return is(pszVersion, pszBuild, pszType, pszId, pszLocale, pszSchema);

   }

   string install::get_latest_build_number(const char * pszVersion)
   {

      string strLatestBuildNumber = m_strmapLatestBuildNumber[pszVersion];

      if (!strLatestBuildNumber.is_empty() && (get_tick_count() - m_dwLatestBuildNumberLastFetch) < ((5000) * 3))
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

      string strVersion(pszVersion);

      if(file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt").has_char())
      {

         strSpaIgnitionBaseUrl = "https://" + file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt") + "/api/spaignition";

      }
/*      else if(pszVersion != NULL && !strcmp(pszVersion,"basis"))
      {

         strSpaIgnitionBaseUrl = "http://basis-server.ca2.cc/api/spaignition";

      }
      else if (pszVersion != NULL && !strcmp(pszVersion, "stage"))
      {

         strSpaIgnitionBaseUrl = "http://stage-server.ca2.cc/api/spaignition";

      } */
      else
      {

         strSpaIgnitionBaseUrl = "http://api.ca2.cc/spaignition";

         /*if(m_strVersion == "basis")
         {

            strVersion = "basis";

            strSpaIgnitionBaseUrl = "http://basis-server.ca2.cc/api/spaignition";

         }
         else
         {

            strVersion = "stage";

            strSpaIgnitionBaseUrl = "http://stage-server.ca2.cc/api/spaignition";

         }*/

      }

      int32_t iRetry = 0;

   RetryBuildNumber:

      if (iRetry > 3)
      {

         return "";

      }

      iRetry++;

      property_set set(get_app());

      set["raw_http"] = true;

      strBuildNumber = Application.http().get(strSpaIgnitionBaseUrl + "/query?node=build&version=" + strVersion, set);

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
         //::aura::library libraryOs(get_app());
         //m_bCa2Installed = libraryOs.open(dir::path(strStage, "os"));
         //if (m_bCa2Installed)
         //{
         ::aura::library libraryCa2(get_app());
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

      if(m_strVersion == "basis")
      {

         m_strCa2Build = Application.http().get("http://basis-server.ca2.cc/api/spaignition/ca2_get_build?authnone",set);

      }
      else
      {

         m_strCa2Build = Application.http().get("http://stage-server.ca2.cc/api/spaignition/ca2_get_build?authnone",set);

      }

   }


   const char * install::ca2_get_build()
   {
      update_ca2_build();
      return m_strCa2Build;
   }


   void install::set_ca2_updated(const char * pszBuild)
   {
      Application.dir().mk(System.dir().element() / "appdata" / get_platform());
      Application.file().put_contents(System.dir().element() / "appdata" / get_platform() / "ca2_build.txt", pszBuild);
   }


   void install::set_updated(const char * pszBuild)
   {
      Application.dir().mk(System.dir().element() / "appdata" / get_platform());
      Application.file().put_contents(System.dir().element() / "appdata" / get_platform() / "build.txt",pszBuild);
   }



   void install::add_spa_start(const char * pszType, const char * pszId)
   {

      ::file::path strPath;

      strPath = System.dir().appdata() / "spa_start.xml";

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

      ::file::path strPath;

      strPath = System.dir().appdata()/"spa_start.xml";

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

      ::file::path path;

      path = System.install_meta_dir(m_strVersion,pszBuild,pszType,pszId,pszLocale,pszSchema) / "installed.txt";

      Application.file().put_contents(path,"");

      string strBuildPath;

      strBuildPath = System.dir().commonappdata() / "spa_build_" + get_platform() + ".txt";

      string strNewBuildNumber = Application.file().as_string(strBuildPath);

      string strBuild(pszBuild);

      if(strBuild.has_char() && isdigit_dup(strBuild[0]))
      {

         Application.file().put_contents(strBuildPath, strBuild);

      }
      else if(strBuild.CompareNoCase("latest") == 0 && m_strmapLatestBuildNumber[m_strVersion].has_char() && isdigit_dup(m_strmapLatestBuildNumber[m_strVersion][0]))
      {

         Application.file().put_contents(strBuildPath,m_strmapLatestBuildNumber[m_strVersion]);

      }



   }


   bool install::is(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
   {

      return System.install_is(pszVersion,pszBuild,pszType,pszId,pszLocale,pszSchema);

   }












   int32_t install::start(const char * pszCommandLine, const char * pszBuild)
   {

      return System.install().asynch_install(pszCommandLine, pszBuild);

   }


   int32_t install::synch(const char * pszCommandLine, const char * pszBuild)
   {

      return System.install().synch_install(pszCommandLine, pszBuild);

   }


   void install::on_set_scalar(e_scalar escalar,int64_t iValue,int iFlags)
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

         return ::int_scalar_source::on_set_scalar(escalar,iValue,iFlags);

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

#ifdef WINDOWSEX

   string get_module_path(HMODULE hmodule)
   {
      wstring wstrPath;
      DWORD dwSize = 1;
      while(natural(wstrPath.get_length() + 1) == dwSize)
      {
         dwSize = ::GetModuleFileNameW(
            hmodule,
            wstrPath.alloc(dwSize + 1024),
            (dwSize + 1024));
         wstrPath.release_buffer();
      }
      return ::str::international::unicode_to_utf8(wstrPath);
   }

#endif

   string install::app_install_get_extern_executable_path(const char * pszVersion,const char * pszBuild,stringa * pstraMd5,int_array * piaLen,::install::installer * pinstaller,string_to_string * pmapMd5,string_to_intptr * pmapLen)
   {

      string strVersion(pszVersion);

      string strBuild(pszBuild);

      string strFormatBuild;

      strFormatBuild = ::str::replace(" ", "_", strBuild);

      bool bPrivileged = false;

      ::file::path strPath;

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

      if (!file_exists_dup("C:\\ca2\\config\\plugin\\do_not_download_file_list.txt") && bPrivileged)
      {

         trace().rich_trace("***Verifying installer");

         ::file::patha straFile;

         ::lemon::array::copy(straFile, ::install_get_plugin_base_library_list(pszVersion));

         if(!::dir::is(strPath.folder()))
         {

            ::dir::mk(strPath.folder());

         }

         ::file::patha straDownload;

         for(index iFile = 0; iFile < straFile.get_size(); iFile++)
         {

            ::file::path strFile = straFile[iFile];

            ::file::path strDownload = strPath.sibling(strFile);

            straDownload.add(strDownload);

         }

         stringa straMd5;

         int_array iaLen;

         if(pstraMd5 != NULL)
         {

            straMd5 = *pstraMd5;

         }

         if(piaLen != NULL)
         {

            iaLen = *piaLen;

         }

         int iMd5Retry = 0;

         md5retry:

         if(!System.install().is_file_ok(straDownload,straFile,straMd5,iaLen, strFormatBuild, iMd5Retry))
         {


            if(straMd5.get_count() != straFile.get_count())
            {

               iMd5Retry++;

               if(iMd5Retry < 8)
                  goto md5retry;

               return "";

            }

#ifdef WINDOWSEX

            // first try to copy from current path (may be there is a version of app.install at the same folder).

            HMODULE hmodule = ::GetModuleHandle("aura.dll");

            if(hmodule != NULL)
            {

               ::file::path str = get_module_path(hmodule);

               if(str.has_char())
               {

                  ::file::path strAuraDir = str.folder();

                  for(index iFile = 0; iFile < straFile.get_size(); iFile++)
                  {

                     ::file::path strFile = strAuraDir / straFile[iFile];

                     if(!file_exists_dup(straDownload[iFile]) && file_exists_dup(strFile) && System.file().md5(strFile) == straMd5[iFile])
                     {

                        ::file_copy_dup(straDownload[iFile], strFile, false);

                     }

                  }


               }


            }

#endif

            single_lock sl(pinstaller != NULL ? &pinstaller->m_mutexOmp : NULL);


            {

               if(pinstaller != NULL)
               {

                  pinstaller->m_daProgress.remove_all();
                  pinstaller->m_daProgress.add(0.0);
                  pinstaller->m_dAppInstallFileCount = straFile.get_size();
                  pinstaller->m_dAppInstallProgressBase = 0.0;

               }
            }

#pragma omp parallel for
            for(index iFile = 0; iFile < straFile.get_size(); iFile++)
            {

               ::file::path strFile = straFile[iFile];

               ::file::path strDownload = strPath.sibling(strFile);

               if(pinstaller != NULL)
               {
                  sl.lock();
                  pinstaller->m_daProgress.element_at_grow(omp_get_thread_num() + 1)  = 0.0;
                  sl.unlock();
               }

               if(!file_exists_dup(strDownload) || System.file().md5(strDownload).CompareNoCase(straMd5[iFile]) != 0)
               {

                  trace().rich_trace("***Downloading installer");

                  string strUrlPrefix = "http://server.ca2.cc/ccvotagus/" + strVersion + "/" + strFormatBuild + "/install/" + System.install().get_platform() + "/";

                  string strUrl;

                  property_set set;

                  set["disable_ca2_sessid"] = true;

                  set["raw_http"] = true;

                  if(pinstaller != NULL)
                  {

                     set["int_scalar_source_listener"] = pinstaller;

                  }

                  int32_t iRetry;

                  bool bFileNice;

                  iRetry = 0;

                  strUrl = strUrlPrefix + strFile + ".bz";

                  bFileNice = false;


                  sl.lock();
                  ::sockets::http_session * & psession = m_httpsessionptra.element_at_grow(omp_get_thread_num() + 1);
                  sl.unlock();


                  while(iRetry < 8 && !bFileNice)
                  {




                     if((psession = Application.http().download(psession,strUrl,strDownload + ".bz",set)) != NULL)
                     {

                        System.compress().unbz(get_app(),strDownload,strDownload + ".bz");

                        if(file_exists_dup(strDownload) && System.file().md5(strDownload).CompareNoCase(straMd5[iFile]) == 0)
                        {

                              bFileNice = true;

                        }


                     }

                     iRetry++;

                  }

                  if(!bFileNice)
                  {

                     // failed by too much retry in any number of the files already downloaded :
                     // so, return failure (no eligible app.install.exe file).
                     //return "";

                  }
                  else
                  {
                     if(pinstaller != NULL)
                     {
                        sl.lock();
                        pinstaller->m_daProgress.element_at_grow(omp_get_thread_num() + 1)  = 0.0;
                        pinstaller->m_dAppInstallProgressBase += 1.0;
                        sl.unlock();
                     }

                  }


               }
               else
               {
                  if(pinstaller != NULL)
                  {
                     sl.lock();
                     pinstaller->m_daProgress.element_at_grow(omp_get_thread_num() + 1)  = 0.0;
                     pinstaller->m_dAppInstallProgressBase += 1.0;
                     sl.unlock();
                  }
               }

            }

         }


         //if (!System.install().is_file_ok(strPath, "app.install.exe", strFormatBuild))
         //{

         //   return "";

         //}

         if(pmapMd5 != NULL || pmapLen != NULL)
         {

            for(index iFile = 0; iFile < straFile.get_count(); iFile++)
            {

               ::file::path strFile = straFile[iFile];

               string strMap = "stage\\" + System.install().get_platform() + "\\" + strFile;

               if(pmapMd5 != NULL)
               {

                  pmapMd5->set_at(strMap,straMd5[iFile]);

               }

               if(pmapLen != NULL)
               {

                  pmapLen->set_at(strMap,iaLen[iFile]);

               }

            }

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

      ::file::path strPath;

#ifdef WINDOWSEX

      xxdebug_box("installer::launcher::ensure_executable", "installer::launcher::ensure_executable", 0);

      string strPlatform = System.install().get_platform();

      strPath = ::dir::element("stage\\" + strPlatform + "\\app.install.exe");

#else

      throw "TODO";

#endif

      return strPath;

   }


   bool install::reference_is_file_ok(const ::file::path & path1,const char * pszTemplate,const char * pszVersion,const char * pszFormatBuild)
   {

      string strVersion(pszVersion);

      string strFormatBuild(pszFormatBuild);

      string strUrl;

      strUrl = "http://" + strVersion + ".spaignition.api.server.ca2.cc/md5?version=" + strVersion + "&stage=";
      strUrl += pszTemplate;
      strUrl += "&build=";
      strUrl += strFormatBuild;
      strUrl += "&platform=";
      strUrl += get_platform();
        

      property_set set(get_app());

      set["raw_http"] = true;

      bool bOk = file_exists_dup(path1) && !stricmp_dup(System.file().md5(path1), Application.http().get(strUrl, set));

      return bOk;

   }


} // namespace install







