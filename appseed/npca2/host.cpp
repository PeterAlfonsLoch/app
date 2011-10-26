#include "StdAfx.h"


UINT g_nRedrawThreadID;
extern bool g_bAppStarted;


UINT APIENTRY _redraw(void * pParam)
{
   ::npca2::host * phost = (::npca2::host *) pParam;
   while(true)
   {
      Sleep(100);
      NPRect invalidRect;
      invalidRect.left     = (uint16_t) phost->m_rect.left;
      invalidRect.top      = (uint16_t) phost->m_rect.top;
      invalidRect.right    = (uint16_t) phost->m_rect.right;
      invalidRect.bottom   = (uint16_t) phost->m_rect.bottom;
      NPN_InvalidateRect(phost->m_instance, &invalidRect);
      NPN_ForceRedraw(phost->m_instance);
   }
}


namespace npca2
{

   ATOM register_class(HINSTANCE hInstance);

   VOID CALLBACK TimerProcHost(HWND hwnd,  UINT uMsg,  UINT_PTR idEvent,  DWORD dwTime);


   host::host(NPP a_instance)
   {
      m_phost           = NULL;
      m_bInitialized    = false;
      m_bOk             = false;
      m_rect.left       = 0;
      m_rect.top        = 0;
      m_rect.bottom     = 0;
      m_rect.right      = 0;

      m_bRunningSpaAdmin = false;

      m_instance = a_instance;

      m_rxchannel.create("ca2/fontopus/ccvotagus/spaboot_install_callback", "npca2.dll");

      ::npca2::register_class((HINSTANCE) ::GetModuleHandleA("npca2.dll"));

      m_hwndMessage = ::CreateWindowExA(0, "npca2_message_window", "npca2_message_window", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);

      SetTimer(m_hwndMessage, (UINT_PTR) this, 84, TimerProcHost); // close to 12 frames per second.

      m_pfile           = NULL;
      NPError err = NPN_GetValue(m_instance, NPNVWindowNPObject, &m_pobjectWindow);

      m_lpbMemory = NULL;
      m_iMemory = -1;

      NPIdentifier n = NPN_GetStringIdentifier("foof");

      sFoo_id = NPN_GetStringIdentifier("foo");
      sBar_id = NPN_GetStringIdentifier("bar");
      sDocument_id = NPN_GetStringIdentifier("document");
      sLocation_id = NPN_GetStringIdentifier("location");
      sBody_id = NPN_GetStringIdentifier("body");
      sCreateElement_id = NPN_GetStringIdentifier("createElement");
      sCreateTextNode_id = NPN_GetStringIdentifier("createTextNode");
      sAppendChild_id = NPN_GetStringIdentifier("appendChild");
      sPluginType_id = NPN_GetStringIdentifier("PluginType");

      NPN_GetProperty(m_instance, m_pobjectWindow, sDocument_id, &m_varDocument);

      err = NPN_SetValue(m_instance, NPPVpluginWindowBool, (void *) FALSE);

      err = NPN_SetValue(m_instance, NPPVpluginTransparentBool, (void *) TRUE);

      m_hwnd = NULL;
      m_bStream = false;


      m_strHostPluginLocation = calc_location_url();

   }

   host::~host()
   {
      NPN_ReleaseVariantValue(&m_varDocument);
      NPN_ReleaseObject(m_pobjectWindow);
      ::DestroyWindow(m_hwndMessage);
   }

   static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
   static WNDPROC lpOldProc = NULL;







   NPBool host::init(NPWindow* aWindow)
   {

      if(aWindow == NULL)
         return FALSE;

      m_rect.left = aWindow->x;
      m_rect.top = aWindow->y;
      m_rect.right = m_rect.left + aWindow->width;
      m_rect.bottom = m_rect.top + aWindow->height;

      m_hwnd = (HWND)aWindow->window;

      if(m_hwnd == NULL)
         return FALSE;


      m_bInitialized = true;


      //NPN_GetValue(m_instance, NPNVnetscapeWindow, &m_hwnd);
      //Sleep(15 * 1000);
      start_plugin();

      if(!initialize())
         return FALSE;

      return TRUE;

   }





   NPBool host::isInitialized()
   {
      return m_bInitialized;
   }

   const char * host::getVersion()
   {
     return NPN_UserAgent(m_instance);
   }









   NPError host::NewStream(NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype)
   {
      m_bOk = false;
      return NPERR_NO_ERROR;
   }







