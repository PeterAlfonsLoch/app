#include "StdAfx.h"


LyricEventsV2::LyricEventsV2()
:LyricEventsV1()

{
}

LyricEventsV2::~LyricEventsV2()
{

}

/*void LyricEventsV2::GetTokenNotes_(int *piStartNote, int *piNotesCount, int iTokenIndex)
{
   if(iTokenIndex < 0)
   {
      *piStartNote = -1;
      *piNotesCount = -1;
      return;
   }
   ASSERT(iTokenIndex >= 0);
   ASSERT(iTokenIndex < m_tkaTokensPosition.get_size());
   imedia::position tkTokenPosition =  m_tkaTokensPosition[iTokenIndex];
   imedia::position tkNotePosition;
   int iStart = 0;
   int iEnd = m_tkaNotesPosition.get_size() - 1;
   if(iStart == iEnd)
   {

   }
   int iMid;
   // Encontra a nota mais localizada na mesma posição
   // ou mais próxima de tkTokenPosition
   while(iStart < iEnd)
   {
      iMid = (iEnd + iStart) / 2;
      tkNotePosition = m_tkaNotesPosition[iMid];
      if(tkTokenPosition > tkNotePosition)
      {
         iStart = iMid + 1;
      }
      else if(tkTokenPosition < tkNotePosition)
      {
         iEnd = iMid - 1;
      }
      else
      {
         break;
      }
   }
   // Encontra a nota localizada imediatamente depois
   // ou na mesma posição de tkTokenPosition
   while(m_tkaNotesPosition[iMid] < tkNotePosition)
   {
      iMid++;
   }
   // Se notas consecutivas estão na mesma posição,
   // toma a primeira das notas.
   while(iMid >= 1)
   {
      if(m_tkaNotesPosition[iMid - 1] == tkNotePosition)
      {
         iMid--;
      }
      else
         break;
   }
   // Encontrou primeira nota do token.
   *piStartNote = iMid;
   // Encontra a última nota do token.
   iTokenIndex++;
   if(iTokenIndex >= m_tkaTokensPosition.get_size())
   {
      *piNotesCount = m_tkaNotesPosition.get_size() - *piStartNote;
      return;
   }
   tkTokenPosition = m_tkaTokensPosition[iTokenIndex];
   int iNotesCount = 0;
   while(m_tkaNotesPosition[iMid] < tkTokenPosition)
   {
      iNotesCount++;
      iMid++;
      if(iMid >= m_tkaNotesPosition.get_size())
         break;
   }
   *piNotesCount = iNotesCount;
}*/

/*void LyricEventsV2::GetTokenNotes(int *piStartNote, int *piNotesCount, int iTokenIndex)
{
   *piStartNote = m_dwaTokensFirstNote[iTokenIndex];
   *piNotesCount = m_dwaTokensNotesCount[iTokenIndex];

}*/
void LyricEventsV2::PrepareForScoring(ikar::karaoke * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);

   if(m_msaTokensPosition.get_size() <= 0 ||
      m_msaNotesPosition.get_size() <= 0)
      return;
   int iNote, iToken;//, k;;
   imedia::time msTokenPosition, msNextTokenPosition;
   imedia::time msNotePosition, msNextNotePosition; //, msLastNotePosition;
   //DWORD msNoteDuration;
//   DWORD msTokenDuration;
   // Corta a duração das notas se necessário,
   // de forma que a duração não passe dos limites
   // de duração do próximo token ou nota.
   // Também corta a duração do token se passara
   // da duração da última nota.
