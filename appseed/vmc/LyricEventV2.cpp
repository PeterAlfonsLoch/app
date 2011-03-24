// LyricEventV2.cpp: implementation of the CLyricEventV2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VmcApp.h"
#include "LyricEventV2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLyricEventV2::CLyricEventV2()
{

}

CLyricEventV2::~CLyricEventV2()
{

}

void CLyricEventV2::FromData(LPDWORD lpdwData)
{
	memcpy((void *) m_pbData, lpdwData, sizeof(m_pbData));
}

void CLyricEventV2::ToData(LPDWORD lpdwData, DWORD cbLeft)
{
	if(cbLeft <= 0)
		return;
	if(cbLeft != sizeof(m_pbData))
	{
		TRACE(_T("BAD EVENT"));
	}

//	TRACE(
//		_T("ToData %05d   %05d   %05d\n"),
//		m_Event.m_nType,
//		m_Event.m_nTrack,
//		m_Event.m_nCurrentIndex);
	void * pVoid = (void *) ((m_pbData + (sizeof(m_pbData))) - cbLeft) ;
	memcpy((void *) lpdwData, pVoid, cbLeft);
}
