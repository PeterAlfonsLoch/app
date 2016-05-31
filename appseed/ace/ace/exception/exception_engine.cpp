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
#ifdef WINDOWSEX
#pragma warning(disable: 4091)
#include <ImageHlp.h>


#elif defined(LINUX)
#include <execinfo.h>
#include <cxxabi.h>
#include <unistd.h>
#elif defined(APPLEOS)
#include <execinfo.h>
#elif defined(ANDROID)
#include <unistd.h>
#include <unwind.h>
#include <dlfcn.h>
#include <cxxabi.h>
#endif
#ifdef __USE_BFD
bool resolve_addr_file_func_line(void *address, const char * * filename, const char ** func, unsigned & iLine);
void init_resolve_addr_file_func_line();
static int bfdinit = 0;
#endif
#ifdef ANDROID

struct BacktraceState
{
   void** current;
   void** end;
};

static _Unwind_Reason_Code unwindCallback(struct _Unwind_Context* context,void* arg)
{
   BacktraceState* state = static_cast<BacktraceState*>(arg);
   uintptr_t pc = _Unwind_GetIP(context);
   if(pc) {
      if(state->current == state->end) {
         return _URC_END_OF_STACK;
      }
      else {
         *state->current++ = reinterpret_cast<void*>(pc);
      }
   }
   return _URC_NO_REASON;
}

size_t captureBacktrace(void** buffer,size_t max)
{
   BacktraceState state ={buffer, buffer + max};
   _Unwind_Backtrace(unwindCallback,&state);

   return state.current - buffer;
}

string dumpBacktrace(void** buffer,size_t count)
{
   string str;
   for(size_t idx = 0; idx < count; ++idx) {
      const void* addr = buffer[idx];
      const char* symbol = "";

      Dl_info info;

      if(dladdr(addr,&info) && info.dli_sname)
      {

         symbol = info.dli_sname;

      }

      int status = 0;

      char * demangled = __cxxabiv1::__cxa_demangle(symbol, 0, 0, &status);

      //str += "  #";
      if (idx < 10)
      {
         str += "0";
      }
      str += ::str::from(idx);
      //str += ": 0x";
      //str += ::hex::upper_from((uint_ptr) addr);
      str += "  ";
      str += (NULL != demangled && 0 == status) ? demangled : symbol;
      str += "\n";

      if (demangled != NULL)
      {

         free(demangled);

      }

   }

   return str;

}


#endif



// The following is defined for x86 (XP and higher), x64 and IA64:
#define GET_CURRENT_CONTEXT(pc, contextFlags) \
   do { \
   memset(pc, 0, sizeof(CONTEXT)); \
   pc->ContextFlags = contextFlags; \
   RtlCaptureContext(pc); \
   } while(0);



#define FAST_STACK_TRACE 1



HANDLE SymGetProcessHandle()
{
#ifdef _WIN32
   return GetCurrentProcess();
#else
   return (HANDLE)(INT_PTR)getpid();
#endif
}

#ifdef WINDOWSEX

#if OSBIT == 64
size_t engine_symbol(char * sz,int n,DWORD64 * pdisplacement,DWORD64 dwAddress)
{

   BYTE symbol[4096];
   PIMAGEHLP_SYMBOL64 pSym = (PIMAGEHLP_SYMBOL64)&symbol;
   memset(pSym,0,sizeof(symbol)) ;
   pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64) ;
   pSym->MaxNameLength = sizeof(symbol) - sizeof(IMAGEHLP_SYMBOL64);

   HANDLE hprocess = SymGetProcessHandle();
   DWORD64 displacement = 0;
   int r = SymGetSymFromAddr64(hprocess,dwAddress,&displacement,pSym);
   if(!r) return 0;
   if(pdisplacement)
      *pdisplacement = displacement;

   strncpy_s(sz,n,pSym->Name,n);

   return strlen(sz);
}
#else
size_t engine_symbol(char * sz, int n, DWORD * pdisplacement, DWORD dwAddress)
{

   BYTE symbol[4096];
   PIMAGEHLP_SYMBOL pSym = (PIMAGEHLP_SYMBOL)&symbol;
   memset(pSym, 0, sizeof(symbol));
   pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
   pSym->MaxNameLength = sizeof(symbol) - sizeof(IMAGEHLP_SYMBOL);

   HANDLE hprocess = SymGetProcessHandle();
   DWORD displacement = 0;
   int r = SymGetSymFromAddr(hprocess, dwAddress, &displacement, pSym);
   if (!r) return 0;
   if (pdisplacement)
      *pdisplacement = displacement;

   strncpy_s(sz, n, pSym->Name, n);

   return strlen(sz);
}

