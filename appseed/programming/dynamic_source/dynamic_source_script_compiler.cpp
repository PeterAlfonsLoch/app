#include "framework.h"
#include "dynamic_source.h"


#include <sys/stat.h>


#if defined(LINUX)
#include <ctype.h>
#endif




/**
* @ ProcessEnvReader.cpp - Implementation File for CProcessEnvReader class
* @ Author - Sarath C
**/

#pragma once

#include <tlhelp32.h>
#include <Winternl.h>

// macro do safe cleanp wtih specified function with object
inline void SAFE_ICON_CLEANUP(HICON hIcon)
{
   if(hIcon)
      DestroyIcon(hIcon);
}

// macro do safe cleanp wtih specified function with object
inline void SAFE_ARRAY_CLEANUP(void* pData)
{
   if(pData)
      free(pData);
}

/**
* Structure to hold the environment string block and it's size
**/
struct _ENVSTRING_t
{
   LPCWSTR pData;
   int nSize;

   _ENVSTRING_t() // Ctor of structure
   {
      pData = 0; nSize = 0;
   }

   ~_ENVSTRING_t() // Ctor of structure
   {
      Clear();
   }
   void Clear() // dtor of structure
   {
      if(pData)
      {
         delete[] pData;
         pData = 0;
      }
      nSize = 0;
   }
};

// enumeration to specify the destinaton of copying while export data
enum COPY_DEST_e { DEST_CLIPBRD,DEST_FILE };

// arrays and other definitions used to process strings
typedef array<PROCESSENTRY32> ProcessInfoArray;
typedef ::pair<string,string> EnvVariableValuePair;
typedef array<EnvVariableValuePair> EnvVarValArray;

/**
* Class provides interfaces to read process information and other misc services
**/
class CProcessEnvReader
{
public:
   // Wrapper to call NtQueryInformationProcess using Run-time dynamic linking
   static NTSTATUS QueryInformationProcesss(IN HANDLE ProcessHandle,
      IN PROCESSINFOCLASS ProcessInformationClass,
      OUT PVOID ProcessInformation,
      IN ULONG ProcessInformationLength,
      OUT PULONG ReturnLength OPTIONAL);

   /* Process Helper functions */
   static BOOL ReadEnvironmentBlock(HANDLE hProcess,_ENVSTRING_t& stEnvData);
   static HANDLE OpenProcessToRead(DWORD dwPID);
   static void ReleaseHandle(HANDLE hHandle);
   static BOOL HasReadAccess(HANDLE hProcess,void* pAddress,int& nSize);
   static void EnumProcessInfo(ProcessInfoArray& arrProcessInfo);
   static string GetProcessNameFromHandle(HANDLE hProcess);
   static string GetProcessNameFromID(DWORD dwPID);

   /* GDI Helper functions */
   static void LoadIconFromProcess(HANDLE hProcess,HICON& hIconSmall,HICON& hIconLarge);

   /* String helper functions */
   static void ConvertUnicodeToMBCS(LPCWSTR lpStringToConvert,int nLen,string& csMBCSStr);
   static void ParseEnvironmentStrings(LPCWSTR lpStringToConvert,int nLen,stringa& EnvStrArr);
   static void SeparateVariablesAndValues(const stringa& EnvStrArray,EnvVarValArray& varValArr);

   /* Export functions */
//   static void ExportEnvStrings(const stringa& csArrEnvStr,COPY_DEST_e Dest,HWND hClipboardOwner);
   static void UpdateProcessMiscInfo(HANDLE hProcess,int nItemSelected);
};

namespace dynamic_source
{

   string escape(const char * lpcsz);

   void add_var_id(string & strResult, strsize & iArroba, stringa & straId, bool bMakeKeyLower = true);


   script_compiler::script_compiler(::aura::application * papp):
      ::object(papp),
//      m_memfileLibError(papp),
  //    m_mutexLibrary(papp),
      m_mutex(papp)//,
//      m_libraryLib(papp)


   {

      file_watcher_initialize_listener_thread(papp);

#if defined(MEMDLEAK)

      m_strDynamicSourceConfiguration = "memdleak";
      m_strDynamicSourceStage = "stage";


#elif defined(DEBUG)

      m_strDynamicSourceConfiguration = "basis";
      m_strDynamicSourceStage = "time";

#else

      m_strDynamicSourceConfiguration = "profiler";
      m_strDynamicSourceStage = "profiler";

#endif

      m_strDynamicSourceStageFolder = System.dir().element()/m_strDynamicSourceStage;

   }

   script_compiler::~script_compiler()
   {
   }

   void script_compiler::initialize()
   {
      prepare_compile_and_link_environment();
      folder_watch();
//      compile_library();
      run_persistent();
      parse_pstr_set();
   }

   void script_compiler::prepare_compile_and_link_environment()
   {

      Application.dir().mk("C:\\ca2\\netnodelite\\symbols");
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
      strPlat2 = " x86";
      m_strPlatform = "Win32";
      m_strStagePlatform = "x86";
      m_strLibPlatform = "x86/";
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
      prepare1(m_strPlat1,m_strPlat1);
      //prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat",
      //   m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat");
      //prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat",
      //   m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat");
      //prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat",
      //   m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat");
#endif
      System.dir().mk(System.dir().element()/m_strDynamicSourceStage / "front",get_app());

//#ifdef WINDOWS
//      string vars1batSrc;
//      string vars2batSrc;
//      string vars1batDst;
//      string vars2batDst;
//      vars1batSrc = System.dir().element()/"nodeapp/stage/dynamic_source/vc_vars.bat";
//      vars2batSrc = System.dir().element()/"nodeapp/stage/dynamic_source/vc_vars_query_registry.bat";
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
      var var = System.process().get_output("\"" + m_strEnv  + "\" "+ m_strPlat2);
      TRACE0(var.get_string());

#endif

      string str;
      string strItem;

      strItem = System.dir().element() / m_strDynamicSourceStage /m_strStagePlatform;
      str = str + strItem + ";";

      strItem = System.dir().element()/ m_strDynamicSourceStage /  m_strStagePlatform / "dynamic_source\\library";
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

      TRACE("Compiling script \"%s\"\n",pscript->m_strName.c_str());

      ::file::path strName(pscript->m_strName);

      pscript->on_start_build();

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
         pscript->m_strSourcePath = strName;
         strTransformName.replace(":","");
      }
      else
      {
         pscript->m_strSourcePath.Format(m_pmanager->m_strNetnodePath / "net\\netseed\\%s",false,strName);
      }
      pscript->m_strSourceDir = pscript->m_strSourcePath.folder();

