/*
Copyright (ca) 2001 - 2002
Author: Konstantin Boukreev
E-mail: konstantin@mail.primorye.ru
Created: 25.12.2001 19:41:07
Version: 1.0.2

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.  Konstantin Boukreev makes no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.

*/

#include "framework.h"

#ifdef LINUX
#include <execinfo.h>
#include <cxxabi.h>
#define _BSD_SOURCE
#include <unistd.h>
#elif defined(APPLEOS)
#include <execinfo.h>
#endif


// The following is defined for x86 (XP and higher), x64 and IA64:
#define GET_CURRENT_CONTEXT(pc, contextFlags) \
   do { \
   memset(pc, 0, sizeof(CONTEXT)); \
   pc->ContextFlags = contextFlags; \
   RtlCaptureContext(pc); \
   } while(0);



#define USED_CONTEXT_FLAGS CONTEXT_FULL
#ifdef WINDOWSEX

#include <tlhelp32.h>

#pragma comment (lib, "dbghelp")

#endif

#ifdef VERIFY
#undef VERIFY
#endif // VERIFY

#ifdef DEBUG
#define VERIFY(x) _ASSERTE(x)
#else
#define VERIFY(x) (x)
#endif //DEBUG

#define WORK_AROUND_SRCLINE_BUG

#ifdef DEBUG
//#if 1
// #define SYM_ENGINE_TRACE_SPIN_COUNT
#endif //DEBUG

///////////////////////////////////////////////////////////////////////

HANDLE SymGetProcessHandle();
int_bool __stdcall My_ReadProcessMemory(HANDLE      hProcess,
DWORD64     qwBaseAddress,
PVOID       lpBuffer,
DWORD       nSize,
LPDWORD     lpNumberOfBytesRead
                                       );



HANDLE SymGetProcessHandle()
{
#ifdef WINDOWS
   if (is_windows_nt())
      //   if (0)
         return GetCurrentProcess();
   else
      return (HANDLE)GetCurrentProcessId();
#else
   return (HANDLE) (int_ptr) getpid();
#endif
}


//#ifdef AMD64

/*typedef
BOOL
(__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)(
_In_ HANDLE hProcess,
_In_ DWORD64 qwBaseAddress,
_Out_writes_bytes_(nSize) PVOID lpBuffer,
_In_ uint32_t nSize,
_Out_ LPDWORD lpNumberOfBytesRead
);*/


int_bool __stdcall My_ReadProcessMemory (
   HANDLE      hProcess,
   DWORD64     qwBaseAddress,
   PVOID       lpBuffer,
   DWORD       nSize,
   LPDWORD     lpNumberOfBytesRead
   )
{

   SIZE_T size = 0;
#if defined(METROWIN) || defined(LINUX) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)
   throw todo(get_thread_app());
#else
   if(!ReadProcessMemory(hProcess, (LPCVOID) qwBaseAddress, (LPVOID) lpBuffer, nSize, &size))
      return FALSE;
#endif
   *lpNumberOfBytesRead = (uint32_t) size;

   return TRUE;

}
/*
#else
int_bool __stdcall My_ReadProcessMemory (HANDLE, LPCVOID lpBaseAddress, LPVOID lpBuffer, uint32_t nSize, SIZE_T * lpNumberOfBytesRead)
{
return ReadProcessMemory(GetCurrentProcess(), lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead) != FALSE;
}
#endif
*/
namespace exception
{


   typedef int_bool (__stdcall *PReadProcessMemoryRoutine)(
      HANDLE      hProcess,
      DWORD64     qwBaseAddress,
      PVOID       lpBuffer,
      uint32_t       nSize,
      LPDWORD     lpNumberOfBytesRead,
      LPVOID      pUserData  // optional data, which was passed in "ShowCallstack"
      );

   // The following is used to pass the "userData"-Pointer to the user-provided readMemoryFunction
   // This has to be done due to a problem with the "hProcess"-parameter in x64...
   // Because this class is in no case multi-threading-enabled (because of the limitations
   // of dbghelp.dll) it is "safe" to use a static-variable

#ifdef WINDOWS

