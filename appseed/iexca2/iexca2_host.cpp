/*****************************************************************************
* host.cpp: Free ActiveX based on ActiveX control for VLC
*****************************************************************************
* Copyright (C) 2005 the VideoLAN team
* Copyright (C) 2008 http://unick-soft.xost.ru
*
* Authors: Damien Fouilleul <Damien.Fouilleul@laposte.net>
* Modification: Oleg <soft_support@list.ru>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*****************************************************************************/

#include "StdAfx.h"
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <Exdisp.h>
#include <SHLGUID.h>
#include <Mshtml.h>

CHAR * utf16_to_8_dup(const wchar_t * psz);

#undef new

HFONT CreatePointFontIndirect(const LOGFONT* lpLogFont, HDC hdc);

DWORD dwProgress = 0;
DWORD dwLastProgressUpdate;

////////////////////////////////////////////////////////////////////////
//class factory      
static LRESULT CALLBACK iexca2_inplace_class_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   iexca2::host * p_instance = reinterpret_cast < iexca2::host *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

   switch( uMsg )
   {
   case WM_USER + 1984 + 1977:
      {
         //              KillTimer(hWnd, 19841977);
         p_instance->deferred_prodevian_redraw();
      }
      return 0;
   case WM_CREATE:
      {
         ::SetTimer(hWnd, 19841977, 5, NULL);
      }
      break;
   case WM_ERASEBKGND:
      return 1L;
      return 0L;
   case WM_TIMER:
      {
         if(wParam == 19841977) // prodevian timer
         {
            p_instance->deferred_prodevian_redraw();
         }
      }
      break;
   default:
      {
         if((uMsg == WM_LBUTTONUP
            || uMsg == WM_RBUTTONUP
            || uMsg == WM_MBUTTONUP) &&
            is_installing_ca2())
         {
            p_instance->m_iHealingSurface++;
         }
      }
      break;
   }
   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifndef WITH_OUT_MFC

static INT_PTR CALLBACK iexca2_dialog_bix_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

   iexca2::host *p_instance = reinterpret_cast < iexca2::host *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

   switch( uMsg )
   {
   case WM_ERASEBKGND:
      return 1L;

   case WM_PAINT:
      PAINTSTRUCT ps;
      RECT pr;
      if( GetUpdateRect(hWnd, &pr, FALSE) )
      {
         RECT bounds;
         GetClientRect(hWnd, &bounds);
         BeginPaint(hWnd, &ps);
         p_instance->on_paint(ps.hdc, &bounds);
         EndPaint(hWnd, &ps);
      }
      return 0L;

   case WM_COMMAND:
      {
         /*switch( wParam )
         {
         case IDC_BUTTON_CLEAR:
         {
         p_instance->clearEditBox();
         break;
         }

         case IDC_BUTTON_URL:
         {
         ShellExecuteA( hWnd, NULL, PAGE_OF_PROGRAM,
         NULL, NULL, SW_SHOW);
         break;
         }
         }*/
         return 0L;
      }        

   default:
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }
};
#endif


namespace iexca2
{

