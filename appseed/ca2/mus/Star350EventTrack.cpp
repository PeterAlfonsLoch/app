#include "StdAfx.h"


// IMPLEMENT_DYNAMIC(Star350EventTrack, Star350TrackBase);

Star350EventTrack::Star350EventTrack()

{
   m_ptracks = NULL;

   m_idxTrack = 0;

   m_tkPosition = 0;
   m_cbLeft = 0;
   m_hpbImage = NULL;
   m_bRunningStatus = 0;

   m_fdwTrack = 0;

   m_smti.m_tkLength = 0;
   m_smti.m_cbLength = 0;

   m_nState = StateOnDelta;

   m_bAutoAllocation = FALSE;
   m_dwAllocation = 0;
   m_dwAllocationAddUp = 512;
   m_hpbAllocation = NULL;
//   m_hpbMirrorAllocation = NULL;

   m_tkDelta = 0;

    m_pevent = new Star350EventV001();
    m_ptrackWorkStorage = new Star350TrackV008();
}

Star350EventTrack::~Star350EventTrack()
{
    if(m_pevent != NULL)
    {
        delete m_pevent;
        m_pevent = NULL;
    }

    if(m_ptrackWorkStorage != NULL)
    {
        delete m_ptrackWorkStorage;
        m_ptrackWorkStorage = NULL;
    }

   m_ptracks = NULL;

   m_idxTrack = 0;

   m_tkPosition = 0;
   m_cbLeft = 0;
   m_hpbImage = NULL;
   m_bRunningStatus = 0;

   m_fdwTrack = 0;

   m_smti.m_tkLength = 0;
   m_smti.m_cbLength = 0;
}

void Star350EventTrack::Initialize(Star350Tracks * pTracks)
{
    m_ptracks = pTracks;
}

SMFRESULT Star350EventTrack::ReadDelta()
{
   imedia::position tkDelta;

   ASSERT(m_nState == StateOnDelta);

   m_hpbEventImage = m_hpbImage;

   if (!(m_dwUsed = GetVDWord((DWORD *) &tkDelta)))
   {
      TRACE("Hit end of track w/o end marker!\n");
      return (SMFRESULT) ::mus::midi::EInvalidFile;
   }

   m_tkDelta = tkDelta;
   m_hpbImage += m_dwUsed;
   m_cbLeft -= m_dwUsed;
   m_nState = StateOnEvent;

   return ::mus::midi::Success;


}

VMSRESULT Star350EventTrack::GetEvent(
        midi_event_base * pEvent,
      imedia::position   tkMax,
      BOOL   bTkMaxInclusive)
{
    VMSRESULT  vmsr;
    if(VMSR_SUCCESS != (vmsr = ReadEvent(tkMax, bTkMaxInclusive)))
    {
        return vmsr;
    }
    *pEvent = * (midi_event_base *) m_pevent;
    return VMSR_SUCCESS;
}


/******************************************************************************
*
* smfGetNextEvent
*
* read the next m_event from the given spfile->
*
* pSmf                      - File to read the m_event from.
*
* pEvent                    - Pointer to an m_event structure which will receive
*                             basic information about the m_pevent->
*
* tkMax                     - Tick destination. An attempt to read past this
*                             position in the file will fail.
*
* Returns
*   ::mus::midi::Success The events were successfully read.
*   ::mus::midi::SEndOfFile There are no more events to read in this track.
*   ::mus::midi::SReachedTkMax No m_event was read because <p tkMax> was reached.
*   ::mus::midi::EInvalidFile A disk or parse error occured on the spfile->
*
* This is the lowest level of parsing for a raw MIDI stream. The basic
* information about one m_event in the file will be returned in pEvent.
*
* Merging data from all tracks into one stream is performed here.
*
* m_pevent->tkDelta will contain the tick delta for the m_pevent->
*
* m_pevent->abEvent will contain a description of the m_pevent->
*  m_pevent->abEvent[0] will contain
*    F0 or F7 for a System Exclusive message.
*    FF for a MIDI file meta m_pevent->
*    The status byte of any other MIDI message. (Running status will
*    be tracked and expanded).
*
* m_pevent->cbParm will contain the number of bytes of paramter data
*   which is still in the file behind the m_event header already read.
*   This data may be read with <f smfGetTrackEventData>. Any unread
*   data will be skipped on the next call to <f smfGetNextTrackEvent>.
*
* Channel messages (0x8? - 0xE?) will always be returned fully in
*   m_pevent->abEvent.
*
*  Meta events will contain the meta type in m_pevent->abEvent[1].
*
*  System exclusive events will contain only an 0xF0 or 0xF7 in
*    m_pevent->abEvent[0].
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
SMFRESULT Star350EventTrack::ReadEvent(
   imedia::position   tkMax,
   BOOL   bTkMaxInclusive)
{
//   imedia::position                   tkEventDelta;
   BYTE                    bEvent;
   DWORD                   dwGotTotal;
   DWORD                   dwGot;
   DWORD                   cbEvent;
    SMFRESULT               smfrc;

    if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }

//   ASSERT(m_nState == StateOnEvent);

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short m_event, which is most cases.
    */
    if (m_cbLeft < 3)
    {
        return (SMFRESULT) ::mus::midi::EInvalidFile;
    }


    m_tkPosition += m_tkDelta;

   m_pevent->m_tkPosition   =  m_tkPosition;
   m_pevent->m_tkDelta      = m_tkDelta;
   m_pevent->SetImage(m_hpbEventImage);

   if(bTkMaxInclusive)
   {
      if (m_tkPosition > tkMax)
      {
         return (SMFRESULT) ::mus::midi::SReachedTkMax;
      }
   }
   else
   {
      if (m_tkPosition >= tkMax)
      {
         return ::mus::midi::SReachedTkMax;
      }
   }


//    m_tkPosition = m_tkPosition;

    bEvent = *m_hpbImage++;

    if (::mus::midi::Msg > bEvent)
    {
        if (0 == m_bRunningStatus)
        {
            return (SMFRESULT) ::mus::midi::EInvalidFile;
        }

        dwGotTotal = 1;
        m_pevent->m_abEvent[0] = m_bRunningStatus;
        m_pevent->m_abEvent[1] = bEvent;
        if (3 == ::mus::midi::GetMessageLen(m_bRunningStatus))
        {
            m_pevent->m_abEvent[2] = *m_hpbImage++;
            dwGotTotal++;
        }
    }
    else if (::mus::midi::SysEx > bEvent)
    {
        m_bRunningStatus = bEvent;

        dwGotTotal = 2;
        m_pevent->m_abEvent[0] = bEvent;
        m_pevent->m_abEvent[1] = *m_hpbImage++;
        if (3 == ::mus::midi::GetMessageLen(bEvent))
        {
            m_pevent->m_abEvent[2] = *m_hpbImage++;
            dwGotTotal++;
        }
    }
    else
    {
        //m_bRunningStatus = 0;
        if (::mus::midi::Meta == bEvent)
        {
            m_pevent->m_abEvent[0] = ::mus::midi::Meta;
            if (::mus::midi::MetaEOT == (m_pevent->m_abEvent[1] = *m_hpbImage++))
            {
                m_fdwTrack |= SMF_TF_EOT;
            m_smti.m_tkLength = m_tkPosition;
            }

            dwGotTotal = 2;
        }
        else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
        {
            m_pevent->m_abEvent[0] = bEvent;
            dwGotTotal = 1;
        }
        else
        {
            return (SMFRESULT) ::mus::midi::EInvalidFile;
        }

        if (0 == (dwGot = GetVDWord( m_cbLeft - 2, &cbEvent)))
        {
            return (SMFRESULT) ::mus::midi::EInvalidFile;
        }

        m_hpbImage  += dwGot;
        dwGotTotal  += dwGot;

        if (dwGotTotal + cbEvent > m_cbLeft)
        {
            return (SMFRESULT) ::mus::midi::EInvalidFile;
        }

        m_pevent->m_cbParm  = cbEvent;
        m_pevent->m_hpbParm = m_hpbImage;

        m_hpbImage += cbEvent;
        dwGotTotal += cbEvent;
    }

    ASSERT(m_cbLeft >= dwGotTotal);

    m_cbLeft -= dwGotTotal;
   m_dwUsed = dwGotTotal;
   m_nState = StateOnDelta;

   m_pevent->m_cbImage = m_hpbImage - m_hpbEventImage;
    m_iCurrentEvent++;

    return ::mus::midi::Success;
}