      if(!Application.file().exists(pscript->m_strSourcePath))
      {
         pscript->m_memfileError << "<pre>";
         str.Format("Source File : \"%s\" does not exist",pscript->m_strSourcePath);
         pscript->m_memfileError << str;
         pscript->m_memfileError << "</pre>";
         return;
      }


      string strTime = m_strTime;


      pscript->m_strCppPath.Format(m_strTime / "dynamic_source\\%s.cpp",strTransformName);



      strClog.Format(m_strTime / "dynamic_source/%s-compile-log.txt",strTransformName);
      strLlog.Format(m_strTime / "dynamic_source/%s-link-log.txt",strTransformName);

      //#ifdef DEBUG
#ifdef LINUX
      strB = System.dir().element() / m_strDynamicSourceStage / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strO = ::file::path(m_strTime) / "intermediate" / m_strPlatform / m_pmanager->m_strNamespace + "_dynamic_source_script" / strTransformName / strTransformName.name() + ".o";
#else
      //strB = m_strDynamicSourceStageFolder / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strP = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".pdb";
      strL = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".lib";
      strE = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".exp";


      ::file::path strDynamicSourceScriptFolder = m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strNamespace + "_dynamic_source_script";
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
      //pscript->m_strBuildBat = strB;
      pscript->m_strScriptPath = m_pmanager->get_script_path(strName);
      //#else
      // pscript->m_strLibraryPath.Format(System.dir().element(m_strDynamicSourceStage /" Release\\%s.dll"), strName);
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
      //::DeleteFile(pscript->m_strBuildBat);
      try
      {
         if(Application.file().exists(pscript->m_strScriptPath + ".old"))
         {
            Application.file().del(pscript->m_strScriptPath + ".old");
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
            Application.file().move(pscript->m_strScriptPath + ".old",pscript->m_strScriptPath);
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
            Application.file().del(pscript->m_strScriptPath + ".old");
         }
      }
      catch(string strError)
      {
         TRACE0(strError + "\n");
      }
#ifndef LINUX

      //      Application.dir().mk(strDVI.folder());
//      Application.dir().mk(pscript->m_strBuildBat.folder());
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

      //   pscript->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   Application.file().copy(strDO1,strSO1,false);
      //}
      //catch(...)
      //{

      //   pscript->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   Application.file().copy(strDO2,strSO2,false);
      //}
      //catch(...)
      //{

      //   pscript->m_bHasTempOsError = true;

      //   return;

      //}




#endif

      Application.dir().mk(pscript->m_strScriptPath.folder());
      Application.dir().mk(strL.folder());
      Application.dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strNamespace + ::file::path("_dynamic_source_script") / strTransformName);

      cppize(pscript);

      string strV(System.dir().element());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;
      strN.replace("\\","/");
      if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
         strN += "/";

      string strBuildCmd;

#ifdef LINUX
      strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
#else
      strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_c") + m_strPlat1 + ".bat");
#endif

      str = Application.file().as_string(strBuildCmd);
      str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
      str.replace("%ITEM_TITLE%",strTransformName.name());
      str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
      str.replace("%LIBS_LIBS%",m_strLibsLibs);
      str.replace("%VS_VARS%",m_strEnv);
      str.replace("%VS_VARS_PLAT2%",m_strPlat2);


      str.replace("%CA2_ROOT%",strV);
      str.replace("%NETNODE_ROOT%",strN);
      str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      str.replace("%PLATFORM%",m_strPlatform);
      str.replace("%STAGEPLATFORM%",m_strStagePlatform);
      //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
      str.replace("%SDK1%",m_strSdk1);
      string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX
      ::str::ends_eat_ci(strTargetPath,".so");
#else
      ::str::ends_eat_ci(strTargetPath,".dll");
#endif
      str.replace("%TARGET_PATH%",strTargetPath);
      //strBuildCmd = pscript->m_strBuildBat;
      //Application.file().put_contents_utf8(strBuildCmd, str);

      ///Application.file().put_contents(strBuildCmd,str);



      bool bTimeout = false;

      ::process::process_sp process(allocer());

      set_thread_priority(::multithreading::priority_highest);

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

            Application.file().put_contents_utf8(strClog, strLog);

            pscript->m_memfileError << "<pre>";

            pscript->m_memfileError << "Compiling...\n";
            pscript->m_memfileError << pscript->m_strCppPath;
            pscript->m_memfileError << "\n";
            if(bTimeout)
            {
               pscript->m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + pscript->m_strCppPath + "\" following this message, they may be out-of-date)";
            }
            str.replace("\r\n","\n");
            pscript->m_memfileError << str;

         }

         strBuildCmd;

#ifdef LINUX
         strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
#else
         strBuildCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_l") + m_strPlat1 + ".bat");
#endif

         str = Application.file().as_string(strBuildCmd);
         str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
         str.replace("%ITEM_TITLE%",strTransformName.name());
         str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
         str.replace("%LIBS_LIBS%",m_strLibsLibs);
         str.replace("%VS_VARS%",m_strEnv);
         str.replace("%VS_VARS_PLAT2%",m_strPlat2);


         str.replace("%CA2_ROOT%",strV);
         str.replace("%NETNODE_ROOT%",strN);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
         str.replace("%SDK1%",m_strSdk1);
         string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX
         ::str::ends_eat_ci(strTargetPath,".so");
#else
         ::str::ends_eat_ci(strTargetPath,".dll");