   class_factory::class_factory(LONG *p_class_ref, HINSTANCE hInstance, REFCLSID rclsid) :
      _p_class_ref(p_class_ref),
      _hinstance(hInstance),
      _classid(rclsid),
      _inplace_picture(NULL)
   {
      WNDCLASS wClass;

      if( ! GetClassInfo(hInstance, getInPlaceWndClassName(), &wClass) )
      {
         wClass.style          = CS_NOCLOSE|CS_DBLCLKS;
         wClass.lpfnWndProc    = iexca2_inplace_class_window_proc;
         wClass.cbClsExtra     = 0;
         wClass.cbWndExtra     = 0;
         wClass.hInstance      = hInstance;
         wClass.hIcon          = NULL;
         wClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
         wClass.hbrBackground  = NULL;
         wClass.lpszMenuName   = NULL;
         wClass.lpszClassName  = getInPlaceWndClassName();

         _inplace_wndclass_atom = RegisterClass(&wClass);
      }
      else
      {
         _inplace_wndclass_atom = 0;
      }

      HBITMAP hbitmap = (HBITMAP)LoadImage(getHInstance(), TEXT("INPLACE-PICT"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
      if( NULL != hbitmap )
      {
         PICTDESC pictDesc;

         pictDesc.cbSizeofstruct = sizeof(PICTDESC);
         pictDesc.picType        = PICTYPE_BITMAP;
         pictDesc.bmp.hbitmap    = hbitmap;
         pictDesc.bmp.hpal       = NULL;

         if( FAILED(OleCreatePictureIndirect(&pictDesc, IID_IPicture, TRUE, reinterpret_cast<LPVOID*>(&_inplace_picture))) )
            _inplace_picture = NULL;
      }
      AddRef();
   }

   class_factory::~class_factory()
   {
      if( 0 != _inplace_wndclass_atom )
         UnregisterClass(MAKEINTATOM(_inplace_wndclass_atom), _hinstance);

      if( NULL != _inplace_picture )
         _inplace_picture->Release();
   }

   STDMETHODIMP class_factory::QueryInterface(REFIID riid, void **ppv)
   {
      if( NULL == ppv )
         return E_INVALIDARG;

      if( (IID_IUnknown == riid)
         || (IID_IClassFactory == riid) )
      {
         AddRef();
         *ppv = reinterpret_cast<LPVOID>(this);

         return NOERROR;
      }

      *ppv = NULL;

      return E_NOINTERFACE;
   }

   STDMETHODIMP_(ULONG) class_factory::AddRef(void)
   {
      return InterlockedIncrement(_p_class_ref);
   }

   STDMETHODIMP_(ULONG) class_factory::Release(void)
   {
      ULONG refcount = InterlockedDecrement(_p_class_ref);
      if( 0 == refcount )
      {
         delete this;
         return 0;
      }
      return refcount;
   }

   STDMETHODIMP class_factory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void **ppv)
   {
      if( NULL == ppv )
         return E_POINTER;

      *ppv = NULL;

      if( (NULL != pUnkOuter) && (IID_IUnknown != riid) ) {
         return CLASS_E_NOAGGREGATION;
      }

      host *host = new class host(this, pUnkOuter);
      if( NULL != host )
      {
         HRESULT hr = host->QueryInterface(riid, ppv);
         // the following will destroy the object if QueryInterface() failed
         host->Release();
         return hr;
      }
      return E_OUTOFMEMORY;
   }

   STDMETHODIMP class_factory::LockServer(BOOL fLock)
   {
      if( fLock )
         AddRef();
      else
         Release();

      return S_OK;
   }


   host::host(class_factory *p_class, LPUNKNOWN pUnkOuter) :
   _inplacewnd(NULL),
      _p_class(p_class),
      _i_ref(1UL),
      _i_codepage(CP_ACP),
   #ifndef WITH_OUT_MFC
      _b_usermode(TRUE)
   #else
      _b_usermode(FALSE) 
   #endif
   {
      p_class->AddRef();

      vlcOleControl = new ole_control(this);
      vlcOleInPlaceObjectWindowless = new ole_inplace_object_windowless(this);
      //vlcOleInPlaceObject = new ole_inplace_object(this);
      //vlcOleInPlaceActiveObject = new ole_inplace_active_object(this);
      vlcPersistStorage = new persist_storage(this);
      vlcPersistStreamInit = new persist_stream_init(this);
      vlcPersistPropertyBag = new persist_property_bag(this);
      vlcProvideClassInfo = new provide_class_info(this);
      vlcConnectionPointContainer = new connection_point_container(this);
      vlcObjectSafety = new object_safety(this);
      vlcControl2 = new control(this);
      vlcViewObject = new view_object(this);
      vlcDataObject = new data_object(this);
      vlcOleObject = new ole_object(this);
      vlcSupportErrorInfo = new support_error_info(this);

      // configure controlling IUnknown interface for implemented interfaces
      this->pUnkOuter = (NULL != pUnkOuter) ? pUnkOuter : dynamic_cast<LPUNKNOWN>(this);

      // default picure
      _p_pict = p_class->getInPlacePict();

      // make sure that persistable properties are initialized
      onInit();
   }

   host::~host()
   {
      AddRef(); 

      delete vlcSupportErrorInfo;
      delete vlcOleObject;
      delete vlcDataObject;
      delete vlcViewObject;
      delete vlcControl2;    
      delete vlcConnectionPointContainer;
      delete vlcProvideClassInfo;
      delete vlcPersistPropertyBag;
      delete vlcPersistStreamInit;
      delete vlcPersistStorage;
      //delete vlcOleInPlaceActiveObject;
      //delete vlcOleInPlaceObject;
      delete vlcObjectSafety;
      delete vlcOleInPlaceObjectWindowless;

      delete vlcOleControl;
      if( _p_pict )
         _p_pict->Release();

      _p_class->Release();
   }

   STDMETHODIMP host::QueryInterface(REFIID riid, void **ppv)
   {
      if( NULL == ppv )
         return E_INVALIDARG;

      if( IID_IUnknown == riid )
         *ppv = reinterpret_cast<LPVOID>(this);
      else if( IID_IOleObject == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcOleObject);
      else if( IID_IOleControl == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcOleControl);
      else if( IID_IOleWindow == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcOleInPlaceObjectWindowless);
      else if( IID_IOleInPlaceObject == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcOleInPlaceObjectWindowless);
      else if( IID_IOleInPlaceObjectWindowless == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcOleInPlaceObjectWindowless);
      //else if( IID_IOleInPlaceActiveObject == riid )
      //  *ppv = reinterpret_cast<LPVOID>(vlcOleInPlaceActiveObject);
      else if( IID_IPersist == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcPersistStreamInit);
      else if( IID_IPersistStreamInit == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcPersistStreamInit);
      else if( IID_IPersistStorage == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcPersistStorage);
      else if( IID_IPersistPropertyBag == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcPersistPropertyBag);
      else if( IID_IProvideClassInfo == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcProvideClassInfo);
      else if( IID_IProvideClassInfo2 == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcProvideClassInfo);
      else if( IID_IConnectionPointContainer == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcConnectionPointContainer);
      else if( IID_IObjectSafety == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcObjectSafety);
      else if( IID_IDispatch == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcControl2);
      else if( IID_iexca2_control_interface == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcControl2);
      else if( IID_IViewObject == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcViewObject);
      else if( IID_IViewObject2 == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcViewObject);
      else if( IID_IDataObject == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcDataObject);
      else if( IID_ISupportErrorInfo == riid )
         *ppv = reinterpret_cast<LPVOID>(vlcSupportErrorInfo);
      else
      {
         *ppv = NULL;
         return E_NOINTERFACE;
      }
      ((LPUNKNOWN)*ppv)->AddRef();
      return NOERROR;
   }

   STDMETHODIMP_(ULONG) host::AddRef(void)
   {
      return InterlockedIncrement((LONG *)&_i_ref);
   }

   STDMETHODIMP_(ULONG) host::Release(void)
   {
      if( ! InterlockedDecrement((LONG *)&_i_ref) )
      {
         delete this;
         return 0;
      }
      return _i_ref;
   }

   //////////////////////////////////////

   HRESULT host::onInit(void)
   {
      //test variable init
      _bstr_testString = NULL;

      _i_backcolor = 0;
      _bstr_testString = NULL;
      // set default/preferred size (320x240) pixels in HIMETRIC
      HDC hDC = CreateDevDC(NULL);
      _extent.cx = 320;
      _extent.cy = 240;
      HimetricFromDP(hDC, (LPPOINT)&_extent, 1);
      DeleteDC(hDC);

      return S_OK;
   }

   HRESULT host::onLoad(void)
   {
      if( true )
      {
         /*
         ** try to retreive the base URL using the client site moniker, which for Internet Explorer
         ** is the URL of the page the host is embedded into.
         */
         LPOLECLIENTSITE pClientSite;
         if( SUCCEEDED(vlcOleObject->GetClientSite(&pClientSite)) && (NULL != pClientSite) )
         {

            /*if(FAILED(pClientSite->QueryInterface(&m_psite)))
            {
            return E_FAIL;
            }
            if(!m_psite->CanInPlaceActivate())
            return E_FAIL;*/
            /*m_hwndSite = NULL;
            m_psite->GetWindow(&m_hwndSite);*/
            IBindCtx *pBC = 0;
            if( SUCCEEDED(CreateBindCtx(0, &pBC)) )
            {
               LPMONIKER pContMoniker = NULL;
               if( SUCCEEDED(pClientSite->GetMoniker(OLEGETMONIKER_ONLYIFTHERE,
                  OLEWHICHMK_CONTAINER, &pContMoniker)) )
               {
                  LPOLESTR base_url;
                  if( SUCCEEDED(pContMoniker->GetDisplayName(pBC, NULL, &base_url)) )
                  {
                     m_strBaseUrl = utf16_to_8_dup(base_url);
                  }
               }
            }
         }
      }
      setDirty(FALSE);


      m_bInitialized = true;

      //NPN_GetValue(m_instance, NPNVnetscapeWindow, &m_hwnd);
      //Sleep(15 * 1000);
      start_plugin();

      if(!initialize())
         return FALSE;


      set_ready();

      return TRUE;

   }



   void host::start_plugin()
   {

      //Sleep(15 * 1000);
      //Sleep(15 * 1000);
      //      update_npca2_installed();

      HANDLE hmutexInstall = ::CreateMutex(NULL, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
      if(::GetLastError() == ERROR_ALREADY_EXISTS)
      {
         m_pplugin = NULL;
         ::CloseHandle(hmutexInstall);
         return;
      }
      ::CloseHandle(hmutexInstall);

      if(m_pplugin == NULL)
      {
         m_pplugin = new ::spa::plugin();
         m_pplugin->m_phost = this;
      }


   }



   void host::setErrorInfo(REFIID riid, const char *description)
   {
      vlcSupportErrorInfo->setErrorInfo( 
         OLESTR("FreeActiveX.AXPlugin.2"),
         riid, description );
   }

   HRESULT host::onAmbientChanged(LPUNKNOWN pContainer, DISPID dispID)
   {
      VARIANT v;
      switch( dispID )
      {
      case DISPID_AMBIENT_BACKCOLOR:
         VariantInit(&v);
         V_VT(&v) = VT_I4;
         if( SUCCEEDED(GetObjectProperty(pContainer, dispID, v)) )
         {
            setBackColor(V_I4(&v));
         }
         break;
      case DISPID_AMBIENT_DISPLAYNAME:
         break;
      case DISPID_AMBIENT_FONT:
         break;
      case DISPID_AMBIENT_FORECOLOR:
         break;
      case DISPID_AMBIENT_LOCALEID:
         break;
      case DISPID_AMBIENT_MESSAGEREFLECT:
         break;
      case DISPID_AMBIENT_SCALEUNITS:
         break;
      case DISPID_AMBIENT_TEXTALIGN:
         break;
      case DISPID_AMBIENT_USERMODE:
         VariantInit(&v);
         V_VT(&v) = VT_BOOL;
         if( SUCCEEDED(GetObjectProperty(pContainer, dispID, v)) )
         {
            //setUserMode(V_BOOL(&v) != VARIANT_FALSE);
         }
         break;
      case DISPID_AMBIENT_UIDEAD:
         break;
      case DISPID_AMBIENT_SHOWGRABHANDLES:
         break;
      case DISPID_AMBIENT_SHOWHATCHING:
         break;
      case DISPID_AMBIENT_DISPLAYASDEFAULT:
         break;
      case DISPID_AMBIENT_SUPPORTSMNEMONICS:
         break;
      case DISPID_AMBIENT_AUTOCLIP:
         break;
      case DISPID_AMBIENT_APPEARANCE:
         break;
      case DISPID_AMBIENT_CODEPAGE:
         VariantInit(&v);
         V_VT(&v) = VT_I4;
         if( SUCCEEDED(GetObjectProperty(pContainer, dispID, v)) )
         {
            setCodePage(V_I4(&v));
         }
         break;
      case DISPID_AMBIENT_PALETTE:
         break;
      case DISPID_AMBIENT_CHARSET:
         break;
      case DISPID_AMBIENT_RIGHTTOLEFT:
         break;
      case DISPID_AMBIENT_TOPTOBOTTOM:
         break;
      case DISPID_UNKNOWN:
         /*
         ** multiple property change, look up the ones we are interested in
         */
         VariantInit(&v);
         V_VT(&v) = VT_BOOL;
         if( SUCCEEDED(GetObjectProperty(pContainer, DISPID_AMBIENT_USERMODE, v)) )
         {
            //setUserMode(V_BOOL(&v) != VARIANT_FALSE);
         }
         VariantInit(&v);
         V_VT(&v) = VT_I4;
         if( SUCCEEDED(GetObjectProperty(pContainer, DISPID_AMBIENT_CODEPAGE, v)) )
         {
            setCodePage(V_I4(&v));
         }
         break;
      }
      return S_OK;
   }

   HRESULT host::onClose(DWORD dwSaveOption)
   {
      if( isInPlaceActive() )
      {        
         onInPlaceDeactivate();        
      }
      finalize();
      vlcDataObject->onClose();
      return S_OK;
   }

   BOOL host::isInPlaceActive(void)
   {
      return (NULL != _inplacewnd);
   }

   HRESULT host::onActivateInPlace(LPMSG lpMesg, HWND hwndParent, LPCRECT lprcPosRect, LPCRECT lprcClipRect)
   {
      RECT clipRect = *lprcClipRect;

      /*
      ** record keeping of control geometry within container
      */
      m_rect = *lprcPosRect;

      /*
      ** Create a window for in place activated control.
      ** the window geometry matches the control viewport
      ** within container so that embedded video is always
      ** properly displayed.
      */
      // How VLC create window
      if(_inplacewnd == NULL)
      {
         _inplacewnd = CreateWindow(_p_class->getInPlaceWndClassName(),
            TEXT("ActiveX Plugin In-Place Window"),
            WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
            lprcPosRect->left,
            lprcPosRect->top,
            lprcPosRect->right-lprcPosRect->left,
            lprcPosRect->bottom-lprcPosRect->top,
            HWND_MESSAGE,
            0,
            _p_class->getHInstance(),
            NULL
            );

         //param work
         if( NULL == _inplacewnd )
            return E_FAIL;

         SetWindowLongPtr(_inplacewnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

         /* change cliprect coordinates system relative to window bounding rect */
         /*OffsetRect(&clipRect, -lprcPosRect->left, -lprcPosRect->top);

         HRGN clipRgn = CreateRectRgnIndirect(&clipRect);
         SetWindowRgn(_inplacewnd, clipRgn, TRUE);

         ShowWindow(_inplacewnd, SW_SHOW);*/


         //start_plugin();

      }

      return S_OK;
   }

   HRESULT host::onInPlaceDeactivate(void)
   {
      {
         fireOnStopEvent();
      }
      m_psite->Release();
      DestroyWindow(_inplacewnd);
      _inplacewnd = NULL;

      return S_OK;
   }

   void host::setBackColor(OLE_COLOR backcolor)
   {
      if( _i_backcolor != backcolor )
      {
         _i_backcolor = backcolor;
         if( isInPlaceActive() )
         {

         }
         setDirty(TRUE);
      }
   }

   void host::setFocus(BOOL fFocus)
   {
      if( fFocus )
         SetActiveWindow(_inplacewnd);
   }

   BOOL host::hasFocus(void)
   {
      return GetActiveWindow() == _inplacewnd;
   }

   void host::onDraw(DVTARGETDEVICE * ptd, HDC hicTargetDev,
      HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds)
   {
      RECT bounds;
      if(lprcWBounds != NULL)
      {
         bounds.right   = lprcWBounds->right;
         bounds.top     = lprcWBounds->top;
         bounds.left    = lprcWBounds->left;
         bounds.top     = lprcWBounds->top;
      }
      else
      {
         bounds = m_rect;
      }


      LPCRECT lpcrect = &bounds;
      HDC hdc = hdcDraw;

      m_bOnPaint = true;
      on_paint(hdc, lpcrect);
      m_bOnPaint = false;

   }




   void host::onPositionChange(LPCRECT lprcPosRect, LPCRECT lprcClipRect)
   {
      RECT clipRect = *lprcClipRect;

      /*
      ** record keeping of control geometry within container
      */
      m_rect = *lprcPosRect;

      /*
      ** change in-place window geometry to match clipping region
      */
      SetWindowPos(_inplacewnd, NULL,
         lprcPosRect->left,
         lprcPosRect->top,
         lprcPosRect->right-lprcPosRect->left,
         lprcPosRect->bottom-lprcPosRect->top,
         SWP_NOACTIVATE|
         SWP_NOCOPYBITS|
         SWP_NOZORDER|
         SWP_NOOWNERZORDER );


      //      if(m_puiHost != NULL)
      {

         /*RECT rectWindow;

         ::GetWindowRect(_inplacewnd, &rectWindow);

         RECT rectSite;

         ::GetWindowRect(m_hwndSite, &rectSite);

         RECT rect = rectWindow;

         rect.left      += rectSite.left;
         rect.top       += rectSite.top;
         rect.right     += rectSite.left;
         rect.bottom    += rectSite.top;

         set_window_rect(&rect);*/

      }

      set_window_rect(&m_rect);

      /* change cliprect coordinates system relative to window bounding rect */
      OffsetRect(&clipRect, -lprcPosRect->left, -lprcPosRect->top);
      HRGN clipRgn = CreateRectRgnIndirect(&clipRect);
      SetWindowRgn(_inplacewnd, clipRgn, FALSE);
   }

   void host::freezeEvents(BOOL freeze)
   {
      vlcConnectionPointContainer->freezeEvents(freeze);
   }

   void host::firePropChangedEvent(DISPID dispid)
   {
      vlcConnectionPointContainer->firePropChangedEvent(dispid);
   }

   void host::fireOnPlayEvent(void)
   {
      DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
   }

   void host::fireOnPauseEvent(void)
   {
      DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
   }

   void host::fireOnStopEvent(void)
   {
      DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
   }


   void host::setTestStringEditBox()
   {
   }

   void host::getTestStringEditBox()
   {
   }

   void host::show()
   {
      ShowWindow(_inplacewnd, SW_SHOWNORMAL);    
   }

   void host::hide()
   {
      ShowWindow(_inplacewnd, SW_HIDE);        
   }

   void host::clearEditBox()
   {
   }

   bool host::open_url(const char * psz)
   {

      IServiceProvider * pisp;
      m_psite->QueryInterface(IID_IServiceProvider, (void **)&pisp);

/*      IWebBrowserApp * papp;
      pisp->QueryService(SID_SWebBrowserApp, IID_IWebBrowserApp, (void **)&papp);*/

      IWebBrowserApp * papp;
      pisp->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void **)&papp);

      IDispatch * pdispDocument;
      papp->get_Document(&pdispDocument);

      IHTMLDocument2 * pdoc;
      pdispDocument->QueryInterface(IID_IHTMLDocument2, (void **) &pdoc);

      BSTR bstrUrl = ::SysAllocString(utf8_to_16(psz));

      pdoc->put_URL(bstrUrl);

      ::SysFreeString(bstrUrl);

      pdispDocument->Release();
      papp->Release();
      pisp->Release();

      return true;
   }

   void host::plugin_system_redraw()
   {
      m_psite->InvalidateRect(NULL, FALSE);
   }

   bool host::is_ok()
   {
      return m_bApp && (m_strPluginUrl.length() > 0);
   }

   void host::post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      ::PostMessageA(_inplacewnd, uiMessage, wparam, lparam);
   }

