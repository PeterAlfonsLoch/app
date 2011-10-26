#include "StdAfx.h"

midi_track::midi_track(::ca::application * papp) :
   ca(papp),
   midi_track_base(papp),
   primitive::memory_container (papp)
{
   m_bWorkTrackEnd = false;
   m_ptracks = NULL;

   m_idxTrack = 0;

   m_tkPosition = 0;
   m_cbLeft = 0;
   m_hpbImage = NULL;


   m_smti.m_tkLength = 0;
   m_smti.m_cbLength = 0;

   m_estate = StateOnDelta;

   m_bAutoAllocation = false;

   m_tkDelta = 0;

   keep_pointer((void **) &m_hpbImage);
   keep_pointer((void **) &m_hpbEventImage);

}

midi_track::midi_track(const midi_track & track) :
   ca(track.get_app()),
   midi_track_base(track.get_app()),
   primitive::memory_container (track)
{
   operator =(track);
}

midi_track::~midi_track()
{
   m_hpbImage = NULL;
}

void midi_track::Initialize(midi_tracks * pTracks)
{
    m_ptracks = pTracks;
}

#ifdef _DEBUG

void midi_track::dump(dump_context & dumpcontext) const
{
   dumpcontext << "\n";
   dumpcontext << "midi_track";
   dumpcontext << "\n";
   imedia::position tk = 0;
   for(int i = 0; i < m_trackWorkStorage.GetEventCount(); i++)
   {
      midi_event_v008 & event = const_cast < midi_track_v008 & > (m_trackWorkStorage).EventAt(i);
      dumpcontext << "delta " << event._GetDelta();
      dumpcontext << "type " << event.GetFullType();

      tk = tk + imedia::position(event._GetDelta());

      dumpcontext << "\n";
   }

}

#endif


////////////////////////////////////////////////////////////////////////////
//
// smfGetVDword
//
// Reads a var length DWORD from the given file.
//
// hpbImage                  - Pointer to the first byte of the VDWORD.
//
// dwLeft                    - Bytes left in image
//
// pDw                       - Pointer to a DWORD to store the result in.
//                             track.
//
// Returns the number of bytes consumed from the stream.
//
// A var length DWORD stored in a MIDI file contains one or more
// bytes. Each byte except the last has the high bit set; only the
// low 7 bits are significant.
//
////////////////////////////////////////////////////////////////////////////
DWORD midi_track::GetVDWord(
   DWORD * pDw)
{
   return GetVDWord(m_cbLeft, pDw);
}

DWORD midi_track::GetVDWord(
   DWORD dwLeft,
   DWORD * pDw)
{
    BYTE                    b;
    DWORD                   dwUsed  = 0;
   byte *               hpbImage = m_hpbImage;

    ASSERT(hpbImage != NULL);
    ASSERT(pDw != NULL);

    *pDw = 0;

    do
    {
        if (!dwLeft)
        {
            return 0;
        }

        b = *hpbImage++;
        dwLeft--;
        dwUsed++;

        *pDw = (*pDw << 7) | (b & 0x7F);
    } while (b&0x80);

    return dwUsed;
}

DWORD midi_track::SetVDWord(
   DWORD dwLeft,
   DWORD dw)
{
   DWORD       dwUsed  = 0;
   byte *      hpbImage = m_hpbImage;
   DWORD         dwBuffer;

   ASSERT(!m_bAutoAllocation);
   ASSERT(hpbImage != NULL);
   ASSERT(dw <= 0x0fffffff);

   if(!dwLeft)
      return 0;
   dwBuffer = dw & 0x7f;
   dwLeft--;
   dwUsed++;
   while ((dw >>= 7) > 0)
   {
      if(!dwLeft)
         return 0;
      dwBuffer <<= 8;
      dwBuffer |= 0x80;
      dwBuffer |= (dw & 0x7f);
      dwLeft--;
      dwUsed++;
   }
   while (TRUE)
   {
      *hpbImage++ = (BYTE) dwBuffer;
      if (dwBuffer & 0x80)
         dwBuffer >>= 8;
      else
         break;
   }

   return dwUsed;
}


DWORD midi_track::SetVDWord(
   DWORD dw)
{
   DWORD                   dwUsed  = 0;
   DWORD               dwBuffer;

   ASSERT(m_bAutoAllocation);
   ASSERT(dw <= 0x0fffffff);


   dwBuffer = dw & 0x7f;
   dwUsed++;
   while ((dw >>= 7) > 0)
   {
      dwBuffer <<= 8;
      dwBuffer |= 0x80;
      dwBuffer |= (dw & 0x7f);
      dwUsed++;
   }
   try
   {
      allocate_add_up(dwUsed);
   }
   catch(memory_exception * pe)
   {
      pe->Delete();
      return 0;
   }

   byte *   hpbImage = m_hpbImage;
   while (TRUE)
   {
      *hpbImage++ = (BYTE) (dwBuffer & 0xff);
      if (dwBuffer & 0x80)
         dwBuffer >>= 8;
      else
         break;
   }

   return dwUsed;
}

//#ifdef _UNICODE
         /*string *pStr;
           int result;
         int bufferSize = 1;
         //LPTSTR wideCharStr = (LPTSTR) malloc(1 * sizeof(char));
         LPTSTR wideCharStr = new char;
         result = MultiByteToWideChar(
         CP_ACP,         // code page
         MB_COMPOSITE,         // character-type options
         (const char *) m_event.hpbParm, // address of string to ::collection::map
         m_event.cbParm,      // number of bytes in string
         wideCharStr,  // address of wide-character buffer
         bufferSize       // size of buffer
         );
         if(result)
         {
            pStr = new string(wideCharStr, result);
            delete wideCharStr;
         }
         else
         {
         bufferSize = MultiByteToWideChar(
         CP_ACP,         // code page
         MB_COMPOSITE,         // character-type options
         (const char *) m_event.hpbParm, // address of string to ::collection::map
         m_event.cbParm,      // number of bytes in string
         wideCharStr,  // address of wide-character buffer
         0       // size of buffer
         );
         //wideCharStr = (LPTSTR) malloc(bufferSize * sizeof(char));

         wideCharStr = new char[bufferSize];
         result = MultiByteToWideChar(
         CP_ACP,         // code page
         MB_COMPOSITE,         // character-type options
         (const char *) m_event.hpbParm, // address of string to ::collection::map
         m_event.cbParm,      // number of bytes in string
         wideCharStr,  // address of wide-character buffer
         bufferSize       // size of buffer
         );
            pStr = new string(wideCharStr, result);
         delete wideCharStr;
         }*/




::mus::midi::e_file_result midi_track::ReadDelta()
{
   imedia::position tkDelta;

   switch(m_estate)
   {
   case StateOnDelta:
      {

         m_hpbEventImage = m_hpbImage;

         if (!(m_dwUsed = GetVDWord((DWORD *) &tkDelta)))
         {
            TRACE("Hit end of track w/o end marker!\n");
            return ::mus::midi::EInvalidFile;
         }

         if(tkDelta > 1000000)
         {
            m_tkDelta = tkDelta;
         }
         else
         {
            m_tkDelta = tkDelta;
         }
         m_hpbImage += m_dwUsed;
         m_cbLeft -= m_dwUsed;
         m_estate = StateOnEvent;

         return ::mus::midi::Success;
      }
   case StateOnEvent:
      {
         return ::mus::midi::Success;
      }
   case StateOnEventRead:
      {
         return ::mus::midi::Success;
      }
   }
   ASSERT(FALSE);
   return ::mus::midi::EFail;



}

