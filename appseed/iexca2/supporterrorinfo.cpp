/*****************************************************************************
 * supporterrorinfo.cpp: Free ActiveX based on ActiveX control for VLC
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


   STDMETHODIMP support_error_info::InterfaceSupportsErrorInfo(REFIID  riid)
   {
       if((riid == IID_iexca2_control_interface) )
       {
           return S_OK;
       }
       return S_FALSE;
   }

   void support_error_info::setErrorInfo(LPCOLESTR progid, REFIID riid, const char *description)
   {
       BSTR bstrDescription = BSTRFromCStr(CP_UTF8, description);
       if( NULL != bstrDescription )
       {
           ICreateErrorInfo* pcerrinfo;

           HRESULT hr = CreateErrorInfo(&pcerrinfo);
           if( SUCCEEDED(hr) )
           {
               IErrorInfo* perrinfo;

               pcerrinfo->SetSource((LPOLESTR)progid);
               pcerrinfo->SetGUID(riid);
               pcerrinfo->SetDescription((LPOLESTR)bstrDescription);
               hr = pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID*) &perrinfo);
               if( SUCCEEDED(hr) )
               {
                  ::SetErrorInfo(0, perrinfo);
                  perrinfo->Release();
               }
               pcerrinfo->Release();
           }
           SysFreeString(bstrDescription);
       }
   }

} // namespace iexca2