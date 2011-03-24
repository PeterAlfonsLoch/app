// MSEvent.cpp: implementation of the CMSEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSEvent.h"

#include "MSEventMidi.h"
#include "MSEventSymbol.h"
#include "VMS_.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSEvent::CMSEvent()
{
    m_dwEventType = VMS_EVENT_MIDI;
}

CMSEvent::~CMSEvent()
{

}

DWORD CMSEvent::GetEventType()
{
    return m_dwEventType;
}

VMSRESULT CMSEvent::GetEventMidi(CMSEventMidi &event)
{
    event = *this;
    return VMSR_SUCCESS;
}

VMSRESULT CMSEvent::GetEventSymbol(CMSEventSymbol &event)
{
    event = *this;
    return VMSR_SUCCESS;
}

VMSRESULT CMSEvent::DeleteContents()
{
    m_tkDelta = 0;
    m_dwEventType = 0;
    memset(m_lpbData, NULL, sizeof(m_lpbData));
    return VMSR_SUCCESS;
}

CMSEvent & CMSEvent::operator =(const CMSEvent &eventSrc)
{
    m_tkDelta = eventSrc.m_tkDelta;
    m_dwEventType = eventSrc.m_dwEventType;
    memcpy(m_lpbData, eventSrc.m_lpbData, sizeof(m_lpbData));
	return *this;
}