#endif
#define USED_CONTEXT_FLAGS CONTEXT_FULL

//#include <tlhelp32.h>

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



HANDLE SymGetProcessHandle();


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

   engine::engine(::ace::application * papp) :
      object(papp)
#ifdef WINDOWSEX
      ,m_bOk(false)
      ,m_iRef(0)
#endif
   {
#ifdef WINDOWSEX
      m_iHa = 0;
      m_iMa = 0;
      ZERO(m_szaModule);
#else
#endif
   }

   engine::~engine()
   {
#ifdef WINDOWSEX
      clear();
#endif
      //   if (m_bOk) guard::instance().clear();
      //::ace::del(&m_mutex);


   }

#ifdef WINDOWSEX

   size_t engine::module(char * psz, int nCount)
   {
      if (!check())
         return 0;

      HANDLE hprocess = SymGetProcessHandle();
      HMODULE hmodule = (HMODULE)SymGetModuleBase64 (hprocess, address());
      if (!hmodule) return 0;
      return get_module_name(hmodule, psz, nCount);
   }
#endif

#ifdef WINDOWSEX

   #if OSBIT == 32

   size_t engine::symbol(char * psz, int nCount, DWORD * pdisplacement)
   {

      if (!check())
         return 0;

      engine_symbol(psz, nCount, pdisplacement, address());

      strcat(psz, "()");

      return strlen(psz);

   }
#else
   size_t engine::symbol(char * psz, int nCount, DWORD64 * pdisplacement)
   {

      if (!check())
         return 0;

      engine_symbol(psz, nCount, pdisplacement, address());

      strcat(psz, "()");

      return strlen(psz);

   }

#endif
#endif

#ifdef WINDOWSEX


   index engine::fileline (char * psz, int nCount, uint32_t * pline, uint32_t * pdisplacement)
   {

      if (!check())
         return 0;

#if OSBIT == 32
      IMAGEHLP_LINE img_line;
      memset(&img_line, 0, sizeof(IMAGEHLP_LINE));
      img_line.SizeOfStruct = sizeof(IMAGEHLP_LINE);
#else
      IMAGEHLP_LINE64 img_line;
      memset(&img_line, 0, sizeof(IMAGEHLP_LINE64));
      img_line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
#endif

      HANDLE hprocess = SymGetProcessHandle();
      DWORD displacement = 0;
      if (!get_line_from_address(hprocess, address(), &displacement, &img_line))
         return 0;
      if (pdisplacement)
         *pdisplacement = displacement;
      if (pline)
         *pline = img_line.LineNumber;
      strncpy(psz, img_line.FileName, nCount);
      return strlen(psz);
   }

#endif


