#pragma once

namespace ikar
{
   class ikar::karaoke;
}


class CLASS_DECL_ca LyricEventsV2 :
   public LyricEventsV1
{
public:
   imedia::time_array                  m_msaTokensPosition; // in millisecs
   imedia::time_array                  m_msaTokensDuration; // in millisecs
   int_int_spreadset                m_riiTokenNote;
   imedia::position_array            m_tkaNotesPosition; // in ticks
   imedia::time_array                  m_msaNotesPosition; // in millisecs
   imedia::time_array                  m_msaNotesDuration; // in millisecs
   dword_array                     m_dwaNotesData;
   dword_array                     m_dwaBeatNote; // for Bouncing Ball
   int_int_spreadset                m_riiNoteBeat;


   LyricEventsV2();
   virtual ~LyricEventsV2();


   int GetPositionNote(imedia::position tkPosition);
   int GetPositionToken(imedia::position tkPosition);
   int GetNoteFirstToken(int iNote);
   static void swap(void * lpVoidSwapArg, int iA, int iB);
   imedia::time GetTotalNotesMillis();
   void GetMillisIntervalNotes(int_array & iaIndexes, imedia::time msMin,  imedia::time msMax);
   void GetMillisNotes_(int *iStartNote, int *iNotesCount, imedia::time msMin, imedia::time msMax);
   BYTE GetNotePitch(int iIndex);


   virtual int GetClassOrder();
   void Reset();
   imedia::position GetCurrentTkNotePosition();
   imedia::position GetNextTkNotePosition();

   void PrepareForBouncingBall(ikar::karaoke * pinterface);
   void PrepareForLyricsDisplay(ikar::karaoke * pinterface);
   void PrepareForScoring(ikar::karaoke * pinterface);


   inline int GetTokenLastNote(int iToken)
   {
      unique_int_sort_array & iaNote = GetTokenNoteArray(iToken);
      if(iaNote.get_size() <= 0)
         return -1;
      return iaNote.last_element();
   }

   inline int GetTokenFirstNote(int iToken)
   {
      unique_int_sort_array & iaNote = GetTokenNoteArray(iToken);
      if(iaNote.get_size() <= 0)
         return -1;
      return iaNote.get_at(0);
   }

   inline unique_int_sort_array & GetTokenNoteArray(int iToken)
   {
      return m_riiTokenNote.b(iToken);
   }

   inline unique_int_sort_array & GetNoteTokenArray(int iNote)
   {
      return m_riiTokenNote.a(iNote);
   }

   void add_token_note(int iToken, int iNote);

};
