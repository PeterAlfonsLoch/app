#include "framework.h"
#include <sys/stat.h>


#if defined(LINUX)
#include <ctype.h>
#endif


namespace dynamic_source
{

   string escape(const char * lpcsz);

   void add_var_id(string & strResult, strsize & iArroba, stringa & straId, bool bMakeKeyLower = true);


   script_compiler::script_compiler(sp(base_application) papp) :
      element(papp),
      m_memfileLibError(papp),
      m_mutexLibrary(papp),
      m_libraryLib(papp)
   {

#if defined(MEMDLEAK)

      m_strDynamicSourceConfiguration = "memdleak";

#elif defined(DEBUG)

      m_strDynamicSourceConfiguration = "basis";

#else

      m_strDynamicSourceConfiguration = "profiler";

#endif

   }

   script_compiler::~script_compiler()
   {
   }

   void script_compiler::initialize()
   {
      prepare_compile_and_link_environment();
      folder_watch();
      compile_library();
      run_persistent();
   }

   void script_compiler::prepare_compile_and_link_environment()
   {
      //string strVars = getenv("VS100COMNTOOLS");
      string strVars;

#ifndef METROWIN

      strVars = getenv("VS120COMNTOOLS");

#endif

      System.file().path().eat_end_level(strVars, 2, "\\");
      m_strEnv = strVars;
      m_strEnv = System.dir().path(strVars, "vc\\vcvarsall.bat");
      //m_strEnv = ".\\vc_vars.bat";

      m_strTime = System.dir().element("time");

      //m_strEnv = "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Bin\\SetEnv.cmd";

      //m_strSdk1 = "windows7.1sdk";
      m_strSdk1 = "vc120";
      string strPlat2;
#ifdef _M_X64
      m_strPlat1     = "64";
      strPlat2 = "  x86_amd64";
      m_strPlatform = "x64";
      m_strLibPlatform = "x64/";
#else
      m_strPlat1     = "";
      strPlat2 = " /x86";
      m_strPlatform = "x86";
      m_strLibPlatform = "";
#endif

      //System.file().lines(m_straSync, "C:\\core\\database\\text\\dynamic_source\\syncer.txt", get_app());
#if defined(LINUX)
      prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bash",
         m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bash",
         m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bash",
         m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bash");
#else
      prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat",
         m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat");
      prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat",
         m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat");
      prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat",
         m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat");
#endif
      System.dir().mk(System.dir().element("stage/front"), get_app());

#ifdef WINDOWS
      string vars1batSrc;
      string vars2batSrc;
      string vars1batDst;
      string vars2batDst;
      vars1batSrc = System.dir().element("nodeapp/stage/dynamic_source/vc_vars.bat");
      vars2batSrc = System.dir().element("nodeapp/stage/dynamic_source/vc_vars_query_registry.bat");
      vars1batDst = System.dir().element("stage/front", "vc_vars.bat");
      vars2batDst = System.dir().element("stage/front", "vc_vars_query_registry.bat");
      try
      {
         Application.file().copy(vars1batDst, vars1batSrc, false);
      }
      catch(...)
      {
      }
      try
      {
         Application.file().copy(vars2batDst, vars2batSrc, false);
      }
      catch(...)
      {
      }

#endif


#ifdef METROWIN

      throw todo(get_app());

#elif defined(LINUX)
#else
      var var = System.process().get_output("\"" + m_strEnv  + "\" "+ strPlat2);
      TRACE0(var.get_string());

#endif

      string str;
      string strItem;

      strItem = System.dir().element("stage\\" + m_strPlatform);
      str = str + strItem + ";";

      strItem = System.dir().element("stage\\" + m_strPlatform + "\\dynamic_source\\library");
      str = str + strItem + ";";
#ifdef WINDOWSEX
      uint32_t dwSize = GetEnvironmentVariable("PATH", NULL, 0);
      LPTSTR lpsz = new char[dwSize + 1];
      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1);
      str += lpsz;
      delete lpsz;
#elif defined(METROWIN)

      throw todo(get_app());

#else
      str += getenv("PATH");
#endif
      bool bResult;
#ifdef WINDOWSEX
      bResult = SetEnvironmentVariable("PATH", str) != FALSE;
#elif defined(METROWIN)