/******************************************************************************
*
* smfGetVDword
*
* Reads a var length DWORD from the given spfile->
*
* hpbImage                  - Pointer to the first byte of the VDWORD.
*
* dwLeft                    - Bytes left in image
*
* pDw                       - Pointer to a DWORD to store the result in.
*                             track.
*
* Returns the number of bytes consumed from the stream.
*
* A var length DWORD stored in a MIDI file contains one or more
* bytes. Each byte except the last has the high bit set; only the
* low 7 bits are significant.
*
*****************************************************************************/
DWORD Star350EventTrack::GetVDWord(
   DWORD * pDw)
{
    return GetVDWord(m_cbLeft, pDw);
}

DWORD Star350EventTrack::GetVDWord(
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

DWORD Star350EventTrack::SetVDWord(
   DWORD dwLeft,
   DWORD dw)
{
    DWORD                   dwUsed  = 0;
   byte *               hpbImage = m_hpbImage;
   DWORD               dwBuffer;
//   CUDWordBytes            udwb;

   ASSERT(!m_bAutoAllocation);
    ASSERT(hpbImage != NULL);
   ASSERT(dw <= 0x0fffffff);

//   udwb.dw = dw;

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



//    pDw = 0;

  //  do
    //{
//        if (!dwLeft)
  //      {
    //        return 0;
      //  }

//        b = *hpbImage++;
  //      dwLeft--;
    //    dwUsed++;

//        *pDw = (*pDw << 7) | (b & 0x7F);
  //  } while (b&0x80);

    return dwUsed;
}


DWORD Star350EventTrack::SetVDWord(
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
   if(!allocate_add_up(dwUsed))
      return 0;
   byte *   hpbImage = m_hpbImage;
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

//#ifdef _UNICODE
         /*string *pStr;
           int result;
         int bufferSize = 1;
         //LPTSTR wideCharStr = (LPTSTR) malloc(1 * sizeof(char));
         LPTSTR wideCharStr = new char;
         result = MultiByteToWideChar(
         CP_ACP,         // code page
         MB_COMPOSITE,         // character-type options
         (const char *) m_pevent->hpbParm, // address of string to ::collection::map
         m_pevent->cbParm,      // number of bytes in string
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
         (const char *) m_pevent->hpbParm, // address of string to ::collection::map
         m_pevent->cbParm,      // number of bytes in string
         wideCharStr,  // address of wide-character buffer
         0       // size of buffer
         );
         //wideCharStr = (LPTSTR) malloc(bufferSize * sizeof(char));

         wideCharStr = new char[bufferSize];
         result = MultiByteToWideChar(
         CP_ACP,         // code page
         MB_COMPOSITE,         // character-type options
         (const char *) m_pevent->hpbParm, // address of string to ::collection::map
         m_pevent->cbParm,      // number of bytes in string
         wideCharStr,  // address of wide-character buffer
         bufferSize       // size of buffer
         );
            pStr = new string(wideCharStr, result);
         delete wideCharStr;
         }*/






/*SMFRESULT Star350EventTrack::GetNextXFInfoHeader(XFInfoHeader * pXfih)
{
   ASSERT(pXfih != NULL);
   //XFInfoHeader * pXfih = NULL;
   SMFRESULT smfrc;
   if(::mus::midi::Success == (smfrc = seek(::mus::midi::SeekXFInfoHeader)))
   {
      string_tokenizer str;
      International
         ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
      //pXfih = new XFInfoHeader();
      pXfih->FromData(str);
      TRACE("****GetXFInfoHeader");
      TRACE("Date: %s\n", pXfih->m_strDate);
      TRACE("Country: %s\n", pXfih->m_strCountry);
      TRACE("Category: %s\n", pXfih->m_strCategory);
      TRACE("Beat: %s\n", pXfih->m_strBeat);
      TRACE("Composer: %s\n", pXfih->m_straComposer.get_format_string("/"));
      TRACE("Lyricist: %s\n", pXfih->m_straLyricist.get_format_string("/"));
      TRACE("Arranger: %s\n", pXfih->m_straArranger.get_format_string("/"));
      TRACE("Performer: %s\n", pXfih->m_straPerformer.get_format_string("/"));
      TRACE("ID: %s\n", pXfih->m_id);
      return ::mus::midi::Success;
   }
   return smfrc;
}*/

/*SMFRESULT Star350EventTrack::GetNextXFInfoHeaderLS(XFInfoHeaderLS * pXfihls)
{
   ASSERT(pXfihls != NULL);
   SMFRESULT smfrc;
   if(::mus::midi::Success == (smfrc = seek(::mus::midi::SeekXFInfoHeader)))
   {
      string_tokenizer str;
      International
         ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
      pXfihls->FromData(str);
      return ::mus::midi::Success;
   }
   return smfrc;
}*/

/*SMFRESULT Star350EventTrack::GetNextXFInfoHeaderLS(XFInfoHeaderLS * pXfihls, const string &strLanguage)
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
}*/

/*SMFRESULT Star350EventTrack::GetNextXFSongName(string &str)
{
   //LPTSTR pSongName = NULL;
   SMFRESULT smfrc;
   if(::mus::midi::Success == (smfrc = seek(::mus::midi::SeekXFSongName)))
   {
   //   string str;
      International
         ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
   //   pSongName = _tcsdup(str);
   //   TRACE("Song Name: %s\n", pSongName);
      return ::mus::midi::Success;
   }
   return smfrc;
}*/



/*SMFRESULT Star350EventTrack::ReadXFInfoHeader_(
   LPTSTR *ppSongName,
    XFInfoHeader **ppXfih,
    XFInfoHeaderLS **ppXfihls)
{
   ASSERT(*ppSongName == NULL);
   ASSERT(*ppXfih == NULL);
   ASSERT(*ppXfihls == NULL);

//    PSMF                    pSmf = (PSMF)hSmf;
   SMFRESULT               smfrc;
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
      return   ::mus::midi::InvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
/*    if (m_fdwTrack & ::mus::midi::EndOfFile)
    {
        return ::mus::midi::SEndOfFile;
    }

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
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
            ** seek point and reaching end-of-spfile->
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
  /*          if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: ReadXFInfoHeader_() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::xf::MetaSongName == m_pevent->GetMetaType()))
        {
         string str;
         International
            ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
         *ppSongName = _tcsdup(str);
         TRACE("Song Name: %s\n", *ppSongName);
         okSongName = TRUE;
        }
      else if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::xf::MetaXFInfoHdr == m_pevent->GetMetaType()))
        {
         string_tokenizer str;
         International
            ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
         if(str.Mid(0, 4).Compare("XFhd") == 0)
         {
            *ppXfih = new XFInfoHeader();
            (*ppXfih)->FromData(str);
            //if(iHi < 0)
            //   goto XF_Lyrics_Parse_End;
            //m_LyricsDisplayOffset = _ttoi(str.Mid(iLo + 1, iHi - iLo - 1));
//         XF_IH_Parse_End:;
            TRACE("****GetXFInfoHeader");
            TRACE("Date: %s\n", (*ppXfih)->m_strDate);
            TRACE("Country: %s\n", (*ppXfih)->m_strCountry);
            TRACE("Category: %s\n", (*ppXfih)->m_strCategory);
            TRACE("Beat: %s\n", (*ppXfih)->m_strBeat);
            TRACE("Composer: %s\n", (*ppXfih)->m_straComposer.get_format_string("/"));
            TRACE("Lyricist: %s\n", (*ppXfih)->m_straLyricist.get_format_string("/"));
            TRACE("Arranger: %s\n", (*ppXfih)->m_straArranger.get_format_string("/"));
            TRACE("Performer: %s\n", (*ppXfih)->m_straPerformer.get_format_string("/"));
            TRACE("ID: %s\n", (*ppXfih)->m_id);
         }
         else if(str.Mid(0, 4).Compare("XFln") == 0)
         {
            *ppXfihls = new XFInfoHeaderLS();
            (*ppXfihls)->FromData(str);
            //if(iHi < 0)
            //   goto XF_Lyrics_Parse_End;
            //m_LyricsDisplayOffset = _ttoi(str.Mid(iLo + 1, iHi - iLo - 1));
//XF_IHLS_Parse_End:;
         okInfoHeaderLS = TRUE;
         }
        }
        smfrc = ReadDelta();
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
    /*        if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: ReadXFInfoHeader_() -> %u", (UINT)smfrc);
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
   return (m_fdwTrack & ::mus::midi::EndOfFile) ? ::mus::midi::SEndOfFile : ::mus::midi::Success;
}*/

/*SMFRESULT Star350EventTrack::WriteXFInfoHeader(
   const char * pSongName,
    XFInfoHeader *pXfih,
    XFInfoHeaderLS *pXfihls)
{
//    PSMF                    pSmf = (PSMF)hSmf;
   SMFRESULT               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;


   if(m_tkPosition != 0)
   {
      return   ::mus::midi::InvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
/*    if (m_fdwTrack & ::mus::midi::EndOfFile)
    {
        return ::mus::midi::SEndOfFile;
    }

   m_pevent->m_tkDelta = 0;
   if(pSongName != NULL)
   {
      m_pevent->SetFullType(::mus::midi::Meta);
      m_pevent->SetMetaType(::mus::xf::MetaSongName);
      m_pevent->m_hpbParm = (byte *)
         International
         ::UnicodeToAnsiDup(pSongName);
      m_pevent->m_cbParm = strlen((const char *)m_pevent->m_hpbParm);
      if((smfrc = WriteCompleteEvent(0x7fffffff, false)) != ::mus::midi::Success)
         return smfrc;
      delete m_pevent->m_hpbParm;
   }
   if(pXfih != NULL)
   {
      m_pevent->SetFullType(::mus::midi::Meta);
      m_pevent->SetMetaType(::mus::xf::MetaXFInfoHdr);
      string str;
      pXfih->ToData(str);
      m_pevent->m_hpbParm = (byte *)
         International
         ::UnicodeToAnsiDup(str);
      m_pevent->m_cbParm = strlen((const char *) m_pevent->m_hpbParm);
      if((smfrc = WriteCompleteEvent(0x7fffffff, false)) != ::mus::midi::Success)
         return smfrc;

      TRACE("****WriteXFInfoHeader");
      TRACE("Date: %s\n", (char *) m_pevent->m_hpbParm);
      delete m_pevent->m_hpbParm;
   }
   if(pXfihls != NULL)
   {
      m_pevent->SetFullType(::mus::midi::Meta);
      m_pevent->SetMetaType(::mus::xf::MetaXFInfoHdr);
      string str;
      pXfihls->ToData(str);
      m_pevent->m_hpbParm = (byte *)
         International
         ::UnicodeToAnsiDup(str);
      m_pevent->m_cbParm = strlen((const char *) m_pevent->m_hpbParm);
      if((smfrc = WriteCompleteEvent(0x7fffffff, false)) != ::mus::midi::Success)
         return smfrc;
      delete m_pevent->m_hpbParm;
   }
   return ::mus::midi::Success;
}*/


/*SMFRESULT Star350EventTrack::ReadKarTokens(
   StringArray *  lpstraTokens,
   imedia::position_array *   lptkaTicks)
{
   ASSERT(lpstraTokens != NULL);
   ASSERT(lptkaTicks != NULL);
    lpstraTokens->remove_all();
    lptkaTicks->remove_all();
//    CMidiEvent m_event;
   imedia::position tkMax = m_smti.m_tkLength;
   SMFRESULT smfrc;
   imedia::position tkLastPosition = 0;

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }

    while(m_tkPosition == 0)
    {
        smfrc = ReadEvent(tkMax, TRUE);
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
                m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: ReadKarTokens() -> %u", (UINT)smfrc);
            break;
        }


       if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
            (::mus::midi::MetaKarLyric == m_pevent->GetMetaType()))
        {
#ifdef _UNICODE

         gen::international::Latin1ToString(str, (char *) m_pevent->hpbParm, m_pevent->cbParm);
#else
         string str((const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
#endif
            if(!str.is_empty())
            {
             if(str.operator[](0) != '@')
             {
             lpstraTokens->add(str);
             lptkaTicks->add(m_tkPosition);
             }
            }
        }
       smfrc = ReadDelta();
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
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-spfile->
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
                m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: ReadKarTokens() -> %u", (UINT)smfrc);
            break;
        }


       if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
            (::mus::midi::MetaKarLyric == m_pevent->GetMetaType()))
        {
#ifdef _UNICODE
         string str((char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
#else
         string str((const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
#endif

         lpstraTokens->add(str);
         lptkaTicks->add(m_tkPosition);
        }
       smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }


   return lpstraTokens->get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}*/

/*SMFRESULT Star350EventTrack::ReadXFTokens(
      StringArray *  lpstraTokens,
      imedia::position_array *   lptkaTicks)
{
   ASSERT(lpstraTokens != NULL);
   ASSERT(lptkaTicks != NULL);
    lpstraTokens->remove_all();
    lptkaTicks->remove_all();
   imedia::position tkMax = m_smti.m_tkLength;
   SMFRESULT smfrc;
   imedia::position tkLastPosition = 0;
   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }

    while(TRUE)
    {
        smfrc = ReadEvent(tkMax, TRUE);
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
                m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: ReadXFTokens() -> %u", (UINT)smfrc);
            break;
        }


       if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
         (::mus::xf::MetaLyric == m_pevent->GetMetaType()))
        {
//#ifdef _UNICODE
//         string *pStr = new string((char *) m_pevent->hpbParm, m_pevent->cbParm);
//#else
//         string *pStr = new string((const char *) m_pevent->hpbParm, m_pevent->cbParm);
//#endif
         string str;
         International
            ::Latin1ToString(
            str,
            (const char *) m_pevent->m_hpbParm,
            m_pevent->m_cbParm);
         TRACE("%s\n", str);
         lpstraTokens->add(str);
         lptkaTicks->add(m_tkPosition);
        }
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
    }


   return lpstraTokens->get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;
}*/

VMSRESULT   Star350EventTrack::seek_begin()
{
    if(m_bAutoAllocation)
   {
      m_tkPosition      = 0;
      m_cbLeft         = m_smti.m_cbLength;
      m_hpbImage         = m_hpbAllocation + sizeof(CHUNKHDR);
      m_bRunningStatus   = 0;
      m_fdwTrack         = 0;
      m_nState         = StateOnDelta;
      m_tkDelta         = 0;
        m_iCurrentEvent     = -1;
   }
   else
   {
        ASSERT(m_ptracks != NULL);
        Star350File *pfile  = m_ptracks->m_pfile;
        ASSERT(pfile != NULL);
      m_tkPosition        = 0;
      m_cbLeft            = m_smti.m_cbLength;
      m_hpbImage          = pfile->GetImage() + m_idxTrack;
      m_bRunningStatus    = 0;
      m_fdwTrack          = 0;
      m_nState         = StateOnDelta;
      m_tkDelta         = 0;
        m_iCurrentEvent     = -1;
   }
    return VMSR_SUCCESS;
}


BOOL Star350EventTrack::allocate(DWORD dwNewLength)
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
//            DWORD dw = GetLastError();
            TRACELASTERROR();
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
}

/*BOOL Star350EventTrack::AllocateMirror(DWORD dwNewLength)
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

SMFRESULT Star350EventTrack::WriteDelta()
{
   ASSERT(m_nState == StateOnDelta);
   ASSERT(m_bAutoAllocation);
   if (!(m_dwUsed = SetVDWord((DWORD) m_tkDelta)))
   {
      TRACE("No Memory Available.");
      return (SMFRESULT) ::mus::midi::ENoMemory;
   }

   m_hpbImage += m_dwUsed;
   m_cbLeft -= m_dwUsed;
   //m_smti.m_cbLength += m_dwUsed;
   m_nState = StateOnEvent;

   return ::mus::midi::Success;
}

void Star350EventTrack::SetAutoAllocation(BOOL bValue)
{
   if(bValue)
   {
      if(!m_bAutoAllocation)
      {
         ASSERT(m_hpbAllocation == NULL);
         ASSERT(m_dwAllocation == 0);
         ASSERT(!m_bAutoAllocation);
            byte * hpb = GetImage();
            DWORD cbSize = GetImageLength();
         m_bAutoAllocation = TRUE;
            if(hpb)
            {
                allocate(cbSize - sizeof(CHUNKHDR));
                memcpy(m_hpbAllocation, hpb, cbSize);
            }

      }
   }
   else
   {
      if(m_bAutoAllocation)
      {
         if(m_hpbAllocation != NULL)
         {
            free(m_hpbAllocation);
            m_hpbAllocation = NULL;
            m_dwAllocation = 0;
         }
      }
      m_bAutoAllocation = FALSE;
   }

}

SMFRESULT Star350EventTrack::WriteCompleteEvent(imedia::position tkMax, bool bUseEventPosition)
{

   ASSERT(m_nState == StateOnDelta);
   ASSERT(m_bAutoAllocation);

   BYTE                    bEvent;
   DWORD                   dwUsedTotal;
   DWORD                   dwUsed;
   DWORD                   cbEvent;
   SMFRESULT            smfrc;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short m_event, which is most cases.
    */

    if(bUseEventPosition)
    {
        ASSERT(m_pevent->m_tkPosition >= m_tkPosition);
       m_tkDelta = m_pevent->m_tkPosition - m_tkPosition;
    }
    else
    {
        m_tkDelta = m_pevent->m_tkDelta;
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

   bEvent = m_pevent->GetFullType();

   if(bEvent < ::mus::midi::Msg)
   {
      ASSERT(FALSE);
   }
   else if(bEvent == m_bRunningStatus)
   {
      if(!allocate_add_up(1))
         return (SMFRESULT) ::mus::midi::ENoMemory;
      dwUsedTotal = 1;
      *m_hpbImage++ = m_pevent->m_abEvent[1];
        if (3 == ::mus::midi::GetMessageLen(m_bRunningStatus))
        {
         if(!allocate_add_up(1))
            return (SMFRESULT) ::mus::midi::ENoMemory;
            *m_hpbImage++ = m_pevent->m_abEvent[2];
            dwUsedTotal++;
        }
   }
   else if(bEvent < ::mus::midi::SysEx)
   {
      m_bRunningStatus = bEvent;
      if(!allocate_add_up(2))
         return (SMFRESULT) ::mus::midi::ENoMemory;
      dwUsedTotal = 2;
      *m_hpbImage++ = bEvent;
      *m_hpbImage++ = m_pevent->m_abEvent[1];
        if (3 == ::mus::midi::GetMessageLen(m_bRunningStatus))
        {
         if(!allocate_add_up(1))
            return (SMFRESULT) ::mus::midi::ENoMemory;
            *m_hpbImage++ = m_pevent->m_abEvent[2];
            dwUsedTotal++;
        }
   }
    else
    {
        m_bRunningStatus = 0;
        if (::mus::midi::Meta == bEvent)
        {
         if(!allocate_add_up(2))
            return (SMFRESULT) ::mus::midi::ENoMemory;
         *m_hpbImage++ = ::mus::midi::Meta;
            if (::mus::midi::MetaEOT == (*m_hpbImage++ = m_pevent->GetMetaType()))
            {
                m_fdwTrack |= SMF_TF_EOT;
            m_smti.m_tkLength = m_tkPosition;
            }
            dwUsedTotal = 2;
        }
        else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
        {
         if(!allocate_add_up(1))
            return (SMFRESULT) ::mus::midi::ENoMemory;
            *m_hpbImage++ = bEvent;
            dwUsedTotal = 1;
        }
        else
        {
            ASSERT(FALSE);
        }

      cbEvent = m_pevent->m_cbParm;

      if(!(dwUsed = SetVDWord(cbEvent)))
      {
         return (SMFRESULT) ::mus::midi::ENoMemory;
      }

        m_hpbImage  += dwUsed;
        dwUsedTotal  += dwUsed;


      if(!allocate_add_up(cbEvent))
         return (SMFRESULT) ::mus::midi::ENoMemory;

      memcpy(m_hpbImage, m_pevent->m_hpbParm, cbEvent);

        m_hpbImage += cbEvent;
        dwUsedTotal += cbEvent;
    }

//   m_smti.m_cbLength += dwUsedTotal;
   m_nState = StateOnDelta;

   return ::mus::midi::Success;
}


SMFRESULT Star350EventTrack::copy(Star350EventTrack *ptrk)
{
   if(m_bAutoAllocation)
   {
      if(!allocate(ptrk->m_smti.m_cbLength))
         return (SMFRESULT) ::mus::midi::ENoMemory;
      byte * hpbImage = ptrk->m_ptracks->m_pfile->GetImage() + ptrk->m_idxTrack - sizeof(CHUNKHDR);
      memcpy(m_hpbAllocation, hpbImage, m_smti.m_cbLength + sizeof(CHUNKHDR));
      return Star350File::Success;
   }
   else
   {
      ASSERT(FALSE);
      return Star350File::FunctionNotSupported;
   }
}

/*SMFRESULT Star350EventTrack::WriteHeader(CHUNKHDR *pHdr)
{
   ASSERT(m_bAutoAllocation);
   ASSERT(m_hpbAllocation != NULL);
   memcpy(
      m_hpbAllocation,
      &pHdr->fourccType,
      sizeof(pHdr->fourccType));
   DWORD dw = pHdr->dwLength;
   dw = DWORDSWAP(dw);
   memcpy(
      m_hpbAllocation + sizeof(pHdr->fourccType),
      &dw,
      sizeof(pHdr->dwLength));
   return ::mus::midi::Success;
}*/

/*SMFRESULT Star350EventTrack::WriteHeaderLength()
{
   ASSERT(!m_bAutoAllocation);
   ASSERT(m_hpbAllocation == NULL);
   byte * hpbImage = GetImage();
   DWORD dw = m_smti.m_cbLength;
   dw = DWORDSWAP(dw);
   memcpy(
      hpbImage + sizeof(FOURCC),
      &dw,
      sizeof(DWORD));
   return ::mus::midi::Success;
}*/


/*SMFRESULT Star350EventTrack::WriteXFLyricEvent(string &str, imedia::position tkPosition)
{
   SMFRESULT smfrc;
   if(tkPosition < m_tkPosition)
      m_pevent->m_tkDelta = 0;
   else
      m_pevent->m_tkDelta = tkPosition - m_tkPosition;
   m_pevent->SetFullType(::mus::midi::Meta);
   m_pevent->SetMetaType(::mus::xf::MetaLyric);
#ifdef _UNICODE
   char * lpStr = gen::international::UnicodeToAnsiDup(str);
   m_pevent->m_hpbParm = (byte *) lpStr;
#else
   const char * lpStr = (const char *) str;
   m_pevent->m_hpbParm = (byte *) (const char *) lpStr;
#endif
   m_pevent->m_cbParm = str.get_length();
   smfrc = WriteCompleteEvent(0x7fffffff, false);
#ifdef _UNICODE
   delete lpStr;
#endif
   return smfrc;
}*/

DWORD Star350EventTrack::GetImageLength()
{
   return m_smti.m_cbLength + sizeof(CHUNKHDR);
}

byte * Star350EventTrack::GetAllocationImage()
{
   return m_hpbAllocation;
}

BOOL Star350EventTrack::allocate_add_up(DWORD dwAddUp)
{
   return allocate(m_smti.m_cbLength + dwAddUp);
}

SMFRESULT Star350EventTrack::copy(Star350EventTrack *pTrk, int iMode)
{
   SMFRESULT smfrc;
   Star350EventV001 *pEvent;
   imedia::position tkDelta;
   if(iMode == CopyNormal)
   {
      return copy(pTrk);
   }
   SetAutoAllocation();
   seek_begin();
    allocate(sizeof(CHUNKHDR));
    memcpy(GetImage(), pTrk->GetImage(), sizeof(CHUNKHDR));
   pTrk->seek_begin();
   pEvent = pTrk->m_pevent;
   tkDelta = 0;
    bool bCopy;
   while(TRUE)
   {
      if(pTrk->m_fdwTrack & SMF_TF_EOT)
         break;
      if(::mus::midi::Success != (smfrc = pTrk->ReadDelta()))
         return (SMFRESULT) ::mus::midi::EInvalidFile;
      pTrk->ReadEvent(0x7fffffff, TRUE);
        bCopy = true;
        if(bCopy)
        {
            if((iMode & CopyExcludeXFMetaLyrics) > 0)
          {
             if(pEvent->GetFullType() == ::mus::midi::Meta &&
                pEvent->GetMetaType() == ::mus::xf::MetaLyric)
             {
                    bCopy = false;
                }
            }
            if(bCopy)
            {
                if((iMode & CopyExcludeKarMetaLyrics) > 0)
              {
                if(pEvent->GetFullType() == ::mus::midi::Meta &&
                    pEvent->GetMetaType() == ::mus::midi::MetaKarLyric)
                 {
                        bCopy = false;
                    }
                }
            }
        }
        if(bCopy)
        {
           *m_pevent = *pEvent;
         m_pevent->m_tkDelta += tkDelta;
         tkDelta = 0;
         WriteCompleteEvent(0x7fffffff, false);
        }
      else
        {
            tkDelta += pEvent->m_tkDelta;
      }

   }
   CHUNKHDR chHdr;
   chHdr.fourccType = FOURCC_MTrk;
   chHdr.dwLength = m_smti.m_cbLength;
//   WriteHeader(&chHdr);
   return ::mus::midi::Success;
}

/*SMFRESULT Star350EventTrack::GetNextKarInfo(
   SoftKaraokeInfo *pKarI)
{
   ASSERT(pKarI != NULL);

//    PSMF                    pSmf = (PSMF)hSmf;
   SMFRESULT               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;
   bool               okSongName = false;
   bool               okAuthor = false;
    bool               okCopyright = false;
   int                  nTCount = 0;



   if(m_tkPosition != 0)
   {
      return   ::mus::midi::InvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
/*    if (m_fdwTrack & ::mus::midi::EndOfFile)
    {
        return ::mus::midi::SEndOfFile;
    }

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }
    while(TRUE)
    {
   //   if(nTCount >= 2)
   //      break;
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
  /*          if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: GetNextKarInfo() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
         (::mus::midi::MetaKarHeader == m_pevent->GetMetaType()))
        {

         string str;
         International
            ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
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
        smfrc = ReadDelta();
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
    /*        if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            m_fdwTrack |= ::mus::midi::EndOfFile;
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
   return okSongName || okAuthor || okCopyright ? ::mus::midi::Success:::mus::midi::SEndOfFile;
}*/


/*SMFRESULT Star350EventTrack::GetNextTune1000Info(
   CTune1000Info *pTune1000I)
{
   ASSERT(pTune1000I != NULL);

//    PSMF                    pSmf = (PSMF)hSmf;
   SMFRESULT               smfrc;
//    CMidiEvent              m_event;
   imedia::position               tkLastDelta = 0 ;
   bool               okSongName = FALSE;
   bool               okOther = FALSE;
   int                  nTCount = 0;



   if(m_tkPosition != 0)
   {
      return   ::mus::midi::InvalidTkPosition;
   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
/*    if (m_fdwTrack & ::mus::midi::EndOfFile)
    {
        return ::mus::midi::SEndOfFile;
    }

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }
    while(TRUE)
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: GetNextTune1000Info() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
         (::mus::midi::MetaTrackName == m_pevent->GetMetaType()
             ))
        {

         string str;
         International
            ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
         //if(str.Mid(0, 2).Compare("@T") == 0)
            if(true)
         {
            nTCount++;
//            if(*ppTune1000I == NULL)
//            {
//               TRACE("****GetKarInfoHeader");
//               *ppTune1000I = new SoftKaraokeInfo();
//            }
            if(nTCount == 1)
            {
               pTune1000I->m_strSongName = str;
               TRACE("Date: %s\n", pTune1000I->m_strSongName);
               okSongName = true;
//               (*ppTune1000I)->m_strSongName = str.Mid(2);
//               TRACE("Date: %s\n", (*ppTune1000I)->m_strSongName);
            }
            if(nTCount == 2)
            {
               pTune1000I->m_straOther.add_unique(str);
               TRACE("Date: %s\n", str);
               okOther = true;
//               (*ppTune1000I)->m_strOther = str.Mid(2);
//               TRACE("Date: %s\n", (*ppTune1000I)->m_strOther);
            }
         }
        }
        smfrc = ReadDelta();
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
//                m_fdwSMF |= ::mus::midi::EndOfFile;
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: GetNextTune1000Info() -> %u", (UINT)smfrc);
            break;
        }
      if(okSongName && okOther)
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
   return okSongName || okOther ? ::mus::midi::Success:::mus::midi::SEndOfFile;
}*/

/*SMFRESULT Star350EventTrack::GetStandardEventsV1(CMidiEventsV1 *pEvents, int iFilter, int iTrack, bool bAnyTrack)
{

   imedia::position tkMax = m_smti.m_tkLength;
   SMFRESULT smfrc;
   imedia::position tkLastPosition = 0;
   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }
   if(bAnyTrack)
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
               m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: GetStandardEventsV1() -> %u", (UINT)smfrc);
            break;
         }



         if ((iFilter == m_pevent->GetType_()))
         {
            pEvents->AddEvent(&m_event);
         }
         smfrc = ReadDelta();
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
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-spfile->
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
               m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: GetStandardEventsV1() -> %u", (UINT)smfrc);
            break;
         }



         if ((iFilter == m_pevent->GetType_()) &&
            (iTrack == m_pevent->GetTrack() ))
         {
            pEvents->AddEvent(&m_event);
         }
         smfrc = ReadDelta();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}*/

/*SMFRESULT Star350EventTrack::GetNoteOnOffEventsV1(CMidiEventsV1 *pEvents, int iTrack, bool bAnyTrack)
{

   imedia::position tkMax = m_smti.m_tkLength;
   SMFRESULT smfrc;
   imedia::position tkLastPosition = 0;
   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }
   if(bAnyTrack)
   {
      while(TRUE)
      {
         smfrc = ReadEvent(tkMax, TRUE);
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
               m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: GetNoteOnOffEventsV1() -> %u", (UINT)smfrc);
            break;
         }



         if ((::mus::midi::NoteOn == m_pevent->GetType_()) ||
            (::mus::midi::NoteOff == m_pevent->GetType_() ))
         {
            pEvents->AddEvent(&m_event);
         }
         smfrc = ReadDelta();
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
            /* smfGetNextEvent doesn't set this because smfSeek uses it
            ** as well and needs to distinguish between reaching the
            ** seek point and reaching end-of-spfile->
            **
            ** To the ::fontopus::user, however, we present the selection between
            ** their given tkBase and tkEnd as the entire file, therefore
            ** we want to translate this into EOF.
            */
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
               m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: GetNoteOnOffEventsV1() -> %u", (UINT)smfrc);
            break;
         }



         if (((::mus::midi::NoteOn == m_pevent->GetType_()) ||
            (::mus::midi::NoteOff == m_pevent->GetType_())) &&
            (iTrack == m_pevent->GetTrack()))
         {
            pEvents->AddEvent(&m_event);
         }
         smfrc = ReadDelta();
         if (::mus::midi::Success != smfrc)
         {
            break;
         }
      }
   }
   return smfrc;

}*/

