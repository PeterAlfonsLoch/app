/*****************************************************************************
 * objectsafety.h: Free ActiveX based on ActiveX control for VLC
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

#pragma once


#if HAVE_OBJSAFE_HEADER
/*
** at last, a version of mingw that supports this header
*/
#include <objsafe.h>

#else
/*
** mingw does not yet support objsafe.h, redefine what we need here
*/

// {CB5BDC81-93C1-11cf-8F20-00805F2CD064}
extern "C" const IID IID_IObjectSafety;

#define INTERFACESAFE_FOR_UNTRUSTED_CALLER 1L
#define INTERFACESAFE_FOR_UNTRUSTED_DATA   2L

struct IObjectSafety : public IUnknown
{
    virtual STDMETHODIMP GetInterfaceSafetyOptions(
        REFIID riid,
        DWORD __RPC_FAR *pdwSupportedOptions,
        DWORD __RPC_FAR *pdwEnabledOptions
    ) = 0;

    virtual STDMETHODIMP SetInterfaceSafetyOptions(
        REFIID riid,
        DWORD dwSupportedOptions,
        DWORD dwOptionSetMask
    ) = 0;
};

#endif


namespace iexca2
{

   class object_safety : public IObjectSafety
   {
   public:

       object_safety(plugin *p_instance) : _p_instance(p_instance) {};
       virtual ~object_safety() {};

       // IUnknown methods
       STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
       {
           if( NULL == ppv)
               return E_POINTER;
           if( (IID_IUnknown == riid)
            || (IID_IObjectSafety == riid) )
           {
               AddRef();
               *ppv = reinterpret_cast<LPVOID>(this);
               return NOERROR;
           }
           return _p_instance->pUnkOuter->QueryInterface(riid, ppv);
       };

       STDMETHODIMP_(ULONG) AddRef(void) { return _p_instance->pUnkOuter->AddRef(); };
       STDMETHODIMP_(ULONG) Release(void) { return _p_instance->pUnkOuter->Release(); };

       // IUnknown methods
       STDMETHODIMP GetInterfaceSafetyOptions(
           REFIID riid,
           DWORD *pdwSupportedOptions,
           DWORD *pdwEnabledOptions
       );

       STDMETHODIMP SetInterfaceSafetyOptions(
           REFIID riid,
           DWORD dwOptionSetMask,
           DWORD dwEnabledOptions
       );

   private:

       plugin *_p_instance;
   };

} // namespace iexca2