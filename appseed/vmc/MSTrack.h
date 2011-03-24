#pragma once
#include "VMS_.h"
#include "MSChunk.h"
#include "MSEvents.h"
typedef struct tag_MSDocChunkHeader MSDOCCHUNKHEADER, * LPMSDOCCHUNKHEADER;

class CMSDoc;
class MidiEventV001;

class CMSTrack  : public CMSChunk
{
    friend CMSDoc;
public:
	CMSTrack(CMSDoc *pDoc);
	virtual ~CMSTrack();
public:
	CMSEvents * GetEvents();
	int GetPixelsSizeX();
	int GetPointsSizeX();
    VMSRESULT DoDefaultNotesCreation(DWORD tkDelta);
    VMSRESULT DoDefaultNotesSpacing();
  	VMSRESULT Read();
	VMSRESULT Write();
	VMSRESULT Write(bool bInsert);

protected:
    CMSEvents     m_evaData;
};
