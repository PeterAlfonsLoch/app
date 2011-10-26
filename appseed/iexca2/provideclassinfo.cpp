/*****************************************************************************
 * provideclassinfo.cpp: Free ActiveX based on ActiveX control for VLC
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

   STDMETHODIMP provide_class_info::GetClassInfo(ITypeInfo **ppTI)
   {
       ITypeLib *p_typelib;

       if( NULL == ppTI )
           return E_POINTER;

       HRESULT hr = _p_instance->getTypeLib(LOCALE_NEUTRAL, &p_typelib);
       if( SUCCEEDED(hr) )
       {
           hr = p_typelib->GetTypeInfoOfGuid(_p_instance->getClassID(), ppTI);
           if( FAILED(hr) )
           {
               *ppTI = NULL;
           }
           p_typelib->Release();
       }
       return hr;
   }

   STDMETHODIMP provide_class_info::GetGUID(DWORD dwGuidKind, GUID *pGUID)
   {
       if( GUIDKIND_DEFAULT_SOURCE_DISP_IID != dwGuidKind )
           return E_INVALIDARG;

       if( NULL == pGUID )
           return E_POINTER;

       *pGUID = _p_instance->getDispEventID();

       return S_OK;
   }

} // namespace iexca2