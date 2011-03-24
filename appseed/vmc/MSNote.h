#pragma once

#include "MSNoteUnit.h"

class CMSNote : public BaseArray<CMSNoteUnit, CMSNoteUnit>  
{
public:
   CMSNote();
   CMSNote(CMSNote &note);
   virtual ~CMSNote();

public:
   CMSNote & operator =(const CMSNote &note);
   void Clear();
   //void AddUnit(int iUnit);
   void AddUnit(int iUnit, short shSymbolDelta, short shPositionY);
   DWORD GetDuration(DWORD tkQuarterNote);

   int     m_iNote;
   int     m_iAccidental;
};
