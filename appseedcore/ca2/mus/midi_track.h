#pragma once

class SoftKaraokeInfo;
class CTune1000Info;
class ::mus::midi::file;
class midi_events_v1;
class midi_tracks;
class CTrackArray;

class CLASS_DECL_ca midi_track :
   public midi_track_base,
   public primitive::memory_container
{
public:

   enum State
   {
      StateOnDelta = 1,
      StateOnEvent = 2,
      StateOnEventRead = 3
   };

   enum CopyModes
   {
      CopyNormal = 1,
      CopyExcludeXFMetaLyrics = 2,
        CopyExcludeKarMetaLyrics = 4

   };
   DWORD                         m_idxTrack;
   int                           m_iIndex;
   imedia::position          m_tkPosition;
   DWORD                         m_cbLeft;            
   bool                          m_bWorkTrackEnd;
   byte *                        m_hpbImage;
   DWORD                           m_dwUsed;
   ::mus::midi::file_flags   m_flags;
   struct tag_smti
   {
      imedia::position       m_tkLength;
      DWORD       m_cbLength;
   } m_smti;     

   imedia::position         m_tkDelta;
   byte *         m_hpbEventImage;

   int               m_iWorkNextPositionEvent;
   imedia::position  m_tkWorkNextPosition;
   bool               m_bAutoAllocation;
   primitive::memory            m_memstorageHelper;
   State               m_estate;
   midi_event_v001      m_event;
   midi_event_v008      m_event8;
   midi_tracks *      m_ptracks;
   midi_track_v008     m_trackWorkStorage;
   int               m_iCurrentEvent;


   midi_track(::ca::application * papp);
   midi_track(const midi_track & track);
   virtual ~midi_track();

   midi_track & operator =(const midi_track &eventSrc);


   void Initialize(midi_tracks * pTracks);
   inline State GetState();
   inline midi_event_v001 & GetEvent();
   
   
   ::mus::midi::e_file_result ReadDelta();

   ::mus::midi::e_file_result ReadEvent(
      imedia::position   tkMax,
      BOOL   bTkMaxInclusive);

   ::mus::midi::e_file_result ReadAnsiXFTokens(stringa & tokena, imedia::position_array * ptkaTicks);
   ::mus::midi::e_file_result ReadShiftJisXFTokens(stringa & tokena, imedia::position_array * lptkaTicks);
   ::mus::midi::e_file_result ReadKarTokens(stringa & tokena, imedia::position_array * lptkaTicks);
   ::mus::midi::e_file_result ReadTune1000Tokens(stringa & tokena, imedia::position_array * lptkaTicks);
   ::mus::midi::e_file_result ReadXFInfoHeader_(LPTSTR * lppStr, XFInfoHeader ** ppXfih, XFInfoHeaderLS ** ppXfihls);

   ::mus::midi::e_file_result GetNextXFInfoHeader(XFInfoHeader * pxfih);
   ::mus::midi::e_file_result GetNextXFInfoHeaderLS(XFInfoHeaderLS * pxfihls);
   ::mus::midi::e_file_result GetNextXFInfoHeaderLS(XFInfoHeaderLS * pxfihls ,const string &strLanguage);
   ::mus::midi::e_file_result GetNextXFSongName(string &str);
   ::mus::midi::e_file_result GetNextKarInfo(SoftKaraokeInfo *pKarI);
   ::mus::midi::e_file_result GetNextTune1000Info(CTune1000Info *pTune1000I);


protected:
   ::mus::midi::e_file_result WorkSetEOT();

   DWORD GetVDWord(DWORD * pDw);
   DWORD GetVDWord(DWORD dwLeft, DWORD * pDw);
   
   DWORD SetVDWord(DWORD dwLeft, DWORD dw);
   DWORD SetVDWord(DWORD dw);

public:
   ::mus::midi::e_file_result _MoveNext(bool bWork);
   void _GetEvent(bool bWork, midi_event_v008 *& pevent, imedia::position tkMax, bool bTkMaxInclusive);
   ::mus::midi::e_file_result _SeekBegin(bool bWork);
   virtual bool WorkIsEOT();
   virtual e_type get_type();
   ::mus::midi::file_flags & GetFlags();
   ::mus::midi::file_flags & _GetFlags();
   void WorkClear();
   virtual void allocate(DWORD dwNewLength);
   ::mus::midi::e_file_result SeekXFLyricsHeader();
   ::mus::midi::e_file_result ReadXFLyricsHeader(::mus::xf_lyrics_id * pxflh);
   ::mus::midi::e_file_result GetDelta(imedia::position & tkDelta);
   ::mus::midi::e_file_result ReadEvent();
   virtual ::mus::midi::e_file_result MoveNext();
   int GetMidiTrackIndex();
   imedia::position get_position();
   //int GetFlags();
   
   
   ::mus::midi::e_file_result get_position(imedia::position & tkPosition, imedia::position  tkMax);
    
   ::mus::midi::e_file_result WorkWriteEvent();
   ::mus::midi::e_file_result WorkWriteEvent(midi_event_v008 & event);
   
   VMSRESULT WorkSeek(DWORD dwSeekWhat);
   void WorkDeleteEvent();

   int m_iWorkCurrentEvent;
   
   ::mus::midi::e_file_result WorkReadKarTokens(
      stringa &  tokena,
      imedia::position_array *   lptkaTicks);

   ::mus::midi::e_file_result WorkReadTune1000Tokens(
      stringa &  tokena,
      imedia::position_array * lptkaTicks);

   ::mus::midi::e_file_result CopyWork(
      midi_track *pTrk,
      int iMode);

   ::mus::midi::e_file_result WorkCopyWork(
      midi_track *pTrk,
      int iMode);

   imedia::position WorkGetPosition();


   virtual ::mus::midi::e_file_result WorkMoveNext();

   virtual void WorkGetEvent(
      midi_event_base *&    pevent,
      imedia::position                  tkMax,
      BOOL                  bTkMaxInclusive);

   virtual void WorkGetEvent(
      midi_event_v008 *&    pevent,
      imedia::position                  tkMax,
      BOOL                  bTkMaxInclusive);

   virtual ::mus::midi::e_file_result WorkSeekBegin();
   virtual ::mus::midi::e_file_result WorkSeekEnd();

   ::mus::midi::e_file_result WorkWriteXFInfoHeader(const char * pSongName, XFInfoHeader *pXfih, XFInfoHeaderLS * pXfihls);

   //::mus::midi::e_file_result WorkWriteXFLyricEvent(
   //   string &str,
   //   imedia::position tkPosition);

   ::mus::midi::e_file_result WorkWriteXFLyricEvent(string &str, imedia::position tkPosition);

   ::mus::midi::e_file_result WorkReadXFTokens(UINT uiCodePage, stringa & tokena, imedia::position_array * lptkaTicks);

   ::mus::midi::e_file_result WorkReadXFTokens(UINT uiCodePage, stringa & tokena, imedia::position_array & positiona, int_array & iaTokenLine);

   ::mus::midi::e_file_result WorkReadEmptyXFTokens(stringa & tokena, imedia::position_array & positiona);

/*   ::mus::midi::e_file_result WorkReadAnsiXFTokens(stringa & tokena, imedia::position_array * lptkaTicks);*/

   ::mus::midi::e_file_result midi_track::WriteXFLyricTrack(stringa & tokena, imedia::position_array & positiona);


   /*::mus::midi::e_file_result WorkReadShiftJisXFTokens(
      stringa &  tokena,
      imedia::position_array *   lptkaTicks);*/

   ::mus::midi::e_file_result WorkGetLevel2Events(midi_events_v1 * pevents, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkGetNoteOnOffEventsV1(midi_events_v1 * pEvents, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkGetStandardEventsV1(midi_events_v1 * pEvents, int iFilter, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkGetStandardEventsV1OnlyMelodic(midi_events_v1 * pEvents, int iFilter, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkSeekXFLyricsHeader();
   ::mus::midi::e_file_result WorkReadXFLyricsHeader(::mus::xf_lyrics_id * pxflh);

   int GetCurrentEvent();
    ::mus::midi::e_file_result WriteEvent(midi_event_v008 & midiEvent);
   midi_track_v008 & GetWorkTrack();
   VMSRESULT ToWorkStorage();
   VMSRESULT FromWorkTrack(bool bExcludeEOT);
   VMSRESULT FromWorkTrack(midi_track_v008 & track);
   VMSRESULT ReadEvent(midi_event_v008 & midiEvent);
   VMSRESULT ReadEvent(midi_event_v001 & midiEvent);
   
   
   ::mus::midi::e_file_result seek(DWORD dwSeekWhat);
    
    virtual ::mus::midi::e_file_result seek_begin();
   
   
   byte *   GetTrackImage();
   DWORD   GetTrackImageLength();
   byte *   GetAllocationImage();
   byte *   GetTrackBody();
   DWORD   GetTrackBodyLength();

   bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);

   bool IsXFFile();
   bool IsTune1000File();

   ::mus::midi::e_file_result GetStandardEventsV1(midi_events_v1 * pEvents, int iFilter, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result GetNoteOnOffEventsV1(midi_events_v1 * pEvents, int iTrack, bool bAnyTrack);

   ::mus::midi::e_file_result GetLevel2Events(midi_events_v1 *pevents, int iTrack, bool bAnyTrack);

   void SetAutoAllocation(BOOL bValue = TRUE);

   ::mus::midi::e_file_result copy(midi_track *pTrk, int iMode);
   
   ::mus::midi::e_file_result WriteXFLyricEvent(string &str, imedia::position tkPosition);

   ::mus::midi::e_file_result WriteHeader(CHUNKHDR *pHdr);
   ::mus::midi::e_file_result WriteHeaderLength();
   ::mus::midi::e_file_result WriteCompleteEvent(imedia::position tkMax, bool bUseEventPosition);
   ::mus::midi::e_file_result WriteCompleteEvent(midi_event_base & event, imedia::position tkMax, bool bUseEventPosition);
   ::mus::midi::e_file_result WriteDelta();
   
   ::mus::midi::e_file_result WriteXFInfoHeader(const char * pSongName, XFInfoHeader *pXfih, XFInfoHeaderLS *pXfihls);
   
   virtual ::mus::midi::e_file_result GetEvent(midi_event_base * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);
   virtual ::mus::midi::e_file_result GetEvent(midi_event_v001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);
   void _WorkGetEvent(midi_event_v008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);
   bool _WorkIsEOT();
   imedia::position _WorkGetPosition();
   ::mus::midi::e_file_result _WorkMoveNext();

   void dump(dump_context & dumpcontext) const;

};

