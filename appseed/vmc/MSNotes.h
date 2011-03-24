#pragma once

#include "MSNote.h"

class CMSNotes : public BaseArray<CMSNote, CMSNote>  
{
public:
	void AddUnit(int iUnit);
	CMSNotes();
	virtual ~CMSNotes();

};