   void host::redraw()
   {
      if(!m_bOnPaint && (::GetTickCount() - m_last_redraw) >= 5)
      {
         NPRect invalidRect;
         invalidRect.left     = (uint16_t) 0;
         invalidRect.top      = (uint16_t) 0;
         invalidRect.right    = (uint16_t) (m_rect.right - m_rect.left);
         invalidRect.bottom   = (uint16_t) (m_rect.bottom - m_rect.top);
         NPN_InvalidateRect(m_instance, &invalidRect);
         NPN_ForceRedraw(m_instance);
         m_last_redraw = ::GetTickCount();
      }


   }



   bool host::is_ok()
   {
      return m_bStream && m_bOk;
   }
   
   void host::post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      ::PostMessage(m_hwnd, uiMessage, wparam, lparam);
   }



   NPError host::SetWindow(NPWindow* pNPWindow) 
   {
      m_rect.left = pNPWindow->x;
      m_rect.top = pNPWindow->y;
      m_rect.right = m_rect.left + pNPWindow->width;
      m_rect.bottom = m_rect.top + pNPWindow->height;

      set_window_rect(&m_rect);

      return NPERR_NO_ERROR;
   }


   void host::shut()
   {
      m_bInitialized = false;
      
      ::KillTimer(m_hwndMessage, (UINT_PTR) this);

      finalize();

      m_hwnd = NULL;
   }


   int32  host::Write(NPStream *stream, int32 offset, int32 len, void *buffer)
   { 

      if(m_strPluginUrl.is_empty() && stream->url != NULL)
         m_strPluginUrl = stream->url;

      if(m_strPluginHeaders.is_empty() && stream->headers != NULL)
         m_strPluginHeaders = stream->headers;

      if(buffer != NULL && len > 0)
      {
         append_memory(buffer, len);
      }

      return len; 

   }


   NPError host::DestroyStream(NPStream *stream, NPError reason)
   {
      if(reason == NPRES_DONE)
      {
         m_bStream = true;
         set_ready();
      }
      return NPERR_NO_ERROR;
   }



   #undef url
   #define Application System


   uint16 host::HandleEvent(void * pvoid)
   {
      NPEvent * pevent = (NPEvent *) pvoid;
#ifdef _WINDOWS
      return message_handler(pevent->event, pevent->wParam, pevent->lParam);
#else
      return message_handler(pevent);
#endif
   }



   bool host::open_url(const char * pszUrl)
   {
      NPVariant varLocation;
      varLocation.type = NPVariantType_String;
      varLocation.value.stringValue.UTF8Characters = pszUrl;
      varLocation.value.stringValue.UTF8Length = strlen_dup(pszUrl);
      NPN_SetProperty(m_instance, m_varDocument.value.objectValue, sLocation_id, &varLocation);
      return true;
   }


   vsstring host::calc_location_url()
   {
      NPVariant varLocation;
      if(!NPN_GetProperty(m_instance, m_pobjectWindow, sLocation_id, &varLocation))
         return "";
      NPObject * plocation = varLocation.value.objectValue;
      // Create a "href" identifier.
      NPIdentifier identifier = NPN_GetStringIdentifier("href");
      // Get the location property from the location object.
      NPVariant varValue;
      if(!NPN_GetProperty(m_instance, plocation, identifier, &varValue))
      {
         NPN_ReleaseVariantValue(&varLocation);
         return "";
      }
      vsstring strUrl(varValue.value.stringValue.UTF8Characters, varValue.value.stringValue.UTF8Length);
      NPN_ReleaseVariantValue(&varValue);
      NPN_ReleaseVariantValue(&varLocation);
      return strUrl;
   }

   HWND host::get_host_window()
   {
      return m_hwnd;
   }

   UINT_PTR host::message_handler(UINT_PTR uiMessage, WPARAM wparam, LPARAM lparam)
   {
      switch(uiMessage)
      {
      case WM_PAINT:
         m_bOnPaint = true;
         if(m_bInitialized)
         {
            on_paint((HDC) wparam, (LPCRECT) lparam);
         }
         m_bOnPaint = false;
         return 0;
      case WM_TIMER:
         {
            switch(wparam)
            {
            case 19841977:
               {
                  NPRect invalidRect;
                  invalidRect.left     = (uint16_t) m_rect.left;
                  invalidRect.top      = (uint16_t) m_rect.top;
                  invalidRect.right    = (uint16_t) m_rect.right;
                  invalidRect.bottom   = (uint16_t) m_rect.bottom;
                  NPN_InvalidateRect(m_instance, &invalidRect);
                  NPN_ForceRedraw(m_instance);
               }
               break;
            }
         }
         return 0;
      }
      return ::hotplugin::host::message_handler(uiMessage, wparam, lparam);      
   }


   VOID CALLBACK TimerProcHost(HWND hwnd,  UINT uMsg,  UINT_PTR idEvent,  DWORD dwTime)
   {

      host * phost = (host *) idEvent;
      phost->redraw();

      if(phost->is_ca2_installation_ready())
      {
         phost->set_ca2_installation_ready(false);
         phost->start_ca2();
      }

   }


   LRESULT CALLBACK window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return DefWindowProc(hWnd, message, wParam, lParam);
   }

   ATOM register_class(HINSTANCE hInstance)
   {
	   WNDCLASSEX wcex;

	   wcex.cbSize = sizeof(WNDCLASSEX);

	   wcex.style			   = 0;
	   wcex.lpfnWndProc	   = &window_proc;
	   wcex.cbClsExtra	   = 0;
	   wcex.cbWndExtra	   = 0;
	   wcex.hInstance		   = hInstance;
	   wcex.hIcon			   = NULL;
	   wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
	   wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
      wcex.lpszMenuName	   = NULL;
	   wcex.lpszClassName	= "npca2_message_window";
	   wcex.hIconSm		   = NULL;

	   return RegisterClassEx(&wcex);
   }


   void host::on_paint(HDC hdcWindow, LPCRECT lprect)
   {
      ::hotplugin::host::on_paint(hdcWindow, lprect);

   }

   bool host::finalize()
   {
      
      ::KillTimer(m_hwndMessage, (UINT_PTR) this);

      return ::hotplugin::host::finalize();

   }



} // namespace npca2



