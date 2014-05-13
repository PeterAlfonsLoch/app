#include "framework.h"



___IOS_STATE gen_MacState;




/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module
extern int32_t CLASS_DECL_BASE __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);


/////////////////////////////////////////////////////////////////////////////
// initialize cast state such that it points to this module's core state

CLASS_DECL_BASE bool __initialize(bool bDLL, DWORD dwVersion)
{
   __MODULE_STATE* pModuleState = __get_module_state();
   pModuleState->m_bDLL = (BYTE)bDLL;
   // xxx   ASSERT(dwVersion <= _MFC_VER);
   // xxx   UNUSED(dwVersion);  // not used in release build
   pModuleState->m_dwVersion = dwVersion;
#ifdef _MBCS
   // set correct multi-byte code-page for Win32 apps
   if (!bDLL)
      _setmbcp(_MB_CP_ANSI);
#endif //_MBCS
   return TRUE;
}

// force initialization early
//#pragma warning(disable: 4074)
//#pragma init_seg(lib)


//char gen_InitAppState = (char)(__initialize(FALSE, _MFC_VER));
char gen_InitAppState = (char)(__initialize(FALSE, 1));




void CLASS_DECL_BASE __ios_term()
{

}


CLASS_DECL_BASE __MODULE_STATE * __set_module_state(__MODULE_STATE* pNewState)
{
   ___THREAD_STATE* pState = gen_ThreadState;
   ASSERT(pState);
   if(pState)
   {
      __MODULE_STATE* pPrevState = pState->m_pModuleState;
      pState->m_pModuleState = pNewState;
      return pPrevState;
   }
   else
   {
      return NULL;
   }
}

__MAINTAIN_STATE::~__MAINTAIN_STATE()
{
   ___THREAD_STATE* pState = gen_ThreadState;
   ASSERT(pState);
   if(pState)
   {
      pState->m_pModuleState = m_pPrevModuleState;
   }
}

__MAINTAIN_STATE2::__MAINTAIN_STATE2(__MODULE_STATE* pNewState)
{
   m_pThreadState = gen_ThreadState;
   ASSERT(m_pThreadState);
   if(m_pThreadState)
   {
      m_pPrevModuleState = m_pThreadState->m_pModuleState;
      m_pThreadState->m_pModuleState = pNewState;
   }
   else
   {
      // This is a very bad state; we have no good way to report the error at this moment
      // since exceptions from here are not expected
      m_pPrevModuleState=NULL;
      m_pThreadState=NULL;
   }
   
   /*   if (__gen_get_ambient_act_ctx() &&
    pNewState->m_hActCtx != INVALID_HANDLE_VALUE)
    {
    m_bValidActCtxCookie = __activate_act_ctx(pNewState->m_hActCtx, &m_ulActCtxCookie);
    }
    else
    {
    m_bValidActCtxCookie = FALSE;
    }*/
}

/////////////////////////////////////////////////////////////////////////////
// ___THREAD_STATE implementation

___THREAD_STATE::___THREAD_STATE()
{
#ifdef DEBUG
   m_nDisablePumpCount = 0;
#endif
   m_msgCur.message = WM_NULL;
   m_nMsgLast = WM_NULL;
   //System.get_cursor_pos(&(m_ptCursorLast));
   m_ptCursorLast = point(0,0);
   m_pSafetyPoolBuffer = NULL;
   m_pWndPark = NULL;
   m_hWndInit = NULL;
   m_pCurrentWinThread = NULL;
   m_pWndInit = NULL;
   m_pModuleState = NULL;
}

___THREAD_STATE::~___THREAD_STATE()
{
   // unhook windows hooks
   // xxx   if (m_hHookOldMsgFilter != NULL)
   // xxx       ::UnhookWindowsHookEx(m_hHookOldMsgFilter);
   // xxx    if (m_hHookOldCbtFilter != NULL)
   // xxx       ::UnhookWindowsHookEx(m_hHookOldCbtFilter);
   
   // free safety pool buffer
   if (m_pSafetyPoolBuffer != NULL)
      free(m_pSafetyPoolBuffer);
   
   // parking ::window must have already been cleaned up by now!
   ASSERT(m_pWndPark == NULL);
   
   
}


