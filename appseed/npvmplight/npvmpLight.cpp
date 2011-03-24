// npvmp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "npvmpLight.h"
// netscape
#ifndef _NPAPI_H_
#include <npapi.h>
#endif
#ifndef _NPUPP_H_
#include <npupp.h>
#endif

NPNetscapeFuncs* g_pNavigatorFuncs = 0;
static NPPluginFuncs* g_pluginFuncs;

//\\// DEFINE
#ifdef WIN32
    #define NP_EXPORT
#else
    #define NP_EXPORT _export
#endif


#include "guibase/guibase.h"
#include "guibase/BaseVirtualTab.h"
#include "mus/mus.h"
#include "musctrl/musctrl.h"
#include "mediaplay/mediaplay.h"
#include "filemanager/filemanager.h"
#include "aud/aud.h"
#include "mplite/mplite.h"
#include "mplite/NPPData.h"
#include "mplite/vmplight.h"
#include "mplite/mplightView.h"
#include "mplite/PaneView.h"

#ifndef _INC_NEW
	#include <new.h>
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MusicalPlayerLightApp * g_papp = NULL;

class ThreadProcStartAppData
{
public:
   HINSTANCE m_hinstance;
};

UINT AFX_CDECL ThreadProcStartApp(LPVOID lpParameter)
{
   ThreadProcStartAppData * pdata = (ThreadProcStartAppData *) lpParameter;
      g_papp = new MusicalPlayerLightApp();

		
      // initialize MFC and print and error on failure
      if (!AfxWinInit(pdata->m_hinstance, NULL, NULL, 0))
      {
	      // TODO: change error code to suit your needs
	      _tprintf(_T("Fatal Error: MFC initialization failed\n"));
      }
      else
      {
	      // TODO: code your application's behavior here.
      }
   delete pdata;
   return 0;
}

UINT AFX_CDECL ThreadProcAppRun(LPVOID lpParameter)
{
   g_papp->m_hThread = ::GetCurrentThread();
   g_papp->m_nThreadID = ::GetCurrentThreadId();
   int nReturnCode = g_papp->CWinThread::Run();

#ifdef _DEBUG
	// Check for missing AfxLockTempMap calls
	if (AfxGetModuleState()->m_nTempMapLock != 0)
	{
		TRACE(traceAppMsg, 0, "Warning: Temp map lock count non-zero (%ld).\n",
			AfxGetModuleState()->m_nTempMapLock);
	}
	AfxLockTempMaps();
	AfxUnlockTempMaps(-1);
#endif

	AfxWinTerm();
   delete g_papp;
   g_papp = NULL;
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	pState->m_pCurrentWinThread = NULL;

	return nReturnCode;
}

static AFX_EXTENSION_MODULE VmsmusctrlDLL = { NULL, NULL };
static HINSTANCE g_hInstance = NULL;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("NPVMPLIGHT.DLL Initializing!\n");

      DWORD dwSize = GetEnvironmentVariable("PATH", NULL, 0);
      LPTSTR lpsz = new char[dwSize + 1024];
      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
      strcat(lpsz, ";U:\\carloscc\\appdev\\main\\build\\debug");
      BOOL bResult = SetEnvironmentVariable("PATH", lpsz);
      delete lpsz;

      g_hInstance = hInstance;


      


		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("NPVMPLIGHT.DLL Terminating!\n");
	}
	return 1;   // ok
}


NPError NPP_Initialize()
{
      g_papp = new MusicalPlayerLightApp();
   // initialize MFC and print and error on failure
   afxContextIsDLL = false;
   if (!AfxWinInit(g_hInstance, NULL, NULL, 0))
   {
      // TODO: change error code to suit your needs
      _tprintf(_T("Fatal Error: MFC initialization failed\n"));
   }
   else
   {
      // TODO: code your application's behavior here.
   }
// App global initializations (rare)
	if (g_papp != NULL && !g_papp->InitApplication())
		return NPERR_GENERIC_ERROR;

   g_papp->m_bInline = true;

	// Perform specific initializations
	if (!g_papp->InitInstance())
	{
		g_papp->ExitInstance();
	}
	AfxBeginThread(ThreadProcAppRun, NULL);

	return NPERR_NO_ERROR;
}


NPError NPP_New(
	NPMIMEType    pluginType,
    NPP instance, uint16 mode,
    int16 argc,   char *argn[],
    char *argv[], NPSavedData *saved)
{
	CNPPData * pdata = new CNPPData();
	instance->pdata = pdata;
	return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData **save)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CNPPData * pdata = (CNPPData *) instance->pdata;
   pdata->m_pdoctemplate->CloseAllDocuments(NULL);
	return NPERR_NO_ERROR;
}




void NPP_Shutdown(void)
{
   g_papp->PostThreadMessage(WM_QUIT, 0, 0);
   {
	   AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	   pState->m_pCurrentWinThread = NULL;
   }
   {
	   _AFX_THREAD_STATE* pState = AfxGetThreadState();
	   pState->m_bNeedTerm = FALSE;
		pState->m_hHookOldMsgFilter = NULL;
   }

}


NPError NPP_SetWindow(NPP instance, NPWindow *window)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CNPPData * pdata = (CNPPData *) instance->pdata;
	
	pdata->m_rectLast.left = window->x;
	pdata->m_rectLast.top = window->y;
	pdata->m_rectLast.right = pdata->m_rectLast.left + window->width;
	pdata->m_rectLast.bottom = pdata->m_rectLast.top + window->height;

	if(pdata->m_hwndParent == NULL)
	{
		pdata->m_hwndParent = (HWND) window->window;
		pdata->OpenPlayerFile(NULL);
	}
	pdata->UpdateWindowPos();
	return NPERR_NO_ERROR;
}

