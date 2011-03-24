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


extern UINT g_nCa2StarterStartThreadID;

namespace iexca2
{

   STDMETHODIMP ole_inplace_object_windowless::GetWindow(HWND *pHwnd)
   {
      return E_FAIL;
   };

   STDMETHODIMP ole_inplace_object_windowless::ContextSensitiveHelp(BOOL fEnterMode)
   {
      return E_NOTIMPL;
   };

   STDMETHODIMP ole_inplace_object_windowless::InPlaceDeactivate(void)
   {
      if( m_pinstance->isInPlaceActive() )
      {
         /*        UIDeactivate();

         m_pinstance->onInPlaceDeactivate();

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
         }*/
         return S_OK;
      }
      return E_UNEXPECTED;
   };

   STDMETHODIMP ole_inplace_object_windowless::UIDeactivate(void)
   {
      if( m_pinstance->isInPlaceActive() )
      {
         /*( m_pinstance->hasFocus() )
         m_pinstance->setFocus(FALSE);

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
         }*/
         return S_OK;
      }
      return E_UNEXPECTED;
   };

   STDMETHODIMP ole_inplace_object_windowless::SetObjectRects(LPCRECT lprcPosRect, LPCRECT lprcClipRect)
   {
      if( m_pinstance->isInPlaceActive() )
      {
         m_pinstance->onPositionChange(lprcPosRect, lprcClipRect);
         return S_OK;
      }
      return E_UNEXPECTED;
   };

   STDMETHODIMP ole_inplace_object_windowless::ReactivateAndUndo(void)
   {
      return INPLACE_E_NOTUNDOABLE;
   };

   UINT APIENTRY _ca2_starter_start(void * pParam);
   // IOleInPlaceActiveObject methods
   STDMETHODIMP ole_inplace_object_windowless::OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
   {

      switch( msg )
      {
      case WM_USER + 1984 + 1977:
         {
            KillTimer(m_pinstance->m_hwndSite, 19841977);
            m_pinstance->redraw();
            *plResult = 0;
         }
         break;
      case WM_CREATE:
         {
         
            *plResult = 0;
         }
         break;
         //return //DefWindowProc(hWnd, uMsg, wParam, lParam);
      case WM_USER + 1983 + 1976:
         {
            update_spa_installed();
            if(is_spa_installed())
               update_spa_updated();
            update_ca2_installed();
            if(is_ca2_installed())
               update_ca2_updated();
            if(is_spa_installed() && is_spa_updated() && is_ca2_installed() && is_ca2_installed())
               m_pinstance->npca2_plugin_start_bergedge_cube();
            else
               m_pinstance->starter_start("mplite");
         }
         return 0;
      case WM_ERASEBKGND:
         {
            *plResult = 1;
         }
         break;
      case WM_TIMER:
         {
            if(wParam == 19841977)
            {
               m_pinstance->redraw();
            }
            *plResult = 0;
         }
         break;
      default:
         {
            if((msg == WM_LBUTTONUP
            || msg == WM_RBUTTONUP
            || msg == WM_MBUTTONUP) &&
               is_installing_ca2())
            {
               m_pinstance->m_iHealingSurface++;
            }

            if(m_pinstance->m_puiHost != NULL)
            {

               LPARAM lparam = lParam;
               if(msg >= WM_MOUSEFIRST
                  && msg <= WM_MOUSELAST)
               {
                  point pt = point(lparam);
                  pt.x -= m_pinstance->m_rect.left;
                  pt.y -= m_pinstance->m_rect.top;
                  lparam = pt._001GetLparam();
               }
               if(msg == WM_MOUSEMOVE)
               {
                  ::win::window * pwindow = dynamic_cast < ::win::window * > (m_pinstance->m_puiHost->m_pimpl);
                  pwindow->m_bMouseHover = true; // avoids tracking mouse leave;
               }
               else if(msg == WM_LBUTTONDOWN)
               {
                  m_pinstance->m_psite->SetFocus(TRUE);
               }
               LRESULT l = m_pinstance->m_puiHost->SendMessageA(msg, wParam, lparam);
               *plResult = l;
            }
            else
            {
               *plResult = 0;
            }
      
         }
         break;
      }

      return S_OK;
   }

   STDMETHODIMP ole_inplace_object_windowless::GetDropTarget(IDropTarget **ppDropTarget)
   {
      return E_FAIL;
   }


} // namespace iexca2