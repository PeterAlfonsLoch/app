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
   /* this function object is used to return the value from a map pair */
   struct enum_connections_dereference
   {
       CONNECTDATA operator()(const std::map<DWORD,LPUNKNOWN>::iterator& i)
       {
           CONNECTDATA cd;

           i->second->AddRef();

           cd.dwCookie = i->first;
           cd.pUnk     = i->second;
           return cd;
       };
   };

   class enum_connections : public enum_iterator<IID_IEnumConnections,
       IEnumConnections,
       CONNECTDATA,
       std::map<DWORD,LPUNKNOWN>::iterator,
       enum_connections_dereference>
   {
   public:
       enum_connections(std::map<DWORD,LPUNKNOWN> &m) :
           enum_iterator<IID_IEnumConnections,
               IEnumConnections,
               CONNECTDATA,
               std::map<DWORD,LPUNKNOWN>::iterator,
               enum_connections_dereference> (m.begin(), m.end())
       {};
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////

   /* this function object is used to retain the dereferenced iterator value */
   struct enum_connection_points_dereference
   {
       LPCONNECTIONPOINT operator()(const std::vector<LPCONNECTIONPOINT>::iterator& i)
       {
           LPCONNECTIONPOINT cp = *i;
           cp->AddRef();
           return cp;
       }
   };

   class enum_connection_points: public enum_iterator<IID_IEnumConnectionPoints,
       IEnumConnectionPoints,
       LPCONNECTIONPOINT,
       std::vector<LPCONNECTIONPOINT>::iterator,
       enum_connection_points_dereference>
   {
   public:
       enum_connection_points(std::vector<LPCONNECTIONPOINT>& v) :
           enum_iterator<IID_IEnumConnectionPoints,
               IEnumConnectionPoints,
               LPCONNECTIONPOINT,
               std::vector<LPCONNECTIONPOINT>::iterator,
               enum_connection_points_dereference> (v.begin(), v.end())
       {};
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////

   STDMETHODIMP connection_point::GetConnectionInterface(IID *iid)
   {
       if( NULL == iid )
           return E_POINTER;

       *iid = _iid;
       return S_OK;
   };

   STDMETHODIMP connection_point::GetConnectionPointContainer(LPCONNECTIONPOINTCONTAINER *ppCPC)
   {
       if( NULL == ppCPC )
           return E_POINTER;

       _p_cpc->AddRef();
       *ppCPC = _p_cpc;
       return S_OK;
   };

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
   };

   STDMETHODIMP connection_point::Unadvise(DWORD pdwCookie)
   {
       std::map<DWORD,LPUNKNOWN>::iterator pcd = _connections.find((DWORD)pdwCookie);
       if( pcd != _connections.end() )
       {
           pcd->second->Release();

           _connections.erase(pdwCookie);
           return S_OK;
       }
       return CONNECT_E_NOCONNECTION;
   };

   STDMETHODIMP connection_point::EnumConnections(IEnumConnections **ppEnum)
   {
       if( NULL == ppEnum )
           return E_POINTER;

       *ppEnum = dynamic_cast<LPENUMCONNECTIONS>(new enum_connections(_connections));

       return (NULL != *ppEnum ) ? S_OK : E_OUTOFMEMORY;
   };

   void connection_point::fireEvent(DISPID dispId, DISPPARAMS *pDispParams)
   {
       std::map<DWORD,LPUNKNOWN>::iterator end = _connections.end();
       std::map<DWORD,LPUNKNOWN>::iterator iter = _connections.begin();

       while( iter != end )
       {
           LPUNKNOWN pUnk = iter->second;
           if( NULL != pUnk )
           {
               IDispatch *pDisp;
               if( SUCCEEDED(pUnk->QueryInterface(_iid, (LPVOID *)&pDisp)) )
               {
                   pDisp->Invoke(dispId, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, pDispParams, NULL, NULL, NULL);
                   pDisp->Release();
               }
           }
           ++iter;
       }
   };

   void connection_point::firePropChangedEvent(DISPID dispId)
   {
       std::map<DWORD,LPUNKNOWN>::iterator end = _connections.end();
       std::map<DWORD,LPUNKNOWN>::iterator iter = _connections.begin();

       while( iter != end )
       {
           LPUNKNOWN pUnk = iter->second;
           if( NULL != pUnk )
           {
               IPropertyNotifySink *pPropSink;
               if( SUCCEEDED(pUnk->QueryInterface(IID_IPropertyNotifySink, (LPVOID *)&pPropSink)) )
               {
                   pPropSink->OnChanged(dispId);
                   pPropSink->Release();
               }
           }
           ++iter;
       }
   };

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
   };

   ////////////////////////////////////////////////////////////////////////////////////////////////

   connection_point_container::connection_point_container(plugin *p_instance) :
       _p_instance(p_instance), _b_freeze(FALSE)
   {
       _p_events = new connection_point(dynamic_cast<LPCONNECTIONPOINTCONTAINER>(this),
               _p_instance->getDispEventID());

       _v_cps.push_back(dynamic_cast<LPCONNECTIONPOINT>(_p_events));

       _p_props = new connection_point(dynamic_cast<LPCONNECTIONPOINTCONTAINER>(this),
               IID_IPropertyNotifySink);

       _v_cps.push_back(dynamic_cast<LPCONNECTIONPOINT>(_p_props));
   };

   connection_point_container::~connection_point_container()
   {
       delete _p_props;
       delete _p_events;
   };

   STDMETHODIMP connection_point_container::EnumConnectionPoints(LPENUMCONNECTIONPOINTS *ppEnum)
   {
       if( NULL == ppEnum )
           return E_POINTER;

       *ppEnum = dynamic_cast<LPENUMCONNECTIONPOINTS>(new enum_connection_points(_v_cps));

       return (NULL != *ppEnum ) ? S_OK : E_OUTOFMEMORY;
   };

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
   };

   void connection_point_container::freezeEvents(BOOL freeze)
   {
       if( ! freeze )
       {
           // release queued events
           while( ! _q_events.empty() )
           {
               dispatch_event *ev = _q_events.front();
               _q_events.pop();
               _p_events->fireEvent(ev->_dispId, &ev->_dispParams);
               delete ev;
           }
       }
       _b_freeze = freeze;
   };

   void connection_point_container::fireEvent(DISPID dispId, DISPPARAMS* pDispParams)
   {
       if( _b_freeze )
       {
           // queue event for later use when container is ready
           _q_events.push(new dispatch_event(dispId, *pDispParams));
           if( _q_events.size() > 10 )
           {
               // too many events in queue, get rid of older one
               delete _q_events.front();
               _q_events.pop();
           }
       }
       else
       {
           _p_events->fireEvent(dispId, pDispParams);
       }
   };

   void connection_point_container::firePropChangedEvent(DISPID dispId)
   {
       if( ! _b_freeze )
           _p_props->firePropChangedEvent(dispId);
   };


} // namespace iexca2