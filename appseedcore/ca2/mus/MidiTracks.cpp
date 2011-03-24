#include "StdAfx.h"
#include <math.h> 

BYTE MidiTracks::m_paramEventNoteOnPositionCB[] = {EVENT_ID_NOTE_ON};
int MidiTracks::m_iparamEventNoteOnPositionCB = 1;

MidiTracks::MidiTracks(::ca::application * papp, ::mus::midi::file * pFile) :
   ca(papp), 
   m_tracka(papp)
{
   m_tracka.Initialize(this);
   m_trackaActive.Initialize(this);

   m_tkLevelLastUpdateInterval = 0;
   m_iaLevel.set_size(16);
   m_iaNoteOn.set_size(16);
   m_iaInstrument.set_size(16);

   m_pFile = pFile;
   m_tkPosition = 0;
   m_iLyricDelay = 0;
   m_bVolumeEventSent = false;

}

MidiTracks::~MidiTracks()
{
}

#ifdef _DEBUG

void MidiTracks::dump(dump_context & dumpcontext) const
{
   dumpcontext << "\n";
   dumpcontext << "\n";
   dumpcontext << "MidiTracks";
   dumpcontext << "\n";
   for(int i = 0; i < GetMidiTrackCount(); i++)
   {
      MidiTrack * ptrack = (MidiTrack *) MidiTrackAt(i);
      dumpcontext << "MidiTrack " << i;
      dumpcontext << "\n";
      ptrack->dump(dumpcontext);
   }
}

#endif

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

/******************************************************************************
*
* smfGetNextEvent
*
* read the next event from the given spfile->
*
* pSmf                      - File to read the event from.
*
* pEvent                    - Pointer to an event structure which will receive
*                             basic information about the event.
*
* tkMax                     - Tick destination. An attempt to read past this
*                             position in the file will fail.
*
* Returns
*   ::mus::midi::Success The events were successfully read.
*   ::mus::midi::SEndOfFile There are no more events to read in this track.
*   ::mus::midi::SReachedTkMax No event was read because <p tkMax> was reached.
*   ::mus::midi::InvalidFile A disk or parse error occured on the spfile->
*
* This is the lowest level of parsing for a raw MIDI stream. The basic
* information about one event in the file will be returned in pEvent.
*
* Merging data from all tracks into one stream is performed here.
* 
* pEvent->tkDelta will contain the tick delta for the event.
*
* pEvent->abEvent will contain a description of the event.
*  pevent->abEvent[0] will contain
*    F0 or F7 for a System Exclusive message.
*    FF for a MIDI file meta event.
*    The status byte of any other MIDI message. (Running status will
*    be tracked and expanded).
*
* pEvent->cbParm will contain the number of bytes of paramter data
*   which is still in the file behind the event header already read.
*   This data may be read with <f smfGetTrackEventData>. Any unread
*   data will be skipped on the next call to <f smfGetNextTrackEvent>.
*
* Channel messages (0x8? - 0xE?) will always be returned fully in
*   pevent->abEvent.
*
*  Meta events will contain the meta type in pevent->abEvent[1].
*
*  System exclusive events will contain only an 0xF0 or 0xF7 in
*    pevent->abEvent[0].
*
*  The following fields in ptrack are used to maintain state and must
*  be updated if a seek-in-track is performed:
*
*  bRunningStatus contains the last running status message or 0 if
*   there is no valid running status.
*
*  hpbImage is a pointer into the file image of the first byte of
*   the event to follow the event just read.
*
*  dwLeft contains the number of bytes from hpbImage to the end
*   of the track.
*
*
* get the next due event from all (in-use?) tracks
*
* For all tracks
*  If not end-of-track
*   decode event delta time without advancing through buffer
*   event_absolute_time = track_tick_time + track_event_delta_time
*   relative_time = event_absolute_time - last_stream_time
*   if relative_time is lowest so far
*    save this track as the next to pull from, along with times
*
* If we found a track with a due event
*  Advance track pointer past event, saving ptr to parm data if needed
*  track_tick_time += track_event_delta_time
*  last_stream_time = track_tick_time
* Else
*  Mark and return end_of_file
*
*****************************************************************************/
::mus::midi::e_file_result MidiTracks::GetNextEvent(
   MidiEventV001 *&         pevent,
   imedia::position                   tkMax,
   BOOL                     bTkMaxInclusive,
   bool                    bOnlyMTrk,
   bool                    bOnlyMidiTrack)
{
   MidiTrackBase *      ptrack;
   MidiTrackBase *      ptrkFound;
   int                  idxTrackFound;
   int                  idxTrack;
//    imedia::position                   tkEventDelta;
   imedia::position                tkEventPosition;
   imedia::position                  tkEventFound;
   int                  iRelTime;
   int                  iMinRelTime;
   ::mus::midi::e_file_result  mfr;

   ASSERT(pevent != NULL);


    iMinRelTime = 0x7fffffff;
   ptrkFound = NULL;

   for (idxTrack = 0; idxTrack < GetTrackCount(); idxTrack++)
    {
      ptrack = TrackAt(idxTrack);
        if(bOnlyMTrk)
        {
           if(ptrack->IsType(MidiTrackBase::TypeMidi))
            {
                MidiTrack * ptrackMidi = (MidiTrack *) ptrack;
                CHUNKHDR FAR * pCh = (CHUNKHDR FAR *) ptrackMidi->GetTrackImage();
                if (pCh->fourccType != FOURCC_MTrk)
                 continue;
            }
        }
        else if(bOnlyMidiTrack)
        {
           if(!ptrack->IsType(MidiTrackBase::TypeMidi))
                continue;
        }
            
        if (ptrack->GetFlags().is_signalized(::mus::midi::EndOfTrack))
            continue;
        

        if(ptrack->GetPosition(tkEventPosition, tkMax) != VMSR_SUCCESS)
        {
            continue;
        }
        
        iRelTime = tkEventPosition - m_tkPosition;
      ASSERT(iRelTime >= 0);

        if (iRelTime < iMinRelTime)
        {
            iMinRelTime = iRelTime;
            ptrkFound = ptrack;
         idxTrackFound = idxTrack;
         tkEventFound = tkEventPosition;
        }
    }

    if (ptrkFound == NULL)
    {
        return ::mus::midi::SEndOfFile;
    }

    ptrack = ptrkFound;

    imedia::position tkPosition = tkEventFound;

    iRelTime = tkPosition - m_tkPosition;
   ASSERT(iRelTime >= 0);
    if(iRelTime < 0)
        iRelTime = 0;

   if(!GetFlags().is_signalized(::mus::midi::DisablePlayLevel1Operations))
   {
      if(iRelTime != 0)
      {
         m_tkLevelLastUpdateInterval += iRelTime;
         if(m_tkLevelLastUpdateInterval > 24)
         {
            m_tkLevelLastUpdateInterval = 0;
            if(!m_bVolumeEventSent)
            {
               return GetVolumeEvent(get_app(), pevent);
            }
            else
            {
               m_bVolumeEventSent = false;
            }
         }
      }
      else
      {
         m_bVolumeEventSent = false;
      }
   }


   if(ptrack->get_type() == MidiTrackBase::TypeLyric)
    {
        ASSERT(true);
    }

   if(bTkMaxInclusive)
   {
      if (m_tkPosition + iMinRelTime > tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition + iMinRelTime >= tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
    
   mfr = ptrack->GetEvent(pevent, tkMax, bTkMaxInclusive);

   if(pevent->GetParamSize() == 21)
   {
//      AfxDebugBreak();
   }
   if(mfr != ::mus::midi::Success)
      return mfr;

   //pevent->operator =(*ptrack->GetEvent());




   
   pevent->SetDelta(iRelTime);
   m_tkPosition += iRelTime;
    m_iCurrentTrack = idxTrackFound;
   ptrack->MoveNext();
    return ::mus::midi::Success;
}

::mus::midi::e_file_result MidiTracks::GetNextEvent(
   MidiEventV001 *&    pevent,
   imedia::position                tkMax, 
   BOOL                 bTkMaxInclusive,
   int                  iTrack)
{
   MidiTrackBase *      ptrack;
   MidiTrackBase *      ptrkFound;
   int                  idxTrackFound;
   int                  idxTrack;
   imedia::position                tkEventPosition;
   int                  iRelTime;
   int                  iMinRelTime;
   ::mus::midi::e_file_result  mfr;

   while(true)
   {
      iMinRelTime = 0x7fffffff;
      ptrkFound = NULL;
      for (idxTrack = 0; idxTrack < GetTrackCount(); idxTrack++)
      {
         ptrack = TrackAt(idxTrack);
            
         if (ptrack->GetFlags().is_signalized(::mus::midi::EndOfTrack))
            continue;

         if(ptrack->GetPosition(tkEventPosition, tkMax) != VMSR_SUCCESS)
         {
            continue;
         }
        
         iRelTime = tkEventPosition - m_tkPosition;

         if(iRelTime < iMinRelTime)
         {
            iMinRelTime = iRelTime;
            ptrkFound = ptrack;
            idxTrackFound = idxTrack;
         }
      }

      if (ptrkFound == NULL)
      {
         return ::mus::midi::SEndOfFile;
      }

      ptrack = ptrkFound;

      if(ptrack->get_type() == MidiTrackBase::TypeLyric)
      {
         ASSERT(true);
      }

      if(bTkMaxInclusive)
      {
         if(m_tkPosition + iMinRelTime > tkMax)
         {
            return ::mus::midi::SReachedTkMax;
         }
      }
      else
      {
         if(m_tkPosition + iMinRelTime >= tkMax)
         {
            return ::mus::midi::SReachedTkMax;
         }
      }
      //Aten鈬o melhorar!!!!
      //em vez de pegar o evento, simplesmente pul・lo
      mfr = ptrack->GetEvent(pevent, tkMax, bTkMaxInclusive);

      if(mfr != ::mus::midi::Success)
         return mfr;

      imedia::position tkPosition = ptrack->GetPosition();

      iRelTime = tkPosition - m_tkPosition;
      if(iRelTime < 0)
         iRelTime = 0;

      if(pevent != NULL)
      {
         pevent->SetDelta(iRelTime);
      }
      m_tkPosition = m_tkPosition + iRelTime;
      m_iCurrentTrack = idxTrackFound;
      if(m_iCurrentTrack == iTrack)
         break;
   }


   mfr = ptrack->MoveNext();
   if(mfr != ::mus::midi::Success)
      return mfr;

   return ::mus::midi::Success;
}


//
//
//
//
//
//
//
//
//
::mus::midi::e_file_result MidiTracks::GetNextEventTkPosition(
    imedia::position *               pTkPosition,
    imedia::position                   tkMax)
{
   MidiTrackBase *         ptrack;
   MidiTrackBase *         pTrkFound ;
   int                  idxTrack;
    //imedia::position               tkEventDelta;
    imedia::position               tkEventPosition;
    imedia::position               tkEventPositionFound;
    imedia::position                   tkRelTime;
    imedia::position                   tkMinRelTime;
//    DWORD                   dwGot;
    VMSRESULT               vmsr;
    

//    ASSERT(pSmf != NULL);
    ASSERT(pTkPosition != NULL);

    if (GetFlags().is_signalized(::mus::midi::EndOfTrack))
    {
        return ::mus::midi::SEndOfFile;
    }

    pTrkFound       = NULL;
    tkMinRelTime    = MAX_TICKS;
    
    //for (ptrack = m_rTracks, idxTrack = m_dwTracks; idxTrack--; ptrack++)
   for (idxTrack = 0; idxTrack < GetTrackCount(); idxTrack++)
    {
      ptrack = TrackAt(idxTrack);
        if (ptrack->GetFlags().is_signalized(::mus::midi::EndOfTrack))
            continue;

//      if(ptrack->GetState() == MidiTrack::StateOnDelta)
//      {
//         if(ptrack->ReadDelta() != ::mus::midi::Success)
//         {
//            TRACE("Hit end of track w/o end marker!\n");
//               return ::mus::midi::InvalidFile;
//         }
//      }
   
//      tkEventDelta = ptrack->m_tkDelta;
        
        if (VMSR_SUCCESS != (vmsr = ptrack->GetPosition(tkEventPosition, tkMax)))
        {
            continue;
        }

       tkRelTime = tkEventPosition - m_tkPosition;

        if (tkRelTime < tkMinRelTime)
        {
            tkMinRelTime = tkRelTime;
            pTrkFound = ptrack;
            tkEventPositionFound = tkEventPosition;
        }
    }

    if (pTrkFound == NULL)
    {
        GetFlags().signalize(::mus::midi::EndOfTrack);
        return ::mus::midi::SEndOfFile;
    }

    ptrack = pTrkFound;

    if (m_tkPosition + tkMinRelTime > tkMax)
    {
        return ::mus::midi::SReachedTkMax;
    }
        

//    dwGot = ptrack->m_dwUsed;
//   tkEventDelta = ptrack->m_tkDelta;
    //ptrack->cbLeft   -= dwGot;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short event, which is most cases.
    */
    //if (ptrack->cbLeft < 3)
    //{
        //return ::mus::midi::InvalidFile;
    //}

//    *pTkPosition = ptrack->m_tkPosition + tkEventDelta;
    *pTkPosition = tkEventPositionFound;
    return ::mus::midi::Success;
}

void MidiTracks::seek_begin()
{
   for (int i = 0; i < GetTrackCount(); i++)
    {
      MidiTrackBase * ptrack = TrackAt(i);
      ptrack->seek_begin();
    }
    m_tkPosition = 0;
   GetFlags().unsignalize(::mus::midi::EndOfTrack);
}

::mus::midi::e_file_result MidiTracks::GetXFTokens(
      string2a &
            token2a,
      imedia::position_2darray *p2DTicks,
      base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a)
{
   ASSERT(p2DTicks != NULL);
   ASSERT(pxflh2a != NULL);
   stringa  tokena;
   imedia::position_array * lptkaTicks = NULL;
   XFLyricsHeader xflh;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(i);
   if(!ptrack->IsType(MidiTrackBase::TypeMidi))
    {
        continue;
    }

      ptrack->seek_begin();
      ::mus::midi::e_file_result smfr;
      smfr = ptrack->SeekXFLyricsHeader();
      if(smfr == ::mus::midi::Success)
      {
         smfr = ptrack->ReadXFLyricsHeader(&xflh);
      }
      

        tokena.remove_all();
        lptkaTicks = new imedia::position_array();
      if(xflh.m_strLanguage == L"JP")
      {
         smfr = ptrack->ReadShiftJisXFTokens(tokena, lptkaTicks);
      }
      else
      {
         smfr = ptrack->ReadAnsiXFTokens(tokena, lptkaTicks);
      }
      if(::mus::midi::Success == smfr)
      {
         token2a.add(tokena);
         p2DTicks->add(lptkaTicks);
         pxflh2a->add(xflh);
      }
        else
        {
            delete lptkaTicks;
        }
        lptkaTicks = NULL;
   }
   return ::mus::midi::Success;
}

::mus::midi::e_file_result MidiTracks::GetKarTokens(
   string2a &    token2a,
   imedia::position_2darray *       p2DTicks
   )
{
   ASSERT(p2DTicks != NULL);
   stringa tokena;
   imedia::position_array * lptkaTicks = NULL;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->seek_begin();
        tokena.remove_all();
        lptkaTicks = new imedia::position_array();
      if(::mus::midi::Success == ptrack->ReadKarTokens(tokena, lptkaTicks))
      {
         token2a.add(tokena);
         p2DTicks->add(lptkaTicks);
      }
        else
        {
            delete lptkaTicks;
        }
        lptkaTicks = NULL;
   }
   return ::mus::midi::Success;
}