void CLASS_DECL_BASE __node_init_thread_state()
{
   
   gen_ThreadState = new ___THREAD_STATE;
   
}

void CLASS_DECL_BASE __node_term_thread_state()
{
   
   delete gen_ThreadState;
   
   gen_ThreadState = NULL;
   
}


CLASS_DECL_BASE ___THREAD_STATE * __get_thread_state()
{
   
   return gen_ThreadState;
   
}


namespace ios
{
   
   CLASS_DECL_BASE ::thread_state * __get_thread_state()
   {
      ___THREAD_STATE *pState =gen_ThreadState;
      ENSURE(pState != NULL);
      return pState;
   }
   
   
} // namespace ios


thread_pointer < ___THREAD_STATE >  gen_ThreadState;


__MODULE_STATE::__MODULE_STATE(bool bDLL, DWORD dwVersion, bool bSystem) //:
//   m_mutexRegClassList(NULL)
{
   m_pmapHWND              = NULL;
   //   m_pmapHDC               = NULL;
   //   m_pmapHGDIOBJ           = NULL;
   m_pmapHMENU             = NULL;
   m_pstrUnregisterList    = NULL;
   /* xxx xxx xxx
    m_classList.Construct(offsetof(::ca2::type_info, m_pNextClass)); */
   
   m_fRegisteredClasses = 0;
   m_bDLL = (BYTE)bDLL;
   //   m_pfn_window_procedure = pfn_window_procedure;
   m_dwVersion = dwVersion;
   m_bSystem = (BYTE)bSystem;
   //   bool bEnable = TRUE;
   try
   {
      //Preallocate the registered classes string, but CRT primitive::memory leak report is
      //called before the string frees primitive::memory, so need to disable tracking.
      //bEnable = __enable_memory_tracking(FALSE);
      //m_pstrUnregisterList->Preallocate(4096);
      //__enable_memory_tracking(bEnable);
   }
   catch(memory_exception * pe)
   {
      //__enable_memory_tracking(bEnable);
      pe->Delete();
   }
   
   // cast starts out in "::fontopus::user control"
   m_bUserCtrl = TRUE;
   
   
   
   //bEnable = __enable_memory_tracking(FALSE);
   //Fusion: allocate dll wrappers array.
   m_pDllIsolationWrappers = NULL;
   //__enable_memory_tracking(bEnable);
   m_bSetAmbientActCtx = TRUE;
   m_hActCtx = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Activation Context API wrappers

#define __ACTCTX_API_INIT_PROCPTR(hKernel,name) \
pfn##name = (PFN_##name) GetProcAddress(hKernel, #name)\


/////////////////////////////////////////////////////////////////////////////
// Global function pointers for Context (WinSxS/Manifest) API, to be init during ca2 API global init.
#define __ACTCTX_API_PTR_DEFINE(name, type, params) \
typedef type (WINAPI* PFN_##name)params; \
PFN_##name pfn##name = NULL;

/*
 __ACTCTX_API_PTR_DEFINE(CreateActCtxW, HANDLE, (PCACTCTXW));
 __ACTCTX_API_PTR_DEFINE(ReleaseActCtx, void, (HANDLE));
 __ACTCTX_API_PTR_DEFINE(ActivateActCtx, bool, (HANDLE, ulong_ptr*));
 __ACTCTX_API_PTR_DEFINE(DeactivateActCtx, bool, (DWORD, ulong_ptr));
 
 __STATIC void CLASS_DECL_BASE __init_context_api()
 {
 static HMODULE hKernel = NULL;
 if (hKernel == NULL)
 {
 hKernel = GetModuleHandle("KERNEL32");
 ENSURE(hKernel != NULL);
 __ACTCTX_API_INIT_PROCPTR(hKernel,CreateActCtxW);
 __ACTCTX_API_INIT_PROCPTR(hKernel,ReleaseActCtx);
 __ACTCTX_API_INIT_PROCPTR(hKernel,ActivateActCtx);
 __ACTCTX_API_INIT_PROCPTR(hKernel,DeactivateActCtx);
 }
 }
 
 #if (_WIN32_WINNT >= 0x0500) || (_WIN32_FUSION >= 0x0100)
 HANDLE CLASS_DECL_BASE __create_act_ctx_w(PCACTCTXW pActCtx)
 {
 HANDLE hCtx = pfnCreateActCtxW != 0 ? pfnCreateActCtxW(pActCtx) : INVALID_HANDLE_VALUE;
 return hCtx;
 }
 #else
 HANDLE CLASS_DECL_BASE __create_act_ctx_w(void *pActCtx)
 {
 HANDLE hCtx = pfnCreateActCtxW != 0 ? pfnCreateActCtxW(pActCtx) : INVALID_HANDLE_VALUE;
 return hCtx;
 }
 #endif
 
 void CLASS_DECL_BASE __release_act_ctx(HANDLE hActCtx)
 {
 if (pfnReleaseActCtx != 0)
 {
 pfnReleaseActCtx(hActCtx);
 }
 }
 
 CLASS_DECL_BASE bool __activate_act_ctx(HANDLE hActCtx, ulong_ptr *lpCookie)
 {
 bool rc = pfnActivateActCtx != 0 ? pfnActivateActCtx(hActCtx, lpCookie) : FALSE;
 return rc;
 }
 
 CLASS_DECL_BASE bool __deactivate_act_ctx(DWORD dwFlags, ulong_ptr ulCookie)
 {
 bool rc = pfnDeactivateActCtx != 0 ? pfnDeactivateActCtx(dwFlags, ulCookie) : FALSE;
 return rc;
 }
 
 */
void __MODULE_STATE::CreateActivationContext()
{
   /*__init_context_api();
    HMODULE hModule = m_hCurrentInstanceHandle;
    
    WCHAR rgchFullModulePath[MAX_PATH + 2];
    rgchFullModulePath[_countof(rgchFullModulePath) - 1] = 0;
    rgchFullModulePath[_countof(rgchFullModulePath) - 2] = 0;
    DWORD dw = GetModuleFileNameW(hModule, rgchFullModulePath, _countof(rgchFullModulePath)-1);
    if (dw == 0)
    {
    return;
    }
    if (rgchFullModulePath[_countof(rgchFullModulePath) - 2] != 0)
    {
    SetLastError(ERROR_BUFFER_OVERFLOW);
    return;
    }
    //First try ID 2 and then ID 1 - this is to consider also a.dll.manifest file
    //for dlls, which ID 2 ignores.
    ACTCTXW actCtx;
    actCtx.cbSize = sizeof(actCtx);
    actCtx.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID | ACTCTX_FLAG_HMODULE_VALID;
    actCtx.lpSource = rgchFullModulePath;
    actCtx.lpResourceName =  MAKEINTRESOURCEW(ISOLATIONAWARE_MANIFEST_RESOURCE_ID);
    actCtx.hModule = hModule;
    m_hActCtx = __create_act_ctx_w(&actCtx);
    if (m_hActCtx == INVALID_HANDLE_VALUE)
    {
    actCtx.lpResourceName =  MAKEINTRESOURCEW(ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID);
    m_hActCtx = __create_act_ctx_w(&actCtx);
    }
    if (m_hActCtx == INVALID_HANDLE_VALUE)
    {
    actCtx.lpResourceName =  MAKEINTRESOURCEW(CREATEPROCESS_MANIFEST_RESOURCE_ID);
    m_hActCtx = __create_act_ctx_w(&actCtx);
    }
    if (m_hActCtx == INVALID_HANDLE_VALUE)
    {
    m_hActCtx = NULL;
    }*/
}

__MODULE_STATE::~__MODULE_STATE()
{
   
   /*   if (m_hActCtx != NULL && m_hActCtx != INVALID_HANDLE_VALUE)
    {
    __release_act_ctx(m_hActCtx);
    m_hActCtx = INVALID_HANDLE_VALUE;
    }*/
   
}


__MODULE_THREAD_STATE::__MODULE_THREAD_STATE()
{
   m_nLastHit = static_cast<int_ptr>(-1);
   m_nLastStatus = static_cast<int_ptr>(-1);
   // xxx   m_pLastInfo = NULL;
   
   // Note: it is only necessary to initialize non-zero data
   //m_pfnNewHandler = &__new_handler;
}

__MODULE_THREAD_STATE::~__MODULE_THREAD_STATE()
{
   
   // xxx   delete m_pLastInfo;
   
   
}

/////////////////////////////////////////////////////////////////////////////
// __MODULE_STATE for base application

LRESULT CALLBACK __window_procedure_base(oswindow, UINT, WPARAM, LPARAM);

class ___BASE_MODULE_STATE : public __MODULE_STATE
{
public:
   //   ___BASE_MODULE_STATE() : __MODULE_STATE(TRUE, __window_procedure_base, _MFC_VER)
   ___BASE_MODULE_STATE() : __MODULE_STATE(TRUE, 1)
   { }
};

___BASE_MODULE_STATE gen_BaseModuleState;

#undef __window_procedure
LRESULT CALLBACK
__window_procedure_base(oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
   return __window_procedure(hWnd, nMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// helper functions for module state

CLASS_DECL_BASE __MODULE_STATE * __get_app_module_state()
{
   return &gen_BaseModuleState;
}

CLASS_DECL_BASE __MODULE_STATE * __get_module_state()
{
   ___THREAD_STATE* pState = gen_ThreadState;
   ENSURE(pState);
   __MODULE_STATE* pResult;
   if (pState->m_pModuleState != NULL)
   {
      // thread state's module state serves as override
      pResult = pState->m_pModuleState;
   }
   else
   {
      // otherwise, use global cast state
      pResult = &gen_BaseModuleState;
   }
   ENSURE(pResult != NULL);
   return pResult;
}

HINSTANCE CLASS_DECL_BASE __get_instance_handle_helper()
{
   return __get_module_state()->m_hCurrentInstanceHandle;
}

bool CLASS_DECL_BASE __is_module_dll()
{
   return __get_module_state()->m_bDLL;
}

bool CLASS_DECL_BASE __init_current_state_app()
{
   ::base::application * pApp = __get_module_state()->m_pCurrentWinApp;
   if (pApp != NULL && !pApp->m_pbaseapp->initialize_instance())
   {
      // Init Failed
      try
      {
         pApp->m_pbaseapp->exit();
      }
      catch(...)
      {
      }
      __ios_term();
      return FALSE;
   }
   return TRUE;
}

CLASS_DECL_BASE __MODULE_THREAD_STATE * __get_module_thread_state()
{
   __MODULE_THREAD_STATE* pResult=__get_module_state()->t_pthread;
   ENSURE(pResult != NULL);
   return pResult;
}




// Note: in separate module so it can be replaced if needed

void CLASS_DECL_BASE __abort()
{
   //   TRACE(::ca2::trace::category_AppMsg, 0, "__abort called.\n");
   
   __ios_term();
   abort();
}

/////////////////////////////////////////////////////////////////////////////



/*
 
 _PNH CLASS_DECL_BASE __set_new_handler(_PNH pfnNewHandler)
 {
 __MODULE_THREAD_STATE* pState = __get_module_thread_state();
 _PNH pfnOldHandler = pState->m_pfnNewHandler;
 pState->m_pfnNewHandler = pfnNewHandler;
 return pfnOldHandler;
 }
 
 */



/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Obsolete API
/*
 void CLASS_DECL_BASE __set_alloc_stop(LONG lRequestNumber)
 {
 _CrtSetBreakAlloc(lRequestNumber);
 }
 */
#ifdef DEBUG
bool CLASS_DECL_BASE __check_memory()
// check all of primitive::memory (look for primitive::memory tromps)
{
   //   return _CrtCheckMemory() != FALSE;
   return false;
}
#endif
/*
 // -- true if block of exact size, allocated on the heap
 // -- set *plRequestNumber to request number (or 0)
 bool CLASS_DECL_BASE __is_memory_block(const void * pData, UINT nBytes,
 LONG* plRequestNumber)
 {
 return _CrtIsMemoryBlock(pData, nBytes, plRequestNumber, NULL, NULL);
 }
 
 */