/*   msTokenPosition = m_msaTokensPosition[0];
   msNotePosition = m_msaNotesPosition[0];
   for(i = 1, iNote = 1;; i++)
   {
      if(iNote > m_msaNotesPosition.get_size())
         break;
      else if(iNote == m_msaNotesPosition.get_size())
         msNextNotePosition = 0x7fffffff;
      else
         msNextNotePosition = m_msaNotesPosition[iNote];

      if(i > m_msaTokensPosition.get_size())
         break;
      else if (i == m_msaTokensPosition.get_size())
         msNextTokenPosition = 0x7fffffff;
      else
         msNextTokenPosition = m_msaTokensPosition[i];


      k  = 0;
//      while(msNotePosition >= msTokenPosition &&
//         msNotePosition < msNextTokenPosition)
         while(msNotePosition < msNextTokenPosition)
      {
         msNoteDuration = m_msaNotesDuration[iNote - 1];
         if(msNoteDuration > msNextNotePosition - msNotePosition)
         {
            msNoteDuration = msNextNotePosition - msNotePosition;
            m_msaNotesDuration[iNote - 1] = msNoteDuration;
         }
         if(msNoteDuration > msNextTokenPosition - msNotePosition)
         {
            msNoteDuration = msNextTokenPosition - msNotePosition;
            m_msaNotesDuration[iNote - 1] = msNoteDuration;
         }
         msLastNotePosition = msNotePosition;
         msNotePosition = msNextNotePosition;
         k++;
         iNote++;
         if(iNote >= m_msaNotesPosition.get_size())
            break;
         msNextNotePosition = m_msaNotesPosition[iNote];
      }
      msTokenDuration = m_msaTokensDuration[i - 1];
      if((msTokenPosition + msTokenDuration > msLastNotePosition + msNoteDuration) &&
         (k > 0))
      {
         m_msaTokensDuration[i - 1] = msLastNotePosition + msNoteDuration - msTokenPosition;
      }
      msTokenPosition = msNextTokenPosition;
//      if(iNote > m_msaNotesPosition.get_size())
//         break;
   } */
// Preenche as matrizes m_dwaNotesToken,
   // m_dwaTokensFirstNote e m_dwaTokensNotesCount
   // para refletir o mapeamento entre tokens
   // e notas.
   msTokenPosition = m_msaTokensPosition[0];
   msNotePosition = m_msaNotesPosition[0];
   for(iToken = 1, iNote = 1; ; iToken++)
   {
      if(iNote > m_msaNotesPosition.get_size())
         break;
      else if(iNote == m_msaNotesPosition.get_size())
         msNextNotePosition = 0x7fffffff;
      else
         msNextNotePosition = m_msaNotesPosition[iNote];

      if(iToken > m_msaTokensPosition.get_size())
         break;
      else if (iToken == m_msaTokensPosition.get_size())
         msNextTokenPosition = 0x7fffffff;
      else
         msNextTokenPosition = m_msaTokensPosition[iToken];

      while(msNotePosition < msNextTokenPosition)
      {
         if(msNotePosition >= msTokenPosition)
         {
            add_token_note(iToken - 1, iNote - 1);
         }
         iNote++;
         if(iNote >= m_msaNotesPosition.get_size())
         {
            break;
         }
         msNotePosition = msNextNotePosition;
         msNextNotePosition = m_msaNotesPosition[iNote];
      }
      msTokenPosition = msNextTokenPosition;
   }

   if(iNote <= m_msaNotesPosition.get_size() &&
      iToken <= m_msaTokensPosition.get_size())
   {
      while(true)
      {
         add_token_note(iToken - 1, iNote - 1);
         iNote++;
         if(iNote >= m_msaNotesPosition.get_size())
         {
            break;
         }
      }
      iToken++;
   }
   while(iToken <= m_msaTokensPosition.get_size())
   {
      add_token_note(iToken - 1, m_msaNotesPosition.get_size() - 1);
      iToken++;
   }


}


