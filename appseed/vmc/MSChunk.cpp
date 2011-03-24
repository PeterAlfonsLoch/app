#include "StdAfx.h"
#include "MSChunk.h"

#include "MSEventMidi.h"
#include "MSEventSymbol.h"

#include "mus/MidiEventV001.h"

#include "MSDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT grbChanMsgLen[] =
{ 
    0,                      /* 0x   not a status byte   */
    0,                      /* 1x   not a status byte   */
    0,                      /* 2x   not a status byte   */
    0,                      /* 3x   not a status byte   */
    0,                      /* 4x   not a status byte   */
    0,                      /* 5x   not a status byte   */
    0,                      /* 6x   not a status byte   */
    0,                      /* 7x   not a status byte   */
    3,                      /* 8x   Note off            */
    3,                      /* 9x   Note on             */
    3,                      /* Ax   Poly pressure       */
    3,                      /* Bx   Control change      */
    2,                      /* Cx   Program change      */
    2,                      /* Dx   Chan pressure       */
    3,                      /* Ex   Pitch bend change   */
    0,                      /* Fx   SysEx (see below)   */             
} ;



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSChunk::CMSChunk(CMSDoc * lpDoc)
{
    m_lpDoc = lpDoc;

    m_lpbData = NULL;
    m_iSize = 0;
    m_iAllocation = 0;
    m_iAllocationAddUp = 65536;
    m_lpHeader = NULL;
    m_iBufferSize = 0;
    m_lpbBuffer = NULL;
    m_iPosition = 0;
    VMSRESULT vmsr;
    if(VMS_FAILED(vmsr = AllocateBuffer(65536)))
    {
        AfxMessageBox(_T("No Memory"));
        AfxThrowVMSException(vmsr);
    }
    m_lpMidiEventV001 = new MidiEventV001();
}

CMSChunk::~CMSChunk()
{
    if(m_lpMidiEventV001 != NULL)
        delete m_lpMidiEventV001;
        
}

VMSRESULT CMSChunk::SeekBegin(int iPosition, int iFrom)
{
    if(iFrom == SeekFile)
    {
        return Seek(iPosition, SeekFileBegin);
    }
    else if(iFrom == SeekChunk)
    {
        return Seek(iPosition, SeekChunkBegin);
    }
    else
    {
        ASSERT(FALSE);
    }
    return VMSR_E_FAIL;
//    LPMSDOCCHUNKHEADER lpch = m_pDoc->GetChunk(m_iChunk, NULL);
  //  m_iPosition = (LPBYTE) lpch - m_pDoc->m_lpbData;
}

