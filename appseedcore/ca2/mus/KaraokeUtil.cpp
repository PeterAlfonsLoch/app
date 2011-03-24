#include "StdAfx.h"

KaraokeUtil::KaraokeUtil(::ca::application * papp) :
   ca(papp)
{
    m_pstar350file = new Star350File(papp);
}

KaraokeUtil::~KaraokeUtil()
{
    if(m_pstar350file != NULL)
    {
        delete m_pstar350file;
        m_pstar350file = NULL;
    }
}

bool KaraokeUtil::IsStar350File(const char * lpcszPath)
{
    bool bResult = m_pstar350file->IsStar350(lpcszPath);
    return bResult;
}

bool KaraokeUtil::IsStar350File(primitive::memory & storage)
{
    bool bResult = m_pstar350file->IsStar350(storage);
    return bResult;
}

VMSRESULT KaraokeUtil::ConvertStar350ToXF(Star350File *pstarfile, ::mus::midi::sequence *pmidiseq, ::mus::midi::e_file_open_mode eOpenMode)
{
   MidiTrack * pmiditrk;
   Star350EventTrack * pstartrk;
    
   ::mus::midi::file & xffile = pmidiseq->GetFile();

   SMFRESULT smfrc;
   MidiTracks tracks(get_app());
   VMSRESULT vmsr;

   pstarfile->ToWorkStorage();

   pmidiseq->GetFile().CloseFile();
   pmidiseq->GetFile().GetTracks().remove_all();

   int idx;

   for (idx=0; idx < pstarfile->GetTracks().get_size(); idx++)
   {
      pstartrk = dynamic_cast<Star350EventTrack *>(pstarfile->GetTracks().element_at(idx));
      if(pstartrk != NULL &&
         !pstartrk->IsLyricsTrack())
      {
         pmiditrk = tracks.CreateTrack();
         pmiditrk->Initialize(&tracks);
         pmiditrk->SetAutoAllocation();
         ConvertStar350ToXF(
            pstarfile,
            pstartrk,
            pmiditrk);
//            TRACE("ConvertStar350ToXF\n");
//            TRACE("track index = %d", idx);
//            TRACE("pmiditrk->...events.size = %d\n",pmiditrk->GetWorkTrack().m_events.get_size());
//            for(int i = 0; i < pmiditrk->GetWorkTrack().m_events.get_size(); i++)
//            {
//                TRACE("event(%d).FullType = %X\n",i, pmiditrk->GetWorkTrack().m_events.element_at(i).GetFullType());
//                TRACE("event(%d).Ch1 = %X\n",i, pmiditrk->GetWorkTrack().m_events.element_at(i).GetChB1());
//            }
//            TRACE("track index = %d", idx);
//            TRACE("pmiditrk->...events.size = %d\n",pmiditrk->GetWorkTrack().m_events.get_size());
      }
   }

   //tracks.FromWorkStorage();

   MidiTrack * pTrackUnion = xffile.GetTracks().CreateTrack();
   //if(VMS_FAILED(vmsr = tracks.CompactTracks(*pTrackUnion, false, false)))
      //return vmsr;
   if(VMS_FAILED(vmsr = tracks.WorkCompactTracksWork(*pTrackUnion, false)))
      return vmsr;

   XFInfoHeader xfInfoHeader;

   pmiditrk = xffile.GetTracks().CreateTrack();
   pmiditrk->SetAutoAllocation();

   Star350InfoHeader * psih = pstarfile->GetInfoHeader();

   psih->ToXFInfoHeader(&xfInfoHeader);
   xfInfoHeader.SetID();

   pmiditrk->WorkWriteXFInfoHeader(
      NULL,
      &xfInfoHeader,
      NULL);

   MidiEventV008 eventV008;
   eventV008.SetFullType(::mus::midi::Meta);
   eventV008.SetMetaType(::mus::midi::MetaEOT);
   eventV008.SetParam(NULL, 0);
   eventV008.SetDelta(0);
   pmiditrk->WorkWriteEvent(eventV008);
   //pmiditrk->WriteCompleteEvent(0x7fffffff, false);

/*   CHUNKHDR chHdr;
   chHdr.fourccType = FOURCC_XFIH;
   chHdr.dwLength = pmiditrk->m_smti.m_cbLength;
   pmiditrk->WriteHeader(&chHdr);*/

   idx = pstarfile->GetLyricTrack();
   pstartrk = dynamic_cast<Star350EventTrack *>(pstarfile->GetTracks().element_at(idx));
   if(pstartrk != NULL)
   {
      pmiditrk = xffile.GetTracks().CreateTrack();
      pmiditrk->SetAutoAllocation();
      ConvertStar350ToXF(
         pstarfile,
         pstartrk,
         pmiditrk);
   }
/*   chHdr.fourccType = FOURCC_XFKM;
   chHdr.dwLength = pmiditrk->m_smti.m_cbLength;
   pmiditrk->WriteHeader(&chHdr);*/

//   xffile.ToWorkStorage();
    

   BYTE XFVERSIONID[] = {
      0x43,  // YAMAHA ID
      0x7B,  //
      0x00,  //
      0x58,  // X
      0x46,  // F
      0x30,  // 0 
      0x32,   // 2
      0x00,
      0x11};

   MidiTrack & trackXF = *(MidiTrack *) xffile.GetTracks().TrackAt(0);
   trackXF.seek_begin();
   eventV008.SetFullType(::mus::midi::Meta);
   eventV008.SetMetaType(::mus::midi::MetaSeqSpecific);
   eventV008.SetParam(XFVERSIONID, sizeof(XFVERSIONID));
   eventV008.SetPosition(0);
   trackXF.GetWorkTrack().insert_at(0, eventV008);

/*    char * lpstr = CInternational
      ::UnicodeToAnsiDup(ki.m_strSongName);
    
    eventV008.clear();
    eventV008.SetFullType(::mus::midi::Meta);
   eventV008.SetMetaType(CXF::MetaSongName);
    //eventV008.SetParamSize(strlen(lpstr));
   eventV008.SetParam((byte *) lpstr, strlen(lpstr));
    trackXF.GetWorkTrack().m_events.insert_at(1, eventV008);
   delete eventV008.GetParam(); */
    int i;
    for(i = 0; i < xffile.GetTracks().GetTrackCount(); i++)
    {
        MidiTrack & trackXF = *(MidiTrack *) xffile.GetTracks().TrackAt(i);
        trackXF.seek_begin();
        while(::mus::midi::Success == trackXF.WorkSeek(::mus::midi::SeekKarID))
        {
            trackXF.WorkDeleteEvent();
        }
    }
   if((smfrc = xffile.WorkMergeTracks()) != ::mus::midi::Success)
      return smfrc;

   MIDIFILEHDR fileHdr;
    
   fileHdr.wFormat = WORDSWAP(0);
   fileHdr.wDivision = WORDSWAP(pstarfile->m_pevheader->wDivision);
   fileHdr.wTracks = WORDSWAP(1) ;

   xffile.WriteHeader(&fileHdr);

   xffile.m_iOpenMode = eOpenMode;
   pmidiseq->m_iOpenMode = eOpenMode;

   if((smfrc = xffile.Build()) != ::mus::midi::Success)
      return smfrc;
   
   SMFFILEINFO             sfi;

   xffile.GetFileInfo(&sfi);
    
   pmidiseq->m_dwTimeDivision = sfi.dwTimeDivision;
   pmidiseq->m_tkLength       = sfi.tkLength;
//   pmidiseq->m_cTrk           = sfi.dwTracks;
   pmidiseq->m_msLength         = pmidiseq->TicksToMillisecs(pmidiseq->m_tkLength);
   pmidiseq->SetState(::mus::midi::sequence::StatusOpened);

   return VMSR_SUCCESS;
}

