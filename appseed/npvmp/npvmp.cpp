// npvmp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "npvmp.h"
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

#include "NPPData.h"
#include "npvmpCntrItem.h"
#include "vmsp.h"

#ifndef _INC_NEW
	#include <new.h>
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CNpvmpApp

BEGIN_MESSAGE_MAP(CNpvmpApp, CWinApp)
	//{{AFX_MSG_MAP(CNpvmpApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNpvmpApp construction

CNpvmpApp::CNpvmpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNpvmpApp object

CNpvmpApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNpvmpApp initialization

BOOL CNpvmpApp::InitInstance()
{
	AfxSetResourceHandle(m_hInstance);
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll();
	return S_OK;
}


NPError NPP_Initialize()
{
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
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CNPPData * pdata = (CNPPData *) instance->pdata;
	pdata->m_pdoctemplate->CloseAllDocuments(true);
	return NPERR_NO_ERROR;
}




void NPP_Shutdown(void)
{
}


NPError NPP_SetWindow(NPP instance, NPWindow *window)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CNPPData * pdata = (CNPPData *) instance->pdata;
	
	pdata->m_rectLast.left = window->x;
	pdata->m_rectLast.top = window->y;
	pdata->m_rectLast.right = pdata->m_rectLast.left + window->width;
	pdata->m_rectLast.bottom = pdata->m_rectLast.top + window->height;

	if(pdata->m_hwndParent == NULL)
	{
		pdata->m_hwndParent = (HWND) window->window;
		pdata->OpenPlayerFile();
	}
	CFrameWnd * pframe = pdata->GetFrame();
	if(pframe != NULL)
	{
		pframe->SetWindowPos(
			&CWnd::wndTop,
			window->x,
			window->y,
			window->width,
			window->height,
			SWP_SHOWWINDOW);
	}
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
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (instance == NULL)
		return;
	CNPPData * pdata = (CNPPData *) instance->pdata;
	if(fname != NULL 
		&& pdata != NULL)
	{
		pdata->m_strFilePath = fname;
		pdata->OpenPlayerFile();
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