::mus::midi::e_file_result midi_track::GetEvent(
   midi_event_base *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   ::mus::midi::e_file_result  mfr;
   if(::mus::midi::Success != (mfr = ReadEvent(tkMax, bTkMaxInclusive)))
   {
      return mfr;
   }
   pevent = &m_event;
   return ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::GetEvent(
   midi_event_v001 *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   ::mus::midi::e_file_result  mfr;
   if(::mus::midi::Success != (mfr = ReadEvent(tkMax, bTkMaxInclusive)))
   {
      return mfr;
   }
   pevent = &m_event;
   return ::mus::midi::Success;
}



/******************************************************************************
*
* smfGetNextEvent
*
* read the next m_event from the given file.
*
* pSmf                      - File to read the m_event from.
*
* pEvent                    - Pointer to an m_event structure which will receive
*                             basic information about the m_event.
*
* tkMax                     - Tick destination. An attempt to read past this
*                             position in the file will fail.
*
* Returns
*   ::mus::midi::Success The events were successfully read.
*   ::mus::midi::SEndOfFile There are no more events to read in this track.
*   ::mus::midi::SReachedTkMax No m_event was read because <p tkMax> was reached.
*   ::mus::midi::EInvalidFile A disk or parse error occured on the file.
*
* This is the lowest level of parsing for a raw MIDI stream. The basic
* information about one m_event in the file will be returned in pEvent.
*
* Merging data from all tracks into one stream is performed here.
*
* m_event.tkDelta will contain the tick delta for the m_event.
*
* m_event.abEvent will contain a description of the m_event.
*  m_event.abEvent[0] will contain
*    F0 or F7 for a System Exclusive message.
*    FF for a MIDI file meta m_event.
*    The status byte of any other MIDI message. (Running status will
*    be tracked and expanded).
*
* m_event.cbParm will contain the number of bytes of paramter data
*   which is still in the file behind the m_event header already read.
*   This data may be read with <f smfGetTrackEventData>. Any unread
*   data will be skipped on the next call to <f smfGetNextTrackEvent>.
*
* Channel messages (0x8? - 0xE?) will always be returned fully in
*   m_event.abEvent.
*
*  Meta events will contain the meta type in m_event.abEvent[1].
*
*  System exclusive events will contain only an 0xF0 or 0xF7 in
*    m_event.abEvent[0].
*
*  The following fields in pTrk are used to maintain state and must
*  be updated if a seek-in-track is performed:
*
*  bRunningStatus contains the last running status message or 0 if
*   there is no valid running status.
*
*  hpbImage is a pointer into the file image of the first byte of
*   the m_event to follow the m_event just read.
*
*  dwLeft contains the number of bytes from hpbImage to the end
*   of the track.
*
*
* get the next due m_event from all (in-use?) tracks
*
* For all tracks
*  If not end-of-track
*   decode m_event delta time without advancing through buffer
*   event_absolute_time = track_tick_time + track_event_delta_time
*   relative_time = event_absolute_time - last_stream_time
*   if relative_time is lowest so far
*    save this track as the next to pull from, along with times
*
* If we found a track with a due m_event
*  Advance track pointer past m_event, saving ptr to parm data if needed
*  track_tick_time += track_event_delta_time
*  last_stream_time = track_tick_time
* Else
*  Mark and return end_of_file
*
*****************************************************************************/
::mus::midi::e_file_result midi_track::ReadEvent(
   imedia::position   tkMax,
   BOOL   bTkMaxInclusive)
{
   BYTE                    bEvent;
   DWORD                   dwGotTotal;
   DWORD                   dwGot;
   DWORD                   cbEvent;
   ::mus::midi::e_file_result      mfr;
   byte *                  hpbImage;

   if(m_estate == StateOnDelta)
   {
      mfr = ReadDelta();
      if(::mus::midi::Success != mfr)
      {
         _GetFlags().signalize(::mus::midi::EndOfTrack);
         return ::mus::midi::SEndOfTrack;
      }
   }


   // Probably you have forgotten to call MoveNext
   ASSERT(m_estate == StateOnEvent);

   m_event.clear();

   // We MUST have at least three bytes here (cause we haven't hit
   // the end-of-track meta yet, which is three bytes long). Checking
   // against three means we don't have to check how much is left
   // in the track again for any short m_event, which is most cases.

   if(m_cbLeft < 3)
   {
      //Attention
      return ::mus::midi::EInvalidFile;
   }


   m_tkPosition += m_tkDelta;

   m_event.SetPosition(m_tkPosition);
   m_event.SetDelta(m_tkDelta);

   if(bTkMaxInclusive)
   {
      if(m_tkPosition > tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }
   else
   {
      if(m_tkPosition >= tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }

   hpbImage = m_hpbImage;

   bEvent = *hpbImage++;

   if (bEvent < ::mus::midi::Msg)
   {
      if(0 == m_ptracks->m_uchRunningStatus)
      {
         //Attention
         return ::mus::midi::EInvalidFile;
      }

      dwGotTotal = 1;
      m_event.SetFullType(m_ptracks->m_uchRunningStatus);
      m_event.SetChB1(bEvent);
      if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
      {
         m_event.SetChB2(*hpbImage++);
         dwGotTotal++;
      }
   }
   else if (::mus::midi::SysEx > bEvent)
   {
      m_ptracks->m_uchRunningStatus = bEvent;

      dwGotTotal = 2;
      m_event.SetFullType(bEvent);
      m_event.SetChB1(*hpbImage++);
      if(3 == ::mus::midi::GetMessageLen(bEvent))
      {
         m_event.SetChB2(*hpbImage++);
         dwGotTotal++;
      }
   }
   else
   {
      if(::mus::midi::Meta == bEvent)
      {
         m_event.SetFullType(::mus::midi::Meta);
         m_event.SetChB1(*hpbImage++);
         if(::mus::midi::MetaEOT == m_event.GetChB1())
         {
            _GetFlags().signalize(::mus::midi::EndOfTrack);
            m_smti.m_tkLength = m_tkPosition;
         }
         dwGotTotal = 2;
      }
      else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
      {
         m_event.SetFullType(bEvent);
         dwGotTotal = 1;
      }
      else
      {
         //Attention
         ASSERT(FALSE);
         return ::mus::midi::EInvalidFile;
      }
      if(0 == (dwGot = ::mus::midi::GetVDWord(hpbImage, m_cbLeft - 2, cbEvent)))
      {
         //Attention
         ASSERT(FALSE);
         return ::mus::midi::EInvalidFile;
      }

      //hpbImage  += dwGot;
      dwGotTotal  += dwGot;

      if(dwGotTotal + cbEvent > m_cbLeft)
      {
         //Attention
         ASSERT(FALSE);
         return ::mus::midi::EInvalidFile;
      }

      m_event.SetParam(hpbImage, cbEvent);

      hpbImage += cbEvent;
      dwGotTotal += cbEvent;
   }

   ASSERT(m_cbLeft >= dwGotTotal);

   m_hpbImage = hpbImage ;
   m_cbLeft -= dwGotTotal;
   m_dwUsed = dwGotTotal;
   m_estate = StateOnEventRead;

   //m_event.m_cbImage = hpbImage - m_hpbEventImage;


   return ::mus::midi::Success;
}

VMSRESULT midi_track::ReadEvent(midi_event_v008 &midiEvent)
{
   BYTE                       bEvent;
   int                        iGotTotal;
   DWORD                      dwGot;
   DWORD                      cbEvent;
   ::mus::midi::e_file_result        smfrc;

   if(m_estate == StateOnDelta)
   {
      smfrc = ReadDelta();
      if(::mus::midi::Success != smfrc)
      {
         _GetFlags().signalize(::mus::midi::EndOfTrack);
         return ::mus::midi::SEndOfTrack;
      }
   }
   else if(m_estate == StateOnEventRead)
   {
      return ::mus::midi::Success;
   }

   // Probably you have forgotten to call MoveNext
   ASSERT(m_estate == StateOnEvent);

   midiEvent.clear();
   midiEvent._SetDelta(m_tkDelta);
   m_tkPosition += m_tkDelta;
   midiEvent.SetPosition(m_tkPosition);
   if (m_cbLeft < 3)
   {
      return VMSR_E_INVALIDFILE;
   }
   bEvent = *m_hpbImage++;
   if (::mus::midi::Msg > bEvent)
   {
      iGotTotal = 1;
      midiEvent._SetFullType(m_ptracks->m_uchRunningStatus);
      midiEvent._SetChB1(bEvent);
      if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
      {
         midiEvent._SetChB2(*m_hpbImage++);
         iGotTotal++;
      }
   }
   else if (::mus::midi::SysEx > bEvent)
   {
      m_ptracks->m_uchRunningStatus = bEvent;
      iGotTotal = 2;
      midiEvent._SetFullType(bEvent);
      midiEvent._SetChB1(*m_hpbImage++);
      if (3 == ::mus::midi::GetMessageLen(bEvent))
      {
         midiEvent._SetChB2(*m_hpbImage++);
         iGotTotal++;
      }
   }
   else
   {
      if (::mus::midi::Meta == bEvent)
      {
         midiEvent._SetFullType(::mus::midi::Meta);
         midiEvent.SetMetaType(*m_hpbImage++);
         if (::mus::midi::MetaEOT == midiEvent.GetMetaType())
         {
            _GetFlags().signalize(::mus::midi::EndOfTrack);
            m_smti.m_tkLength = m_tkPosition;
         }
         iGotTotal = 2;
      }
      else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
      {
         midiEvent._SetFullType(bEvent);
         iGotTotal = 1;
      }
      else
      {
         return VMSR_E_INVALIDFILE;
      }

      if (0 == (dwGot = midi_event_base::GetVDWord(m_hpbImage, m_cbLeft - iGotTotal, &cbEvent)))
      {
         return VMSR_E_INVALIDFILE;
      }

      m_hpbImage  += dwGot;
      iGotTotal  += dwGot;

      if (iGotTotal + (int) cbEvent > (int) m_cbLeft)
      {
         return VMSR_E_INVALIDFILE;
      }

      midiEvent.WriteParam(m_hpbImage, cbEvent);

      m_hpbImage += cbEvent;
      iGotTotal += cbEvent;
   }

   ASSERT(m_cbLeft >= (DWORD) iGotTotal);

   m_cbLeft -= iGotTotal;
   m_dwUsed = iGotTotal;
   m_estate = StateOnEventRead;
   m_iCurrentEvent++;

   return VMSR_SUCCESS;
}

VMSRESULT midi_track::ReadEvent(midi_event_v001 &midiEvent)
{
   BYTE                       bEvent;
   int                        iGotTotal;
   DWORD                      dwGot;
   DWORD                      cbEvent;
   ::mus::midi::e_file_result        smfrc;

   if(m_estate == StateOnDelta)
   {
      smfrc = ReadDelta();
      if(::mus::midi::Success != smfrc)
      {
         _GetFlags().signalize(::mus::midi::EndOfTrack);
         return ::mus::midi::SEndOfTrack;
      }
   }
   else if(m_estate == StateOnEventRead)
   {
      return ::mus::midi::Success;
   }

   // Probably you have forgotten to call MoveNext
   ASSERT(m_estate == StateOnEvent);


   midiEvent.clear();
   midiEvent._SetDelta(m_tkDelta);
   m_tkPosition += m_tkDelta;
   midiEvent.SetPosition(m_tkPosition);
   if (m_cbLeft < 1)
   {
      return VMSR_E_INVALIDFILE;
   }
   midiEvent._SetImage(m_hpbImage);
   bEvent = *m_hpbImage++;
   if (bEvent < ::mus::midi::Msg)
   {
      //ASSERT(m_ptracks->m_uchRunningStatus >= ::mus::midi::Msg);
      iGotTotal = 1;
      midiEvent._SetFullType(m_ptracks->m_uchRunningStatus);
      midiEvent._SetChB1(bEvent);
      if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
      {
         if (m_cbLeft < 2)
         {
            return VMSR_E_INVALIDFILE;
         }
         midiEvent._SetChB2(*m_hpbImage++);
         iGotTotal++;
      }
   }
   else if (::mus::midi::SysEx > bEvent)
   {
      if (m_cbLeft < 2)
      {
         return VMSR_E_INVALIDFILE;
      }
      m_ptracks->m_uchRunningStatus = bEvent;
      iGotTotal = 2;
      midiEvent._SetFullType(bEvent);
      midiEvent._SetChB1(*m_hpbImage++);
      if (3 == ::mus::midi::GetMessageLen(bEvent))
      {
         if (m_cbLeft < 3)
         {
            return VMSR_E_INVALIDFILE;
         }
         midiEvent._SetChB2(*m_hpbImage++);
         iGotTotal++;
      }
   }
   else
   {
      if (::mus::midi::Meta == bEvent)
      {
         if (m_cbLeft < 2)
         {
            return VMSR_E_INVALIDFILE;
         }
         midiEvent._SetFullType(::mus::midi::Meta);
         midiEvent._SetMetaType(*m_hpbImage++);
         if (::mus::midi::MetaEOT == midiEvent.GetMetaType())
         {
            _GetFlags().signalize(::mus::midi::EndOfTrack);
            m_smti.m_tkLength = m_tkPosition;
         }
         iGotTotal = 2;
      }
      else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
      {
         midiEvent._SetFullType(bEvent);
         iGotTotal = 1;
      }
      else
      {
         return VMSR_E_INVALIDFILE;
      }

      dwGot = midi_event_base::GetVDWord(m_hpbImage, m_cbLeft - iGotTotal, &cbEvent);

      m_hpbImage  += dwGot;
      iGotTotal  += dwGot;

      if (iGotTotal + (int) cbEvent > (int) m_cbLeft)
      {
         return VMSR_E_INVALIDFILE;
      }

      midiEvent._SetParam(m_hpbImage, cbEvent);

      m_hpbImage += cbEvent;
      iGotTotal += cbEvent;
   }

   ASSERT(m_cbLeft >= (DWORD) iGotTotal);

   m_cbLeft -= iGotTotal;
   m_dwUsed = iGotTotal;
   m_estate = StateOnEventRead;

   midiEvent._SetImageSize(iGotTotal);

   /*TRACE("%04d ", midiEvent.GetDelta());

   switch(midiEvent.get_type())
   {
   case ::mus::midi::NoteOff:
      TRACE("%02d ", midiEvent.GetTrack());
      TRACE("NoteOff %d %d", midiEvent.GetChB1(), midiEvent.GetChB2());
      break;
   case ::mus::midi::NoteOn:
      TRACE("%02d ", midiEvent.GetTrack());
      TRACE("NoteOn %d %d", midiEvent.GetChB1(), midiEvent.GetChB2());
      break;
   }
   TRACE("\n");
   */

   return VMSR_SUCCESS;
}




::mus::midi::e_file_result midi_track::GetNextXFInfoHeader(XFInfoHeader * pXfih)
{
   ASSERT(pXfih != NULL);
   ::mus::midi::e_file_result smfrc;
   if(::mus::midi::Success == (smfrc = seek(::mus::midi::SeekXFInfoHeader)))
   {
      string_tokenizer strtokenizer;
      gen::international::MultiByteToMultiByte(CP_UTF8, strtokenizer, gen::international::CodePageLatin1, (const char *) m_event.GetParam(), m_event.GetParamSize());
      pXfih->FromData(strtokenizer);
      string str;
      TRACE("****GetXFInfoHeader");
      TRACE("Date: %s\n", pXfih->m_strDate);
      TRACE("Country: %s\n", pXfih->m_strCountry);
      TRACE("Category: %s\n", pXfih->m_strCategory);
      TRACE("Beat: %s\n", pXfih->m_strBeat);

      pXfih->m_straComposer.get_format_string(str, "/");
      TRACE("Composer: %s\n", str);

      pXfih->m_straLyricist.get_format_string(str, "/");
      TRACE("Lyricist: %s\n", str);

      pXfih->m_straArranger.get_format_string(str, "/");
      TRACE("Arranger: %s\n", str);

      pXfih->m_straPerformer.get_format_string(str,"/");
      TRACE("Performer: %s\n", str);

      TRACE("ID: %s\n", pXfih->m_id);
      return ::mus::midi::Success;
   }
   return smfrc;
}

::mus::midi::e_file_result midi_track::GetNextXFInfoHeaderLS(XFInfoHeaderLS * pXfihls)
{
   ASSERT(pXfihls != NULL);
   ::mus::midi::e_file_result smfrc;
   if(::mus::midi::Success == (smfrc = seek(::mus::midi::SeekXFInfoHeaderLS)))
   {
      string_tokenizer str;
      gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
      pXfihls->FromData(str);
      return ::mus::midi::Success;
   }
   return smfrc;
}

::mus::midi::e_file_result midi_track::GetNextXFInfoHeaderLS(XFInfoHeaderLS * pXfihls, const string &strLanguage)
{
   XFInfoHeaderLS xfihls;
   while(::mus::midi::Success == GetNextXFInfoHeaderLS(&xfihls))
   {
      if(xfihls.m_strLanguage.CompareNoCase(strLanguage) == 0)
      {
         *pXfihls = xfihls;
         return ::mus::midi::Success;
      }
   }
   return ::mus::midi::SEndOfFile;
}

::mus::midi::e_file_result midi_track::GetNextXFSongName(string &str)
{
   //LPTSTR pSongName = NULL;
   ::mus::midi::e_file_result smfrc;
   if(::mus::midi::Success == (smfrc = seek(::mus::midi::SeekXFSongName)))
   {
   //   string str;

      gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
   //   pSongName = _tcsdup(str);
   //   TRACE("Song Name: %s\n", pSongName);
      return ::mus::midi::Success;
   }
   return smfrc;
}



::mus::midi::e_file_result midi_track::ReadXFInfoHeader_(
   LPTSTR *ppSongName,
    XFInfoHeader **ppXfih,
    XFInfoHeaderLS **ppXfihls)
{
   ASSERT(*ppSongName == NULL);
   ASSERT(*ppXfih == NULL);
   ASSERT(*ppXfihls == NULL);

//    PSMF                    pSmf = (PSMF)hSmf;
   ::mus::midi::e_file_result               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;
   BOOL               okSongName = FALSE;
   BOOL               okInfoHeader = FALSE;
   BOOL               okInfoHeaderLS = FALSE;

   *ppXfih = NULL;
   *ppXfihls = NULL;
   *ppSongName = NULL;

   if(m_tkPosition != 0)
   {
      return   ::mus::midi::EInvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
    if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
    {
        return ::mus::midi::SEndOfFile;
    }

    while(TRUE)
    {
      if(okSongName &&
         okInfoHeader &&
         okInfoHeaderLS)
         break;
        smfrc = ReadEvent(0, TRUE);
        if (::mus::midi::Success != smfrc)
        {
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-file.
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            _GetFlags().signalize(::mus::midi::EndOfFile);
            }

            TRACE( "smfReadEvents: ReadXFInfoHeader_() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_event.GetFullType()) &&
          (::mus::xf::MetaSongName == m_event.GetMetaType()))
        {
         string str;
         gen::international::MultiByteToOEM(
            gen::international::CodePageLatin1,
            str,
            (const char *) m_event.GetParam(), m_event.GetParamSize());
         *ppSongName = _tcsdup(str);
         TRACE("Song Name: %s\n", *ppSongName);
         okSongName = TRUE;
        }
      else if ((::mus::midi::Meta == m_event.GetFullType()) &&
          (::mus::xf::MetaXFInfoHdr == m_event.GetMetaType()))
        {
         string_tokenizer wstrtokenizer;
         gen::international::multibyte_to_utf8(
            gen::international::CodePageLatin1,
            wstrtokenizer,
            (const char *) m_event.GetParam(),
            m_event.GetParamSize());
         if(wstrtokenizer.Mid(0, 4).Compare("XFhd") == 0)
         {
            *ppXfih = new XFInfoHeader();
            (*ppXfih)->FromData(wstrtokenizer);
            //if(iHi < 0)
            //   goto XF_Lyrics_Parse_End;
            //m_LyricsDisplayOffset = _ttoi(str.Mid(iLo + 1, iHi - iLo - 1));
//         XF_IH_Parse_End:;
                string str;
            TRACE("****GetXFInfoHeader");
            TRACE("Date: %s\n", (*ppXfih)->m_strDate);
            TRACE("Country: %s\n", (*ppXfih)->m_strCountry);
            TRACE("Category: %s\n", (*ppXfih)->m_strCategory);
            TRACE("Beat: %s\n", (*ppXfih)->m_strBeat);

            (*ppXfih)->m_straComposer.get_format_string(str, "/");
            TRACE("Composer: %s\n", str);

                (*ppXfih)->m_straLyricist.get_format_string(str, "/");
            TRACE("Lyricist: %s\n", str);

                (*ppXfih)->m_straArranger.get_format_string(str, "/");
            TRACE("Arranger: %s\n", str);

                (*ppXfih)->m_straPerformer.get_format_string(str, "/");
            TRACE("Performer: %s\n", str);

            TRACE("ID: %s\n", (*ppXfih)->m_id);
         }
         else if(wstrtokenizer.Mid(0, 4).Compare("XFln") == 0)
         {
            *ppXfihls = new XFInfoHeaderLS();
            (*ppXfihls)->FromData(wstrtokenizer);
            //if(iHi < 0)
            //   goto XF_Lyrics_Parse_End;
            //m_LyricsDisplayOffset = _ttoi(str.Mid(iLo + 1, iHi - iLo - 1));
//XF_IHLS_Parse_End:;
         okInfoHeaderLS = TRUE;
         }
        }
    }
//   if(!okSongName &&
//      !okInfoHeader)
//   {
//      delete *ppXfih;
//      pXfih = NULL;
//   }
//   if(!okInfoHeaderLS)
//   {
//      delete *ppXfihls;
//      pXfihls= NULL;
//   }
//    return (m_fdwSMF & ::mus::midi::EndOfFile) ? ::mus::midi::SEndOfFile : ::mus::midi::Success;
   return (_GetFlags().is_signalized(::mus::midi::EndOfFile)) ? ::mus::midi::SEndOfFile : ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::WriteXFInfoHeader(
   const char * pszSongName,
   XFInfoHeader *pXfih,
   XFInfoHeaderLS *pXfihls)
{
//    PSMF                    pSmf = (PSMF)hSmf;
   ::mus::midi::e_file_result               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;
   primitive::memory   memstorage;

   if(m_tkPosition != 0)
   {
      return   ::mus::midi::EInvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
    if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
    {
        return ::mus::midi::SEndOfFile;
    }

   m_event.SetDelta(0);
   if(pszSongName != NULL)
   {
      m_event.SetFullType(::mus::midi::Meta);
      m_event.SetMetaType(::mus::xf::MetaSongName);
      memstorage.allocate(gen::international::Utf8ToMultiByteCount(gen::international::CodePageLatin1, pszSongName));
      m_event.SetParam((byte *) memstorage.get_data(), memstorage.get_size() - 1);
      gen::international::utf8_to_multibyte(
         gen::international::CodePageLatin1,
         (char *) m_event.GetParam(),
         m_event.GetParamSize(),
         pszSongName);
//      m_event.GetParam() = (byte *)
//         International
//         ::UnicodeToAnsiDup(pSongName);
      //m_event.m_cbParm = strlen((const char *)m_event.GetParam());
      if((smfrc = WriteCompleteEvent(0x7fffffff, false)) != ::mus::midi::Success)
         return smfrc;
   }
   if(pXfih != NULL)
   {
      m_event.SetFullType(::mus::midi::Meta);
      m_event.SetMetaType(::mus::xf::MetaXFInfoHdr);
      string str;
      pXfih->ToData(str);

      gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, memstorage, str);
//      memstorage.allocate(
//         International
//         ::StringToLatin1Count(str)@);
      m_event.SetParam((byte *) memstorage.get_data(),
      memstorage.get_size() - 1);
//      gen::international::StringToLatin1(
//         (char *) m_event.GetParam() ,
//         m_event.GetParamSize(),
//         str);
//      m_event.GetParam() = (byte *)
//         International
//         ::UnicodeToAnsiDup(str);
//      m_event.GetParamSize() = strlen((const char *) m_event.GetParam());
      if((smfrc = WriteCompleteEvent(0x7fffffff, false)) != ::mus::midi::Success)
         return smfrc;

      TRACE("****WriteXFInfoHeader");
      TRACE("Date: %s\n", (char *) m_event.GetParam());
//      free(m_event.GetParam());
   }
   if(pXfihls != NULL)
   {
      m_event.SetFullType(::mus::midi::Meta);
      m_event.SetMetaType(::mus::xf::MetaXFInfoHdr);
      string str;
      pXfihls->ToData(str);
      memstorage.allocate(
         gen::international::Utf8ToMultiByteCount(gen::international::CodePageLatin1, str));
      m_event.SetParam((byte *) memstorage.get_data(),
       memstorage.get_size() - 1);
      gen::international::utf8_to_multibyte(
         gen::international::CodePageLatin1,
         (char *) m_event.GetParam() ,
         m_event.GetParamSize(),
         str);
//      m_event.GetParam() = (byte *)
//         International
//         ::UnicodeToAnsiDup(str);
//      m_event.GetParamSize() = strlen((const char *) m_event.GetParam());
      if((smfrc = WriteCompleteEvent(0x7fffffff, false)) != ::mus::midi::Success)
         return smfrc;
//      delete m_event.GetParam();
   }
   return ::mus::midi::Success;
}


::mus::midi::e_file_result midi_track::ReadKarTokens(
   stringa &  tokena,
   imedia::position_array *   lptkaTicks)
{
   string str;
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   ASSERT(lptkaTicks != NULL);
   tokena.remove_all();
   lptkaTicks->remove_all();


   while(m_tkPosition == 0)
   {
      smfrc = ReadEvent(tkMax, TRUE);
      if(::mus::midi::Success != smfrc)
      {
         break;
      }
      if((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::midi::MetaKarLyric == m_event.GetMetaType()))
      {
         LPTSTR lpsz = str.GetBufferSetLength(m_event.GetParamSize() + 1);
         memcpy(lpsz, m_event.GetParam(), m_event.GetParamSize());
         lpsz[m_event.GetParamSize()] = '\0';
         str.ReleaseBuffer();
         //gen::international::MultiByteToUnicode(
           // CodePageLatin1,
//            str, (char *) m_event.GetParam(), m_event.GetParamSize());
         if(!str.is_empty())
         {
            if(str[0] != '@')
            {
               tokena.add(str);
               lptkaTicks->add(m_tkPosition);
            }
         }
      }
      smfrc = MoveNext();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }
   if (::mus::midi::Success != smfrc)
   {
      return smfrc;
   }
   while(TRUE)
   {
      smfrc = ReadEvent(tkMax, TRUE);
      if (::mus::midi::Success != smfrc)
      {
         break;
      }


      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::midi::MetaKarLyric == m_event.GetMetaType()))
      {
/*         gen::international::MultiByteToUnicode(
            CodePageLatin1,
            str,
            (char *) m_event.GetParam(),
            m_event.GetParamSize());*/
         LPTSTR lpsz = str.GetBufferSetLength(m_event.GetParamSize() + 1);
         memcpy(lpsz, m_event.GetParam(), m_event.GetParamSize());
         lpsz[m_event.GetParamSize()] = '\0';
         str.ReleaseBuffer();
         tokena.add(str);
         lptkaTicks->add(m_tkPosition);
      }
      smfrc = MoveNext();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::ReadAnsiXFTokens(
      stringa &  tokena,
      imedia::position_array *   lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   string str;
   tokena.remove_all();
   lptkaTicks->remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   //m_ptracks->seek_begin();

   //midi_event_v008 event;

   /*    while(::mus::midi::Success == ReadEvent(tkMax, TRUE))
   {
   if ((::mus::midi::Meta == m_event.GetFullType()) &&
   (::mus::xf::MetaLyric == m_event.GetMetaType()))
   {
         string str;
         International
         ::Latin1ToString(
         str,
         (const char *) m_event.GetParam(),
         m_event.GetParamSize());
         TRACE("%s\n", str);
         lpstraTokens->add(str);
         lptkaTicks->add(m_tkPosition);
         }
}*/

   while(TRUE)
   {
      smfrc = ReadEvent(tkMax, TRUE);
      if (::mus::midi::Success != smfrc)
      {
         break;
      }


      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::xf::MetaLyric == m_event.GetMetaType()))
      {
         gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
         TRACE("%s\n", str);
         tokena.add(str);
         lptkaTicks->add(m_tkPosition);
      }


      smfrc = MoveNext();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::ReadShiftJisXFTokens(
      stringa &  tokena,
      imedia::position_array *   lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   tokena.remove_all();
   lptkaTicks->remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   string str;

   while(TRUE)
   {
      smfrc = ReadEvent(tkMax, TRUE);
      if (::mus::midi::Success != smfrc)
      {
         break;
      }


      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::xf::MetaLyric == m_event.GetMetaType()))
      {
         gen::international::multibyte_to_utf8(gen::international::CodePageShiftJIS, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
         TRACE("%s\n", str);
         tokena.add(str);
         lptkaTicks->add(m_tkPosition);
      }


      smfrc = MoveNext();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}


::mus::midi::e_file_result   midi_track::seek_begin()
{
   if(m_bAutoAllocation)
   {
      m_tkPosition      = 0;
      m_cbLeft            = m_smti.m_cbLength;
      m_hpbImage         = GetAllocationImage() + sizeof(CHUNKHDR);
      m_ptracks->m_uchRunningStatus   = 0;
      m_estate            = StateOnDelta;
      m_tkDelta         = 0;
      m_iCurrentEvent   = -1;
      _GetFlags().unsignalize_all();
   }
   else
   {
      ASSERT(m_ptracks != NULL);
      ::mus::midi::file * pfile  = m_ptracks->m_pFile;
      if(pfile == NULL)
      {
         m_hpbImage        = NULL;
      }
      else
      {
         m_hpbImage        = pfile->GetImage() + m_idxTrack;
      }
      m_tkPosition         = 0;
      m_cbLeft             = m_smti.m_cbLength;
      m_ptracks->m_uchRunningStatus     = 0;
      m_estate               = StateOnDelta;
      m_tkDelta            = 0;
      m_iCurrentEvent      = -1;
      _GetFlags().unsignalize_all();
   }
    return ::mus::midi::Success;
}


/*BOOL midi_track::allocate(DWORD dwNewLength)
{
   ASSERT(m_bAutoAllocation);
//   if(m_bMirrorAllocation)
//      if(!AllocateMirror(dwNewLength))
//         return FALSE;
   if(m_hpbAllocation == NULL)
   {
      m_hpbAllocation = (byte *) malloc(dwNewLength + sizeof(CHUNKHDR));
      if(m_hpbAllocation!= NULL)
      {
//         m_dwAllocation = HeapSize(theApp.m_hHeap, 0 , m_hpbAllocation);
         m_dwAllocation = dwNewLength + sizeof(CHUNKHDR);
         m_hpbImage = m_hpbAllocation + sizeof(CHUNKHDR);
         m_smti.m_cbLength = dwNewLength;
//         m_dwAllocation = dwNewLength + sizeof(CHUNKHDR);
         return TRUE;
      }
      else
      {
         return FALSE;
      }
   }
   else
   {
      if(dwNewLength  + sizeof(CHUNKHDR) > m_dwAllocation)
      {
         DWORD dwAllocation = dwNewLength + sizeof(CHUNKHDR)+ m_dwAllocationAddUp;
         LPVOID lpVoid = realloc(m_hpbAllocation, dwAllocation);
         //LPVOID lpVoid =HeapReAlloc(theApp.m_hHeap, 0, m_hpbAllocation, dwAllocation);
         if(lpVoid == NULL)
         {
            DWORD dw = GetLastError();
//            TRACELASTERROR();
            return FALSE;
         }
         else
         {
            //m_dwAllocation = HeapSize(theApp.m_hHeap, 0 , m_hpbAllocation);
            m_dwAllocation = dwAllocation;
            m_hpbImage = (byte *) lpVoid + (m_hpbImage - m_hpbAllocation);
            m_hpbAllocation = (byte *) lpVoid;
            m_smti.m_cbLength = dwNewLength;
            return TRUE;
         }
      }
      else
      {
         m_smti.m_cbLength = dwNewLength;
         return TRUE;
      }

   }
}*/

/*BOOL midi_track::AllocateMirror(DWORD dwNewLength)
{
   ASSERT(m_bMirrorAllocation);
   if(m_hpbMirrorAllocation == NULL)
   {
      m_hpbMirrorAllocation = (byte *) malloc(dwNewLength + sizeof(CHUNKHDR));
      if(m_hpbMirrorAllocation!= NULL)
      {
         m_hpbMirrorImage = m_hpbMirrorAllocation + sizeof(CHUNKHDR);
         return TRUE;
      }
      else
      {
         return FALSE;
      }
   }
   else
   {
      if(dwNewLength  + sizeof(CHUNKHDR) > m_dwAllocation)
      {
         DWORD dwAllocation = dwNewLength + sizeof(CHUNKHDR)+ m_dwAllocationAddUp;
         LPVOID lpVoid = realloc(m_hpbAllocation, dwAllocation);
         //LPVOID lpVoid =HeapReAlloc(theApp.m_hHeap, 0, m_hpbAllocation, dwAllocation);
         if(lpVoid == NULL)
         {
            DWORD dw = GetLastError();
            TRACELASTERROR();
            return FALSE;
         }
         else
         {
            //m_dwAllocation = HeapSize(theApp.m_hHeap, 0 , m_hpbAllocation);
            m_hpbMirrorImage = (byte *) lpVoid + (m_hpbMirrorImage - m_hpbMirrorAllocation);
            m_hpbMirrorAllocation = (byte *) lpVoid;
            return TRUE;
         }
      }
      else
      {
         return TRUE;
      }

   }
}*/

::mus::midi::e_file_result midi_track::WriteDelta()
{
   ASSERT(m_estate == StateOnDelta);
   ASSERT(m_bAutoAllocation);
   if (!(m_dwUsed = SetVDWord((DWORD) m_tkDelta)))
   {
      TRACE("No Memory Available.");
      return ::mus::midi::ENoMemory;
   }

   m_hpbImage += m_dwUsed;
   m_cbLeft -= m_dwUsed;
   //m_smti.m_cbLength += m_dwUsed;
   m_estate = StateOnEvent;

   return ::mus::midi::Success;
}

void midi_track::SetAutoAllocation(BOOL bValue)
{
   if(bValue)
   {
      if(!m_bAutoAllocation)
      {
         ASSERT(!m_bAutoAllocation);
         byte * hpb = GetTrackImage();
         DWORD cbSize = GetTrackImageLength();
         m_bAutoAllocation = true;
         if(hpb != NULL)
         {
            allocate(cbSize);
            memcpy(GetAllocationImage(), hpb, cbSize);
         }
         else
         {
            allocate(sizeof(CHUNKHDR));
         }
         m_hpbImage = get_data();
      }
   }
   else
   {
      if(m_bAutoAllocation)
      {
/*         if(m_hpbAllocation != NULL)
         {
            free(m_hpbAllocation);
            m_hpbAllocation = NULL;
            m_dwAllocation = 0;
         }*/
      }
      m_bAutoAllocation = false;
   }

}

::mus::midi::e_file_result midi_track::WriteCompleteEvent(imedia::position tkMax, bool bUseEventPosition)
{

   ASSERT(m_estate == StateOnDelta);
   ASSERT(m_bAutoAllocation);

   BYTE                    bEvent;
   DWORD                   dwUsedTotal;
   DWORD                   dwUsed;
   DWORD                   cbEvent;
   ::mus::midi::e_file_result            smfrc;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short m_event, which is most cases.
    */

    if(bUseEventPosition)
    {
        ASSERT(m_event.get_position() >= m_tkPosition);
       m_tkDelta = m_event.get_position() - m_tkPosition;
    }
    else
    {
        m_tkDelta = m_event._GetDelta();
    }


   if((smfrc = WriteDelta()) != ::mus::midi::Success)
   {
      return smfrc;
   }

   m_tkPosition += m_tkDelta;

   if (m_tkPosition > tkMax)
    {
        return ::mus::midi::SReachedTkMax;
    }

   bEvent = m_event.GetFullType();

   if(bEvent < ::mus::midi::Msg)
   {
      try
      {
         allocate_add_up(1);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }


      dwUsedTotal = 1;
      *m_hpbImage++ = m_event.GetChB1();
        if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
        {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception * pe)
         {
            pe->Delete();
            return ::mus::midi::ENoMemory;
         }
            *m_hpbImage++ = m_event.GetChB2();
            dwUsedTotal++;
        }
   }
   else if(bEvent < ::mus::midi::SysEx)
   {
      m_ptracks->m_uchRunningStatus = bEvent;
      try
      {
         allocate_add_up(2);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }
      dwUsedTotal = 2;
      *m_hpbImage++ = bEvent;
      *m_hpbImage++ = m_event.GetChB1();
        if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
        {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception *)
         {
            return ::mus::midi::ENoMemory;
         }
            *m_hpbImage++ = m_event.GetChB2();
            dwUsedTotal++;
        }
   }
    else
    {
        if (::mus::midi::Meta == bEvent)
        {
         try
         {
            allocate_add_up(2);
         }
         catch(memory_exception *)
         {
            return ::mus::midi::ENoMemory;
         }
         *m_hpbImage++ = ::mus::midi::Meta;
            if (::mus::midi::MetaEOT == (*m_hpbImage++ = m_event.GetMetaType()))
            {
                _GetFlags().signalize(::mus::midi::EndOfTrack);
            m_smti.m_tkLength = m_tkPosition;
            }
            dwUsedTotal = 2;
        }
        else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
        {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception *)
         {
            return ::mus::midi::ENoMemory;
         }
            *m_hpbImage++ = bEvent;
            dwUsedTotal = 1;
        }
        else
        {
            ASSERT(FALSE);
        }

      cbEvent = m_event.GetParamSize();

      if(!(dwUsed = SetVDWord(cbEvent)))
      {
         return ::mus::midi::ENoMemory;
      }

        m_hpbImage  += dwUsed;
        dwUsedTotal  += dwUsed;


      try
      {
         allocate_add_up(cbEvent);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }

      memcpy(m_hpbImage, m_event.GetParam(), cbEvent);

        m_hpbImage += cbEvent;
        dwUsedTotal += cbEvent;
    }

//   m_smti.m_cbLength += dwUsedTotal;
   m_estate = StateOnDelta;

   return ::mus::midi::Success;
}


::mus::midi::e_file_result midi_track::WriteCompleteEvent(midi_event_base & event, imedia::position tkMax, bool bUseEventPosition)
{

   ASSERT(m_estate == StateOnDelta);
   ASSERT(m_bAutoAllocation);

   BYTE                    bEvent;
   DWORD                   dwUsedTotal;
   DWORD                   dwUsed;
   DWORD                   cbEvent;
   ::mus::midi::e_file_result            smfrc;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short event, which is most cases.
    */

    if(bUseEventPosition)
    {
        ASSERT(event.get_position() >= m_tkPosition);
       m_tkDelta = event.get_position() - m_tkPosition;
    }
    else
    {
        m_tkDelta = event.GetDelta();
    }


   if((smfrc = WriteDelta()) != ::mus::midi::Success)
   {
      return smfrc;
   }

   m_tkPosition += m_tkDelta;

   if (m_tkPosition > tkMax)
    {
        return ::mus::midi::SReachedTkMax;
    }

   bEvent = event.GetFullType();

   if(bEvent < ::mus::midi::Msg)
   {
      ASSERT(FALSE);
   }
   else if(bEvent == m_ptracks->m_uchRunningStatus)
   {
      try
      {
         allocate_add_up(1);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }


      dwUsedTotal = 1;
      *m_hpbImage++ = event.GetChB1();
        if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
        {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception * pe)
         {
            pe->Delete();
            return ::mus::midi::ENoMemory;
         }
            *m_hpbImage++ = event.GetChB2();
            dwUsedTotal++;
        }
   }
   else if(bEvent < ::mus::midi::SysEx)
   {
      m_ptracks->m_uchRunningStatus = bEvent;
      try
      {
         allocate_add_up(2);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }
      dwUsedTotal = 2;
      *m_hpbImage++ = bEvent;
      *m_hpbImage++ = event.GetChB1();
        if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
        {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception *)
         {
            return ::mus::midi::ENoMemory;
         }
            *m_hpbImage++ = event.GetChB2();
            dwUsedTotal++;
        }
   }
    else
    {
        if (::mus::midi::Meta == bEvent)
        {
         try
         {
            allocate_add_up(2);
         }
         catch(memory_exception *)
         {
            return ::mus::midi::ENoMemory;
         }
         *m_hpbImage++ = ::mus::midi::Meta;
            if (::mus::midi::MetaEOT == (*m_hpbImage++ = event.GetMetaType()))
            {
                _GetFlags().signalize(::mus::midi::EndOfTrack);
            m_smti.m_tkLength = m_tkPosition;
            }
            dwUsedTotal = 2;
        }
        else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
        {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception *)
         {
            return ::mus::midi::ENoMemory;
         }
            *m_hpbImage++ = bEvent;
            dwUsedTotal = 1;
        }
        else
        {
            ASSERT(FALSE);
        }

      cbEvent = event.GetParamSize();

      if(!(dwUsed = SetVDWord(cbEvent)))
      {
         return ::mus::midi::ENoMemory;
      }

        m_hpbImage  += dwUsed;
        dwUsedTotal  += dwUsed;


      try
      {
         allocate_add_up(cbEvent);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }

      memcpy(m_hpbImage, event.GetParam(), cbEvent);

        m_hpbImage += cbEvent;
        dwUsedTotal += cbEvent;
    }