#endif
         str.replace("%TARGET_PATH%",strTargetPath);
         string strHmhLctvWildPdbPath;
         string strRndTitle;
         System.math().gen_rand_alnum(strRndTitle.GetBufferSetLength(64),64);
         strRndTitle.ReleaseBuffer();
         strHmhLctvWildPdbPath = ::file::path("C:\\ca2\\netnodelite\\symbols") / strRndTitle;
         
         str.replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

         //strBuildCmd = pscript->m_strBuildBat;
         //Application.file().put_contents_utf8(strBuildCmd, str);

         //Application.file().put_contents(strBuildCmd,str);

         //str.replace("\\", "/");

         bTimeout = false;

         ::process::process_sp process(allocer());

         set_thread_priority(::multithreading::priority_highest);

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
               pscript->m_memfileError << "Linking...\n";
               str.replace("\r\n","\n");
               pscript->m_memfileError << str;
               pscript->m_memfileError << "</pre>";


            }

            pscript->m_strError = pscript->m_memfileError.m_spmemorybuffer->get_memory()->to_string();

            pscript->m_strError.trim();

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

   }

   void script_compiler::cppize(ds_script * pscript)
   {

      auto ftDs = get_file_time(pscript->m_strSourcePath);

      if(Application.file().exists(pscript->m_strCppPath))
      {

         if(ftDs == pscript->m_ftDs)
         {

            return; // nothing to do

         }

      }

      Application.dir().mk(pscript->m_strCppPath.folder());
      
      cppize1(pscript);

      pscript->m_ftDs = ftDs;

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
      /*::file::buffer_sp spfile(allocer());
      if(spfile->open(pscript->m_strSourcePath, ::file::type_binary | ::file::mode_read | ::file::share_deny_none).failed())
      return;

      memory memstorage;
      memstorage.allocate(spfile->get_length() + 1);
      memstorage.get_data()[memstorage.get_size() - 1] = '\0';
      memstorage.read(file);*/
      string strSource = Application.file().as_string(pscript->m_strSourcePath);
      strsize iPosId = -1;
      stringa straId;
      string strDest;
      strDest = "";
      strDest += "#include \"netnode_dynamic_source_script.h\"\r\n";
      //strDest += "#include \"11ca2_fontopus.h\"\r\n";
      //for(int32_t i = 0; i < m_straLibIncludePath.get_count(); i++)
      //{
      //   string str;
      //   str = m_straLibIncludePath[i].relative();
      //   ::str::ends_eat_ci(str, ".ds");
      //   strDest += "#include \""+str+".h\"\r\n";
      //}
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
      strDest += "   " + m_pmanager->m_strNamespace + "_dynamic_source_script(dynamic_source::script * pscript) : ::object(pscript->get_app()), dynamic_source::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_impl(pscript) {};  \r\n";
      strDest += "   virtual void run();\r\n";
      strDest += "   \r\n\r\n";
      strDest += strDs;
      strDest += "   \r\n\r\n\r\n";
      strDest += "};\r\n";
      strDest += "\r\n";
      strDest += "extern \"C\" __declspec(dllexport) dynamic_source::script_instance * __cdecl create_dynamic_source_script_instance (dynamic_source::script * pscript)\r\n";
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


      string strCppPath =  pscript->m_strCppPath;

      strCppPath.replace("\\","\\\\");

      strDest += " \r\n \
         extern \"C\" int32_t APIENTRY \r\n \
         DllMain(HINSTANCE hInstance,uint32_t dwReason,LPVOID lpReserved) \r\n \
      { \r\n \
\r\n  \
 \r\n \r\n \
         UNREFERENCED_PARAMETER(hInstance); \r\n \
         UNREFERENCED_PARAMETER(lpReserved); \r\n \
 \r\n \
 \r\n \
         if(dwReason == DLL_PROCESS_ATTACH) \r\n \
         { \r\n \
 \r\n \
 \r\n \
             ::OutputDebugString(\"netnodelite script initializing : " + strCppPath + "!\\n\"); \r\n \
 \r\n \
 \r\n \
         } \r\n \
         else if(dwReason == DLL_PROCESS_DETACH) \r\n \
         { \r\n \
 \r\n \
 \r\n \
            ::OutputDebugString(\"netnodelite script terminating : " + strCppPath + "!\\n\"); \r\n \
 \r\n \
 \r\n \
         } \r\n \
 \r\n \
         return 1;    \r\n \
 \r\n \
      }\r\n\r\n\r\n\r\n\r\n";

      //Application.file().put_contents_utf8(pscript->m_strCppPath, strDest);
      Application.file().put_contents(pscript->m_strCppPath, strDest);

   }

   void script_compiler::prepare1(const char * lpcszSource, const char * lpcszDest)
   {


      string strBuildCmd = m_strEnv;

      strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;

      ::process::process_sp process(allocer());


      file_put_contents_dup("C:\\ca2\\env.bat","@call " + strBuildCmd + "\r\n@set");

      set_thread_priority(::multithreading::priority_highest);

      process->create_child_process("C:\\ca2\\env.bat",true,::file::path(m_strEnv).folder(),::multithreading::priority_highest);
      string strLog;

   //   EnvVarValArray arrEnvVarVal;

   //   uint32_t dwStart = ::get_tick_count();

   //   uint32_t dwExitCode;

   //   string strLog;

   //   stringa m_strArray;
   //   // Open the process for further operations
   //   HANDLE hProcess = CProcessEnvReader::OpenProcessToRead(process->m_iPid);
   //   if(hProcess)
   //   {
   //      _ENVSTRING_t stEnvData;
   //      // Read the process environment block
   //      if(!CProcessEnvReader::ReadEnvironmentBlock(hProcess,stEnvData))
   //      {
   //         return;
   //      }

   //      // Parse the retrieved data
   //      CProcessEnvReader::ParseEnvironmentStrings(stEnvData.pData,
   //         stEnvData.nSize / 2,
   //         m_strArray);


   //      // Seperate values and variables
   //      CProcessEnvReader::SeparateVariablesAndValues(m_strArray,arrEnvVarVal);

   //      // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
   //      CProcessEnvReader::ReleaseHandle(hProcess);
   //   }
   //process->write("\n");
      uint32_t dwExitCode;
      DWORD dwStart = get_tick_count();
   while(true)
   {

      strLog += process->read();

      if(process->has_exited(&dwExitCode))
         break;

      Sleep(100);

      if(::get_tick_count() - dwStart > 840 * 1000) // 14 minutes
      {

         //            bTimeout = true;

         break;

      }

   }

      strLog += process->read();
      stringa stra;

      stra.add_lines(strLog);

      Sleep(10000);

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

      

      stra.add_lines(strLog);

      //string strEnv = file_as_string_dup("C:\\ca2\\env.txt");

      ::file::path strFolder;
      strFolder = System.dir().element();
      if(!::str::ends(strFolder, "/") && !::str::ends(strFolder, "\\"))
         strFolder += "/";
      string strTemplate;
      string strSource = "nodeapp/stage/dynamic_source/";
      strSource += lpcszSource;

      string strN = m_pmanager->m_strNetnodePath;
      strN.replace("\\","/");
      if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
         strN += "/";

      //#ifdef DEBUG
      strTemplate = strFolder/ strSource;
      //#else
      // strTemplate = strFolder, "app/stage/core/fontopus/app/main/matter/dynamic_source_cl.bat", false);
      //#endif
      string str;
      str = Application.file().as_string(strTemplate);
      /*string strVars = getenv("VS100COMNTOOLS");
      System.file().path().eat_end_level(strVars, 2, "/");
      strVars += "vc/bin/vcvars32.bat";*/
      str.replace("%VS_VARS%", m_strEnv);
      str.replace("%VS_VARS_PLAT2%", m_strPlat2);

      string strV(System.dir().element());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";
      str.replace("%CA2_ROOT%",strV);
      str.replace("%NETNODE_ROOT%", strN);
      str.replace("%SDK1%", m_strSdk1);
      string strDest = m_strDynamicSourceStage / "front"  / lpcszDest;
      ::file::path strCmd;
      //#ifdef DEBUG
      strCmd = strFolder/ strDest;
      //#else
      // strCmd = strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_cl.bat", false);
      //#endif
      Application.dir().mk(strCmd.folder());
      //Application.file().put_contents_utf8(strCmd, str);
      Application.file().put_contents(strCmd, str);
      Application.dir().mk(m_strTime/ "dynamic_source");
   }


   void script_compiler::handle_file_action(::file_watcher::id watchid, const char * pszFolder, const char * psz, ::file_watcher::e_action eaction)
   {

      synch_lock sl(&m_mutex);

      UNREFERENCED_PARAMETER(eaction);
      ::file::path str = ::file::path(pszFolder) / psz;
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

      if(::str::begins(str, m_pmanager->m_strNetseedDsCa2Path/ "library/include"))
      {
//         compile_library();
         m_pmanager->m_pcache->set_all_out_of_date();
      }
      else if(::str::begins(str, m_pmanager->m_strNetseedDsCa2Path / "library/source"))
      {
         //compile_library();
      }
      else if(defer_run_persistent(str))
      {
      }

   }

   void script_compiler::folder_watch()
   {

      m_filewatchid           = add_file_watch(m_pmanager->m_strNetseedDsCa2Path, true);
      //m_filewatchidFribox     = add_file_watch("Z:/fribox/ds/", true);

   }

   library & script_compiler::lib(const char * pszLibrary)
   {

      single_lock slLibrary(&m_mutexLibrary,TRUE);

      auto p = m_mapLib.PLookup(pszLibrary);

      if(p != NULL)
      {
         return *p->m_element2;
      }

      m_mapLib[pszLibrary] = canew(library(get_app()));

      library & l = *m_mapLib[pszLibrary];

      
      string strV(System.dir().element());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;
      strN.replace("\\","/");
      if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
         strN += "/";


      //unload_library();

      string strLibrary(pszLibrary);

      ::file::path strName = strLibrary;

      m_strLibsLibs = System.dir().element() / "time/library" / m_strStagePlatform / "/library/"+strLibrary+".lib";

      //m_memfileLibError.set_length(0);
      string strFolder;
      strFolder = System.dir().element();

      l.m_straLibSourcePath.m_pprovider=get_app();
      l.m_straLibSourcePath.clear_results();
      l.m_straLibSourcePath.rls(m_pmanager->m_strNetseedDsCa2Path / "library" / strName);
      for(int32_t i = 0; i < l.m_straLibSourcePath.get_size();)
      {
         if(l.m_straLibSourcePath[i].ext() != "ds" && l.m_straLibSourcePath[i].ext() != "cpp")
         {
            l.m_straLibSourcePath.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      l.m_straLibCppPath.remove_all();
      ::file::path strLibRel = ::file::path("dynamic_source/library") / strName;
      for(int32_t i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         string str = l.m_straLibSourcePath[i].relative();
         ::str::ends_eat_ci(str,".ds");
         str.replace(":","");
         l.m_straLibCppPath.add(m_strTime / strLibRel / str + ".cpp");
      }
      l.m_straLibIncludePath.m_pprovider=get_app();
      l.m_straLibIncludePath.clear_results();
      l.m_straLibIncludePath.rls(m_pmanager->m_strNetseedDsCa2Path / "library" / strName);
      for(int32_t i = 0; i < l.m_straLibIncludePath.get_size();)
      {
         if(l.m_straLibIncludePath[i].ext() != "h"
            || ::str::find_ci(l.m_straLibIncludePath[i],"\\.svn\\") >= 0
            || Application.dir().is(l.m_straLibIncludePath[i]))
         {
            l.m_straLibIncludePath.remove_at(i);
         }
         else
         {
            i++;
         }
      }
      l.m_straLibHppPath.remove_all();
      for(int32_t i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         string str = l.m_straLibIncludePath[i].relative();
         ::str::ends_eat_ci(str,".ds");
         str.replace(":","");
         l.m_straLibHppPath.add(m_strTime / strLibRel / str + ".h");
      }

      string strLib(strName.name());


      //#ifdef DEBUG
#ifdef LINUX
      l.m_strLibraryPath = "/core/" / m_strDynamicSourceStage / "x86/libnetnodelibrary.so";
#else
      l.m_strLibraryPath = System.dir().element() / m_strDynamicSourceStage / m_strStagePlatform / "dynamic_source/" / strName / strLib + ".dll";
#endif
      //#else
      // plib->m_strLibraryPath.Format(strFolder, "app/stage/core/fontopus/app/main/front/Release/%s.dll", false), strName);
      //#endif

      Application.dir().mk(l.m_strLibraryPath.folder());
      Application.dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strNamespace + "_dynamic_source_library/library");

      for(int32_t i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         cppize(l.m_straLibIncludePath[i],l.m_straLibHppPath[i],cpptype_include);
      }


//      string strN = m_pmanager->m_strNetnodePath;
  //    strN.replace("\\","/");
    //  if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
      //   strN += "/";


#ifdef WINDOWS
      string vars1batSrc;
      string vars2batSrc;
      string vars1batDst;
      string vars2batDst;
      vars1batSrc = System.dir().element() / "nodeapp/stage/dynamic_source/vc_vars.bat";
      vars2batSrc = System.dir().element() / "nodeapp/stage/dynamic_source/vc_vars_query_registry.bat";
      vars1batDst = System.dir().element() / m_strDynamicSourceStage / "front/vc_vars.bat";
      vars2batDst = System.dir().element() / m_strDynamicSourceStage / "front/vc_vars_query_registry.bat";
      try
      {
         Application.file().copy(vars1batDst,vars1batSrc,false);
      }
      catch(...)
      {
      }
      try
      {
         Application.file().copy(vars2batDst,vars2batSrc,false);
      }
      catch(...)
      {
      }

#endif

      for(int32_t i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         if(l.m_straLibSourcePath[i].ext() == "cpp")
         {
            ::CopyFile(l.m_straLibSourcePath[i],l.m_straLibCppPath[i], FALSE);
         }
         else
         {
            cppize(l.m_straLibSourcePath[i],l.m_straLibCppPath[i],cpptype_source);

         }
         string strRel = l.m_straLibSourcePath[i].relative();
         ::str::ends_eat_ci(strRel,".ds");
         ::str::ends_eat_ci(strRel,".cpp");
         strRel.replace("\\","/");
         ::file::path str1;
         str1 = "library/source" / strRel;
         string strCmd;
         //#ifdef DEBUG
//#ifdef LINUX
//         strCmd = System.dir().element()/ m_strDynamicSourceStage / "front"/ m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash";
//#else
//         strCmd = System.dir().element() / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bat";
//#endif
#ifdef LINUX
         strCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
#else
         strCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_libc") + m_strPlat1 + ".bat");
#endif

         //#else
         //    strCmd.Format(strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_cl.bat", false));
         //#endif
         string str = Application.file().as_string(strCmd);


         str.replace("%ITEM_NAME%",::str::replace("\\","/",string(l.m_straLibCppPath[i])));
         str.replace("%ITEM_TITLE%",l.m_straLibCppPath[i].name());
         str.replace("%ITEM_DIR%",::str::replace("\\","/",string(l.m_straLibCppPath[i].folder())) + "/");
         str.replace("%LIBS_LIBS%",m_strLibsLibs);
         str.replace("%VS_VARS%",m_strEnv);
         str.replace("%VS_VARS_PLAT2%",m_strPlat2);


         str.replace("%CA2_ROOT%",strV);
         str.replace("%NETNODE_ROOT%",strN);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
         str.replace("%SDK1%",m_strSdk1);


         //str.replace("%ITEM_NAME%",::str::replace("\\","/",string(str1)));
         //str.replace("%ITEM_DIR%",::str::replace("\\", "/", string(str1.folder())) +"/" );
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         str.replace("%NETNODE_ROOT%",strN);
         str.replace("%LIBPLATFORM%",m_strLibPlatform);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%SDK1%",m_strSdk1);
         Application.dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strNamespace + "_dynamic_source_library" / str1.folder());
         Application.dir().mk(m_strTime / "library" / m_strStagePlatform / str1.folder());

         string strFormat = "libc-" + str1;

         strFormat.replace("/","-");
         strFormat.replace("\\","-");

#ifdef LINUX
         strFormat += ".bash";
#else
         strFormat += ".bat";
#endif
         strCmd = System.dir().element() / m_strDynamicSourceStage / "front" / strFormat;

         bool bTimeout = false;

         ::process::process_sp process(allocer());

         set_thread_priority(::multithreading::priority_highest);

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
         string strClog;
         strClog = m_strTime / strLibRel / strRel +"-compile-log.txt";

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

               l.m_memfileError << "<pre>";

               l.m_memfileError << "Compiling...\n";
               l.m_memfileError << l.m_straLibCppPath[i];
               l.m_memfileError << "\n";
               if(bTimeout)
               {
                  l.m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + l.m_straLibCppPath[i] + "\" following this message, they may be out-of-date)";
               }
               str.replace("\r\n","\n");
               l.m_memfileError << str;

            }



            l.m_strError = l.m_memfileError.m_spmemorybuffer->get_memory()->to_string();

            l.m_strError.trim();

         }


      }

      string strObjs;
      for(int32_t i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         strObjs += " ";
         ::file::path strRel = l.m_straLibSourcePath[i].relative();
         ::str::ends_eat_ci(strRel,".ds");
         strObjs += m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strNamespace + "_dynamic_source_library/library" / strName;
         strObjs += m_strTime.sep();
         strObjs += strRel;
#ifdef LINUX
         strObjs+=".o";
#else
         strObjs+=".obj";
#endif
         strObjs += " ";
      }
      ::file::path strCmd;
      //#ifdef DEBUG
