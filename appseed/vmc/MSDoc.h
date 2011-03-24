#pragma once

#include "VMS_.h"

#include "DocumentElement.h"
#include "DocumentBookmark.h"
#include "DEStaff.h"
#include "DEClef.h"
#include "DEKeySignature.h"
#include "DETimeSignature.h"
#include "DENoteSet.h"
#include "DECoTimeNoteSet.h"
#include "DENote.h"
#include "DERest.h"


#include "mus/MidiDocHelper.h"

class MidiFile;
class MidiEventV001;
class CMSTrack;
class CMSHeader;
class CMSChunk;

typedef struct tag_MSDocChunkHeader
{
    FOURCC      m_fourccType;
    DWORD       m_dwLength;
} MSDOCCHUNKHEADER, * LPMSDOCCHUNKHEADER;



class CMSDoc : 
   public BaseDocument,
   public MidiDocHelper
{
    friend  CMSTrack;
public:
   CMSDoc(::ca::application * papp);

public:
	enum EDocumentElement
	{
		DEDocumentBookmark,
		DEStaff,
		DEClef,
		DEKeySignature,
		DETimeSignature,
		DENoteSet,
		DECoTimeNoteSet,
		DENote,
		DERest,
	};

	class CElementReference
	{
	public:
		EDocumentElement	m_edocumentelement;
		int					m_iIndex;
	};
    
	BaseArray<CMSTrack *,
        CMSTrack *> * GetTracks()
    {
        return &m_lpaTracks;
    }

protected:
    LPBYTE          m_lpbData;
    int             m_iAllocation;
    int             m_iAllocationAddUp;
    int             m_iSize;
    int             m_iPosition;

	BaseArray <CElementReference, CElementReference &> 
					m_elementa;
	BaseArray <CDocumentBookmark, CDocumentBookmark &>
					m_bookmarka;
	BaseArray <CDEStaff, CDEStaff &>
					m_staffa;
	BaseArray <CDEClef, CDEClef &>
					m_clefa;
	BaseArray <CDEKeySignature, CDEKeySignature &>
					m_keysignaturea;
	BaseArray <CDETimeSignature, CDETimeSignature &>
					m_timesignaturea;
	BaseArray <CDENoteSet, CDENoteSet &>
					m_noteseta;
	BaseArray <CDECoTimeNoteSet, CDECoTimeNoteSet &>
					m_cotimenoteseta;
	BaseArray <CDENote, CDENote &>
					m_notea;
	BaseArray <CDERest, CDERest &>
					m_resta;

					
   windows_thread * HelperGetMidiPlayerCallbackThread();

    CMSHeader *     m_lpHeader;
    BaseArray<CMSTrack *,
        CMSTrack *>
                    m_lpaTracks;

    
// Operations
public:

	virtual void Serialize(Ex1Archive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
public:
	VMSRESULT UpdateSymbolsDelta();
	VMSRESULT ReadTracks();
	int GetMaxTracksPixelsSizeX();
	
	VMSRESULT MergeChunks();
	VMSRESULT DoDefaultNotesCreation(DWORD tkDelta);
    VMSRESULT DoDefaultNotesSpacing();
//	VMSRESULT WriteVDWord(DWORD dw, bool bInsert, LPINT lpiUsed = NULL);
//	VMSRESULT Write(MidiEventV001 *lpEvent, bool bInsert);
	VMSRESULT InsertSpace(int iChunkIndex, int iSize);
	VMSRESULT Seek(int iPosition);
	VMSRESULT GetChunk(int iIndex, LPMSDOCCHUNKHEADER * lpChunkHeader, LPVOID * lpChunkData);
	VMSRESULT SizeUp(int iAddUp);
	VMSRESULT Write(void * lpData, int iSize, bool bInsert);
    VMSRESULT Write(CMSChunk * lpChunk, bool bInsert);
	//VMSRESULT Write(BYTE byte, bool bInsert);
    
	VMSRESULT GetChunkCount(LPINT lpiCount);
	VMSRESULT SetHeader(MidiFile *lpFile);
	VMSRESULT CreateFromMidiFile(MidiFile * lpFile);
	VMSRESULT SetSize(int iNewSize);
	VMSRESULT Allocate(int iNewSize);
	virtual ~CMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