   void host::get_window_rect(LPRECT lprect)
   {
      //RECT rectSite;
      //GetWindowRect(m_hwndSite, &rectSite);
      lprect->left      = m_rect.left;    //   + rectSite.left;
      lprect->right     = m_rect.right;   //   + rectSite.left;
      lprect->top       = m_rect.top;     //   + rectSite.top;
      lprect->bottom    = m_rect.bottom;  //   + rectSite.top;
   }

   void host::on_prepare_memory()
   {
      /*      if(&m_psystem->file() == NULL || &m_psystem->dir() == NULL)
      return;
      ::string str = m_psystem->file().as_string(m_psystem->dir().path(m_psystem->dir().name(m_strBaseUrl.c_str()), m_strSrc.c_str()), m_psystem);
      //App(::get_app()).http().get(App(::get_app()).dir().path(m_strBaseUrl.c_str(), m_strSrc.c_str()));
      m_iMemory = str.get_length();
      m_lpbMemory = (byte *) malloc(m_iMemory);
      memcpy_dup(m_lpbMemory, (const char *) str, m_iMemory);*/
   }


   HWND host::get_host_window()
   {
      return m_hwndSite;
   }


   /*   void host::start_plugin()
   {

   update_ca2_installed();

   if(is_ca2_installed())
   {
   HMODULE hmodule = ::LoadLibraryA("ca2.dll");
   FN_NEW_HOTPLUGIN fn_new_hotplugin = (FN_NEW_HOTPLUGIN) ::GetProcAddress(hmodule, "new_hotplugin");
   m_pplugin = fn_new_hotplugin();
   }
   else
   {
   m_pplugin = new ::spa_plugin();
   }
   m_pplugin->m_phost = this;
   }
   */

} // namespace iexca2

