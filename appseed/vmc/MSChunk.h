#pragma once

#include "VMS_.h"

typedef struct tag_MSDocChunkHeader MSDOCCHUNKHEADER, * LPMSDOCCHUNKHEADER;
class CMSDoc;
class CMSEvent;
class CMSEventMidi;
class CMSEventSymbol;
class MidiEventV001;


class CMSChunk  
{
    enum
    {
        SeekFile= 1,
        SeekFileBegin = 2,
        SeekFileCurrent = 3,
        SeekFileEnd = 4,

        SeekChunk = 10,
        SeekChunkBegin = 11,
        SeekChunkCurrent = 12,
        SeekChunkEnd = 13
    };
public:
	CMSChunk(CMSDoc * lpDoc);
	virtual ~CMSChunk();

protected:
    LPMSDOCCHUNKHEADER  m_lpHeader;
    CMSDoc *            m_lpDoc;
    int                 m_iDocPosition;
    int                 m_iChunk;
    
    LPBYTE              m_lpbData;
    int                 m_iAllocation;
    int                 m_iAllocationAddUp;
    int                 m_iSize;
    int                 m_iPosition;

    LPBYTE              m_lpbBuffer;
    int                 m_iBufferAllocation;
    int                 m_iBufferSize;
    int                 m_iBufferPosition;

    bool                m_bInsert;

    MidiEventV001 *    m_lpMidiEventV001;

public:
   VMSRESULT Write(short sh, bool bInsert);
   VMSRESULT Read(LPVOID lpData, int iSize);
   VMSRESULT ReadVDWord(LPDWORD lpdw);
   VMSRESULT Read(BYTE * bByte);
   VMSRESULT Read(CMSEvent * lpEvent);
   VMSRESULT Write(CMSEventSymbol * lpEvent, bool bInsert, DWORD dwEventType = VMS_EVENT_SYMBOL);

   VMSRESULT GetChunkType(FOURCC * lpFourcc);
   VMSRESULT GetSize(LPINT lpiSize);
   VMSRESULT GetData(LPBYTE * lppData);
   VMSRESULT SetHeader(FOURCC fourcc);
   VMSRESULT Write(LPMSDOCCHUNKHEADER lpChunkHeader);
   VMSRESULT Allocate(int iNewSize);
   VMSRESULT AllocateBuffer(int iNewSize);
   VMSRESULT SetSize(int iNewSize);
   VMSRESULT SetChunk(int iIndex);
   VMSRESULT SizeUp(int iAddUp);
   VMSRESULT Write(void * lpData, int iSize, bool bInsert);
   VMSRESULT Write(BYTE byte, bool bInsert);
   VMSRESULT Write(MidiEventBase * lpEvent, bool bInsert, DWORD dwEventType = VMS_EVENT_MIDI);
   VMSRESULT Write(CMSEvent * lpEvent, bool bInsert);
   VMSRESULT WriteVDWord(DWORD dw, bool bInsert, LPINT lpiUsed = NULL);
   VMSRESULT InsertSpace(int iPosition, int iSize);
   VMSRESULT SeekBegin(int iPosition = 0, int iFrom = SeekChunk);

   VMSRESULT Seek(int iPosition, int iFrom);
   VMSRESULT Flush();

};