//      strCmd = System.dir().element() / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 +
//#ifdef LINUX
//         ".bash";
//#else
//         ".bat";
//#endif
#ifdef LINUX
      strCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");
#else
      strCmd.Format(System.dir().element() / "nodeapp\\stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_libl") + m_strPlat1 + ".bat");
#endif
      //#else
      // strCmd.Format(strFolder, "app\\stage\\core\\fontopus\\app\\main\\front\\dynamic_source_libl.bat", false));
      //#endif
      string str = Application.file().as_string(strCmd);
      str.replace("%ITEM_NAME%",::file::path("library")/strName);
      str.replace("%ITEM_DIR%","library");
      str.replace("%OBJECTS%",strObjs);
      str.replace("%PLATFORM%",m_strPlatform);
      str.replace("%STAGEPLATFORM%",m_strStagePlatform);
      str.replace("%NETNODE_ROOT%",strN);
      str.replace("%LIBPLATFORM%",m_strLibPlatform);
      str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      str.replace("%SDK1%",m_strSdk1);
      string strTargetName = l.m_strLibraryPath;
      ::str::ends_eat_ci(strTargetName,".dll");
      str.replace("%TARGET_NAME%", strTargetName);
      Application.dir().mk(System.dir().element()/ m_strDynamicSourceStage / m_strStagePlatform /"library");