      throw todo(get_app());

#elif defined(LINUX)
#else
      bResult = setenv("PATH", str, TRUE);
#endif
      TRACE("script_compiler::prepare_compile_and_link_environment SetEnvironmentVariable return bool %d", bResult);

   }

   void script_compiler::compile(ds_script * pscript)
   {
      
      single_lock slScript(&pscript->m_mutex, TRUE);
      
      TRACE("Compiling script \"%s\"\n", pscript->m_strName.c_str());
      
      string strName(pscript->m_strName);
      
      pscript->on_start_build();

#ifdef WINDOWS

      strName.replace("/", "\\");

#endif

      //strName.replace("/", "\\");
      //string strFolder;
      //strFolder = System.dir().element();
      string str;
      string strB;
      string strO;
      string strP;
      string strL;
      string strE;
      string strSVI;
      string strSVP;
      string strSPCH;
      string strDVI;
      string strDVP;
      string strDPCH;

      /*string strScript(strName);
      strScript.replace("\\", ",");
      strScript.replace("/", ",");
      strScript = "ca2" + m_pmanager->m_strNamespace + "_script." + strScript;*/
      string strScript;
      strScript = System.file().title_(strName);
      string strTransformName = strName;
      if(Application.file().exists(strName))
      {
         pscript->m_strSourcePath = strName;
         strTransformName.replace(":", "");
      }
      else
      {
         pscript->m_strSourcePath.Format(System.dir().path(m_pmanager->m_strNetnodePath, "net\\netseed\\%s", false), strName);
      }
      pscript->m_strSourceDir = System.dir().name(pscript->m_strSourcePath);

      if(!Application.file().exists(pscript->m_strSourcePath))
      {
         pscript->m_memfileError<< "<pre>";
         str.Format("Source File : \"%s\" does not exist", pscript->m_strSourcePath);
         pscript->m_memfileError << str;
         pscript->m_memfileError<< "</pre>";
         return;
      }


      string strTime = m_strTime;


      pscript->m_strCppPath.Format(System.dir().path(m_strTime, "dynamic_source\\%s.cpp", false), strTransformName);
      //#ifdef DEBUG
#ifdef LINUX
      pscript->m_strBuildBat.Format(System.dir().stage("front\\dynamic_source\\BuildBat\\%s%s.bat"), System.file().name_(strTransformName), strTransformName);
      strO.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\%s\\%s.o", false), strTransformName, System.file().name_(strTransformName));
      pscript->m_strScriptPath = System.dir().path(System.dir().stage(m_strPlatform+"\\dynamic_source"), System.dir().path(System.dir().name(strTransformName), strScript + ".so", false));
#else
      pscript->m_strBuildBat.Format(System.dir().stage("front\\dynamic_source\\BuildBat\\%s\\%s.bat"), System.file().name_(strTransformName), strTransformName);
      strO.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\%s\\%s.obj", false), strTransformName, System.file().name_(strTransformName));
      strP.Format(System.dir().stage(m_strPlatform+"\\dynamic_source\\%s.pdb"), System.dir().path(System.dir().name(strTransformName), strScript, false));
      strL.Format(System.dir().stage(m_strPlatform+"\\dynamic_source\\%s.lib"), System.dir().path(System.dir().name(strTransformName), strScript, false));
      strE.Format(System.dir().stage(m_strPlatform+"\\dynamic_source\\%s.exp"), System.dir().path(System.dir().name(strTransformName), strScript, false));
      strDVI.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\%s\\" + m_strSdk1 + ".idb", false), strTransformName);
      strDVP.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\%s\\" + m_strSdk1 + ".pdb", false), strTransformName);
      strDPCH.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\%s\\" + m_pmanager->m_strNamespace + "_dynamic_source_script.pch", false), strTransformName);
      strSVI.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\" + m_strSdk1 + ".idb", false), strTransformName);
      strSVP.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\" + m_strSdk1 + ".pdb", false), strTransformName);
      strSPCH.Format(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script\\" + m_pmanager->m_strNamespace + "_dynamic_source_script.pch", false), strTransformName);
      pscript->m_strScriptPath = System.dir().path(System.dir().stage(m_strPlatform+"\\dynamic_source"), System.dir().path(System.dir().name(strTransformName), strScript + ".dll", false));
#endif
      //#else
      // pscript->m_strLibraryPath.Format(System.dir().stage("Release\\%s.dll"), strName);
      //#endif

      try
      {
         if(Application.file().exists(strO))
         {
            System.file().del(strO);
         }
      }
      catch(...)
      {
      }
#ifndef LINUX
      try
      {
         if(Application.file().exists(strP))
         {
            System.file().del(strP);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Application.file().exists(strL))
         {
            System.file().del(strL);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Application.file().exists(strE))
         {
            System.file().del(strE);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Application.file().exists(strDPCH))
         {
            System.file().del(strDPCH);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Application.file().exists(strDVP))
         {
            System.file().del(strDVP);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Application.file().exists(strDVI))
         {
            System.file().del(strDVI);
         }
      }
      catch(...)
      {
      }
#endif
      //::DeleteFile(pscript->m_strBuildBat);
      try
      {
         if(Application.file().exists(pscript->m_strScriptPath + ".old"))
         {
            System.file().del(pscript->m_strScriptPath + ".old");
         }
      }
      catch(string strError)
      {
         TRACE0(strError + "\n");
      }
      try
      {
         if(Application.file().exists(pscript->m_strScriptPath))
         {
            System.file().move(pscript->m_strScriptPath + ".old", pscript->m_strScriptPath);
         }
      }
      catch(string strError)
      {
         TRACE0(strError + "\n");
      }
      try
      {
         if(Application.file().exists(pscript->m_strScriptPath + ".old"))
         {
            System.file().del(pscript->m_strScriptPath + ".old");
         }
      }
      catch(string strError)
      {
         TRACE0(strError + "\n");
      }
#ifndef LINUX

      Application.dir().mk(System.dir().name(strDVI));
      Application.dir().mk(System.dir().name(pscript->m_strBuildBat));
      try
      {
         //         Application.file().copy(strDVI, strSVI, false);
      }
      catch(...)
      {
      }
      try
      {
         Application.file().copy(strDVP, strSVP, false);
      }
      catch(...)
      {
      }
      try
      {
         Application.file().copy(strDPCH, strSPCH, false);
      }
      catch(...)
      {

         pscript->m_bHasTempOsError = true;

         return;

      }



      string vars1batSrc;
      string vars2batSrc;
      string vars1batDst;
      string vars2batDst;
      vars1batSrc = System.dir().element("nodeapp/stage/dynamic_source/vc_vars.bat");
      vars2batSrc = System.dir().element("nodeapp/stage/dynamic_source/vc_vars_query_registry.bat");
      vars1batDst = System.dir().path(System.dir().name(pscript->m_strBuildBat), "vc_vars.bat", false);
      vars2batDst = System.dir().path(System.dir().name(pscript->m_strBuildBat), "vc_vars_query_registry.bat", false);
      try
      {
         Application.file().copy(vars1batDst, vars1batSrc, false);
      }
      catch(...)
      {
      }
      try
      {
         Application.file().copy(vars2batDst, vars2batSrc, false);
      }
      catch(...)
      {
      }


#endif

      Application.dir().mk(System.dir().name(pscript->m_strScriptPath));
      Application.dir().mk(System.dir().name(strL));
      Application.dir().mk(System.dir().path(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_script", false), strTransformName));

      cppize(pscript);

      string strV(System.dir().element());
      strV.replace("\\", "/");
      if(!::str::ends(strV, "/") && !::str::ends(strV, "\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;

      string strBuildCmd;
#ifdef LINUX
      strBuildCmd.Format(System.dir().element("nodeapp\\stage\\dynamic_source\\" + m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash"));
#else
      //#ifdef DEBUG
      strBuildCmd.Format(System.dir().element("nodeapp\\stage\\dynamic_source\\" + m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bat"));
      //#else
      // strBuildCmd.Format(System.dir().stage("front\\dynamic_source_cl.bat"));
      //#endif
#endif
      str = Application.file().as_string(strBuildCmd);
      str.replace("%ITEM_NAME%", strTransformName);
      str.replace("%ITEM_TITLE%", System.file().name_(strTransformName));
      str.replace("%ITEM_DIR%", System.dir().name(strTransformName));
      str.replace("%LIBS_LIBS%", m_strLibsLibs);
      str.replace("%VS_VARS%", m_strEnv);
      string strPlat2;
#ifdef _M_X64
      strPlat2 = "x86_amd64";
#else
      strPlat2 = " /x86";
#endif
      str.replace("%VS_VARS_PLAT2%", strPlat2);


      str.replace("%CA2_ROOT%", strV);
      str.replace("%NETNODE_ROOT%", strN);
      str.replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
      str.replace("%PLATFORM%", m_strPlatform);
      str.replace("%LIBPLATFORM%", m_strLibPlatform);
      str.replace("%SDK1%", m_strSdk1);
      string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX
      ::str::ends_eat_ci(strTargetPath, ".so");
#else
      ::str::ends_eat_ci(strTargetPath, ".dll");
#endif
      str.replace("%TARGET_PATH%", strTargetPath);
      strBuildCmd = pscript->m_strBuildBat;
      //Application.file().put_contents_utf8(strBuildCmd, str);

      Application.file().put_contents(strBuildCmd, str);

      bool bTimeout = false;

#ifndef METROWIN

      ::core::process process;

      process.create_child_process(strBuildCmd, false, System.dir().name(pscript->m_strBuildBat), ::core::scheduling_priority_highest);

      uint32_t dwStart = ::get_tick_count();
      uint32_t dwExitCode;
      while(true)
      {
         if(process.has_exited(&dwExitCode))
            break;
         Sleep(84);
         if(::get_tick_count() - dwStart > 5 * 60 * 1000) // 5 minutes
         {
            bTimeout = true;
            break;
         }
      }
      //system(strCmd);

      //   TRACE0(strBuildCmd);
      // var varBuildOutput;
      //varBuildOutput = System.process().get_output(strBuildCmd);

      /*TRACE0(strLinkCmd);
      var varLinkOutput;
      varLinkOutput = System.process().get_output(strLinkCmd);*/

#else

      throw todo(get_app());

#endif


#ifdef LINUX

      Sleep(1984);

#endif
      pscript->m_memfileError.m_spbuffer->set_length(0);
      pscript->m_memfileError << "<pre>";

      pscript->m_memfileError << "Compiling...\n";
      pscript->m_memfileError << pscript->m_strCppPath;
      pscript->m_memfileError << "\n";
      if(bTimeout)
      {
         pscript->m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + pscript->m_strCppPath +"\" following this message, they may be out-of-date)";
      }
      str.Format(System.dir().path(m_strTime, "dynamic_source\\%s-compile-log.txt", false), strTransformName);
      str = Application.file().as_string(str);
      str.replace("\r\n", "\n");
      pscript->m_memfileError << str;

      pscript->m_memfileError<< "Linking...\n";
      str.Format(System.dir().path(m_strTime, "dynamic_source\\%s-link-log.txt", false), strTransformName);
      str = Application.file().as_string(str);
      str.replace("\r\n", "\n");
      pscript->m_memfileError << str;
      pscript->m_memfileError << "</pre>";

#ifndef LINUX

      try
      {
         System.file().del(strDVI);
      }
      catch(...)
      {
      }
      try
      {
         System.file().del(strDVP);
      }
      catch(...)
      {
      }
      try
      {
         System.file().del(strDPCH);
      }
      catch(...)
      {
      }

#endif
      pscript->m_dwLastBuildTime = ::get_tick_count();

      // Wait for finalization of build
      // or delay in case of error to avoid run conditions due extreme overload.
      //Sleep(pscript->m_pmanager->m_dwBuildTimeWindow +
      // System.math().RandRange(0, pscript->m_pmanager->m_dwBuildTimeRandomWindow));
      pscript->m_bShouldBuild =false;
#ifdef WINDOWSEX

      HANDLE h = create_file(pscript->m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      try
      {
         memset(&pscript->m_ftCreation, 0, sizeof(FILETIME));
         memset(&pscript->m_ftModified, 0, sizeof(FILETIME));
         ::GetFileTime(h, &pscript->m_ftCreation, NULL, &pscript->m_ftModified);
      }
      catch(...)
      {
      }

      ::CloseHandle(h);

#elif defined(METROWIN)

      ::Windows::Storage::StorageFile ^ h = get_os_file(pscript->m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      try
      {
         memset(&pscript->m_ftCreation, 0, sizeof(FILETIME));
         memset(&pscript->m_ftModified, 0, sizeof(FILETIME));
         ::get_file_time(h, &pscript->m_ftCreation, NULL, &pscript->m_ftModified);
      }
      catch(...)
      {
      }


#else
      //      HANDLE h = ::CreateFile(pscript->m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      memset(&pscript->m_ftCreation, 0, sizeof(__time_t));
      memset(&pscript->m_ftAccess, 0, sizeof(__time_t));
      memset(&pscript->m_ftModified, 0, sizeof(__time_t));

      struct stat st;

      stat(pscript->m_strSourcePath, &st);

      pscript->m_ftCreation = st.st_ctime;
      pscript->m_ftAccess = st.st_atime;
      pscript->m_ftModified = st.st_mtime;

#endif

   }

   void script_compiler::cppize(ds_script * pscript)
   {
      Application.dir().mk(System.dir().name(pscript->m_strCppPath));
      cppize1(pscript);
   }

   string escape(const char * lpcsz)
   {
      string str(lpcsz);
      str.replace("\\", "\\\\");
      str.replace("\"", "\\\"");
      str.replace("\r\n", "\\r\\n");
      str.replace("\r", "\\r\\n");
      str.replace("\n", "\\r\\n");
      str.replace("\t", "\\t");
      return str;
   }

   void script_compiler::cppize1(ds_script * pscript)
   {
      /*::file::binary_buffer_sp spfile(allocer());
      if(!spfile->open(pscript->m_strSourcePath, ::file::type_binary | ::file::mode_read | ::file::share_deny_none))
      return;

      primitive::memory memstorage;
      memstorage.allocate(spfile->get_length() + 1);
      memstorage.get_data()[memstorage.get_size() - 1] = '\0';
      memstorage.read(file);*/
      string strSource = Application.file().as_string(pscript->m_strSourcePath);
      strsize iPosId = -1;
      stringa straId;
      string strDest;
      strDest = "";
      strDest += "#include \"framework.h\"\r\n";
      strDest += "#include \"11ca2_fontopus.h\"\r\n";
      for(int32_t i = 0; i < m_straLibIncludePath.get_count(); i++)
      {
         string str;
         str = m_straLibIncludeRelPath[i];
         ::str::ends_eat_ci(str, ".ds");
         strDest += "#include \""+str+".h\"\r\n";
      }
      strsize iStart = 0;
      strsize iPos = 0;
      strsize iLastEnd = 0;
      if(strSource.Mid(0, 4) == "<?ss")
      {
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.Mid(iPos + 4, iLastEnd - iPos - 6), false, straId);
            iStart = iLastEnd;
         }
      }
      else if(strSource.Mid(0, 7) == "<? //ss")
      {
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.Mid(iPos + 7, iLastEnd - iPos - 7 - 2), false, straId);
            iStart = iLastEnd;
         }
      }
      string strDs;
      if(strSource.Mid(iStart, 4) == "<?ds")
      {
         iStart +=4;
         while(true)
         {
            strsize iMid = strSource.find("?>", iStart);
            iLastEnd = strSource.find("ds?>", iStart);
            if(iMid > 0 && iMid < iLastEnd)
            {
               strDs += cppize2(strSource.Mid(iStart, iMid - iStart), true, straId);
               iStart = iMid + 2;
               iMid = strSource.find("<?", iStart);
               if(iMid < iLastEnd)
               {
                  strDs += get_ds_print(strSource.Mid(iStart, iMid - iStart));
               }
               iStart = iMid + 2;
               continue;
            }
            if(iLastEnd > 0)
            {
               strDs += cppize2(strSource.Mid(iStart, iLastEnd - iStart), true, straId);
               iStart = iLastEnd + 4;
               iLastEnd = iStart;
            }
             break;
         }
      }
      strDest += "\r\n";
      strDest += "\r\n";
      iPosId = strDest.get_length();
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "class " + m_pmanager->m_strNamespace + "_dynamic_source_script : virtual public ::" + m_pmanager->m_strNamespace + "::script_instance\r\n";
      strDest += "{\r\n";
      strDest += "public:\r\n";
      strDest += "   " + m_pmanager->m_strNamespace + "_dynamic_source_script(dynamic_source::script * pscript) : element(pscript->get_app()), dynamic_source::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_impl(pscript) {};  \r\n";
      strDest += "   virtual void run();\r\n";
      strDest += "   \r\n\r\n";
      strDest += strDs;
      strDest += "   \r\n\r\n\r\n";
      strDest += "};\r\n";
      strDest += "\r\n";
      strDest += "extern \"C\" dynamic_source::script_instance * __cdecl create_dynamic_source_script_instance (dynamic_source::script * pscript)\r\n";
      strDest += "{\r\n";
      strDest += "   return dynamic_cast < dynamic_source::script_instance * > (canew(" + m_pmanager->m_strNamespace + "_dynamic_source_script(pscript)));\r\n";
      strDest += "}\r\n";
      strDest += "\r\n";
      strDest += "void " + m_pmanager->m_strNamespace + "_dynamic_source_script::run()\r\n";
      strDest += "{\r\n";
      strDest += "//Start parsed user script\r\n";
      straId.remove_all();
      while((iPos = strSource.find("<?", iStart)) >= 0)
      {
         if(iPos > iLastEnd)
         {
            strDest += get_ds_print(strSource.Mid(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd < 0)
            break;
         iLastEnd += 2;
         int32_t iShift = 0;
         if(strSource.Mid(iPos, 5).CompareNoCase("<?php") == 0)
            iShift = 3;
         strDest += cppize2(strSource.Mid(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), true, straId);
         iStart = iLastEnd;
      }
      strDest += get_ds_print(strSource.Mid(iStart));
      strDest += "//End parsed user script\r\n";
      strDest += "}\r\n";

      string strId;
      for(int32_t i = 0; i < straId.get_size(); i++)
      {
         strId += "static class id lscript_id" + ::str::from(i) + "(\"" + straId[i] + "\");\r\n";
      }

      strDest = strDest.Left(iPosId) + strId + strDest.Mid(iPosId);

      //Application.file().put_contents_utf8(pscript->m_strCppPath, strDest);
      Application.file().put_contents(pscript->m_strCppPath, strDest);

   }

   void script_compiler::prepare1(const char * lpcszSource, const char * lpcszDest)
   {
      string strFolder;
      strFolder = System.dir().element();
      if(!::str::ends(strFolder, "/") && !::str::ends(strFolder, "\\"))
         strFolder += "/";
      string strTemplate;
      string strSource = "nodeapp\\stage\\dynamic_source\\";
      strSource += lpcszSource;

      string strN = m_pmanager->m_strNetnodePath;

      //#ifdef DEBUG
      strTemplate = System.dir().path(strFolder, strSource, false );
      //#else
      // strTemplate = System.dir().path(strFolder, "app\\stage\\core\\fontopus\\app\\main\\matter\\dynamic_source_cl.bat", false);
      //#endif
      string str;
      str = Application.file().as_string(strTemplate);
      /*string strVars = getenv("VS100COMNTOOLS");
      System.file().path().eat_end_level(strVars, 2, "\\");
      strVars += "vc\\bin\\vcvars32.bat";*/
      str.replace("%VS_VARS%", m_strEnv);
      string strPlat2;
#ifdef _M_X64
      strPlat2 = "x86_amd64";
#else
      strPlat2 = " /x86";
#endif
      str.replace("%VS_VARS_PLAT2%", strPlat2);

      string strV(strFolder);
      strV.replace("\\", "/");
      str.replace("%CA2_ROOT%", strV);
      str.replace("%NETNODE_ROOT%", strN);
      str.replace("%SDK1%", m_strSdk1);
      string strDest = "stage\\front\\";
      strDest += lpcszDest;
      string strCmd;
      //#ifdef DEBUG
      strCmd = System.dir().path(strFolder, strDest, false);
      //#else
      // strCmd = System.dir().path(strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_cl.bat", false);
      //#endif
      Application.dir().mk(System.dir().name(strCmd));
      //Application.file().put_contents_utf8(strCmd, str);
      Application.file().put_contents(strCmd, str);
      Application.dir().mk(System.dir().path(m_strTime, "dynamic_source\\", false));
   }


   void script_compiler::handle_file_action(::file_watcher::id watchid, const char * pszFolder, const char * psz, ::file_watcher::e_action eaction)
   {
      UNREFERENCED_PARAMETER(eaction);
      string str = System.dir().path(pszFolder, psz, false);
      string strTransfer = str;

      // does not transfer
      if(::str::find_ci("netnode_persistent_ui_str", strTransfer) >= 0)
         return;

      if(m_straSync.get_count() > 1)
      {
         for(int32_t i = 1; i < m_straSync.get_count(); i++)
         {

            property_set set(get_app());

            Application.http().get("http://" + m_straSync[i] + "/sync?src=" +m_straSync[0] + "&url=" + System.url().url_encode(strTransfer) + "&pwd=sym123&authnone=1", set);

         }

      }

      int32_t i = 0;

      while(i < str.get_length() && str[i] != '\\' && str[i] != '/')
      {

         i++;

      }

      if(::str::begins(str, System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "library\\include", false)))
      {
         compile_library();
         m_pmanager->m_pcache->set_all_out_of_date();
      }
      else if(::str::begins(str, System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "library\\source", false)))
      {
         compile_library();
      }
      else if(defer_run_persistent(str))
      {
      }

   }

   void script_compiler::folder_watch()
   {

      m_filewatchid           = add_file_watch(m_pmanager->m_strNetseedDsCa2Path, true);
      m_filewatchidFribox     = add_file_watch("Z:\\fribox\\ds\\", true);

   }

   void script_compiler::compile_library()
   {
      single_lock slLibrary(&m_mutexLibrary, TRUE);

      unload_library();
      string strName = "library";

      m_strLibsLibs = System.dir().element("time/library/" + m_strPlatform + "/library/library.lib");

      m_memfileLibError.set_length(0);
      string strFolder;
      strFolder = System.dir().element();
      m_straLibSourcePath.remove_all();
      m_straLibSourceRelPath.remove_all();
      Application.dir().rls(System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "library\\source", false),  &m_straLibSourcePath, NULL, &m_straLibSourceRelPath);
      for(int32_t i = 0; i < m_straLibSourcePath.get_size(); )
      {
         if(System.file().extension(m_straLibSourcePath[i]) != "ds")
         {
            m_straLibSourcePath.remove_at(i);
            m_straLibSourceRelPath.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      m_straLibCppPath.remove_all();
      for(int32_t i = 0; i < m_straLibSourcePath.get_size(); i++ )
      {
         string str = m_straLibSourceRelPath[i];
         ::str::ends_eat_ci(str, ".ds");
         str.replace(":", "");
         m_straLibCppPath.add(System.dir().path(System.dir().path(m_strTime, "dynamic_source\\library\\source", false), str + ".cpp"));
      }
      m_straLibIncludePath.remove_all();
      m_straLibIncludeRelPath.remove_all();
      Application.dir().rls(System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "library\\include", false),  &m_straLibIncludePath, NULL, &m_straLibIncludeRelPath);
      for(int32_t i = 0; i < m_straLibIncludePath.get_size(); )
      {
         if(System.file().extension(m_straLibIncludePath[i]) != "ds"
            || ::str::find_ci(m_straLibIncludePath[i], "\\.svn\\") >= 0
            || Application.dir().is(m_straLibIncludePath[i]))
         {
            m_straLibIncludePath.remove_at(i);
            m_straLibIncludeRelPath.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      m_straLibHppPath.remove_all();
      for(int32_t i = 0; i < m_straLibIncludePath.get_size(); i++ )
      {
         string str = m_straLibIncludeRelPath[i];
         ::str::ends_eat_ci(str, ".ds");
         str.replace(":", "");
         m_straLibHppPath.add(System.dir().path(System.dir().path(m_strTime, "dynamic_source\\library\\include", false), str + ".h"));
      }

      string strLib(System.file().name_(strName));


      //#ifdef DEBUG
#ifdef LINUX
      m_strLibraryPath = "/core/stage/x86/libnetnodelibrary.so";
#else
      m_strLibraryPath.Format(System.dir().stage(m_strPlatform + "\\dynamic_source\\library\\%s.dll"), System.dir().path(System.dir().name(strName), strLib, false));
#endif
      //#else
      // plib->m_strLibraryPath.Format(System.dir().path(strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\Release\\%s.dll", false), strName);
      //#endif

      Application.dir().mk(System.dir().name(m_strLibraryPath));
      Application.dir().mk(System.dir().path(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_library\\library", false), System.dir().name(strName), false));

      for(int32_t i = 0; i < m_straLibIncludePath.get_size(); i++)
      {
         cppize(m_straLibIncludePath[i], m_straLibHppPath[i], cpptype_include);
      }


      string strN = m_pmanager->m_strNetnodePath;

      for(int32_t i = 0; i < m_straLibSourcePath.get_size(); i++)
      {
         cppize(m_straLibSourcePath[i], m_straLibCppPath[i], cpptype_source);
         string strRel = m_straLibSourceRelPath[i];
         ::str::ends_eat_ci(strRel, ".ds");
         strRel.replace("\\", "/");
         string str1;
         str1 = "library/source/" + strRel;
         string strCmd;
         //#ifdef DEBUG
#ifdef LINUX
         strCmd = System.dir().element("stage\\front\\" + m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
#else
         strCmd = System.dir().element("stage\\front\\" + m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bat");
#endif
         //#else
         //    strCmd.Format(System.dir().path(strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_cl.bat", false));
         //#endif
         string str = Application.file().as_string(strCmd);
         str.replace("%ITEM_NAME%", str1);
         str.replace("%ITEM_DIR%", System.dir().name(str1));
         str.replace("%PLATFORM%", m_strPlatform);
         str.replace("%NETNODE_ROOT%", strN);
         str.replace("%LIBPLATFORM%", m_strLibPlatform);
         str.replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
         str.replace("%SDK1%", m_strSdk1);
         Application.dir().mk(System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_library\\" + System.dir().name(str1)));
         Application.dir().mk(System.dir().path(m_strTime, "library\\" + m_strPlatform + "\\" + System.dir().name(str1), false));
#ifdef LINUX
         strCmd = System.dir().element("stage\\front\\libc1.bash");
#else
         strCmd = System.dir().element("stage\\front\\libc1.bat");
         string vars1batSrc;
         string vars2batSrc;
         string vars1batDst;
         string vars2batDst;
         vars1batSrc = System.dir().element("nodeapp/stage/dynamic_source/vc_vars.bat");
         vars2batSrc = System.dir().element("nodeapp/stage/dynamic_source/vc_vars_query_registry.bat");
         vars1batDst = System.dir().stage("stage\\front", "vc_vars.bat");
         vars2batDst = System.dir().stage("stage\\front", "vc_vars_query_registry.bat");
         try
         {
            Application.file().copy(vars1batDst, vars1batSrc, false);
         }
         catch(...)
         {
         }
         try
         {
            Application.file().copy(vars2batDst, vars2batSrc, false);
         }
         catch(...)
         {
         }
#endif

         //Application.file().put_contents_utf8(strCmd, str);
         Application.file().put_contents(strCmd, str);

#ifndef METROWIN
         ::core::process process;

         process.create_child_process(strCmd, false, System.dir().element("stage\\front"), ::core::scheduling_priority_highest);


         uint32_t dwExitCode;
         while(true)
         {
            if(process.has_exited(&dwExitCode))
               break;
            Sleep(84);
         }
#else

         throw todo(get_app());


#endif
         m_memfileLibError << "<html><head></head><body><pre>";
         str.Format(System.dir().path(m_strTime, "dynamic_source\\library\\%s-compile-log.txt"), str1);
         str = Application.file().as_string(str);
         str.replace("\r\n", "</pre><pre>");
         m_memfileLibError << str;
         //system(strCmd);
      }

      string strObjs;
      for(int32_t i = 0; i < m_straLibSourcePath.get_size(); i++)
      {
         strObjs += " ";
         string strRel = m_straLibSourceRelPath[i];
         ::str::ends_eat_ci(strRel, ".ds");
         strObjs += System.dir().path(
            System.dir().path(m_strTime, "intermediate\\" + m_strPlatform + "\\" + m_strDynamicSourceConfiguration + "\\" + m_pmanager->m_strNamespace + "_dynamic_source_library\\library\\source", false),
#ifdef LINUX
            strRel + ".o", false);
#else
            strRel + ".obj", false);
#endif
         strObjs += " ";
      }
      string strCmd;
      //#ifdef DEBUG
      strCmd.Format(System.dir().stage("front\\" + m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 +
#ifdef LINUX
         ".bash"));
#else
         ".bat"));
#endif
      //#else
      // strCmd.Format(System.dir().path(strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_libl.bat", false));
      //#endif
      string str = Application.file().as_string(strCmd);
      str.replace("%ITEM_NAME%", "library" PATH_SEPARATOR + strName);
      str.replace("%ITEM_DIR%", "library");
      str.replace("%OBJS%", strObjs);
      str.replace("%PLATFORM%", m_strPlatform);
      str.replace("%NETNODE_ROOT%", strN);
      str.replace("%LIBPLATFORM%", m_strLibPlatform);
      str.replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
      str.replace("%SDK1%", m_strSdk1);
      string strTargetName = m_strLibraryPath;
      ::str::ends_eat_ci(strTargetName, ".dll");
      str.replace("%TARGET_NAME%", strTargetName);
      Application.dir().mk(System.dir().element("stage\\" + m_strPlatform + "\\library"));
#ifdef LINUX
      Sleep(1984);
      strCmd = System.dir().element("stage\\front\\libl1.bash");
#else
      strCmd = System.dir().element("stage\\front\\libl1.bat");
#endif
      //Application.file().put_contents_utf8(strCmd, str);
      Application.file().put_contents(strCmd, str);

#ifndef METROWIN

      ::core::process process;


      process.create_child_process(strCmd, false, System.dir().name(strCmd), ::core::scheduling_priority_highest);

      uint32_t dwExitCode;
      while(true)
      {
         if(process.has_exited(&dwExitCode))
            break;
         Sleep(84);
      }

#endif


      str.Format(System.dir().path(m_strTime, "dynamic_source\\library\\%s-link-log.txt"), strName);
      //str.Format("V:\\time\\core\\fontopus\\net\\dynamic_source\\%s-build-log.txt", lpcszName);
      str = Application.file().as_string(str);
      str.replace("\r\n", "</pre><pre>");
      m_memfileLibError << str;
      m_memfileLibError << "</pre></body></html>";
      load_library();
   }



   void script_compiler::cppize(const char * lpcszSource, const char * lpcszDest, ecpptype e_type)
   {
      Application.dir().mk(System.dir().name(lpcszDest));
      cppize1(lpcszSource, lpcszDest, e_type);
   }

   void script_compiler::cppize1(const char * lpcszSource, const char * lpcszDest, ecpptype e_type)
   {

      string strSource = Application.file().as_string(lpcszSource);

      bool bCode = false;

      string strDest;
      strDest = "";
      strDest = "";
      if(e_type == cpptype_source || e_type == cpptype_ds)
      {
         strDest += "#include \"framework.h\"\r\n";
         strDest += "#include \"11ca2_fontopus.h\"\r\n";
         for(int32_t i = 0; i < m_straLibIncludePath.get_count(); i++)
         {
            string str;
            str = m_straLibIncludeRelPath[i];
            ::str::ends_eat_ci(str, ".ds");
            strDest += "#include \""+str+".h\"\r\n";
         }
      }

      strDest += "\r\n";
      strDest += "\r\n";
      strsize iPosId = strDest.get_length();
      strDest += "\r\n";
      strDest += "\r\n";

      strsize iStart = 0;
      strsize iPos = 0;
      strsize iLastEnd = 0;
      stringa straId;
      while((iPos = strSource.find("<?", iStart)) >= 0)
      {
         if(iPos > iLastEnd && bCode)
         {
            strDest += get_ds_print(strSource.Mid(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd < 0)
            break;
         iLastEnd += 2;
         int32_t iShift = 0;
         if(strSource.Mid(iPos, 5).CompareNoCase("<?php") == 0)
            iShift = 3;
         bCode = true;
         strDest += cppize2(strSource.Mid(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), false, straId);
         iStart = iLastEnd;
      }
      /*   strDest += "   print(\"" ;
      strDest += escape(strSource.Mid(iStart));
      strDest += "\");\r\n";
      strDest += "//End parsed user script\r\n";
      strDest += "}\r\n";*/

      string strId;
      for(int32_t i = 0; i < straId.get_size(); i++)
      {
         strId += "static class id lscript_id" + ::str::from(i) + "(\"" + straId[i] + "\");\r\n";
      }

      strDest = strDest.Left(iPosId) + strId + strDest.Mid(iPosId);

      //Application.file().put_contents_utf8(lpcszDest, strDest);
      Application.file().put_contents(lpcszDest, strDest);


   }


   void add_var_id(string & strResult, strsize & iArroba, stringa & straId, bool bMakeKeyLower)
   {
      string strKey = strResult.Mid(iArroba);
      if(bMakeKeyLower)
      {
         strKey.make_lower();
      }
      strsize iFind = straId.find_first(strKey);
      if(iFind <= 0)
      {
         straId.add(strKey);
         iFind = straId.get_upper_bound();
      }
      strResult = strResult.Left(iArroba) + " lscript_id" + ::str::from(iFind);
      iArroba = -1;
   }

   string script_compiler::cppize2(const char * psz, bool bScript, stringa & straId)
   {
      string str(psz);
      str.trim();
      bool bInSimpleQuote = false;
      bool bInDoubleQuote = false;
      strsize iSimpleQuote = 0;
      strsize iArroba = -1;
      bool bInVar = false;
      bool bInSlash = false;
      bool bInRet = false;
      bool bInSpec1 = false;
      bool bInSpec1Close = false;
      bool bInSpec2 = false;
      bool bInSpec2Close = false;
      bool bServer = false;
      strsize iServer = -1;
      strsize iBracket = 0;
      bool bInBrace = false;
      strsize iVar = -1;
      strsize iIdLen = 0;
      char ch;
      char chNext;
      string strResult;
      strsize iLen = str.get_length();
      strsize i = 0;
      bool bInitial = true;
      string strSpec1;
      strsize iOpenParen = 1; // open Parenthesis Count
      stringa straFunction;
      index_array iaFunctionParen; // index of the parenthesis of the function
      bool bInserted = false;
      bool bNewLine = true;
      bool bLow = false;
      while(i < iLen)
      {
         bInserted = false;
         ch = str[i];
         chNext = str[i + 1];
         if(::str::begins(str.Mid(i), "bk_filter_active1"))
         {
            //__debug_break();
         }
         if(bInSpec1)
         {
            if(ch == '\r' || ch == '\n')
            {
               bNewLine = true;
               i++;
            }
            else if(isspace(ch))
            {
               i++;
               continue;
            }
            else if(ch == '(')
            {
               strResult += strSpec1 + "(";
               bInSpec1 = false;
               i++;
               bNewLine = false;
               continue;
            }
            else
            {
               strResult += strSpec1 + "(";
               bInSpec1Close = true;
               bInSpec1 = false;
            }
         }
         if(bInSpec2)
         {
            if(ch == '\r' || ch == '\n')
            {
               bNewLine = true;
               i++;
            }
            else if(isspace(ch))
            {
               i++;
               continue;
            }
            else if(ch == '=')
            {
               strResult += ".propset().add(id(), ";
               bInSpec2 = false;
               bInSpec2Close = true;
               i++;
               bNewLine = false;
               continue;
            }
            else
            {
               ///erro
            }
         }
         if(bServer)
         {
            if(isalpha(ch) || isdigit(ch) || ch == '.' || ch == ',' || ch == '-' || ch == '_')
            {
               if(iServer < 0)
               {
                  iServer = strResult.get_length();
               }
            }
            else if(iServer >= 0)
            {
               bool bWaitQuote = true;
               bool bWaitCloseBracket = false;
               bServer = false;
               add_var_id(strResult, iServer, straId);
               strResult += "]";
               while(i < iLen)
               {
                  ch = str[i];
                  if(isspace(ch))
                     i++;
                  else if(bWaitQuote && (ch == '\'' || ch=='\"'))
                  {
                     bWaitQuote = false;
                     bWaitCloseBracket = true;
                     i++;
                  }
                  else if(bWaitCloseBracket && ch == ']')
                  {
                     i++;
                     break;
                  }
                  else
                  {
                     strResult += ":*<invalid-syntax>*:"; // fatal;
                     break;
                     break;
                     //throw simple_exception(get_app(), "invalid syntax.");
                  }
               }
               continue;
            }
            else
            {
               i++;
               continue;
            }
         }
         if(iBracket > 0 && ch == ']')
         {
            strResult += ch;
            iBracket--;
         }
         else if(bInSimpleQuote)
         {
            if(bInSlash)
            {
               bInSlash = false;
               strResult += ch;
            }
            else
            {
               if(ch == '\\')
               {
                  bInSlash = true;
                  if(chNext != '{'
                     && chNext != '}'
                     && chNext != '$')
                  {
                     strResult += ch;
                  }
               }
               else if(ch == '\'')
               {
                  bInSimpleQuote = false;
                  //strResult += "\")";
                  strResult += "\"";
               }
               else
               {
                  bInSlash = false;
                  strResult += ch;
               }
            }
         }
         else if(iArroba >= 0)
         {
            if(bInSlash)
            {
               bInSlash = false;
               strResult += ch;
            }
            else
            {
               if(ch == '\\')
               {
                  bInSlash = true;
                  if(chNext != '{'
                     && chNext != '}'
                     && chNext != '$')
                  {
                     strResult += ch;
                  }
               }
               else if(ch == '@')
               {
                  add_var_id(strResult, iArroba, straId);
               }
               else
               {
                  bInSlash = false;
                  strResult += ch;
               }
            }
         }
         else if(bInVar)
         {
            if(isdigit(ch) || isalpha(ch) || ch == '_')
            {
               if(bLow)
               {
                  strResult += (char) tolower(ch);
               }
               else
               {
                  strResult += ch;
               }
            }
            else
            {
               bInVar = false;
               bLow = false;
               if(bInDoubleQuote)
               {
                  if(ch == '$')
                  {
                     bInVar = true;
                     add_var_id(strResult, iVar, straId);
                     strResult += ") + gstr(";
                     iVar = strResult.length();
                     bLow = true;
                     i++;
                     continue;
                  }
                  else
                  {
                     //strResult += "\") + unitext(\"";
                     add_var_id(strResult, iVar, straId);
                     strResult += ") + \"";
                     if(ch == '\"')
                     {
                        bInDoubleQuote = false;
                        //strResult += "\")";
                        strResult += "\"";
                        i++;
                        continue;
                     }
                     else if(ch == '\\')
                     {
                        bInSlash = true;
                     }
                  }
               }
               else
               {
                  while(isspace(str[i]) && i < iLen)
                  {
                     i++;
                  }
                  ch = str[i];
                  if(ch == '[' && chNext != ']')
                  {
                     iBracket++;
                     add_var_id(strResult, iVar, straId);
                     strResult += ").propset()";
                  }
                  else if(ch == '-' && chNext == '>')
                  {
                     i+=2;
                     while(isspace(str[i]) && i < iLen)
                     {
                        i++;
                     }
                     ch = str[i];
                     string strToken;
                     if(isalpha(ch) || ch == '_')
                     {
                        strToken += ch;
                        i++;
                     }
                     else
                     {
                        strResult = "-> error";
                        return strResult;
                     }
                     ch = str[i];
                     while(isdigit(ch) || isalpha(ch) || ch == '_')
                     {
                        strToken += ch;
                        i++;
                        ch = str[i];
                     }
                     ch = str[i];
                     while(isspace(ch))
                     {
                        i++;
                        ch = str[i];
                     }
                     if(ch == '(')
                     {
                        i++;
                        ch = str[i];
                        iaFunctionParen.add(iOpenParen);
                        iOpenParen++;
                        straFunction.add(strToken);
                        while(isspace(ch))
                        {
                           i++;
                           ch = str[i];
                        }
                        if(ch == ')')
                        {
                           add_var_id(strResult, iVar, straId);
                           strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->call(\""+ strToken + "\" ";
                        }
                        else
                        {
                           add_var_id(strResult, iVar, straId);
                           strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->call(\""+ strToken + "\", ";
                           continue;
                        }
                     }
                     else
                     {
                        add_var_id(strResult, iVar, straId);
                        strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->m_propertyset[\""+ strToken + "\"]";
                     }
                  }
                  else
                  {
                     add_var_id(strResult, iVar, straId);
                     strResult += ")";
                  }
               }
               if(ch == ';')
                  goto ch_comma;
               else
                  goto ch_else;
               //strResult += ch;
            }
         }
         else if(bInDoubleQuote)
         {
            if(bInSlash)
            {
               bInSlash = false;
               strResult += ch;
            }
            else
            {
               if(ch == '$' && (isalpha(chNext) || chNext == '_'))
               {
                  bInVar = true;
                  //strResult += "\") + glowstr(\"";
                  strResult += "\" + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else if(ch == '{')
               {
                  bInBrace = true;
                  bInDoubleQuote = false;
                  //strResult += "\") + ";
                  strResult += "\" + ";
               }
               else if(ch == '\\')
               {
                  bInSlash = true;
                  if(chNext != '{'
                     && chNext != '}'
                     && chNext != '$')
                  {
                     strResult += ch;
                  }
               }
               else if(ch == '\"')
               {
                  bInDoubleQuote = false;
                  //strResult += "\")";
                  strResult += "\"";
               }
               else
               {
                  bInSlash = false;
                  strResult += ch;
               }
            }
         }
         else if(ch == '\"')
         {
            bInDoubleQuote = true;
            //strResult += "unitext(\"";
            strResult += "\"";
         }
         else if(ch == '\'')
         {
            bInSimpleQuote = true;
            //strResult += "unitext(\""; // overloads should cope with the possibility of conversion between string to character
            strResult += "\""; // overloads should cope with the possibility of conversion between string to character
            iSimpleQuote = strResult.get_length();
         }
         else if(ch == '@')
         {
            iArroba = strResult.get_length();
         }
         else if(ch == '_' && chNext == '_' && is_id(&str[i], str.get_length() - i,  "__ch", 4, iIdLen))
         {
            strResult += "'";
            bInVar = false;
            i += iIdLen;
            while(str[i] != '(' && i < iLen)
               i++;
            i++;
            while(str[i] != ')' && i < iLen)
            {
               strResult += str[i];
               i++;
            }
            strResult += "'";

         }
         else if(ch == '$' && (isalpha(chNext) || chNext == '_'))
         {
            if(bInVar)
            {
               if(bInDoubleQuote)
               {
                  add_var_id(strResult, iVar, straId);
                  strResult += ") + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else
               {
                  add_var_id(strResult, iVar, straId);
                  strResult += ")"; // probably will generate compile error, leave to ca++ compiler
               }
            }
            else
            {
               bInVar = true;
               if(bInDoubleQuote)
               {
                  //strResult += "\") + glowstr(\"";
                  strResult += "\" + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else
               {
                  if(is_id(&str[i + 1], str.get_length() - i - 1, "_GET", 4,  iIdLen))
                  {
                     strResult += "geta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_POST", 5,  iIdLen))
                  {
                     strResult += "posta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_REQUEST", 8, iIdLen))
                  {
                     strResult += "requesta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_SERVER", 7, iIdLen))
                  {
                     strResult += "inattra()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_COOKIE", 7, iIdLen))
                  {
                     strResult += "cookies()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else
                  {
                     strResult += "gprop(";
                     iVar = strResult.length();
                     bLow = true;
                  }
               }
            }
         }
         else if(ch == ';')
         {
ch_comma:
            if(bInRet)
            {
               bInRet = false;
               strResult += ch;
               strResult += "\r\nreturn;\r\n}\r\n";
            }
            else if(bInSpec1Close)
            {
               bInSpec1Close = false;
               strResult += ")";
               strResult += ch;
            }
            else if(bInSpec2Close)
            {
               bInSpec2Close = false;
               strResult += ")";
               strResult += ch;
            }
            else
            {
               strResult += ch;
            }
            bInitial = true;
         }
         else if(ch == '(')
         {
            strResult += ch;
            iOpenParen++;
         }
         else if(ch == ')')
         {
            iOpenParen--;
            //if(iaFunctionParen.pop_match('');
            strResult += ch;
         }
         else if(ch == '#')
         {
            if(bNewLine)
            {
               strResult += ch;
               i++;
               while(i < iLen)
               {
                  ch = str[i];
                  strResult += ch;
                  if(ch == '\r' || ch == '\n')
                     break;
                  i++;

               }

            }
         }
         else
         {
ch_else:
            if(bScript && is_id(&str[i], str.get_length() - i,  "return", 6,  iIdLen) && next_nonspace(str.Mid(i + iIdLen))[0] != ';')
            {
               bInRet = true;
               strResult += "\r\n{\r\nm_varRet = ";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.get_length() - i,  "include", 7, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "include";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.get_length() - i,   "print", 5,  iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "print";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.get_length() - i,  "echo", 4, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "echo";
               i += iIdLen - 1;
            }
            else if(str.Mid(i, 2) == "[]")
            {
               bInSpec2 = true;
               i += 2 - 1;
            }
            else if(bInBrace && ch == '}')
            {
               bInDoubleQuote = true;
               bInBrace = false;
               //strResult += " + unitext(\"";
               strResult += " + \"";
            }
            else
            {
               if(ch == '\r' || ch == '\n')
               {
                  bNewLine = true;

               }
               else if(isspace((int) (unsigned char) ch))
               {
               }
               else
               {
                  bNewLine = false;
               }
               if(bLow)
               {
                  strResult += (char) tolower(ch);
               }
               else
               {
                  strResult += ch;
               }
            }
         }
         i++;
      }
      return strResult;

   }


   bool script_compiler::is_id(const char * psz, strsize iLen, const char * pszId, strsize iIdLen, strsize & iIdLenRet)
   {
      if(iLen < iIdLen)
         return false;
      if(iIdLen == iLen)
      {
         if(!strcmp(psz, pszId))
         {
            iIdLenRet = iIdLen;
            return true;
         }
      }
      if(::str::begins(psz, pszId)
         && !isdigit(psz[iIdLen]) && !isalpha(psz[iIdLen]) && psz[iIdLen] != '_')
      {
         iIdLenRet = iIdLen;
         return true;
      }
      return false;
   }

   const char * script_compiler::next_nonspace(const char * psz)
   {
      while(*psz != '\0' && isspace(*psz))
      {
         psz++;
      }
      return psz;
   }

   void script_compiler::run_persistent()
   {
      string strPath = System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "core\\persistent", false);
      stringa stra;
      Application.dir().rls(strPath, &stra);

      string strCat;
      strCat = System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "core\\netnode_persistent_ui_str.ds", false);
      string strBody;
      strBody = "<?\r\n";
      strBody += "// ATTENTION!\r\n";
      strBody += "// Do not edit this file\r\n";
      strBody += "// This file is automatically generated as the\r\n";
      strBody += "// concatenation of all .ds files in thisr\r\n";
      strBody += "// folder and subfolders!\r\n";
      strBody += "\r\n";
      strBody += "?>\r\n\r\n\r\n";
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string str = stra[i];
         if(::str::begins_ci(str, System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "core\\persistent", false))
            && ::str::ends_ci(str, ".ds"))
         {
            strBody += Application.file().as_string(str);
         }
      }
      //Application.file().put_contents_utf8(strCat, strBody);
      Application.file().put_contents(strCat, strBody);
      string strInclude = strCat;
      //   defer_run_persistent(str);
      ::str::begins_eat_ci(strInclude, m_pmanager->m_strNetseedDsCa2Path);
      ::str::ends_eat_ci(strInclude, ".ds");
      script_instance * pinstance = m_pmanager->get(strInclude);
      if(pinstance != NULL)
      {
         string strError;
         pinstance->initialize(pinstance, NULL, NULL, m_pmanager);
         ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript.m_p);
         if(pdsscript != NULL)
         {
            try
            {
               pdsscript->m_memfileError.seek_to_begin();
               m_pmanager->m_strPersistentError += pdsscript->m_memfileError.to_string();;
            }
            catch(...)
            {
            }
         }
         try
         {
            pinstance->run();
            pinstance->destroy();
         }
         catch(...)
         {
         }
      }
   }


   bool script_compiler::defer_run_persistent(const char *psz)
   {
      string str(psz);

      if(::str::find_ci("pstr_set", psz) && ::str::ends_ci(psz, ".txt"))
      {
         string strCat;
         strCat = System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "core\\netnode_persistent_ui_str.ds", false);
         string strInclude = strCat;
         ::str::begins_eat_ci(strInclude, m_pmanager->m_strNetseedDsCa2Path);
         ::str::ends_eat_ci(strInclude, ".ds");
         script_instance * pinstance = m_pmanager->get(strInclude);
         if(pinstance != NULL)
         {
            string strError;
            pinstance->initialize(pinstance, NULL, NULL, m_pmanager);
            ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript.m_p);
            if(pdsscript != NULL)
            {
               try
               {
                  pdsscript->m_memfileError.seek_to_begin();
                  m_pmanager->m_strPersistentError += pdsscript->m_memfileError.to_string();
               }
               catch(...)
               {
               }
            }
            pinstance->run();
            pinstance->destroy();
         }
      }
      else if(::str::begins_eat_ci(str, System.dir().path(m_pmanager->m_strNetseedDsCa2Path, "core\\persistent", false))
         && ::str::ends_eat_ci(str, ".ds")
         && str.CompareNoCase("netnode_persistent_ui_str") != 0)
      {
         run_persistent();
         return true;
      }
      return false;
   }


   bool script_compiler::library_DoesMatchVersion()
   {

      if(get_tick_count() - m_dwLastLibraryVersionCheck < (1984 + 1977))
      {
         return m_bLastLibraryVersionCheck;
      }

      single_lock slLibrary(&m_mutexLibrary, TRUE);

      for(int32_t i = 0; i < m_straLibSourcePath.get_size(); i++)
      {

         //FILETIME ftCreation;
         //FILETIME ftAccess;
         //FILETIME ftModified;
         //memset(&ftCreation, 0, sizeof(FILETIME));
         //memset(&ftAccess, 0, sizeof(FILETIME));
         //memset(&ftModified, 0, sizeof(FILETIME));
         //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
         //GetFileTime(h, &ftCreation, &ftAccess, &ftModified);
         //::CloseHandle(h);

         struct stat st;

         stat(m_straLibSourcePath[i], &st);

         if(memcmp(&st.st_ctime, &m_ftaLibCreation[i], sizeof(__time_t)) != 0
            || memcmp(&m_ftaLibModified[i], &st.st_mtime, sizeof(__time_t)) != 0)
         {
            m_bLastLibraryVersionCheck = false;
            m_dwLastLibraryVersionCheck = get_tick_count();
            return false;

         }

      }

      m_bLastLibraryVersionCheck    = true;
      m_dwLastLibraryVersionCheck   = get_tick_count();

      return true;

   }
   void script_compiler::load_library()
   {

      single_lock slLibrary(&m_mutexLibrary, TRUE);

      if(!m_libraryLib.open(m_strLibraryPath))
         return;

      m_ftaLibCreation.allocate(m_straLibSourcePath.get_size());
      m_ftaLibAccess.allocate(m_straLibSourcePath.get_size());
      m_ftaLibModified.allocate(m_straLibSourcePath.get_size());

      for(int32_t i = 0; i < m_straLibSourcePath.get_size(); i++)
      {

         struct stat st;

         stat(m_straLibSourcePath[i], &st);

         m_ftaLibCreation[i]  = st.st_ctime;
         m_ftaLibAccess[i]    = st.st_atime;
         m_ftaLibModified[i]  = st.st_mtime;

         //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
         //memset(&m_ftaLibCreation[i], 0, sizeof(FILETIME));
         //memset(&m_ftaLibAccess[i], 0, sizeof(FILETIME));
         //memset(&m_ftaLibModified[i], 0, sizeof(FILETIME));
         //GetFileTime(h , &m_ftaLibCreation[i], &m_ftaLibAccess[i], &m_ftaLibModified[i]);
         //::CloseHandle(h);

      }

   }


   void script_compiler::unload_library()
   {
      single_lock slLibrary(&m_mutexLibrary, TRUE);
      m_libraryLib.close();
   }

   string script_compiler::get_ds_print(const char *psz)
   {
      string strSource(psz);
      string strDest;
      while(strSource.get_length() > 0)
      {
         strsize iLen = min(4 * 1024, strSource.get_length());
         if(strSource.get_length() > iLen)
         {
            if(strSource[iLen] == '\n')
               iLen++;
         }
         string str = strSource.Left(iLen);
         //strDest += "   ds_print(unitext(\"";
         strDest += "\r\n   ds_print(\"";
         strDest += escape(str);
         //strDest += "\"));\r\n";
         strDest += "\");\r\n";
         strSource = strSource.Mid(iLen);
      }
      return strDest;
   }


} // namespace dynamic_source