   static PReadProcessMemoryRoutine s_readMemoryFunction = NULL;
   static LPVOID s_readMemoryFunction_UserData = NULL;

#endif

   engine::engine(sp(::base::application) papp) :
      element(papp)
#ifdef WINDOWSEX
      ,m_bOk(false)
      ,m_pstackframe(NULL)
      ,m_iRef(0)
#endif
   {

      m_pmutex = new mutex(papp);

   }

   engine::~engine()
   {
#ifdef WINDOWSEX
      clear();
#endif
      //   if (m_bOk) guard::instance().clear();
      delete m_pmutex;
#ifdef WINDOWSEX

      delete m_pstackframe;
#endif
   }

#ifdef WINDOWSEX

   size_t engine::module(string & str)
   {
      if (!check())
         return 0;

      HANDLE hprocess = SymGetProcessHandle();
      HMODULE hmodule = (HMODULE)SymGetModuleBase64 (hprocess, m_uiAddress);
      if (!hmodule) return 0;
      return get_module_basename(hmodule, str);
   }
#endif

#ifdef WINDOWSEX

   size_t engine::symbol(string & str, DWORD64 * pdisplacement)
   {
      if (!check())
         return 0;

      BYTE symbol [ 512 ] ;
      PIMAGEHLP_SYMBOL64 pSym = (PIMAGEHLP_SYMBOL64)&symbol;
      memset(pSym, 0, sizeof(symbol)) ;
      pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64) ;
      pSym->MaxNameLength = sizeof(symbol) - sizeof(IMAGEHLP_SYMBOL64);

      HANDLE hprocess = SymGetProcessHandle();
      DWORD64 displacement = 0;
      int32_t r = SymGetSymFromAddr64(hprocess, m_uiAddress, &displacement, pSym);
      if (!r) return 0;
      if (pdisplacement)
         *pdisplacement = displacement;

      str = pSym->Name;
      str += "()";

      return str.get_length();
   }

#endif

#ifdef WINDOWSEX


   index engine::fileline (string & str, uint32_t * pline, uint32_t * pdisplacement)
   {

      if (!check())
         return 0;

      IMAGEHLP_LINE64 img_line;
      memset(&img_line, 0, sizeof(IMAGEHLP_LINE64));
      img_line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

      HANDLE hprocess = SymGetProcessHandle();
      DWORD displacement = 0;
      if (!get_line_from_address(hprocess, m_uiAddress, &displacement, &img_line))
         return 0;
      if (pdisplacement)
         *pdisplacement = displacement;
      if (pline)
         *pline = img_line.LineNumber;
      str = img_line.FileName;
      return str.get_length();
   }

#endif


#ifdef WINDOWSEX

   bool engine::stack_first (CONTEXT* pcontext)
   {

      if(!pcontext || IsBadReadPtr(pcontext, sizeof(CONTEXT)))
         return false;

      if(!check())
         return false;

      if(!m_pstackframe)
      {
         m_pstackframe = new STACKFRAME64;
         if (!m_pstackframe) return false;
      }

      memset(m_pstackframe, 0, sizeof(STACKFRAME64));

      //  s_readMemoryFunction = readMemoryFunction;
      //s_readMemoryFunction_UserData = pUserData;


#ifdef AMD64
      m_pstackframe->AddrPC.Offset       = pcontext->Rip;
      m_pstackframe->AddrPC.Mode         = AddrModeFlat;
      m_pstackframe->AddrStack.Offset    = pcontext->Rsp;
      m_pstackframe->AddrStack.Mode      = AddrModeFlat;
      m_pstackframe->AddrFrame.Offset    = pcontext->Rsp;
      m_pstackframe->AddrFrame.Mode      = AddrModeFlat;
#elif defined(X86)
      m_pstackframe->AddrPC.Offset       = pcontext->Eip;
      m_pstackframe->AddrPC.Mode         = AddrModeFlat;
      m_pstackframe->AddrStack.Offset    = pcontext->Esp;
      m_pstackframe->AddrStack.Mode      = AddrModeFlat;
      m_pstackframe->AddrFrame.Offset    = pcontext->Ebp;
      m_pstackframe->AddrFrame.Mode      = AddrModeFlat;
#else
      m_pstackframe->AddrPC.offset       = (uint32_t)pcontext->Fir;
      m_pstackframe->AddrPC.Mode         = AddrModeFlat;
      m_pstackframe->AddrReturn.offset   = (uint32_t)pcontext->IntRa;
      m_pstackframe->AddrReturn.Mode     = AddrModeFlat;
      m_pstackframe->AddrStack.offset    = (uint32_t)pcontext->IntSp;
      m_pstackframe->AddrStack.Mode      = AddrModeFlat;
      m_pstackframe->AddrFrame.offset    = (uint32_t)pcontext->IntFp;
      m_pstackframe->AddrFrame.Mode      = AddrModeFlat;
#endif

      m_pcontext = pcontext;
      return stack_next();
   }