/*bool Star350EventTrack::IsSoftKaraokeFile(CStdioFile * lpFile)
{
    //::mus::midi::file * pFile = m_pTracks->m_pFile;
   SMFRESULT               smfrc;
   imedia::position               tkLastDelta = 0 ;
   bool               bIsSoftKaraokeFile = false;
    bool                    bSoftKaraoke = false;


   //ASSERT(m_tkPosition == 0);
    seek_begin();
//   {
//      return   ::mus::midi::InvalidTkPosition;
//   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
/*   ASSERT(!(m_fdwTrack & ::mus::midi::EndOfFile));
    //if (m_fdwTrack & ::mus::midi::EndOfFile)
    //{
//        return ::mus::midi::SEndOfFile;
  //  }

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return false;
      }
   }
    int nArrobaCount = 0;
    while(TRUE)
    {
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: IsSoftKaraokeFile() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::midi::MetaTrackName == m_pevent->GetMetaType()))
        {
         string str;
         International
            ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
         if(str.CollateNoCase("Soft Karaoke") == 0)
         {
            bSoftKaraoke = true;
                if(lpFile != NULL)
                {
                    string strFormat;
                    strFormat.Format("%s\n", str);
                    lpFile->write_string(strFormat);
                }

         }
        }
        else if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::midi::MetaKarHeader == m_pevent->GetMetaType()))
        {

         string str;
         International
            ::Latin1ToString(str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
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
                if(lpFile != NULL)
                {
                    string strFormat;
                    strFormat.Format("%s\n", str);
                    lpFile->write_string(strFormat);
                }
            }

        }
        if(nArrobaCount > 0 && bSoftKaraoke)
            break;
        smfrc = ReadDelta();
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
/*            if (::mus::midi::SReachedTkMax == smfrc)
            {
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: IsSoftKaraokeFile() -> %u", (UINT)smfrc);
            break;
        }
    }
    bIsSoftKaraokeFile = nArrobaCount > 0 || bSoftKaraoke;
   return bIsSoftKaraokeFile;

}*/