::mus::midi::e_file_result MidiTracks::GetXFInfoHeaders(
   CXFInfoHeaders *pxfihs)
{
   ASSERT(pxfihs != NULL);
   pxfihs->Empty();
   int nIndex, nSize;
   nSize = GetTrackCount();
   //string str lpsz;
   //XFInfoHeader * pxfih;
   //XFInfoHeaderLS * pxfihls;
   XFInfoHeaderLS xfihls;
   for(nIndex = 0; nIndex < nSize; nIndex++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(nIndex);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      if(pxfihs->m_xfInfoHeader.is_empty())
      {
         ptrack->seek_begin();
         ptrack->GetNextXFInfoHeader(&pxfihs->m_xfInfoHeader);
         ptrack->seek_begin();
         ptrack->GetNextXFSongName(pxfihs->m_strSongName);
      }
      ptrack->seek_begin();
      
      if(::mus::midi::Success == ptrack->GetNextXFInfoHeaderLS(&xfihls))
      {
         pxfihs->m_xfaInfoHeaderLS.add(xfihls);
      }
      if(pxfihs->m_strSongName.is_empty())
      {
         ptrack->seek_begin();
         ptrack->GetNextXFSongName(pxfihs->m_strSongName);
      }
   }
   return ::mus::midi::SEndOfFile;

}


::mus::midi::e_file_result MidiTracks::GetKarInfoHeader(
   SoftKaraokeInfo *pKarI)
{
   ASSERT(pKarI != NULL);
   if(GetTrackCount() >=3)
   {
      MidiTrack *ptrack = (MidiTrack *) TrackAt(2);
      ASSERT(ptrack->IsType(MidiTrackBase::TypeMidi));
      return ptrack->GetNextKarInfo(pKarI);
   }
   else
   {
      MidiTrack *ptrack = (MidiTrack *) TrackAt(0);
        ASSERT(ptrack->IsType(MidiTrackBase::TypeMidi));
      return ptrack->GetNextKarInfo(pKarI);
   }

}

::mus::midi::e_file_result MidiTracks::GetTune1000InfoHeader(
   CTune1000Info *pTune1000I, int iTrack)
{
   ASSERT(pTune1000I != NULL);
//   if(GetTrackCount() >=3)
//   {
//      MidiTrack *ptrack = TrackAt(2);
//      return ptrack->GetNextTune1000Info(pTune1000I);
//   }
//   else
//   {
    if(iTrack >= 0 && iTrack < GetTrackCount())
    {
      MidiTrack *ptrack = (MidiTrack *) TrackAt(iTrack);
      ASSERT(ptrack->IsType(MidiTrackBase::TypeMidi));
      return ptrack->GetNextTune1000Info(pTune1000I);
    }
    else
    {
        return ::mus::midi::SNotFound;
    }

//   }

}