NPError WINAPI NP_EXPORT
NP_GetEntryPoints(NPPluginFuncs* pFuncs)
{
    // trap a NULL ptr 
    if(pFuncs == NULL)
        return NPERR_INVALID_FUNCTABLE_ERROR;

    // if the plugin's function table is smaller than the plugin expects,
    // then they are incompatible, and should return an error 

    pFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
    pFuncs->newp          = NPP_New;
    pFuncs->destroy       = NPP_Destroy;
    pFuncs->setwindow     = NPP_SetWindow;
    pFuncs->newstream     = NPP_NewStream;
    pFuncs->destroystream = NPP_DestroyStream;
    pFuncs->asfile        = NPP_StreamAsFile;
    pFuncs->writeready    = NPP_WriteReady;
    pFuncs->write         = NPP_Write;
    pFuncs->print         = NPP_Print;
    pFuncs->event         = 0;       /// reserved 

	g_pluginFuncs		  = pFuncs;

    return NPERR_NO_ERROR;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\.
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//.
// NP_Initialize
//
//	called immediately after the plugin DLL is loaded
//
NPError WINAPI NP_EXPORT 
NP_Initialize(NPNetscapeFuncs* pFuncs)
{
    // trap a NULL ptr 
    if(pFuncs == NULL)
        return NPERR_INVALID_FUNCTABLE_ERROR;

    g_pNavigatorFuncs = pFuncs; // save it for future reference 

    // if the plugin's major ver level is lower than the Navigator's,
    // then they are incompatible, and should return an error 
    if(HIBYTE(pFuncs->version) > NP_VERSION_MAJOR)
        return NPERR_INCOMPATIBLE_VERSION_ERROR;

	// We have to defer these assignments until g_pNavigatorFuncs is set
    int navMinorVers = g_pNavigatorFuncs->version & 0xFF;

	if( navMinorVers >= NPVERS_HAS_NOTIFICATION ) {
		g_pluginFuncs->urlnotify = NPP_URLNotify;
	}
	
#ifdef WIN32 // An ugly hack, because Win16 lags behind in Java
	if( navMinorVers >= NPVERS_HAS_LIVECONNECT ) {
#else
	if( navMinorVers >= NPVERS_WIN16_HAS_LIVECONNECT )
#endif // WIN32
//		g_pluginFuncs->javaClass = Private_GetJavaClass();
	}

	// NPP_Initialize is a standard (cross-platform) initialize function.
    return NPP_Initialize();
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\.
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//.
// NP_Shutdown
//
//	called immediately before the plugin DLL is unloaded.
//	This functio shuold check for some ref count on the dll to see if it is
//	unloadable or it needs to stay in memory. 
//
NPError WINAPI NP_EXPORT 
NP_Shutdown()
{
    NPP_Shutdown();
    g_pNavigatorFuncs = NULL;
    return NPERR_NO_ERROR;
}








//------------------------------------------------------------------------------------
// NPP_NewStream:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_NewStream(NPP instance,
							NPMIMEType type,
							NPStream *stream, 
							NPBool seekable,
							uint16 *stype)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
	
	*stype = NP_ASFILEONLY;
	
	return NPERR_NO_ERROR;
}


//------------------------------------------------------------------------------------
// NPP_WriteReady:
//------------------------------------------------------------------------------------
int32 NP_LOADDS
NPP_WriteReady(NPP instance, NPStream *stream)
{
	if (instance == NULL)
		return -1;

	
	return -1; 
}



//------------------------------------------------------------------------------------
// NPP_Write:
//------------------------------------------------------------------------------------
int32 NP_LOADDS
NPP_Write(NPP instance, NPStream *stream, int32 offset, int32 len, void *buffer)
{
	if (instance == NULL)
		return -1;
	
		
	return -1;
}



//------------------------------------------------------------------------------------
// NPP_DestroyStream:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_DestroyStream(NPP instance, NPStream *stream, NPError reason)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
		
	
	return NPERR_NO_ERROR;
}


//------------------------------------------------------------------------------------
// NPP_StreamAsFile:
//------------------------------------------------------------------------------------
void NP_LOADDS
NPP_StreamAsFile(NPP instance, NPStream *stream, const char* fname)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (instance == NULL)
		return;
	CNPPData * pdata = (CNPPData *) instance->pdata;
	if(fname != NULL 
		&& pdata != NULL)
	{
		pdata->OpenPlayerFile(fname);
	}
	return;
}



//------------------------------------------------------------------------------------
// NPP_Print:
//------------------------------------------------------------------------------------
void NP_LOADDS
NPP_Print(NPP instance, NPPrint* printInfo)
{
    if(printInfo == NULL)   // trap invalid parm
        return;

	if (instance != NULL)
	{
	}

}


//------------------------------------------------------------------------------------
// NPP_HandleEvent:
// Mac-only.
//------------------------------------------------------------------------------------
int16 NPP_HandleEvent(NPP instance, void* event)
{
	NPBool eventHandled = FALSE;
	if (instance == NULL)
		return eventHandled;
		
	
	return eventHandled;
}

//------------------------------------------------------------------------------------
// NPP_URLNotify:
//------------------------------------------------------------------------------------
void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
	if( instance != NULL )
	{
		//
	}
}


//------------------------------------------------------------------------------------
// NPP_GetJavaClass:
//------------------------------------------------------------------------------------
jref NPP_GetJavaClass(void)
{

	return NULL;
}