/*BOOL Star350EventTrack::Mirror()
{
   memcpy(m_hpbMirrorAllocation, m_hpbAllocation, m_dwAllocation);
   return TRUE;
}

SMFRESULT Star350EventTrack::InsertCompleteEvent(imedia::position tkMax)
{

}*/

/*BOOL Star350EventTrack::ContainsEvent(midi_event_base *pEvent)
{
   byte * hpbImageStart = GetImage();
   byte * hpbImageEnd = hpbImageStart + m_smti.m_cbLength + sizeof(CHUNKHDR);
   return pEvent->GetImage() >= hpbImageStart &&
      pEvent->GetImage() < hpbImageEnd;
}*/

byte * Star350EventTrack::GetImage()
{
    if(m_bAutoAllocation)
    {
        return m_hpbAllocation;
    }
    else
    {
        if(m_ptracks == NULL)
            return NULL;
       ASSERT(m_ptracks != NULL);
        Star350File * pFile = m_ptracks->m_pfile;
        ASSERT(pFile != NULL);
       return pFile->GetImage() + m_idxTrack - sizeof(CHUNKHDR);
    }
}

SMFRESULT Star350EventTrack::seek(DWORD dwSeekWhat)
{
   SMFRESULT               smfrc;
   imedia::position               tkLastDelta = 0 ;
//   BOOL               okSongName = FALSE;
//   BOOL               okInfoHeader = FALSE;
//   BOOL               okInfoHeaderLS = FALSE;

//   if(m_tkPosition != 0)
//   {
//      return   ::mus::midi::InvalidTkPosition;
//   }

    if (m_fdwTrack & ::mus::midi::EndOfFile)
    {
        return ::mus::midi::SEndOfFile;
    }

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }
    while(TRUE)
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
            if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
               (::mus::xf::MetaSongName == m_pevent->GetMetaType()))
               return ::mus::midi::Success;
            break;
         }
      case ::mus::midi::SeekXFInfoHeader:
         {
            if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
            (::mus::xf::MetaXFInfoHdr == m_pevent->GetMetaType()))
            {
               string_tokenizer str;
               gen::international::MultiByteToOEM(
                  gen::international::CodePageLatin1,
                  str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
               if(str.Mid(0, 4).CompareNoCase("XFhd") == 0)
                  return ::mus::midi::Success;
            }
            break;
         }
      case ::mus::midi::SeekXFInfoHeaderLS:
         {
         if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::xf::MetaXFInfoHdr == m_pevent->GetMetaType()))
              {
               string_tokenizer str;
               gen::international::MultiByteToOEM(
                  gen::international::CodePageLatin1,
                  str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
               if(str.Mid(0, 4).Compare("XFln") == 0)
                  return ::mus::midi::Success;
            }
            break;
        case ::mus::midi::SeekKarID:
            if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::midi::MetaTrackName == m_pevent->GetMetaType()))
        {
         string str;
         gen::international::MultiByteToOEM(
            gen::international::CodePageLatin1,
            str, (const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
         if(str.CollateNoCase("Soft Karaoke") == 0)
         {
                return ::mus::midi::Success;
         }
        }
            break;
         }
      default:;
      }
        smfrc = ReadDelta();
        if (::mus::midi::Success != smfrc)
         break;
    }
   return smfrc;

}