int MidiTracks::CalcMelodyTrack(
   MidiEventsV1 ** ppEventsRet,
   imedia::position_array *pTicks,
   WORD wFileFormat)
{
   UNREFERENCED_PARAMETER(wFileFormat);
   ASSERT(*ppEventsRet == NULL);
   int i, j, k, iMatches;
   int iBestMatch;
   dword_array dwaBestMatchesIndexes;
   dword_array dwaBestMatchesScores;
   imedia::position tkTolerance = 0;
   imedia::position tkPositionA, tkPositionB;
   const imedia::position tkToleranceAddUp = WORDSWAP(m_pFile->m_pFileHeader->wDivision) / 4;

   MidiTrack * ptrack;
   MidiEventsV1 * pEvents;
//   primitive_array < MidiEventsV1 *> eventsArray;
   //primitive_array < primitive_array < MidiEventsV1 *>> eventsArray2D;
   
   int2a i2aEventMatch;
   bool bAnyTrack = m_pFile->GetFormat() == 1;
   const int max_tracks_search = 16;
   int iTrack, iTrackCount;
   if(m_pFile->GetFormat() == 1)
   {
      iTrackCount = GetMidiTrackCount();
   }
   else
   {
      iTrackCount = max_tracks_search;
   }

   
   
   
   
   
   int iToleranceStep;
   int iToleranceStepCount;   


   for(iTrack = 0; iTrack < iTrackCount; iTrack++)
   {
      i2aEventMatch.add_new();
      if(m_pFile->GetFormat() == 0)
      {
         ptrack = (MidiTrack *) MidiTrackAt(0);
      }
      else
      {
         if(iTrack >= iTrackCount)
            break;
         ptrack = (MidiTrack *) MidiTrackAt(iTrack);
      }
      pEvents = new MidiEventsV1();
      ptrack->WorkSeekBegin();
      ptrack->WorkGetStandardEventsV1(pEvents, ::mus::midi::NoteOn, iTrack, bAnyTrack);
  //    eventsArray.add(pEvents);
      iToleranceStep = 0;
      for(tkTolerance = 0;
         tkTolerance <= WORDSWAP(m_pFile->m_pFileHeader->wDivision);
         tkTolerance += tkToleranceAddUp)
      {
         
         k = 0;
         iMatches = 0;
         for(j = 0; j < pTicks->get_size(); j++)
         {
            if(k >= pEvents->m_tkaEventsPosition.get_size())
            {
               //iMatches -= 3;
               break;
            }
            tkPositionA = pTicks->get_at(j);
            while(tkPositionA - tkTolerance >
               (tkPositionB = pEvents->m_tkaEventsPosition.get_at(k)))
            {
               iMatches--; // 2001-05-05 Ser・que funciona?ｿ
               k++;
               if(k >= pEvents->m_tkaEventsPosition.get_size())
                  break;
            }
            if(tkPositionB >= tkPositionA - tkTolerance &&
               tkPositionB <= tkPositionA + tkTolerance)
            {
               iMatches++;
            }
            else
            {
               //iMatches--;
               iMatches -= 3;
            }
         }
         iMatches -= 3 * (pTicks->get_size() - j);
         i2aEventMatch[iTrack].add(iMatches);
      }
   }

   if(i2aEventMatch.get_size() > 0)
   {
      iToleranceStepCount = i2aEventMatch[0].get_size();
   }
   else
   {
      iToleranceStepCount = 0;
   }

   for(iToleranceStep = 0;
      iToleranceStep < iToleranceStepCount;
      iToleranceStep++)
   {
      int_array & iaEventMatch = i2aEventMatch[iToleranceStep];
      iMatches = 0x80000000;
      iBestMatch = 0x80000000;
      for(i = 0; i < iaEventMatch.get_size(); i++)
      {
         if(iaEventMatch.element_at(i) > iMatches)
         {
            iBestMatch = i;
            iMatches = iaEventMatch.element_at(i);
         }
      }
      if(iBestMatch >= 0)
      {
         dwaBestMatchesIndexes.add(iBestMatch);
         dwaBestMatchesScores.add(iMatches);
      }
      tkTolerance += tkToleranceAddUp;
   }









   
   
   
   
   
   
   
   
   
   
/*   while(tkTolerance <= DWORDSWAP(m_pFile->m_pFileHeader->wDivision))
   {
      for(i = 0; i < iSize; i++)
      {
         if(m_pFile->GetFormat() == 0)
         {
            ptrack = (MidiTrack *) MidiTrackAt(0);
         }
         else
         {
            if(i >= GetTrackCount())
               break;
            ptrack = (MidiTrack *) MidiTrackAt(i);
         }
         pEvents = new MidiEventsV1();
         ptrack->WorkSeekBegin();
         ptrack->WorkGetStandardEventsV1(pEvents, ::mus::midi::NoteOn, i, bAnyTrack);
         eventsArray.add(pEvents);
         k = 0;
         iMatches = 0;
         for(j = 0; j < pTicks->get_size(); j++)
         {
            if(k >= pEvents->m_tkaEventsPosition.get_size())
                {
                    //iMatches -= 3;
               break;
                }
            tkPositionA = pTicks->get_at(j);
            while(tkPositionA - tkTolerance >
               (tkPositionB = pEvents->m_tkaEventsPosition.get_at(k)))
            {
               iMatches--; // 2001-05-05 Ser・que funciona?ｿ
               k++;
               if(k >= pEvents->m_tkaEventsPosition.get_size())
                  break;
            }
            if(tkPositionB >= tkPositionA - tkTolerance &&
               tkPositionB <= tkPositionA + tkTolerance)
            {
               iMatches++;
            }
            else
            {
               //iMatches--;
               iMatches -= 3;
            }
         }
         iMatches -= 3 * (pTicks->get_size() - j);
//         TRACE("iMatches %d iTrack %d\n", iMatches, i);
         eventsMatches.add(iMatches);
      }
      iMatches = 0x80000000;
      iBestMatch = 0x80000000;
      for(i = 0; i < eventsMatches.get_size(); i++)
      {
         if(eventsMatches.get_at(i) > iMatches)
         {
            iBestMatch = i;
            iMatches = eventsMatches.get_at(i);
         }
      }
      for(i = 0; i < iSize; i++)
      {
         delete eventsArray.get_at(i);
      }
      eventsArray.remove_all();   
      if(iBestMatch >= 0)
   //      break;
      {
         dwaBestMatchesIndexes.add(iBestMatch);
         dwaBestMatchesScores.add(iMatches);
      }
      tkTolerance += tkToleranceAddUp;
        eventsMatches.remove_all();
   
   }*/



//   if(iBestMatch >= 0)
   if(dwaBestMatchesIndexes.get_size() > 0)
   {
      
      int iWorstMatches = 0xffffffff;
      for(i = 0; i < dwaBestMatchesIndexes.get_size(); i++)
      {
         if(((int) dwaBestMatchesScores.get_at(i)) < iWorstMatches)
         {
            iWorstMatches = (int) dwaBestMatchesScores.get_at(i);
         }
      }
      if(iWorstMatches < 0)
      {
         for(i = 0; i < dwaBestMatchesIndexes.get_size(); i++)
         {
            dwaBestMatchesScores.set_at(i,
               (int)dwaBestMatchesScores.get_at(i) -
               iWorstMatches);
         }
      }
      iMatches = 0x80000000;
      iBestMatch = -1;
      for(i = 0; i < dwaBestMatchesIndexes.get_size(); i++)
      {
         if(((int) dwaBestMatchesScores.get_at(i) ) > pow((double)iMatches, (double)i))
         {
            iBestMatch =  dwaBestMatchesIndexes.get_at(i);
            iMatches = (int) dwaBestMatchesScores.get_at(i);
         }
      }
/*      for(i = 0; i < iSize; i++)
      {
         if(i == iBestMatch)
         {
            *ppEventsRet = eventsArray.get_at(i);
         }
         else
         {
            delete eventsArray.get_at(i);
         }
      }*/
      if(iBestMatch >= 0)
      {
         if(m_pFile->GetFormat() == 0)
         {
            ptrack = (MidiTrack *) TrackAt(0);
         }
         else
         {
            if(i >= GetTrackCount())
               goto Skip090;
            ptrack = (MidiTrack *) TrackAt(iBestMatch);
         }
         pEvents = new MidiEventsV1();
         ptrack->WorkSeekBegin();
         ptrack->WorkGetStandardEventsV1(pEvents, ::mus::midi::NoteOn, iBestMatch, bAnyTrack);
         *ppEventsRet = pEvents;
      }
Skip090:;

   }

   return iBestMatch;

}

int MidiTracks::WorkCalcMelodyTrack(
   MidiEventsV1 ** ppEventsRet,
   imedia::position_array & positiona,
   int_array & iaTokenLine,
   WORD wFileFormat)
{
   UNREFERENCED_PARAMETER(iaTokenLine);
   UNREFERENCED_PARAMETER(wFileFormat);
   ASSERT(*ppEventsRet == NULL);


   dword_array dwaBestMatchesIndexes;
   dword_array dwaBestMatchesScores;
   imedia::position tkTolerance = 0;
   imedia::position tkPositionA, tkPositionB;
   //const imedia::position tkToleranceAddUp = 60;
   const imedia::position tkToleranceTotal = m_pFile->GetDivision();
   const imedia::position tkToleranceAddUp = tkToleranceTotal / 4;
   MidiTrack * ptrack;
   MidiEventsV1 * pEvents;
   primitive_array < MidiEventsV1 *> eventsArray;
   //primitive_array < primitive_array < MidiEventsV1 *>> eventsArray2D;
   int_array eventsMatches;
   bool bAnyTrack = m_pFile->GetFormat() == 1;
   const int max_tracks_search = 16;
/*   if(m_pFile->GetFormat() == 1)
   {
      iSize = GetMidiTrackCount();
   }
   else
   {
      iSize = max_tracks_search;
   }*/
   double_array daCorrel;
//   bool bAnyTrack = m_pFile->GetFormat() == 1;
//   const int max_tracks_search = 16;
   int iTrack, iTrackCount;
   if(m_pFile->GetFormat() == 1)
   {
      iTrackCount = GetMidiTrackCount();
   }
   else
   {
      iTrackCount = max_tracks_search;
   }
















   /// old begin /////////////////////////////////////////////

/*   while(tkTolerance <= WORDSWAP(m_pFile->m_pFileHeader->wDivision))
   {
      for(i = 0; i < iSize; i++)
      {
         if(m_pFile->GetFormat() == 0)
         {
            ptrack = (MidiTrack *) MidiTrackAt(0);
         }
         else
         {
            if(i >= GetTrackCount())
               break;
            ptrack = (MidiTrack *) MidiTrackAt(i);
         }
         pEvents = new MidiEventsV1();
         ptrack->WorkSeekBegin();
         ptrack->WorkGetStandardEventsV1(pEvents, ::mus::midi::NoteOn, i, bAnyTrack);
         eventsArray.add(pEvents);
         k = 0;
         iMatches = 0;
         for(j = 0; j < positiona.get_size(); j++)
         {
            if(k >= pEvents->m_tkaEventsPosition.get_size())
                {
                    //iMatches -= 3;
               break;
                }
            tkPositionA = positiona.get_at(j);
            while(tkPositionA - tkTolerance >
               (tkPositionB = pEvents->m_tkaEventsPosition.get_at(k)))
            {
               iMatches--; // 2001-05-05 Ser・que funciona?ｿ
               k++;
               if(k >= pEvents->m_tkaEventsPosition.get_size())
                  break;
            }
            if(tkPositionB >= tkPositionA - tkTolerance &&
               tkPositionB <= tkPositionA + tkTolerance)
            {
               iMatches++;
            }
            else
            {
               //iMatches--;
               iMatches -= 3;
            }
         }
         iMatches -= 3 * (positiona.get_size() - j);
//         TRACE("iMatches %d iTrack %d\n", iMatches, i);
         eventsMatches.add(iMatches);
      }
      iMatches = 0x80000000;
      iBestMatch = 0x80000000;
      for(i = 0; i < eventsMatches.get_size(); i++)
      {
         if(eventsMatches.get_at(i) > iMatches)
         {
            iBestMatch = i;
            iMatches = eventsMatches.get_at(i);
         }
      }
      for(i = 0; i < iSize; i++)
      {
         delete eventsArray.get_at(i);
      }
      eventsArray.remove_all();   
      if(iBestMatch >= 0)
   //      break;
      {
         dwaBestMatchesIndexes.add(iBestMatch);
         dwaBestMatchesScores.add(iMatches);
      }
      tkTolerance += tkToleranceAddUp;
        eventsMatches.remove_all();
   
   }*/



   /// old end /////////////////////////////////////////////







































   double dCorrel;



   for(iTrack = 0; iTrack < iTrackCount; iTrack++)
   {
      if(m_pFile->GetFormat() == 0)
      {
         ptrack = (MidiTrack *) MidiTrackAt(0);
      }
      else
      {
         if(iTrack >= GetTrackCount())
            break;
         ptrack = (MidiTrack *) MidiTrackAt(iTrack);
      }
      pEvents = new MidiEventsV1();
      ptrack->WorkSeekBegin();
      ptrack->WorkGetStandardEventsV1(pEvents, ::mus::midi::NoteOn, iTrack, bAnyTrack);
      dCorrel = 0.0;
      int i = 0;
      int j = 0;
      while(true)
      {
         if(i >= positiona.get_count())
            break;
         imedia::position tkPosition = positiona[i];
         imedia::position tkNextPosition;
         if((i + 1) >= positiona.get_count())
            tkNextPosition = tkPosition + 96 * 2;
         else
            tkNextPosition = positiona[i+1];
         int iTry = 0;
         while(true)
         {
            if(j >= pEvents->m_tkaEventsPosition.get_count())
               break;
            imedia::position tkEvent = pEvents->m_tkaEventsPosition.element_at(j);
            double dDiff = tkEvent - tkPosition;
            // to favor a causal relation
            if(dDiff < 0.0)
            {
               dCorrel += dDiff * 5.0 - 177.0;
            }
            // to favor near notes
            else if(dDiff > 48.0)
            {
               if(iTry > 0)
               {
                  break;
               }
               else
               {
                  dCorrel -= dDiff * 5.0 + 177.0;
               }
            }
            else if(tkNextPosition - tkEvent < 12)
            {
               break;
            }
            else
            {
               if(dDiff < 12.0 && iTry == 0)
               {
                  dCorrel += 1984;
               }
               else
               {
                  dCorrel += 1984 / (dDiff * 5.0 + (iTry * 77.0));  
               }
            }
            j++;
            iTry++;
         }
         i++;
      }
      daCorrel.add(dCorrel);
   }


   int iFound = -1;

   dCorrel = -1000.0 * 1000.0 * 100.0;

   for(int i = 0; i < daCorrel.get_size(); i++)
   {
      if(daCorrel[i] > dCorrel)
      {
         dCorrel = daCorrel[i];
         iFound = i;
      }
   }

   return iFound;

}

