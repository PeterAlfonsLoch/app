#include "StdAfx.h"
#include <math.h>


Star350Tracks::Star350Tracks(Star350File * pfile) :
   primitive_array < Star350TrackBase * >()
{
    m_pfile = pfile;
   m_tkPosition = 0;
    m_iLyricDelay = 0;

}

Star350Tracks::~Star350Tracks()
{

}

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
*   Star350File::Success The events were successfully read.
*   Star350File::EndOfFile There are no more events to read in this track.
*   Star350File::ReachedTkMax No event was read because <p tkMax> was reached.
*   Star350File::InvalidFile A disk or parse error occured on the spfile->
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
*  The following fields in pTrk are used to maintain state and must
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
SMFRESULT Star350Tracks::GetNextEvent(
   midi_event_base *      pEvent,
   imedia::position                   tkMax,
   BOOL               bTkMaxInclusive,
   bool bOnlyMTrk,
   bool bOnlyMidiTrack)
{
   Star350TrackBase *      pTrk;
   Star350TrackBase *      pTrkFound;
   int                  idxTrackFound;
   int                  idxTrack;
//    imedia::position                   tkEventDelta;
    imedia::position                   tkEventPosition;
    imedia::position                     iRelTime;
    imedia::position                     iMinRelTime;
   SMFRESULT            smfrc;

    ASSERT(pEvent != NULL);


    iMinRelTime = 0x7fffffff;
   pTrkFound = NULL;

   for (idxTrack = 0; idxTrack < m_nSize; idxTrack++)
    {
      pTrk = operator [](idxTrack);
        if(bOnlyMTrk)
        {
            if(base < Star350EventTrack >::bases(pTrk))
            {
                Star350EventTrack * pTrack = (Star350EventTrack *) pTrk;
                CHUNKHDR FAR * pCh = (CHUNKHDR FAR *)pTrack->GetImage();
                if (pCh->fourccType != FOURCC_MTrk)
                 continue;
            }
        }
        else if(bOnlyMidiTrack)
        {
            if(!base < Star350EventTrack >::bases(pTrk))
                continue;
        }

        if (pTrk->GetFlags() & SMF_TF_EOT)
            continue;


        if(pTrk->GetNextEventPosition(&tkEventPosition, tkMax) != VMSR_SUCCESS)
        {
            continue;
        }

        iRelTime = tkEventPosition - m_tkPosition;

        if (iRelTime < iMinRelTime)
        {
            iMinRelTime = iRelTime;
            pTrkFound = pTrk;
         idxTrackFound = idxTrack;
        }
    }

    if (pTrkFound == NULL)
    {
        return Star350File::EndOfFile;
    }

    pTrk = pTrkFound;

    if(base < Star350LyricTrack >::bases(pTrk))
    {
        ASSERT(true);
    }

   if(bTkMaxInclusive)
   {
      if (m_tkPosition + iMinRelTime > tkMax)
      {
         return Star350File::ReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition + iMinRelTime >= tkMax)
      {
         return Star350File::ReachedTkMax;
      }
   }

   smfrc = pTrk->GetEvent(pEvent, tkMax, bTkMaxInclusive);

   if(smfrc != Star350File::Success)
      return smfrc;

   //pEvent->operator =(*pTrk->GetEvent());

    imedia::position tkPosition = pTrk->get_position();

    iRelTime = pTrk->get_position() - m_tkPosition;
    if(iRelTime < 0)
        iRelTime = 0;

   pEvent->SetDelta(iRelTime);
   m_tkPosition = m_tkPosition + iRelTime;
    m_iCurrentTrack = idxTrackFound;

    return Star350File::Success;
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
SMFRESULT Star350Tracks::GetNextEventTkPosition(
    imedia::position *               pTkPosition,
    imedia::position                   tkMax)
{
   Star350TrackBase *         pTrk;
   Star350TrackBase *         pTrkFound ;
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

    if (m_fdwSMF & Star350File::FlagEof)
    {
        return Star350File::EndOfFile;
    }

    pTrkFound       = NULL;
    tkMinRelTime    = MAX_TICKS;

    //for (pTrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; pTrk++)
   for (idxTrack = 0; idxTrack < m_nSize; idxTrack++)
    {
      pTrk = operator [](idxTrack);
        if (pTrk->GetFlags() & SMF_TF_EOT)
            continue;

//      if(pTrk->GetState() == Star350EventTrack::StateOnDelta)
//      {
//         if(pTrk->ReadDelta() != Star350File::Success)
//         {
//            TRACE("Hit end of track w/o end marker!\n");
//               return Star350File::InvalidFile;
//         }
//      }

//      tkEventDelta = pTrk->m_tkDelta;

        if (VMSR_SUCCESS != (vmsr = pTrk->GetNextEventPosition(&tkEventPosition, tkMax)))
        {
            continue;
        }

       tkRelTime = tkEventPosition - m_tkPosition;

        if (tkRelTime < tkMinRelTime)
        {
            tkMinRelTime = tkRelTime;
            pTrkFound = pTrk;
            tkEventPositionFound = tkEventPosition;
        }
    }

    if (pTrkFound == NULL)
    {
        m_fdwSMF |= Star350File::FlagEof;
        return Star350File::EndOfFile;
    }

    pTrk = pTrkFound;

    if (m_tkPosition + tkMinRelTime > tkMax)
    {
        return Star350File::ReachedTkMax;
    }


//    dwGot = pTrk->m_dwUsed;
//   tkEventDelta = pTrk->m_tkDelta;
    //pTrk->cbLeft   -= dwGot;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short event, which is most cases.
    */
    //if (pTrk->cbLeft < 3)
    //{
        //return Star350File::InvalidFile;
    //}

//    *pTkPosition = pTrk->m_tkPosition + tkEventDelta;
    *pTkPosition = tkEventPositionFound;
    return Star350File::Success;
}

void Star350Tracks::seek_begin()
{
   for (int i = 0; i < m_nSize; i++)
    {
      Star350TrackBase * pTrk = this->element_at(i);
      pTrk->seek_begin();
    }
    m_tkPosition = 0;
}

/*SMFRESULT Star350Tracks::GetXFTokens(
      C2DStringArray *p2DTokens,
      C2DTickArray *p2DTicks)
{
   ASSERT(p2DTokens != NULL);
   ASSERT(p2DTicks != NULL);
   StringArray * lpstraTokens = NULL;
   CTickArray * lptkaTicks = NULL;
   for(int i = 0; i < m_nSize; i++)
   {
      Star350EventTrack *pTrk = (Star350EventTrack *)operator [](i);
        if(!base < Star350EventTrack >::bases(pTrk))
            continue;
      pTrk->seek_begin();
        lpstraTokens = new StringArray();
        lptkaTicks = new CTickArray();
      if(Star350File::Success == pTrk->ReadXFTokens(lpstraTokens, lptkaTicks))
      {
         p2DTokens->add(lpstraTokens);
         p2DTicks->add(lptkaTicks);
      }
        else
        {
            delete lpstraTokens;
            delete lptkaTicks;
        }
        lpstraTokens = NULL;
        lptkaTicks = NULL;
   }
   return Star350File::Success;
}*/

/*SMFRESULT Star350Tracks::GetKarTokens(
      C2DStringArray *p2DTokens,
      C2DTickArray *p2DTicks)
{
   ASSERT(p2DTokens != NULL);
   ASSERT(p2DTicks != NULL);
   StringArray * lpstraTokens = NULL;
   CTickArray * lptkaTicks = NULL;
   for(int i = 0; i < m_nSize; i++)
   {
      Star350EventTrack *pTrk = (Star350EventTrack *)operator [](i);
        if(!base < Star350EventTrack >::bases(pTrk))
            continue;
      pTrk->seek_begin();
        lpstraTokens = new StringArray();
        lptkaTicks = new CTickArray();
      if(Star350File::Success == pTrk->ReadKarTokens(lpstraTokens, lptkaTicks))
      {
         p2DTokens->add(lpstraTokens);
         p2DTicks->add(lptkaTicks);
      }
        else
        {
            delete lpstraTokens;
            delete lptkaTicks;
        }
        lpstraTokens = NULL;
        lptkaTicks = NULL;
   }
   return Star350File::Success;
}*/


/*SMFRESULT Star350Tracks::GetXFInfoHeaders(
   CXFInfoHeaders *pxfihs)
{
   ASSERT(pxfihs != NULL);
   pxfihs->Empty();
   int nIndex, nSize;
   nSize = m_nSize;
   //string str lpsz;
   //XFInfoHeader * pxfih;
   //XFInfoHeaderLS * pxfihls;
   XFInfoHeaderLS xfihls;
   for(nIndex = 0; nIndex < nSize; nIndex++)
   {
      Star350EventTrack *pTrk = (Star350EventTrack *)operator [](nIndex);
        if(!base < Star350EventTrack >::bases(pTrk))
            continue;
      if(pxfihs->m_xfInfoHeader.is_empty())
      {
         pTrk->seek_begin();
         pTrk->GetNextXFInfoHeader(&pxfihs->m_xfInfoHeader);
         pTrk->seek_begin();
         pTrk->GetNextXFSongName(pxfihs->m_strSongName);
      }
      pTrk->seek_begin();

      if(Star350File::Success == pTrk->GetNextXFInfoHeaderLS(&xfihls))
      {
         pxfihs->m_xfaInfoHeaderLS.add(xfihls);
      }
      if(pxfihs->m_strSongName.is_empty())
      {
         pTrk->seek_begin();
         pTrk->GetNextXFSongName(pxfihs->m_strSongName);
      }
   }
   return Star350File::EndOfFile;

}*/


/*SMFRESULT Star350Tracks::GetKarInfoHeader(
   SoftKaraokeInfo *pKarI)
{
   ASSERT(pKarI != NULL);
   if(m_nSize >=3)
   {
      Star350EventTrack *pTrk = (Star350EventTrack *) operator [](2);
        ASSERT(base < Star350EventTrack >::bases(pTrk));
      return pTrk->GetNextKarInfo(pKarI);
   }
   else
   {
      Star350EventTrack *pTrk = (Star350EventTrack *) operator [](0);
        ASSERT(base < Star350EventTrack >::bases(pTrk));
      return pTrk->GetNextKarInfo(pKarI);
   }

}*/

/*SMFRESULT Star350Tracks::GetTune1000InfoHeader(
   CTune1000Info *pTune1000I)
{
   ASSERT(pTune1000I != NULL);
//   if(m_nSize >=3)
//   {
//      Star350EventTrack *pTrk = operator [](2);
//      return pTrk->GetNextTune1000Info(pTune1000I);
//   }
//   else
//   {
    if(this->get_size() > 0)
    {
      Star350EventTrack *pTrk = (Star350EventTrack *) operator [](0);
        ASSERT(base < Star350EventTrack >::bases(pTrk));
      return pTrk->GetNextTune1000Info(pTune1000I);
    }
    else
    {
        return Star350File::NotFound;
    }

//   }

}*/

/*int Star350Tracks::CalcMelodyTrack(
   CMidiEventsV1 ** ppEventsRet,
   CTickArray *pTicks,
   WORD wFileFormat)
{
   ASSERT(*ppEventsRet == NULL);
   int i, j, k, iMatches, iSize;
   int iBestMatch;
   dword_array dwaBestMatchesIndexes;
   dword_array dwaBestMatchesScores;
   imedia::position tkTolerance = 0;
   imedia::position tkPositionA, tkPositionB;
   //const imedia::position tkToleranceAddUp = 60;
    const imedia::position tkToleranceAddUp = DWORDSWAP(m_pfile->m_pFileHeader->wDivision) / 4;
   Star350EventTrack * pTrack;
   CMidiEventsV1 * pEvents;
   primitive_array < CMidiEventsV1 *> eventsArray;
   //primitive_array < primitive_array < CMidiEventsV1 *>> eventsArray2D;
   int_array eventsMatches;
   bool bAnyTrack = m_pfile->GetFormat() == 1;
   const int max_tracks_search = 16;
   if(m_pfile->GetFormat() == 1)
   {
      iSize = m_nSize;
   }
   else
   {
      iSize = max_tracks_search;
   }
   while(tkTolerance <= DWORDSWAP(m_pfile->m_pFileHeader->wDivision))
   {
      for(i = 0; i < iSize; i++)
      {
         if(m_pfile->GetFormat() == 0)
         {
            pTrack = (Star350EventTrack *) this->element_at(0);
         }
         else
         {
            if(i >= m_nSize)
               break;
            pTrack = (Star350EventTrack *) this->element_at(i);
         }
            if(!base < Star350EventTrack >::bases(pTrack))
                continue;
         pEvents = new CMidiEventsV1();
         pTrack->seek_begin();
         pTrack->GetStandardEventsV1(pEvents, ::mus::midi::NoteOn, i, bAnyTrack);
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

   }
//   if(iBestMatch >= 0)
   if(dwaBestMatchesIndexes.get_size() > 0)
   {

      int iWorstMatches = 0x7fffffff;
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
/*      if(iBestMatch >= 0)
      {
         if(m_pfile->GetFormat() == 0)
         {
            pTrack = (Star350EventTrack *) this->element_at(0);
         }
         else
         {
            if(i >= m_nSize)
               goto Skip090;
            pTrack = (Star350EventTrack *) this->element_at(iBestMatch);
         }
         pEvents = new CMidiEventsV1();
         pTrack->seek_begin();
         pTrack->GetStandardEventsV1(pEvents, ::mus::midi::NoteOn, iBestMatch, bAnyTrack);
         *ppEventsRet = pEvents;
      }
Skip090:;

   }

   return iBestMatch;

}*/

/*bool Star350Tracks::IsSoftKaraokeFile(CStdioFile * lpFile)
{
    bool bIsSoftKaraokeFile;
   if(m_nSize < 2)
    {
      bIsSoftKaraokeFile = false;
    }
   else
    {
        Star350EventTrack * pTrack = (Star350EventTrack *)this->element_at(1);
        pTrack->seek_begin();
        if(!base < Star350EventTrack >::bases(pTrack) || !(bIsSoftKaraokeFile = pTrack->IsSoftKaraokeFile(lpFile)))
        {
            if(m_nSize >= 3)
            {
                Star350EventTrack * pTrack = (Star350EventTrack *)this->element_at(2);
                if(!base < Star350EventTrack >::bases(pTrack))
                {
                    bIsSoftKaraokeFile = false;
                }else
                {
                    pTrack->seek_begin();
                    StringArray strArray;
                    CTickArray tkArray;
                    pTrack->seek_begin();
                    pTrack->ReadKarTokens(&strArray, &tkArray);
                    if(strArray.get_size() > 0)
                        bIsSoftKaraokeFile = true;
                }
            }
        }
    }
    return bIsSoftKaraokeFile;
}*/

/*Star350EventTrack * Star350Tracks::GetEventTrack(midi_event_base *pEvent)
{
   int i;
   for(i = 0; i < m_nSize; i++)
   {
      Star350EventTrack * pTrack = &this->element_at(i);
      if(pTrack->ContainsEvent(pEvent))
         return pTrack;
   }
   return NULL;
} */

Star350EventTrack * Star350Tracks::seek(DWORD dwSeekWhat)
{
   for(int i = 0; i < m_nSize; i++)
   {
      Star350EventTrack * pTrack = (Star350EventTrack *)this->element_at(i);
        if(!base < Star350EventTrack >::bases(pTrack))
            continue;
      pTrack->seek_begin();
      if(pTrack->seek(dwSeekWhat) == Star350File::Success)
        {
            m_iCurrentTrack = i;
         return pTrack;
        }
   }
   return NULL;
}

bool Star350Tracks::IsXFFile()
{
    if(m_nSize <= 0)
        return false;
    else
    {
        for(int i = 0; i < m_nSize; i++)
        {
          Star350EventTrack * pTrack = (Star350EventTrack *)this->element_at(i);
            if(!base < Star350EventTrack >::bases(pTrack))
                continue;
            if(pTrack->IsXFFile())
            {
                return true;
            }
        }
        return false;
    }

}



/*void Star350Tracks::FromWorkStorage()
{
   for(int i = 0; i < m_nSize; i++)
   {
      Star350EventTrack * pTrack = (Star350EventTrack *)this->element_at(i);
        if(!base < Star350EventTrack >::bases(pTrack))
            continue;
      pTrack->FromWorkStorage();
   }

}*/

void Star350Tracks::ToWorkStorage()
{

    for(int i = 0; i < m_nSize; i++)
   {
      Star350EventTrack * pTrack = (Star350EventTrack *)this->element_at(i);
        if(!base < Star350EventTrack >::bases(pTrack))
            continue;
      pTrack->ToWorkStorage();
   }
}

/*VMSRESULT Star350Tracks::CompactTracks(
    Star350EventTrack & trackUnion,
    bool bOnlyMTrk,
    bool bOnlyMidiTrack)
{
//    Star350EventTrack trackUnion;
    trackUnion.SetAutoAllocation();
    seek_begin();
    CMidiEventV001 midiEvent;
    while(Star350File::Success == GetNextEvent(&midiEvent, 0x7fffffff, true, bOnlyMTrk, bOnlyMidiTrack))
    {
        if(midiEvent.GetFullType() == ::mus::midi::Meta &&
            midiEvent.GetMetaType() == ::mus::midi::MetaEOT)
        {
        }
        else
        {
            *trackUnion.GetEvent() = midiEvent;
            trackUnion.WriteCompleteEvent(0x7fffffff, false);
        }
    }
    midiEvent.SetFullType(::mus::midi::Meta);
    midiEvent.SetMetaType(::mus::midi::MetaEOT);
    midiEvent.SetParam(NULL, 0);
    *trackUnion.GetEvent() = midiEvent;
    trackUnion.WriteCompleteEvent(0x7fffffff, false);

    CHUNKHDR hdr;
    hdr.fourccType = FOURCC_MTrk;
    hdr.dwLength = trackUnion.m_smti.m_cbLength;
    trackUnion.WriteHeader(&hdr);


    return VMSR_SUCCESS;

}*/

/*VMSRESULT Star350Tracks::ExpandTrack(int iTrackIndex)
{
//    Star350EventTrack trackUnion;
    Star350EventTrack * ptrackParam = (Star350EventTrack *) this->element_at(iTrackIndex);
    ASSERT(base < Star350EventTrack >::bases(ptrackParam));
    remove_at(iTrackIndex);
    ptrackParam->seek_begin();
    ::collection::map<int, int, Star350EventTrack *, Star350EventTrack *> mapTracks;
    Star350EventTrack * ptrack;
    CMidiEventV001 * pmidieev;
    while(Star350File::Success == ptrackParam->ReadEvent(0x7fffffff, true))
    {
        pmidieev = ptrackParam->GetEvent();
        if(pmidieev->GetFullType() == ::mus::midi::Meta &&
            pmidieev->GetMetaType() == ::mus::midi::MetaEOT)
        {
        }
        else if(pmidieev->GetFullType() < ::mus::midi::SysEx)
        {
            if(!mapTracks.Lookup(pmidieev->GetTrack(), ptrack))
            {
                ptrack = new Star350EventTrack();
                ptrack->SetAutoAllocation();
                mapTracks.set_at(pmidieev->GetTrack(), ptrack);
            }
            *ptrack->GetEvent() = *pmidieev;
            ptrack->WriteCompleteEvent(0x7fffffff, true);
        }
        else
        {
            if(!mapTracks.Lookup(0, ptrack))
            {
                ptrack = new Star350EventTrack();
                ptrack->SetAutoAllocation();
                mapTracks.set_at(0, ptrack);
            }
            *ptrack->GetEvent() = *pmidieev;
            ptrack->WriteCompleteEvent(0x7fffffff, true);
        }
    }
    for(int i = 15; i >= 0; i--)
    {
        if(mapTracks.Lookup(i, ptrack))
        {
            CMidiEventV001 midiEvent;
            midiEvent.SetFullType(::mus::midi::Meta);
            midiEvent.SetMetaType(::mus::midi::MetaEOT);
            midiEvent.SetParam(NULL, 0);
            *ptrack->GetEvent() = midiEvent;
            ptrack->WriteCompleteEvent(0x7fffffff, false);


            CHUNKHDR hdr;
            hdr.fourccType = FOURCC_MTrk;
            hdr.dwLength = ptrack->m_smti.m_cbLength;
            ptrack->WriteHeader(&hdr);
            ptrack->Initialize(this);
           insert_at(0, ptrack);
        }
    }
    return VMSR_SUCCESS;
}*/

int Star350Tracks::GetMidiTrackIndex(int iIndex)
{
   if(base < Star350EventTrack > :: bases(this->element_at(iIndex)))
        return ((Star350EventTrack*)this->element_at(iIndex))->GetMidiTrackIndex();
    else
        return -1;
}

VMSRESULT Star350Tracks::SetLyricDelay(int iDelay)
{
    m_iLyricDelay = iDelay;
    for(int i = 0; i < this->get_size(); i++)
    {
        Star350LyricTrack * pltrack = dynamic_cast<Star350LyricTrack *>(this->element_at(i));
        if(pltrack != NULL)
        {
            pltrack->m_iDelay = iDelay;
        }
    }
    return VMSR_SUCCESS;
}

VMSRESULT Star350Tracks::GetLyricDelay(int *lpiDelay)
{
    *lpiDelay = m_iLyricDelay;
    return VMSR_SUCCESS;
}