//   m_smti.m_cbLength += dwUsedTotal;
   m_estate = StateOnDelta;

   return ::mus::midi::Success;
}

/*::mus::midi::e_file_result midi_track::copy(midi_track *pTrk)
{
   if(m_bAutoAllocation)
   {
      if(!allocate(pTrk->m_smti.m_cbLength))
         return ::mus::midi::ENoMemory;
      byte * hpbImage = pTrk->m_ptracks->m_pFile->GetImage() + pTrk->m_idxTrack - sizeof(CHUNKHDR);
      memcpy(m_hpbAllocation, hpbImage, m_smti.m_cbLength + sizeof(CHUNKHDR));
      return ::mus::midi::Success;
   }
   else
   {
      ASSERT(FALSE);
      return ::mus::midi::FunctionNotSupported;
   }
}*/

::mus::midi::e_file_result midi_track::WriteHeader(CHUNKHDR *pHdr)
{
   ASSERT(m_bAutoAllocation);
   byte * hpbAllocation = GetAllocationImage();
   ASSERT(hpbAllocation != NULL);
   memcpy(
      hpbAllocation,
      &pHdr->fourccType,
      sizeof(pHdr->fourccType));
   DWORD dw = pHdr->dwLength;
   dw = DWORDSWAP(dw);
   memcpy(
      hpbAllocation + sizeof(pHdr->fourccType),
      &dw,
      sizeof(pHdr->dwLength));
   return ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::WriteHeaderLength()
{
   ASSERT(!m_bAutoAllocation);
   //byte * hpbAllocation = GetAllocationImage();
   //ASSERT(hpbAllocation == NULL);
   byte * hpbImage = GetTrackImage();
   DWORD dw = m_smti.m_cbLength;
   dw = DWORDSWAP(dw);
   memcpy(
      hpbImage + sizeof(FOURCC),
      &dw,
      sizeof(DWORD));
   return ::mus::midi::Success;
}


::mus::midi::e_file_result midi_track::WriteXFLyricEvent(string &str, imedia::position tkPosition)
{
   ::mus::midi::e_file_result smfrc;
   if(tkPosition < m_tkPosition)
      m_event.SetDelta(0);
   else
      m_event.SetDelta(tkPosition - m_tkPosition);
   m_event.SetFullType(::mus::midi::Meta);
   m_event.SetMetaType(::mus::xf::MetaLyric);

   gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, m_memstorageHelper, str);
   m_event.SetParam((byte *) m_memstorageHelper.get_data(), m_memstorageHelper.get_size() - 1);
   smfrc = WriteCompleteEvent(0x7fffffff, false);
   return smfrc;
}


