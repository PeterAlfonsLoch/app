/*****************************************************************************
 * oleobject.cpp: Free ActiveX based on ActiveX control for VLC
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


namespace iexca2
{


   ole_object::ole_object(host *p_instance) :
   _p_clientsite(NULL), _p_instance(p_instance)
   {
       CreateOleAdviseHolder(&_p_advise_holder);
   }

   ole_object::~ole_object()
   {
       SetClientSite(NULL);
       Close(OLECLOSE_NOSAVE);
       _p_advise_holder->Release();
   }

   STDMETHODIMP ole_object::Advise(IAdviseSink *pAdvSink, DWORD *dwConnection)
   {
       return _p_advise_holder->Advise(pAdvSink, dwConnection);
   }

   STDMETHODIMP ole_object::Close(DWORD dwSaveOption)
   {
       {
           _p_advise_holder->SendOnClose();
           return _p_instance->onClose(dwSaveOption);     
       }
       return S_OK;
   }

   STDMETHODIMP ole_object::DoVerb(LONG iVerb, LPMSG lpMsg, LPOLECLIENTSITE pActiveSite,
                                       LONG lIndex, HWND hwndParent, LPCRECT lprcPosRect)
   {
       switch( iVerb )
       {
           case OLEIVERB_PRIMARY:
           case OLEIVERB_SHOW:
           case OLEIVERB_OPEN:
               // force control to be visible when activating in place
               return doInPlaceActivate(lpMsg, pActiveSite, hwndParent, lprcPosRect, TRUE);

           case OLEIVERB_INPLACEACTIVATE:
               return doInPlaceActivate(lpMsg, pActiveSite, hwndParent, lprcPosRect, FALSE);

           case OLEIVERB_HIDE:
               return S_OK;

           case OLEIVERB_UIACTIVATE:
               // UI activate only if visible
               if( true )
                   return doInPlaceActivate(lpMsg, pActiveSite, hwndParent, lprcPosRect, TRUE);
               return OLEOBJ_S_CANNOT_DOVERB_NOW;

           case OLEIVERB_DISCARDUNDOSTATE:
               return S_OK;

           default:
               if( iVerb > 0 ) {
                   doInPlaceActivate(lpMsg, pActiveSite, hwndParent, lprcPosRect, TRUE);
                   return OLEOBJ_S_INVALIDVERB;
               }
               return E_NOTIMPL;
       }
   }

   HRESULT ole_object::doInPlaceActivate(LPMSG lpMsg, LPOLECLIENTSITE pActiveSite, HWND hwndParent, LPCRECT lprcPosRect, BOOL uiActivate)
   {
       RECT posRect;
       RECT clipRect;
       LPCRECT lprcClipRect = lprcPosRect;
    

      if( pActiveSite )
       {
           LPOLEINPLACESITE p_inPlaceSite = NULL;
           IOleInPlaceSiteEx *p_inPlaceSiteEx = NULL;
           LPOLEINPLACEFRAME p_inPlaceFrame = NULL;
           LPOLEINPLACEUIWINDOW p_inPlaceUIWindow = NULL;

           if( FAILED(pActiveSite->QueryInterface(IID_IOleInPlaceSiteEx, reinterpret_cast<void**>(&p_inPlaceSiteEx))) )
           {
              return E_FAIL;
           }
        
           p_inPlaceSite = p_inPlaceSiteEx;
           p_inPlaceSite->AddRef();
           if(FAILED(pActiveSite->QueryInterface(IID_IOleInPlaceSite, reinterpret_cast<void**>(&p_inPlaceSite)) ))
           {
               p_inPlaceSite = p_inPlaceSiteEx = NULL;
           }
           if(FAILED(pActiveSite->QueryInterface(&_p_instance->m_psite)))
           {
               if( p_inPlaceSiteEx )
                   p_inPlaceSiteEx->Release();
               if( p_inPlaceFrame )
                   p_inPlaceFrame->Release();
               if( p_inPlaceUIWindow )
                   p_inPlaceUIWindow->Release();
              return E_FAIL;
           }
           if(_p_instance->m_psite->CanWindowlessActivate() != S_OK)
           {
               if( p_inPlaceSiteEx )
                   p_inPlaceSiteEx->Release();
               if( p_inPlaceFrame )
                   p_inPlaceFrame->Release();
               if( p_inPlaceUIWindow )
                   p_inPlaceUIWindow->Release();
               return E_FAIL;
           }
           _p_instance->m_hwndSite = NULL;
           _p_instance->m_psite->GetWindow(&_p_instance->m_hwndSite);

           if( p_inPlaceSite )
           {
               OLEINPLACEFRAMEINFO oleFrameInfo;

               oleFrameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);
               if( SUCCEEDED(p_inPlaceSite->GetWindowContext(&p_inPlaceFrame, &p_inPlaceUIWindow, &posRect, &clipRect, &oleFrameInfo)) )
               {
                   lprcPosRect = &posRect;
                   lprcClipRect = &clipRect;
               }

               if( (NULL == hwndParent) && FAILED(p_inPlaceSite->GetWindow(&hwndParent)) )
               {
                   p_inPlaceSite->Release();
                   if( p_inPlaceSiteEx )
                       p_inPlaceSiteEx->Release();
                   if( p_inPlaceFrame )
                       p_inPlaceFrame->Release();
                   if( p_inPlaceUIWindow )
                       p_inPlaceUIWindow->Release();

                   return OLEOBJ_S_INVALIDHWND;
               }
           }
           else if( NULL == hwndParent )
           {
               return OLEOBJ_S_INVALIDHWND;
           }
           else if( NULL == lprcPosRect )
           {
               SetRect(&posRect, 0, 0, 0, 0);
               lprcPosRect = &posRect;
               lprcClipRect = &posRect;
           }

           // check if not already activated
           if( ! _p_instance->isInPlaceActive() )
           {
               if( ((NULL == p_inPlaceSite) || (S_OK == p_inPlaceSite->CanInPlaceActivate()))
                && SUCCEEDED(_p_instance->onActivateInPlace(lpMsg, hwndParent, lprcPosRect, lprcClipRect)) )
               {
                   if( p_inPlaceSiteEx )
                   {
                       BOOL needsRedraw;
                       p_inPlaceSiteEx->OnInPlaceActivateEx(&needsRedraw, ACTIVATE_WINDOWLESS );
                   }
                   else if( p_inPlaceSite )
                       p_inPlaceSite->OnInPlaceActivate();
               }
               else
               {
                   if( p_inPlaceSite )
                   {
                       p_inPlaceSite->Release();
                       if( p_inPlaceSiteEx )
                           p_inPlaceSiteEx->Release();
                       if( p_inPlaceFrame )
                           p_inPlaceFrame->Release();
                       if( p_inPlaceUIWindow )
                           p_inPlaceUIWindow->Release();
                   }
                   return OLEOBJ_S_CANNOT_DOVERB_NOW;
               }
           }

           if( p_inPlaceSite )
               p_inPlaceSite->OnPosRectChange(lprcPosRect);

           if( uiActivate )
           {
               if( (NULL == p_inPlaceSiteEx) || (S_OK == p_inPlaceSiteEx->RequestUIActivate()) )
               {
                   if( p_inPlaceSite)
                   {
                       p_inPlaceSite->OnUIActivate();

                       LPOLEINPLACEACTIVEOBJECT p_inPlaceActiveObject;
                       if( SUCCEEDED(QueryInterface(IID_IOleInPlaceActiveObject, reinterpret_cast<void**>(&p_inPlaceActiveObject))) )
                       {
                           if( p_inPlaceFrame )
                               p_inPlaceFrame->SetActiveObject(p_inPlaceActiveObject, NULL);
                           if( p_inPlaceUIWindow )
                               p_inPlaceUIWindow->SetActiveObject(p_inPlaceActiveObject, NULL);
                           p_inPlaceActiveObject->Release();
                       }
                       if( p_inPlaceFrame )
                           p_inPlaceFrame->RequestBorderSpace(NULL);

                       pActiveSite->ShowObject();
                   }
                   _p_instance->setFocus(TRUE);
               }
           }

           if( p_inPlaceSite )
           {
               p_inPlaceSite->Release();
               if( p_inPlaceSiteEx )
                   p_inPlaceSiteEx->Release();
               if( p_inPlaceFrame )
                   p_inPlaceFrame->Release();
               if( p_inPlaceUIWindow )
                   p_inPlaceUIWindow->Release();
           }
           return S_OK;
       }
       return OLEOBJ_S_CANNOT_DOVERB_NOW;
   }

   STDMETHODIMP ole_object::EnumAdvise(IEnumSTATDATA **ppEnumAdvise)
   {
       return _p_advise_holder->EnumAdvise(ppEnumAdvise);
   }

   STDMETHODIMP ole_object::EnumVerbs(IEnumOLEVERB **ppEnumOleVerb)
   {
       return OleRegEnumVerbs(_p_instance->getClassID(),
           ppEnumOleVerb);
   }

   STDMETHODIMP ole_object::GetClientSite(LPOLECLIENTSITE *ppClientSite)
   {
       if( NULL == ppClientSite )
           return E_POINTER;

       if( NULL != _p_clientsite )
           _p_clientsite->AddRef();

       *ppClientSite = _p_clientsite;
       return S_OK;
   }

   STDMETHODIMP ole_object::GetClipboardData(DWORD dwReserved, LPDATAOBJECT *ppDataObject)
   {
       return _p_instance->pUnkOuter->QueryInterface(IID_IDataObject, (void **)ppDataObject);
   }

   STDMETHODIMP ole_object::GetExtent(DWORD dwDrawAspect, SIZEL *pSizel)
   {
       if( NULL == pSizel )
           return E_POINTER;

       if( dwDrawAspect & DVASPECT_CONTENT )
       {
           *pSizel = _p_instance->getExtent();
           return S_OK;
       }
       pSizel->cx= 0L;
       pSizel->cy= 0L;
       return E_NOTIMPL;
   }

   STDMETHODIMP ole_object::GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus)
   {
       if( NULL == pdwStatus )
           return E_POINTER;

       switch( dwAspect )
       {
           case DVASPECT_CONTENT:
               *pdwStatus = OLEMISC_RECOMPOSEONRESIZE
                   | OLEMISC_CANTLINKINSIDE
                   | OLEMISC_INSIDEOUT
                   | OLEMISC_ACTIVATEWHENVISIBLE
                   | OLEMISC_SETCLIENTSITEFIRST;
               break;
           default:
               *pdwStatus = 0;
       }

       return S_OK;
   }

   STDMETHODIMP ole_object::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER *ppMoniker)
   {
       if( NULL != _p_clientsite )
           return _p_clientsite->GetMoniker(dwAssign,dwWhichMoniker, ppMoniker);

       return E_UNEXPECTED;
   }

   STDMETHODIMP ole_object::GetUserClassID(LPCLSID pClsid)
   {
       if( NULL == pClsid )
           return E_POINTER;
 
       *pClsid = _p_instance->getClassID();
       return S_OK;
   }

   STDMETHODIMP ole_object::GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType)
   {
       return OleRegGetUserType(_p_instance->getClassID(),
           dwFormOfType, pszUserType);
   }

   STDMETHODIMP ole_object::InitFromData(LPDATAOBJECT pDataObject, BOOL fCreation, DWORD dwReserved)
   {
       return E_NOTIMPL;
   }

   STDMETHODIMP ole_object::IsUpToDate(void)
   {
       return S_OK;
   }

   STDMETHODIMP ole_object::SetClientSite(LPOLECLIENTSITE pClientSite)
   {
       if( NULL != _p_clientsite )
           _p_clientsite->Release();

       _p_clientsite = pClientSite;

       if( NULL != pClientSite )
       {
           pClientSite->AddRef();
           _p_instance->onAmbientChanged(pClientSite, DISPID_UNKNOWN);
       }

      if (pClientSite != NULL)
      {
         // Obtain URL from container moniker.
         IMoniker * spmk;
         LPOLESTR pszDisplayName;

         if (SUCCEEDED(pClientSite->GetMoniker(
                                       OLEGETMONIKER_TEMPFORUSER,
                                       OLEWHICHMK_CONTAINER,
                                       &spmk)))
         {
            if (SUCCEEDED(spmk->GetDisplayName(
                                    NULL, NULL, &pszDisplayName)))
            {
               _p_instance->m_strHostPluginLocation.attach(utf16_to_8(pszDisplayName));
               CoTaskMemFree((LPVOID)pszDisplayName);
            }
            spmk->Release();
         }
      }
       return S_OK;
   }

   STDMETHODIMP ole_object::SetColorScheme(LOGPALETTE *pLogpal)
   {
       return E_NOTIMPL;
   }

   STDMETHODIMP ole_object::SetExtent(DWORD dwDrawAspect, SIZEL *pSizel)
   {
       if( NULL == pSizel )
           return E_POINTER;

       if( dwDrawAspect & DVASPECT_CONTENT )
       {
           _p_instance->setExtent(*pSizel);

           if( _p_instance->isInPlaceActive() )
           {
               LPOLEINPLACESITE p_inPlaceSite;

               if( SUCCEEDED(_p_clientsite->QueryInterface(IID_IOleInPlaceSite, (void**)&p_inPlaceSite)) )
               {
                   HWND hwnd;

                   if( SUCCEEDED(p_inPlaceSite->GetWindow(&hwnd)) )
                   {
                       // use HIMETRIC to pixel transform
                       RECT posRect = _p_instance->getPosRect();
                       HDC hDC = GetDC(hwnd);
                       posRect.right = (pSizel->cx*GetDeviceCaps(hDC, LOGPIXELSX)/2540L)+posRect.left;
                       posRect.bottom = (pSizel->cy*GetDeviceCaps(hDC, LOGPIXELSY)/2540L)+posRect.top;
                       DeleteDC(hDC);
                       p_inPlaceSite->OnPosRectChange(&posRect);
                   }
                   p_inPlaceSite->Release();
               }
           }
           return S_OK;
       }
       return E_NOTIMPL;
   }

   STDMETHODIMP ole_object::SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
   {
       return S_OK;
   }

   STDMETHODIMP ole_object::SetMoniker(DWORD dwWhichMoniker, LPMONIKER pMoniker)
   {
       return _p_advise_holder->SendOnRename(pMoniker);
   }

   STDMETHODIMP ole_object::Unadvise(DWORD dwConnection)
   {
       return _p_advise_holder->Unadvise(dwConnection);
   }

   STDMETHODIMP ole_object::Update(void)
   {
       return S_OK;
   }


} // namespace iexca2