void LyricEventsV2::PrepareForLyricsDisplay(ikar::karaoke * pinterface)
{
   UNREFERENCED_PARAMETER(pinterface);

   if(m_msaTokensPosition.get_size() <= 0 ||
      m_msaNotesPosition.get_size() <= 0)
      return;

   int iNoteIndex;

   int iToken, iNextToken;
   int iNote, iNextNote;

   imedia::time timeToken, timeNextToken;
   imedia::time timeNote, timeNextNote, timeLastNote;
   imedia::time timeNoteDuration, timeTokenDuration;
   imedia::time timeLongestNoteDuration;
   imedia::time timeLBound;
   imedia::time timeSpan;
   base_array<DWORD, DWORD> dwSamePositionNotes;

   imedia::position positionToken, positionNextToken;
   imedia::position positionNote, positionNextNote, positionLastNote;
   imedia::position positionNoteDuration, positionTokenDuration;
   imedia::position positionLBound;
   imedia::position positionSpan;

   imedia::position_array & positionaToken   = m_tkaTokensPosition;
   imedia::position_array & positionaNote    = m_tkaNotesPosition;

   imedia::time_array & timeaToken   = m_msaTokensPosition;
   imedia::time_array & timeaNote    = m_msaNotesPosition;

   // remove same position notes leaving the longest note.



   iToken      = 0;
   iNextToken  = 1;
   iNote       = 0;
   iNextNote   = 1;


   for(;;iNote++)
   {
      iNextToken     = iToken + 1;
      iNextNote      = iNote + 1;

      // Calculate the next token position
      if(iNextToken > positionaToken.get_size())
         break;
      else if (iNextToken == positionaToken.get_size())
      {
         positionNextToken = 0x7fffffff;
         timeNextToken     = 0x7fffffff;
      }
      else
      {
         positionNextToken = positionaToken[iNextToken];
         timeNextToken     = timeaToken[iNextToken];
      }

      // Calculate the next note position
      if(iNextNote > positionaNote.get_size())
         break;
      else if(iNextNote == positionaNote.get_size())
      {
         positionNextNote  = 0x7fffffff;
         timeNextNote      = 0x7fffffff;
      }
      else
      {
         positionNextNote  = positionaNote[iNextNote];
         timeNextNote      = timeaNote[iNextNote];
      }

      positionToken     = positionaToken   [iToken];
      positionNote      = positionaNote    [iNote];

      timeToken         = timeaToken   [iToken];
      timeNote          = timeaNote    [iNote];

      // Detect same position notes.
      if(positionNextNote == positionNote)
      {
         while(positionNextNote == positionNote)
         {
            if(dwSamePositionNotes.get_size() == 0)
            {
               dwSamePositionNotes.add(iNote);
            }
            dwSamePositionNotes.add(iNextNote);

            iNote++;
            iNextNote++;

            // Calculate the next note position
            if(iNextNote > positionaNote.get_size())
               break;
            else if(iNextNote == positionaNote.get_size())
            {
               positionNextNote  = 0x7fffffff;
               timeNextNote      = 0x7fffffff;
            }
            else
            {
               positionNextNote  = positionaNote[iNextNote];
               timeNextNote      = timeaNote[iNextNote];
            }

            positionNote   = positionaNote[iNote];
            timeNote       = timeaNote[iNote];

         }
         if (dwSamePositionNotes.get_size() > 0)
         {

            iNoteIndex = dwSamePositionNotes.element_at(0);
            timeLongestNoteDuration = m_msaNotesDuration[iNoteIndex];

            // remove all notes after the first same position note
            for(;dwSamePositionNotes.get_size() > 1;)
            {
               iNoteIndex = dwSamePositionNotes.element_at(dwSamePositionNotes.get_size() - 1);
               if(iNoteIndex >= m_dwaNotesData.get_count())
                  break;
               m_dwaNotesData.remove_at(iNoteIndex);
               if(m_msaNotesDuration[iNoteIndex] > timeLongestNoteDuration)
               {
                  timeLongestNoteDuration = m_msaNotesDuration[iNoteIndex];
               }
               m_msaNotesDuration.remove_at(iNoteIndex);
               m_msaNotesPosition.remove_at(iNoteIndex);
               m_tkaNotesPosition.remove_at(iNoteIndex);
               dwSamePositionNotes.remove_at(dwSamePositionNotes.get_size() - 1);

            }

            iNoteIndex = dwSamePositionNotes.element_at(0);
            m_msaNotesDuration[iNoteIndex] = timeLongestNoteDuration;
            iNextNote = iNoteIndex + 1;
            dwSamePositionNotes.remove_at(0);
         }
      }
   }


   // Clip notes to token bounds
   // set notes durations consecutive until the
   // last token note.

   positionLastNote = 0;


   iToken      = 0;
   iNextToken  = 1;
   iNote       = 0;
   iNextNote   = 1;


   for(;;iToken++)
   {
      iNextToken     = iToken + 1;
      iNextNote      = iNote + 1;

      // Calculate the next token position
      if(iNextToken >= positionaToken.get_size())
         break;

      // Calculate the next note position
      if(iNextNote >= positionaNote.get_size())
         break;

      int iStartNote = iNote;
      // Clip notes to token bounds
      while(m_msaNotesPosition[iNote] < ((int)m_msaTokensPosition[iNextToken] - 50))
      {
         if(iStartNote == iNote)
         {
            m_msaNotesPosition[iNote] = m_msaTokensPosition[iToken];
            m_tkaNotesPosition[iNote] = m_tkaTokensPosition[iToken];
         }

         if(m_msaNotesDuration[iNote] + m_msaNotesPosition[iNote] >
            ((int)m_msaTokensPosition[iNextToken] - 50))
         {
            m_msaNotesDuration[iNote] = (int)m_msaTokensPosition[iNextToken] - (int)m_msaNotesPosition[iNote] - 50;
         }

         iNote++;
         iNextNote++;

         if(iNextNote >= positionaNote.get_size())
            break;

      }
      for(int i = iStartNote; i < iNote - 1; i++)
      {
         m_msaNotesDuration[i] = m_msaNotesPosition[i + 1] - m_msaNotesPosition[i];
      }
      if(m_msaTokensDuration[iToken] > m_msaTokensPosition[iNextToken] - m_msaTokensPosition[iToken])
      {
         m_msaTokensDuration[iToken] = m_msaTokensPosition[iNextToken] - m_msaTokensPosition[iToken];
      }
      if(iNextNote > positionaNote.get_size())
         break;
   }





   // create the mapping between tokens and notes
   iToken      = 0;
   iNextToken  = 1;
   iNote       = 0;
   iNextNote   = 1;


   for(;;iToken++)
   {
      iNextToken     = iToken + 1;
      iNextNote      = iNote + 1;

      // Calculate the next token position
      if(iNextToken > positionaToken.get_size())
         break;
      else if (iNextToken == positionaToken.get_size())
         positionNextToken = 0x7fffffff;
      else
         positionNextToken = positionaToken[iNextToken];

      // Calculate the next note position
      if(iNextNote > positionaNote.get_size())
         break;
      else if(iNextNote == positionaNote.get_size())
         positionNextNote = 0x7fffffff;
      else
         positionNextNote = positionaNote[iNextNote];

      positionToken      = positionaToken   [iToken];
      positionNote       = positionaNote    [iNote];

      if(positionNote < positionNextToken)
      {
         // It already exists at least one note for the token.
         // add the note(s).
         while(positionNote < positionNextToken)
         {
            add_token_note(iToken, iNote);

            // Calculate the next note position

            iNote++;
            iNextNote++;


            if(iNextNote > positionaNote.get_size())
               break;
            else if(iNextNote == positionaNote.get_size())
               positionNextNote = 0x7fffffff;
            else
               positionNextNote = positionaNote[iNextNote];

            positionNote = positionaNote[iNote];
         }
      }
      else
      {
         // There is no notes associated with the token.
         //XXXASSERT(FALSE);
      }
   }

}