/*extern "C"
{
#include <ntddk.h>
};*/

/*#pragma warning (disable: 4731) // EBP register overwritten
#pragma warning (disable: 4733) // non-SAFESEH compliant

typedef void (__stdcall* CleanupFN)();

struct CleanupEntry
{
    long		m_nPrevIdx;
    CleanupFN	m_pfnCleanup;
};

struct UnwindFrame
{
    ULONG			m_sig;
    long			m_nCleanupCount;   //number of entries in unwindtable
    CleanupEntry*	m_pCleanupArr;
	// C++ try-catch data is omitted
};

struct ExcReg
{ 
    ExcReg*	m_pPrev;
    ULONG	m_handler;
    long	m_NextCleanup;
    ULONG	m_ebp;
};

void FrameUnwind(UnwindFrame* pUFrame, ULONG dwEbp, ExcReg* pExcFrame)
{
    const CleanupEntry* pCleanupArr = pUFrame->m_pCleanupArr;
    int count = pUFrame->m_nCleanupCount;

//commented on insertion 2011-05-31	ASSERT(pExcFrame->m_NextCleanup < pUFrame->m_nCleanupCount); // stack corruption test

	while (true)
	{
		long nNextID = pExcFrame->m_NextCleanup;
		if (nNextID < 0)
			break;

		const CleanupEntry& entry = pCleanupArr[nNextID];
		CleanupFN pfnCleanup = entry.m_pfnCleanup;
		pExcFrame->m_NextCleanup = entry.m_nPrevIdx;

		__try {
			_asm
			{
				mov EAX, pfnCleanup
				push EBP       //save current EBP
				mov EBP, dwEbp  //the EBP of the unwinding function
				call EAX
				pop EBP
			}
		} __finally {
			if (AbnormalTermination())
				// one of the destructor has raised an exception that resulted
				// in another unwind.
				FrameUnwind(pUFrame, dwEbp, pExcFrame); // recursively
		}
	}
}

EXCEPTION_DISPOSITION __cdecl FrameHandler(UnwindFrame* pUFrame, EXCEPTION_RECORD* pExc, ExcReg* pExcFrame)
{
	// EXCEPTION_UNWINDING = 2, EXCEPTION_EXIT_UNWIND = 4
    if (6 & pExc->ExceptionFlags)
		FrameUnwind(pUFrame, (ULONG) (ULONG_PTR) &pExcFrame->m_ebp, pExcFrame);
    return ExceptionContinueSearch;
}

extern "C" __declspec (naked)
EXCEPTION_DISPOSITION __cdecl __CxxFrameHandler3(int a, int b, int c, int d)
{
	_asm {
		//prolog
        push EBP
        mov EBP, ESP

		// We don't use the last two parameters (processor and dispatcher contexts)
		// Hence - push just the 1st two parameters, plus the UnwindFrame passed in EAX
        push b
        push a
        push EAX

        call FrameHandler

		//epilog
        mov ESP, EBP
        pop EBP
        ret
	};
}
*/