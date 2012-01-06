#include "StdAfx.h"
#include <stdarg.h>
#include "sal.h"



#ifndef _ApplicationFrameworkDLL
   #error file must be compiled with _ApplicationFrameworkDLL
#endif

/////////////////////////////////////////////////////////////////////////////
// _ApplicationFrameworkDLL support

static AFX_EXTENSION_MODULE coreDLL;

/////////////////////////////////////////////////////////////////////////////
// CDynLinkLibrary class

// IMPLEMENT_DYNAMIC(CDynLinkLibrary, command_target)

// Constructor - will wire into the current application's list
CDynLinkLibrary::CDynLinkLibrary(AFX_EXTENSION_MODULE& state, BOOL bSystem)
{
/*xxx   m_classList.Construct(offsetof(::ca::type_info, m_pNextClass));
*/

   // copy info from AFX_EXTENSION_MODULE struct
   ASSERT(state.hModule != NULL);
   m_hModule = state.hModule;
   m_hResource = state.hResource;
   m_bSystem = bSystem;

   // insert at the head of the list (extensions will go in front of core DLL)
   DEBUG_ONLY(m_pNextDLL = NULL);
   AfxLockGlobals(CRIT_DYNLINKLIST);
   AfxUnlockGlobals(CRIT_DYNLINKLIST);
}

CDynLinkLibrary::CDynLinkLibrary(HINSTANCE hModule, HINSTANCE hResource)
{
   /* xxx
   m_classList.Construct(offsetof(::ca::type_info, m_pNextClass));
*/
   m_hModule = hModule;
   m_hResource = hResource;
   m_bSystem = FALSE;

   // insert at the head of the list (extensions will go in front of core DLL)
   DEBUG_ONLY(m_pNextDLL = NULL);
   AfxLockGlobals(CRIT_DYNLINKLIST);
   AfxUnlockGlobals(CRIT_DYNLINKLIST);
}


CDynLinkLibrary::~CDynLinkLibrary()
{
   // remove this frame window from the list of frame windows
   AfxLockGlobals(CRIT_DYNLINKLIST);
   AfxUnlockGlobals(CRIT_DYNLINKLIST);
}

/////////////////////////////////////////////////////////////////////////////
// CDynLinkLibrary diagnostics

#ifdef _DEBUG
void CDynLinkLibrary::assert_valid() const
{
   ASSERT(m_hModule != NULL);
}