#ifdef WINDOWSEX

   bool engine::stack_first(CONTEXT* pcontext)
   {
      m_iAddressRead = 0;
#if !FAST_STACK_TRACE
      if(!pcontext || IsBadReadPtr(pcontext, sizeof(CONTEXT)))
         return false;

      if(!check())
         return false;

      memset(&m_stackframe, 0, sizeof(STACKFRAME64));

      //  s_readMemoryFunction = readMemoryFunction;
      //s_readMemoryFunction_UserData = pUserData;


#ifdef AMD64
      m_stackframe.AddrPC.Offset       = pcontext->Rip;
      m_stackframe.AddrPC.Mode         = AddrModeFlat;
      m_stackframe.AddrStack.Offset    = pcontext->Rsp;
      m_stackframe.AddrStack.Mode      = AddrModeFlat;
      m_stackframe.AddrFrame.Offset    = pcontext->Rsp;
      m_stackframe.AddrFrame.Mode      = AddrModeFlat;
#elif defined(X86)
      m_stackframe.AddrPC.Offset       = pcontext->Eip;
      m_stackframe.AddrPC.Mode         = AddrModeFlat;
      m_stackframe.AddrStack.Offset    = pcontext->Esp;
      m_stackframe.AddrStack.Mode      = AddrModeFlat;
      m_stackframe.AddrFrame.Offset    = pcontext->Ebp;
      m_stackframe.AddrFrame.Mode      = AddrModeFlat;
#else
      m_stackframe.AddrPC.offset       = (uint32_t)pcontext->Fir;
      m_stackframe.AddrPC.Mode         = AddrModeFlat;
      m_stackframe.AddrReturn.offset   = (uint32_t)pcontext->IntRa;
      m_stackframe.AddrReturn.Mode     = AddrModeFlat;
      m_stackframe.AddrStack.offset    = (uint32_t)pcontext->IntSp;
      m_stackframe.AddrStack.Mode      = AddrModeFlat;
      m_stackframe.AddrFrame.offset    = (uint32_t)pcontext->IntFp;
      m_stackframe.AddrFrame.Mode      = AddrModeFlat;
#endif

      m_context = *pcontext;
#endif
      backtrace();
      return stack_next();
   }

#endif


#ifdef WINDOWSEX
#if OSBIT == 32
   void engine::backtrace(DWORD *pui, int &c)
#else
      void engine::backtrace(DWORD64 *pui, int &c)
#endif
   {
      synch_lock sl(&m_mutex);
#if FAST_STACK_TRACE

      UINT32 maxframes = c;
      ULONG BackTraceHash;
      c = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID*>(pui), &BackTraceHash);

#endif
   }
   void engine::backtrace()
   {

#if FAST_STACK_TRACE
      UINT32 maxframes = sizeof(m_uia) / sizeof(m_uia[0]);
      ULONG BackTraceHash;
      m_iAddressWrite = RtlCaptureStackBackTrace(0, maxframes, reinterpret_cast<PVOID*>(&m_uia), &BackTraceHash);
#else
      m_iAddressWrite = 0;
   if (!m_bOk)
   {
      _ASSERTE(0);
      return;
   }


   while (true)
   {

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
         &m_stackframe,                       // __inout   LP STACKFRAME64 StackFrame,
         &m_context,                  // __inout   PVOID ContextRecord,
         My_ReadProcessMemory,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
                                                   //NULL,                     // __in_opt  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
         SymFunctionTableAccess64,                      // __in_opt  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
         SymGetModuleBase64,                     // __in_opt  PGET_MODULE_AXIS_ROUTINE64 GetModuleBaseRoutine,
         NULL                       // __in_opt  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
         ) != FALSE;
      /*#else
      bool r = StackWalk64 (
      ,
      hprocess,
      get_current_thread(),
      &m_stackframe,
      m_pcontext,
      My_ReadProcessMemory,
      SymFunctionTableAccess64,
      SymGetModuleBase64,
      0) != FALSE;
      #endif*/

      if (!r || !m_stackframe.AddrFrame.Offset)
      {

         return;

      }

      bRetry = false;

   retry_get_base:

      // "Debugging Applications" John Robbins
      // Before I get too carried away and start calculating
      // everything, I need to double-check that the address returned
      // by StackWalk really exists. I've seen cases in which
      // StackWalk returns TRUE but the address doesn't belong to
      // a module in the process.

      DWORD64 dwModBase = SymGetModuleBase64(hprocess, m_stackframe.AddrPC.Offset);

      if (!dwModBase)
      {
         //::OutputDebugString("engine::stack_next :: StackWalk returned TRUE but the address doesn't belong to a module in the process.");
         return;
         if (bRetry)
         {

            m_bSkip = true;

            return;

         }

         System.eengine().reset();

         bRetry = true;

         goto retry_get_base;

      }
      m_bSkip = false;
      address(m_stackframe.AddrPC.Offset);

   }

#endif
   }

   bool engine::stack_next()
   {
      if (m_iAddressRead >= m_iAddressWrite)
         return false;
      m_iAddressRead++;
      return true;
   }