byte * midi_track::GetAllocationImage()
{
   return get_data();
}

::mus::midi::e_file_result midi_track::copy(midi_track *pTrk, int iMode)
{
   midi_event_v001 * pevent;
   imedia::position tkDelta;

   SetAutoAllocation();
   seek_begin();
   allocate(sizeof(CHUNKHDR));
   memcpy(GetTrackImage(), pTrk->GetTrackImage(), sizeof(CHUNKHDR));
   pTrk->seek_begin();
   pevent = &pTrk->m_event;
   tkDelta = 0;
   register bool bCopy;
   while(TRUE)
   {
      if(pTrk->_GetFlags().is_signalized(::mus::midi::EndOfTrack))
         break;
      if(pTrk->ReadEvent(0x7fffffff, TRUE) != VMSR_SUCCESS)
         break;
         bCopy = true;
      if(pevent->GetFlags() != 0)
      {
         bCopy = false;
      }
      if(bCopy)
      {
         if((iMode & CopyExcludeXFMetaLyrics) > 0)
         {
            if(pevent->_GetFullType() == ::mus::midi::Meta &&
               pevent->_GetMetaType() == ::mus::xf::MetaLyric)
            {
               bCopy = false;
            }
         }
         if(bCopy)
         {
            if((iMode & CopyExcludeKarMetaLyrics) > 0)
            {
               if(pevent->_GetFullType() == ::mus::midi::Meta &&
                  pevent->_GetMetaType() == ::mus::midi::MetaKarLyric)
               {
                  bCopy = false;
               }
            }
         }
      }
      if(bCopy)
      {
         m_event = *pevent;
         m_event.SetDelta(m_event._GetDelta() + tkDelta);
         tkDelta = 0;
         WriteCompleteEvent(0x7fffffff, false);
      }
      else
      {
         tkDelta += pevent->_GetDelta();
      }
      if(pTrk->MoveNext() != VMSR_SUCCESS)
         break;

   }
   CHUNKHDR chHdr;
   chHdr.fourccType = FOURCC_MTrk;
   chHdr.dwLength = m_smti.m_cbLength;
   WriteHeader(&chHdr);
   return ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::CopyWork(midi_track *pTrk, int iMode)
{
   imedia::position tkDelta;

   SetAutoAllocation();
   seek_begin();
   allocate(sizeof(CHUNKHDR));
   memcpy(GetTrackImage(), pTrk->GetTrackImage(), sizeof(CHUNKHDR));
   pTrk->seek_begin();
   tkDelta = 0;
   register bool bCopy;

   for(int i = 0; i < pTrk->m_trackWorkStorage.GetEventCount(); i++)
   {
      midi_event_v008 & event = pTrk->m_trackWorkStorage.EventAt(i);
      bCopy = true;
      if(event.GetFlags() != 0)
      {
         bCopy = false;
      }
      if(bCopy)
      {
         if((iMode & CopyExcludeXFMetaLyrics) > 0)
         {
            if(event._GetFullType() == ::mus::midi::Meta &&
               event._GetMetaType() == ::mus::xf::MetaLyric)
            {
               bCopy = false;
            }
         }
         if(bCopy)
         {
            if((iMode & CopyExcludeKarMetaLyrics) > 0)
            {
               if(event._GetFullType() == ::mus::midi::Meta &&
                  event._GetMetaType() == ::mus::midi::MetaKarLyric)
               {
                  bCopy = false;
               }
            }
         }
      }
      if(bCopy)
      {
         m_event = event;
         m_event.SetDelta(m_event._GetDelta() + tkDelta);
         tkDelta = 0;
         WriteCompleteEvent(0x7fffffff, false);
      }
      else
      {
         tkDelta += event._GetDelta();
      }
   }
   CHUNKHDR chHdr;
   chHdr.fourccType = FOURCC_MTrk;
   chHdr.dwLength = m_smti.m_cbLength;
   WriteHeader(&chHdr);
   return ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::WorkCopyWork(midi_track *pTrk, int iMode)
{
   imedia::position tkDelta;
   bool bCopy;

   m_trackWorkStorage.remove_all();

   memcpy(&m_trackWorkStorage.m_chunkHeader, &pTrk->m_trackWorkStorage.m_chunkHeader, sizeof(CHUNKHDR));

   tkDelta = 0;
   for(int i = 0; i < pTrk->m_trackWorkStorage.GetEventCount(); i++)
   {
      midi_event_v008 & event = pTrk->m_trackWorkStorage.EventAt(i);
//      ASSERT(event.GetFullType() >= ::mus::midi::Msg);
      bCopy = true;
      if(event.GetFlags() != 0)
      {
         bCopy = false;
      }
      if(bCopy)
      {
         if((iMode & CopyExcludeXFMetaLyrics) > 0)
         {
            if(event.GetFullType() == ::mus::midi::Meta &&
               event.GetMetaType() == ::mus::xf::MetaLyric)
            {
               bCopy = false;
            }
         }
         if(bCopy)
         {
            if((iMode & CopyExcludeKarMetaLyrics) > 0)
            {
               if(event.GetFullType() == ::mus::midi::Meta &&
                  event.GetMetaType() == ::mus::midi::MetaKarLyric)
               {
                  bCopy = false;
               }
            }
         }
      }
      if(bCopy)
      {
         m_trackWorkStorage.add(event);
         m_trackWorkStorage.LastEvent().SetDelta(event._GetDelta() + tkDelta);
         tkDelta = 0;
      }
      else
      {
         tkDelta += event._GetDelta();
      }
   }
   return ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::GetNextKarInfo(
   SoftKaraokeInfo *pKarI)
{
   ASSERT(pKarI != NULL);

//    PSMF                    pSmf = (PSMF)hSmf;
   ::mus::midi::e_file_result               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;
   bool               okSongName = false;
   bool               okAuthor = false;
    bool               okCopyright = false;
   int                  nTCount = 0;



   if(m_tkPosition != 0)
   {
      return   ::mus::midi::EInvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
    if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
    {
        return ::mus::midi::SEndOfFile;
    }

   while(true)
   {
   //   if(nTCount >= 2)
   //      break;
        smfrc = ReadEvent(0, TRUE);
        if (::mus::midi::Success != smfrc)
        {
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-file.
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            _GetFlags().signalize(::mus::midi::EndOfFile);
            }

            TRACE( "smfReadEvents: GetNextKarInfo() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::midi::MetaKarHeader == m_event.GetMetaType()))
        {

         string str;
         gen::international::MultiByteToMultiByte(
            gen::international::CodePageLatin1,
            str,
            ::GetOEMCP(),
            (const char *) m_event.GetParam(), m_event.GetParamSize());
         if(str.Mid(0, 2).Compare("@T") == 0)
         {
            nTCount++;
//            if(*ppKarI == NULL)
//            {
//               TRACE("****GetKarInfoHeader");
//               *ppKarI = new SoftKaraokeInfo();
//            }
            if(nTCount == 1)
            {
               pKarI->m_strSongName = str.Mid(2);
               TRACE("Date: %s\n", pKarI->m_strSongName);
               okSongName = true;
//               (*ppKarI)->m_strSongName = str.Mid(2);
//               TRACE("Date: %s\n", (*ppKarI)->m_strSongName);
            }
            if(nTCount == 2)
            {
               pKarI->m_strAuthor = str.Mid(2);
               TRACE("Date: %s\n", str.Mid(2));
               okAuthor = true;
//               (*ppKarI)->m_strOther = str.Mid(2);
//               TRACE("Date: %s\n", (*ppKarI)->m_strOther);
            }
            if(nTCount >= 3)
            {
               pKarI->m_strCopyright = str.Mid(2);
               TRACE("Date: %s\n", str.Mid(2));
               okCopyright = true;
//               (*ppKarI)->m_strOther = str.Mid(2);
//               TRACE("Date: %s\n", (*ppKarI)->m_strOther);
            }
         }
        }
        smfrc = MoveNext();
        if (::mus::midi::Success != smfrc)
        {
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-spfile->
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            _GetFlags().signalize(::mus::midi::EndOfFile);
            }

            TRACE( "smfReadEvents: GetNextKarInfo() -> %u", (UINT)smfrc);
            break;
        }
      if(okSongName && okAuthor && okCopyright)
         break;
    }
//   if(!okSongName &&
//      !okInfoHeader)
//   {
//      delete *ppXfih;
//      pXfih = NULL;
//   }
//   if(!okInfoHeaderLS)
//   {
//      delete *ppXfihls;
//      pXfihls= NULL;
//   }
//    return (m_fdwSMF & ::mus::midi::EndOfFile) ? ::mus::midi::SEndOfFile : ::mus::midi::Success;
   return okSongName || okAuthor || okCopyright ? ::mus::midi::Success : ::mus::midi::SEndOfFile;
}


::mus::midi::e_file_result midi_track::GetNextTune1000Info(
   CTune1000Info *pTune1000I)
{
   ASSERT(pTune1000I != NULL);

//    PSMF                    pSmf = (PSMF)hSmf;
   ::mus::midi::e_file_result               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;
   bool               okSongName = FALSE;
   bool               okOther = FALSE;
   bool               okTSongName = FALSE;
   bool               okTOther = FALSE;
   int               nTCount = 0;
   int               nCount = 0;


   if(m_tkPosition != 0)
   {
      return   ::mus::midi::EInvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
    if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
    {
        return ::mus::midi::SEndOfFile;
    }

   while(true)
   {
//      if(nTCount >= 2)
//         break;
        smfrc = ReadEvent(0, TRUE);
        if (::mus::midi::Success != smfrc)
        {
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-spfile->
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            _GetFlags().signalize(::mus::midi::EndOfFile);
            }

            TRACE( "smfReadEvents: GetNextTune1000Info() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::midi::MetaTrackName == m_event.GetMetaType()
          || ::mus::midi::MetaKarLyric == m_event.GetMetaType()  ))
        {

         string str;
         gen::international::multibyte_to_utf8(
            gen::international::CodePageLatin1,
            str,
            (const char *) m_event.GetParam(), m_event.GetParamSize());
         if(str.Mid(0, 2).Compare("@T") == 0)
         {
            nTCount++;
            if(nTCount == 1)
            {
               pTune1000I->m_strSongName = str.Mid(2);
               TRACE("Date: %s\n", pTune1000I->m_strSongName);
               okTSongName = true;
            }
            if(nTCount >= 2)
            {
               pTune1000I->m_straOther.add_unique(str.Mid(2));
               TRACE("Date: %s\n", str);
               okTOther = true;
            }
         }
         else if(!okTSongName && str != "@LENGL")
         {
            nCount++;
            if(nCount == 1)
            {
               pTune1000I->m_strSongName = str;
               TRACE("Date: %s\n", pTune1000I->m_strSongName);
               okSongName = true;
            }
            if(nCount == 2)
            {
               pTune1000I->m_straOther.add_unique(str);
               TRACE("Date: %s\n", str);
               okOther = true;
            }
         }
        }
        smfrc = MoveNext();
        if (::mus::midi::Success != smfrc)
        {
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-file.
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            _GetFlags().signalize(::mus::midi::EndOfFile);
            }

            TRACE( "smfReadEvents: GetNextTune1000Info() -> %u", (UINT)smfrc);
            break;
        }
    }
//   if(!okSongName &&
//      !okInfoHeader)
//   {
//      delete *ppXfih;
//      pXfih = NULL;
//   }
//   if(!okInfoHeaderLS)
//   {
//      delete *ppXfihls;
//      pXfihls= NULL;
//   }
//    return (m_fdwSMF & ::mus::midi::EndOfFile) ? ::mus::midi::SEndOfFile : ::mus::midi::Success;
   return okSongName || okOther ? ::mus::midi::Success : ::mus::midi::SEndOfFile;
}

::mus::midi::e_file_result midi_track::GetStandardEventsV1(midi_events_v1 *pEvents, int iFilter, int iTrack, bool bAnyTrack)
{

   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   if(bAnyTrack)
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
         if (::mus::midi::Success != smfrc)
         {
            break;
         }



         if ((iFilter == m_event._GetType()))
         {
            pEvents->AddEvent(&m_event, m_tkPosition);
         }
         smfrc = MoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   else
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
         if (::mus::midi::Success != smfrc)
         {
            break;
         }



         if ((iFilter == m_event._GetType()) &&
            (iTrack == m_event._GetTrack() ))
         {
            pEvents->AddEvent(&m_event, m_tkPosition);
         }
         smfrc = MoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}

::mus::midi::e_file_result midi_track::GetNoteOnOffEventsV1(midi_events_v1 *pEvents, int iTrack, bool bAnyTrack)
{

   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   if(bAnyTrack)
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
         if (::mus::midi::Success != smfrc)
         {
            break;
         }



         if ((::mus::midi::NoteOn == m_event._GetType()) ||
            (::mus::midi::NoteOff == m_event._GetType() ))
         {
            pEvents->AddEvent(&m_event, m_tkPosition);
         }
      }
   }
   else
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
         if (::mus::midi::Success != smfrc)
         {
            break;
         }



         if (((::mus::midi::NoteOn == m_event._GetType()) ||
            (::mus::midi::NoteOff == m_event._GetType())) &&
            (iTrack == m_event._GetTrack()))
         {
            pEvents->AddEvent(&m_event, m_tkPosition);
         }
         smfrc = MoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}


// it returns in pevents, note on, note off,
// and maximum and minimum peaks of pitch bend

::mus::midi::e_file_result midi_track::GetLevel2Events(midi_events_v1 *pevents, int iTrack, bool bAnyTrack)
{

   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   int iPitchBend;
   int iLastPitchBend = 0;
   enum EDirection
   {
      Up,
      Down,
   } edirection = Up;
   midi_event_v001 eventLastPitchBend;
   if(bAnyTrack)
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
         if (::mus::midi::Success != smfrc)
         {
            break;
         }



         if ((::mus::midi::NoteOn == m_event._GetType()) ||
            (::mus::midi::NoteOff == m_event._GetType() ))
         {
            pevents->AddEvent(&m_event, m_tkPosition);
         }
         else if (::mus::midi::PitchBend == m_event._GetType())
         {
            iPitchBend = m_event.GetPitchBendLevel();
            if(edirection == Up)
            {
               if(iPitchBend < iLastPitchBend)
               {
                  edirection = Down;
                  pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
               }
               else if(iPitchBend == 0
                  && iLastPitchBend != 0)
               {
                  pevents->AddEvent(&m_event, m_tkPosition);
               }

            }
            else if(edirection == Down)
            {
               if(iPitchBend > iLastPitchBend)
               {
                  edirection = Up;
                  pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
               }
               else if(iPitchBend == 0
                  && iLastPitchBend != 0)
               {
                  pevents->AddEvent(&m_event, m_tkPosition);
               }
            }
            eventLastPitchBend = m_event;
            iLastPitchBend = iPitchBend;
         }

         smfrc = MoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   else
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
         if (::mus::midi::Success != smfrc)
         {
            break;
         }



         if (iTrack == m_event._GetTrack())
         {
            if(((::mus::midi::NoteOn == m_event._GetType()) ||
               (::mus::midi::NoteOff == m_event._GetType())))
            {
               pevents->AddEvent(&m_event, m_tkPosition);
            }
            else if (::mus::midi::PitchBend == m_event._GetType())
            {
               iPitchBend = m_event.GetPitchBendLevel();
               if(edirection == Up)
               {
                  if(iPitchBend < iLastPitchBend)
                  {
                     edirection = Down;
                     pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
                  }
                  else if(iPitchBend == 0
                     && iLastPitchBend != 0)
                  {
                     pevents->AddEvent(&m_event, m_tkPosition);
                  }

               }
               else if(edirection == Down)
               {
                  if(iPitchBend > iLastPitchBend)
                  {
                     edirection = Up;
                     pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
                  }
                  else if(iPitchBend == 0
                     && iLastPitchBend != 0)
                  {
                     pevents->AddEvent(&m_event, m_tkPosition);
                  }
               }
               eventLastPitchBend = m_event;
               iLastPitchBend = iPitchBend;
            }
         }
         smfrc = MoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}

bool midi_track::IsTune1000File()
{
   seek_begin();
   stringa strArray;
   imedia::position_array tkArray;
   ReadTune1000Tokens(strArray, &tkArray);
   if(strArray.get_size() > 0)
      return true;
   seek_begin();
   ReadKarTokens(strArray, &tkArray);
   if(strArray.get_size() > 0)
      return true;


   return false;

}

bool midi_track::IsSoftKaraokeFile(bool bWork, stringa * pstra)
{
   midi_event_v008 * pevent;
   ::mus::midi::e_file_result               smfrc;
   imedia::position               tkLastDelta = 0 ;
   bool               bIsSoftKaraokeFile = false;
   bool                    bSoftKaraoke = false;

   smfrc = _SeekBegin(bWork);
   if (::mus::midi::Success != smfrc)
   {
      TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
      return false;
   }

   ASSERT(!_GetFlags().is_signalized(::mus::midi::EndOfFile));
   int nArrobaCount = 0;
   while(true)
   {
      _GetEvent(bWork, pevent, 0, TRUE);

      if(m_tkPosition > 0)
         break;

      if((::mus::midi::Meta == pevent->GetFullType()) &&
         (::mus::midi::MetaTrackName == pevent->GetMetaType()))
      {
         string str;
         gen::international::MultiByteToOEM(
            gen::international::CodePageLatin1,
            str,
            (const char *) pevent->GetParam(),
            pevent->GetParamSize());
         if(str.CollateNoCase("Soft Karaoke") == 0)
         {
            bSoftKaraoke = true;
            if(pstra != NULL)
            {
               pstra->add(str);
            }
         }
      }
      else if ((::mus::midi::Meta == pevent->GetFullType()) &&
         (::mus::midi::MetaKarHeader == pevent->GetMetaType()))
      {
         string str;
         gen::international::MultiByteToOEM(
            gen::international::CodePageLatin1,
            str,
            (const char *) pevent->GetParam(), pevent->GetParamSize());
         string strMid =  str.Mid(0, 19);
         //if(strMid.Compare("@T") == 0 ||
//                strMid.Compare("@I") == 0 ||
  //              strMid.Compare("@L") == 0 ||
    //            strMid.Compare("@K") == 0 ||
      //          strMid.Compare("@V") == 0)
        //    {
         if(strMid.Compare("@KMIDI KARAOKE FILE") == 0)
         {
            nArrobaCount++;
            if(pstra != NULL)
            {
               pstra->add(str);
            }
         }
      }
      if(nArrobaCount > 0 && bSoftKaraoke)
         break;

      smfrc = _MoveNext(bWork);

      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }

   bIsSoftKaraokeFile = nArrobaCount > 0 || bSoftKaraoke;
   return bIsSoftKaraokeFile;
}


/*BOOL midi_track::Mirror()
{
   memcpy(m_hpbMirrorAllocation, m_hpbAllocation, m_dwAllocation);
   return TRUE;
}

::mus::midi::e_file_result midi_track::InsertCompleteEvent(imedia::position tkMax)
{

}*/

/*BOOL midi_track::ContainsEvent(midi_event_base *pEvent)
{
   byte * hpbImageStart = GetImage();
   byte * hpbImageEnd = hpbImageStart + m_smti.m_cbLength + sizeof(CHUNKHDR);
   return pEvent->GetImage() >= hpbImageStart &&
      pEvent->GetImage() < hpbImageEnd;
}*/

DWORD midi_track::GetTrackImageLength()
{
   return m_smti.m_cbLength + sizeof(CHUNKHDR);
}

byte * midi_track::GetTrackImage()
{
    if(m_bAutoAllocation)
    {
        return GetAllocationImage();
    }
    else
    {
        if(m_ptracks == NULL)
            return NULL;
       ASSERT(m_ptracks != NULL);
        ::mus::midi::file * pFile = m_ptracks->m_pFile;
        if(pFile == NULL)
            return NULL;
        else
        {
            ASSERT(pFile != NULL);
            if(pFile->GetImage() == NULL)
                return NULL;
            else
               return pFile->GetImage() + m_idxTrack - sizeof(CHUNKHDR);
        }
    }
}

DWORD midi_track::GetTrackBodyLength()
{
   return m_smti.m_cbLength + sizeof(CHUNKHDR);
}

byte * midi_track::GetTrackBody()
{
    if(m_bAutoAllocation)
    {
      if(GetAllocationImage() == NULL)
         return NULL;
      else
         return GetAllocationImage() + sizeof(CHUNKHDR);
    }
    else
    {
        if(m_ptracks == NULL)
            return NULL;
       ASSERT(m_ptracks != NULL);
        ::mus::midi::file * pFile = m_ptracks->m_pFile;
        if(pFile == NULL)
            return NULL;
        else
        {
            ASSERT(pFile != NULL);
            if(pFile->GetImage() == NULL)
                return NULL;
            else
               return pFile->GetImage() + m_idxTrack;
        }
    }
}

::mus::midi::e_file_result midi_track::seek(DWORD dwSeekWhat)
{
   ::mus::midi::e_file_result               smfrc;
   imedia::position               tkLastDelta = 0 ;
//   BOOL               okSongName = FALSE;
//   BOOL               okInfoHeader = FALSE;
//   BOOL               okInfoHeaderLS = FALSE;

   //   if(m_tkPosition != 0)
   //   {
   //      return   ::mus::midi::EInvalidTkPosition;
   //   }

   if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
   {
      return ::mus::midi::SEndOfFile;
   }

   while(true)
   {
      smfrc = ReadEvent(0, TRUE);
      if (::mus::midi::Success != smfrc)
         break;
      if(m_tkPosition > 0)
         break;
      switch(dwSeekWhat)
      {
      case ::mus::midi::SeekXFSongName:
         {
            if ((::mus::midi::Meta == m_event.GetFullType()) &&
               (::mus::xf::MetaSongName == m_event.GetMetaType()))
               return ::mus::midi::Success;
            break;
         }
      case ::mus::midi::SeekXFInfoHeader:
         {
            if ((::mus::midi::Meta == m_event.GetFullType()) &&
               (::mus::xf::MetaXFInfoHdr == m_event.GetMetaType()))
            {
               string_tokenizer str;
               gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
               if(gen::str::begins_ci(str, "XFhd"))
                  return ::mus::midi::Success;
            }
            break;
         }
      case ::mus::midi::SeekXFInfoHeaderLS:
         {
            if ((::mus::midi::Meta == m_event.GetFullType()) &&
               (::mus::xf::MetaXFInfoHdr == m_event.GetMetaType()))
            {
               string_tokenizer str;
               gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
               if(gen::str::begins_ci(str, "XFln"))
                  return ::mus::midi::Success;
            }
            break;
      case ::mus::midi::SeekKarID:
         if ((::mus::midi::Meta == m_event.GetFullType()) &&
            (::mus::midi::MetaTrackName == m_event.GetMetaType()))
         {
            string str;
            gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) m_event.GetParam(), m_event.GetParamSize());
            if(str.CollateNoCase("Soft Karaoke") == 0)
            {
               return ::mus::midi::Success;
            }
         }
         break;
         }
      default:;
      }

      smfrc = MoveNext();
      if (::mus::midi::Success != smfrc)
         break;
   }
   return smfrc;
}