bool MidiTracks::IsTune1000File()
{
    bool bIsTune1000File = false;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack * ptrack = (MidiTrack *)TrackAt(i);
      ptrack->seek_begin();
      if(ptrack->IsType(MidiTrackBase::TypeMidi) && (bIsTune1000File = ptrack->IsTune1000File()))
      {
         break;
      }
   }
    return bIsTune1000File;
}

bool MidiTracks::IsSoftKaraokeFile(bool bWork, stringa * pstra)
{
   if(GetTrackCount() < 2)
   {
      return false;
   }
   else
   {
      MidiTrack * ptrack = (MidiTrack *)TrackAt(1);
      ptrack->_SeekBegin(bWork);
      if(ptrack->IsType(MidiTrackBase::TypeMidi)
         && ptrack->IsSoftKaraokeFile(bWork, pstra))
      {
         return true;
      }
      else
      {
         if(GetTrackCount() >= 3)
         {
            MidiTrack * ptrack = (MidiTrack *)TrackAt(2);
            if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            {
               return false;
            }
            else
            {
               ptrack->_SeekBegin(bWork);
               stringa strArray;
               imedia::position_array tkArray;
               ptrack->seek_begin();
               ptrack->ReadKarTokens(strArray, &tkArray);
               if(strArray.get_size() > 0)
                  return true;
               else
                  return false;
            }
         }
         else
         {
            return false;
         }
      }
    }
}

/*MidiTrack * MidiTracks::GetEventTrack(CMidiEventBase *pEvent)
{
   int i;
   for(i = 0; i < get_size(); i++)
   {
      MidiTrack * ptrack = &TrackAt(i);
      if(ptrack->ContainsEvent(pEvent))
         return ptrack;
   }
   return NULL;
} */

MidiTrack * MidiTracks::seek(DWORD dwSeekWhat)
{
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack * ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->seek_begin();
      if(ptrack->seek(dwSeekWhat) == ::mus::midi::Success)
        {
            m_iCurrentTrack = i;
         return ptrack;
        }
   }
   return NULL;
}

bool MidiTracks::IsXFFile()
{
    if(GetTrackCount() <= 0)
        return false;
    else
    {
        for(int i = 0; i < GetTrackCount(); i++)
        {
          MidiTrack * ptrack = (MidiTrack *)TrackAt(i);
            if(!ptrack->IsType(MidiTrackBase::TypeMidi))
                continue;
            if(ptrack->IsXFFile())
            {
                return true;
            }
        }
        return false;
    }

}



void MidiTracks::FromWorkStorage()
{
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack * ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->FromWorkTrack(false);
   }

}

void MidiTracks::ToWorkStorage()
{
   for(int i = 0; i < GetMidiTrackCount(); i++)
   {
      MidiTrack * ptrack = MidiTrackAt(i);
      ptrack->ToWorkStorage();
   }
}

VMSRESULT MidiTracks::CompactTracks(
    MidiTrack & trackUnion,
    bool bOnlyMTrk,
    bool bOnlyMidiTrack)
{
//    MidiTrack trackUnion;
    trackUnion.SetAutoAllocation();
    seek_begin();
    MidiEventV001 * pevent;
    while(::mus::midi::Success == GetNextEvent(pevent, 0x7fffffff, true, bOnlyMTrk, bOnlyMidiTrack))
    {
        if(pevent->GetFlags() != 0 ||
         (pevent->GetFullType() == ::mus::midi::Meta &&
            pevent->GetMetaType() == ::mus::midi::MetaEOT))
        {
        }
        else
        {
            trackUnion.WriteCompleteEvent(*pevent, 0x7fffffff, false);
        }
    }
    pevent->SetFullType(::mus::midi::Meta);
    pevent->SetMetaType(::mus::midi::MetaEOT);
    pevent->SetParam(NULL, 0);
    trackUnion.WriteCompleteEvent(*pevent, 0x7fffffff, false);
    
    CHUNKHDR hdr;
    hdr.fourccType = FOURCC_MTrk;
    hdr.dwLength = trackUnion.m_smti.m_cbLength;
    trackUnion.WriteHeader(&hdr);


    return VMSR_SUCCESS;

}

VMSRESULT MidiTracks::WorkCompactTracks(
    MidiTrack & trackUnion,
    bool bOnlyMTrk)
{
//    MidiTrack trackUnion;
    trackUnion.SetAutoAllocation();
    WorkSeekBegin();
    MidiEventV008 * pevent;
    while(::mus::midi::Success == WorkGetNextRawEvent(pevent, 0x7fffffff, true, bOnlyMTrk))
    {
        if(pevent->GetFlags() != 0 ||
         (pevent->GetFullType() == ::mus::midi::Meta &&
            pevent->GetMetaType() == ::mus::midi::MetaEOT))
        {
        }
        else
        {
            if(pevent->_GetType() == ::mus::midi::NoteOn)
            {
                if(pevent->_GetTrack() != 3)
                {
//                    int i = 1 + 2;
                }
            }
            
            trackUnion.WriteCompleteEvent(*pevent, 0x7fffffff, false);
        }
    }
    pevent->SetFullType(::mus::midi::Meta);
    pevent->SetMetaType(::mus::midi::MetaEOT);
    pevent->SetParam(NULL, 0);
    trackUnion.WriteCompleteEvent(*pevent, 0x7fffffff, false);
    
    CHUNKHDR hdr;
    hdr.fourccType = FOURCC_MTrk;
    hdr.dwLength = trackUnion.m_smti.m_cbLength;
    trackUnion.WriteHeader(&hdr);


    return VMSR_SUCCESS;

}

VMSRESULT MidiTracks::WorkCompactMidiTracks(
    MidiTrack & trackUnion,
    bool bOnlyMTrk)
{
//    MidiTrack trackUnion;
    trackUnion.SetAutoAllocation();
    WorkSeekBegin();
    MidiEventV008 * pevent;
    while(::mus::midi::Success == WorkGetNextRawMidiEvent(pevent, 0x7fffffff, true, bOnlyMTrk))
    {
        if(pevent->GetFlags() != 0 ||
         (pevent->GetFullType() == ::mus::midi::Meta &&
            pevent->GetMetaType() == ::mus::midi::MetaEOT))
        {
        }
        else
        {
            if(pevent->_GetType() == ::mus::midi::NoteOn)
            {
                if(pevent->_GetTrack() != 3)
                {
//                    int i = 1 + 2;
                }
            }
            
            trackUnion.WriteCompleteEvent(*pevent, 0x7fffffff, false);
        }
    }
    pevent->SetFullType(::mus::midi::Meta);
    pevent->SetMetaType(::mus::midi::MetaEOT);
    pevent->SetParam(NULL, 0);
    trackUnion.WriteCompleteEvent(*pevent, 0x7fffffff, false);
    
    CHUNKHDR hdr;
    hdr.fourccType = FOURCC_MTrk;
    hdr.dwLength = trackUnion.m_smti.m_cbLength;
    trackUnion.WriteHeader(&hdr);


    return VMSR_SUCCESS;

}

