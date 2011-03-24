/*****************************************************************************
 * vlccontrol.h: Free ActiveX based on ActiveX control for VLC
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

#ifndef _VLCCONTROL2_H_
#define _VLCCONTROL2_H_

#include "iexca2_h.h"

class AXControl : public IAXControl
{
public:

    AXControl(VLCPlugin *p_instance);
    virtual ~AXControl();

    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if( NULL == ppv )
          return E_POINTER;
        if( (IID_IUnknown == riid)
         || (IID_IDispatch == riid)
         || (IID_IAXControl == riid) )
        {
            AddRef();
            *ppv = reinterpret_cast<LPVOID>(this);
            return NOERROR;
        }
        return _p_instance->pUnkOuter->QueryInterface(riid, ppv);
    };

    STDMETHODIMP_(ULONG) AddRef(void) { return _p_instance->pUnkOuter->AddRef(); };
    STDMETHODIMP_(ULONG) Release(void) { return _p_instance->pUnkOuter->Release(); };

    // IDispatch methods
    STDMETHODIMP GetTypeInfoCount(UINT*);
    STDMETHODIMP GetTypeInfo(UINT, LCID, LPTYPEINFO*);
    STDMETHODIMP GetIDsOfNames(REFIID,LPOLESTR*,UINT,LCID,DISPID*);
    STDMETHODIMP Invoke(DISPID,REFIID,LCID,WORD,DISPPARAMS*,VARIANT*,EXCEPINFO*,UINT*);


    // AXControl 
    // set test string from parent application
    virtual HRESULT STDMETHODCALLTYPE put_TestString( BSTR str );
    // get test string from parent application
    virtual HRESULT STDMETHODCALLTYPE get_TestString( BSTR *str );
    // show/hide activex window
    virtual HRESULT STDMETHODCALLTYPE SetVisible( 
            VARIANT_BOOL isShow);

protected:
    HRESULT loadTypeInfo();

private:
    VLCPlugin*      _p_instance;
    ITypeInfo*      _p_typeinfo;

};

#endif