VMSRESULT midi_track::WorkSeek(DWORD dwSeekWhat)
{
   ::mus::midi::e_file_result     smfrc = ::mus::midi::SNotFound;
   imedia::position               tkLastDelta = 0 ;
//   bool               okSongName = FALSE;
//   bool               okInfoHeader = FALSE;
//   bool               okInfoHeaderLS = FALSE;

   if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
   {
      return ::mus::midi::SEndOfFile;
   }

   int iSize = m_trackWorkStorage.GetEventCount() - 1;
   while(m_iWorkCurrentEvent < iSize)
   {
      midi_event_v008 & event = m_trackWorkStorage.EventAt(m_iWorkCurrentEvent + 1);
      m_iWorkCurrentEvent++;
      m_tkPosition += event._GetDelta();
      switch(dwSeekWhat)
      {
      case ::mus::midi::SeekXFSongName:
         {
            if((::mus::midi::Meta == event.GetFullType()) &&
               (::mus::xf::MetaSongName == event.GetMetaType()))
               return ::mus::midi::Success;
            if(m_tkPosition > 0)
               return ::mus::midi::SNotFound;
            break;
         }
      case ::mus::midi::SeekXFInfoHeader:
         {
            if ((::mus::midi::Meta == event.GetFullType()) &&
            (::mus::xf::MetaXFInfoHdr == event.GetMetaType()))
            {
               string_tokenizer str;
               gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) event.GetParam(), event.GetParamSize());
               if(gen::str::begins_ci(str, "XFhd"))
                  return ::mus::midi::Success;
            }
            if(m_tkPosition > 0)
               return ::mus::midi::SNotFound;
            break;
         }
      case ::mus::midi::SeekXFInfoHeaderLS:
         {
            if ((::mus::midi::Meta == event.GetFullType()) &&
             (::mus::xf::MetaXFInfoHdr == event.GetMetaType()))
            {
               string_tokenizer str;
               gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) event.GetParam(), event.GetParamSize());
               if(gen::str::begins_ci(str, "XFln"))
                  return ::mus::midi::Success;
            }
            if(m_tkPosition > 0)
               return ::mus::midi::SNotFound;
         }
         break;
      case ::mus::midi::SeekKarID:
         {
            if ((::mus::midi::Meta == event.GetFullType()) &&
            (::mus::midi::MetaTrackName == event.GetMetaType()))
            {
               if(event.GetParam() != NULL)
               {
                  string str;
                  gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) event.GetParam(), event.GetParamSize());
                  if(str.CollateNoCase("Soft Karaoke") == 0)
                  {
                     return ::mus::midi::Success;
                  }
               }
            }
            if(m_tkPosition > 0)
               return ::mus::midi::SNotFound;
         }
         break;
      default:;
      }
   }
   return smfrc;

}