VMSRESULT MidiTracks::WorkCompactTracksWork(
   MidiTrack & trackUnion,
   bool bOnlyMTrk)
{
   trackUnion.GetWorkTrack().remove_all();
   WorkSeekBegin();
   MidiEventV008 * pevent;
   imedia::position tkLastPosition = 0;
   imedia::position tkPosition = 0;
   while(WorkGetNextRawEvent(
      pevent,
      0x7fffffff,
      true,
      bOnlyMTrk)
      == ::mus::midi::Success)
   {
      tkPosition = GetPosition();
      if(pevent->GetFlags() != 0 ||
         (pevent->GetFullType() == ::mus::midi::Meta &&
         pevent->GetMetaType() == ::mus::midi::MetaEOT))
      {
      }
      else
      {
         trackUnion.GetWorkTrack().add(
            (imedia::position) (tkPosition - tkLastPosition),
            *pevent);
      }
      tkLastPosition = tkPosition;
   }
    pevent->SetFullType(::mus::midi::Meta);
    pevent->SetMetaType(::mus::midi::MetaEOT);
    pevent->SetParam(NULL, 0);
    trackUnion.GetWorkTrack().add(*pevent);

    return VMSR_SUCCESS;

}

VMSRESULT MidiTracks::WorkCompactMidiTracksWork(
    MidiTrack & trackUnion,
    bool bOnlyMTrk)
{
   trackUnion.GetWorkTrack().remove_all();
   WorkSeekBegin();
   MidiEventV008 * pevent = NULL;
   imedia::position tkLastPosition = 0;
   imedia::position tkPosition = 0;

   while(
      WorkGetNextRawMidiEvent(
         pevent, 
         0x7fffffff, 
         true, 
         bOnlyMTrk)
         == ::mus::midi::Success)
   {
      tkPosition = GetPosition();
      if(pevent->GetFlags() != 0 ||
         (pevent->GetFullType() == ::mus::midi::Meta &&
          pevent->GetMetaType() == ::mus::midi::MetaEOT))
      {
      }
      else
      {
         trackUnion.GetWorkTrack().add(
            (imedia::position) (tkPosition - tkLastPosition),
            *pevent);
      }
      tkLastPosition = tkPosition;
   }
   MidiEventV008 event;
   event.SetDelta(0);
   event.SetFullType(::mus::midi::Meta);
   event.SetMetaType(::mus::midi::MetaEOT);
   event.SetParam(NULL, 0);
   trackUnion.GetWorkTrack().add(event);

   return VMSR_SUCCESS;

}

// put in Format 1?ｿ
VMSRESULT MidiTracks::ExpandTrack(index iTrackIndex)
{
//    MidiTrack trackUnion;
    MidiTrack * ptrackParam = (MidiTrack *) TrackAt(iTrackIndex);
    ASSERT(ptrackParam->IsType(MidiTrackBase::TypeMidi));
    remove_at(iTrackIndex);
    ptrackParam->seek_begin();
    ::collection::map<int, int, MidiTrack *, MidiTrack *> mapTracks;
    MidiTrack * ptrack;
   ptrackParam->ToWorkStorage();
   ptrackParam->WorkSeekBegin();
   MidiEventV008 * pevent;
    while(true)
    {
       ptrackParam->WorkGetEvent(
         pevent,
         0x7fffffff,
         true);
        if(pevent->GetFullType() == ::mus::midi::Meta &&
            pevent->GetMetaType() == ::mus::midi::MetaEOT)
        {
        }
        else if(pevent->GetFullType() < ::mus::midi::SysEx)
        {
            if(!mapTracks.Lookup(pevent->_GetTrack(), ptrack))
            {
                ptrack = CreateTrack();
                ptrack->SetAutoAllocation();
                mapTracks.set_at(pevent->_GetTrack(), ptrack);
            }
            ptrack->GetWorkTrack().add(*pevent);
        }
        else
        {
            if(!mapTracks.Lookup(0, ptrack))
            {
                ptrack = CreateTrack();
                ptrack->SetAutoAllocation();
                mapTracks.set_at(0, ptrack);
            }
            ptrack->GetWorkTrack().add(*pevent);
        }
      if(::mus::midi::Success != ptrackParam->WorkMoveNext())
         break;
    }
    for(int i = 0; i < 15; i++)
    {
        if(mapTracks.Lookup(i, ptrack))
        {
            ptrack->GetEvent().SetFullType(::mus::midi::Meta);
            ptrack->GetEvent().SetMetaType(::mus::midi::MetaEOT);
            ptrack->GetEvent().SetParam(NULL, 0);
            ptrack->GetEvent().SetDelta(0);
            ptrack->WorkWriteEvent();
    
    
            CHUNKHDR hdr;
            hdr.fourccType = FOURCC_MTrk;
            hdr.dwLength = ptrack->m_smti.m_cbLength;
            ptrack->WriteHeader(&hdr);
            ptrack->Initialize(this);
         ptrack->FromWorkTrack(false);
        }
    }
    return VMSR_SUCCESS;
}

index MidiTracks::GetMidiTrackIndex(index iIndex)
{
    if(TrackAt(iIndex)->get_type() == MidiTrackBase::TypeMidi)
        return ((MidiTrack*)TrackAt(iIndex))->GetMidiTrackIndex();
    else
        return -1;
}

VMSRESULT MidiTracks::SetLyricDelay(int iDelay)
{
    m_iLyricDelay = iDelay;
    for(int i = 0; i < GetTrackCount(); i++)
    {
        MidiLyricTrack * pltrack = dynamic_cast<MidiLyricTrack *>(TrackAt(i));
        if(pltrack != NULL)
        {
            pltrack->SetDelay(iDelay);
        }
    }
    return VMSR_SUCCESS;
}

VMSRESULT MidiTracks::GetLyricDelay(int *lpiDelay)
{
    *lpiDelay = m_iLyricDelay;
    return VMSR_SUCCESS;
}

void MidiTracks::OnStop()
{
   int i;
   m_tkLevelLastUpdateInterval = 0;
   
   for(i = 0; i < m_iaLevel.get_size(); i++)
   {
      m_iaLevel.element_at(i) = 0;
   }

   for(i = 0; i < m_iaNoteOn.get_size(); i++)
   {
      m_iaNoteOn.element_at(i) = 0;
   }

}

::mus::midi::e_file_result MidiTracks::GetVolumeEvent(::ca::application * papp, MidiEventV008 *& pevent)
{
   pevent = &m_midieventVolume;
   pevent->clear();
   pevent->SetFullType(::mus::midi::Meta);
   pevent->SetFlags(1);
   pevent->SetDelta(0);
   pevent->SetPosition(GetPosition());
   gen::memory_file memFile(papp);
   memFile << EVENT_ID_NOTE_ON;
   for(int i = 0; i < m_iaLevel.get_size(); i++)
   {
      memFile << (BYTE) m_iaLevel.element_at(i);
   }
   memFile.Flush();
   DWORD dwLength = memFile.get_length();
   LPBYTE lpData = memFile.DetachStorage();
   pevent->SetParam(lpData, dwLength);
   
   m_bVolumeEventSent = true;

   return ::mus::midi::Success;
}

::mus::midi::e_file_result MidiTracks::GetVolumeEvent(::ca::application * papp, MidiEventV001 *& pevent)
{
   pevent = &m_midieventV001Volume;
   pevent->clear();
   pevent->SetFullType(::mus::midi::Meta);
   pevent->SetFlags(1);
   pevent->SetDelta(0);
   pevent->SetPosition(GetPosition());
   gen::memory_file memFile(papp);
   memFile << EVENT_ID_NOTE_ON;
   for(int i = 0; i < m_iaLevel.get_size(); i++)
   {
      memFile << (BYTE) m_iaLevel.element_at(i);
   }
   memFile.Flush();
   DWORD dwLength = memFile.get_length();
   LPBYTE lpData = memFile.DetachStorage();
   pevent->SetParam(lpData, dwLength);
   
   m_bVolumeEventSent = true;

   return ::mus::midi::Success;
}


bool MidiTracks::WorkGetLongestXFLyrics(string &wstrParam)
{
   string2a wstr2a;
   imedia::position_2darray position2a;
   int2a i2aTokenLine;
   if(WorkGetXFTokens(CP_ACP, wstr2a, position2a, i2aTokenLine, NULL) != ::mus::midi::Success)
      return false;

   int iMatch = -1;
   int iMaxSize = 0;
   int iSize;
   int i;
   for(i = 0; i <wstr2a.get_size(); i++)
   {
      iSize = wstr2a.element_at(i).get_size();
      if(iSize > iMaxSize)
      {
         iMaxSize = iSize;
         iMatch = i;
      }
   }
   if(iMatch < 0)
      return false;

   stringa stra = wstr2a.element_at(iMatch);

   int            iTokens;
   int            iChars;
   int            iCharsFirst;
   WCHAR            wch;
   string         str;
   int            iStr;
   int            xPosition;
   BOOL            forceInsertion = FALSE;
   bool            bLineFirstToken;
   bool            bLineLastToken;


   iChars = -1;
   iCharsFirst = 0;
   iStr = 0;
   iTokens = -1;
   xPosition = 0;

   iSize = stra.get_size();
   int iLen;
   string wstrFinal;
   string wstrLine;
   bLineFirstToken = true;
   bLineLastToken = false;
   
   for(i = 0; i < iSize;)
   {
      str = stra.element_at(i);
      iLen = str.get_length();
      if(iLen <= 0)
      {
         i++;
         continue;
      }
      for(int j = 0; j < iLen; j++)
      {
         wch = str[j];

         if(bLineFirstToken)
         {
            if(wch == '\\')
            {
               forceInsertion = true;
            }
            else if(wch == '^')
            {
               wstrLine += ' ';
            }
            else if(wch == '/')
            {
            }
            else if(wch == '%')
            {
            }
            else if(wch == '<')
            {
            }
            else if(wch == '>')
            {
               wstrLine += '\t';
            }
            else
            {
               wstrLine += wch;
            }
         }
         else
         {
            if(forceInsertion)
            {
               forceInsertion = false;
               wstrLine += wch;
            }
            else if(wch == '\\')
            {
               forceInsertion = true;
            }
            else if(wch == '^')
            {
               wstrLine += ' ';
            }
            else if(wch == '/')
            {
               bLineLastToken = true;
               break;
            }
            else if(wch == '%')
            {
               bLineLastToken = true;
               break;
            }
            else if(wch == '<')
            {
               if(j == 1)
               {
                  bLineLastToken = true;
                  break;
               }
            }
            else if(wch == '>')
            {
               wstrLine += '\t';
            }
            else if(wch == '\n')
            {
               bLineLastToken = true;
               break;
            }
            else if(wch == '\r')
            {
               bLineLastToken = true;
               break;
            }
            else
            {
               wstrLine += wch;
            }
         }
      }
      if(bLineLastToken)
      {
         wstrFinal += wstrLine;
         wstrLine.Empty();
         wstrFinal += "\r\n";
         bLineFirstToken = true;
         bLineLastToken = false;
      }
      else
      {
         bLineFirstToken = false;
         i++;
      }
   }
   wstrFinal += wstrLine;
   wstrFinal += "\r\n";

   wstrParam = wstrFinal;
   return true;
}

