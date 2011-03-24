#include "StdAfx.h"
#include "plugin_instance.h"


UINT g_nRedrawThreadID;
extern bool g_bAppStarted;





UINT APIENTRY _redraw(void * pParam)
{
   nsPluginInstance * pplugin = (nsPluginInstance *) pParam;
   while(true)
   {
      Sleep(100);
      NPRect invalidRect;
      invalidRect.left = pplugin->m_rect.left;
      invalidRect.top = pplugin->m_rect.top;
      invalidRect.right = pplugin->m_rect.right;
      invalidRect.bottom = pplugin->m_rect.bottom;
      NPN_InvalidateRect(pplugin->m_instance, &invalidRect);
      NPN_ForceRedraw(pplugin->m_instance);
   }
}

nsPluginInstance::nsPluginInstance(NPP a_instance) : 
   nsPluginInstanceBase(),
   m_instance(a_instance)
{
   m_pszUrl = NULL;
   m_pszHeaders = NULL;
   m_pmemory = NULL;
   m_pfile = NULL;
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

   m_puiHost = NULL;

   m_hwnd = NULL;
   m_bStream = false;
}

nsPluginInstance::~nsPluginInstance()
{
   if(m_puiHost != NULL)
   {
      delete m_puiHost;
   }

   NPN_ReleaseVariantValue(&m_varDocument);
   NPN_ReleaseObject(m_pobjectWindow);
}

static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
static WNDPROC lpOldProc = NULL;







NPBool nsPluginInstance::init(NPWindow* aWindow)
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

   //_beginthreadex(NULL, 0, _redraw, this, 0, &g_nRedrawThreadID); 


   
   NPN_GetValue(m_instance, NPNVnetscapeWindow, &m_hwnd);
   if(m_hwnd != NULL)
   {
      
   }

   //::SetTimer(NULL, (UINT_PTR) this , 20, TimerProcRedraw);


   update_spa_installed();
   if(is_spa_installed())
   {
      update_spa_updated();
      if(is_spa_updated())
      {
         update_ca2_installed();
         if(is_ca2_installed())
            update_ca2_updated();
      }
   }

   /*update_spa_installed();
   if(is_spa_installed())
   {
      update_spa_updated();
      if(is_spa_updated())
      {
         update_ca2_installed();
         if(is_ca2_installed())
            update_ca2_updated();
      }
   }*/
   
   //start_ca2();
   starter_start("mplite");

   return TRUE;
}





NPBool nsPluginInstance::isInitialized()
{
   return m_bInitialized;
}

const char * nsPluginInstance::getVersion()
{
  return NPN_UserAgent(m_instance);
}









NPError nsPluginInstance::NewStream(NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype)
{
   //::DeleteObject(hEventReady);
   m_bPreCheck = false;
   return NPERR_NO_ERROR;


}







void nsPluginInstance::redraw()
{
   if(!m_bOnPaint && (::GetTickCount() - m_last_redraw) >= 84)
   {
      NPRect invalidRect;
      invalidRect.left = 0;
      invalidRect.top = 0;
      invalidRect.right = m_rect.right - m_rect.left;
      invalidRect.bottom = m_rect.bottom - m_rect.top;
      NPN_InvalidateRect(m_instance, &invalidRect);
      NPN_ForceRedraw(m_instance);
      m_last_redraw = ::GetTickCount();
   }

   if(m_bCa2JustInstalled)
   {
      m_bCa2JustInstalled = false;
      start_ca2();
   }

}



bool nsPluginInstance::is_ok()
{
   return m_bApp && m_bStream;
}
   
void nsPluginInstance::post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
{
   ::PostMessage(m_hwnd, uiMessage, wparam, lparam);
}


void nsPluginInstance::get_window_rect(LPRECT lprect)
{
   RECT rectWindow;
   //::GetWindowRect(m_hwnd, &rectWindow);
   *lprect = m_rect;
/*   lprect->left      += rectWindow.left;
   lprect->right     += rectWindow.left;
   lprect->top       += rectWindow.top;
   lprect->bottom       += rectWindow.top;*/
}


HWND nsPluginInstance::get_host_window()
{
   return m_hwnd;
}



NPError nsPluginInstance::SetWindow(NPWindow* pNPWindow) 
{
   m_rect.left = pNPWindow->x;
   m_rect.top = pNPWindow->y;
   m_rect.right = m_rect.left + pNPWindow->width;
   m_rect.bottom = m_rect.top + pNPWindow->height;

   if(m_puiHost != NULL)
   {
      m_puiHost->m_bRectOk = true;
      m_puiHost->m_pimpl->m_bRectOk = true;
      m_puiHost->m_rectParentClient =  m_rect;
      m_puiHost->m_rectParentClient.offset(-point64(m_puiHost->m_rectParentClient.top_left()));
      m_puiHost->m_pimpl->m_rectParentClient = m_puiHost->m_rectParentClient;
      rect64 rectWindow;
      m_puiHost->GetWindowRect(rectWindow);
      m_puiHost->SetWindowPos(ZORDER_TOP, rectWindow.left, rectWindow.top, rectWindow.width(), rectWindow.height(), 0);
      m_puiHost->SendMessageA(WM_SIZE);
      m_puiHost->SendMessageA(WM_MOVE);
   }

   return NPERR_NO_ERROR;
}


