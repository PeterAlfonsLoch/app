/*****************************************************************************
 * objectsafety.cpp: Free ActiveX based on ActiveX control for VLC
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


   STDMETHODIMP object_safety::GetInterfaceSafetyOptions(
       REFIID riid,
       DWORD *pdwSupportedOptions,
       DWORD *pdwEnabledOptions
   )
   {
       if( (NULL == pdwSupportedOptions) || (NULL == pdwEnabledOptions) )
           return E_POINTER;

       *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACESAFE_FOR_UNTRUSTED_CALLER;

       if( (IID_IDispatch == riid)
        || (IID_iexca2_control_interface == riid) )
       {
           *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
           return NOERROR;
       }
       else if( (IID_IPersist == riid)
             || (IID_IPersistStreamInit == riid)
             || (IID_IPersistStorage == riid)
             || (IID_IPersistPropertyBag == riid) )
       {
           *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
           return NOERROR;
       }
       *pdwEnabledOptions = 0;
       return E_NOINTERFACE;
   };

   STDMETHODIMP object_safety::SetInterfaceSafetyOptions(
       REFIID riid,
       DWORD dwOptionSetMask,
       DWORD dwEnabledOptions
   )
   {
       if( (IID_IDispatch == riid)
        || (IID_iexca2_control_interface == riid) )
       {
           if( (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask)
            && (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions) )
           {
               return NOERROR;
           }
           return E_FAIL;
       }
       else if( (IID_IPersist == riid)
             || (IID_IPersistStreamInit == riid)
             || (IID_IPersistStorage == riid)
             || (IID_IPersistPropertyBag == riid) )
       {
           if( (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask)
            && (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions) )
           {
               return NOERROR;
           }
           return E_FAIL;
       }
       return E_FAIL;
   };

} // namespace iexca2