bool MidiTracks::WorkGetLongestSoftKaraokeLyrics(string &wstrParam)
{
   string2a wstr2a;
   imedia::position_2darray tick2a;
   base_array<XFLyricsHeader, XFLyricsHeader&> xflh2a;
   if(WorkGetSoftKaraokeTokens(
      wstr2a,
      &tick2a,
      &xflh2a) != ::mus::midi::Success)
      return false;

   int iMatch = -1;
   int iMaxSize = 0;
   int iSize;
   int i;
   for(i = 0; i <wstr2a.get_size(); i++)
   {
      iSize = wstr2a.element_at(i).get_size();
      if(iSize > iMaxSize)
      {
         iMaxSize = iSize;
         iMatch = i;
      }
   }
   if(iMatch < 0)
      return false;

   stringa stra = wstr2a.element_at(iMatch);

   int               iTokens;
   int               iChars;
   int               iCharsFirst;
   WCHAR            wch;
   string            str;
   int               iStr;
   int               xPosition;


   iChars = -1;
   iCharsFirst = 0;
   iStr = 0;
   iTokens = -1;
   xPosition = 0;

   iSize = stra.get_size();
   int iLen;
   string wstrFinal;
   
   for(i = 0; i < iSize; i++)
   {
      str = stra.element_at(i);
      iLen = str.get_length();
      for(int j = 0; j < iLen; j++)
      {
         wch = str[j];

         if(wch == '\\')
         {
            wstrFinal += "\r\n";
         }
         else if(wch == L'/')
         {
            wstrFinal += "\r\n";
            wstrFinal += "\r\n";
         }
         else
         {
            wstrFinal += wch;
         }
      }
   }
   wstrFinal += "\r\n";

   wstrParam = wstrFinal;
   return true;

}



MidiLyricTrack * MidiTracks::CreateLyricTrack()
{
   return m_tracka.CreateLyricTrack();
}