void nsPluginInstance::shut()
{
   //::KillTimer(NULL, (UINT_PTR) this);

   plugin::finalize();

   m_hwnd = NULL;
   m_bInitialized = false;
}


int32  nsPluginInstance::Write(NPStream *stream, int32 offset, int32 len, void *buffer)
{ 
   if(m_pszUrl == NULL && stream->url != NULL)
      m_pszUrl = _strdup(stream->url);
   if(m_pszHeaders == NULL && stream->headers != NULL)
      m_pszHeaders = _strdup(stream->headers);
   if(m_pfile != NULL && m_pmemory != NULL)
   {
      if(m_lpbMemory != NULL)
      {
         m_pmemory = new primitive::memory(m_lpbMemory, m_iMemory);
         m_lpbMemory = NULL;
         m_iMemory = 0;
      }
      m_pfile->write(buffer, len);
   }
   else
   {
      if(m_lpbMemory != NULL)
      {
         if(offset + len > m_iMemory)
         {
            m_lpbMemory = (BYTE *) realloc(m_lpbMemory, offset + len);
         }
      }
      else
      {
         m_lpbMemory = (BYTE *) malloc(offset + len);
      }
      memcpy(&m_lpbMemory[offset], buffer, len);
      if(offset + len > m_iMemory)
      {
         m_iMemory = offset + len;
      }
   }
   return len; 
}


NPError nsPluginInstance::DestroyStream(NPStream *stream, NPError reason)
{
   if(reason == NPRES_DONE)
   {
      m_bStream = true;
      if(m_puiHost != NULL)
      {
         m_puiHost->defer_check(npca2::check_before_start);
      }
   }
   

  
   return NPERR_NO_ERROR;
}



#undef url
#define Application System


uint16 nsPluginInstance::HandleEvent(void * pvoid)
{
   NPEvent * pevent = (NPEvent *) pvoid;

   switch(pevent->event)
   {
   case WM_USER + 1984 + 1977:
      {
         start_ca2();
      }
      return 0;
   case WM_PAINT:
      m_bOnPaint = true;
      if(!is_spa_installed() || !is_spa_updated())
      {
         onBarePaint((HDC) pevent->wParam, (LPCRECT) pevent->lParam);
      }
      else if(is_ca2_installed() && !is_installing_ca2())
      {
         onCa2Paint((HDC) pevent->wParam, (LPCRECT) pevent->lParam);
      }
      else
      {
         onPaint((HDC) pevent->wParam, (LPCRECT) pevent->lParam);
      }
      m_bOnPaint = false;
      return 0;
   case WM_TIMER:
      {
         switch(pevent->wParam)
         {
         case 19841977:
            {
               NPRect invalidRect;
               invalidRect.left = m_rect.left;
               invalidRect.top = m_rect.top;
               invalidRect.right = m_rect.right;
               invalidRect.bottom = m_rect.bottom;
               NPN_InvalidateRect(m_instance, &invalidRect);
               NPN_ForceRedraw(m_instance);
            }
            break;
         case 8477:
            {
               KillTimer(m_hwnd, 8477);
               start_ca2();

            };
            break;
         }
      }
      return 0;
   default:
      {
         if(!is_spa_installed() || !is_spa_updated())
         {
            return 1;
         }

         if((pevent->event == WM_LBUTTONUP
         || pevent->event == WM_RBUTTONUP
         || pevent->event == WM_MBUTTONUP) &&
            is_installing_ca2())
         {
            m_iHealingSurface++;
         }
         if(m_puiHost != NULL)
         {
            LPARAM lparam = pevent->lParam;
            if(pevent->event >= WM_MOUSEFIRST
               && pevent->event <= WM_MOUSELAST)
            {
               point pt = point(lparam);
               //pt.x -= m_rect.left;
               //pt.y -= m_rect.top;
               lparam = pt._001GetLparam();
            }
            if(pevent->event == WM_MOUSEMOVE)
            {
               ::ca::window * pwindow = dynamic_cast < ::ca::window * > (m_puiHost->m_pimpl);
               pwindow->m_bMouseHover = true; // avoids tracking mouse leave;
            }
            LRESULT l = m_puiHost->SendMessageA(pevent->event, pevent->wParam, lparam);
            return l;
         }
      };
   };
   return 0;      
}



void nsPluginInstance::get_window_rect(__rect64 * lprect)
{
   //class rect rectWindow;
   //::GetWindowRect(m_hwnd, &rectWindow);
   class rect64 rect;
   rect = m_rect;
   //rect.offset(point64(rectWindow.top_left()));
   *lprect = rect;
}

bool nsPluginInstance::open_url(const char * pszUrl)
{
   string strLocation(pszUrl);
   NPVariant varLocation;
   varLocation.type = NPVariantType_String;
   varLocation.value.stringValue.UTF8Characters = strLocation;
   varLocation.value.stringValue.UTF8Length = strLocation.get_length();
   NPN_SetProperty(m_instance, m_varDocument.value.objectValue, sLocation_id, &varLocation);
   return true;
}

npca2::host_interaction * nsPluginInstance::create_host_interaction()
{
   npca2::host_interaction * pinteraction = new npca2::host_interaction(m_psystem);
   pinteraction->create_message_window("npca2");
   ::ca::window * pwindow = dynamic_cast < ::ca::window * > (pinteraction->m_pimpl);
   pwindow->m_bTranslateMouseMessageCursor = false;
   return pinteraction;
}
