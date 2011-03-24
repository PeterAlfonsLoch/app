#pragma once

#include "VMS_.h"

#include "MSEvent.h"
#include "MSNotes.h"
#include "MSNote.h"
#include "MSNoteUnit.h"

class CMSEvents : public BaseArray <CMSEvent, CMSEvent>  
{
public:
   CMSEvents();
   virtual ~CMSEvents();


   VMSRESULT UpdateSymbolsDelta();
   int         m_iCurrentEvent;
   void InsertAt(int iIndex, CMSNoteUnit &noteUnit, LPINT lpiNextIndex);
   void InsertAt(int iIndex, CMSNote &note, LPINT lpiNextIndex);
   void InsertAt(int iIndex, CMSNotes &notes, LPINT lpiNextIndex);
   void InsertAt(int iIndex, CMSEvent &event);
   bool HasNotes();
   VMSRESULT GetNotesSymbolsIndexes(BaseDWORDArray &dwArray);
   VMSRESULT GetNextEventMidi(
      BYTE bType,
      CMSEvent ** lppEventMidiParam,
      int iIndex,
      LPINT lpiIndex,
      LPDWORD lptkDelta,
      CMSEvents *lpevaSymbols);

   VMSRESULT GetNextEventMidi(
      BYTE bType,
      BYTE bPitch,
      CMSEvent ** lppEventMidiParam,
      int iIndex,
      LPINT lpiIndex,
      LPDWORD lptkDelta,
      CMSEvents *lpevaSymbols);

   VMSRESULT GetNextEventSymbol(
      CMSEvent ** lppEventSymbolParam,
      int iIndex,
      LPINT lpiIndex,
      LPDWORD lptkDelta = NULL);

   VMSRESULT GetPositionEventSymbol(
      CMSEvent ** lppEventSymbolParam,
      int iPosition,
      LPINT lpiIndex,
      LPINT lpiPosition,
      LPDWORD lptkDelta = NULL);

};