#endif






#ifdef WINDOWSEX

#if OSBIT == 32
   bool engine::get_line_from_address (HANDLE hprocess, DWORD uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE * pline)
   {
#ifdef WORK_AROUND_SRCLINE_BUG
      // "Debugging Applications" John Robbins
      // The problem is that the symbol engine finds only those source
      // line addresses (after the first lookup) that fall exactly on
      // a zero displacement. I'll walk backward 100 bytes to
      // find the line and return the proper displacement.
      uint32_t dwDisplacement = 0 ;
      while (!SymGetLineFromAddr (hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
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
#else
   bool engine::get_line_from_address(HANDLE hprocess, DWORD64 uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE64 * pline)
   {
#ifdef WORK_AROUND_SRCLINE_BUG
      // "Debugging Applications" John Robbins
      // The problem is that the symbol engine finds only those source
      // line addresses (after the first lookup) that fall exactly on
      // a zero displacement. I'll walk backward 100 bytes to
      // find the line and return the proper displacement.
      uint32_t dwDisplacement = 0;
      while (!SymGetLineFromAddr64(hprocess, uiAddress - dwDisplacement, puiDisplacement, pline))
      {
         if (100 == ++dwDisplacement)
            return false;
      }

      // "Debugging Applications" John Robbins
      // I found the line, and the source line information is correct, so
      // change the displacement if I had to search backward to find the source line.
      if (dwDisplacement)
         *puiDisplacement = dwDisplacement;
      return true;
#else
      return 0 != SymGetLineFromAddr64(hprocess, uiAddress, (uint32_t *)puiDisplacement, pline);
#endif
   }
#endif

#endif









#ifdef WINDOWSEX


   size_t engine::get_module_name (HMODULE hmodule, char * psz, int nCount)
   {

      for (int32_t i = 0; i < m_iMa; i++)
      {
         if (m_ma[i] == hmodule)
         {
            if (m_szaModule[i] == NULL)
               return 0;
            strncpy(psz, m_szaModule[i], nCount);
            return strlen(psz);

         }
      }

      char filename[MAX_PATH];
      if (!GetModuleFileNameA(hmodule, filename, MAX_PATH))
      {
         m_ma[m_iMa] = hmodule;
         m_szaModule[m_iMa++] = NULL;

         return 0;
      }

      m_ma[m_iMa] = hmodule;
      m_szaModule[m_iMa] = strdup(filename);
      strncpy(psz, m_szaModule[m_iMa++], nCount);
      //uint32_t r = GetModuleFileNameA(hmodule, psz, nCount);

      //if(!r)
        // return 0;



      // find the last '\' mark.
      //char * p = strrchr(psz, '\\');

      //if(p != NULL)
      //{

      //   *(p + 1) = '\0';

      //}

      return strlen(psz);

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

#include <malloc.h>

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

      //if(!::file_exists_dup("C:\\core\\exception_engine.txt"))
      //{
      //   return false;
      //}


      single_lock sl(&m_mutex, true);

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

      single_lock sl(&m_mutex, true);

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

      //if(!::file_exists_dup("C:\\core\\exception_engine.txt"))
      //{
      //   return;
      //}

      single_lock sl(&m_mutex, true);

#ifdef WINDOWSEX
      clear();
      init();
#endif

   }

#ifdef WINDOWSEX


   bool engine::load_module(HANDLE hProcess, HMODULE hMod)
   {

      for(int32_t i = 0; i < m_iHa; i++)
      {
         if(m_ha[i] == hMod)
            return true;
      }

      m_ha[m_iHa++] = hMod;

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
      if (!SymLoadModule(hProcess, hFile, filename, 0, (uint_ptr)hMod, 0) && ERROR_SUCCESS != GetLastError())
      {
         return false;
      }

      return true;
   }


#endif






#ifdef WINDOWSEX


   bool engine::stack_trace(CONTEXT * pcontext, uint_ptr uiSkip, const char * pszFormat)
   {

      if(!pszFormat)
         return false;

      return stack_trace(pcontext, uiSkip, false, pszFormat);

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
   char * engine::stack_trace(uint_ptr uiSkip, void * caller_address, const char * pszFormat)
#else
   bool engine::stack_trace(uint_ptr uiSkip, const char * pszFormat)
#endif
   {



      single_lock sl(&m_mutex, true);
      *_strS = '\0';

#ifdef WINDOWSEX

      if (!pszFormat) return false;

      // attempts to get current thread's context

#if FAST_STACK_TRACE
      stack_trace(NULL, uiSkip, false, pszFormat);

#else

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

      stack_trace(&context, uiSkip, false, pszFormat);


#endif

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



      return true;
#elif defined(METROWIN) || defined(SOLARIS)

      return _strS;

#elif defined(ANDROID)

      const size_t max = 30;

      void* buffer[max];

      int iSkip = MIN(uiSkip, max - 1);

      if (iSkip == max - 1)
      {

         return "";

      }

      int iCount = captureBacktrace(buffer, max);

      strncpy(_strS, dumpBacktrace(&buffer[iSkip], iCount - iSkip), sizeof(_strS));

      return _strS;

#else

       void * array[64];

       int32_t size = ::backtrace(array, 64);

       if(caller_address != NULL)
       {

         array[1] = caller_address;

       }

       return stack_trace(array, size);


   #endif



   }





#ifdef WINDOWSEX


   bool engine::stack_trace(CONTEXT * pcontext, uint_ptr uiSkip, bool bSkip, const char * pszFormat)
   {
      *_strS = '\0';
      if (!stack_first(pcontext))
         return false;

      do
      {
         if (!uiSkip && !bSkip)
         {

            strcat(_strS, get_frame(pszFormat));

         }
         else
         {
            --uiSkip;
         }
      }
      while(stack_next());

      return true;

   }

#if OSBIT == 32
   char * engine::stack_trace(DWORD * pui, int c, const char * pszFormat)
#else
   char * engine::stack_trace(DWORD64 * pui, int c, const char * pszFormat)
#endif
   {
      synch_lock sl(&m_mutex);
      *_strS = '\0';

      memcpy(m_uia, pui, MIN(c*sizeof(*pui), sizeof(m_uia)));

      m_iAddressWrite = c;
      m_iAddressRead = 0;
      char * psz;
      do
      {
         psz = get_frame(pszFormat);
         if (psz == NULL)
            break;
         strcat(_strS, psz);
      } while (stack_next());

      return _strS;
   }

#endif

#if defined(WINDOWSEX) 


   char * engine::get_frame(const char * pszFormat)
   {


      *_str = '\0';
      *_strBuf = '\0';
      *_strFile = '\0';
      *_strSymbol = '\0';

      uint32_t uiLineDisplacement = 0;
      uint32_t uiLineNumber = 0;
#if OSBIT == 32
      DWORD uiSymbolDisplacement = 0;
#else
      DWORD64 uiSymbolDisplacement = 0;
#endif

      char sz[2];
      sz[1] = '\0';
      for (char * p = (char *)pszFormat; *p; ++p)
      {
         if (*p == '%')
         {
            ++p; // skips '%'
            char ca = *p;
            switch (ca)
            {
            case 'm':
               if(module(_strBuf, sizeof(_strBuf)))
               {
                  strcat(_str, _strBuf);
               }
               else
               {
                  strcat(_str, "?.?");
               }
               break;
            case 'f':
               if(*_strFile == '\0')
               {
                  if(!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
                  {
                     strcpy(_strFile, " ");
                  }
               }
               strcat(_str, _strFile);
               break;
            case 'l':
               if (*_strFile == '\0')
               {
                  if(!fileline(_strFile, sizeof(_strFile), &uiLineNumber, &uiLineDisplacement))
                  {
                     strcpy(_strFile, " ");
                  }
               }
               if (*(p + 1) == 'd')
               {
                  ultoa_dup(_strBuf, uiLineDisplacement, 10);
                  strcat(_str, _strBuf);
                  ++p;
               }
               else
               {
                  ultoa_dup(_strBuf, uiLineNumber, 10);
                  strcat(_str, _strBuf);
               }
               break;
            case 's':
               if(*_strSymbol == '\0')
               {
                  if(!symbol(_strSymbol, sizeof(_strSymbol), &uiSymbolDisplacement))
                  {
                     strcpy(_strSymbol, "?()");
                  }
               }
               if (*(p + 1) == 'd')
               {
                  ultoa_dup(_strBuf, uiSymbolDisplacement, 10);
                  strcat(_str, _strBuf);
                  ++p;
               }
               else
               {
                  if (strncmp(_strSymbol, "dispatch::AddMessageHandler", strlen("dispatch::AddMessageHandler")) == 0)
                  {
//                     strcpy(_strS, "\n");
  //                   strcat(_strS, _strSymbol);
    //                 strcat(_strS, "\n");
      //               return NULL;
                     strcat(_strS, " * * * ");
                  }
                  strcat(_str, _strSymbol);
               }
               break;
            case '%':
               strcat(_str, "%");
               break;
            default:
               strcat(_str, "%");
               sz[0] = ca;
               strcat(_str, sz);
               break;
            }
         }
         else
         {
            sz[0] = *p;
            strcat(_str, sz);
         }

      }

      return _str;

   }
    
#elif defined(MACOS)

   void engine::backtrace(void *pui, int &c)
   {

      synch_lock sl(&m_mutex);

      UINT32 maxframes = c;

      c = ::backtrace(&pui, maxframes);

   }

   char * engine::stack_trace(void * pui, int c, const char * pszFormat)
   {

      char ** messages = backtrace_symbols(&pui, c);

      char szN[24];

      *_strS = '\0';

      char syscom[1024];

      const char * func;
      const char * file;
      unsigned iLine;

      for (int32_t i = 1; i < c && messages != NULL; ++i)
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

         if (mangled_name && offset_begin && offset_end && mangled_name < offset_begin)
         {

            *mangled_name++ = '\0';
            *offset_begin++ = '\0';
            *offset_end++ = '\0';

            int32_t status;

//            char * real_name = abi::__cxa_demangle(mangled_name, 0, 0, &status);
             string real_name = demangle(mangled_name);

            strcat(_strS, "[bt]: (");
            ultoa_dup(szN, i, 10);
            strcat(_strS, szN);
            strcat(_strS, ") ");
            strcat(_strS, messages[i]);
            strcat(_strS, " : ");

            if (status == 0)
            {

               strcat(_strS, real_name);

            }
            else
            {

               strcat(_strS, mangled_name);

            }

            strcat(_strS, "+");
            strcat(_strS, offset_begin);
            strcat(_strS, offset_end);
            strcat(_strS,"\n");

//            if(real_name != NULL)
//            {
//
//               free(real_name);
//
//            }

         }
         else
         {

            strcat(_strS, "[bt]: (");
            ultoa_dup(szN, i, 10);
            strcat(_strS, szN);
            strcat(_strS, ") ");
            strcat(_strS, messages[i]);

         }

         strcat(_strS,"\n");

      }

      return _strS;

   }


#elif defined(LINUX) || defined(MACOS) 
    
    void engine::backtrace(void *pui, int &c)
    {
        
        synch_lock sl(&m_mutex);
        
        UINT32 maxframes = c;
        
        c = ::backtrace(pui, maxframes);
        
    }
    
    char * engine::stack_trace(void * pui, int c, const char * pszFormat)
    {
        
        char ** messages = backtrace_symbols(pui, c);
        
        char szN[24];
        
        *_strS = '\0';
        
        char syscom[1024];
        
        const char * func;
        const char * file;
        unsigned iLine;
        
        for (int32_t i = 1; i < c && messages != NULL; ++i)
        {
#ifdef __USE_BFD
            
            if(resolve_addr_file_func_line(((void **)pui)[i], &file, &func, iLine))
            {
                
                
                strcat(_strS, file);
                strcat(_strS, ":");
                ultoa_dup(szN, iLine, 10);
                strcat(_strS, szN);
                strcat(_strS, ":1: warning: ");
                
            }
#endif // __USE_BFD
            
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
            
            if (mangled_name && offset_begin && offset_end && mangled_name < offset_begin)
            {
                
                *mangled_name++ = '\0';
                *offset_begin++ = '\0';
                *offset_end++ = '\0';
                
                int32_t status;
                
                char * real_name = abi::__cxa_demangle(mangled_name, 0, 0, &status);
                
                strcat(_strS, "[bt]: (");
                ultoa_dup(szN, i, 10);
                strcat(_strS, szN);
                strcat(_strS, ") ");
                strcat(_strS, messages[i]);
                strcat(_strS, " : ");
                
                if (status == 0)
                {
                    
                    strcat(_strS, real_name);
                    
                }
                else
                {
                    
                    strcat(_strS, mangled_name);
                    
                }
                
                strcat(_strS, "+");
                strcat(_strS, offset_begin);
                strcat(_strS, offset_end);
                strcat(_strS,"\n");
                
                if(real_name != NULL)
                {
                    
                    free(real_name);
                    
                }
                
            }
            else
            {
                
                strcat(_strS, "[bt]: (");
                ultoa_dup(szN, i, 10);
                strcat(_strS, szN);
                strcat(_strS, ") ");
                strcat(_strS, messages[i]);
                
            }
            
            strcat(_strS,"\n");
            
        }
        
        return _strS;
        
    }
    
    
#endif


} // namespace exception

#ifdef __USE_BFD

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include <execinfo.h>
#include <signal.h>
#include <bfd.h>
#include <unistd.h>

/* globals retained across calls to resolve. */
static const char * moda[]={"/ca2/stage/x86/libace.so", "/ca2/stage/x86/libbase.so", "/ca2/stage/x86/libcore.so", NULL};
static bfd* abfda[64];
static asymbol **symsa[64];
static asection *texta[64];
static int bfdcount = 0;

int free_resolve_addr_file_func_line()
{

   int i = 0;

   while(i < 64)
   {

      if(abfda[i] == NULL)
      {

         return i;

      }

      i++;

   }

   return -1;

}

bool prep_resolve_addr_file_func_line(const char * f)
{

   int i = free_resolve_addr_file_func_line();

   if(i < 0)
   {

      return false;

   }

   bfd* & abfd = abfda[i];

   asymbol ** & syms = symsa[i];

   asection * & text = texta[i];

   abfd = bfd_openr(f, 0);

   if (!abfd)
   {

      perror("bfd_openr failed: ");

      return false;

   }

   /* oddly, this is required for it to work... */
   bfd_check_format(abfd,bfd_object);

   unsigned storage_needed = bfd_get_symtab_upper_bound(abfd);

   syms = (asymbol **) malloc(storage_needed);

   unsigned cSymbols = bfd_canonicalize_symtab(abfd, syms);

   text = bfd_get_section_by_name(abfd, ".text");

   return true;

}


void init_resolve_addr_file_func_line()
{

   if(bfdinit)
      return;

   bfdinit = 1;

   ZERO(abfda);

   ZERO(symsa);

 	ZERO(texta)

   bfd_init();

   char ename[1024];

   int l = readlink("/proc/self/exe",ename,sizeof(ename));

   if (l == -1)
   {

      perror("failed to find executable\n");

      return false;

   }

   ename[l] = 0;

   prep_resolve_addr_file_func_line(ename);

   const char ** p = (const char **) moda;

   while(*p)
   {

      if(prep_resolve_addr_file_func_line(*p))
      {
         bfdcount++;

      }

      p++;

   }

}

bool resolve_addr_file_func_line1(bfd* abfd, asymbol **syms, asection *text, void *address, const char * * filename, const char ** func, unsigned & iLine)
{
    long offset = ((long)address) - text->vma;
    if (offset > 0) {
         *filename = NULL;
    *func = NULL;

        if (bfd_find_nearest_line(abfd, text, syms, offset, filename, func, &iLine) && *filename)
            return true;
            return false;
    }
    return false;
}


bool resolve_addr_file_func_line(void *address, const char * * filename, const char ** func, unsigned & iLine)
{
   int i;
   while(i < bfdcount)
   {

      if(resolve_addr_file_func_line1(abfda[i], symsa[i], texta[i],address, filename, func, iLine))
         return true;

      i++;

   }
    return false;
}


#endif