::mus::midi::e_file_result MidiTracks::WorkGetNextEvent(
   MidiEventV008 *&         pevent,
   imedia::position                   tkMax,
   BOOL                     bTkMaxInclusive,
   bool                    bOnlyMTrk)
{
   MidiTrackBase *         ptrack;
   MidiTrackBase *         ptrkFound;
   int                     idxTrackFound;
   int                     idxTrack;
   imedia::position                   tkEventPosition;
   imedia::position                     tkEventFound;
   int                     iRelTime;
   int                     iMinRelTime;

   iMinRelTime = 0x7fffffff;
   ptrkFound = NULL;
   bool bNextEventLookUp;
   
   for(idxTrack = 0; idxTrack < GetActiveTrackCount(); idxTrack++)
   {
      ptrack = ActiveTrackAt(idxTrack);
      if(ptrack->WorkIsEOT())
      {
         DeactivateTrack(ptrack);
         idxTrack--;
         continue;
      }

      if(bOnlyMTrk)
      {
         if(ptrack->IsType(MidiTrackBase::TypeMidi))
         {
            MidiTrack * pmiditrack = (MidiTrack *) ptrack;
            CHUNKHDR FAR * pCh = (CHUNKHDR FAR *) pmiditrack->GetTrackImage();
            if (pCh->fourccType != FOURCC_MTrk)
               continue;
         }
         else
         {
            continue;
         }
      }

      bNextEventLookUp = true;
      while(true)
      {
         tkEventPosition = ptrack->WorkGetPosition();
         iRelTime = tkEventPosition - m_tkPosition;
         ASSERT(iRelTime >= 0);
         if(iRelTime < 0)
         {
            if(ptrack->WorkMoveNext() != VMSR_SUCCESS)
            {
               if(ptrack->WorkIsEOT())
               {
                  DeactivateTrack(ptrack);
               }
               bNextEventLookUp = false;
               break;
            }
         }
         else
         {
            break;
         }
      }
      if(!bNextEventLookUp)
      {
         continue;
      }
      ASSERT(iRelTime >= 0);
      if (iRelTime < iMinRelTime)
      {
         iMinRelTime    = iRelTime;
         ptrkFound      = ptrack;
         idxTrackFound  = idxTrack;
         tkEventFound   = tkEventPosition;
         if(iRelTime == 0)
            break;
      }
   }

   if (ptrkFound == NULL)
   {
      return ::mus::midi::SEndOfFile;
   }
   
   ptrack = ptrkFound;

    

   imedia::position tkPosition = tkEventFound;

   iRelTime = tkPosition - m_tkPosition;
   ASSERT(iRelTime >= 0);
   if(iRelTime < 0)
      iRelTime = 0;

   // XXX
   if(!GetFlags().is_signalized(::mus::midi::DisablePlayLevel1Operations))
   {
      if(iRelTime != 0)
      {
         m_tkLevelLastUpdateInterval += iRelTime;
         if(m_tkLevelLastUpdateInterval > 24)
         {
            m_tkLevelLastUpdateInterval = 0;
            if(!m_bVolumeEventSent)
            {
               return GetVolumeEvent(get_app(), pevent);
            }
            else
            {
               m_bVolumeEventSent = false;
            }
         }
      }
      else
      {
         m_bVolumeEventSent = false;
      }
   }


   if(ptrack->get_type() == MidiTrackBase::TypeLyric)
   {
      ASSERT(true);
   }

   if(bTkMaxInclusive)
   {
      if (m_tkPosition + iMinRelTime > tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition + iMinRelTime >= tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
    
   ptrack->WorkGetEvent(pevent, tkMax, bTkMaxInclusive);

   if(!GetFlags().is_signalized(::mus::midi::DisablePlayLevel1Operations))
   {
      if(pevent->_GetType() == ::mus::midi::ProgramChange)
      {
         m_iaInstrument.element_at(pevent->_GetTrack())
            = pevent->GetChB1();
      }
   }

   m_iCurrentTrack = idxTrackFound;
   m_tkPosition = ptrack->GetPosition();
   ptrack->WorkMoveNext();
   
   
   return ::mus::midi::Success;
}

::mus::midi::e_file_result MidiTracks::WorkGetNextRawEvent(
   MidiEventV008 *&         pevent,
   imedia::position                   tkMax,
   BOOL                     bTkMaxInclusive,
   bool                    bOnlyMTrk)
{
   MidiTrackBase *         ptrack;
   MidiTrackBase *         ptrkFound;
   int                     idxTrackFound;
   int                     idxTrack;
   imedia::position                   tkEventPosition;
   imedia::position                     tkEventFound;
   int                     iRelTime;
   int                     iMinRelTime;



   iMinRelTime = 0x7fffffff;
   ptrkFound = NULL;
   bool bNextEventLookUp;
   for (idxTrack = 0; idxTrack < GetActiveTrackCount(); idxTrack++)
   {
      ptrack = ActiveTrackAt(idxTrack);
      ASSERT(!ptrack->WorkIsEOT());
      if(bOnlyMTrk)
      {
         if(ptrack->IsType(MidiTrackBase::TypeMidi))
         {
            MidiTrack * ptrackMidi = (MidiTrack *) ptrack;
            CHUNKHDR FAR * pCh = (CHUNKHDR FAR *) ptrackMidi->GetTrackImage();
            if (pCh->fourccType != FOURCC_MTrk)
               continue;
         }
      }
      bNextEventLookUp = true;
      while(true)
      {
         tkEventPosition = ptrack->WorkGetPosition();
         iRelTime = tkEventPosition - m_tkPosition;
         ASSERT(iRelTime >= 0);
         if(iRelTime < 0)
         {
            if(ptrack->WorkMoveNext() != VMSR_SUCCESS)
            {
               if(ptrack->WorkIsEOT())
               {
                  DeactivateTrack(ptrack);
               }
               bNextEventLookUp = false;
               break;
            }
         }
         else
         {
            break;
         }
      }
      if(!bNextEventLookUp)
      {
         continue;
      }
      ASSERT(iRelTime >= 0);

        if (iRelTime < iMinRelTime)
        {
            iMinRelTime = iRelTime;
            ptrkFound = ptrack;
         idxTrackFound = idxTrack;
         tkEventFound = tkEventPosition;
        }
    }

    if (ptrkFound == NULL)
    {
        return ::mus::midi::SEndOfFile;
    }

    ptrack = ptrkFound;

    imedia::position tkPosition = tkEventFound;

   iRelTime = tkPosition - m_tkPosition;
   ASSERT(iRelTime >= 0);
   if(iRelTime < 0)
      iRelTime = 0;



   if(ptrack->get_type() == MidiTrackBase::TypeLyric)
   {
      ASSERT(true);
   }

   if(bTkMaxInclusive)
   {
      if (m_tkPosition + iMinRelTime > tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition + iMinRelTime >= tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
    
   ptrack->WorkGetEvent(pevent, tkMax, bTkMaxInclusive);
   m_iCurrentTrack = idxTrackFound;
   m_tkPosition = ptrack->GetPosition();
   ptrack->WorkMoveNext();
   
   if(ptrack->WorkIsEOT())
   {
      DeactivateTrack(ptrack);
   }
   return ::mus::midi::Success;
}

::mus::midi::e_file_result MidiTracks::WorkGetNextRawMidiEvent(
   MidiEventV008 *&         pevent,
   imedia::position                   tkMax,
   BOOL                     bTkMaxInclusive,
   bool                    bOnlyMTrk)
{
   MidiTrack *         ptrack;
   MidiTrack *         ptrkFound;
   int                     idxTrackFound;
   int                     idxTrack;
   imedia::position                   tkEventPosition;
   imedia::position                     tkEventFound;
   int                     iRelTime;
   int                     iMinRelTime;

   iMinRelTime = 0x7fffffff;
   ptrkFound = NULL;
   bool bNextEventLookUp;
   for (idxTrack = 0; idxTrack < GetActiveMidiTrackCount(); idxTrack++)
   {
      ptrack = ActiveMidiTrackAt(idxTrack);
      if(ptrack->_WorkIsEOT())
      {
         DeactivateTrack(ptrack);
         continue;
      }
      if(bOnlyMTrk)
      {
         MidiTrack * ptrackMidi = (MidiTrack *) ptrack;
         CHUNKHDR FAR * pCh = (CHUNKHDR FAR *) ptrackMidi->GetTrackImage();
         if (pCh->fourccType != FOURCC_MTrk)
            continue;
      }
      bNextEventLookUp = true;
      while(true)
      {
         tkEventPosition = ptrack->_WorkGetPosition();
         iRelTime = tkEventPosition - m_tkPosition;
         if(iRelTime < 0)
         {
            if(ptrack->_WorkMoveNext() != VMSR_SUCCESS)
            {
               if(ptrack->_WorkIsEOT())
               {
                  DeactivateTrack(ptrack);
               }
               bNextEventLookUp = false;
               break;
            }
         }
         else
         {
            break;
         }
      }
      if(!bNextEventLookUp)
      {
         continue;
      }
      ASSERT(iRelTime >= 0);

      if(iRelTime < iMinRelTime)
      {
         iMinRelTime = iRelTime;
         ptrkFound = ptrack;
         idxTrackFound = idxTrack;
         tkEventFound = tkEventPosition;
         if(iRelTime == 0)
            break;
      }
   }

   if (ptrkFound == NULL)
   {
      return ::mus::midi::SEndOfFile;
   }

   ptrack = ptrkFound;

    imedia::position tkPosition = tkEventFound;

   iRelTime = tkPosition - m_tkPosition;
   ASSERT(iRelTime >= 0);
   if(iRelTime < 0)
      iRelTime = 0;



   if(ptrack->get_type() == MidiTrackBase::TypeLyric)
   {
      ASSERT(true);
   }

   if(bTkMaxInclusive)
   {
      if (m_tkPosition + iMinRelTime > tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition + iMinRelTime >= tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
    
   ptrack->_WorkGetEvent(pevent, tkMax, bTkMaxInclusive);
   
   m_iCurrentTrack = idxTrackFound;
   m_tkPosition = ptrack->GetPosition();
   ptrack->_WorkMoveNext();
   
   if(ptrack->_WorkIsEOT())
   {
      DeactivateTrack(ptrack);
   }
   return ::mus::midi::Success;
}

void MidiTracks::WorkSeekBegin()
{
   m_trackaActive = m_tracka;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrackBase * ptrack = (MidiTrack *) TrackAt(i);
      ptrack->WorkSeekBegin();
   }
   m_tkPosition = 0;
   GetFlags().unsignalize(::mus::midi::EndOfTrack);
}

void MidiTracks::WorkSeekEnd()
{
   imedia::position tkPosition = 0;
   for (int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrackBase * ptrack = (MidiTrack *) TrackAt(i);
      ptrack->WorkSeekEnd();
      if(ptrack->GetPosition() > tkPosition)
      {
         tkPosition = ptrack->GetPosition();
      }
   }
   m_tkPosition = tkPosition;
   GetFlags().signalize(::mus::midi::EndOfTrack);
}


::mus::midi::e_file_result MidiTracks::WorkGetXFTokens(UINT uiCodePage, string2a & token2a, imedia::position_2darray *p2DTicks, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a)
{
   ASSERT(p2DTicks != NULL);
   ASSERT(pxflh2a != NULL);
   stringa  tokena;
   imedia::position_array * lptkaTicks = NULL;
   XFLyricsHeader xflh;
   ASSERT(FALSE);

   imedia::position_array positiona;

   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->WorkSeekBegin();
      ::mus::midi::e_file_result smfr;
      smfr = ptrack->WorkSeekXFLyricsHeader();
      if(smfr == ::mus::midi::Success)
      {
         smfr = ptrack->WorkReadXFLyricsHeader(&xflh);
      }

      tokena.remove_all();

      lptkaTicks = new imedia::position_array();
      ptrack->WorkSeekBegin();
      smfr = ptrack->WorkReadXFTokens(uiCodePage, tokena, lptkaTicks);

      if(smfr == ::mus::midi::Success 
      || smfr == ::mus::midi::SEndOfTrack)
      {
         token2a.add(tokena);
         p2DTicks->add(lptkaTicks);
         pxflh2a->add(xflh);
      }
      else
      {
         delete lptkaTicks;
      }
      lptkaTicks = NULL;
   }
   return ::mus::midi::Success;
}


/*::mus::midi::e_file_result MidiTracks::WorkGetXFTokens(
      string2a &
            token2a,
      imedia::position_2darray *p2DTicks,
      base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a)
{
   ASSERT(p2DTicks != NULL);
   ASSERT(pxflh2a != NULL);
   stringa  tokena;
   imedia::position_array * lptkaTicks = NULL;
   XFLyricsHeader xflh;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->WorkSeekBegin();
      ::mus::midi::e_file_result smfr;
      smfr = ptrack->WorkSeekXFLyricsHeader();
      if(smfr == ::mus::midi::Success)
      {
         smfr = ptrack->WorkReadXFLyricsHeader(&xflh);
      }


        tokena.remove_all();
        lptkaTicks = new imedia::position_array();
      ptrack->WorkSeekBegin();
      smfr = ptrack->WorkReadXFTokens(tokena, lptkaTicks);
      if(::mus::midi::Success == smfr)
      {
         token2a.add(tokena);
         p2DTicks->add(lptkaTicks);
         pxflh2a->add(xflh);
      }
        else
        {
            delete lptkaTicks;
        }
        lptkaTicks = NULL;
   }
   return ::mus::midi::Success;
}*/



::mus::midi::e_file_result MidiTracks::WorkGetXFTokens(UINT uiCodePage, string2a & token2a, imedia::position_2darray & position2a, int2a & i2aTokenLine, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a)
{
   stringa  tokena;
   int_array iaTokenLine;
   imedia::position_array positiona;
   XFLyricsHeader xflh;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->WorkSeekBegin();
      ::mus::midi::e_file_result smfr;
      if(pxflh2a != NULL)
      {
      
         smfr = ptrack->WorkSeekXFLyricsHeader();
         if(smfr == ::mus::midi::Success)
         {
            smfr = ptrack->WorkReadXFLyricsHeader(&xflh);
         }
      }


      tokena.remove_all();
      positiona.remove_all();
      iaTokenLine.remove_all();
      ptrack->WorkSeekBegin();
      smfr = ptrack->WorkReadXFTokens(uiCodePage, tokena, positiona, iaTokenLine);
      if(::mus::midi::Success == smfr)
      {
         token2a.add(tokena);
         position2a.add(positiona);
         i2aTokenLine.add(iaTokenLine);
         if(pxflh2a != NULL)
         {
            pxflh2a->add(xflh);
         }
      }
   }
   return ::mus::midi::Success;
}


::mus::midi::e_file_result MidiTracks::WorkGetEmptyXFTokens(int iTrack, string2a & token2a, imedia::position_2darray & position2a, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a)
{
   UNREFERENCED_PARAMETER(pxflh2a);
   stringa  tokena;
   imedia::position_array positiona;
   XFLyricsHeader xflh;
   ::mus::midi::e_file_result smfrc;
   string str;
   WorkSeekBegin();
   MidiEventV008 * pevent = NULL;
   int i = 0;
   while(true)
   {
      smfrc   = WorkGetNextEvent(pevent, 0x0fffffff, true, false);
      if(smfrc != ::mus::midi::Success)
      {
         break;
      }
      if(pevent->GetTrack() == iTrack
         && ::mus::midi::NoteOn == pevent->GetType_()
         && pevent->GetNoteVelocity() != 0)
      {
         if((i % 3) == 0)
         {
            str = "<---";
         }
         else
         {
            str = "---";
         }
         
         TRACE("%s\n", str);
         tokena.add(str);
         positiona.add(imedia::position(m_tkPosition));
         i++;
      }
   }
   token2a.add(tokena);
   position2a.add(positiona);

   return smfrc;
}

::mus::midi::e_file_result MidiTracks::WorkGetSoftKaraokeTokens(string2a & token2a, imedia::position_2darray * p2DTicks, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a)
{
   ASSERT(p2DTicks != NULL);
   ASSERT(pxflh2a != NULL);
   stringa  tokena;
   imedia::position_array * lptkaTicks = NULL;
   XFLyricsHeader xflh;
   for(int i = 0; i < GetTrackCount(); i++)
   {
      MidiTrack *ptrack = (MidiTrack *)TrackAt(i);
        if(!ptrack->IsType(MidiTrackBase::TypeMidi))
            continue;
      ptrack->WorkSeekBegin();
      tokena.remove_all();
      lptkaTicks = new imedia::position_array();
      if(::mus::midi::Success == ptrack->WorkReadKarTokens(
         tokena, lptkaTicks))
      {
         token2a.add(tokena);
         p2DTicks->add(lptkaTicks);
         pxflh2a->add(xflh);
      }
      else
      {
         delete lptkaTicks;
      }

      ptrack->WorkSeekBegin();
      tokena.remove_all();
      lptkaTicks = new imedia::position_array();
      if(::mus::midi::Success == ptrack->WorkReadTune1000Tokens(
         tokena, lptkaTicks))
      {
         token2a.add(tokena);
         p2DTicks->add(lptkaTicks);
         pxflh2a->add(xflh);
      }
      else
      {
         delete lptkaTicks;
      }
      lptkaTicks = NULL;
   }
   return ::mus::midi::Success;
}


::mus::midi::e_file_result MidiTracks::WorkQuantizeVR()
{
   for(int i = 0; i < m_tracka.GetTrackCount(); i++)
   {

   }
   return ::mus::midi::Success;
}

MidiTrack * MidiTracks::CreateTrack(index iIndex, FOURCC fourcc)
{
   return m_tracka.CreateTrack(iIndex, fourcc);
}

void MidiTracks::remove_all()
{
   m_tracka.remove_all();
   m_trackaActive.remove_all();
}

MidiTrack * MidiTracks::CreateTrack(FOURCC fourcc)
{
   return m_tracka.CreateTrack(fourcc);
}




// remove all MidiTrack tracks

void MidiTracks::RemoveAllMidiTracks()
{
   m_tracka.RemoveAllMidiTracks();
}

void MidiTracks::DeactivateTrack(MidiTrackBase * ptrack)
{
   m_trackaActive.RemoveTrack(ptrack);
}
void MidiTracks::clear()
{
   remove_all();
   m_tkPosition         = 0;
   m_iLyricDelay        = 0;
   m_bVolumeEventSent   = false;

}


void MidiTracks::remove_at(index iIndex)
{
   m_tracka.remove_at(iIndex);
}





void MidiTracks::SetAutoAllocation(bool bSet)
{
   for (int i = 0; i < GetTrackCount(); i++)
    {
      MidiTrackBase * ptrack = TrackAt(i);
      if(ptrack->IsType(MidiTrackBase::TypeMidi))
      {
         MidiTrack * pmiditrack = (MidiTrack *) ptrack;
         pmiditrack->SetAutoAllocation(bSet);
      }
    }

}



::mus::midi::file_flags & MidiTracks::GetFlags()
{
   return m_flagsFile;
}



MidiTrack * MidiTracks::TrackPtrAllocArray::CreateTrack(FOURCC fourcc)
{
   return CreateTrack(GetMidiTrackCount(), fourcc);
}

MidiTrack * MidiTracks::TrackPtrAllocArray::CreateTrack(index iIndex, FOURCC fourcc)
{
   if(iIndex >= m_miditracka.get_size())
   {
      while(iIndex >= m_miditracka.get_size())
      {
         m_miditracka.add(new MidiTrack(get_app()));
         m_tracka.add(m_miditracka.last_ptr());
      }
   }
   MidiTrack * ptrack = m_miditracka.ptr_at(iIndex);
   ptrack->WorkClear();
   ptrack->Initialize(m_ptracks);
   ptrack->GetWorkTrack().m_chunkHeader.fourccType = fourcc;
   ptrack->WorkSeekBegin();
   ptrack->seek_begin();
   return ptrack;
}

MidiLyricTrack * MidiTracks::TrackPtrAllocArray::CreateLyricTrack()
{
   return CreateLyricTrack(GetLyricTrackCount());
}

MidiLyricTrack * MidiTracks::TrackPtrAllocArray::CreateLyricTrack(index iIndex)
{
   MidiLyricTrack * ptrack;
   if(iIndex >= m_lyrictracka.get_size())
   {
      while(iIndex >= m_lyrictracka.get_size())
      {
         ptrack = new MidiLyricTrack(get_app());
         m_lyrictracka.add(ptrack);
         m_tracka.add(ptrack);
      }
   }
   ptrack = m_lyrictracka.ptr_at(iIndex);
   ptrack->m_pfile = m_ptracks->m_pFile;
   return ptrack;
}

void MidiTracks::TrackPtrAllocArray::RemoveTrack(MidiTrackBase * ptrack)
{
   m_miditracka      -= ptrack;
   m_lyrictracka     -= ptrack;
   m_tracka          -= ptrack;
}

void MidiTracks::TrackPtrArray::RemoveTrack(MidiTrackBase * ptrack)
{
   m_miditracka      -= ptrack;
   m_lyrictracka     -= ptrack;
   m_tracka          -= ptrack;
}

void MidiTracks::TrackPtrAllocArray::copy(TrackPtrAllocArray & base_array)
{
   m_miditracka         = base_array.m_miditracka;
   m_lyrictracka        = base_array.m_lyrictracka;
   m_tracka.ptr_copy(base_array.m_tracka);
}

void MidiTracks::TrackPtrArray::copy(TrackPtrAllocArray & base_array)
{
   m_miditracka.ptr_copy(base_array.m_miditracka);
   m_lyrictracka.ptr_copy(base_array.m_lyrictracka);
   m_tracka.ptr_copy(base_array.m_tracka);
}

MidiTracks::TrackPtrArray & MidiTracks::TrackPtrArray::operator = (TrackPtrAllocArray & base_array)
{
   copy(base_array);
   return *this;
}

void MidiTracks::TrackPtrAllocArray::remove_at(index iIndex)
{
   MidiTrackBase * ptrack  = m_tracka.ptr_at(iIndex);
   m_miditracka            -= ptrack;
   m_lyrictracka           -= ptrack;
   m_tracka                -= ptrack;
}

void MidiTracks::TrackPtrAllocArray::remove_all()
{
   m_tracka.remove_all();
   m_miditracka.remove_all();
   m_lyrictracka.remove_all();
}

void MidiTracks::TrackPtrArray::remove_all()
{
   m_tracka.remove_all();
   m_miditracka.remove_all();
   m_lyrictracka.remove_all();
}

void MidiTracks::TrackPtrAllocArray::RemoveAllMidiTracks()
{
   while(m_miditracka.get_size() > 0)
   {
      MidiTrack * ptrack = m_miditracka.ptr_at(0);
      m_tracka -= ptrack;
      m_miditracka.remove_at(0);
   }
}

MidiTracks::TrackPtrAllocArray::TrackPtrAllocArray(::ca::application * papp)
: ca(papp)
{
   m_ptracks = NULL;
}

void MidiTracks::TrackPtrAllocArray::Initialize(MidiTracks *ptracks)
{
   m_ptracks = ptracks;
}

MidiTracks::TrackPtrArray::TrackPtrArray()
{
   m_ptracks = NULL;
}

void MidiTracks::TrackPtrArray::Initialize(MidiTracks *ptracks)
{
   m_ptracks = ptracks;
}

imedia::position MidiTracks::CalcTkLength()
{
   imedia::position tk = 0;
   for(int i = 0; i < GetMidiTrackCount(); i++)
   {
      if(MidiTrackAt(i)->m_smti.m_tkLength > (int) tk)
      {
         tk = MidiTrackAt(i)->m_smti.m_tkLength;
      }
   }
   return tk;
}



MidiTrackBase * MidiTracks::TrackAt(index iIndex)
{
   return m_tracka.TrackAt(iIndex);
}

// MidiTracks::TrackPtrAllocArray
MidiTrackBase * MidiTracks::TrackPtrAllocArray::TrackAt(index iIndex)
{
   return m_tracka.ptr_at(iIndex);
}

count MidiTracks::TrackPtrAllocArray::GetTrackCount() const
{
   return m_tracka.get_size();
}

count MidiTracks::TrackPtrAllocArray::GetMidiTrackCount() const
{
   return m_miditracka.get_size();
}

count MidiTracks::TrackPtrAllocArray::GetLyricTrackCount()
{
   return m_lyrictracka.get_size();
}

MidiTrack * MidiTracks::TrackPtrAllocArray::MidiTrackAt(index iIndex)
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < GetMidiTrackCount());
   return m_miditracka.ptr_at(iIndex);
}

MidiTrack * MidiTracks::TrackPtrAllocArray::MidiTrackAt(index iIndex) const
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < GetMidiTrackCount());
   return const_cast < MidiTrack *> (m_miditracka.ptr_at(iIndex));
}

