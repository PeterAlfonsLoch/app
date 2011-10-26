/*****************************************************************************
 * connectioncontainer.cpp: Free ActiveX based on ActiveX control for VLC
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

   struct connect_data :
      public CONNECTDATA
   {
      typedef CONNECTDATA BASE;
      connect_data()
      {
      }

      connect_data(DWORD dwCookieParam, LPUNKNOWN pUnkParam)
      {
         dwCookie = dwCookieParam;
         pUnk = pUnkParam;
      }

   };

   class lp_connection_point
   {
   public:
      typedef LPCONNECTIONPOINT BASE;

      LPCONNECTIONPOINT m_ppoint;

      lp_connection_point()
      {
      }

      lp_connection_point(LPCONNECTIONPOINT lpconnection)
      {
         m_ppoint = lpconnection;
         lpconnection->AddRef();
      }

      operator BASE()
      {
         return m_ppoint;
      }

   };

   typedef simple_enum < IID_IEnumConnections, IEnumConnections, connect_data > enum_connections;
   typedef simple_enum < IID_IEnumConnectionPoints, IEnumConnectionPoints, lp_connection_point > enum_connection_points;

   STDMETHODIMP connection_point::GetConnectionInterface(IID *iid)
   {
       if( NULL == iid )
           return E_POINTER;

       *iid = _iid;
       return S_OK;
   }

   STDMETHODIMP connection_point::GetConnectionPointContainer(LPCONNECTIONPOINTCONTAINER *ppCPC)
   {
       if( NULL == ppCPC )
           return E_POINTER;

       _p_cpc->AddRef();
       *ppCPC = _p_cpc;
       return S_OK;
   }

   STDMETHODIMP connection_point::Advise(IUnknown *pUnk, DWORD *pdwCookie)
   {
       static DWORD dwCookieCounter = 0;

       if( (NULL == pUnk) || (NULL == pdwCookie) )
           return E_POINTER;

       if( SUCCEEDED(pUnk->QueryInterface(_iid, (LPVOID *)&pUnk)) )
       {
           *pdwCookie = ++dwCookieCounter;
           _connections[*pdwCookie] = pUnk;
           return S_OK;
       }
       return CONNECT_E_CANNOTCONNECT;
   }

   STDMETHODIMP connection_point::Unadvise(DWORD pdwCookie)
   {
      LPUNKNOWN lpUnknown;
       if(_connections.Lookup(pdwCookie, lpUnknown))
       {
           lpUnknown->Release();

           _connections.remove_key(pdwCookie);
           return S_OK;
       }
       return CONNECT_E_NOCONNECTION;
   }

   STDMETHODIMP connection_point::EnumConnections(IEnumConnections **ppEnum)
   {
       if( NULL == ppEnum )
           return E_POINTER;

       *ppEnum = dynamic_cast<LPENUMCONNECTIONS>(new enum_connections(_connections));

       return (NULL != *ppEnum ) ? S_OK : E_OUTOFMEMORY;
   }

   void connection_point::fireEvent(DISPID dispId, DISPPARAMS *pDispParams)
   {
      POSITION pos = _connections.get_start_position();
      DWORD key;
      LPUNKNOWN pUnk;
      while(pos != NULL)
      {
         _connections.get_next_assoc(pos, key, pUnk);
         if(pUnk != NULL)
         {
            IDispatch *pDisp;
            if( SUCCEEDED(pUnk->QueryInterface(_iid, (LPVOID *)&pDisp)) )
            {
               pDisp->Invoke(dispId, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, pDispParams, NULL, NULL, NULL);
               pDisp->Release();
            }
         }
       }
   }

   void connection_point::firePropChangedEvent(DISPID dispId)
   {
      POSITION pos = _connections.get_start_position();
      DWORD key;
      LPUNKNOWN pUnk;
      while(pos != NULL)
      {
         _connections.get_next_assoc(pos, key, pUnk);
         if(pUnk != NULL)
         {
            IPropertyNotifySink *pPropSink;
            if( SUCCEEDED(pUnk->QueryInterface(IID_IPropertyNotifySink, (LPVOID *)&pPropSink)) )
            {
                  pPropSink->OnChanged(dispId);
                  pPropSink->Release();
            }
         }
       }
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////

   dispatch_event::~dispatch_event()
   {
       //clear event arguments
       if( NULL != _dispParams.rgvarg )
       {
           for(unsigned int c=0; c<_dispParams.cArgs; ++c)
               VariantClear(_dispParams.rgvarg+c);
           CoTaskMemFree(_dispParams.rgvarg);
       }
       if( NULL != _dispParams.rgdispidNamedArgs )
           CoTaskMemFree(_dispParams.rgdispidNamedArgs);
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////

   connection_point_container::connection_point_container(host *p_instance) :
       _p_instance(p_instance), _b_freeze(FALSE)
   {
       _p_events = new connection_point(dynamic_cast<LPCONNECTIONPOINTCONTAINER>(this),
               _p_instance->getDispEventID());

       _v_cps.add(dynamic_cast<LPCONNECTIONPOINT>(_p_events));

       _p_props = new connection_point(dynamic_cast<LPCONNECTIONPOINTCONTAINER>(this),
               IID_IPropertyNotifySink);

       _v_cps.add(dynamic_cast<LPCONNECTIONPOINT>(_p_props));
   }

   connection_point_container::~connection_point_container()
   {
       delete _p_props;
       delete _p_events;
   }

   STDMETHODIMP connection_point_container::EnumConnectionPoints(LPENUMCONNECTIONPOINTS *ppEnum)
   {
       if( NULL == ppEnum )
           return E_POINTER;

       *ppEnum = dynamic_cast<LPENUMCONNECTIONPOINTS>(new enum_connection_points(_v_cps));

       return (NULL != *ppEnum ) ? S_OK : E_OUTOFMEMORY;
   }

   STDMETHODIMP connection_point_container::FindConnectionPoint(REFIID riid, IConnectionPoint **ppCP)
   {
       if( NULL == ppCP )
           return E_POINTER;

       *ppCP = NULL;

       if( IID_IPropertyNotifySink == riid )
       {
           _p_props->AddRef();
           *ppCP = dynamic_cast<LPCONNECTIONPOINT>(_p_props);
       }
       else if( _p_instance->getDispEventID() == riid )
       {
           _p_events->AddRef();
           *ppCP = dynamic_cast<LPCONNECTIONPOINT>(_p_events);
       }
       else
           return CONNECT_E_NOCONNECTION;

       return NOERROR;
   }

   void connection_point_container::freezeEvents(BOOL freeze)
   {
       if( ! freeze )
       {
           // release queued events
           while(_q_events.get_count() > 0)
           {
               dispatch_event *ev = _q_events.element_at(0);
               _q_events.remove_at(0);
               _p_events->fireEvent(ev->_dispId, &ev->_dispParams);
               delete ev;
           }
       }
       _b_freeze = freeze;
   }

   void connection_point_container::fireEvent(DISPID dispId, DISPPARAMS* pDispParams)
   {
       if( _b_freeze )
       {
           // queue event for later use when container is ready
           _q_events.add(new dispatch_event(dispId, *pDispParams));
           if( _q_events.get_count() > 10 )
           {
               // too many events in queue, get rid of older one
               delete _q_events.element_at(0);
               _q_events.remove_at(0);
           }
       }
       else
       {
           _p_events->fireEvent(dispId, pDispParams);
       }
   }

   void connection_point_container::firePropChangedEvent(DISPID dispId)
   {
       if( ! _b_freeze )
           _p_props->firePropChangedEvent(dispId);
   }


} // namespace iexca2