void LyricEventsV2::PrepareForBouncingBall(ikar::karaoke * pinterface)
{

   if(m_msaTokensPosition.get_size() <= 0 ||
      m_msaNotesPosition.get_size() <= 0)
      return;

   int iNoteIndex;

   int iToken, iNextToken;
   int iNote, iNextNote;

   imedia::time timeToken, timeNextToken;
   imedia::time timeNote, timeNextNote, timeLastNote;
   imedia::time timeNoteDuration, timeTokenDuration;
   imedia::time timeLongestNoteDuration;
   imedia::time timePosition;
   imedia::time timeDuration;
   imedia::time timeSpan;
   base_array<DWORD, DWORD> dwSamePositionNotes;

   imedia::position positionToken, positionNextToken;
   imedia::position positionNote, positionNextNote, positionLastNote;
   imedia::position positionNoteDuration, positionTokenDuration;
   imedia::position positionLBound;
   imedia::position positionSpan;

   imedia::position_array & positionaToken   = m_tkaTokensPosition;
   imedia::position_array & positionaNote    = m_tkaNotesPosition;

   imedia::time_array & timeaToken   = m_msaTokensPosition;
   imedia::time_array & timeaNote    = m_msaNotesPosition;

   // remove same position notes leaving the longest note.



   iToken      = 0;
   iNextToken  = 1;
   iNote       = 0;
   iNextNote   = 1;


   for(;;iNote++)
   {
      iNextToken     = iToken + 1;
      iNextNote      = iNote + 1;

      // Calculate the next token position
      if(iNextToken > positionaToken.get_size())
         break;
      else if (iNextToken == positionaToken.get_size())
      {
         positionNextToken = 0x7fffffff;
         timeNextToken     = 0x7fffffff;
      }
      else
      {
         positionNextToken = positionaToken[iNextToken];
         timeNextToken     = timeaToken[iNextToken];
      }

      // Calculate the next note position
      if(iNextNote > positionaNote.get_size())
         break;
      else if(iNextNote == positionaNote.get_size())
      {
         positionNextNote  = 0x7fffffff;
         timeNextNote      = 0x7fffffff;
      }
      else
      {
         positionNextNote  = positionaNote[iNextNote];
         timeNextNote      = timeaNote[iNextNote];
      }

      positionToken     = positionaToken   [iToken];
      positionNote      = positionaNote    [iNote];

      timeToken         = timeaToken   [iToken];
      timeNote          = timeaNote    [iNote];

      // Detect same position notes.
      if(positionNextNote == positionNote)
      {
         while(positionNextNote == positionNote)
         {
            if(dwSamePositionNotes.get_size() == 0)
            {
               dwSamePositionNotes.add(iNote);
            }
            dwSamePositionNotes.add(iNextNote);

            iNote++;
            iNextNote++;

            // Calculate the next note position
            if(iNextNote > positionaNote.get_size())
               break;
            else if(iNextNote == positionaNote.get_size())
            {
               positionNextNote  = 0x7fffffff;
               timeNextNote      = 0x7fffffff;
            }
            else
            {
               positionNextNote  = positionaNote[iNextNote];
               timeNextNote      = timeaNote[iNextNote];
            }

            positionNote   = positionaNote[iNote];
            timeNote       = timeaNote[iNote];

         }
         if (dwSamePositionNotes.get_size() > 0)
         {

            iNoteIndex = dwSamePositionNotes.element_at(0);
            timeLongestNoteDuration = m_msaNotesDuration[iNoteIndex];

            // remove all notes after the first same position note
            for(;dwSamePositionNotes.get_size() > 1;)
            {
               iNoteIndex = dwSamePositionNotes.element_at(dwSamePositionNotes.get_size() - 1);
               if(iNoteIndex >= m_dwaNotesData.get_count())
                  break;
               m_dwaNotesData.remove_at(iNoteIndex);
               if(m_msaNotesDuration[iNoteIndex] > timeLongestNoteDuration)
               {
                  timeLongestNoteDuration = m_msaNotesDuration[iNoteIndex];
               }
               m_msaNotesDuration.remove_at(iNoteIndex);
               m_msaNotesPosition.remove_at(iNoteIndex);
               m_tkaNotesPosition.remove_at(iNoteIndex);
               dwSamePositionNotes.remove_at(dwSamePositionNotes.get_size() - 1);

            }

            iNoteIndex = dwSamePositionNotes.element_at(0);
            m_msaNotesDuration[iNoteIndex] = timeLongestNoteDuration;
            iNextNote = iNoteIndex + 1;
            dwSamePositionNotes.remove_at(0);
         }
      }
   }


   // Clip notes to token bounds
   // set notes durations consecutive until the
   // last token note.

   positionLastNote = 0;


   iToken      = 0;
   iNextToken  = 1;
   iNote       = 0;
   iNextNote   = 1;


   for(;;iToken++)
   {
      iNextToken     = iToken + 1;
      iNextNote      = iNote + 1;

      // Calculate the next token position
      if(iNextToken >= positionaToken.get_size())
         break;

      // Calculate the next note position
      if(iNextNote >= positionaNote.get_size())
         break;

      timeNote       = m_msaNotesPosition[iNote];
      timeNextToken  = m_msaTokensPosition[iNextToken];

      int iStartNote = iNote;
      // Clip notes to token bounds
      while(timeNote < ((int)timeNextToken - 50))
      {
         if(iStartNote == iNote)
         {
            m_msaNotesPosition[iNote] = m_msaTokensPosition[iToken];
            m_tkaNotesPosition[iNote] = m_tkaTokensPosition[iToken];
         }

         timeDuration = (int)m_msaTokensPosition[iNextToken] - (int)m_msaNotesPosition[iNote];

         m_msaNotesDuration[iNote] = timeDuration;

         iNote++;
         iNextNote++;

         if(iNextNote >= positionaNote.get_size())
            break;

      }
      int i;
      for(i = iStartNote; i < iNote; i++)
      {
         timeDuration = (int)m_msaNotesPosition[i + 1] - (int)m_msaNotesPosition[i];
         m_msaNotesDuration[i] = timeDuration;
      }
      if(iToken >= 0)
      {
         if(m_msaTokensDuration[iToken] > m_msaTokensPosition[iNextToken] - m_msaTokensPosition[iToken])
         {
            m_msaTokensDuration[iToken] = m_msaTokensPosition[iNextToken] - m_msaTokensPosition[iToken];
         }
      }
      if(iNextNote > positionaNote.get_size())
         break;
   }

   imedia::position tkQuarterNote = pinterface->GetQuarterNote();


   m_dwaBeatNote.remove_all();

   iNote       = -1;

   int iOffset = 0;
   imedia::position tkStart = 0;

   while(true)
   {
      iNextNote      = iNote + 1;
      if(iNextNote >= positionaNote.get_size())
         break;

      bool bAlreadyBeatNote = (tkStart % tkQuarterNote) < (tkQuarterNote / 16);
      if(!bAlreadyBeatNote || tkStart == 0)
      {
         imedia::position tkAdd = tkQuarterNote;
         while(true)
         {
            imedia::position tkBeg = (tkStart % tkQuarterNote) + tkAdd;
            imedia::position tkEnd = tkBeg + tkQuarterNote;
            if((tkBeg - tkStart) >= (tkQuarterNote / 2)
            && (m_tkaNotesPosition[iNextNote] - tkEnd) >= (tkQuarterNote / 2))
            {
               m_tkaNotesPosition.insert_at(iNote + 1, tkBeg);
               timePosition = pinterface->PositionToTime(tkBeg);
               m_msaNotesPosition.insert_at(iNote + 1, timePosition);
               timeDuration = (int) pinterface->PositionToTime(tkEnd) - timePosition;
               m_msaNotesDuration.insert_at(iNote + 1, timeDuration);
               m_dwaBeatNote.add(iNote + 1);
               m_riiNoteBeat.spread(iNote - iOffset, iNote + 1);
               iNote++;
               iNextNote++;
               iOffset++;
               tkAdd += tkQuarterNote;
            }
            else
            {
               break;
            }
         }
      }
      m_riiNoteBeat.spread(iNote - iOffset - 1, iNote);
      iNote++;
      if(iNote >= positionaNote.get_size())
         break;
      tkStart = m_tkaNotesPosition[iNote];
   }



   // create the mapping between tokens and notes
   iToken      = -1;
   iNextToken  = 1;
   iNote       = 0;
   iNextNote   = 1;


   for(;;iToken++)
   {
      iNextToken     = iToken + 1;
      iNextNote      = iNote + 1;

      // Calculate the next token position
      if(iNextToken > positionaToken.get_size())
         break;
      else if (iNextToken == positionaToken.get_size())
         positionNextToken = 0x7fffffff;
      else
         positionNextToken = positionaToken[iNextToken];

      // Calculate the next note position
      if(iNextNote > positionaNote.get_size())
         break;
      else if(iNextNote == positionaNote.get_size())
         positionNextNote = 0x7fffffff;
      else
         positionNextNote = positionaNote[iNextNote];

      if(iToken < 0)
         positionToken = 0;
      else
         positionToken      = positionaToken   [iToken];
      positionNote       = positionaNote    [iNote];

      // It already exists at least one note for the token.
      // add the note(s).
      while(positionNote < positionNextToken)
      {
         add_token_note(iToken, iNote);

         // Calculate the next note position

         iNote++;
         iNextNote++;


         if(iNextNote > positionaNote.get_size())
            break;
         else if(iNextNote == positionaNote.get_size())
            positionNextNote = 0x7fffffff;
         else
            positionNextNote = positionaNote[iNextNote];

         positionNote = positionaNote[iNote];
      }
   }


}

