#include "framework.h"


#include <sys/stat.h>


#if defined(LINUX)
#include <ctype.h>
#endif





namespace introjection
{


library::library(::aura::application * papp):
   object(papp),
   m_library(papp),
   m_memfileError(papp)
{

   ZERO(m_filetime);

}


library::~library()
{


}


compiler::compiler(::aura::application * papp):
   ::object(papp),
    //      m_memfileLibError(papp),
    //    m_mutexLibrary(papp),
    m_mutex(papp)//,
    //      m_libraryLib(papp)


{


#if MEMDLEAK

   m_strDynamicSourceConfiguration = "memdleak";
   m_strDynamicSourceStage = "stage";


#elif defined(DEBUG)

   m_strDynamicSourceConfiguration = "basis";
   m_strDynamicSourceStage = "time";

#else

   m_strDynamicSourceConfiguration = "profiler";
   m_strDynamicSourceStage = "profiler";

#endif
   m_strDynamicSourceStageFolder = System.dir().element() / m_strDynamicSourceStage;


   initialize();

}

compiler::~compiler()
{
}

void compiler::initialize()
{
   prepare_compile_and_link_environment();
   //   folder_watch();
   //      compile_library();
   // run_persistent();
   // parse_pstr_set();
}

void compiler::prepare_compile_and_link_environment()
{

   Application.dir().mk("C:\\ca2\\introjection\\symbols");
   //string strVars = getenv("VS100COMNTOOLS");
   ::file::path strVars;

#ifndef METROWIN

   strVars = getenv("VS140COMNTOOLS");

#endif

   m_strEnv = strVars.up(2);
   m_strEnv = m_strEnv / "vc\\vcvarsall.bat";
   //m_strEnv = ".\\vc_vars.bat";

   m_strTime = System.dir().element() / "time";

   //m_strEnv = "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Bin\\SetEnv.cmd";

   //m_strSdk1 = "windows7.1sdk";
   m_strSdk1 = "vc140";
#ifdef OS64BIT
#ifdef LINUX
   m_strPlat1     = "64";
   m_strPlatform = "x86";
   m_strStagePlatform = "x86";
   m_strLibPlatform = "x86/";
#else
   m_strPlat1     = "64";
   //m_strPlat2 = "  x86_amd64";
   m_strPlat2 = "amd64";
   m_strPlatform = "x64";
   m_strStagePlatform = "x64";
   m_strLibPlatform = "x64/";
#endif
#else
   m_strPlat1     = "32";
   m_strPlat2 = " x86";
   m_strPlatform = "Win32";
   m_strStagePlatform = "x86";
   m_strLibPlatform = "x86/";
#endif

   //System.file().lines(m_straSync, "C:\\core\\database\\text\\introjection\\syncer.txt", get_app());
#if defined(LINUX)
   prepare1(m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash",
            m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
   prepare1(m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash",
            m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
   prepare1(m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash",
            m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");
#else
   prepare1(m_strPlat1,m_strPlat1);
   //prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat",
   //   m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat");
   //prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat",
   //   m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat");
   //prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat",
   //   m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat");
#endif
   System.dir().mk(System.dir().element() / m_strDynamicSourceStage / "front",get_app());

   //#ifdef WINDOWS
   //      string vars1batSrc;
   //      string vars2batSrc;
   //      string vars1batDst;
   //      string vars2batDst;
   //      vars1batSrc = System.dir().element()/"nodeapp/stage/introjection/vc_vars.bat";
   //      vars2batSrc = System.dir().element()/"nodeapp/stage/introjection/vc_vars_query_registry.bat";
   //      vars1batDst = System.dir().element()/ m_strDynamicSourceStage / "front"/"vc_vars.bat";
   //      vars2batDst = System.dir().element()/m_strDynamicSourceStage /"front"/"vc_vars_query_registry.bat";
   //      try
   //      {
   //         Application.file().copy(vars1batDst, vars1batSrc, false);
   //      }
   //      catch(...)
   //      {
   //      }
   //      try
   //      {
   //         Application.file().copy(vars2batDst, vars2batSrc, false);
   //      }
   //      catch(...)
   //      {
   //      }
   //
   //#endif


#ifdef METROWIN

   throw todo(get_app());

#elif defined(LINUX)
#else
   var var = System.process().get_output("\"" + m_strEnv + "\" " + m_strPlat2);
   TRACE0(var.get_string());

#endif

   string str;
   string strItem;

   strItem = System.dir().element() / m_strDynamicSourceStage / m_strStagePlatform;
   str = str + strItem + ";";

   strItem = System.dir().element() / m_strDynamicSourceStage / m_strStagePlatform / "introjection\\library";
   str = str + strItem + ";";
#ifdef WINDOWSEX
   uint32_t dwSize = GetEnvironmentVariable("PATH",NULL,0);
   LPTSTR lpsz = new char[dwSize + 1];
   dwSize = GetEnvironmentVariable("PATH",lpsz,dwSize + 1);
   str += lpsz;
   delete lpsz;
#elif defined(METROWIN)

   throw todo(get_app());

#else
   str += getenv("PATH");
#endif
   bool bResult;
#ifdef WINDOWSEX
   bResult = SetEnvironmentVariable("PATH",str) != FALSE;
#elif defined(METROWIN)

   throw todo(get_app());

#elif defined(LINUX)
#else
   bResult = setenv("PATH",str,TRUE);
#endif
   TRACE("compiler::prepare_compile_and_link_environment SetEnvironmentVariable return bool %d",bResult);


}



DWORD RunSilent(char* strFunct,char* strstrParams)
{

#ifdef WINDOWSEX

   STARTUPINFO StartupInfo;
   PROCESS_INFORMATION ProcessInfo;
   char Args[4096];
   char *pEnvCMD = NULL;
   char *pDefaultCMD = "CMD.EXE";
   ULONG rc;

   memset(&StartupInfo,0,sizeof(StartupInfo));
   StartupInfo.cb = sizeof(STARTUPINFO);
   StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
   StartupInfo.wShowWindow = SW_HIDE;

   Args[0] = 0;

   pEnvCMD = getenv("COMSPEC");

   if(pEnvCMD)
   {

      strcpy(Args,pEnvCMD);
   }
   else
   {
      strcpy(Args,pDefaultCMD);
   }

   // "/c" option - Do the command then terminate the command window
   strcat(Args," /c ");
   //the application you would like to run from the command window
   strcat(Args,strFunct);
   strcat(Args," ");
   //the parameters passed to the application being run from the command window.
   strcat(Args,strstrParams);

   if(!CreateProcess(NULL,Args,NULL,NULL,FALSE,
                     CREATE_NEW_CONSOLE,
                     NULL,
                     NULL,
                     &StartupInfo,
                     &ProcessInfo))
   {
      return GetLastError();
   }

   WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
   if(!GetExitCodeProcess(ProcessInfo.hProcess,&rc))
      rc = 0;

   CloseHandle(ProcessInfo.hThread);
   CloseHandle(ProcessInfo.hProcess);

   return rc;

#else

    string strCmdLine;

    strCmdLine = strFunct;
    if(strlen_dup(strstrParams) > 0)
    {
        strCmdLine +=  " ";
        strCmdLine += strstrParams;
    }

    int32_t processId;

    if(!create_process(strCmdLine, &processId))
        return -1;


    while(true)
    {

        if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
            break;
        sleep(millis(23));
    }

    return 0;
#endif

}


void compiler::prepare1(const char * lpcszSource,const char * lpcszDest)
{

   //Sleep(15000);

   string strBuildCmd = m_strEnv;

   strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;

   ::process::process_sp process(allocer());


   file_put_contents_dup("C:\\ca2\\env1.bat","C:\\ca2\\env.bat > C:\\ca2\\env.txt");
   file_put_contents_dup("C:\\ca2\\env.bat","@call " + strBuildCmd + "\r\n@set");

   //      set_thread_priority(::multithreading::priority_highest);
   RunSilent("C:\\ca2\\env1.bat","");
   //::system("Y:\\bergedge\\hi5\\program\\hstart.exe /NOCONSOLE \"C:\\ca2\\env1.bat\"");
   string strLog;

//         EnvVarValArray arrEnvVarVal;
//
//         uint32_t dwStart = ::get_tick_count();
//
//         uint32_t dwExitCode;
//
////         string strLog;
//
//         stringa m_strArray;
//         // Open the process for further operations
//         HANDLE hProcess = CProcessEnvReader::OpenProcessToRead(process->m_iPid);
//         if(hProcess)
//         {
//            _ENVSTRING_t stEnvData;
//            // Read the process environment block
//            if(!CProcessEnvReader::ReadEnvironmentBlock(hProcess,stEnvData))
//            {
//               return;
//            }
//
//            // Parse the retrieved data
//            CProcessEnvReader::ParseEnvironmentStrings(stEnvData.pData,
//               stEnvData.nSize / 2,
//               m_strArray);
//
//
//            // Seperate values and variables
//            CProcessEnvReader::SeparateVariablesAndValues(m_strArray,arrEnvVarVal);
//            string_to_string map;
//
//            for(auto pair : arrEnvVarVal)
//            {
//               map[pair.m_element1] = pair.m_element2;
//               SetEnvironmentVariable(pair.m_element1,pair.m_element2);
//            }
//
//            // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
//            CProcessEnvReader::ReleaseHandle(hProcess);
//         }
   //process->write("\n");
   //uint32_t dwExitCode = 0;
   //DWORD dwStart = get_tick_count();
   //while(true)
   //{

   //   strLog += process->read();

   //   if(process->has_exited(&dwExitCode))
   //      break;

   //   Sleep(100);

   //   if(::get_tick_count() - dwStart > 840 * 1000) // 14 minutes
   //   {

   //      //            bTimeout = true;

   //      break;

   //   }

   //}

   //strLog += process->read();
   strLog = file_as_string_dup("C:\\ca2\\env.txt");

   stringa stra;

   stra.add_lines(strLog);

   //Sleep(10000);

#ifdef WINDOWSEX
   EnvVarValArray arrEnvVarVal;
   // Seperate values and variables
   CProcessEnvReader::SeparateVariablesAndValues(stra,arrEnvVarVal);

   string_to_string map;

   for(auto pair : arrEnvVarVal)
   {
      map[pair.m_element1] = pair.m_element2;
      SetEnvironmentVariable(pair.m_element1,pair.m_element2);
   }



   //SetEnvironmentVariable("INCLUDE",map["INCLUDE"]);
   //SetEnvironmentVariable("LIBPATH",map["LIBPATH"]);
   //SetEnvironmentVariable("PATH",map["PATH"]);

   // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
   //CProcessEnvReader::ReleaseHandle(hProcess);



//      stra.add_lines(strLog);

   //string strEnv = file_as_string_dup("C:\\ca2\\env.txt");

#endif

   ::file::path strFolder;
   strFolder = System.dir().element();
   if(!::str::ends(strFolder,"/") && !::str::ends(strFolder,"\\"))
      strFolder += "/";
   string strTemplate;
   string strSource = "nodeapp/stage/dynamic_source/";
   strSource += lpcszSource;

   //      string strN = m_pmanager->m_strNetnodePath;
   //    strN.replace("\\","/");
   //  if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
   //   strN += "/";

   //#ifdef DEBUG
   strTemplate = strFolder / strSource;
   //#else
   // strTemplate = strFolder, "app/stage/core/fontopus/app/main/matter/dynamic_source_cl.bat", false);
   //#endif
   string str;
   str = Application.file().as_string(strTemplate);
   /*string strVars = getenv("VS100COMNTOOLS");
   System.file().path().eat_end_level(strVars, 2, "/");
   strVars += "vc/bin/vcvars32.bat";*/
   str.replace("%VS_VARS%",m_strEnv);
   str.replace("%VS_VARS_PLAT2%",m_strPlat2);

   string strV(System.dir().element());
   strV.replace("\\","/");
   if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
      strV += "/";
   str.replace("%CA2_ROOT%",strV);
   //str.replace("%NETNODE_ROOT%",strN);
   str.replace("%SDK1%",m_strSdk1);
   string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
   ::file::path strCmd;
   //#ifdef DEBUG
   strCmd = strFolder / strDest;
   //#else
   // strCmd = strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_cl.bat", false);
   //#endif
   Application.dir().mk(strCmd.folder());
   //Application.file().put_contents_utf8(strCmd, str);
   Application.file().put_contents(strCmd,str);
   Application.dir().mk(m_strTime / "dynamic_source");
}





::aura::library & compiler::compile(string strFilePath,bool & bNew)
{

   sp(library) & lib = m_lib[strFilePath];

   if(lib.is_null())
   {

      lib = canew(library(get_app()));

   }

   if(get_file_time(strFilePath) == lib->m_filetime)
   {

      bNew = false;

      return lib->m_library;

   }

   lib->m_library.close();

   bNew = true;

   lib->m_filetime = get_file_time(strFilePath);

   ::file::path strName(strFilePath);

   lib->m_pathScript = strName;

   //lib->on_start_build();

#ifdef WINDOWS

   strName.replace("/","\\");

#endif

   //strName.replace("/", "\\");
   //string strFolder;
   //strFolder = System.dir().element();
   string str;
   //::file::path strB;
   ::file::path strO;
   ::file::path strP;
   ::file::path strL;
   ::file::path strE;
   //::file::path strSVI;
   //::file::path strSVP;
   //::file::path strSPC;
   //::file::path strDVI;
   ::file::path strDVP;
   //::file::path strDPC;
   //::file::path strSO1;
   //::file::path strSO2;
   //::file::path strDO1;
   //::file::path strDO2;
   ::file::path strClog;
   ::file::path strLlog;
   ::file::path strObj;


   /*string strScript(strName);
   strScript.replace("\\", ",");
   strScript.replace("/", ",");
   strScript = "ca2" + m_pmanager->m_strNamespace + "_script." + strScript;*/
   ::file::path strScript;
   strScript = strName.title();
   ::file::path strTransformName = strName;
   if(Application.file().exists(strName))
   {
      //         lib->m_strSourcePath = strName;
      strTransformName.replace(":","");
      ::str::ends_eat_ci(strTransformName,".cpp");
   }
   else
   {
      return lib->m_library;
   }

   ::file::path strSourceDir;
   strSourceDir = strName.folder();

   //if(!Application.file().exists(lib->m_strSourcePath))
   //{
   //   lib->m_memfileError << "<pre>";
   //   str.Format("Source File : \"%s\" does not exist",lib->m_strSourcePath);
   //   lib->m_memfileError << str;
   //   lib->m_memfileError << "</pre>";
   //   return;
   //}


   //      string strTime = m_strTime;


   string strCppPath;

   //strCppPath = lib->m_pathScript;



   strClog = lib->m_pathScript + "-compile-log.txt";
   strLlog = lib->m_pathScript + "-link-log.txt";
   ::file::path strDynamicSourceScriptFolder = m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / string("introjection");

   //#ifdef DEBUG
#ifdef LINUX
   strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bash";
   strObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".o";
#else
   //strB = m_strDynamicSourceStageFolder / "front\\introjection\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
   strP = m_strDynamicSourceStageFolder / m_strStagePlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".pdb";
   strL = m_strDynamicSourceStageFolder / m_strStagePlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".lib";
   strE = m_strDynamicSourceStageFolder / m_strStagePlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".exp";
   //strCppPath = m_strDynamicSourceStageFolder / "introjection" / strTransformName.sibling(strScript.name()) + ".cpp";
   strCppPath = strName;

   //strDVI = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".idb";
   strDVP = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".pdb";
   //strDPC = strDynamicSourceScriptFolder / strTransformName / m_pmanager->m_strNamespace + "_dynamic_source_script.pch";
   //strDO1 = strDynamicSourceScriptFolder / strTransformName / "framework.obj";
   //strDO2 = strDynamicSourceScriptFolder / strTransformName / m_pmanager->m_strNamespace + "_dynamic_source_script.obj";
   //strSVI = strDynamicSourceScriptFolder / m_strSdk1 + ".idb";
   //strSVP = strDynamicSourceScriptFolder / m_strSdk1 + ".pdb";
   //strSPC = strDynamicSourceScriptFolder / m_pmanager->m_strNamespace + "_dynamic_source_script.pch";
   //strSO1 = strDynamicSourceScriptFolder / "framework.obj";
   //strSO2 = strDynamicSourceScriptFolder / m_pmanager->m_strNamespace + "_dynamic_source_script.obj";

   strObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".obj";

   strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bat";


#endif
   //lib->m_strBuildBat = strB;
   //m_pathScript = m_pmanager->get_script_path(strName);
   //#else
   // lib->m_strLibraryPath.Format(System.dir().element(m_strDynamicSourceStage /" Release\\%s.dll"), strName);
   //#endif

   try
   {
      if(Application.file().exists(strO))
      {
         Application.file().del(strO);
      }
   }
   catch(...)
   {
   }
   try
   {
      if(Application.file().exists(strObj))
      {
         Application.file().del(strObj);
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
         Application.file().del(strP);
      }
   }
   catch(...)
   {
   }
   try
   {
      if(Application.file().exists(strL))
      {
         Application.file().del(strL);
      }
   }
   catch(...)
   {
   }
   try
   {
      if(Application.file().exists(strE))
      {
         Application.file().del(strE);
      }
   }
   catch(...)
   {
   }
   //try
   //{
   //   if(Application.file().exists(strDPC))
   //   {
   //      Application.file().del(strDPC);
   //   }
   //}
   //catch(...)
   //{
   //}
   //try
   //{
   //   if(Application.file().exists(strDVP))
   //   {
   //      Application.file().del(strDVP);
   //   }
   //}
   //catch(...)
   //{
   //}
   //try
   //{
   //   if(Application.file().exists(strDVI))
   //   {
   //      Application.file().del(strDVI);
   //   }
   //}
   //catch(...)
   //{
   //}
   //try
   //{
   //   if(Application.file().exists(strDO1))
   //   {
   //      Application.file().del(strDO1);
   //   }
   //}
   //catch(...)
   //{
   //}
   //try
   //{
   //   if(Application.file().exists(strDO2))
   //   {
   //      Application.file().del(strDO2);
   //   }
   //}
   //catch(...)
   //{
   //}
#endif
   try
   {
      if(Application.file().exists(strClog))
      {
         Application.file().del(strClog);
      }
   }
   catch(...)
   {
   }
   try
   {
      if(Application.file().exists(strLlog))
      {
         Application.file().del(strLlog);
      }
   }
   catch(...)
   {
   }
   //::DeleteFile(lib->m_strBuildBat);
   //try
   //{
   //   if(Application.file().exists(lib->m_pathScript + ".old"))
   //   {
   //      Application.file().del(lib->m_pathScript + ".old");
   //   }
   //}
   //catch(string strError)
   //{
   //   TRACE0(strError + "\n");
   //}
   try
   {
      //if(Application.file().exists(lib->m_pathScript))
      //{
      //   Application.file().copy(strCppPath,lib->m_pathScript);
      //}
   }
   catch(string strError)
   {
      TRACE0(strError + "\n");
   }
   //try
   //{
   //   if(Application.file().exists(lib->m_pathScript + ".old"))
   //   {
   //      Application.file().del(lib->m_pathScript + ".old");
   //   }
   //}
   //catch(string strError)
   //{
   //   TRACE0(strError + "\n");
   //}
#ifndef LINUX

   //      Application.dir().mk(strDVI.folder());
   //      Application.dir().mk(lib->m_strBuildBat.folder());
   //try
   //{
   //   //         Application.file().copy(strDVI, strSVI, false);
   //}
   //catch(...)
   //{
   //}
   //try
   //{
   //   Application.file().copy(strDVP, strSVP, false);
   //}
   //catch(...)
   //{
   //}
   //try
   //{
   //   Application.file().copy(strDPC, strSPC, false);
   //}
   //catch(...)
   //{

   //   lib->m_bHasTempOsError = true;

   //   return;

   //}
   //try
   //{
   //   Application.file().copy(strDO1,strSO1,false);
   //}
   //catch(...)
   //{

   //   lib->m_bHasTempOsError = true;

   //   return;

   //}
   //try
   //{
   //   Application.file().copy(strDO2,strSO2,false);
   //}
   //catch(...)
   //{

   //   lib->m_bHasTempOsError = true;

   //   return;

   //}




#endif

   Application.dir().mk(lib->m_pathScript.folder());
   Application.dir().mk(strL.folder());
   Application.dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / "xmpp_resident" / strTransformName);

   //string strV(System.dir().element());
   //strV.replace("\\","/");
   //if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
   //   strV += "/";

   //string strN = m_pmanager->m_strNetnodePath;
   //strN.replace("\\","/");
   //if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
   //   strN += "/";

   string strBuildCmd;

#ifdef LINUX
   strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\introjection" / m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
#else
   strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\introjection" / m_strDynamicSourceConfiguration + ::file::path("_c") + m_strPlat1 + ".bat");
#endif

   str = Application.file().as_string(strBuildCmd);
   str.replace("%SOURCE%",::str::replace("\\","/",string(strName)));
   str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
   str.replace("%ITEM_TITLE%",strTransformName.name());
   str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
   str.replace("%LIBS_LIBS%",m_strLibsLibs);
   str.replace("%VS_VARS%",m_strEnv);
   str.replace("%VS_VARS_PLAT2%",m_strPlat2);

   string strElem = System.dir().element();

   strElem.replace("\\","/");

   strElem += "/";
   string strHmhLctvWildPdbPath;
   string strRndTitle;
   System.math().gen_rand_alnum(strRndTitle.GetBufferSetLength(64),64);
   strRndTitle.ReleaseBuffer();
   strHmhLctvWildPdbPath = ::file::path("C:\\ca2\\netnodelite\\symbols") / strRndTitle;
   strHmhLctvWildPdbPath.replace("\\","/");
   str.replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

   str.replace("%CA2_ROOT%",strElem);
   str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
   str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
   str.replace("%PLATFORM%",m_strPlatform);
   str.replace("%STAGEPLATFORM%",m_strStagePlatform);
   //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
   str.replace("%SDK1%",m_strSdk1);
   string strT2 = lib->m_pathScript;
   strT2.replace("\\",".");
   strT2.replace("/",".");
   strT2.replace(":","_");
   string strTargetPath = System.dir().element() / "time" / m_strPlatform / m_strDynamicSourceConfiguration / strT2 ;
   ::str::ends_eat_ci(strTargetPath,".cpp");
#ifdef LINUX
   ::str::ends_eat_ci(strTargetPath,".so");
#else
   ::str::ends_eat_ci(strTargetPath,".dll");
#endif
   strTargetPath += "-"+strRndTitle;
   str.replace("%TARGET_PATH%",strTargetPath);
   //strBuildCmd = lib->m_strBuildBat;
   //Application.file().put_contents_utf8(strBuildCmd, str);

   ///Application.file().put_contents(strBuildCmd,str);



   bool bTimeout = false;

   ::process::process_sp process(allocer());

   //      ::multithreading::set_thread_priority(::multithreading::priority_highest);

   process->create_child_process(str,true,NULL,::multithreading::priority_highest);

   uint32_t dwStart = ::get_tick_count();

   uint32_t dwExitCode;

   string strLog;

   while(true)
   {

      strLog += process->read();

      if(process->has_exited(&dwExitCode))
         break;

      Sleep(100);

      if(::get_tick_count() - dwStart > 840 * 1000) // 14 minutes
      {

         bTimeout = true;

         break;

      }

   }

   strLog += process->read();

   if(bTimeout)
   {

      process->kill();

   }

   if(!bTimeout && strLog.has_char())
   {

#ifdef LINUX

      //Sleep(1984);

#endif


      str = strLog;



      str.trim();

      if(str.has_char())
      {

         Application.file().put_contents_utf8(strClog,strLog);

         lib->m_memfileError << "<pre>";

         lib->m_memfileError << "Compiling...\n";
         lib->m_memfileError << lib->m_pathScript;
         lib->m_memfileError << "\n";
         if(bTimeout)
         {
            lib->m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + lib->m_pathScript + "\" following this message, they may be out-of-date)";
         }
         str.replace("\r\n","\n");
         lib->m_memfileError << str;

      }

      strBuildCmd;

#ifdef LINUX
      strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\introjection" / m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
#else
      strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\introjection" / m_strDynamicSourceConfiguration + ::file::path("_l") + m_strPlat1 + ".bat");
#endif

      str = Application.file().as_string(strBuildCmd);


      str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
      str.replace("%ITEM_TITLE%",strTransformName.name());
      str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
      str.replace("%LIBS_LIBS%",m_strLibsLibs);
      str.replace("%VS_VARS%",m_strEnv);
      str.replace("%VS_VARS_PLAT2%",m_strPlat2);

      str.replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

      str.replace("%CA2_ROOT%",strElem);
      str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      str.replace("%PLATFORM%",m_strPlatform);
      str.replace("%STAGEPLATFORM%",m_strStagePlatform);
      //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
      str.replace("%SDK1%",m_strSdk1);
      //string strTargetPath = lib->m_pathScript;
      //strTargetPath.replace("\\",".");
      //strTargetPath.replace("/",".");
      //::str::ends_eat_ci(strTargetPath,".cpp");
      //#ifdef LINUX
      //         ::str::ends_eat_ci(strTargetPath,".so");
      //#else
      //         ::str::ends_eat_ci(strTargetPath,".dll");
      //#endif
      //         strTargetPath = System.dir().element() /
      str.replace("%TARGET_PATH%",strTargetPath);

      //strBuildCmd = lib->m_strBuildBat;
      //Application.file().put_contents_utf8(strBuildCmd, str);

      //Application.file().put_contents(strBuildCmd,str);

      //str.replace("\\", "/");

      bTimeout = false;

      ::process::process_sp process(allocer());

      //         set_thread_priority(::multithreading::priority_highest);

      process->create_child_process(str,true,NULL,::multithreading::priority_highest);

      uint32_t dwStart = ::get_tick_count();

      uint32_t dwExitCode;

      string strLog;

      while(true)
      {

         strLog += process->read();

         if(process->has_exited(&dwExitCode))
            break;

         Sleep(100);

         if(::get_tick_count() - dwStart > 840 * 1000) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      strLog += process->read();



      if(!bTimeout && strLog.has_char())
      {

#ifdef LINUX

         //Sleep(1984);

#endif



         str = strLog;

         str.trim();

         if(str.has_char())
         {

            Application.file().put_contents_utf8(strLlog,strLog);
            lib->m_memfileError << "Linking...\n";
            str.replace("\r\n","\n");
            lib->m_memfileError << str;
            lib->m_memfileError << "</pre>";


         }

         lib->m_strError = lib->m_memfileError.m_spmemorybuffer->get_memory()->to_string();

         lib->m_strError.trim();

      }

   }

#ifndef LINUX

   //try
   //{
   //   Application.file().del(strDVI);
   //}
   //catch(...)
   //{
   //}
   try
   {
      Application.file().del(strDVP);
   }
   catch(...)
   {
   }
   //try
   //{
   //   Application.file().del(strDPC);
   //}
   //catch(...)
   //{
   //}

#endif

   lib->m_library.open(strTargetPath + ".dll");

   lib->m_library.open_ca2_library();

   return lib->m_library;

}

}