VMSRESULT Star350EventTrack::WorkSeek(DWORD dwSeekWhat)
{
   SMFRESULT               smfrc = ::mus::midi::Success;
   imedia::position               tkLastDelta = 0 ;
//   BOOL               okSongName = FALSE;
//   BOOL               okInfoHeader = FALSE;
//   BOOL               okInfoHeaderLS = FALSE;

    if (m_fdwTrack & ::mus::midi::EndOfFile)
    {
        return ::mus::midi::SEndOfFile;
    }

    int iSize = m_ptrackWorkStorage->m_events.get_size() - 1;
    while(m_iCurrentEvent < iSize)
    {
        Star350EventV008 & event = m_ptrackWorkStorage->m_events.element_at(m_iCurrentEvent + 1);
        m_iCurrentEvent++;

        m_tkPosition += event.GetDelta();
      switch(dwSeekWhat)
      {
      case ::mus::midi::SeekXFSongName:
         {
            if ((::mus::midi::Meta == event.GetFullType()) &&
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
               gen::international::MultiByteToOEM(
                  gen::international::CodePageLatin1,
                  str, (const char *) event.GetParam(), event.GetParamSize());
               if(str.Mid(0, 4).CompareNoCase("XFhd") == 0)
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
               gen::international::MultiByteToOEM(
                  gen::international::CodePageLatin1,
                  str, (const char *) event.GetParam(), event.GetParamSize());
               if(str.Mid(0, 4).Compare("XFln") == 0)
                  return ::mus::midi::Success;
            }
                if(m_tkPosition > 0)
                    return ::mus::midi::SNotFound;
            break;
        case ::mus::midi::SeekKarID:
            if ((::mus::midi::Meta == event.GetFullType()) &&
          (::mus::midi::MetaTrackName == event.GetMetaType()))
        {
         string str;
            if(event.GetParam() != NULL)
            {
               gen::international::MultiByteToOEM(
                  gen::international::CodePageLatin1,
                  str, (const char *) event.GetParam(), event.GetParamSize());
             if(str.CollateNoCase("Soft Karaoke") == 0)
             {
                    return ::mus::midi::Success;
             }
            }
        }
                if(m_tkPosition > 0)
                    return ::mus::midi::SNotFound;
            break;
         }
      default:;
      }
//        if (::mus::midi::Success != smfrc)
//         break;
    }
   return smfrc;

}