void CDynLinkLibrary::dump(dump_context& dc) const
{
   command_target::dump(dc);

   dc << "m_hModule = " << (UINT_PTR)m_hModule;
   dc << "\nm_hResource = " << (UINT_PTR)m_hResource;

   if (m_hModule != NULL)
   {
      char szName[_MAX_PATH];
      GetModuleFileName(m_hModule, szName, _countof(szName));
      dc << "\nmodule name = " << szName;
   }
   else
      dc << "\nmodule name is unknown";

   dc << "\n";
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// special initialization and helper functions

// This is called in an extension DLL's DllMain
//  It makes a copy of the DLL's HMODULE, as well as a copy of the
//  runtime class objects that have been initialized by this
//  extension DLL as part of normal static object construction
//  executed before DllMain is entered.

BOOL AfxInitExtensionModule(AFX_EXTENSION_MODULE& state, HMODULE hModule)
{
   // only initialize once
   if (state.bInitialized)
   {
//      System.InitLocalData(hModule);
      return TRUE;
   }
   state.bInitialized = TRUE;

   // save the current HMODULE information for resource loading
   ASSERT(hModule != NULL);
   state.hModule = hModule;
   state.hResource = hModule;

   return TRUE;
}


void AfxTermExtensionModule(AFX_EXTENSION_MODULE & state, BOOL bAll)
{
   UNREFERENCED_PARAMETER(bAll);
   // make sure initialized
   if (!state.bInitialized)
      return;

   // search for CDynLinkLibrary matching state.hModule and delete it
   ASSERT(state.hModule != NULL);
   //AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   AfxLockGlobals(CRIT_DYNLINKLIST);
/*   for (CDynLinkLibrary* pDLL = pModuleState->m_libraryList; pDLL != NULL; )
   {
      CDynLinkLibrary* pNextDLL = pDLL->m_pNextDLL;
      if (bAll || pDLL->m_hModule == state.hModule)
         delete pDLL;    // will unwire itself
      pDLL = pNextDLL;
   }*/
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // delete any local storage attached to this module
//   AfxTermLocalData(state.hModule, TRUE);

   // remove any entries from the window message ::collection::map cache
//   AfxResetMsgCache();
}

/////////////////////////////////////////////////////////////////////////////
// special LoadLibrary and FreeLibrary for loading ca2 API extension DLLs

HINSTANCE AfxLoadLibrary(const char * lpszModuleName)
{
   ASSERT(lpszModuleName != NULL);
   AfxLockGlobals(CRIT_LOCKSHARED);
    HINSTANCE hInstLib = LoadLibrary(lpszModuleName);
   AfxUnlockGlobals(CRIT_LOCKSHARED);
   return hInstLib;
}

 
 
HINSTANCE AfxLoadLibraryEx(const char * lpFileName,  HANDLE hFile,  DWORD dwFlags)
{  
      
   ASSERT(lpFileName != NULL);
   AfxLockGlobals(CRIT_LOCKSHARED);
   HINSTANCE hInstLib = LoadLibraryEx(lpFileName,hFile,dwFlags);
   AfxUnlockGlobals(CRIT_LOCKSHARED);
   return hInstLib;
}
 

BOOL AfxFreeLibrary(HINSTANCE hInstLib)
{
   AfxLockGlobals(CRIT_LOCKSHARED);
   BOOL bResult = FreeLibrary(hInstLib);
   AfxUnlockGlobals(CRIT_LOCKSHARED);
   return bResult;
}


HINSTANCE AfxFindResourceHandle(const char * lpszName, const char * lpszType)
{
   ASSERT(lpszName != NULL);
   ASSERT(lpszType != NULL);

//   HINSTANCE hInst;

   // first check the main module state
/*   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   if (!pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResource(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   // check for non-system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   CDynLinkLibrary* pDLL;
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL;
      pDLL = pDLL->m_pNextDLL)
   {
      if (!pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResource(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // check language specific resource next
   hInst = pModuleState->m_appLangDLL;
   if (hInst != NULL && ::FindResource(hInst, lpszName, lpszType) != NULL)
      return hInst;

   // check the main system module state
   if (pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (::FindResource(hInst, lpszName, lpszType) != NULL)
         return hInst;
   }

   // check for system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL; pDLL = pDLL->m_pNextDLL)
   {
      if (pDLL->m_bSystem && pDLL->m_hResource != NULL &&
         ::FindResource(pDLL->m_hResource, lpszName, lpszType) != NULL)
      {
         // found it in a DLL
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return pDLL->m_hResource;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);*/

   // if failed to find resource, return application resource
//   return AfxGetResourceHandle();
   return NULL;
}

HINSTANCE AfxFindStringResourceHandle(UINT nID)
{
   UNREFERENCED_PARAMETER(nID);
//   HINSTANCE hInst;

   // first check the main module state
/*   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   if (!pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (_template::AtlGetStringResourceImage(hInst, nID) != NULL)
      {
         // found a non-zero string in cast
         return hInst;
      }
   }

   // check non-system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   CDynLinkLibrary* pDLL;
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL;
      pDLL = pDLL->m_pNextDLL)
   {
      if (!pDLL->m_bSystem && (hInst = pDLL->m_hResource) != NULL &&
        (_template::AtlGetStringResourceImage(hInst, nID) != NULL))
      {
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return hInst;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // check language specific DLL next
   hInst = pModuleState->m_appLangDLL;
   if (hInst != NULL && (_template::AtlGetStringResourceImage(hInst, nID) != NULL))
   {
      // found a non-zero string in language DLL
      return hInst;
   }

   // check the system module state
   if (pModuleState->m_bSystem)
   {
      hInst = AfxGetResourceHandle();
      if (_template::AtlGetStringResourceImage(hInst, nID) != NULL)
      {
         // found a non-zero string in cast
         return hInst;
      }
   }

   // check system DLLs in proper order
   AfxLockGlobals(CRIT_DYNLINKLIST);
   for (pDLL = pModuleState->m_libraryList; pDLL != NULL; pDLL = pDLL->m_pNextDLL)
   {
      if (pDLL->m_bSystem && (hInst = pDLL->m_hResource) != NULL &&
         (_template::AtlGetStringResourceImage(hInst, nID) != NULL))
      {
         AfxUnlockGlobals(CRIT_DYNLINKLIST);
         return hInst;
      }
   }
   AfxUnlockGlobals(CRIT_DYNLINKLIST);

   // did not find it*/
   return NULL;
}

// AfxLoadString must not only check for the appropriate string segment
//   in the resource file, but also that the string is non-zero
/*int AfxLoadString(UINT nID, __out_ecount_opt(nMaxBuf) wchar_t * lpszBuf, UINT nMaxBuf)
{
   ASSERT(fx_is_valid_address(lpszBuf, nMaxBuf*sizeof(WCHAR)));
   if( lpszBuf == NULL || nMaxBuf == 0)
      AfxThrowInvalidArgException();

   HINSTANCE hInst;
   const _template::ATLSTRINGRESOURCEIMAGE* pImage;
   int nCharsToCopy;

   hInst = AfxFindStringResourceHandle(nID);
   if (hInst == NULL)
   {
      lpszBuf[0] = L'\0';
      return 0;
   }

   pImage = _template::AtlGetStringResourceImage(hInst, nID);
   ASSERT(pImage != NULL);
   ASSERT(pImage->nLength != 0);
   nCharsToCopy = min(nMaxBuf-1, pImage->nLength);
   _template::checked::memcpy_s(lpszBuf, (nMaxBuf-1)*sizeof(WCHAR), 
      pImage->achString, nCharsToCopy*sizeof(WCHAR));
   lpszBuf[nCharsToCopy] = L'\0';

   return nCharsToCopy;
}
*/
/*
int AfxLoadString(UINT nID, __out_ecount_opt(nMaxBuf) char * lpszBuf, UINT nMaxBuf)
{
   ASSERT(fx_is_valid_address(lpszBuf, nMaxBuf*sizeof(CHAR)));
   if( lpszBuf == NULL || nMaxBuf == 0)
      AfxThrowInvalidArgException();

   HINSTANCE hInst;
   const _template::ATLSTRINGRESOURCEIMAGE* pImage;
   int nBytes;

   hInst = AfxFindStringResourceHandle(nID);
   if (hInst == NULL)
   {
      lpszBuf[0] = L'\0';
      return 0;
   }

   pImage = _template::AtlGetStringResourceImage(hInst, nID);
   ASSERT(pImage != NULL);
   ASSERT(pImage->nLength != 0);
   nBytes = ::WideCharToMultiByte(CP_ACP, 0, pImage->achString, pImage->nLength, lpszBuf, nMaxBuf-1, NULL, NULL);
   lpszBuf[nBytes] = '\0';

   return nBytes;
}
*/

/////////////////////////////////////////////////////////////////////////////
// Library initialization and cleanup


extern "C" BOOL WINAPI RawDllMain(HINSTANCE, DWORD dwReason, LPVOID);
extern "C" BOOL (WINAPI * const _pRawDllMain)(HINSTANCE , DWORD , LPVOID) = &RawDllMain;

extern "C"
BOOL WINAPI RawDllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
   hInstance;
   try
   {
      if (dwReason == DLL_PROCESS_ATTACH)
      {
         SetErrorMode(SetErrorMode(0) |
            SEM_FAILCRITICALERRORS|SEM_NOOPENFILEERRORBOX);

         // add a reference to thread local storage data
//         AfxTlsAddRef();

         // make sure we have enough primitive::memory to attempt to start (8kb)
         void * pMinHeap = LocalAlloc(NONZEROLPTR, 0x2000);
         if (pMinHeap == NULL)
            return FALSE;   // fail if primitive::memory alloc fails
         LocalFree(pMinHeap);

         // cause early initialization of _afxCriticalSection
         if (!AfxCriticalInit())
            return FALSE;

      }
      else if (dwReason == DLL_PROCESS_DETACH)
      {

         // free up the _afxCriticalSection
         AfxCriticalTerm();

         // remove reference from thread local data
//         AfxTlsRelease();
      }
   }
   catch( base_exception* e )
   {
      e->Delete();
      return FALSE;
   }
   
   return TRUE;    // ok
}

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {

      use_base_ca2_allocator();

      // initialize this DLL's extension module
      VERIFY(AfxInitExtensionModule(coreDLL, hInstance));





   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      // free language specific DLL
/*      AFX_MODULE_STATE* pState = AfxGetModuleState();
      if (pState->m_appLangDLL != NULL)
      {
         ::FreeLibrary(pState->m_appLangDLL);
         pState->m_appLangDLL = NULL;
      }

      // free the DLL info blocks
      CDynLinkLibrary* pDLL;
      while ((pDLL = pState->m_libraryList) != NULL)
         delete pDLL;
      ASSERT(pState->m_libraryList.is_empty());

      // cleanup module state for this process
      AfxTermExtensionModule(coreDLL);


      // cleanup module state in OLE private module state
      AfxTermExtensionModule(coreDLL, TRUE);

      // free any local data for this process/thread
      AfxTermLocalData(NULL, TRUE);*/
   }
   else if (dwReason == DLL_THREAD_DETACH)
   {
//      AfxTermThread();
   }

   return TRUE;    // ok
}