//#ifdef LINUX
//      //Sleep(1984);
//      strCmd = System.dir().element()/m_strDynamicSourceStage/ "front\\libl1.bash";
//#else
//      strCmd = System.dir().element()/ m_strDynamicSourceStage / "front\\libl1.bat";
//#endif

      //Application.file().put_contents_utf8(strCmd, str);
      bool bTimeout = false;

      ::process::process_sp process(allocer());

      set_thread_priority(::multithreading::priority_highest);

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

      string strLlog;

      strLlog = m_strTime / strLibRel /"link-log.txt";


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
            l.m_memfileError << "Linking...\n";
            str.replace("\r\n","\n");
            l.m_memfileError << str;
            l.m_memfileError << "</pre>";


         }

         l.m_strError = l.m_memfileError.m_spmemorybuffer->get_memory()->to_string();

         l.m_strError.trim();

      }



      l.load_library();

      return l;

   }



   void script_compiler::cppize(const ::file::path & lpcszSource,const ::file::path & lpcszDest,ecpptype e_type)
   {
      Application.dir().mk(lpcszDest.folder());
      cppize1(lpcszSource, lpcszDest, e_type);
   }

   void script_compiler::cppize1(const ::file::path & lpcszSource,const ::file::path & lpcszDest,ecpptype e_type)
   {

      string strSource = Application.file().as_string(lpcszSource);

      bool bCode = false;

      string strDest;
      strDest = "";
      strDest = "";
      if(e_type == cpptype_source || e_type == cpptype_ds)
      {
         strDest += "#include \"netnode_dynamic_source_script.h\"\r\n";
         //strDest += "#include \"11ca2_fontopus.h\"\r\n";
         //for(int32_t i = 0; i < m_straLibIncludePath.get_count(); i++)
         //{
         //   string str;
         //   str = m_straLibIncludePath[i].relative();
         //   ::str::ends_eat_ci(str, ".ds");
         //   strDest += "#include \""+str+".h\"\r\n";
         //}
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

   string script_compiler::cppize2(const string & psz,bool bScript,stringa & straId)
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
            //debug_break();
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
      string strPath = m_pmanager->m_strNetseedDsCa2Path/ "core\\persistent";
      ::file::listing stra(get_app());
      stra.rls(strPath);

      string strCat;
      strCat = m_pmanager->m_strNetseedDsCa2Path/ "core\\netnode_persistent_ui_str.ds";
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
         if(::str::begins_ci(str, m_pmanager->m_strNetseedDsCa2Path/ "core\\persistent")
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
         ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript);
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
            avoid_parsing_exception avoidparsingexception;
            pinstance->run();
         }
         catch(...)
         {
         }
         try
         {
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

         parse_pstr_set();

         //string strCat;
         //strCat = m_pmanager->m_strNetseedDsCa2Path/ "core\\netnode_persistent_ui_str.ds";
         //string strInclude = strCat;
         //::str::begins_eat_ci(strInclude, m_pmanager->m_strNetseedDsCa2Path);
         //::str::ends_eat_ci(strInclude, ".ds");
         //script_instance * pinstance = m_pmanager->get(strInclude);
         //if(pinstance != NULL)
         //{
         //   string strError;
         //   pinstance->initialize(pinstance, NULL, NULL, m_pmanager);
         //   ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript);
         //   if(pdsscript != NULL)
         //   {
         //      try
         //      {
         //         pdsscript->m_memfileError.seek_to_begin();
         //         m_pmanager->m_strPersistentError += pdsscript->m_memfileError.to_string();
         //      }
         //      catch(...)
         //      {
         //      }
         //   }
         //   try
         //   {
         //      avoid_parsing_exception avoidparsingexception;
         //      pinstance->run();
         //   }
         //   catch(...)
         //   {
         //   }
         //   try
         //   {
         //      pinstance->destroy();
         //   }
         //   catch(...)
         //   {
         //   }
         //}
      }
      else if(::str::begins_eat_ci(str,m_pmanager->m_strNetseedDsCa2Path/ "core\\persistent")
         && ::str::ends_eat_ci(str, ".ds")
         && str.CompareNoCase("netnode_persistent_ui_str") != 0)
      {
         run_persistent();
         return true;
      }
      return false;
   }


   //bool script_compiler::library_DoesMatchVersion()
   //{

   //   if(get_tick_count() - m_dwLastLibraryVersionCheck < (5000))
   //   {
   //      return m_bLastLibraryVersionCheck;
   //   }

   //   single_lock slLibrary(&m_mutexLibrary, TRUE);

   //   for(int32_t i = 0; i < m_straLibSourcePath.get_size(); i++)
   //   {

   //      //FILETIME ftCreation;
   //      //FILETIME ftAccess;
   //      //FILETIME ftModified;
   //      //memset(&ftCreation, 0, sizeof(FILETIME));
   //      //memset(&ftAccess, 0, sizeof(FILETIME));
   //      //memset(&ftModified, 0, sizeof(FILETIME));
   //      //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   //      //GetFileTime(h, &ftCreation, &ftAccess, &ftModified);
   //      //::CloseHandle(h);

   //      struct stat st;

   //      stat(m_straLibSourcePath[i], &st);

   //      if(memcmp(&st.st_ctime, &m_ftaLibCreation[i], sizeof(__time_t)) != 0
   //         || memcmp(&m_ftaLibModified[i], &st.st_mtime, sizeof(__time_t)) != 0)
   //      {
   //         m_bLastLibraryVersionCheck = false;
   //         m_dwLastLibraryVersionCheck = get_tick_count();
   //         return false;

   //      }

   //   }

   //   m_bLastLibraryVersionCheck    = true;
   //   m_dwLastLibraryVersionCheck   = get_tick_count();

   //   return true;

   //}
   void library::load_library()
   {

      single_lock slLibrary(&m_mutex, TRUE);

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

   library::library(::aura::application * papp):
      object(papp),
      m_memfileError(papp),
      m_memfileLibError(papp),
      m_mutex(papp),
      m_libraryLib(papp)

   {
   }
   library::~library()
   {
   }


   void library::unload_library()
   {
      single_lock slLibrary(&m_mutex, TRUE);
      m_libraryLib.close();
   }

   string script_compiler::get_ds_print(const char *psz)
   {
      string strSource(psz);
      string strDest;
      while(strSource.get_length() > 0)
      {
         strsize iLen = MIN(4 * 1024, strSource.get_length());
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


   void script_compiler::parse_pstr_set()
   {

      ::file::listing straFile(get_app());

      straFile.rls(m_pmanager->m_strNetnodePath / "net/netseed/core/pstr_set");

      for(int i = 0; i < straFile.get_count(); i++)
      {
         string strFile = straFile[i];
         if(::str::find_ci(".svn",strFile) >= 0 || !::str::ends_ci(strFile,".txt"))
            continue;
         strFile = Application.file().as_string(strFile);
         stringa straLine;
         straLine.explode("\r\n",strFile);
         string strExtra;
         for(int j = 0; j < straLine.get_count(); j++)
         {
            string strLine = straLine[j];
            const char * psz = strLine;
            try
            {
               ::str::consume_spaces(psz,0);
               string strId = ::str::consume_c_quoted_value(psz);
               ::str::consume_spaces(psz,1);
               string strLocale = ::str::consume_c_quoted_value(psz);
               ::str::consume_spaces(psz,1);
               string strSchema = ::str::consume_c_quoted_value(psz);
               ::str::consume_spaces(psz,1);
               string strValue = ::str::consume_c_quoted_value(psz);
               strExtra = "";
               try
               {
                  ::str::consume_spaces(psz,1);
                  strExtra = ::str::consume_c_quoted_value(psz);
               }
               catch(...)
               {
               }
               if(strExtra.has_char())
               {
                  pstr_set(strId + "." + strExtra,strLocale,strSchema,strValue);
               }
               else
               {
                  pstr_set(strId,strLocale,strSchema,strValue);
               }

            }
            catch(...)
            {
            }
         }
      }

   }


   void script_compiler::pstr_set(id pszTopic,id idLocale,id idSchema,const char * psz)
   {

      retry_single_lock sl(&m_pmanager->m_mutexPersistentStr,millis(0),millis(840));

      System.str().set(pszTopic,idLocale,idSchema,psz);

   }


} // namespace dynamic_source





  /**
  * @ ProcessEnvReader.cpp - Implementation File for CProcessEnvReader class
  * @ Author - Sarath C
  **/

#include <Winternl.h>
#include <psapi.h>

#define SHOW_ERR_DLG( x ) ::MessageBox( 0, x,_T("Exception"), MB_ICONERROR )

#pragma comment (lib,"psapi.lib" )
#pragma comment (lib,"Shell32.lib")

  /**
  * Wrapper to call NtQueryInformationProcess API by Run-Time Dynamic Linking
  * Check MSDN Documentation : http://msdn2.microsoft.com/en-us/library/ms684280(VS.85).aspx
  **/
NTSTATUS CProcessEnvReader::QueryInformationProcesss(
   IN HANDLE ProcessHandle,
   IN PROCESSINFOCLASS ProcessInformationClass,
   OUT PVOID ProcessInformation,
   IN ULONG ProcessInformationLength,
   OUT PULONG ReturnLength OPTIONAL
   )
{
   typedef NTSTATUS(__stdcall *QueryInfoProcess) (
      IN HANDLE ProcessHandle,
      IN PROCESSINFOCLASS ProcessInformationClass,
      OUT PVOID ProcessInformation,
      IN ULONG ProcessInformationLength,
      OUT PULONG ReturnLength OPTIONAL
      );

   HMODULE hModNTDll = LoadLibrary(_T("ntdll.dll"));

   if(!hModNTDll)
   {
      SHOW_ERR_DLG(_T("Error Loading library"));
   }

   QueryInfoProcess QueryProcInfo = (QueryInfoProcess)GetProcAddress(hModNTDll,
      "NtQueryInformationProcess");
   if(!QueryProcInfo)
   {
      SHOW_ERR_DLG(_T("Can't find NtQueryInformationProcess in ntdll.dll"));
      return FALSE;
   }

   NTSTATUS ntStat =  QueryProcInfo(ProcessHandle,
      ProcessInformationClass,
      ProcessInformation,
      ProcessInformationLength,
      ReturnLength);

   FreeLibrary(hModNTDll);

   return ntStat;
}


/**
* Function to Read teh environment block of specified process
**/
BOOL CProcessEnvReader::ReadEnvironmentBlock(HANDLE hProcess,_ENVSTRING_t& stEnvData)
{
   // Buffer to hold the string read from process	
   UCHAR* pchBuffEnvString = 0;
   stEnvData.Clear();
   __try
   {
      PROCESS_BASIC_INFORMATION stBasiProcInfo ={0};
      ULONG uReturnLength = 0;
      NTSTATUS ntStat =  QueryInformationProcesss(hProcess,
         ProcessBasicInformation,
         &stBasiProcInfo,
         sizeof(stBasiProcInfo),
         &uReturnLength);

      // Read the process environment block
      PEB peb ={0};
      SIZE_T nReturnNumBytes = 0;
      // Check read access of specified location in the processs and get the size of block
      ReadProcessMemory(hProcess,(LPCVOID)stBasiProcInfo.PebBaseAddress,&peb,sizeof(peb),&nReturnNumBytes);


      // Get the address of RTL_USER_PROCESS_PARAMETERS structure 
      UCHAR* puPEB = (UCHAR*)&peb;
      UCHAR* pRTLUserInfo = (UCHAR*)*((long*)(puPEB + 0x10));

      int nReadbleSize = 0;
      if(!HasReadAccess(hProcess,pRTLUserInfo,nReadbleSize))
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return FALSE;
      }

      // Get the first 0x64 bytes of RTL_USER_PROCESS_PARAMETERS strcuture
      char cBuffRTLUserInfo[0x64] ={0};
      ReadProcessMemory(hProcess,(LPCVOID)pRTLUserInfo,cBuffRTLUserInfo,0x64,&nReturnNumBytes);

      // Validate the read operation
      if(!nReturnNumBytes)
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return FALSE;
      }

      // Get the value at offset 0x48 to get the pointer to environment string block
      UCHAR* pAddrEnvStrBlock = (UCHAR*)*((long*)(&cBuffRTLUserInfo[0] + 0x48));

      if(!HasReadAccess(hProcess,pAddrEnvStrBlock,nReadbleSize))
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return FALSE;
      }

      // Allocate buffer for to copy the block
      pchBuffEnvString = new UCHAR[nReadbleSize];
      memset(pchBuffEnvString,0,sizeof(UCHAR)* nReadbleSize);

      // Read the environment block
      ReadProcessMemory(hProcess,(LPCVOID)pAddrEnvStrBlock,
         pchBuffEnvString,nReadbleSize,&nReturnNumBytes);

      // Cleanup existing data if any

      if(nReturnNumBytes)
      {
         // Set the values in the return pointer
         stEnvData.pData = (LPCWSTR)pchBuffEnvString;
         stEnvData.nSize = nReturnNumBytes;
         return TRUE;
      }
      else
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
      }
   }
   __except(SHOW_ERR_DLG(_T("Exception occured on reading process memory")))
   {
      SAFE_ARRAY_CLEANUP(pchBuffEnvString);
   }

   return FALSE;
}


