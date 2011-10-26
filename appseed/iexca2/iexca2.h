#pragma once

#include "c/c.h"


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

       REFCLSID getClassID(void) { return (REFCLSID)_classid; }

       LPCTSTR getInPlaceWndClassName(void) const { return TEXT("ActiveX Plugin In-Place"); }
       HINSTANCE getHInstance(void) const { return _hinstance; }
       LPPICTURE getInPlacePict(void) const
           { if( NULL != _inplace_picture) _inplace_picture->AddRef(); return _inplace_picture; }

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
//#include <tchar.h>
#include <shlwapi.h>

#define INITGUID
#include <guiddef.h>
#include <docobj.h>
#include <ocidl.h>
#include "oleidl.h"
#include <ole2.h>
//#include <string.h>
#include <winreg.h>
#include <winuser.h>
#include <servprov.h>
#include <shlwapi.h>
#include <wininet.h>



#include "iexca2_host.h"

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

#include "iexca2_h.h"

#undef new





