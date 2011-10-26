/*****************************************************************************
 * persiststreaminit.cpp: Free ActiveX based on ActiveX control for VLC
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

   class variant
   {

   public:

       variant(void)
       {
           VariantInit(&_v);
       }

       ~variant(void)
       {
           VariantClear(&_v);
       }

       variant(VARIANTARG &v)
       {
           VariantInit(&_v);
           VariantCopy(&_v, &v);
       }

       variant(VARIANTARG *v)
       {
           VariantInit(&_v);
           VariantCopy(&_v, v);
       }

       variant(const variant &vv)
       {
           VariantInit(&_v);
           VariantCopy(&_v, const_cast<VARIANTARG *>(&(vv._v)));
       }

       variant(int i)
       {
           V_VT(&_v) = VT_I4;
           V_I4(&_v) = i;
       }

       variant(BSTR bstr)
       {
           VARIANT arg;
           V_VT(&arg) = VT_BSTR;
           V_BSTR(&arg) = bstr;
           VariantInit(&_v);
           VariantCopy(&_v, &arg);
       }

       inline const VARIANTARG *variantArg(void) const {
           return &_v;
       }

       inline void swap(variant &v1, variant &v2)
       {
           VARIANTARG tmp = v1._v;
           v1._v = v2._v;
           v2._v = tmp;
       }

   private:

       VARIANTARG _v;
   };


   typedef simple_attrib_map < wstring, variant>::pair AxVLCPropertyPair;
   typedef simple_attrib_map < wstring, variant> AxVLCPropertyMap;

   ///////////////////////////

   class VLCPropertyBag : public IPropertyBag
   {

   public:

       VLCPropertyBag(void) : _i_ref(1) {}
       virtual ~VLCPropertyBag() {}

       // IUnknown methods
       STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
       {
           if( NULL == ppv )
               return E_POINTER;
           if( (IID_IUnknown == riid)
            || (IID_IPropertyBag == riid) )
           {
               AddRef();
               *ppv = reinterpret_cast<LPVOID>(this);
               return NOERROR;
           }
           // standalone object
           return E_NOINTERFACE;
       }

       STDMETHODIMP_(ULONG) AddRef(void)
           { return InterlockedIncrement(&_i_ref); }

       STDMETHODIMP_(ULONG) Release(void)
       {
           ULONG refcount = InterlockedDecrement(&_i_ref);
           if( 0 == refcount )
           {
               delete this;
               return 0;
           }
           return refcount;
       }

       // IPropertyBag methods

       STDMETHODIMP Read(LPCOLESTR pszPropName, VARIANT *pVar, IErrorLog *pErrorLog)
       {
           if( (NULL == pszPropName) || (NULL == pVar) )
               return E_POINTER;

           wstring axPropName(pszPropName);
           AxVLCPropertyPair * ppair = _pm.PLookup(axPropName);
           if(ppair != NULL)
           {
               VARTYPE vtype = V_VT(pVar);
               VARIANTARG v;
               VariantInit(&v);
               VariantCopy(&v, const_cast<VARIANTARG*>(ppair->m_value.variantArg()));
               if( (V_VT(&v) != vtype) && FAILED(VariantChangeType(&v, &v, 0, vtype)) )
               {
                   VariantClear(&v);
                   return E_FAIL;
               }
               *pVar = v;
               return S_OK;
           }
           else
               return E_INVALIDARG;
       }
 
       STDMETHODIMP Write(LPCOLESTR pszPropName, VARIANT *pVar)
       {
           if( (NULL == pszPropName) || (NULL == pVar) )
               return E_POINTER;

           _pm.set_at(pszPropName, pVar);
           return S_OK;
       }

       // custom methods

       HRESULT Load(LPSTREAM pStm)
       {
           if( NULL == pStm )
               return E_INVALIDARG;

           HRESULT result;

           AxVLCPropertyPair *val;
           result = ReadProperty(pStm, &val);
           if( SUCCEEDED(result) )
           {
               if( (val->m_key == L"(Count)") && (VT_I4 == V_VT(val->m_value.variantArg())) )
               {
                   size_t count = V_I4(val->m_value.variantArg());
                   delete val;
                   while( count-- )
                   {
                       result = ReadProperty(pStm, &val);
                       if( FAILED(result) )
                           return result;

                       _pm.set_at(L"(Count)", val->m_value);
                       delete val;
                   }
               }
           }
           return result;
       }

       HRESULT Save(LPSTREAM pStm)
       {
           if( NULL == pStm )
               return E_INVALIDARG;

           HRESULT result;

           AxVLCPropertyPair header(L"(Count)");
           header.m_value = _pm.get_count();
           result = WriteProperty(pStm, header);


           wstring key;
           variant value;

           if( SUCCEEDED(result) )
           {
              simple_attrib_map < wstring, variant>::pair * ppair = _pm.PGetFirstAssoc();
               while(ppair != NULL)
               {
                   result = WriteProperty(pStm, *ppair);
                   if( FAILED(result) )
                       return result;
                   ppair = _pm.PGetNextAssoc(ppair);
               }
           }
           return result;
       }

       BOOL IsEmpty()
       {
           return _pm.get_count() == 0;
       }

   private:

       HRESULT WriteProperty(LPSTREAM pStm, const AxVLCPropertyPair &prop)
       {
           HRESULT result;

           const wstring propName = prop.m_key;

           ULONG len = propName.size();

           if( 0 == len )
               return E_INVALIDARG;

           result = pStm->Write(&len, sizeof(len), NULL);
           if( FAILED(result) )
               return result;

           result = pStm->Write(propName, len*sizeof(WCHAR), NULL);
           if( FAILED(result) )
               return result;

           const VARIANTARG *propValue = prop.m_value.variantArg();
           VARTYPE vtype = V_VT(propValue);
           switch( vtype )
           {
               case VT_BOOL:
                   result = pStm->Write(&vtype, sizeof(vtype), NULL);
                   if( FAILED(result) )
                       return result;
                   result = pStm->Write(&V_BOOL(propValue), sizeof(V_BOOL(propValue)), NULL);
                   if( FAILED(result) )
                       return result;
                   break;
               case VT_I4:
                   result = pStm->Write(&vtype, sizeof(vtype), NULL);
                   if( FAILED(result) )
                       return result;
                   result = pStm->Write(&V_I4(propValue), sizeof(V_I4(propValue)), NULL);
                   if( FAILED(result) )
                       return result;
                   break;
               case VT_BSTR:
                   result = pStm->Write(&vtype, sizeof(vtype), NULL);
                   if( FAILED(result) )
                       return result;
                   len = SysStringLen(V_BSTR(propValue));
                   result = pStm->Write(&len, sizeof(len), NULL);
                   if( FAILED(result) )
                       return result;
                   if( len > 0 )
                   {
                       result = pStm->Write(V_BSTR(propValue), len*sizeof(OLECHAR), NULL);
                       if( FAILED(result) )
                           return result;
                   }
                   break;
               default:
                   vtype = VT_EMPTY;
                   result = pStm->Write(&vtype, sizeof(vtype), NULL);
                   if( FAILED(result) )
                       return result;
           }
           return result;
       }

       HRESULT ReadProperty(LPSTREAM pStm, AxVLCPropertyPair **prop)
       {
           HRESULT result;

           ULONG len;

           result = pStm->Read(&len, sizeof(len), NULL);
           if( FAILED(result) )
               return result;

           if( 0 == len )
               return E_INVALIDARG;

           wstring propName;
           propName.alloc(len + 1);
           if( NULL == propName )
               return E_OUTOFMEMORY;

           result = pStm->Read((void *) (const wchar_t *) propName, len*sizeof(WCHAR), NULL);
           if( FAILED(result) )
               return result;

           ((wchar_t *) (const wchar_t *) propName)[len] = L'\0';

           VARIANTARG propValue;

           VARTYPE vtype;
           result = pStm->Read(&vtype, sizeof(vtype), NULL);
           if( FAILED(result) )
               return result;

           switch( vtype )
           {
               case VT_BOOL:
                   V_VT(&propValue) = vtype;
                   result = pStm->Read(&V_BOOL(&propValue), sizeof(V_BOOL(&propValue)), NULL);
                   if( FAILED(result) )
                       return result;
                   break;
               case VT_I4:
                   V_VT(&propValue) = vtype;
                   result = pStm->Read(&V_I4(&propValue), sizeof(V_I4(&propValue)), NULL);
                   if( FAILED(result) )
                       return result;
                   break;
               case VT_BSTR:
                   V_VT(&propValue) = vtype;
                   result = pStm->Read(&len, sizeof(len), NULL);
                   if( FAILED(result) )
                       return result;

                   V_BSTR(&propValue) = NULL;
                   if( len > 0 )
                   {
                       V_BSTR(&propValue) = SysAllocStringLen(NULL, len);
                       if( NULL == V_BSTR(&propValue) )
                           return E_OUTOFMEMORY;

                       result = pStm->Read(V_BSTR(&propValue), len*sizeof(OLECHAR), NULL);
                       if( FAILED(result) )
                       {
                           SysFreeString(V_BSTR(&propValue));
                           return result;
                       }
                   }
                   break;
               default:
                   VariantInit(&propValue);
           }

           *prop = new AxVLCPropertyPair((LPCWSTR)propName);
           (*prop)->m_value = propValue;


           return S_OK;
       }

       AxVLCPropertyMap _pm;
       LONG _i_ref;
   };

   ///////////////////////////

   persist_stream_init::persist_stream_init(host *p_instance) : _p_instance(p_instance)
   {
       _p_props = new VLCPropertyBag();
   }

   persist_stream_init::~persist_stream_init()
   {
       _p_props->Release();
   }

   STDMETHODIMP persist_stream_init::GetClassID(LPCLSID pClsID)
   {
       if( NULL == pClsID )
           return E_POINTER;

       *pClsID = _p_instance->getClassID();

       return S_OK;
   }

   STDMETHODIMP persist_stream_init::InitNew(void)
   {
       return _p_instance->onInit();
   }

   STDMETHODIMP persist_stream_init::Load(LPSTREAM pStm)
   {
       HRESULT result = _p_props->Load(pStm);
       if( FAILED(result) )
           return result;

       LPPERSISTPROPERTYBAG pPersistPropBag;
       if( FAILED(QueryInterface(IID_IPersistPropertyBag, (void**)&pPersistPropBag)) )
           return E_FAIL;

       result = pPersistPropBag->Load(_p_props, NULL);
       pPersistPropBag->Release();

       return result;
   }

   STDMETHODIMP persist_stream_init::Save(LPSTREAM pStm, BOOL fClearDirty)
   {
       if( NULL == pStm )
           return E_INVALIDARG;

       LPPERSISTPROPERTYBAG pPersistPropBag;
       if( FAILED(QueryInterface(IID_IPersistPropertyBag, (void**)&pPersistPropBag)) )
           return E_FAIL;

       HRESULT result = pPersistPropBag->Save(_p_props, fClearDirty, _p_props->IsEmpty());
       pPersistPropBag->Release();
       if( FAILED(result) )
           return result;

       return _p_props->Save(pStm);
   }

   STDMETHODIMP persist_stream_init::IsDirty(void)
   {
       return _p_instance->isDirty() ? S_OK : S_FALSE;
   }

   STDMETHODIMP persist_stream_init::GetSizeMax(ULARGE_INTEGER *pcbSize)
   {
       pcbSize->HighPart = 0UL;
       pcbSize->LowPart  = 16384UL; // just a guess

       return S_OK;
   }

 } // namespace iexca2