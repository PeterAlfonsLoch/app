/*****************************************************************************
 * connectioncontainer.h: Free ActiveX based on ActiveX control for VLC
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

namespace iexca2
{

   class connection_point : public IConnectionPoint
   {

   public:

       connection_point(IConnectionPointContainer *p_cpc, REFIID iid) :
           _iid(iid), _p_cpc(p_cpc) {};
       virtual ~connection_point() {};

       // IUnknown methods
       STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
       {
           if( NULL == ppv )
               return E_POINTER;
           if( (IID_IUnknown == riid)
            || (IID_IConnectionPoint == riid) )
           {
               AddRef();
               *ppv = reinterpret_cast<LPVOID>(this);
               return NOERROR;
           }
           // must be a standalone object
           return E_NOINTERFACE;
       };

       STDMETHODIMP_(ULONG) AddRef(void) { return _p_cpc->AddRef(); };
       STDMETHODIMP_(ULONG) Release(void) { return _p_cpc->Release(); };

       // IConnectionPoint methods
       STDMETHODIMP GetConnectionInterface(IID *);
       STDMETHODIMP GetConnectionPointContainer(LPCONNECTIONPOINTCONTAINER *);
       STDMETHODIMP Advise(IUnknown *, DWORD *);
       STDMETHODIMP Unadvise(DWORD);
       STDMETHODIMP EnumConnections(LPENUMCONNECTIONS *);

       void fireEvent(DISPID dispIdMember, DISPPARAMS* pDispParams);
       void firePropChangedEvent(DISPID dispId);

   private:

       REFIID _iid;
       IConnectionPointContainer *_p_cpc;
       std::map<DWORD, LPUNKNOWN> _connections;
   };

   //////////////////////////////////////////////////////////////////////////

   class dispatch_event
   {
   public:
       dispatch_event(DISPID dispId, DISPPARAMS dispParams) :
           _dispId(dispId), _dispParams(dispParams) {};
       dispatch_event(const dispatch_event&);
       ~dispatch_event();

       DISPID      _dispId;
       DISPPARAMS  _dispParams;
   };

   class connection_point_container : public IConnectionPointContainer
   {

   public:

       connection_point_container(plugin *p_instance);
       virtual ~connection_point_container();

       // IUnknown methods
       STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
       {
           if( NULL == ppv)
               return E_POINTER;
           if( (IID_IUnknown == riid)
            || (IID_IConnectionPointContainer == riid) )
           {
               AddRef();
               *ppv = reinterpret_cast<LPVOID>(this);
               return NOERROR;
           }
           return _p_instance->pUnkOuter->QueryInterface(riid, ppv);
       };

       STDMETHODIMP_(ULONG) AddRef(void) { return _p_instance->pUnkOuter->AddRef(); };
       STDMETHODIMP_(ULONG) Release(void) { return _p_instance->pUnkOuter->Release(); };

       // IConnectionPointContainer methods
       STDMETHODIMP EnumConnectionPoints(LPENUMCONNECTIONPOINTS *);
       STDMETHODIMP FindConnectionPoint(REFIID, LPCONNECTIONPOINT *);

       void freezeEvents(BOOL);
       void fireEvent(DISPID, DISPPARAMS*);
       void firePropChangedEvent(DISPID dispId);

   private:

       plugin *_p_instance;
       BOOL _b_freeze;
       connection_point *_p_events;
       connection_point *_p_props;
       std::vector<LPCONNECTIONPOINT> _v_cps;
       std::queue<class dispatch_event *> _q_events;
   };

} // namespace iexca2

