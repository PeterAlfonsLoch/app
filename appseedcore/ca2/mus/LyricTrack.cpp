#include "StdAfx.h"

MidiLyricTrack::MidiLyricTrack(::ca::application * papp) :
   ca(papp),
   MidiTrackBase(papp)
{
   m_pfile = NULL;
   m_iDelay = 0;
}

MidiLyricTrack::MidiLyricTrack(::mus::midi::file * pfile) :
   ca(pfile->get_app()),
   MidiTrackBase(pfile->get_app())
{
   m_pfile = pfile;
   m_iDelay = 0;
}

MidiLyricTrack::MidiLyricTrack(const MidiLyricTrack & track) :
   ca(track.get_app()),
   MidiTrackBase(track.get_app())
{
   operator = (track);
}

MidiLyricTrack::~MidiLyricTrack()
{

}

::mus::midi::e_file_result MidiLyricTrack::GetPosition(imedia::position & tkPositionParam, imedia::position tkMax)
{
   if(m_iCurrentEvent >= m_trackWorkStorage.GetEventCount())
   {
      return ::mus::midi::SEndOfTrack;
   }
   //    MidiEventV008 & event = m_trackWorkStorage.EventAt(m_iCurrentEvent);

   imedia::position tkPosition = -1;
   if(m_iCurrentEvent == m_iLastEvent &&
      m_iDelay == m_iLastDelay)
   {
      tkPosition = m_tkLastPosition;
   }
   else
   {
      /*tkPosition = m_tkPosition + event.GetDelta();
      int iMsPosition  = m_pfile->TicksToMillisecs(tkPosition);
      iMsPosition += m_iDelay;
      tkPosition = m_pfile->MillisecsToTicks(iMsPosition);
      m_iLastEvent = m_iCurrentEvent;
      m_iLastDelay = m_iDelay;
      m_tkLastPosition = tkPosition;*/
      tkPosition = ApplyDelay(m_tkPosition);
      m_iLastEvent = m_iCurrentEvent;
      m_iLastDelay = m_iDelay;
      m_tkLastPosition = tkPosition;
   }

   if(tkPosition > tkMax)
   {
      return ::mus::midi::SReachedTkMax;
   }
   tkPositionParam = tkPosition;
   return ::mus::midi::Success;
}

::mus::midi::file_flags & MidiLyricTrack::GetFlags()
{
   return m_flagsFile;
}

const ::mus::midi::file_flags & MidiLyricTrack::GetFlags() const
{
   return m_flagsFile;
}

::mus::midi::e_file_result MidiLyricTrack::GetEvent(MidiEventBase *& pevent, imedia::position tkMax, BOOL bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(tkMax);
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
   if(m_iCurrentEvent > m_trackWorkStorage.GetEventCount())
   {
      return ::mus::midi::SEndOfTrack;
   }
   if(m_tkPosition > tkMax)
   {
      return ::mus::midi::SReachedTkMax;
   }
   pevent = &m_trackWorkStorage.EventAt(m_iCurrentEvent);
   return ::mus::midi::Success;
}

::mus::midi::e_file_result MidiLyricTrack::GetEvent(
   MidiEventV001 *& pevent,
   imedia::position   tkMax,
   BOOL   bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
   if(m_iCurrentEvent > m_trackWorkStorage.GetEventCount())
   {
      return ::mus::midi::SEndOfTrack;
   }
   if(m_tkPosition > tkMax)
   {
      return ::mus::midi::SReachedTkMax;
   }
   MidiEventV008 & event = m_trackWorkStorage.EventAt(m_iCurrentEvent);
   m_eventv001 = event;
   pevent = &m_eventv001;
   return ::mus::midi::Success;
}

imedia::position MidiLyricTrack::GetPosition()
{
   return ApplyDelay(m_tkPosition);
}