bool midi_track::IsXFFile()
{
   if(m_trackWorkStorage.GetEventCount() > 0)
   {
      midi_event_v008 * pevent;
      ::mus::midi::e_file_result               smfrc;
      imedia::position               tkLastDelta = 0 ;
      bool               bIsXFFile = false;

      smfrc = WorkSeekBegin();
      if (::mus::midi::Success != smfrc)
      {
         TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
         return bIsXFFile;
      }


      while(TRUE)
      {
         WorkGetEvent(pevent, 0x7fffffff, TRUE);

         if ((::mus::midi::Meta == pevent->GetFullType()) &&
             (::mus::midi::MetaSeqSpecific == pevent->GetMetaType()))
           {
               if(pevent->GetParam()[0] == 0x43 && // YAMAHA ID
                   pevent->GetParam()[1] == 0x7B && //
                   pevent->GetParam()[2] == 0x00 && //
                   pevent->GetParam()[3] == 0x58 && // X
                   pevent->GetParam()[4] == 0x46 && // F
                   pevent->GetParam()[5] == 0x30) // 0
               {
                   bIsXFFile = pevent->GetParam()[6] == 0x32 && m_tkPosition == 0;
               bIsXFFile |= (pevent->GetParam()[6] == 0x31);
               if(bIsXFFile)
                  break;
               }
           }
           smfrc = WorkMoveNext();
           if (::mus::midi::Success != smfrc)
           {
               TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
               break;
           }
       }
      return bIsXFFile;
   }
   else
   {
      ::mus::midi::e_file_result               smfrc;
      imedia::position               tkLastDelta = 0 ;
      bool               bIsXFFile = false;

      smfrc = seek_begin();
      if (::mus::midi::Success != smfrc)
      {
         TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
         return bIsXFFile;
      }


      while(TRUE)
      {
         smfrc = ReadEvent(0, true);
         if(smfrc != ::mus::midi::Success)
            return false;

         if ((::mus::midi::Meta == m_event.GetFullType()) &&
            (::mus::midi::MetaSeqSpecific == m_event.GetMetaType()))
         {
            if(m_event.GetParam()[0] == 0x43 && // YAMAHA ID
               m_event.GetParam()[1] == 0x7B && //
               m_event.GetParam()[2] == 0x00 && //
               m_event.GetParam()[3] == 0x58 && // X
               m_event.GetParam()[4] == 0x46 && // F
               m_event.GetParam()[5] == 0x30) // 0
            {
               bIsXFFile = m_event.GetParam()[6] == 0x32 && m_tkPosition == 0;
               bIsXFFile |= (m_event.GetParam()[6] == 0x31);
               if(bIsXFFile)
                  break;
            }
         }
         smfrc = MoveNext();
         if (::mus::midi::Success != smfrc)
         {
            TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
            break;
         }
      }
      return bIsXFFile;
   }

}

::mus::midi::e_file_result midi_track::ReadTune1000Tokens(
   stringa &  tokena,
   imedia::position_array *lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   string str;
   tokena.remove_all();
   lptkaTicks->remove_all();

   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   while(true)
   {
      smfrc = ReadEvent(tkMax, TRUE);
      if (::mus::midi::Success != smfrc)
      {
         break;
      }


      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::midi::MetaLyric == m_event.GetMetaType()))
      {
/*         gen::international::MultiByteToUnicode(
            CodePageLatin1,
            str,
            (char *) m_event.GetParam(),
            m_event.GetParamSize());*/
         LPTSTR lpsz = str.GetBufferSetLength(m_event.GetParamSize() + 1);
         memcpy(lpsz, m_event.GetParam(), m_event.GetParamSize());
         lpsz[m_event.GetParamSize()] = '\0';
         str.ReleaseBuffer();
         tokena.add(str);
         lptkaTicks->add(m_tkPosition);
      }
      smfrc = MoveNext();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }

   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}


VMSRESULT midi_track::FromWorkTrack(bool b)
{
   UNREFERENCED_PARAMETER(b);
   return FromWorkTrack(m_trackWorkStorage);
}

VMSRESULT midi_track::FromWorkTrack(midi_track_v008 & track)
{

   SetAutoAllocation();
   allocate(sizeof(CHUNKHDR));
   seek_begin();

   m_smti.m_cbLength = 0;
   int iCount = track.GetEventCount();
   for(int i = 0; i < iCount; i++)
   {
      WriteEvent(track.EventAt(i));
   }

   m_smti.m_cbLength = this->get_size() - sizeof(CHUNKHDR);
   m_trackWorkStorage.m_chunkHeader.dwLength = this->get_size() - sizeof(CHUNKHDR);
   WriteHeader(&track.m_chunkHeader);

   return VMSR_SUCCESS;
}


VMSRESULT midi_track::ToWorkStorage()
{
   midi_event_v001 eventWork;

   int iCurrentEvent = m_iCurrentEvent;

   ASSERT(GetTrackImage());

   memcpy(&m_trackWorkStorage.m_chunkHeader, GetTrackImage(), sizeof(CHUNKHDR));


   seek_begin();
   m_trackWorkStorage.remove_all();
   while(ReadEvent(eventWork) == VMSR_SUCCESS)
   {
//      ASSERT(eventWork.GetFullType() >= ::mus::midi::Msg);
//      if(m_tkPosition >= 31450)
  //       AfxDebugBreak();
      m_trackWorkStorage.add(eventWork);
      if(MoveNext() != ::mus::midi::Success)
         break;
   }
   m_smti.m_tkLength = m_tkPosition;
   m_iCurrentEvent = iCurrentEvent;
   return VMSR_SUCCESS;
}

midi_track_v008 & midi_track::GetWorkTrack()
{
    return m_trackWorkStorage;
}

::mus::midi::e_file_result midi_track::WriteEvent(midi_event_v008 & eventMidi)
{
   ASSERT(m_estate == StateOnDelta);
   ASSERT(m_bAutoAllocation);

   BYTE                       bEvent;
   DWORD                      cbEvent;
   ::mus::midi::e_file_result         smfrc;
   DWORD                      dwUsed;

   m_tkDelta = eventMidi._GetDelta();

   if(m_tkDelta < 0)
      m_tkDelta = 0;

   if((smfrc = WriteDelta()) != ::mus::midi::Success)
   {
      return smfrc;
   }

   m_tkPosition += eventMidi._GetDelta();

   bEvent = eventMidi.GetFullType();

   //if(bEvent == m_ptracks->m_uchRunningStatus)
   if(false) // do not optimize with Running Status
   {
      try
      {
         allocate_add_up(1);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }

      *m_hpbImage++ = eventMidi.GetChB1();

      if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
      {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception * pe)
         {
            pe->Delete();
            return ::mus::midi::ENoMemory;
         }
         *m_hpbImage++ = eventMidi.GetChB2();
      }
   }
   else if(bEvent < ::mus::midi::SysEx)
   {
      m_ptracks->m_uchRunningStatus = bEvent;
      try
      {
         allocate_add_up(2);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }
      *m_hpbImage++ = bEvent;
      *m_hpbImage++ = eventMidi.GetChB1();
      if (3 == ::mus::midi::GetMessageLen(m_ptracks->m_uchRunningStatus))
      {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception * pe)
         {
            pe->Delete();
            return ::mus::midi::ENoMemory;
         }
         *m_hpbImage++ = eventMidi.GetChB2();
      }
   }
   else
   {
      if (::mus::midi::Meta == bEvent)
      {
         try
         {
            allocate_add_up(2);
         }
         catch(memory_exception * pe)
         {
            pe->Delete();
            return ::mus::midi::ENoMemory;
         }
         *m_hpbImage++ = ::mus::midi::Meta;
         if (::mus::midi::MetaEOT == (*m_hpbImage++ = eventMidi.GetMetaType()))
         {
            _GetFlags().signalize(::mus::midi::EndOfTrack);
            m_smti.m_tkLength = m_tkPosition;
         }
      }
      else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
      {
         try
         {
            allocate_add_up(1);
         }
         catch(memory_exception * pe)
         {
            pe->Delete();
            return ::mus::midi::ENoMemory;
         }
         *m_hpbImage++ = bEvent;
      }
      else
      {
         ASSERT(FALSE);
      }

      cbEvent = eventMidi.GetParamSize();

      if(!(dwUsed = SetVDWord(cbEvent)))
      {
         return ::mus::midi::ENoMemory;
      }

      m_hpbImage     += dwUsed;

      try
      {
         allocate_add_up(cbEvent);
      }
      catch(memory_exception * pe)
      {
         pe->Delete();
         return ::mus::midi::ENoMemory;
      }

      memcpy(m_hpbImage, eventMidi.GetParam(), cbEvent);

      m_hpbImage     += cbEvent;
   }

   m_estate = StateOnDelta;

   return ::mus::midi::Success;
}

int midi_track::GetCurrentEvent()
{
    return m_iCurrentEvent;
}

void midi_track::WorkDeleteEvent()
{
    m_trackWorkStorage.remove_at(m_iWorkCurrentEvent);
///    m_iCurrentEvent--;
}


/*midi_track & midi_track::operator =(midi_track &eventSrc)
{
    m_bAutoAllocation = eventSrc.m_bAutoAllocation;
    m_ptracks->m_uchRunningStatus = eventSrc.m_ptracks->m_uchRunningStatus;
    m_cbLeft = eventSrc.m_cbLeft;
    //m_dwAllocation = eventSrc.m_dwAllocation;
//    m_dwAllocationAddUp = eventSrc.m_dwAllocationAddUp;
    m_dwUsed = eventSrc.m_dwUsed;
    m_event = eventSrc.m_event;
    m_fdwTrack = eventSrc.m_fdwTrack;
    if(eventSrc.m_hpbAllocation != NULL &&
        eventSrc.m_bAutoAllocation)
    {
        allocate(eventSrc.m_dwAllocation);
        memcpy(m_hpbAllocation, eventSrc.m_hpbAllocation, m_dwAllocation);
    }
    m_hpbEventImage = m_hpbAllocation + (eventSrc.m_hpbEventImage - eventSrc.m_hpbAllocation);
    m_hpbImage = m_hpbAllocation + (eventSrc.m_hpbImage - eventSrc.m_hpbAllocation);
    m_iCurrentEvent = eventSrc.m_iCurrentEvent;
    m_idxTrack = eventSrc.m_idxTrack;
    m_estate = eventSrc.m_estate;
    m_ptracks = eventSrc.m_ptracks;
    m_smti = eventSrc.m_smti;
    m_tkDelta = eventSrc.m_tkDelta;
    m_tkPosition = eventSrc.m_tkPosition;
    m_trackWorkStorage = eventSrc.m_trackWorkStorage;

    return *this;

}*/

::mus::midi::e_file_result midi_track::get_position(imedia::position & tkPosition, imedia::position tkMax)
{
   UNREFERENCED_PARAMETER(tkMax);
   ASSERT(m_estate == StateOnDelta);

   imedia::position tkDelta;
    VMSRESULT vmsr;
   vmsr = GetDelta(tkDelta);
   if (::mus::midi::Success != vmsr)
   {
      _GetFlags().signalize(::mus::midi::EndOfTrack);
      return ::mus::midi::SEndOfTrack;
   }
    if(_GetFlags().is_signalized(::mus::midi::EndOfTrack))
    {
       return ::mus::midi::SEndOfTrack;
    }
    tkPosition = m_tkPosition + tkDelta;
    return ::mus::midi::Success;

}

/*int midi_track::GetFlags()
{
    return m_fdwTrack;
}*/

imedia::position midi_track::get_position()
{
   if(m_estate == StateOnDelta || m_estate == StateOnEventRead)
   {
      return m_tkPosition;
   }
   else
   {
      return m_tkPosition + m_tkDelta;
   }
}

int midi_track::GetMidiTrackIndex()
{
    seek_begin();
    int iFirstTrack = -1;
    int iTrack = -1;
    while(::mus::midi::Success == ReadEvent(0x7fffffff, true))
    {
        midi_event_v001 & event = GetEvent();
        if(event.GetFullType() < ::mus::midi::SysEx)
        {
            iTrack = event._GetTrack();
            if(iFirstTrack < 0)
            {
                iFirstTrack = iTrack;
            }
            else
            {
                if(iTrack != iFirstTrack)
                {
                    return -2;
                }
            }
        }
    }
    return iFirstTrack;

}

::mus::midi::e_file_result midi_track::MoveNext()
{
   if(m_estate != StateOnEventRead)
   {
      return ::mus::midi::EFail;
   }

   if(_GetFlags().is_signalized(::mus::midi::EndOfTrack))
   {
      return ::mus::midi::SEndOfTrack;
   }

   m_iCurrentEvent++;
   m_estate = StateOnDelta;

   return ::mus::midi::Success;

}

::mus::midi::e_file_result midi_track::ReadEvent()
{
   return ReadEvent(0x7fffffff, true);
}

::mus::midi::e_file_result midi_track::GetDelta(imedia::position &tkDeltaParam)
{
   imedia::position tkDelta;

   switch(m_estate)
   {
   case StateOnDelta:
      {
         if (!(m_dwUsed = GetVDWord((DWORD *) &tkDelta)))
         {
            TRACE("Hit end of track w/o end marker!\n");
            return ::mus::midi::EInvalidFile;
         }
         tkDeltaParam = tkDelta;
         return ::mus::midi::Success;
      }
   case StateOnEvent:
      {
         tkDeltaParam = m_tkDelta;
         return ::mus::midi::Success;
      }
   case StateOnEventRead:
      {
         tkDeltaParam = m_tkDelta;
         return ::mus::midi::Success;
      }
   }
   ASSERT(FALSE);
   return ::mus::midi::EFail;



}

::mus::midi::e_file_result midi_track::SeekXFLyricsHeader()
{
   ::mus::midi::e_file_result               smfrc;
   imedia::position               tkLastDelta = 0 ;


    if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
    {
        return ::mus::midi::SEndOfFile;
    }

   while(true)
   {
      smfrc = ReadEvent(0, TRUE);
      if(::mus::midi::Success != smfrc)
         break;
      if(m_tkPosition > 0)
      {
         smfrc = ::mus::midi::SNotFound;
         break;
      }
      if ((::mus::midi::Meta == m_event.GetFullType()) &&
         (::mus::xf::MetaLyricsHeader == m_event.GetMetaType()))
      {
         string str;
         gen::international::MultiByteToOEM(
            gen::international::CodePageLatin1,
            str, (const char *) m_event.GetParam(), 6);
         if(str.CollateNoCase("$Lyrc:") == 0)
         {
                return ::mus::midi::Success;
         }
      }

        smfrc = MoveNext();
        if (::mus::midi::Success != smfrc)
         break;
    }
   return smfrc;

}

::mus::midi::e_file_result midi_track::ReadXFLyricsHeader(::mus::xf_lyrics_id *pxflh)
{
   if (::mus::midi::Meta != m_event.GetFullType())
      return ::mus::midi::EFail;
   if(::mus::xf::MetaLyricsHeader != m_event.GetMetaType())
      return ::mus::midi::EFail;
   string_tokenizer tokenizer;
   string strToken;
   gen::international::multibyte_to_utf8(
      gen::international::CodePageLatin1,
      tokenizer, (const char *) m_event.GetParam(), m_event.GetParamSize());
   if(!tokenizer.GetNextToken(strToken, ":"))
      return ::mus::midi::EFail;
   if(strToken.CollateNoCase("$Lyrc") != 0)
      return ::mus::midi::EFail;

   string strMidiChannel;
   if(!tokenizer.GetNextToken(strMidiChannel, ":"))
      return ::mus::midi::EFail;

   string strOffsetValue;
   if(!tokenizer.GetNextToken(strOffsetValue, ":"))
      return ::mus::midi::EFail;

   string strLanguage;
   tokenizer.GetNextToken(strLanguage, ":");

   pxflh->m_strLanguage = strLanguage;


   tokenizer.Restart(strMidiChannel);
   string strChannel;
   while(tokenizer.GetNextToken(strChannel, ","))
   {
      pxflh->m_MelodyTracks.add(_tcstoul(strChannel, NULL, 10));
   }

   pxflh->m_tkDisplayOffset = _tcstoul(strOffsetValue, NULL, 10);


   return ::mus::midi::Success;


}