bool Star350EventTrack::IsXFFile()
{
   SMFRESULT               smfrc;
   imedia::position               tkLastDelta = 0 ;
   bool               bIsXFFile = false;


   ASSERT(m_tkPosition == 0);
//   {
//      return   ::mus::midi::InvalidTkPosition;
//   }

    /*
    ** read events from the track and pack them into the buffer in polymsg
    ** format.
    **
    ** If a SysEx or meta would go over a buffer boundry, split it.
    */
   ASSERT(!(m_fdwTrack & ::mus::midi::EndOfFile));
    //if (m_fdwTrack & ::mus::midi::EndOfFile)
    //{
//        return ::mus::midi::SEndOfFile;
  //  }

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return false;
      }
   }
    while(TRUE)
    {
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
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
            break;
        }
      if(m_tkPosition > 0)
         break;

      if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
          (::mus::midi::MetaSeqSpecific == m_pevent->GetMetaType()))
        {
            if(m_pevent->m_hpbParm[0] == 0x43 && // YAMAHA ID
                m_pevent->m_hpbParm[1] == 0x7B && //
                m_pevent->m_hpbParm[2] == 0x00 && //
                m_pevent->m_hpbParm[3] == 0x58 && // X
                m_pevent->m_hpbParm[4] == 0x46 && // F
                m_pevent->m_hpbParm[5] == 0x30 && // 0
                m_pevent->m_hpbParm[6] == 0x32 )  // 2
            {
                bIsXFFile = true;
                break;
            }
        }
        smfrc = ReadDelta();
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
            m_fdwTrack |= ::mus::midi::EndOfFile;
            }

            TRACE( "smfReadEvents: IsXFFile() -> %u", (UINT)smfrc);
            break;
        }
    }
   return bIsXFFile;

}