/**
* Helper function to check the read access to the virtual memory of specified process
**/
BOOL CProcessEnvReader::HasReadAccess(HANDLE hProcess,
   void* pAddress,int& nSize)
{
   MEMORY_BASIC_INFORMATION memInfo;
   __try
   {
      VirtualQueryEx(hProcess,pAddress,&memInfo,sizeof(memInfo));
      if(PAGE_NOACCESS == memInfo.Protect ||
         PAGE_EXECUTE == memInfo.Protect)
      {
         nSize = 0;
         return FALSE;
      }

      nSize = memInfo.RegionSize;
      return TRUE;
   }
   __except(SHOW_ERR_DLG(_T("Failed to close Handle")))
   {

   }
   return FALSE;
}


/**
* Function to open the specified process to read or query information
**/
HANDLE CProcessEnvReader::OpenProcessToRead(DWORD dwPID)
{
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
      PROCESS_VM_READ,FALSE,dwPID);
   return hProcess;
}


/**
* Function release an opened handle
**/
void CProcessEnvReader::ReleaseHandle(HANDLE hHandle)
{
   __try
   {
      if(hHandle)
         CloseHandle(hHandle);
   }
   __except(SHOW_ERR_DLG(_T("Failed to close Handle")))
   {

   }
}


/**
* Function to enumerate and update process tree
**/
void CProcessEnvReader::EnumProcessInfo(ProcessInfoArray& arrProcessInfo)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   // Take a snapshot of all processes in the system.
   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
   if(hProcessSnap == INVALID_HANDLE_VALUE)
   {
      return;
   }

   // Set the size of the structure before using it.
   pe32.dwSize = sizeof(PROCESSENTRY32);

   // Retrieve information about the first process, and exit if unsuccessful
   if(!Process32First(hProcessSnap,&pe32))
   {
      CloseHandle(hProcessSnap);    // Must clean up the
                                    //   snapshot object!
      return;
   }

   // Now walk the snapshot of processes, and
   // display information about each process in turn
   string csProcessInfo;
   int i = 0;
   do
   {
      arrProcessInfo.push_back(pe32);

   } while(Process32Next(hProcessSnap,&pe32));

   CloseHandle(hProcessSnap);
}

