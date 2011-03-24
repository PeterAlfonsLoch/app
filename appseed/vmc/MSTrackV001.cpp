// MSTrackV001.cpp: implementation of the CMSTrackV001 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSTrackV001.h"

#include "MSTrack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMSTrackV001::CMSTrackV001()
{
    m_lpTrack = NULL;
}

CMSTrackV001::CMSTrackV001(CMSTrack *lpTrack)
{
    ASSERT(lpTrack != NULL);
    m_lpTrack = lpTrack;

}

CMSTrackV001::~CMSTrackV001()
{
    m_lpTrack = NULL;
}

VMSRESULT CMSTrackV001::Seek(int iOffset, int iFrom)
{
    if(iFrom == SeekEventBegin)
    {
        m_iCurrentEvent = iOffset;
    }
    else if(iFrom == SeekEventCurrent)
    {
        m_iCurrentEvent += iOffset;
    }
    else if(iFrom == SeekEventEnd)
    {
        m_iCurrentEvent = m_lpTrack->GetEvents()->GetSize() + iOffset;
    }
    ASSERT(m_iCurrentEvent >= 0 && m_iCurrentEvent <= m_lpTrack->GetEvents()->GetSize());
    CMSEvents * lpEvents = GetEvents();
    m_tkPosition = 0;
    for(int i = 0; i < m_iCurrentEvent; i++)
    {
        CMSEvent * lpEvent = &lpEvents->ElementAt(i);
        m_tkPosition += lpEvent->m_tkDelta;
    }

    return VMSR_SUCCESS;
}

VMSRESULT CMSTrackV001::SeekBegin(int iOffset)
{
    return Seek(iOffset, SeekEventBegin);
}

CMSEvents * CMSTrackV001::GetEvents()
{
    ASSERT(m_lpTrack != NULL);
    return m_lpTrack->GetEvents();
}