MidiLyricTrack * MidiTracks::TrackPtrAllocArray::LyricTrackAt(index iIndex)
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < GetLyricTrackCount());
   return m_lyrictracka.ptr_at(iIndex);

}

// MidiTracks::TrackPtrArray
MidiTrackBase * MidiTracks::TrackPtrArray::TrackAt(index iIndex)
{
   return &m_tracka.element_at(iIndex);
}

count MidiTracks::TrackPtrArray::GetTrackCount() const
{
   return m_tracka.get_size();
}

count MidiTracks::TrackPtrArray::GetMidiTrackCount() const
{
   return m_miditracka.get_size();
}

count MidiTracks::TrackPtrArray::GetLyricTrackCount()
{
   return m_lyrictracka.get_size();
}

MidiTrack * MidiTracks::TrackPtrArray::MidiTrackAt(index iIndex)
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < GetMidiTrackCount());
   return m_miditracka.ptr_at(iIndex);
}

MidiLyricTrack * MidiTracks::TrackPtrArray::LyricTrackAt(index iIndex)
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < GetLyricTrackCount());
   return m_lyrictracka.ptr_at(iIndex);

}

count MidiTracks::GetTrackCount()
{
   return m_tracka.GetTrackCount();
}


MidiTrack * MidiTracks::MidiTrackAt(index iIndex)
{
   return m_tracka.MidiTrackAt(iIndex);
}

MidiTrack * MidiTracks::MidiTrackAt(index iIndex) const
{
   return m_tracka.MidiTrackAt(iIndex);
}

MidiTrack * MidiTracks::ActiveMidiTrackAt(index iIndex)
{
   return m_trackaActive.MidiTrackAt(iIndex);
}

MidiTrackBase * MidiTracks::ActiveTrackAt(index iIndex)
{
   return m_trackaActive.TrackAt(iIndex);
}

count MidiTracks::GetMidiTrackCount() const
{
   return m_tracka.GetMidiTrackCount();
}

count MidiTracks::GetActiveTrackCount() const
{
   return m_trackaActive.GetTrackCount();
}

count MidiTracks::GetActiveMidiTrackCount() const
{
   return m_trackaActive.GetMidiTrackCount();
}

imedia::position MidiTracks::GetPosition()
{
   return m_tkPosition;
}