imedia::position LyricEventsV2::GetCurrentTkNotePosition()
{
   if(m_iCurrentNote < 0)
      return 0x7fffffff;
   if(m_iCurrentNote >= m_tkaNotesPosition.get_size())
      return 0x7fffffff;
   return m_tkaNotesPosition.get_at(m_iCurrentNote);
}

imedia::position LyricEventsV2::GetNextTkNotePosition()
{
   if(m_iCurrentNote + 1 < 0)
      return 0x7fffffff;
   if(m_iCurrentNote + 1 >= m_tkaNotesPosition.get_size())
      return 0x7fffffff;
   return m_tkaNotesPosition.get_at(m_iCurrentNote + 1);
}

void LyricEventsV2::Reset()
{
   LyricEventsV1::Reset();
   m_msaNotesDuration.remove_all();
   m_msaNotesPosition.remove_all();
   m_msaTokensDuration.remove_all();
   m_msaTokensPosition.remove_all();
}

int LyricEventsV2::GetClassOrder()
{
   return 2;
}


BYTE LyricEventsV2::GetNotePitch(int iIndex)
{
   DWORD dw = m_dwaNotesData.get_at(iIndex);
   return (BYTE) ((dw & 0x0000ff00) >> 8);
}
void LyricEventsV2::GetMillisNotes_(
   int *piStartNote,
   int *piNotesCount,
   imedia::time msMin,
   imedia::time msMax)
{
   imedia::time msNotePosition;
   int iStart = 0;
   int iEnd = m_msaNotesPosition.get_size() - 1;
   if(iStart == iEnd)
   {

   }
   int iMid;
   // Encontra a nota mais localizada na mesma posição
   // ou mais próxima de tkTokenPosition
   while(iStart < iEnd)
   {
      iMid = (iEnd + iStart) / 2;
      msNotePosition = m_msaNotesPosition[iMid];
      if(msMin > msNotePosition)
      {
         iStart = iMid + 1;
      }
      else if(msMin < msNotePosition)
      {
         iEnd = iMid - 1;
      }
      else
      {
         break;
      }
   }
   if(iMid >= m_msaNotesPosition.get_size())
      iMid = m_msaNotesPosition.get_size() - 1;
   else if(iMid < 0)
      iMid = 0;

   while(m_msaNotesPosition[iMid] > msMin)
   {
      if(iMid == 0)
         break;
      iMid--;
   }
   // Encontra a nota localizada imediatamente depois
   // ou na mesma posição de tkTokenPosition
   while(m_msaNotesPosition[iMid] < msMin)
   {
      iMid++;
      if(iMid >= m_msaNotesPosition.get_size())
      {
         iMid = m_msaNotesPosition.get_size() - 1;
         break;
      }
   }
   // Se notas consecutivas estão na mesma posição,
   // toma a primeira das notas.
   while(iMid >= 1)
   {
      if(m_msaNotesPosition[iMid - 1] == msMin)
      {
         iMid--;
      }
      else
         break;
   }
   // Encontrou primeira nota do token.
   *piStartNote = iMid;
   // Encontra a última nota do token.
//   iMid++;
//   if(iMid >= m_msaNotesPosition.get_size())
//   {
//      *piNotesCount = m_msaNotesPosition.get_size() - *piStartNote;
//      return;
//   }
   msNotePosition = m_msaNotesPosition[iMid];
   int iNotesCount = 0;
   while(m_msaNotesPosition[iMid] <= msMax)
   {
      iNotesCount++;
      iMid++;
      if(iMid >= m_msaNotesPosition.get_size())
         break;
   }
   *piNotesCount = iNotesCount;

}