#endif


#ifdef WINDOWSEX

   bool engine::stack_next()
   {
      if (!m_pstackframe || !m_pcontext)
      {
         _ASSERTE(0);
         return false;
      }

      if (!m_bOk)
      {
         _ASSERTE(0);
         return false;
      }

      SetLastError(0);
      HANDLE hprocess = SymGetProcessHandle();

      uint32_t dwType;

      bool bRetry;

#ifdef AMD64
      dwType = IMAGE_FILE_MACHINE_AMD64;
#else
      dwType = IMAGE_FILE_MACHINE_I386;
#endif

      bool r = StackWalk64(
         dwType,   // __in      uint32_t MachineType,
         hprocess,        // __in      HANDLE hProcess,
         get_current_thread(),         // __in      HANDLE hThread,
         m_pstackframe,                       // __inout   LP STACKFRAME64 StackFrame,
         m_pcontext,                  // __inout   PVOID ContextRecord,
         My_ReadProcessMemory,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
         //NULL,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
         SymFunctionTableAccess64,                      // __in_opt  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
         SymGetModuleBase64,                     // __in_opt  PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine,
         NULL                       // __in_opt  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
         ) != FALSE;
      /*#else
      bool r = StackWalk64 (
      ,
      hprocess,
      get_current_thread(),
      m_pstackframe,
      m_pcontext,
      My_ReadProcessMemory,
      SymFunctionTableAccess64,
      SymGetModuleBase64,
      0) != FALSE;
      #endif*/

      if (!r || !m_pstackframe->AddrFrame.Offset)
      {

         return false;

      }

      bRetry = false;

retry_get_base:

      // "Debugging Applications" John Robbins
      // Before I get too carried away and start calculating
      // everything, I need to double-check that the address returned
      // by StackWalk really exists. I've seen cases in which
      // StackWalk returns TRUE but the address doesn't belong to
      // a module in the process.

      DWORD64 dwModBase = SymGetModuleBase64 (hprocess, m_pstackframe->AddrPC.Offset);

      if (!dwModBase)
      {
         //::OutputDebugString("engine::stack_next :: StackWalk returned TRUE but the address doesn't belong to a module in the process.");

         if(bRetry)
         {

            m_bSkip = true;

            return false;

         }

         ::base::system::eengine().reset();

         bRetry = true;

         goto retry_get_base;

      }
      m_bSkip = false;
      address(m_pstackframe->AddrPC.Offset);
      return true;
   }

#endif