/**
* Get the name of the process from handle
**/
string CProcessEnvReader::GetProcessNameFromHandle(HANDLE hProcess)
{
   TCHAR szProcessName[MAX_PATH] ={0};
   GetModuleFileNameEx(hProcess,0,szProcessName,MAX_PATH);
   return szProcessName;
}

string CProcessEnvReader::GetProcessNameFromID(DWORD dwPID)
{
   HANDLE hProcess = OpenProcessToRead(dwPID);
   string csName = GetProcessNameFromHandle(hProcess);
   ReleaseHandle(hProcess);
   return csName;
}
/**
* Function to load Icon from a process
**/
void CProcessEnvReader::LoadIconFromProcess(HANDLE hProcess,HICON& hIconSmall,HICON& hIconLarge)
{
   if(hProcess)
   {
      ExtractIconEx(GetProcessNameFromHandle(hProcess),
         0,&hIconSmall,&hIconLarge,1);
   }
}


/**
* Helper function to convert Unicode string to Multibyte
**/
void CProcessEnvReader::ConvertUnicodeToMBCS(LPCWSTR lpStringToConvert,int nLen,string& csMBCSStr)
{
   char* buff = new char[nLen + 1];

   WideCharToMultiByte(CP_ACP,0,lpStringToConvert,-1,
      buff,nLen + 1,NULL,NULL);

   csMBCSStr = buff;
   delete[]buff;
}


