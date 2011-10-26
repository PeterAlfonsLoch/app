/*****************************************************************************
* viewobject.cpp: Free ActiveX based on ActiveX control for VLC
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

   STDMETHODIMP view_object::Draw(DWORD dwAspect, LONG lindex, PVOID pvAspect,
      DVTARGETDEVICE *ptd, HDC hicTargetDev, HDC hdcDraw, LPCRECTL lprcBounds,
      LPCRECTL lprcWBounds, BOOL(CALLBACK *pfnContinue)(ULONG_PTR), ULONG_PTR dwContinue)
   {

      if( dwAspect & DVASPECT_CONTENT )
      {
         int iDC = 0;
         if(lprcWBounds != NULL)
         {
            SIZEL size = _p_instance->getExtent();
            iDC = ::SaveDC(hdcDraw);
            // needs to scale canvas
            SetMapMode(hdcDraw, MM_TEXT);
            SetWindowOrgEx(hdcDraw, 0, 0, NULL);
            SetWindowExtEx(hdcDraw, size.cx, size.cy, NULL);
            OffsetViewportOrgEx(hdcDraw, lprcWBounds->left, lprcWBounds->right, NULL);
            SetViewportExtEx(hdcDraw, lprcWBounds->right - lprcWBounds->left, lprcWBounds->bottom - lprcWBounds->top, NULL);
         }
      
         _p_instance->onDraw(ptd, hicTargetDev, hdcDraw, lprcBounds, lprcWBounds);

         if(lprcWBounds != NULL)
         {
            ::RestoreDC(hdcDraw, iDC);
         }

         return S_OK;
      }
      return E_NOTIMPL;
   }

   STDMETHODIMP view_object::Freeze(DWORD dwAspect, LONG lindex,
      PVOID pvAspect, LPDWORD pdwFreeze)
   {
      return E_NOTIMPL;
   }

   STDMETHODIMP view_object::GetAdvise(LPDWORD pdwAspect, LPDWORD padvf,
      LPADVISESINK *ppAdviseSink)
   {
      if( NULL != pdwAspect )
         *pdwAspect = _dwAspect;

      if( NULL != padvf )
         *padvf = _advf;

      if( NULL != ppAdviseSink )
      {
         *ppAdviseSink = _pAdvSink;
         if( NULL != _pAdvSink )
            _pAdvSink->AddRef();
      }

      return S_OK;
   }

   STDMETHODIMP view_object::GetColorSet(DWORD dwAspect, LONG lindex,
      PVOID pvAspect, DVTARGETDEVICE *ptd, HDC hicTargetDev, LPLOGPALETTE *ppColorSet)
   {
      return S_FALSE;
   }

   STDMETHODIMP view_object::SetAdvise(DWORD dwAspect, DWORD advf,
      LPADVISESINK pAdvSink)
   {
      if( NULL != pAdvSink )
         pAdvSink->AddRef();

      if( NULL != _pAdvSink )
         _pAdvSink->Release();

      _dwAspect = dwAspect;
      _advf = advf;
      _pAdvSink = pAdvSink;

      if( (dwAspect & DVASPECT_CONTENT) && (advf & ADVF_PRIMEFIRST) && (NULL != _pAdvSink) )
      {
         _pAdvSink->OnViewChange(DVASPECT_CONTENT, -1);
      }

      return S_OK;
   }

   STDMETHODIMP view_object::Unfreeze(DWORD dwFreeze)
   {
      return E_NOTIMPL;
   }

   STDMETHODIMP view_object::GetExtent(DWORD dwAspect, LONG lindex,
      DVTARGETDEVICE *ptd, LPSIZEL lpSizel)
   {
      if( dwAspect & DVASPECT_CONTENT )
      {
         *lpSizel = _p_instance->getExtent();
         return S_OK;
      }
      lpSizel->cx= 0L;
      lpSizel->cy= 0L;
      return E_NOTIMPL;
   }

} // namespace iexca2