VMSRESULT KaraokeUtil::ConvertStar350ToXF(
   Star350File * pstarfile,
   Star350EventTrack *pstartrk, MidiTrack *pmiditrk)
{
   Star350EventV008 * lpstarev;
   MidiEventV008 midiev;
   base_array <MidiEventV008, MidiEventV008 &> midieva;
   MidiEventV001 midiev1;
   MidiEventV001 * lpmidiev1 = NULL;
   base_array <MidiEventV001, MidiEventV001 &> eventsPending;
   imedia::position tkMinPosition = 0x7fffffff;
   imedia::position tkPosition = 0;
   imedia::position tkLastPosition = 0;
   BYTE XFLYRICSHEADER[] = "$Lyrc:1:270:L1";
   BYTE CUEPOINTSOLO[] = "&s";

   pmiditrk->GetWorkTrack().remove_all();

   if(pstartrk->IsLyricsTrack())
   {
      string strLyrics;
      string str;
      pstarfile->GetLyricsText(strLyrics);

      pmiditrk->WorkSeekBegin();
         
      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaXFLyricsHeader);
      midiev.SetParam(XFLYRICSHEADER, sizeof(XFLYRICSHEADER) - 1);
      midiev.SetPosition(0);
      midiev.SetDelta(0);
      pmiditrk->WorkWriteEvent(midiev);

      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaCuePoint);
      midiev.SetParam(CUEPOINTSOLO, sizeof(CUEPOINTSOLO) - 1);
      midiev.SetPosition(0);
      midiev.SetDelta(0);
      pmiditrk->WorkWriteEvent(midiev);

      bool bPendingLineBreak = false;

      for(int i = 0; i < pstartrk->GetWorkTrack()->m_events.get_size(); i++)
      {
         lpstarev = &pstartrk->GetWorkTrack()->m_events.element_at(i);
         tkLastPosition = tkPosition;
         tkPosition += lpstarev->GetDelta();

         if(lpstarev->GetStar350Type()
            == Star350EventBase::EventTypeLineBreak)
         {
            bPendingLineBreak = true;
         }
         else if(lpstarev->GetStar350Type()
            == Star350EventBase::EventTypeLyrics)
         {
             string strToken =
               strLyrics.Mid(
                  lpstarev->GetLyricsOffset(),
                  lpstarev->GetLyricsCount());

                    //if(strToken.Mid(0, 1).Compare("\\") == 0)
                //{
                 //  str = "<";
                   //str += strToken.Mid(1);
                //}
                //else if(strToken.Mid(0, 1).Compare("/") == 0)
            if( bPendingLineBreak)
            {
               str = "/";
               pmiditrk->WorkWriteXFLyricEvent(str, tkPosition);
               str = strToken;
               bPendingLineBreak = false;
            }
            else
            {
               str = strToken;
            }
            str.replace(" ", "^");
            pmiditrk->WorkWriteXFLyricEvent(str, tkPosition);
         }
      }
      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaEOT);
      midiev.SetParam(NULL, 0);
      midiev.SetPosition(tkPosition);
      midiev.SetDelta(0);
      pmiditrk->WorkWriteEvent(midiev);
   }
   else
   {
        //pmiditrk->GetWorkTrack().set_size(pstartrk->GetWorkTrack()->m_events.get_size(), 100);
        pmiditrk->GetWorkTrack().remove_all();
    //pmiditrk->GetWorkTrack().m_events.set_size(pstartrk->GetWorkTrack()->m_events.get_size());
      for(int i = 0; i < pstartrk->GetWorkTrack()->m_events.get_size(); i++)
      {
         lpstarev = &pstartrk->GetWorkTrack()->m_events.element_at(i);
         tkPosition += lpstarev->GetDelta();
        
         while(tkPosition >= tkMinPosition)
         {
            ASSERT(tkMinPosition >= tkLastPosition);
                
            lpmidiev1->SetDelta(tkMinPosition - tkLastPosition);
            tkLastPosition = tkMinPosition;

            midiev.clear();
            midiev = *lpmidiev1;
            midiev.SetPosition(tkMinPosition);
            pmiditrk->GetWorkTrack().add(midiev);
                
            eventsPending.remove_at(0);
            if(eventsPending.get_size() <= 0)
            {
               lpmidiev1 = NULL;
               tkMinPosition = 0x7fffffff;
            }
            else
            {
               lpmidiev1 = &eventsPending.element_at(0);
               tkMinPosition = lpmidiev1->GetPosition();
            }
         }

         midiev.clear();
         midieva.remove_all();
         ConvertStar350ToXF(lpstarev, &midieva);

         for(int j = 0; j < midieva.get_size(); j++)
         {
            //TRACE("ConvertStar350To XF i = %d, j = %d\n", i, j);
            midiev = midieva.element_at(j);
            if(midiev.get_type() == 0x90)
            {
//               int i123 = 1 + 2;
            }
            if(j == midieva.get_size() - 1)
            {
               ASSERT(tkPosition >= tkLastPosition);
               midiev.SetDelta(tkPosition - tkLastPosition);
               tkLastPosition = tkPosition;
            }
            else
            {
               midiev.SetDelta(0);
            }
            //                tkPosition += midiev.GetDelta();
            //            if(lpstarev->GetStar350Type() == Star350EventBase::EventTypeMidi)
            //            {
            //                tkLastPosition = tkPosition;
            midiev.SetPosition(tkPosition);
            pmiditrk->GetWorkTrack().add(midiev);
            if(lpstarev->get_type() == ::mus::midi::NoteOn)
            {
               midiev1.set_type(::mus::midi::NoteOff);
               midiev1.SetTrack(midiev.GetTrack());
               midiev1.SetNotePitch(midiev.GetNotePitch());
               midiev1.SetPosition(tkPosition + lpstarev->GetDuration());
               eventsPending.add(midiev1);
               
               sort::QuickSort(
                  (base_array<MidiEventV001, MidiEventV001 &> &) eventsPending,
                  MidiEventV001::CompareTkPosition,
                  MidiEventV001::swap);
               
               //                eventsPending.QuickSort(eventsPending.CompareTkPosition);
               //                SortQuickSort<MidiEventV001, MidiEventV001 &>
               //                  (
               //                &,
               //              SortCompareTkPosition<MidiEventV001 *>,
               //            CSort::swap,
               //          NULL)
               lpmidiev1 = &eventsPending.element_at(0);
               tkMinPosition = lpmidiev1->GetPosition();
            }
         }
      }
      while(lpmidiev1 != NULL)
      {
         ASSERT(tkMinPosition >= tkLastPosition);
         
         lpmidiev1->SetDelta(tkMinPosition - tkLastPosition);
         tkLastPosition = tkMinPosition;
         
         midiev.clear();
         midiev = *lpmidiev1;
         midiev.SetPosition(tkMinPosition);
         pmiditrk->GetWorkTrack().add(midiev);
         
         eventsPending.remove_at(0);
         if(eventsPending.get_size() <= 0)
         {
            lpmidiev1 = NULL;
            tkMinPosition = 0x7fffffff;
         }
         else
         {
            lpmidiev1 = &eventsPending.element_at(0);
            tkMinPosition = lpmidiev1->GetPosition();
         }
      }
      midiev.clear();
      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaEOT);
      midiev.SetPosition(tkPosition);
      midiev.SetDelta(0);
      pmiditrk->GetWorkTrack().add(midiev);
      
    }
    
    CHUNKHDR hdr;
    hdr.fourccType = FOURCC_MTrk;
    hdr.dwLength = pmiditrk->m_smti.m_cbLength;
    pmiditrk->WriteHeader(&hdr);

    return VMSR_SUCCESS;
}

