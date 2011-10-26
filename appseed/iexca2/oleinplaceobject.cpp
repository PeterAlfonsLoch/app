/*****************************************************************************
 * oleinplaceobject.cpp: Free ActiveX based on ActiveX control for VLC
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

   STDMETHODIMP ole_inplace_object::GetWindow(HWND *pHwnd)
   {
       if( NULL == pHwnd )
           return E_POINTER;

       *pHwnd = NULL;
       if( _p_instance->isInPlaceActive() )
       {
           if( NULL != (*pHwnd = _p_instance->getInPlaceWindow()) )
               return S_OK;
       }
       return E_FAIL;
   }

   STDMETHODIMP ole_inplace_object::ContextSensitiveHelp(BOOL fEnterMode)
   {
       return E_NOTIMPL;
   }

   STDMETHODIMP ole_inplace_object::InPlaceDeactivate(void)
   {
       if( _p_instance->isInPlaceActive() )
       {
           UIDeactivate();

           _p_instance->onInPlaceDeactivate();

           LPOLEOBJECT p_oleObject;
           if( SUCCEEDED(QueryInterface(IID_IOleObject, (void**)&p_oleObject)) )
           {
               LPOLECLIENTSITE p_clientSite;
               if( SUCCEEDED(p_oleObject->GetClientSite(&p_clientSite)) )
               {
                   LPOLEINPLACESITE p_inPlaceSite;

                   if( SUCCEEDED(p_clientSite->QueryInterface(IID_IOleInPlaceSite, (void**)&p_inPlaceSite)) )
                   {
                       p_inPlaceSite->OnInPlaceDeactivate();
                       p_inPlaceSite->Release();
                   }
                   p_clientSite->Release();
               }
               p_oleObject->Release();
           }
           return S_OK;
       }
       return E_UNEXPECTED;
   }

   STDMETHODIMP ole_inplace_object::UIDeactivate(void)
   {
       if( _p_instance->isInPlaceActive() )
       {
           if( _p_instance->hasFocus() )
               _p_instance->setFocus(FALSE);

           LPOLEOBJECT p_oleObject;
           if( SUCCEEDED(QueryInterface(IID_IOleObject, (void**)&p_oleObject)) )
           {
               LPOLECLIENTSITE p_clientSite;
               if( SUCCEEDED(p_oleObject->GetClientSite(&p_clientSite)) )
               {
                   LPOLEINPLACESITE p_inPlaceSite;

                   if( SUCCEEDED(p_clientSite->QueryInterface(IID_IOleInPlaceSite, (void**)&p_inPlaceSite)) )
                   {
                       LPOLEINPLACEFRAME p_inPlaceFrame;
                       LPOLEINPLACEUIWINDOW p_inPlaceUIWindow;
                       OLEINPLACEFRAMEINFO oleFrameInfo;
                       RECT posRect, clipRect;

                       oleFrameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);
                       if( SUCCEEDED(p_inPlaceSite->GetWindowContext(&p_inPlaceFrame, &p_inPlaceUIWindow, &posRect, &clipRect, &oleFrameInfo)) )
                       {
                           if( p_inPlaceFrame )
                           {
                               p_inPlaceFrame->SetActiveObject(NULL, NULL);
                               p_inPlaceFrame->Release();
                           }
                           if( p_inPlaceUIWindow )
                           {
                               p_inPlaceUIWindow->SetActiveObject(NULL, NULL);
                               p_inPlaceUIWindow->Release();
                           }
                       }
                       p_inPlaceSite->OnUIDeactivate(FALSE);
                       p_inPlaceSite->Release();
                   }
                   p_clientSite->Release();
               }
               p_oleObject->Release();
           }
           return S_OK;
       }
       return E_UNEXPECTED;
   }

   STDMETHODIMP ole_inplace_object::SetObjectRects(LPCRECT lprcPosRect, LPCRECT lprcClipRect)
   {
       if( _p_instance->isInPlaceActive() )
       {
           _p_instance->onPositionChange(lprcPosRect, lprcClipRect);
           return S_OK;
       }
       return E_UNEXPECTED;
   }

   STDMETHODIMP ole_inplace_object::ReactivateAndUndo(void)
   {
       return INPLACE_E_NOTUNDOABLE;
   }


} // namespace iexca2