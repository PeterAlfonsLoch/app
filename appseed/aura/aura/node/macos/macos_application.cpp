#include "framework.h"
#include "macos.h"
#include <mach-o/dyld.h>



namespace macos
{


   application::application(::aura::application * papp) :
      element(papp)
   {
      m_pthreadimpl.alloc(allocer());
      m_pthreadimpl->m_pthread = this;

      shell::theLinuxShell.Initialize();
      
   }

   application::~application()
   {

   }


   void application::_001OnFileNew()
   {
      //      ::ca2::smart_pointer < ::application_base > ::m_p->_001OnFileNew(NULL);
   }

   ::user::document * application::_001OpenDocumentFile(var varFile)
   {
      //    return ::ca2::smart_pointer < ::application_base > ::m_p->_001OpenDocumentFile(varFile);
      return NULL;
   }

   void application::_001EnableShellOpen()
   {
      // xxx       ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

      // xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
      // xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
   }

   bool application::_001OnDDECommand(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      return FALSE;
   }

   
   HINSTANCE application::GetHinstance()
   {
      
      return NULL;
      
   }

   
   string application::get_version()
   {
      
      return "";


   }

   void application::TermThread(HINSTANCE hInstTerm)
   {


   }



   bool application::process_initialize()
   {

      return true;
      
   }


   bool application::initialize1()
   {

         set_run();

      return true;

   }


   bool application::initialize2()
   {
      return true;
   }

   bool application::initialize3()
   {
      return true;
   }

   // thread termination
   int32_t application::exit_instance() // default will 'delete this'
   {

      // avoid calling CloseHandle() on our own thread handle
      // during the thread destructor
      m_pthreadimpl->set_os_data(NULL);


      int32_t iRet = ::aura::application::exit_instance();


      return iRet;
   }
   

   ::thread * application::GetThread()
   {

      return ::get_thread();
      
   }
   

   void application::set_thread(::thread * pthread)
   {
      
      ::set_thread(pthread);
      
   }
   

   ///////////////////////////////////////////////////////////////////////////
   // application Initialization

   void application::SetCurrentHandles()
   {
      //ASSERT(this == afxCurrentWinApp);
      //if(afxCurrentAppName != NULL)
      // return;
      //ASSERT(afxCurrentAppName == NULL);


      // Note: there are a number of _tcsdup (aka _strdup) calls that are
      // made here for the exe path, help file path, etc.  In previous
      // versions of ca2 API, this primitive::memory was never freed.  In this and future
      // versions this primitive::memory is automatically freed during application's
      // destructor.  If you are freeing the primitive::memory yourself, you should
      // either remove the code or set the pointers to NULL after freeing
      // the primitive::memory.

      // get path of executable
      /*   char szBuff[_MAX_PATH];
      DWORD dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
      if( dwRet == 0 || dwRet == _MAX_PATH )
      throw user_exception();*/

      /*
      LPTSTR lpszExt = ::PathFindExtension(szBuff);
      ASSERT(lpszExt != NULL);
      if( lpszExt == NULL )
      throw user_exception();

      ASSERT(*lpszExt == '.');
      *lpszExt = 0;       // no suffix
      */

//      string strExeName;
      //string strTitle = System.load_string("System.title");
      // get the exe title from the full path name [no extension]
  //    strExeName = System.get_module_title();



      m_pimpl->set_os_data(::GetCurrentThread());


   }



   void application::get_time(struct timeval *p)
   {
#ifdef _WIN32
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      uint64_t tt;
      memcpy(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      p->tv_sec = (long)tt / 1000000;
      p->tv_usec = (long)tt % 1000000;
#else
      gettimeofday(p, NULL);
#endif
   }

   void application::set_env_var(const string & var,const string & value)
   {
#if (defined(SOLARIS8) || defined(SOLARIS))
      {
         static std::collection::map<string, char *> vmap;
         if (vmap.find(var) != vmap.end())
         {
            delete[] vmap[var];
         }
         vmap[var] = new char[var.get_length() + 1 + value.get_length() + 1];
         sprintf(vmap[var], "%s=%s", var, value);
         putenv( vmap[var] );
      }
#elif defined _WIN32
      {
         string slask = var + "=" + value;
         _putenv( (const char *)slask);
      }
#else
      setenv(var, value, 1);
#endif
   }

   uint32_t application::get_thread_id()
   {
      return ::GetCurrentThreadId();
   }



   bool application::set_main_init_data(::aura::main_init_data * pdata)
   {

      m_pmaininitdata = (::macos::main_init_data *) pdata;

      if(m_pmaininitdata != NULL && m_pimpl->is_system())
      {
         if(!win_init(m_pmaininitdata))
            return false;
      }

      return true;

   }

   bool application::win_init(main_init_data * pdata)
   {
      ASSERT(pdata->m_hPrevInstance == NULL);

      string strCmdLine          = pdata->m_strCommandLine;

      // handle critical errors and avoid Windows message boxes
      // xxx         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

      System.m_strCmdLine = strCmdLine;
      //pApp->SetCurrentHandles();
      SetCurrentHandles();

      __init_thread();

      return true;

   }

   bool application::update_module_paths()
   {
      string str;

      char * lpsz = str.GetBufferSetLength(1024);

      uint32_t size = 1024;

      if(_NSGetExecutablePath(lpsz, &size) == 0)
      {

         str.ReleaseBuffer();

      }
      else
      {

         lpsz = str.GetBufferSetLength(size);

         if(_NSGetExecutablePath(lpsz, &size) == 0)
         {

            str.ReleaseBuffer();

         }
         else
         {

            return false;

         }

      }

      System.m_strModuleFolder = ::dir::name(str);


      {

         char * pszCurDir = getcwd(NULL, 0);

         string strCurDir = pszCurDir;

         free(pszCurDir);

         if(file_exists_dup(::dir::path(strCurDir, "libcore.dylib")))
         {
            
            System.m_strCa2ModuleFolder = strCurDir;
            
         }
         else if(file_exists_dup(::dir::path(System.m_strModuleFolder, "libcore.dylib")))
         {
            
            System.m_strCa2ModuleFolder = System.m_strModuleFolder;
            
         }
         else
         {

            System.m_strCa2ModuleFolder = ::dir::name(::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libcore.dylib", "rfs")); // readable - normal file - non zero sized
            
         }

      }


      return true;

   }

   
   
    
    
    string application::draw2d_get_default_library_name()
    {
        
        return "draw2d_quartz2d";
        
    }
   string application::multimedia_audio_get_default_library_name()
   {
      
      return "audio_core_audio";
      
   }

   string application::multimedia_audio_mixer_get_default_library_name()
   {
      
      return "audio_mixer_core_audio";
   
   }
   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {
      
      return "music_midi_core_audio";
      
   }
   
   
   void application::ShowWaitCursor(bool bShow)
   {
      
      UNREFERENCED_PARAMETER(bShow);
      
   }

   
   
} // namespace macos





