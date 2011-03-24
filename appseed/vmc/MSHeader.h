#pragma once

#include "MSChunk.h"
#include "VMS_.h"

class CMSDoc;

class CMSHeader : public CMSChunk  
{
public:
	
   CMSHeader(CMSDoc * lpDoc);
   virtual ~CMSHeader();
   int                 m_iVersion;
   MIDIFILEHDR         m_midiFileHeader;

   VMSRESULT Write(bool bInsert);
   VMSRESULT Write();
};

