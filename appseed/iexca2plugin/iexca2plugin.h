/*****************************************************************************
 * plugin.h: Free ActiveX based on ActiveX control for VLC
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

#pragma comment(lib, "Wtsapi32.lib")

#include "include/ca2.h"
#include "win/win.h"
#include "../npca2plugin/spa.h"
#include "../npca2plugin/npca2_gen.h"
#include "../npca2plugin/npca2_host_interaction.h"
#include "../npca2plugin/npca2_starter_start.h"
#include "../npca2plugin/npca2_plugin.h"
#include "../npca2plugin/npca2_system.h"
#include "../npca2plugin/npca2_history.h"
#include "../npca2plugin/npca2_run_start_installer.h"


#include <ole2.h>
#include <olectl.h>

const char * ca2_browser_plugin_get_module_name();

extern "C" const GUID CLSID_iexca2_control;
extern "C" const GUID CLSID_iexca2_control2;
extern "C" const GUID LIBID_iexca2;
extern "C" const GUID DIID_iexca2_events_dispatch;


namespace iexca2
{

   class class_factory : public IClassFactory
   {

   public:

       class_factory(LONG *p_class_ref, HINSTANCE hInstance, REFCLSID rclsid);

       /* IUnknown methods */
       STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
       STDMETHODIMP_(ULONG) AddRef(void);
       STDMETHODIMP_(ULONG) Release(void);

       /* IClassFactory methods */
       STDMETHODIMP CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void **ppv);
       STDMETHODIMP LockServer(BOOL fLock);

       REFCLSID getClassID(void) { return (REFCLSID)_classid; };

       LPCTSTR getInPlaceWndClassName(void) const { return TEXT("ActiveX Plugin In-Place"); };
       HINSTANCE getHInstance(void) const { return _hinstance; };
       LPPICTURE getInPlacePict(void) const
           { if( NULL != _inplace_picture) _inplace_picture->AddRef(); return _inplace_picture; };

   protected:

       virtual ~class_factory();

   private:

       LPLONG      _p_class_ref;
       HINSTANCE   _hinstance;
       CLSID       _classid;
       ATOM        _inplace_wndclass_atom;
       LPPICTURE   _inplace_picture;
   };

} // namespace iexca2

#include <comcat.h>
#include <tchar.h>
#include <shlwapi.h>

#define INITGUID
#include <guiddef.h>
#include <docobj.h>
#include <ocidl.h>
#include "oleidl.h"
#include <ole2.h>
#include <string.h>
#include <winreg.h>
#include <winuser.h>
#include <servprov.h>
#include <shlwapi.h>
#include <wininet.h>
#include <vector>
#include <queue>
#include <map>



#include "plugin.h"

#include "iexca2_h.h"

#include "oleobject.h"
#include "olecontrol.h"
#include "oleinplaceobject.h"
#include "oleinplaceactiveobject.h"
#include "oleinplaceobjectwindowless.h"
#include "persistpropbag.h"
#include "persiststreaminit.h"
#include "persiststorage.h"
#include "provideclassinfo.h"
#include "connectioncontainer.h"
#include "objectsafety.h"
//#include "vlccontrol.h"
#include "control.h"
#include "viewobject.h"
#include "dataobject.h"
#include "supporterrorinfo.h"

#include "setting.h"
#include "utils.h"

#include "viewobject.h"
#include "supporterrorinfo.h"

#undef new