VMSRESULT CMSChunk::SetChunk(int iIndex)
{
    m_iChunk = iIndex;
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Allocate(int iNewSize)
{
    ASSERT(iNewSize > 0);
    if(m_lpbData == NULL)
    {
        LPBYTE lpbData = (LPBYTE) malloc(iNewSize);
        if(lpbData == NULL)
            return VMSR_E_NOMEMORY;
        m_lpbData = lpbData;
        m_iAllocation = iNewSize;
    }
    else
    {
        if(iNewSize > m_iAllocation)
        {
            LPBYTE lpbData = (LPBYTE) realloc(m_lpbData, iNewSize);
            if(lpbData == NULL)
                return VMSR_E_NOMEMORY;
            m_lpbData = lpbData;
            m_iAllocation = iNewSize;
        }
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::SetSize(int iNewSize)
{
    VMSRESULT vmsr;
    if(iNewSize > m_iAllocation)
    {
        if(VMS_FAILED(vmsr = Allocate(iNewSize + m_iAllocationAddUp)))
            return vmsr;
    }
    
    m_iSize = iNewSize;

    return true;
}




VMSRESULT CMSChunk::AllocateBuffer(int iNewSize)
{
    ASSERT(iNewSize > 0);
    if(m_lpbBuffer == NULL)
    {
        LPBYTE lpbBuffer = (LPBYTE) malloc(iNewSize);
        if(lpbBuffer == NULL)
            return false;
        m_lpbBuffer = lpbBuffer;
        m_iBufferAllocation = iNewSize;
    }
    else
    {
        LPBYTE lpbBuffer = (LPBYTE) realloc(m_lpbBuffer, iNewSize);
        if(lpbBuffer == NULL)
            return false;
        m_lpbBuffer = lpbBuffer;
        m_iBufferAllocation = iNewSize;
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Write(BYTE byte, bool bInsert)
{
    return Write(&byte, sizeof(byte), bInsert);
}

VMSRESULT CMSChunk::Write(void *lpData, int iSize, bool bInsert)
{
    VMSRESULT vmsr;
    if(bInsert != m_bInsert)
    {
       if(VMS_FAILED(vmsr = Flush()))
            return vmsr;
       m_bInsert = bInsert;
    }
    if(m_lpbBuffer == NULL)
    {
        if(VMS_FAILED(vmsr = AllocateBuffer(1024)))
        {
            return vmsr;
        }
    }
    int iDifference;
    while(true)
    {
        iDifference = m_iBufferAllocation - (m_iPosition + iSize - m_iBufferPosition);
        if(iDifference < 0)
        {
            memcpy(m_lpbBuffer + m_iPosition - m_iBufferPosition, lpData, iSize + iDifference);
            m_iBufferSize = m_iBufferAllocation;
            if(VMS_FAILED(vmsr = Flush()))
                return vmsr;
            m_iBufferPosition += m_iBufferAllocation;
            lpData = (LPBYTE) lpData +  iSize + iDifference;
            m_iPosition += iSize + iDifference;
            iSize = -iDifference;
            
        }
        else
            break;
    }
    if(iSize > 0)
    {
        memcpy(m_lpbBuffer + m_iPosition - m_iBufferPosition, lpData, iSize);
        m_iBufferSize += iSize;
        m_iPosition += iSize;
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Flush()
{
    VMSRESULT vmsr;
    if(m_iBufferSize <= 0)
        return true;
    if(m_bInsert)
    {
        if(m_iBufferPosition + m_iBufferSize > m_iSize)
        {
            if(VMS_FAILED(vmsr = SetSize(m_iBufferPosition + m_iBufferSize)))
                return vmsr;
        }
        memcpy(m_lpbData + m_iBufferPosition, m_lpbBuffer, m_iBufferSize);
        m_iBufferSize = 0;
    }
    else
    {
        if(VMS_FAILED(vmsr = SizeUp(m_iBufferSize)))
            return vmsr;
        memmove(m_lpbData + m_iBufferPosition, m_lpbData + m_iBufferPosition + m_iBufferSize, m_iSize - (m_iBufferPosition + m_iBufferSize));
        memcpy(m_lpbData + m_iBufferPosition, m_lpbBuffer, m_iBufferSize);
    }
    m_iBufferSize = 0;
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::SizeUp(int iAddUp)
{
    ASSERT(iAddUp > 0);
    return SetSize(m_iSize + iAddUp);
}


VMSRESULT CMSChunk::Seek(int iPosition, int iFrom)
{
    VMSRESULT vmsr;

    if(VMS_FAILED(vmsr = Flush()))
        return vmsr;

    if(iFrom == SeekChunkBegin)
    {
        m_iPosition = iPosition;
        m_iBufferPosition = iPosition;
    }
    else
    {
        ASSERT(FALSE);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::InsertSpace(int iPosition, int iSize)
{
    VMSRESULT vmsr;
    ASSERT(iSize > 0);
    if(VMS_FAILED(vmsr = SizeUp(iSize)))
        return vmsr;
    LPBYTE lpData  = m_lpbData + iPosition;
    if(m_iSize - iPosition - iSize > 0)
        memmove(lpData, lpData + iSize, m_iSize - iPosition - iSize);
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Write(MidiEventBase *lpEvent, bool bInsert, DWORD dwEventType)
{
    VMSRESULT vmsr;
    BOOL                    bEvent;
    DWORD                   cbEvent;

    if(VMS_FAILED(vmsr = WriteVDWord(lpEvent->GetDelta(), bInsert)))
        return vmsr;
    
    if(VMS_FAILED(vmsr = WriteVDWord(dwEventType, bInsert)))
        return vmsr;
    
    bEvent = lpEvent->GetFullType();

    if(bEvent < Midi::Msg)
	{
		ASSERT(FALSE);
	}
	else if(bEvent < Midi::SysEx)
	{
		if(VMS_FAILED(vmsr = Write((BYTE) bEvent, bInsert)))
            return vmsr;
/* xxx		if(VMS_FAILED(vmsr = Write((BYTE) lpEvent->G[1], bInsert)))
            return vmsr;
        if (3 == grbChanMsgLen[(bEvent >> 4) & 0x0F])
        {
            if(VMS_FAILED(vmsr = Write((BYTE) lpEvent->m_abEvent[2], bInsert)))
                return vmsr;
        }*/
	}
    else
    {
        if (Midi::Meta == bEvent)
        {
            if(VMS_FAILED(vmsr = Write((BYTE) Midi::Meta, bInsert)))
                return vmsr;
            if(VMS_FAILED(vmsr = Write((BYTE) lpEvent->GetMetaType(), bInsert)))
                return vmsr;
        }
        else if (Midi::SysEx == bEvent || Midi::SysExEnd == bEvent)
        {
            if(VMS_FAILED(vmsr = Write((BYTE) bEvent, bInsert)))
                return vmsr;
        }
        else
        {
            ASSERT(FALSE);
        }

/*		cbEvent = lpEvent->m_cbParm;
        
        if(VMS_FAILED(vmsr = WriteVDWord(cbEvent, bInsert)))
            return vmsr;

        if(VMS_FAILED(vmsr = Write(lpEvent->m_hpbParm, cbEvent, bInsert)))
            return vmsr;*/
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::WriteVDWord(DWORD dw, bool bInsert, LPINT lpiUsed)
{
    int                     iUsed  = 0;
	DWORD					dwBuffer;
    VMSRESULT               vmsr;

	ASSERT(dw <= 0x0fffffff);
	
	dwBuffer = dw & 0x7f;
	iUsed++;
	while ((dw >>= 7) > 0)
	{
		dwBuffer <<= 8;
		dwBuffer |= 0x80;
		dwBuffer |= (dw & 0x7f);
		iUsed++;
	}
	while (TRUE)
	{
		if(VMS_FAILED(vmsr = Write((BYTE) dwBuffer, bInsert)))
            return vmsr;
		if (dwBuffer & 0x80)
			dwBuffer >>= 8;
		else
			break;
	}
    if(lpiUsed != NULL)
        *lpiUsed = iUsed;
    return VMSR_SUCCESS;
}


VMSRESULT CMSChunk::Write(LPMSDOCCHUNKHEADER lpChunkHeader)
{
    VMSRESULT vmsr;

    if(m_lpHeader == NULL)
    {
        InsertSpace(0, sizeof(MSDOCCHUNKHEADER));
    }
    if(VMS_FAILED(vmsr = GetData((LPBYTE*)&m_lpHeader)))
        return vmsr;
    *m_lpHeader = *lpChunkHeader;
    return VMSR_SUCCESS;    
}

VMSRESULT CMSChunk::SetHeader(FOURCC fourcc)
{
    VMSRESULT vmsr;
    MSDOCCHUNKHEADER ch;
    ch.m_fourccType = fourcc;
    ch.m_dwLength = m_iSize - sizeof(MSDOCCHUNKHEADER);
    if(VMS_FAILED(vmsr = Write(&ch)))
        return vmsr;
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::GetData(LPBYTE *lppbData)
{
    ASSERT(lppbData !=  NULL);
    *lppbData = m_lpbData;
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::GetSize(LPINT lpiSize)
{
    ASSERT(lpiSize != NULL);
    *lpiSize = m_iSize;
    return VMSR_SUCCESS;

}

VMSRESULT CMSChunk::GetChunkType(FOURCC *lpFourcc)
{
    if(m_lpHeader != NULL)
    {
        *lpFourcc = m_lpHeader->m_fourccType;
        return VMSR_SUCCESS;
    }
    else
    {
        ASSERT(FALSE);
        return VMSR_E_FAIL;
    }

}

VMSRESULT CMSChunk::Write(CMSEvent *lpEvent, bool bInsert)
{
    VMSRESULT           vmsr;
    CMSEventMidi        eventMidi;
    CMSEventSymbol      eventSymbol;

    switch(lpEvent->GetEventType())
    {
    case VMS_EVENT_MIDI:
    case VMS_EVENT_MIDI_DELETED:
        lpEvent->GetEventMidi(eventMidi);
        eventMidi.GetMidiEventV001(m_lpMidiEventV001, 0xffffffff);
        if(VMS_FAILED(vmsr = Write(m_lpMidiEventV001, bInsert, eventMidi.GetEventType())))
            return vmsr;
        break;
    case VMS_EVENT_SYMBOL:
    case VMS_EVENT_SYMBOL_DELETED:
        lpEvent->GetEventSymbol(eventSymbol);
        if(VMS_FAILED(vmsr = Write(&eventSymbol, bInsert)))
            return vmsr;
        break;
    default:

        ASSERT(FALSE);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Write(CMSEventSymbol *lpEvent, bool bInsert, DWORD dwEventType)
{
    VMSRESULT vmsr;

    if(VMS_FAILED(vmsr = WriteVDWord(lpEvent->m_tkDelta, bInsert)))
        return vmsr;
    
    if(VMS_FAILED(vmsr = WriteVDWord(dwEventType, bInsert)))
        return vmsr;
    
    if(VMS_FAILED(vmsr = (lpEvent->GetData(), lpEvent->GetDataSize())))
        return vmsr;
    
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Read(CMSEvent *lpEvent)
{
    VMSRESULT vmsr;
    CMSEventMidi    eventMidi;
    CMSEventSymbol  eventSymbol;
    int             iLeft;
    lpEvent->DeleteContents();
    if(VMS_FAILED(vmsr = ReadVDWord(&lpEvent->m_tkDelta)) ||
        vmsr == VMSR_S_ENDOFFILE)
        return vmsr;
    if(VMS_FAILED(vmsr = ReadVDWord(&lpEvent->m_dwEventType)) ||
        vmsr == VMSR_S_ENDOFFILE)
        return vmsr;
    iLeft = m_iSize - m_iPosition;
    switch(lpEvent->m_dwEventType)
    {
    case VMS_EVENT_MIDI:
    case VMS_EVENT_MIDI_DELETED:
        lpEvent->GetEventMidi(eventMidi);
        if(VMS_FAILED(vmsr = eventMidi.FromData(m_lpbData + m_iPosition, &iLeft)))
            return vmsr;
        m_iPosition = m_iSize - iLeft;
        *lpEvent = eventMidi;
        break;
    case VMS_EVENT_SYMBOL:
    case VMS_EVENT_SYMBOL_DELETED:
        lpEvent->GetEventSymbol(eventSymbol);
        if(VMS_FAILED(vmsr = eventSymbol.FromData(m_lpbData + m_iPosition, &iLeft)))
            return vmsr;
        m_iPosition = m_iSize - iLeft;
        *lpEvent = eventSymbol;
        break;
    default:
        ASSERT(FALSE);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Read(BYTE *lpbyte)
{
    return Read((LPVOID) lpbyte, sizeof(BYTE));
}

VMSRESULT CMSChunk::ReadVDWord(LPDWORD lpdw)
{
    VMSRESULT               vmsr;
    BYTE                    b;

    ASSERT(lpdw != NULL);
    
    *lpdw = 0;

    do
    {
        if(VMS_FAILED(vmsr = Read(&b)) ||
            vmsr == VMSR_S_ENDOFFILE)
            return vmsr;
        *lpdw = (*lpdw << 7) | (b & 0x7F);
    } while (b&0x80);

    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Read(LPVOID lpData, int iSize)
{
    if(m_iPosition + iSize > m_iSize)
        return VMSR_S_ENDOFFILE;
    memcpy(lpData, m_lpbData + m_iPosition, iSize);
    m_iPosition += iSize;
    return VMSR_SUCCESS;
}

VMSRESULT CMSChunk::Write(short sh, bool bInsert)
{
    return Write(&sh, sizeof(sh), bInsert);
}
