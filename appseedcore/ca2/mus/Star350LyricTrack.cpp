#include "StdAfx.h"

Star350LyricTrack::Star350LyricTrack(Star350File * pfile)
{
    m_pfile = pfile;
    m_iDelay = 0;
    


}

Star350LyricTrack::~Star350LyricTrack()
{

}

VMSRESULT Star350LyricTrack::GetNextEventPosition(imedia::position *ptkPosition, imedia::position tkMax)
{
    if(m_iCurrentEvent >= m_trackWorkStorage.GetEventCount())
    {
        return Star350File::EndOfTrack;
    }
    MidiEventV008 & event = m_trackWorkStorage.EventAt(m_iCurrentEvent);
    
    imedia::position tkPosition = -1;
//    if(m_iCurrentEvent == m_iLastEvent &&
  //      m_iDelay == m_iLastDelay)
    //{
      //  tkPosition = m_tkLastPosition;
//    }
  //  else
    //{
        tkPosition = m_tkPosition + event.GetDelta();
//        int iMsPosition  = m_pfile->TicksToMillisecs(tkPosition);
  //      iMsPosition += m_iDelay;
    //    tkPosition = m_pfile->MillisecsToTicks(iMsPosition);
      //  m_iLastEvent = m_iCurrentEvent;
        //m_iLastDelay = m_iDelay;
//        m_tkLastPosition = tkPosition;
  //  }

    if(tkPosition > tkMax)
    {
        return Star350File::ReachedTkMax;
    }
    *ptkPosition = tkPosition;
    return VMSR_SUCCESS;
}

int Star350LyricTrack::GetFlags()
{
    return m_iFlags;
}

VMSRESULT Star350LyricTrack::GetEvent(
    MidiEventBase * pEvent,
    imedia::position   tkMax,
   BOOL   bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
    if(m_iCurrentEvent > m_trackWorkStorage.GetEventCount())
    {
        return Star350File::EndOfTrack;
    }
    MidiEventV008 & event = m_trackWorkStorage.EventAt(m_iCurrentEvent);
    imedia::position tkPosition = m_tkPosition + event.GetDelta();
    if(tkPosition > tkMax)
    {
        return Star350File::ReachedTkMax;
    }
    m_tkPosition = tkPosition;
    *pEvent = event;
    m_iCurrentEvent++;
    return VMSR_SUCCESS;
}

imedia::position Star350LyricTrack::GetPosition()
{
    imedia::position tkPosition = m_tkPosition;
//    int iMsPosition  = m_pfile->TicksToMillisecs(tkPosition);
  //  iMsPosition += m_iDelay;
    //tkPosition = m_pfile->MillisecsToTicks(iMsPosition);
    return tkPosition;
}

VMSRESULT Star350LyricTrack::seek_begin()
{
    m_iCurrentEvent = 0;
    m_tkPosition = 0;
    m_iFlags = 0;
//    m_tkLastPosition = -1;
  //  m_iLastEvent = -1;
    return VMSR_SUCCESS;
}

/*VMSRESULT Star350LyricTrack::Prepare(CLyricEventsV1 & events)
{
    m_trackWorkStorage.m_events.remove_all();
    MidiEventV008 event;
    imedia::position tkPosition;
    imedia::position tkLastPosition = 0;
    events.m_iCurrentToken = 0;
      Carray<
      CLyricEventV1,
      CLyricEventV1&>   lvaPending;

    while(events.m_iCurrentToken < events.m_tkaTokensPosition.GetEventCount())
    {
        lvaPending.add(events);
        tkPosition = events.m_tkaTokensPosition.EventAt(events.m_iCurrentToken);
        if(tkLastPosition != tkPosition)
        {
            event.SetFlags(1); // Flag 1 means POSITIONCB
            event.SetDelta(tkPosition - tkLastPosition);

              CMemFile memFile;
           CArchive ar(&memFile, CArchive::store);
            ar << EVENT_ID_LYRIC_V1;
           lvaPending.Serialize(ar);
           ar.Flush();
            DWORD dwLength = memFile.get_length();
            LPBYTE lpData = memFile.Detach();
            event.SetParam(lpData, dwLength);
            //memFile.Attach(lpData, dwLength);
            lvaPending.remove_all();
            m_trackWorkStorage.m_events.add(event);
        }
        tkLastPosition = tkPosition;
        events.m_iCurrentToken++;
    }

    return VMSR_SUCCESS;
}*/

/*VMSRESULT Star350LyricTrack::Prepare(CLyricEventsV2 & events)
{
    m_trackWorkStorage.m_events.remove_all();
    MidiEventV008 event;
    imedia::position tkPosition;
    imedia::position tkLastPosition = 0;
    events.m_iCurrentToken = 0;
    events.m_iCurrentNote = 0;
      Carray<
      CLyricEventV1,
      CLyricEventV1&>   lvaPending;
    Carray<DWORD, DWORD> dwArray;
    //CMemFile memFile;
   //CArchive ar(&memFile, CArchive::store);
    while(events.m_iCurrentNote < events.m_msaNotesPosition.GetEventCount())
    {
      
        dwArray.remove_all();
      events.GetNoteTokens(events.m_iCurrentNote, dwArray);
      if(dwArray.GetEventCount() > 0)
        {
         events.m_iCurrentToken = dwArray.get_at(0);
//      else
//         events.m_iCurrentToken = -1;
            lvaPending.add(events);
            tkPosition = events.m_tkaNotesPosition.element_at(events.m_iCurrentNote);
            if(tkLastPosition != tkPosition)
            {

                event.SetFlags(1); // Flag 1 means POSITIONCB
                event.SetDelta(tkPosition - tkLastPosition);
                CMemFile memFile;
               CArchive ar(&memFile, CArchive::store);
                ar << EVENT_ID_LYRIC_V1;
               lvaPending.Serialize(ar);
               ar.Flush();

               lvaPending.Serialize(ar);
               ar.Flush();
                DWORD dwLength = memFile.get_length();
    //            LPBYTE lpData = memFile.Detach();
                memFile.seek_to_begin();
                event.SetParam(memFile);
                m_trackWorkStorage.m_events.add(event);
                lvaPending.remove_all();
            }
            
        }
        tkLastPosition = tkPosition;
        events.m_iCurrentNote++;
    }
    return VMSR_SUCCESS;
}*/
