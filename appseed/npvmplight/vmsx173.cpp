// vmsx173.cpp : Implementation of CVmsx173App and DLL registration.

#include "stdafx.h"
#include "vmsx173.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



const GUID CDECL BASED_CODE _tlid =
		{ 0xc8dfaf76, 0xda4a, 0x43ec, { 0x8c, 0xe6, 0x8b, 0x44, 0xc5, 0x14, 0xe4, 0x64 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;







/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