VMSRESULT KaraokeUtil::ConvertStar350ToXF(
    Star350EventV008 *pstarev,
    base_array <MidiEventV008, MidiEventV008 &> *pmidieva)
{
   MidiEventV008 midiev;
   if(pstarev->GetStar350Type() == Star350EventBase::EventTypeTrackName)
   {
      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaChannelPrefix);
      BYTE b = 0;
      midiev.WriteParam(&b, 1);
      pmidieva->add(midiev);
      
      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaTrackName);
      midiev.WriteParam(pstarev->GetParam(), pstarev->GetParamSize());
      pmidieva->add(midiev);
   }
   else if(pstarev->GetStar350Type() == Star350EventBase::EventTypeMidiTempo)
   {
      midiev.SetFullType(::mus::midi::Meta);
      midiev.SetMetaType(::mus::midi::MetaTempo);
      
      unsigned char pb[3];
      unsigned char ch;
      memcpy(pb, pstarev->GetParam(), pstarev->GetParamSize());
      ch = pb[0];
      pb[0] = pb[2];
      pb[2] = ch;
      
      midiev.WriteParam(pb, 3);
      pmidieva->add(midiev);
   }
   else if(pstarev->GetStar350Type() == Star350EventBase::EventTypeMidi)
   {
      midiev.SetFullType(pstarev->GetFullType());
      midiev.SetChB1(pstarev->GetChB1());
      midiev.SetChB2(pstarev->GetChB2());
      midiev.WriteParam(pstarev->GetParam(), pstarev->GetParamSize());
      midiev.SetDelta(pstarev->GetDelta());
      midiev.SetFlags(pstarev->GetFlags());
      pmidieva->add(midiev);
   }
   return VMSR_SUCCESS;
}
