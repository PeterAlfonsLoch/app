// MSHeader.cpp: implementation of the CMSHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
//#include "VMSApp.h"
#include "MSHeader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSHeader::CMSHeader(CMSDoc * lpDoc)
: CMSChunk(lpDoc)
{

}

CMSHeader::~CMSHeader()
{

}

VMSRESULT CMSHeader::Write(bool bInsert)
{
    VMSRESULT vmsr;

    if(VMS_FAILED(vmsr =
        CMSChunk::Write((LPVOID) &m_iVersion, sizeof(m_iVersion), bInsert)))
        return vmsr;

    if(VMS_FAILED(vmsr =
        CMSChunk::Write((LPVOID) &m_midiFileHeader, sizeof(m_midiFileHeader), bInsert)))
        return vmsr;

    return VMSR_SUCCESS;
}
VMSRESULT CMSHeader::Write()
{
    VMSRESULT vmsr;

    if(VMS_FAILED(vmsr =
        SetSize(0)))
        return vmsr;

    if(VMS_FAILED(vmsr =
        SeekBegin()))
        return vmsr;

    if(VMS_FAILED(vmsr =
        Write(true)))
        return vmsr;

    if(VMS_FAILED(vmsr =
        CMSChunk::SetHeader(FOURCC_MShd)))
        return vmsr;

    return VMSR_SUCCESS;
}