::mus::midi::e_file_result MidiLyricTrack::seek_begin()
{
   m_iCurrentEvent      = -1;
   m_tkPosition         = 0;
   m_tkLastPosition     = 0;
   m_iLastEvent         = -1;
   GetFlags().unsignalize_all();
   return MoveNext();
}

::mus::midi::e_file_result MidiLyricTrack::seek_end()
{
   m_iCurrentEvent = m_trackWorkStorage.GetEventCount();
   m_tkPosition = m_trackWorkStorage.EventAt(m_trackWorkStorage.GetEventCount() - 1).GetPosition();
   GetFlags().signalize(::mus::midi::EndOfFile);
   m_tkLastPosition = m_trackWorkStorage.EventAt(m_trackWorkStorage.GetEventCount() - 2).GetPosition();
   m_iLastEvent = m_trackWorkStorage.GetEventCount() - 2;
   return ::mus::midi::Success;
}


VMSRESULT MidiLyricTrack::Prepare(::ca::application * papp, LyricEventsV1 & events)
{
   gen::memory_file       memFile(papp);
   MidiEventV008    event;
   imedia::position             tkPosition;
   imedia::position             tkLastPosition = 0;
   base_array < LyricEventV1, LyricEventV1 &> lvaPending;

   events.m_iCurrentToken = 0;


   TRACE("\n");
   TRACE("\n");
   m_trackWorkStorage.remove_all();
   while(events.m_iCurrentToken < events.m_tkaTokensPosition.get_size())
   {
      lvaPending.add(events);
      tkPosition = events.m_tkaTokensPosition.element_at(events.m_iCurrentToken);
      TRACE("MidiLyricTrack::Prepare V1 tkPosition %d", tkPosition);
      if(tkPosition >= tkLastPosition)
      {
         event._SetFlags(1); // Flag 1 means POSITIONCB
         event._SetDelta(tkPosition - tkLastPosition);
         event._SetPosition(tkPosition);
         TRACE(" Delta %d", event._GetDelta());
         TRACE(" Token %d", events.m_iCurrentToken);

         //         TRACE(" msPosition %d", events.m_msaNotesPosition.element_at(events.m_iCurrentNote));

         memFile.clear();
         /*xxx         CArchive ar(&memFile, CArchive::store);
         ar << EVENT_ID_LYRIC_V1;
         lvaPending.Serialize(ar);
         ar.Flush();
         DWORD dwLength = memFile.get_length();
         LPBYTE lpData = memFile.GetAllocation();
         event.SetParam(lpData, dwLength);
         //memFile.Attach(lpData, dwLength);
         lvaPending.remove_all();
         m_trackWorkStorage.add(event);
         tkLastPosition = tkPosition;*/
      }
      TRACE("\n");
      events.m_iCurrentToken++;
   }

   return VMSR_SUCCESS;
}

VMSRESULT MidiLyricTrack::Prepare(::ca::application * papp, LyricEventsV2 & events)
{
   gen::memory_file       memFile(papp);
   MidiEventV008    event;
   imedia::position             tkPosition;
   imedia::position             tkLastPosition = 0;
   base_array < LyricEventV1, LyricEventV1 &> lvaPending;
   unique_int_sort_array ia;

   events.m_iCurrentToken = 0;
   events.m_iCurrentNote = 0;
   m_trackWorkStorage.remove_all();



   TRACE("\n");
   TRACE("\n");
   while(events.m_iCurrentNote < events.m_msaNotesPosition.get_size())
   {
      ia.remove_all();
      ia  = events.GetNoteTokenArray(events.m_iCurrentNote);
      if(ia.get_size() > 0)
      {
         events.m_iCurrentToken = ia.get_at(0);
         lvaPending.add(events);
         tkPosition = events.m_tkaNotesPosition.element_at(events.m_iCurrentNote);
         TRACE("MidiLyricTrack::Prepare V2 tkPosition %d", tkPosition);
         if(tkPosition >= tkLastPosition)
         {
            event._SetFlags(1); // Flag 1 means POSITIONCB
            ASSERT(tkPosition >= tkLastPosition);
            event._SetDelta(tkPosition - tkLastPosition);
            event._SetPosition(tkPosition);
            TRACE(" Delta %d", event._GetDelta());
            TRACE(" Token %d", events.m_iCurrentToken);
            TRACE(" Note %d", events.m_iCurrentNote);
            //            TRACE(" msPosition %d", events.m_msaNotesPosition.element_at(events.m_iCurrentNote));

            memFile.clear();
            /*xxxx            CArchive ar(&memFile, CArchive::store);
            ar << EVENT_ID_LYRIC_V1;
            lvaPending.Serialize(ar);
            ar.Flush();

            DWORD dwLength = memFile.get_length();
            memFile.seek_to_begin();
            event.SetParam(memFile);
            m_trackWorkStorage.add(event);
            lvaPending.remove_all();
            tkLastPosition = tkPosition;*/
         }
         TRACE("\n");
      }
      events.m_iCurrentNote++;
   }
   return VMSR_SUCCESS;
}