SMFRESULT Star350EventTrack::ReadTune1000Tokens(stringa * lpstraTokens, imedia::position_array *lptkaTicks)
{
   ASSERT(lpstraTokens != NULL);
   ASSERT(lptkaTicks != NULL);

    imedia::position tkMax = m_smti.m_tkLength;
   SMFRESULT smfrc;
   imedia::position tkLastPosition = 0;

   if(m_nState == StateOnDelta)
   {
      smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }

    while(TRUE)
    {
        smfrc = ReadEvent(tkMax, TRUE);
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
                m_fdwTrack |= SMF_TF_EOT;
            }

            TRACE1("smfReadEvents: ReadTune1000Tokens() -> %u", (UINT)smfrc);
            break;
        }


       if ((::mus::midi::Meta == m_pevent->GetFullType()) &&
            (::mus::midi::MetaLyric == m_pevent->GetMetaType()))
        {
#ifdef _UNICODE
         string str((char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
#else
         string str((const char *) m_pevent->m_hpbParm, m_pevent->m_cbParm);
#endif

         lpstraTokens->add(str);
         lptkaTicks->add(m_tkPosition);
        }
       smfrc = ReadDelta();
      if (::mus::midi::Success != smfrc)
      {
         break;
      }
   }

   return lpstraTokens->get_size() == 0 ? ::mus::midi::SEndOfTrack : ::mus::midi::Success;

}