#ifdef WINDOWSEX


   bool engine::get_line_from_address (HANDLE hprocess, DWORD64 uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE64 * pline)
   {
#ifdef WORK_AROUND_SRCLINE_BUG
      // "Debugging Applications" John Robbins
      // The problem is that the symbol engine finds only those source
      // line addresses (after the first lookup) that fall exactly on
      // a zero displacement. I'll walk backward 100 bytes to
      // find the line and return the proper displacement.
      uint32_t dwDisplacement = 0 ;
      while (!SymGetLineFromAddr64 (hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
      {
         if (100 == ++dwDisplacement)
            return false;
      }

      // "Debugging Applications" John Robbins
      // I found the line, and the source line information is correct, so
      // change the displacement if I had to search backward to find the source line.
      if(dwDisplacement)
         *puiDisplacement = dwDisplacement;
      return true;
#else
      return 0 != SymGetLineFromAddr64 (hprocess, uiAddress, (uint32_t *) puiDisplacement, pline);
#endif
   }


#endif









#ifdef WINDOWSEX


   size_t engine::get_module_basename (HMODULE hmodule, string & str)
   {

      char filename[MAX_PATH];

      uint32_t r = GetModuleFileNameA(hmodule, filename, MAX_PATH);

      if(!r)
         return 0;

      str = filename;

      // find the last '\' mark.
      size_t iPos = str.reverse_find('\\');

      if(iPos >= 0)
      {

         str = str.substr(iPos + 1);

      }

      return str.get_length();

   }


#endif









#ifdef WINDOWSEX



   bool engine::check()
   {
      if (!m_bOk)
         m_bOk = init();
      return m_bOk;
   }



#endif






















#ifdef WINDOWSEX



   bool engine::load_modules()
   {

      HANDLE hprocess = SymGetProcessHandle();
      uint32_t  dwPid = GetCurrentProcessId();

      // enumerate modules
      if (is_windows_nt())
      {
         typedef bool (WINAPI *ENUMPROCESSMODULES)(HANDLE, HMODULE*, uint32_t, LPDWORD);

         HINSTANCE hInst = LoadLibrary("psapi.dll");
         if (hInst)
         {
            ENUMPROCESSMODULES fnEnumProcessModules =
               (ENUMPROCESSMODULES)GetProcAddress(hInst, "EnumProcessModules");
            DWORD cbNeeded = 0;
            if (fnEnumProcessModules &&
               fnEnumProcessModules(GetCurrentProcess(), 0, 0, &cbNeeded) &&
               cbNeeded)
            {
               HMODULE * pmod = (HMODULE *)alloca(cbNeeded);
               DWORD cb = cbNeeded;
               if (fnEnumProcessModules(GetCurrentProcess(), pmod, cb, &cbNeeded))
               {
                  m_iRef = 0;
                  for (uint32_t i = 0; i < cb / sizeof (HMODULE); ++i)
                  {
                     if (!load_module(hprocess, pmod[i]))
                     {
                        //   m_iRef = -1;
                        //   break;
//                        _ASSERTE(0);
                           m_iRef = -1;
                           break;
                     }
                  }
               }
            }
            else
            {
               _ASSERTE(0);
            }
            VERIFY(FreeLibrary(hInst));
         }
         else
         {
            _ASSERTE(0);
         }
      }
      else
      {
         typedef HANDLE (WINAPI *CREATESNAPSHOT)(uint32_t, uint32_t);
         typedef bool (WINAPI *MODULEWALK)(HANDLE, LPMODULEENTRY32);

         HMODULE hMod = GetModuleHandle("kernel32");
         CREATESNAPSHOT fnCreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(hMod, "CreateToolhelp32Snapshot");
         MODULEWALK fnModule32First = (MODULEWALK)GetProcAddress(hMod, "Module32First");
         MODULEWALK fnModule32Next  = (MODULEWALK)GetProcAddress(hMod, "Module32Next");

         if (fnCreateToolhelp32Snapshot &&
            fnModule32First &&
            fnModule32Next)
         {
            HANDLE hModSnap = fnCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
            if (hModSnap)
            {
               MODULEENTRY32 me32 = {0};
               me32.dwSize = sizeof(MODULEENTRY32);
               if (fnModule32First(hModSnap, &me32))
               {
                  m_iRef = 0;
                  do
                  {
                     if (!load_module(hprocess, me32.hModule))
                     {
                        //   m_iRef = -1;
                        //   break;
                     }
                  }
                  while(fnModule32Next(hModSnap, &me32));
               }
               VERIFY(CloseHandle(hModSnap));
            }
         }
      }

      if (m_iRef == -1)
      {
         VERIFY(SymCleanup(SymGetProcessHandle()));
      }

      return true;

   }

#endif
















#ifdef WINDOWSEX



   bool engine::init()
   {

      if(!::file_exists_dup("C:\\core\\exception_engine.txt"))
      {
         return false;
      }


      single_lock sl(m_pmutex, true);

      if (!m_iRef)
      {
         m_iRef = -1;

         HANDLE hprocess = SymGetProcessHandle();
         uint32_t  dwPid = GetCurrentProcessId();

         // initializes
         SymSetOptions(SymGetOptions()|SYMOPT_DEFERRED_LOADS|SYMOPT_LOAD_LINES);
         //   SymSetOptions (SYMOPT_UNDNAME|SYMOPT_LOAD_LINES);
         if (::SymInitialize(hprocess, 0, TRUE))
         {
            load_modules();
         }
         else
         {
            _ASSERTE(0);
         }
      }
      if (m_iRef == -1)
         return false;
      if (0 == m_iRef)
         ++m_iRef; // lock it once
      //   ++m_iRef;
      return true;
   }

#endif














#ifdef WINDOWSEX



   bool engine::fail() const
   {

      return m_iRef == -1;

   }

#endif





#ifdef WINDOWSEX


   void engine::clear()
   {

      single_lock sl(m_pmutex, true);

      if (m_iRef ==  0) return;
      if (m_iRef == -1) return;
      if (--m_iRef == 0)
      {
         VERIFY(SymCleanup(SymGetProcessHandle()));
      }
   }

#endif




   void engine::reset()
   {

      if(!::file_exists_dup("C:\\core\\exception_engine.txt"))
      {
         return;
      }

      single_lock sl(m_pmutex, true);

#ifdef WINDOWSEX
      clear();
      init();
#endif

   }

#ifdef WINDOWSEX


   bool engine::load_module(HANDLE hProcess, HMODULE hMod)
   {

      for(int32_t i = 0; i < m_ha.get_count(); i++)
      {
         if(m_ha[i] == hMod)
            return true;
      }

      m_ha.add(hMod);

      char filename[MAX_PATH];
      if (!GetModuleFileNameA(hMod, filename, MAX_PATH))
      {
         return false;
      }

      HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
      if (hFile == INVALID_HANDLE_VALUE)
      {
         return false;
      }

      // "Debugging Applications" John Robbins
      // For whatever reason, SymLoadModule can return zero, but it still loads the modules. Sheez.
      SetLastError(ERROR_SUCCESS);
      if (!SymLoadModule(hProcess, hFile, filename, 0, (uint32_t)hMod, 0) && ERROR_SUCCESS != GetLastError())
      {
         return false;
      }

      return true;
   }


#endif






#ifdef WINDOWSEX


   bool engine::stack_trace(string & str, CONTEXT * pcontext, uint_ptr uiSkip, const char * pszFormat)
   {

      if(!pszFormat)
         return false;

      m_uiAddress = 0;

      return stack_trace(str, pcontext, uiSkip, false, pszFormat);

   }


#endif















#ifdef WINDOWSEX


   /////////////////////////////////////////////
   // prints a current thread's stack

   struct current_context : CONTEXT
   {
      HANDLE   thread;
      volatile int32_t signal;
   };

   uint32_t WINAPI engine::stack_trace_ThreadProc(void * lpvoidParam)
   {


      current_context * pcontext = reinterpret_cast<current_context*>(lpvoidParam);

      __try
      {
         // Konstantin, 14.01.2002 17:21:32
         // must wait in spin lock until main thread will leave a ResumeThread (must return back to ::fontopus::user context)
         int32_t iInverseAgility = 26 + 33; // former iPatienceQuota
         int32_t iPatience = iInverseAgility;
         while(pcontext->signal && iPatience > 0)
         {
            if(!SwitchToThread())
               Sleep(10); // forces switch to another thread
            iPatience--;
         }

         //         char sz[200];
         //         sprintf(sz, "engine::stack_trace patience near down %u%%\n", iPatience * 100 / iInverseAgility);
         //         ::OutputDebugString(sz);

         if (-1 == SuspendThread(pcontext->thread))
         {
            pcontext->signal  = -1;
            __leave;
         }

         __try
         {
#ifdef AMD64
            GET_CURRENT_CONTEXT(pcontext, USED_CONTEXT_FLAGS);
#else
            pcontext->signal = GetThreadContext(pcontext->thread, pcontext) ? 1 : -1;
#endif
         }
         __finally
         {
            VERIFY(-1 != ResumeThread(pcontext->thread));
         }
      }
      __except(EXCEPTION_EXECUTE_HANDLER)
      {
         pcontext->signal  = -1;
      }
      return 0;
   }

#endif






#if defined(LINUX) || defined(METROWIN) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)
   bool engine::stack_trace(string & str, uint_ptr uiSkip, void * caller_address, const char * pszFormat)
#else
   bool engine::stack_trace(string & str, uint_ptr uiSkip, const char * pszFormat)
#endif
   {

#ifdef WINDOWSEX

      single_lock sl(m_pmutex, true);

      if(!pszFormat) return false;

      // attempts to get current thread's context

      current_context context;
      memset(&context, 0, sizeof(current_context));

      bool bOk = DuplicateHandle(GetCurrentProcess(), get_current_thread(), GetCurrentProcess(), &context.thread, 0, 0, DUPLICATE_SAME_ACCESS) != FALSE;

      _ASSERTE(bOk);
      _ASSERTE(context.thread);

      if (!bOk || !context.thread)
         return false;

      context.ContextFlags = CONTEXT_CONTROL; // CONTEXT_FULL;
      context.signal = -1;


      GET_CURRENT_CONTEXT((&context), USED_CONTEXT_FLAGS);

      /*uint32_t dwDummy;
      HANDLE hthreadWorker = create_thread(0, 0, &engine::stack_trace_ThreadProc, &context, CREATE_SUSPENDED, &dwDummy);
      _ASSERTE(hthreadWorker);

      if (hthreadWorker)
      {
      //VERIFY(SetThreadPriority(hthreadWorker, THREAD_PRIORITY_TIME_CRITICAL)); //  THREAD_PRIORITY_HIGHEST
      if (-1 != ResumeThread(hthreadWorker))
      {
      int32_t iInverseAgility = 26 + 33; // former iPatienceQuota
      int32_t iPatience = iInverseAgility;
      // Konstantin, 14.01.2002 17:21:32
      context.signal = 0;            // only now the worker thread can get this thread context
      while (!context.signal && iPatience > 0)
      {
      if(!SwitchToThread())
      Sleep(10); // forces switch to another thread
      iPatience--; // wait in spin
      }
      //char sz[200];
      //sprintf(sz, "engine::stack_trace patience near down %u%%\n", iPatience * 100 / iInverseAgility);
      //::OutputDebugString(sz);
      }
      else
      {
      VERIFY(TerminateThread(hthreadWorker, 0));
      }
      VERIFY(CloseHandle(hthreadWorker));
      }
      VERIFY(CloseHandle(context.thread));

      if (context.signal == -1)
      {
      _ASSERTE(0);
      return false;
      }*/
      // now it can print stack

      m_uiAddress = 0;

      stack_trace(str, &context, uiSkip, false, pszFormat);

      return true;
#elif defined(METROWIN) || defined(ANDROID) || defined(SOLARIS)

      return true;

#else


       void * array[1024];
       int32_t size = backtrace(array, 1024);

       if(caller_address != NULL)
       {

         array[1] = caller_address;

       }


       char ** messages = backtrace_symbols(array, size);

       // skip first stack frame (points here)
       for (int32_t i = 1; i < size && messages != NULL; ++i)
       {
           char *mangled_name = 0, *offset_begin = 0, *offset_end = 0;

           // find parantheses and +address offset surrounding mangled name
           for (char *p = messages[i]; *p; ++p)
           {
               if (*p == '(')
               {
                   mangled_name = p;
               }
               else if (*p == '+')
               {
                   offset_begin = p;
               }
               else if (*p == ')')
               {
                   offset_end = p;
                   break;
               }
           }

           // if the line could be processed, attempt to demangle the symbol
           if (mangled_name && offset_begin && offset_end &&
               mangled_name < offset_begin)
           {
               *mangled_name++ = '\0';
               *offset_begin++ = '\0';
               *offset_end++ = '\0';

#ifdef LINUX

               int32_t status;
               char * real_name = abi::__cxa_demangle(mangled_name, 0, 0, &status);

               // if demangling is successful, output the demangled function name
               if (status == 0)
               {
                   str += "[bt]: (" + ::str::from(i) + ") " + messages[i] + " : "
                             + real_name +  "+" +  offset_begin + offset_end
                             + "\n";

               }
               // otherwise, output the mangled function name
               else

#endif

               {
                   str += "[bt]: (" + ::str::from(i) + ") " + messages[i] + " : "
                             + mangled_name + "+" + offset_begin + offset_end
                             + "\n";
               }

#ifdef LINUX

               free(real_name);

#endif

           }
           // otherwise, print the whole line
           else
           {
               str += "[bt]: (" + ::str::from(i) + ") " +  messages[i]+  "\n";
           }
       }
       str += "\n";

      return true;

   #endif


   }





#ifdef WINDOWSEX


   bool engine::stack_trace(string & str, CONTEXT * pcontext, uint_ptr uiSkip, bool bSkip, const char * pszFormat)
   {

      if (!stack_first(pcontext))
         return false;

      do
      {
         if (!uiSkip && !bSkip)
         {

            str += get_frame(pszFormat);

         }
         else
         {
            --uiSkip;
         }
      }
      while(stack_next());

      return true;

   }

#endif

#ifdef WINDOWSEX


   string engine::get_frame(const char * pszFormat)
   {

      string str;

      string strBuf;
      string strFile;
      string strSymbol;


      uint32_t uiLineDisplacement = 0;
      uint32_t uiLineNumber = 0;
      DWORD64 uiSymbolDisplacement = 0;


      for (char * p = (char *)pszFormat; *p; ++p)
      {
         if (*p == '%')
         {
            ++p; // skips '%'
            char ca = *p;
            switch (ca)
            {
            case 'm':
               if(module(strBuf))
               {
                  str += strBuf;
               }
               else
               {
                  str += "?.?";
               }
               break;
            case 'f':
               if(strFile.is_empty())
               {
                  if(!fileline(strFile, &uiLineNumber, &uiLineDisplacement))
                  {
                     strFile = " ";
                  }
               }
               str += strFile;
               break;
            case 'l':
               if(strFile.is_empty())
               {
                  if(!fileline(strFile, &uiLineNumber, &uiLineDisplacement))
                  {
                     strFile = " ";
                  }
               }
               if (*(p + 1) == 'd')
               {
                  strBuf = i64toa_dup(uiLineDisplacement);
                  str += strBuf;
                  ++p;
               }
               else
               {
                  strBuf = i64toa_dup(uiLineNumber);
                  str += strBuf;
               }
               break;
            case 's':
               if(strSymbol.is_empty())
               {
                  if(!symbol(strSymbol, &uiSymbolDisplacement))
                  {
                     strSymbol = "?()";
                  }
               }
               if (*(p + 1) == 'd')
               {
                  strBuf = i64toa_dup(uiSymbolDisplacement);
                  str += strBuf;
                  ++p;
               }
               else
               {
                  str += strSymbol;
               }
               break;
            case '%':
               str += '%';
               break;
            default:
               str += '%';
               str += ca;
               break;
            }
         }
         else
         {
            str += *p;
         }

      }

      return str;

   }

#endif


} // namespace exception


