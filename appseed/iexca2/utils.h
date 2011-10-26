/*****************************************************************************
 * utils.h: Free ActiveX based on ActiveX control for VLC
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


// utilities
extern char *CStrFromWSTR(UINT codePage, LPCWSTR wstr, UINT len);
extern char *CStrFromBSTR(UINT codePage, BSTR bstr);
extern BSTR BSTRFromCStr(UINT codePage, LPCSTR s);

// properties
extern HRESULT GetObjectProperty(LPUNKNOWN object, DISPID dispID, VARIANT& v);

// properties
extern HDC CreateDevDC(DVTARGETDEVICE *ptd);
extern void DPFromHimetric(HDC hdc, LPPOINT pt, int count);
extern void HimetricFromDP(HDC hdc, LPPOINT pt, int count);

// URL
extern LPWSTR CombineURL(LPCWSTR baseUrl, LPCWSTR url);

/**************************************************************************************************/


template < REFIID EnumeratorIID, class Enumerator, class T >
class simple_enum : 
   public Enumerator,
   public simple_array < T >
{

public:

   simple_enum()
   {
      m_i = 0;
   }

   simple_enum(const simple_enum & a)
   {
      m_i = 0;
      *this = a;
   }

   template < class KEY, class VALUE >
   simple_enum(const simple_map < KEY, VALUE > & map)
   {
      m_i = 0;
      *this = map;
   }

   template < class VAL >
   simple_enum(const simple_array < VAL > & a)
   {
      m_i = 0;
      *this = a;
   }

    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if( NULL == ppv )
            return E_POINTER;
        if( (IID_IUnknown == riid)
         || (EnumeratorIID == riid) )
        {
            AddRef();
            *ppv = reinterpret_cast<LPVOID>(this);
            return NOERROR;
        }
        // standalone object
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        return InterlockedIncrement(&_refcount);
    }

    STDMETHODIMP_(ULONG) Release(void)
    {
        ULONG refcount = InterlockedDecrement(&_refcount);
        if( 0 == refcount )
        {
            delete this;
            return 0;
        }
        return refcount;
    }


    // IEnumXXXX methods
    STDMETHODIMP Next(ULONG celt, typename T::BASE *rgelt, ULONG *pceltFetched)
    {
        if( NULL == rgelt )
            return E_POINTER;

        if( (celt > 1) && (NULL == pceltFetched) )
            return E_INVALIDARG;

        ULONG c = 0;

        while( (c < celt) && (m_i < get_count()) )
        {
            rgelt[c] = element_at(m_i);
            m_i++;
            ++c;
        }

        if( NULL != pceltFetched )
            *pceltFetched = c;

        return (c == celt) ? S_OK : S_FALSE;
    }

    STDMETHODIMP Skip(ULONG celt)
    {
        ULONG c = 0;

        while( (c < celt) && (m_i < get_count()) )
        {
            m_i++;
            ++c;
        }
        return (c == celt) ? S_OK : S_FALSE;
    }

    STDMETHODIMP Reset(void)
    {
        m_i = 0;
        return S_OK;
    }

    STDMETHODIMP Clone(Enumerator **ppEnum)
    {
        if( NULL == ppEnum )
            return E_POINTER;
        *ppEnum = dynamic_cast<Enumerator *>(new simple_enum(*this));
        return (NULL != *ppEnum ) ? S_OK : E_OUTOFMEMORY;
    }


    template < class KEY, class VALUE >
    simple_enum & operator = (const simple_map < KEY, VALUE > & map)
    {
       KEY key;
       VALUE value;
       POSITION pos = map.get_start_position();
       while(pos != NULL)
       {
          map.get_next_assoc(pos, key, value);
          add(T(key, value));
       }
       return *this;
    }

    template < class VAL >
    simple_enum & operator = (const simple_array < VAL > & a)
    {
       for(int i = 0; i < a.get_count(); i++)
       {
          add(T(a[i]));
       }
       return *this;
    }

private:

    LONG     _refcount;
    int m_i;

};


/*

template < REFIID EnumeratorIID, class Enumerator, class T, class Iterator, class Dereference = VLCDereference<T, Iterator> >
class enum_iterator : 
   public Enumerator
{

public:

    enum_iterator(const Iterator& from, const Iterator& to) :
        _refcount(1),
        _begin(from),
        _curr(from),
        _end(to)
    {}

    enum_iterator(const enum_iterator& e) :
        Enumerator(),
        _refcount(e._refcount),
        _begin(e._begin),
        _curr(e._curr),
        _end(e._end)
    {}

    virtual ~enum_iterator()
    {}

    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        if( NULL == ppv )
            return E_POINTER;
        if( (IID_IUnknown == riid)
         || (EnumeratorIID == riid) )
        {
            AddRef();
            *ppv = reinterpret_cast<LPVOID>(this);
            return NOERROR;
        }
        // standalone object
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {
        return InterlockedIncrement(&_refcount);
    }

    STDMETHODIMP_(ULONG) Release(void)
    {
        ULONG refcount = InterlockedDecrement(&_refcount);
        if( 0 == refcount )
        {
            delete this;
            return 0;
        }
        return refcount;
    }


    // IEnumXXXX methods
    STDMETHODIMP Next(ULONG celt, T *rgelt, ULONG *pceltFetched)
    {
        if( NULL == rgelt )
            return E_POINTER;

        if( (celt > 1) && (NULL == pceltFetched) )
            return E_INVALIDARG;

        ULONG c = 0;

        while( (c < celt) && (_curr != _end) )
        {
            rgelt[c] = dereference(_curr);
            ++_curr;
            ++c;
        }

        if( NULL != pceltFetched )
            *pceltFetched = c;

        return (c == celt) ? S_OK : S_FALSE;
    }

    STDMETHODIMP Skip(ULONG celt)
    {
        ULONG c = 0;

        while( (c < celt) && (_curr != _end) )
        {
            _curr = _curr->getN;
            ++c;
        }
        return (c == celt) ? S_OK : S_FALSE;
    }

    STDMETHODIMP Reset(void)
    {
        _curr = _begin;
        return S_OK;
    }

    STDMETHODIMP Clone(Enumerator **ppEnum)
    {
        if( NULL == ppEnum )
            return E_POINTER;
        *ppEnum = dynamic_cast<Enumerator *>(new enum_iterator(*this));
        return (NULL != *ppEnum ) ? S_OK : E_OUTOFMEMORY;
    }

private:

    LONG     _refcount;
    Iterator _begin, _curr, _end;

    Dereference dereference;

};
*/
#define __W(STR) L##STR

#define W(STR) __W(STR)