////////////////////////////////////////////////////////////////////////////
// Special initialization entry point for controls

void AfxCoreInitModule()
{
/*   ASSERT(AfxGetModuleState() != AfxGetAppModuleState());

   // construct new dynlink library in this context for core resources
   CDynLinkLibrary* pDLL = new CDynLinkLibrary(coreDLL, TRUE);

   // borrow resources from language specific DLL if loaded
   AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
   AFX_MODULE_STATE* pAppState = AfxGetAppModuleState();
   if (pModuleState->m_appLangDLL == NULL)
      pModuleState->m_appLangDLL = pAppState->m_appLangDLL;*/
}


/*
/////////////////////////////////////////////////////////////////////////////
// Special code to wire up vector deleting destructors

static void _AfxForceVectorDelete()
{
#ifdef _DEBUG
   ASSERT(FALSE);  // never called
#endif

   new ::ca::bitmap[2];
   new CBitmapButton[2];
   new ::ca::brush[2];
   new simple_button[2];
   new byte_array[2];
   new simple_combo_box[2];
   new ::ca::graphics[2];
   new dword_array[2];
   new dialog[2];
   new CDialogBar[2];
   new user::edit_plain_text[2];
   new ::ex1::filesp[2];
   new ::ca::font_sp[2];
   new frame_window[2];
   new gdi_object[2];
   new CListBox[2];
   new CCheckListBox[2];
   new map_ptr_to_ptr[2];
   new CMapPtrToWord[2];
   new CMapStringToOb[2];
   new CMapStringToPtr[2];
   new string_to_string_map[2];
   new CMapWordToOb[2];
   new CMapWordToPtr[2];
   new CMemFile[2];
   new ::userbase::menu[2];
   new CMetaFileDC[2];
   new CObArray[2];
   new object_list[2];
   new ::ca::paletter_sp[2];
   new ::ca::pen_sp[2];
   new CPtrArray[2];
   new pointer_list[2];
   new CRectTracker[2];
   new CRgn[2];
   new CScrollBar[2];
   new CSharedFile[2];
   new CSplitterWnd[2];
   new CStatic[2];
   new simple_status_bar[2];
   new CStdioFile[2];
   new string[2];
   new StringArray[2];
   new string_list[2];
   new thread_slot_data[2];
   new class time[2];
   new time_span[2];
   new simple_toolbar[2];
   new CUIntArray[2];
   new window[2];
   new word_array[2];

   new CFileFind[2];
   new CInternetSession[2];

   new CDragListBox[2];
   new status_bar_control[2];
   new CListCtrl[2];
   new CTreeCtrl[2];
   new CSpinButtonCtrl[2];
   new CSliderCtrl[2];
   new CProgressCtrl[2];
   new CHeaderCtrl[2];
   new CHotKeyCtrl[2];
   new CToolTipCtrl[2];
   new CTabCtrl[2];
   new CAnimateCtrl[2];
   new ::image_list[2];
   new CToolBarCtrl[2];
   new CRichEditCtrl[2];

   new mirror_file[2];
   new CDockState[2];

   new CListView[2];
   new CTreeView[2];
   new CCommandLineInfo[2];
   new document_manager[2];

   new CPageSetupDialog[2];

   new semaphore[2];
   new mutex[2];
   new event[2];
   new critical_section[2];

#ifdef _CA_DLL
   new COleDataSource[2];
   new COleDispatchDriver[2];
   new COleDropSource[2];
   new CMonikerFile[2];
   new COleResizeBar[2];
   new CAsyncMonikerFile[2];
   new CCachedDataPathProperty[2];
   new CDataPathProperty[2];
   new COleStreamFile[2];
   new COleTemplateServer[2];
   new COleDataObject[2];
   new COleDropTarget[2];
   new COleIPFrameWnd[2];

   new COleDocIPFrameWnd[2];

   new COleVariant[2];
   new CRichEditView[2];
   new CRichEditCntrItem[2];
#endif

#ifdef _CA_DLL
   new CDatabase[2];
   new CLongBinary[2];
#endif

// Net
#ifdef _CA_DLL
   new CAsyncSocket[2];
   new CSocket[2];
#endif
}
void (*_afxForceVectorDelete_mfc)() = &_AfxForceVectorDelete;

*/

//#include <delayimp.h>
/*
extern "C"
{
FARPROC
WINAPI
Downlevel_DelayLoadFailureHook(
   UINT unReason,
   PDelayLoadInfo pDelayInfo
   );

PfnDliHook __pfnDliFailureHook2 = Downlevel_DelayLoadFailureHook;

}
*/
/////////////////////////////////////////////////////////////////////////////