void LyricEventsV2::GetMillisIntervalNotes(
   int_array  & iaIndexes,
   imedia::time msMin,
   imedia::time msMax)
{
   int iNote = 0;
   if(iNote >= m_msaNotesPosition.get_size())
      return;
   while(m_msaNotesPosition[iNote] + m_msaNotesDuration[iNote] < msMin)
   {
      iNote++;
      if(iNote >= m_msaNotesPosition.get_size())
         return;
   }
   while(m_msaNotesPosition[iNote] < msMax)
   {
      if( (m_msaNotesPosition[iNote] > msMin) ||
         (m_msaNotesPosition[iNote] + m_msaNotesDuration[iNote] > msMin))
      {
         iaIndexes.add(iNote);
      }
      iNote++;
      if(iNote >= m_msaNotesPosition.get_size())
         return;
   }

}

imedia::time LyricEventsV2::GetTotalNotesMillis()
{
   imedia::time dwRet = 0;
   for(int i = 0; i < m_msaNotesDuration.get_size(); i++)
   {
      dwRet += m_msaNotesDuration[i];
   }
   return dwRet;

}

void LyricEventsV2::swap(void *lpVoidSwapArg, int iA, int iB)
{
   LyricEventsV2 * pThis = (LyricEventsV2 *) lpVoidSwapArg;
   pThis->m_dwaNotesData.swap(iA, iB);
   pThis->m_msaNotesDuration.swap(iA, iB);
   //   CBaseSort::swap(pThis->m_msaNotesPosition, iA, iB);
   pThis->m_tkaNotesPosition.swap(iA, iB);
}

int LyricEventsV2::GetNoteFirstToken(int iNote)
{
   unique_int_sort_array & ia = GetNoteTokenArray(iNote);
   if(ia.get_size() > 0)
      return ia.get_at(0);
   else
      return 0x7fffffff;
}


int LyricEventsV2::GetPositionNote(imedia::position tkPosition)
{
    int i = 0;
    while(i < m_tkaNotesPosition.get_size())
    {
        if(tkPosition < m_tkaNotesPosition.get_at(i))
            break;
        i++;
    }
    return i - 1;
}

int LyricEventsV2::GetPositionToken(imedia::position tkPosition)
{
    int i = 0;
    while(i < m_tkaTokensPosition.get_size())
    {
        if(tkPosition < m_tkaTokensPosition.get_at(i))
            break;
        i++;
    }
    return i - 1;
}


void LyricEventsV2::add_token_note(int iToken, int iNote)
{
   m_riiTokenNote.spread(iToken, iNote);
}