::mus::midi::e_file_result MidiLyricTrack::MoveNext()
{
   m_iCurrentEvent++;
   if(m_iCurrentEvent >= m_trackWorkStorage.GetEventCount())
   {
      return ::mus::midi::SEndOfTrack;
   }

   m_tkPosition += m_trackWorkStorage.EventAt(m_iCurrentEvent)._GetDelta();
   //TRACE("MidiLyricTrack::MoveNext iEvent %d position %d Next %d\n",
   //   m_iCurrentEvent, m_tkPosition, m_tkNextPosition);
   return ::mus::midi::Success;

}

MidiLyricTrack & MidiLyricTrack::operator =(const MidiLyricTrack &track)
{
   m_iCurrentEvent = track.m_iCurrentEvent;
   m_iDelay = track.m_iDelay;
   GetFlags() = track.GetFlags();
   m_iLastDelay = track.m_iLastDelay;
   m_iLastEvent = track.m_iLastEvent;
   m_pfile = track.m_pfile;
   m_tkLastPosition = track.m_tkLastPosition;
   m_tkPosition = track.m_tkPosition;
   m_trackWorkStorage = track.m_trackWorkStorage;
   return * this;


}

imedia::position MidiLyricTrack::WorkGetPosition()
{
   imedia::position tkPosition = 0x7fffffff;
   GetPosition(tkPosition, 0x7fffffff);
   return tkPosition;
}

::mus::midi::e_file_result MidiLyricTrack::WorkMoveNext()
{
   return MoveNext();
}

void MidiLyricTrack::WorkGetEvent(
   MidiEventBase *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   WorkGetEvent((MidiEventV008 *&) pevent, tkMax, bTkMaxInclusive);
}

void MidiLyricTrack::WorkGetEvent(
   MidiEventV008 *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
   if(m_iCurrentEvent > m_trackWorkStorage.GetEventCount())
   {
      return;
   }
   if(m_tkPosition > tkMax)
   {
      return;
   }
   MidiEventV008 & event = m_trackWorkStorage.EventAt(m_iCurrentEvent);
   pevent = &event;
}


::mus::midi::e_file_result MidiLyricTrack::WorkSeekBegin()
{
   return seek_begin();
}

::mus::midi::e_file_result MidiLyricTrack::WorkSeekEnd()
{
   return seek_end();
}

MidiTrackBase::e_type MidiLyricTrack::get_type()
{
   return TypeLyric;
}

bool MidiLyricTrack::WorkIsEOT()
{
   return m_iCurrentEvent >= m_trackWorkStorage.GetEventCount();
}


imedia::position MidiLyricTrack::ApplyDelay(imedia::position tkPosition)
{
   return m_pfile->MillisecsToTicks(
      m_pfile->TicksToMillisecs(tkPosition)
      + m_iDelay);
}

void MidiLyricTrack::SetDelay(int iMillis)
{
   m_iDelay = iMillis;
}