::mus::midi::e_file_result midi_track::WorkReadXFTokens(UINT uiCodePage, stringa &  tokena, imedia::position_array & positiona, int_array & iaTokenLine)
{

   string str;
   tokena.remove_all();
   positiona.remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   midi_event_v008 * pevent;
   int iLine = 0;

   if(!_WorkIsEOT())
   {
      while(TRUE)
      {

         _WorkGetEvent(pevent, tkMax, TRUE);

         if ((::mus::midi::Meta == pevent->GetFullType()) &&
         (::mus::xf::MetaLyric == pevent->GetMetaType()))
         {
            gen::international::multibyte_to_utf8(uiCodePage, str, (const char * ) pevent->GetParam(), pevent->GetParamSize());
            if(str[0] == '<')
            {
               iLine++;
            }
            TRACE("%s\n", str);
            tokena.add(str);
            iaTokenLine.add(iLine);
            positiona.add(imedia::position(m_tkPosition));
         }

         smfrc = _WorkMoveNext();

         if (::mus::midi::Success != smfrc)
         {
            break;
         }

      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

/*::mus::midi::e_file_result midi_track::WorkReadXFTokens(
   stringa &  tokena,
   imedia::position_array & positiona,
   int_array & iaTokenLine)
{
   string str;
   string str;
    tokena.remove_all();
    positiona.remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   midi_event_v008 * pevent;
   int iLine = 0;

   if(!_WorkIsEOT())
   {
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);

         if ((::mus::midi::Meta == pevent->GetFullType()) &&
         (::mus::xf::MetaLyric == pevent->GetMetaType()))
         {
         LPTSTR lpsz = str.GetBuffer(pevent->GetParamSize() + 1);
         memcpy(lpsz, pevent->GetParam(), pevent->GetParamSize());
         lpsz[pevent->GetParamSize()] = '\0';
         if(lpsz[0] == '<')
         {
            iLine++;
         }
         str.ReleaseBuffer();
         TRACE("%s\n", str);
         gen::international::ACPToUnicode(str, str);
         tokena.add(str);
         iaTokenLine.add(iLine);
         positiona.add(imedia::position(m_tkPosition));
         }


         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
         break;
         }
      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}*/

::mus::midi::e_file_result midi_track::WriteXFLyricTrack(
   stringa &  tokena,
   imedia::position_array & positiona)
{

   BYTE XFLYRICSHEADER[] = "$Lyrc:1:270:L1";
   BYTE CUEPOINTSOLO[] = "&s";
   string str;
   imedia::position tkPosition;

   midi_event_v008 event;



   WorkSeekBegin();

   event.SetFullType(::mus::midi::Meta);
   event.SetMetaType(::mus::midi::MetaXFLyricsHeader);
   event.SetParam(XFLYRICSHEADER, sizeof(XFLYRICSHEADER) - 1);
   event.SetDelta(0);
   WorkWriteEvent(event);

   event.SetFullType(::mus::midi::Meta);
   event.SetMetaType(::mus::midi::MetaCuePoint);
   event.SetParam(CUEPOINTSOLO, sizeof(CUEPOINTSOLO) - 1);
   WorkWriteEvent(event);

   string strToken;
   for(int j = 0; j < tokena.get_size(); j++)
   {
      strToken = tokena.element_at(j);
      tkPosition = positiona.get_at(j);
      if(strToken.Mid(0, 1).Compare("\\") == 0)
      {
         str = "<";
         str += strToken.Mid(1);
      }
      else if(strToken.Mid(0, 1).Compare("/") == 0)
      {
         str = "/";
         WorkWriteXFLyricEvent(str, tkPosition);
         str = strToken.Mid(1);
      }
      else
      {
         str = strToken;
      }
      str.replace(" ", "^");
      WorkWriteXFLyricEvent(str, tkPosition);
   }
   event.SetFullType(::mus::midi::Meta);
   event.SetMetaType(::mus::midi::MetaEOT);
   event.SetParam(NULL, 0);
   WorkWriteEvent(event);
   m_trackWorkStorage.m_chunkHeader.fourccType = FOURCC_XFKM;

   return ::mus::midi::Success;

}

::mus::midi::e_file_result midi_track::WorkReadEmptyXFTokens(
   stringa &  tokena,
   imedia::position_array & positiona)
{
   string str;
    tokena.remove_all();
    positiona.remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   midi_event_v008 * pevent;

   if(!_WorkIsEOT())
   {
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);

         if (::mus::midi::NoteOn == pevent->GetType_() &&
         pevent->GetNoteVelocity() != 0)
         {
         //LPTSTR lpsz = str.GetBuffer(pevent->GetParamSize() + 1);
           // LPTSTR lpsz = "---";
         //memcpy(lpsz, pevent->GetParam(), pevent->GetParamSize());
         //lpsz[pevent->GetParamSize()] = '\0';
         //str.ReleaseBuffer();
            str = "---";
         TRACE("%s\n", str);
         tokena.add(str);
         positiona.add(imedia::position(m_tkPosition));
         }


         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
         break;
         }
      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::WorkReadXFTokens(UINT uiCodePage, stringa &  tokena, imedia::position_array * lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   string str;
   tokena.remove_all();
   lptkaTicks->remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   midi_event_v008 * pevent;

   if(!_WorkIsEOT())
   {
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);

         if((::mus::midi::Meta == pevent->GetFullType()) &&
            (::mus::xf::MetaLyric == pevent->GetMetaType()))
         {
            gen::international::multibyte_to_utf8(uiCodePage, str, (const char * ) pevent->GetParam(), pevent->GetParamSize());
            tokena.add(str);
            lptkaTicks->add(m_tkPosition);
         }


         smfrc = _WorkMoveNext();

         if (::mus::midi::Success != smfrc)
         {
         break;
         }

      }
   }


   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

/*::mus::midi::e_file_result midi_track::WorkReadAnsiXFTokens(stringa &  tokena, imedia::position_array *   lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   string str;
   tokena.remove_all();
   lptkaTicks->remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   midi_event_v008 * pevent;

   if(!_WorkIsEOT())
   {
      while(TRUE)
      {

         _WorkGetEvent(pevent, tkMax, TRUE);

         if ((::mus::midi::Meta == pevent->GetFullType()) &&
            (::mus::xf::MetaLyric == pevent->GetMetaType()))
         {
            gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, str, (const char *) pevent->GetParam(), pevent->GetParamSize());
            TRACE("%s\n", str);
            tokena.add(str);
            lptkaTicks->add(m_tkPosition);
         }

         smfrc =  WorkMoveNext();

         if (::mus::midi::Success != smfrc)
         {
            break;
         }

      }
   }

   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::WorkReadShiftJisXFTokens(stringa &  tokena, imedia::position_array *   lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   tokena.remove_all();
   lptkaTicks->remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   string str;
   midi_event_v008 * pevent;

   if(!_WorkIsEOT())
   {
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);
         if ((::mus::midi::Meta == pevent->GetFullType()) &&
         (::mus::xf::MetaLyric == pevent->GetMetaType()))
         {
            gen::international::MultiByteToUnicode(
               gen::international::CodePageShiftJIS,
               str,
               (const char *) pevent->GetParam(),
               pevent->GetParamSize());
            TRACE("%s\n", str);
            tokena.add(str);
            lptkaTicks->add(m_tkPosition);
         }
         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
         break;
         }
      }
   }

   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}*/

::mus::midi::e_file_result midi_track::WorkReadKarTokens(
   stringa &  tokena,
   imedia::position_array *   lptkaTicks)
{

   ASSERT(lptkaTicks != NULL);
   string str;
    tokena.remove_all();
    lptkaTicks->remove_all();
//    CMidiEvent m_event;
   imedia::position tkMax = m_smti.m_tkLength;
   imedia::position tkLastPosition = 0;
   imedia::position tkPosition = 0;
   int i;
   for(i = 0; i < m_trackWorkStorage.GetEventCount(); i++)
   {
      if(tkPosition > 0)
         break;
      midi_event_v008 & event = m_trackWorkStorage.EventAt(i);
      tkPosition = event._GetPosition();
      if((::mus::midi::Meta == event.GetFullType()) &&
         (::mus::midi::MetaKarLyric == event.GetMetaType()))
      {
         LPTSTR lpsz = str.GetBufferSetLength(event.GetParamSize() + 1);
         memcpy(lpsz, event.GetParam(), event.GetParamSize());
         lpsz[event.GetParamSize()] = '\0';
         str.ReleaseBuffer();
/*         gen::international::MultiByteToUnicode(
            CodePageLatin1,
            str,
            (char *) event.GetParam(), event.GetParamSize());*/
         if(!str.is_empty())
         {
            if(str.operator[](0) != '@')
            {
               tokena.add(str);
               lptkaTicks->add(tkPosition);
            }
         }
      }
   }
   for(; i < m_trackWorkStorage.GetEventCount(); i++)
   {
      midi_event_v008 & event = m_trackWorkStorage.EventAt(i);
      tkPosition = event._GetPosition();
      if ((::mus::midi::Meta == event.GetFullType()) &&
         (::mus::midi::MetaKarLyric == event.GetMetaType()))
      {
         LPTSTR lpsz = str.GetBufferSetLength(event.GetParamSize() + 1);
         memcpy(lpsz, event.GetParam(), event.GetParamSize());
         lpsz[event.GetParamSize()] = '\0';
         str.ReleaseBuffer();
/*
         gen::international::MultiByteToUnicode(
            CodePageLatin1,
            str, (char *) event.GetParam(), event.GetParamSize());*/
         tokena.add(str);
         lptkaTicks->add(tkPosition);
      }
   }

   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}

::mus::midi::e_file_result midi_track::WorkReadTune1000Tokens(
   stringa &  tokena,
   imedia::position_array *lptkaTicks)
{
   ASSERT(lptkaTicks != NULL);
   string str;
   tokena.remove_all();
   lptkaTicks->remove_all();

   imedia::position tkMax = m_smti.m_tkLength;
   imedia::position tkLastPosition = 0;

   imedia::position tkPosition = 0;

   for(int i = 0; i < m_trackWorkStorage.GetEventCount(); i++)
   {
      midi_event_v008 & event = m_trackWorkStorage.EventAt(i);
      tkPosition = event._GetPosition();
      if ((::mus::midi::Meta == event.GetFullType()) &&
         (::mus::midi::MetaLyric == event.GetMetaType()))
      {
         LPTSTR lpsz = str.GetBufferSetLength(event.GetParamSize() + 1);
         memcpy(lpsz, event.GetParam(), event.GetParamSize());
         lpsz[event.GetParamSize()] = '\0';
         str.ReleaseBuffer();
/*         gen::international::MultiByteToUnicode(
            CodePageLatin1,
            str, (char *) event.GetParam(), event.GetParamSize());*/
         tokena.add(str);
         lptkaTicks->add(tkPosition);
      }
   }

   return tokena.get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;

}



::mus::midi::e_file_result midi_track::WorkMoveNext()
{
   m_estate = StateOnEventRead;

   m_iWorkCurrentEvent++;
   if(m_iWorkCurrentEvent >= m_trackWorkStorage.GetEventCount())
   {
      m_bWorkTrackEnd = true;
      _GetFlags().signalize(::mus::midi::EndOfFile);
      m_smti.m_tkLength = m_tkPosition;
      return ::mus::midi::SEndOfTrack;
   }

   m_tkPosition  += m_trackWorkStorage.EventAt(m_iWorkCurrentEvent).GetDelta();

   return ::mus::midi::Success;

}


void midi_track::WorkGetEvent(
   midi_event_base *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(tkMax);
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
   ASSERT(pevent != NULL);
   ASSERT(m_estate == StateOnEventRead);
   ASSERT(!_WorkIsEOT());
   pevent = &m_trackWorkStorage.EventAt(m_iWorkCurrentEvent);
}

void midi_track::WorkGetEvent(
   midi_event_v008 *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(tkMax);
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
   ASSERT(m_estate == StateOnEventRead);
   ASSERT(!_WorkIsEOT());
   pevent = &m_trackWorkStorage.EventAt(m_iWorkCurrentEvent);
}


::mus::midi::e_file_result   midi_track::WorkSeekBegin()
{
   m_iWorkCurrentEvent  = -1;
   m_tkPosition         = 0;
   m_bWorkTrackEnd      = false;
   return _WorkMoveNext();
}

::mus::midi::e_file_result   midi_track::WorkSeekEnd()
{
   m_iWorkCurrentEvent = m_trackWorkStorage.GetEventCount();
   m_bWorkTrackEnd = true;
   m_estate = StateOnEventRead;
   _GetFlags().signalize(::mus::midi::EndOfFile);
   m_tkPosition = m_smti.m_tkLength;
   if(m_trackWorkStorage.GetEventCount() <= 0)
   {
      m_tkPosition = 0;
   }
   else
   {
      m_tkPosition = m_trackWorkStorage.EventAt(m_trackWorkStorage.GetEventCount() - 1).get_position();
   }
   return ::mus::midi::SEndOfTrack;
}

::mus::midi::e_file_result midi_track::WorkGetNoteOnOffEventsV1(midi_events_v1 *pEvents, int iTrack, bool bAnyTrack)
{
   midi_event_v008 * pevent;
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   if(!_WorkIsEOT())
   {
       if(bAnyTrack)
      {
         while(TRUE)
         {
            _WorkGetEvent(pevent, tkMax, TRUE);

            if ((::mus::midi::NoteOn == pevent->_GetType()) ||
               (::mus::midi::NoteOff == pevent->_GetType() ))
            {

               pEvents->AddEvent(pevent, m_tkPosition);
            }
            smfrc = _WorkMoveNext();
            if (::mus::midi::Success != smfrc)
            {
               break;
            }
         }
      }
      else
      {
         while(TRUE)
         {
            _WorkGetEvent(pevent, tkMax, TRUE);

            if (((::mus::midi::NoteOn == pevent->_GetType()) ||
               (::mus::midi::NoteOff == pevent->_GetType())) &&
               (iTrack == pevent->_GetTrack()))
            {
               pEvents->AddEvent(pevent, m_tkPosition);
            }
            smfrc = _WorkMoveNext();
            if (::mus::midi::Success != smfrc)
            {
               break;
            }
         }
      }
   }
   return smfrc;

}


// it returns in pevents, note on, note off,
// and maximum and minimum peaks of pitch bend

::mus::midi::e_file_result midi_track::WorkGetLevel2Events(midi_events_v1 *pevents, int iTrack, bool bAnyTrack)
{
   midi_event_v008 * pevent;
   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   int iPitchBend;
   int iLastPitchBend = 0;
   enum EDirection
   {
      Up,
      Down,
   } edirection = Up;
   midi_event_v001 eventLastPitchBend;
   if(!_WorkIsEOT())
   {
      if(bAnyTrack)
      {
         while(TRUE)
         {
            _WorkGetEvent(pevent, tkMax, TRUE);

            if ((::mus::midi::NoteOn == pevent->_GetType()) ||
               (::mus::midi::NoteOff == pevent->_GetType() ))
            {

               pevents->AddEvent(pevent, m_tkPosition);
            }
            else if (::mus::midi::PitchBend == pevent->_GetType())
            {
               iPitchBend = pevent->GetPitchBendLevel();
               if(edirection == Up)
               {
                  if(iPitchBend < iLastPitchBend)
                  {
                     edirection = Down;
//                     pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
                     pevents->AddEvent(pevent, m_tkPosition);
                  }
                  else if(iPitchBend == 0
                     && iLastPitchBend != 0)
                  {
                     pevents->AddEvent(pevent, m_tkPosition);
                  }

               }
               else if(edirection == Down)
               {
                  if(iPitchBend > iLastPitchBend)
                  {
                     edirection = Up;
//                     pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
                     pevents->AddEvent(pevent, m_tkPosition);
                  }
                  else if(iPitchBend == 0
                     && iLastPitchBend != 0)
                  {
                     pevents->AddEvent(pevent, m_tkPosition);
                  }
               }
               eventLastPitchBend = *pevent;
               iLastPitchBend = iPitchBend;
            }

            smfrc = _WorkMoveNext();
            if (::mus::midi::Success != smfrc)
            {
               break;
            }
         }
      }
      else
      {
         while(TRUE)
         {
            _WorkGetEvent(pevent, tkMax, TRUE);


            if (iTrack == pevent->_GetTrack())
            {
               if(((::mus::midi::NoteOn == pevent->_GetType()) ||
                  (::mus::midi::NoteOff == pevent->_GetType())))
               {
                  pevents->AddEvent(pevent, m_tkPosition);
               }
               else if (::mus::midi::PitchBend == pevent->_GetType())
               {
                  iPitchBend = pevent->GetPitchBendLevel();
                  if(edirection == Up)
                  {
                     if(iPitchBend < iLastPitchBend)
                     {
                        edirection = Down;
                        //pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
                        pevents->AddEvent(pevent, m_tkPosition);
                     }
                     else if(iPitchBend == 0
                        && iLastPitchBend != 0)
                     {
                        pevents->AddEvent(pevent, m_tkPosition);
                     }

                  }
                  else if(edirection == Down)
                  {
                     if(iPitchBend > iLastPitchBend)
                     {
                        edirection = Up;
                        //pevents->AddEvent(&eventLastPitchBend, tkLastPosition);
                        pevents->AddEvent(pevent, m_tkPosition);
                     }
                     else if(iPitchBend == 0
                        && iLastPitchBend != 0)
                     {
                        pevents->AddEvent(pevent, m_tkPosition);
                     }
                  }
                  eventLastPitchBend = *pevent;
                  iLastPitchBend = iPitchBend;
               }
            }
            smfrc = _WorkMoveNext();
            if (::mus::midi::Success != smfrc)
            {
               break;
            }
         }
      }
   }
   return smfrc;

}

::mus::midi::e_file_result midi_track::WorkGetStandardEventsV1(midi_events_v1 *pEvents, int iFilter, int iTrack, bool bAnyTrack)
{
   midi_event_v008 * pevent;

   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;
   if(bAnyTrack)
   {
      if(_WorkIsEOT())
         ::mus::midi::SEndOfTrack;
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);

         if(iFilter == ::mus::midi::NoteOn)
         {
            if(::mus::midi::NoteOn == pevent->_GetType()
            && pevent->GetNoteVelocity() != 0)
            {
               pEvents->AddEvent(pevent);
            }
         }
         else
         {
            if(iFilter == pevent->_GetType())
            {
               pEvents->AddEvent(pevent);
            }
         }

         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   else
   {
      if(_WorkIsEOT())
         ::mus::midi::SEndOfTrack;
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);

         if(iTrack == pevent->_GetTrack())
         {
            if(iFilter == ::mus::midi::NoteOn)
            {
               if(::mus::midi::NoteOn == pevent->_GetType()
               && pevent->GetNoteVelocity() != 0)
               {
                  pEvents->AddEvent(pevent);
               }
            }
            else
            {
               if (iFilter == pevent->_GetType())
               {

                  pEvents->AddEvent(pevent);
               }
            }
         }

         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}

::mus::midi::e_file_result midi_track::WorkGetStandardEventsV1OnlyMelodic(midi_events_v1 *pEvents, int iFilter, int iTrack, bool bAnyTrack)
{
   midi_event_v008 * pevent;

   imedia::position tkMax = m_smti.m_tkLength;
   ::mus::midi::e_file_result smfrc;
   imedia::position tkLastPosition = 0;

   if(bAnyTrack)
   {
      if(_WorkIsEOT())
         ::mus::midi::SEndOfTrack;
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);


         if ((iFilter == pevent->_GetType()))
         {
            pEvents->AddEvent(pevent);
         }

         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   else
   {
      if(_WorkIsEOT())
         ::mus::midi::SEndOfTrack;
      while(TRUE)
      {
         _WorkGetEvent(pevent, tkMax, TRUE);

         if ((iFilter == pevent->_GetType()) &&
            (iTrack == pevent->_GetTrack() ))
         {

            pEvents->AddEvent(pevent);
         }

         smfrc = _WorkMoveNext();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}

midi_track & midi_track::operator =(const midi_track &track)
{
   m_bAutoAllocation = track.m_bAutoAllocation;
   m_cbLeft = track.m_cbLeft;
   m_dwUsed = track.m_dwUsed;
   m_estate = track.m_estate;
   m_event = track.m_event;
   m_flags = track.m_flags;
   m_hpbEventImage = track.m_hpbEventImage;
   m_hpbImage = track.m_hpbImage;
   m_iCurrentEvent = track.m_iCurrentEvent;
   m_idxTrack = track.m_idxTrack;
   m_iIndex = track.m_iIndex;
   m_iWorkCurrentEvent = track.m_iWorkCurrentEvent;
   m_memstorageHelper.copy_from(&track.m_memstorageHelper);
   m_ptracks = track.m_ptracks;
   m_smti = track.m_smti;
   m_tkDelta = track.m_tkDelta;
   m_tkPosition = track.m_tkPosition;
   m_trackWorkStorage = track.m_trackWorkStorage;
   primitive::memory_container::operator =(track);
   keep_pointer((void **) &m_hpbImage);
   keep_pointer((void **) &m_hpbEventImage);
   return *this;
}

void midi_track::allocate(DWORD dwNewLength)
{
   ASSERT(m_bAutoAllocation);
   if(m_hpbImage == NULL)
   {
      m_hpbImage = (byte *) sizeof(CHUNKHDR);
   }
   primitive::memory_container::allocate(dwNewLength);
   m_smti.m_cbLength = primitive::memory_container::get_size() - sizeof(CHUNKHDR);
}

::mus::midi::e_file_result midi_track::WorkWriteXFInfoHeader(const char * pSongName, XFInfoHeader * pXfih, XFInfoHeaderLS * pXfihls)
{

//   ::mus::midi::e_file_result               smfrc;
   imedia::position               tkLastDelta = 0 ;
   primitive::memory   memstorage;

   if(m_tkPosition != 0)
   {
      return   ::mus::midi::EInvalidTkPosition;
   }

   m_event.SetDelta(0);
   if(pSongName != NULL)
   {
      m_event.SetFullType(::mus::midi::Meta);
      m_event.SetMetaType(::mus::xf::MetaSongName);
      memstorage.allocate(gen::international::Utf8ToMultiByteCount(gen::international::CodePageLatin1, pSongName));
      m_event.SetParam((byte *) memstorage.get_data(), memstorage.get_size() - 1);
      gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, (char *) m_event.GetParam(), m_event.GetParamSize(), pSongName);
      WorkWriteEvent();
   }
   if(pXfih != NULL)
   {
      m_event.SetFullType(::mus::midi::Meta);
      m_event.SetMetaType(::mus::xf::MetaXFInfoHdr);
      string str;
      pXfih->ToData(str);
      gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, memstorage, str);
      m_event.SetParam((byte *) memstorage.get_data(), memstorage.get_size() - 1);
      WorkWriteEvent();
   }
   if(pXfihls != NULL)
   {
      m_event.SetFullType(::mus::midi::Meta);
      m_event.SetMetaType(::mus::xf::MetaXFInfoHdr);
      string str;
      pXfihls->ToData(str);
      memstorage.allocate(gen::international::Utf8ToMultiByteCount(gen::international::CodePageLatin1, str));
      m_event.SetParam((byte *) memstorage.get_data(), memstorage.get_size() - 1);
      gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, (char *) m_event.GetParam(), m_event.GetParamSize(), str);
      WorkWriteEvent();
   }
   return ::mus::midi::Success;
}

// event position is set to the current track position
// track position is updated accordingly to the event delta
// so the delta must have been filled correctly.
::mus::midi::e_file_result midi_track::WorkWriteEvent()
{
   m_tkPosition += m_event.GetDelta();
   m_event.SetPosition(get_position());
   m_trackWorkStorage.add(m_event);
   return ::mus::midi::Success;
}

// event position is set to the current track position
// track position is updated accordingly to the event delta
// so the delta must have been filled correctly.
::mus::midi::e_file_result midi_track::WorkWriteEvent(midi_event_v008 & event)
{
   m_tkPosition += event.GetDelta();
   m_trackWorkStorage.add(event);
   return ::mus::midi::Success;
}

/*
::mus::midi::e_file_result midi_track::WorkWriteXFLyricEvent(string &str, imedia::position tkPosition)
{
   ::mus::midi::e_file_result smfrc;
   if(tkPosition < m_tkPosition)
      m_event.SetDelta(0);
   else
      m_event.SetDelta(tkPosition - m_tkPosition);
   m_event.SetFullType(::mus::midi::Meta);
   m_event.SetMetaType(::mus::xf::MetaLyric);

   gen::international::UnicodeToMultiByte(gen::international::CodePageLatin1, m_memstorageHelper, str);
   m_event.SetParam((byte *) m_memstorageHelper.get_data(),
      m_memstorageHelper.get_size() - 1);
   smfrc = WorkWriteEvent();
   return smfrc;
}
*/

::mus::midi::e_file_result midi_track::WorkWriteXFLyricEvent(string &str, imedia::position tkPosition)
{
   ::mus::midi::e_file_result smfrc;
   if(tkPosition < m_tkPosition)
      m_event.SetDelta(0);
   else
      m_event.SetDelta(tkPosition - m_tkPosition);
   m_event.SetFullType(::mus::midi::Meta);
   m_event.SetMetaType(::mus::xf::MetaLyric);
   m_memstorageHelper.allocate(str.get_length());
   m_event.SetParam((byte *) m_memstorageHelper.get_data(),
      m_memstorageHelper.get_size());
   memcpy(
      (char *) m_event.GetParam() ,
      (const char *) str,
      m_event.GetParamSize());
   smfrc = WorkWriteEvent();
   return smfrc;
}

void midi_track::WorkClear()
{
   m_trackWorkStorage.clear();
}

::mus::midi::e_file_result midi_track::WorkSeekXFLyricsHeader()
{
   ::mus::midi::e_file_result               smfrc;
   imedia::position               tkLastDelta = 0 ;
   midi_event_v008 * pevent;

   if (_GetFlags().is_signalized(::mus::midi::EndOfFile))
   {
      return ::mus::midi::SEndOfFile;
   }

   if(_WorkIsEOT())
   {
      return ::mus::midi::SEndOfFile;
   }

   while(TRUE)
   {
      _WorkGetEvent(pevent, 0, TRUE);
      if(m_tkPosition > 0)
      {
         smfrc = ::mus::midi::SNotFound;
         break;
      }
      if ((::mus::midi::Meta == pevent->GetFullType()) &&
         (::mus::xf::MetaLyricsHeader == pevent->GetMetaType()))
      {
         string str;
         gen::international::MultiByteToOEM(
            gen::international::CodePageLatin1,
            str, (const char *) pevent->GetParam(), 6);
         if(str.CollateNoCase("$Lyrc:") == 0)
         {
                return ::mus::midi::Success;
         }
      }

        smfrc = _WorkMoveNext();
        if (::mus::midi::Success != smfrc)
         break;
    }
   return smfrc;

}


::mus::midi::e_file_result midi_track::WorkReadXFLyricsHeader(::mus::xf_lyrics_id *pxflh)
{
   midi_event_v008 * pevent;
   WorkGetEvent(pevent, 0, TRUE);
   if (::mus::midi::Meta != pevent->GetFullType())
      return ::mus::midi::EFail;
   if(::mus::xf::MetaLyricsHeader != pevent->GetMetaType())
      return ::mus::midi::EFail;
   string_tokenizer tokenizer;
   string strToken;
   gen::international::multibyte_to_utf8(gen::international::CodePageLatin1, tokenizer, (const char *) pevent->GetParam(), pevent->GetParamSize());
   if(!tokenizer.GetNextToken(strToken, ":"))
      return ::mus::midi::EFail;
   if(strToken.CollateNoCase("$Lyrc") != 0)
      return ::mus::midi::EFail;

   string strMidiChannel;
   if(!tokenizer.GetNextToken(strMidiChannel, ":"))
      return ::mus::midi::EFail;

   string strOffsetValue;
   if(!tokenizer.GetNextToken(strOffsetValue, ":"))
      return ::mus::midi::EFail;

   string strLanguage;
   tokenizer.GetNextToken(strLanguage, ":");

   pxflh->m_strLanguage = strLanguage;


   tokenizer.Restart(strMidiChannel);
   string strChannel;
   while(tokenizer.GetNextToken(strChannel, ","))
   {
      pxflh->m_MelodyTracks.add(strtoul(strChannel, NULL, 10));
   }

   pxflh->m_tkDisplayOffset = strtoul(strOffsetValue, NULL, 10);


   return ::mus::midi::Success;


}

::mus::midi::file_flags & midi_track::GetFlags()
{
   return m_flags;
}

midi_track_base::e_type midi_track::get_type()
{
   return TypeMidi;
}

bool midi_track::WorkIsEOT()
{
   return m_bWorkTrackEnd;

}

::mus::midi::e_file_result midi_track::WorkSetEOT()
{
   m_bWorkTrackEnd = true;
   _GetFlags().signalize(::mus::midi::EndOfFile);
   m_smti.m_tkLength = m_tkPosition;
   return ::mus::midi::SEndOfTrack;
}

::mus::midi::e_file_result midi_track::_SeekBegin(bool bWork)
{
   if(bWork)
   {
      return WorkSeekBegin();
   }
   else
   {
      return seek_begin();
   }
}

void midi_track::_GetEvent(
   bool bWork,
   midi_event_v008 *&pevent,
   imedia::position tkMax,
   bool bTkMaxInclusive
   )
{
   if(bWork)
   {
      _WorkGetEvent(
         pevent,
         tkMax,
         bTkMaxInclusive);
   }
   else
   {
      if(m_estate == StateOnDelta
         || m_estate == StateOnEvent)
      {
         ReadEvent();
      }
      m_event8 = m_event;
      pevent = &m_event8;
   }
}

::mus::midi::e_file_result midi_track::_MoveNext(bool bWork)
{
   if(bWork)
   {
      return WorkMoveNext();
   }
   else
   {
      ::mus::midi::e_file_result smfr = MoveNext();
      if(smfr != ::mus::midi::Success)
         return smfr;
      return ReadEvent();
   }

}

midi_track::State midi_track::GetState()
   {
      return m_estate;
   }


midi_event_v001 & midi_track::GetEvent()
   {
      return m_event;
   }


void midi_track::_WorkGetEvent(
   midi_event_v008 *&    pevent,
   imedia::position                  tkMax,
   BOOL                  bTkMaxInclusive)
{
   UNREFERENCED_PARAMETER(tkMax);
   UNREFERENCED_PARAMETER(bTkMaxInclusive);
   ASSERT(m_estate == StateOnEventRead);
   ASSERT(!_WorkIsEOT());
   pevent = &m_trackWorkStorage.EventAt(m_iWorkCurrentEvent);
}

imedia::position midi_track::_WorkGetPosition()
{
   ASSERT(m_estate == StateOnEventRead);
   ASSERT(!_WorkIsEOT());
   return m_tkPosition;
}


::mus::midi::e_file_result midi_track::_WorkMoveNext()
{
   m_estate = StateOnEventRead;
   m_iWorkCurrentEvent++;
   if(m_iWorkCurrentEvent >= m_trackWorkStorage.GetEventCount())
   {
      return WorkSetEOT();
   }
   m_tkPosition = m_tkPosition + m_trackWorkStorage.EventAt(m_iWorkCurrentEvent)._GetDelta();
   return ::mus::midi::Success;
}

bool midi_track::_WorkIsEOT()
{
   return m_bWorkTrackEnd;
}

::mus::midi::file_flags & midi_track::_GetFlags()
{
   return m_flags;
}

imedia::position midi_track::WorkGetPosition()
{
   return m_tkPosition;
}

