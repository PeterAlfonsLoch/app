#include "StdAfx.h"
#include "Star350LyricTracks.h"

Star350LyricTracks::Star350LyricTracks(::ca::application * papp) :
   array_app_alloc < MidiLyricTrack, MidiLyricTrack & > (papp)
{

}

Star350LyricTracks::~Star350LyricTracks()
{

}

/*VMSRESULT Star350LyricTracks::GetNextEventTkPosition(
    imedia::position *               pTkPosition,
    imedia::position                   tkMax)
{
   CMidiTrack *         pTrk;
   CMidiTrack *         pTrkFound ;
   int                  idxTrack;
    imedia::position               tkEventDelta;
    imedia::position                   tkRelTime;
    imedia::position                   tkMinRelTime;
    DWORD                   dwGot;
    

//    ASSERT(pSmf != NULL);
    ASSERT(pTkPosition != NULL);

    if (m_fdwSMF & CMidiFile::FlagEof)
    {
        return CMidiFile::EndOfFile;
    }

    pTrkFound       = NULL;
    tkMinRelTime    = MAX_TICKS;
    
    //for (pTrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; pTrk++)
   for (idxTrack = 0; idxTrack < m_nSize; idxTrack++)
    {
      pTrk = &operator [](idxTrack);
        if (pTrk->m_fdwTrack & SMF_TF_EOT)
            continue;

      if(pTrk->GetState() == CMidiTrack::StateOnDelta)
      {
         if(pTrk->ReadDelta() != CMidiFile::Success)
         {
            TRACE("Hit end of track w/o end marker!\n");
               return CMidiFile::InvalidFile;
         }
      }
   
      tkEventDelta = pTrk->m_tkDelta;

       tkRelTime = pTrk->m_tkPosition + tkEventDelta - m_tkPosition;

        if (tkRelTime < tkMinRelTime)
        {
            tkMinRelTime = tkRelTime;
            pTrkFound = pTrk;
        }
    }

    if (pTrkFound == NULL)
    {
        m_fdwSMF |= CMidiFile::FlagEof;
        return CMidiFile::EndOfFile;
    }

    pTrk = pTrkFound;

    if (m_tkPosition + tkMinRelTime > tkMax)
    {
        return CMidiFile::ReachedTkMax;
    }
        

    dwGot = pTrk->m_dwUsed;
   tkEventDelta = pTrk->m_tkDelta;
    //pTrk->cbLeft   -= dwGot;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short event, which is most cases.
    */
    //if (pTrk->cbLeft < 3)
    //{
        //return CMidiFile::InvalidFile;
    //}

/*    *pTkPosition = pTrk->m_tkPosition + tkEventDelta;

    return CMidiFile::Success;
}

void Star350LyricTracks::seek_begin()
{
   for (int i = 0; i < m_nSize; i++)
    {
      CLyricTrack *pTrk = &element_at(i);
      pTrk->seek_begin();
    }
}

VMSRESULT Star350LyricTracks::GetNextEvent(
    CMidiEventV001 *         pEvent,
    imedia::position                   tkMax,
   BOOL               bTkMaxInclusive)
{
   CMidiTrack *         pTrk;
   CMidiTrack *         pTrkFound;
   int                  idxTrackFound;
   int                  idxTrack;
    imedia::position                   tkEventDelta;
    imedia::position                   tkRelTime;
    imedia::position                   tkMinRelTime;
   SMFRESULT            smfrc;

    ASSERT(pEvent != NULL);


    tkMinRelTime    = MAX_TICKS;
   pTrkFound = NULL;

   for (idxTrack = 0; idxTrack < m_nSize; idxTrack++)
    {
      pTrk = &operator [](idxTrack);
        if (pTrk->m_fdwTrack & SMF_TF_EOT)
            continue;

        
        if (pTrk->GetState() == CMidiTrack::StateOnDelta)
        {
         if(pTrk->ReadDelta() != CMidiFile::Success)
         {
            TRACE("Hit end of track w/o end marker!\n");
            return CMidiFile::InvalidFile;
         }
        }
      tkEventDelta = pTrk->m_tkDelta;

        tkRelTime = pTrk->m_tkPosition + tkEventDelta - m_tkPosition;

        if (tkRelTime < tkMinRelTime)
        {
            tkMinRelTime = tkRelTime;
            pTrkFound = pTrk;
         idxTrackFound = idxTrack;
        }
    }

    if (pTrkFound == NULL)
    {
        return CMidiFile::EndOfFile;
    }

    pTrk = pTrkFound;

   if(bTkMaxInclusive)
   {
      if (m_tkPosition + tkMinRelTime > tkMax)
      {
         return CMidiFile::ReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition + tkMinRelTime >= tkMax)
      {
         return CMidiFile::ReachedTkMax;
      }
   }
    
   smfrc = pTrk->ReadEvent(tkMax, bTkMaxInclusive);

   if(smfrc != CMidiFile::Success)
      return smfrc;

   pEvent->operator =(*pTrk->GetEvent());


   pEvent->m_tkDelta = pTrk->m_tkPosition - m_tkPosition;
   m_tkPosition = pTrk->m_tkPosition;
    m_iCurrentTrack = idxTrackFound;

    return CMidiFile::Success;
}
*/