/**
* Extract each strings
**/
void CProcessEnvReader::ParseEnvironmentStrings(LPCWSTR lpStringToConvert,int nLen,stringa& EnvStrArr)
{
   int nIdx = 0;

   EnvStrArr.remove_all();
   while(nIdx < nLen)
   {
      size_t nSingleLen = wcslen(&lpStringToConvert[nIdx]);
      if(nSingleLen == 0)
         break;

#ifdef _UNICODE // if UNICODE, no need to convert
      LPCTSTR lpcsStr = (wchar_t*)&lpStringToConvert[nIdx];
#else // Convert to MBCS otherwise
      string csValue;
      CProcessEnvReader::ConvertUnicodeToMBCS(&lpStringToConvert[nIdx],nSingleLen,csValue);
      LPCTSTR lpcsStr = (LPCTSTR)csValue;
#endif
      nIdx += nSingleLen + 1;
      EnvStrArr.add(lpcsStr); // add string to array
   }
}


/**
* Function to Seperate variables and values
* e.g PATH=C:\ will be changed to "PATH" and "C:\"
* this will do for entire array
**/
void CProcessEnvReader::SeparateVariablesAndValues(const stringa& EnvStrArray,EnvVarValArray& varValArr)
{

   int nLen = EnvStrArray.get_size();
   for(int i = 0; i< nLen; i++)
   {
      const string& csVal = EnvStrArray[i];
      int nIndex = csVal.find(_T("="),0);

      if(-1 == nIndex || 0 == nIndex)
      {
         continue;
      }

      EnvVariableValuePair ValPair;
      // get the LHS of "=" in the string
      ValPair.m_element1= csVal.Left(nIndex);

      ValPair.m_element2 = csVal.Right(csVal.length() - nIndex - 1);
      varValArr.push_back(ValPair);
   }
}


///**
//* Function to export the string to specified destination
//**/
//void CProcessEnvReader::ExportEnvStrings(const stringa& csArrEnvStr,
//   COPY_DEST_e Dest,
//   HWND hClipboardOwner)
//{
//   const int nSize = csArrEnvStr.get_count();
//   if(!nSize)
//      return;
//
//   // Prepare the string to export
//   string csVal;
//   for(int i = 0; i < nSize; i++)
//   {
//      csVal += csArrEnvStr[i];
//      csVal+="\r\n";
//   }
//
//   if(DEST_FILE == Dest) // Copy to file
//   {
//      static TCHAR szFilter[] = _T("Text File(*.txt)|*.txt||");
//      CFileDialog fileDlg(FALSE,_T("*.txt"),NULL,NULL,szFilter,NULL);
//      if(IDOK == fileDlg.DoModal())
//      {
//         string csFilePath = fileDlg.GetPathName();
//         CStdioFile file(csFilePath,CFile::modeCreate | CFile::modeWrite);
//         file.WriteString(csVal);
//      }
//   }
//   else //  Copy data to Clipboard
//   {
//      HGLOBAL hText;
//      hText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE,csVal.GetLength()*sizeof(TCHAR) + 1);
//      TCHAR* pText = (TCHAR*)GlobalLock(hText);
//      _tcscpy(pText,csVal);
//      GlobalUnlock(hText);
//      OpenClipboard(hClipboardOwner);
//      EmptyClipboard();
//      SetClipboardData(CF_TEXT,hText);
//      CloseClipboard();
//   }
//}