VMSRESULT Star350EventTrack::ReadEvent(Star350EventV008 &midiEvent)
{
   BYTE                    bEvent;
   int                     iGotTotal;
   DWORD                   dwGot;
   DWORD                   cbEvent;

    SMFRESULT               smfrc;
//if(m_nState == StateOnDelta)
//   {
    DWORD dwLeft = m_cbLeft;

    VMSRESULT vmsr = midiEvent.FromData(
        m_hpbImage,
        (LPINT) &dwLeft,
        Star350EventBase::EventType (0));

    if(VMS_FAILED(vmsr))
        return vmsr;

    iGotTotal = m_cbLeft - dwLeft;

   m_cbLeft = dwLeft;
   m_dwUsed = iGotTotal;
   m_nState = StateOnDelta;
   m_hpbImage += iGotTotal;
   m_iCurrentEvent++;

   return vmsr;


   midiEvent.clear();
   smfrc = ReadDelta();
   if (::mus::midi::Success != smfrc)
   {
      m_fdwTrack |= SMF_TF_EOT;
      return ::mus::midi::SEndOfTrack;
   }
//   }
    midiEvent.SetDelta(m_tkDelta);
    if (m_cbLeft < 3)
    {
        return VMSR_E_INVALIDFILE;
    }
//    byte *                  hpbImage = (byte *) m_hpbImage;
    bEvent = *m_hpbImage++;

    if (::mus::midi::Msg > bEvent)
    {
//        ASSERT(FALSE);
        iGotTotal = 1;
        midiEvent.SetFullType(m_bRunningStatus);
        midiEvent.SetChB1(bEvent);
        if (3 == ::mus::midi::GetMessageLen(m_bRunningStatus))
        {
            midiEvent.SetChB2(*m_hpbImage++);
            iGotTotal++;
        }
    }
    else if (::mus::midi::SysEx > bEvent)
    {
        m_bRunningStatus = bEvent;

        iGotTotal = 2;
        midiEvent.SetFullType(bEvent);
        midiEvent.SetChB1(*m_hpbImage++);
        if (3 == ::mus::midi::GetMessageLen(bEvent))
        {
            midiEvent.SetChB2(*m_hpbImage++);
            iGotTotal++;
        }
    }
    else
    {
        m_bRunningStatus = 0;
        if (::mus::midi::Meta == bEvent)
        {
            midiEvent.SetFullType(::mus::midi::Meta);
            midiEvent.SetMetaType(*m_hpbImage++);
            if (::mus::midi::MetaEOT == midiEvent.GetMetaType())
            {

                m_fdwTrack |= SMF_TF_EOT;
            m_smti.m_tkLength = m_tkPosition;
            }

            iGotTotal = 2;
        }
        else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
        {
            midiEvent.SetFullType(bEvent);
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
   m_nState = StateOnDelta;
    m_iCurrentEvent++;

    return VMSR_SUCCESS;

}

/*VMSRESULT Star350EventTrack::FromWorkStorage()
{
//    WriteHeader(&m_ptrackWorkStorage->m_chunkHeader);
    int iCount = m_ptrackWorkStorage->m_events.get_size();
    SetAutoAllocation();
    allocate(0);
    m_smti.m_cbLength = 0;
    seek_begin();

    for(int i = 0; i < iCount; i++)
    {
        WriteEvent(m_ptrackWorkStorage->m_events.element_at(i));
    }
    m_ptrackWorkStorage->m_chunkHeader.dwLength = m_smti.m_cbLength;
    WriteHeader(&m_ptrackWorkStorage->m_chunkHeader);

    return VMSR_SUCCESS;
}*/

VMSRESULT Star350EventTrack::ToWorkStorage()
{
    Star350EventV008 eventWork;
    int iCurrentEvent = m_iCurrentEvent;
    seek_begin();
    if(m_hpbAllocation == NULL)
    {
        memcpy(&m_ptrackWorkStorage->m_chunkHeader, GetImage(), sizeof(STAR350CHUNKHDR));
    }
    else
    {
        memcpy(&m_ptrackWorkStorage->m_chunkHeader, m_hpbAllocation, sizeof(STAR350CHUNKHDR));
    }
    m_ptrackWorkStorage->m_events.remove_all();
    VMSRESULT vmsr;
    while(VMS_SUCCEEDED(vmsr = ReadEvent(eventWork)))
    {
        if(vmsr != VMSR_S_SKIP)
        {
            m_ptrackWorkStorage->m_events.add(eventWork);
        }
        eventWork.clear();
    }

    m_iCurrentEvent = iCurrentEvent;
    return VMSR_SUCCESS;

}

Star350TrackV008 * Star350EventTrack::GetWorkTrack()
{
    return m_ptrackWorkStorage;
}

/*SMFRESULT Star350EventTrack::WriteEvent(CMidiEventV008 & eventMidi)
{

   ASSERT(m_nState == StateOnDelta);
   ASSERT(m_bAutoAllocation);

   BYTE                    bEvent;
   DWORD                   dwUsedTotal;
   DWORD                   dwUsed;
   DWORD                   cbEvent;
   SMFRESULT            smfrc;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short m_event, which is most cases.
    */

/*   m_tkDelta = eventMidi.GetDelta();

   if((smfrc = WriteDelta()) != ::mus::midi::Success)
   {
      return smfrc;
   }

   m_tkPosition += m_tkDelta;

//   if (m_tkPosition > tkMax)
  //  {
    //    return ::mus::midi::SReachedTkMax;
    //}

   bEvent = eventMidi.GetFullType();

   if(bEvent < ::mus::midi::Msg)
   {
      ASSERT(FALSE);
   }
   else if(bEvent == m_bRunningStatus)
   {
      if(!allocate_add_up(1))
         return ::mus::midi::ENoMemory;
      dwUsedTotal = 1;
      *m_hpbImage++ = eventMidi.GetChB1();
        if (3 == grbChanMsgLen[(m_bRunningStatus >> 4) & 0x0F])
        {
         if(!allocate_add_up(1))
            return ::mus::midi::ENoMemory;
            *m_hpbImage++ = eventMidi.GetChB2();
            dwUsedTotal++;
        }
   }
   else if(bEvent < ::mus::midi::SysEx)
   {
      m_bRunningStatus = bEvent;
      if(!allocate_add_up(2))
         return ::mus::midi::ENoMemory;
      dwUsedTotal = 2;
      *m_hpbImage++ = bEvent;
      *m_hpbImage++ = eventMidi.GetChB1();
        if (3 == grbChanMsgLen[(m_bRunningStatus >> 4) & 0x0F])
        {
         if(!allocate_add_up(1))
            return ::mus::midi::ENoMemory;
            *m_hpbImage++ = eventMidi.GetChB2();
            dwUsedTotal++;
        }
   }
    else
    {
        m_bRunningStatus = 0;
        if (::mus::midi::Meta == bEvent)
        {
         if(!allocate_add_up(2))
            return ::mus::midi::ENoMemory;
         *m_hpbImage++ = ::mus::midi::Meta;
            if (::mus::midi::MetaEOT == (*m_hpbImage++ = eventMidi.GetMetaType()))
            {
                m_fdwTrack |= SMF_TF_EOT;
            m_smti.m_tkLength = m_tkPosition;
            }
            dwUsedTotal = 2;
        }
        else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
        {
         if(!allocate_add_up(1))
            return ::mus::midi::ENoMemory;
            *m_hpbImage++ = bEvent;
            dwUsedTotal = 1;
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

        m_hpbImage  += dwUsed;
        dwUsedTotal  += dwUsed;


      if(!allocate_add_up(cbEvent))
         return ::mus::midi::ENoMemory;

      memcpy(m_hpbImage, eventMidi.GetParam(), cbEvent);

        m_hpbImage += cbEvent;
        dwUsedTotal += cbEvent;
    }

//   m_smti.m_cbLength += dwUsedTotal;
   m_nState = StateOnDelta;

   return ::mus::midi::Success;
}*/

int Star350EventTrack::GetCurrentEvent()
{
    return m_iCurrentEvent;
}

void Star350EventTrack::WorkDeleteEvent()
{
    m_ptrackWorkStorage->m_events.remove_at(m_iCurrentEvent);
    m_iCurrentEvent--;
}


Star350EventTrack & Star350EventTrack::operator =(Star350EventTrack &eventSrc)
{
    m_bAutoAllocation = eventSrc.m_bAutoAllocation;
    m_bRunningStatus = eventSrc.m_bRunningStatus;
    m_cbLeft = eventSrc.m_cbLeft;
    //m_dwAllocation = eventSrc.m_dwAllocation;
    m_dwAllocationAddUp = eventSrc.m_dwAllocationAddUp;
    m_dwUsed = eventSrc.m_dwUsed;
    *m_pevent = *eventSrc.m_pevent;
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
    m_nState = eventSrc.m_nState;
    m_ptracks = eventSrc.m_ptracks;
    m_smti = eventSrc.m_smti;
    m_tkDelta = eventSrc.m_tkDelta;
    m_tkPosition = eventSrc.m_tkPosition;
    *m_ptrackWorkStorage = *eventSrc.m_ptrackWorkStorage;

    return *this;

}

VMSRESULT Star350EventTrack::GetNextEventPosition(imedia::position *ptkPosition, imedia::position tkMax)
{
   UNREFERENCED_PARAMETER(tkMax);
   VMSRESULT vmsr;
   if(m_nState == StateOnDelta)
   {
      vmsr = ReadDelta();
      if (::mus::midi::Success != vmsr)
      {
         m_fdwTrack |= SMF_TF_EOT;
         return ::mus::midi::SEndOfTrack;
      }
   }
    if(m_fdwTrack & SMF_TF_EOT)
    {
       return ::mus::midi::SEndOfTrack;
    }
    *ptkPosition = m_tkPosition + m_tkDelta;
    return VMSR_SUCCESS;

}

int Star350EventTrack::GetFlags()
{
    return m_fdwTrack;
}

imedia::position Star350EventTrack::get_position()
{
    return m_tkPosition;
}

int Star350EventTrack::GetMidiTrackIndex()
{
    seek_begin();
    int iFirstTrack = -1;
    int iTrack = -1;
    while(::mus::midi::Success == ReadEvent(0x7fffffff, true))
    {
        Star350EventV001 * pevent = GetEvent();
        if(pevent->GetFullType() < ::mus::midi::SysEx)
        {
            iTrack = pevent->GetTrack();
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

bool Star350EventTrack::IsLyricsTrack()
{
    return m_bLyricsTrack;
}


void Star350EventTrack::SetLyricsTrack(bool bLyricsTrack)
{
    m_bLyricsTrack = bLyricsTrack;
}
