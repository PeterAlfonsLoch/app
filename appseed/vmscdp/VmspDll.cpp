// VmspDll.cpp: implementation of the CVmspDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VmspDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVmspDll * CVmspDll::g_pvmspdll = NULL;

CVmspDll::CVmspDll()
{

}

CVmspDll::~CVmspDll()
{

}

 CVmspDll * CVmspDll::GetVmspDll()
 {
     return g_pvmspdll;
 }
 void CVmspDll::SetVmspDll( CVmspDll * pvmspdll)
 {
     g_pvmspdll = pvmspdll;
 }
