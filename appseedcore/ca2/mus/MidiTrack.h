#pragma once

class SoftKaraokeInfo;
class CTune1000Info;
class ::mus::midi::file;
class MidiEventsV1;
class MidiTracks;
class CTrackArray;

class CLASS_DECL_ca MidiTrack :
   public MidiTrackBase,
   public primitive::memory_container < primitive::memory >
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
   MidiEventV001      m_event;
   MidiEventV008      m_event8;
   MidiTracks *      m_ptracks;
   MidiTrackV008     m_trackWorkStorage;
   int               m_iCurrentEvent;


   MidiTrack(::ca::application * papp);
   MidiTrack(const MidiTrack & track);
   virtual ~MidiTrack();

   MidiTrack & operator =(const MidiTrack &eventSrc);


   void Initialize(MidiTracks * pTracks);
   inline State GetState();
   inline MidiEventV001 & GetEvent();
   
   
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
   void _GetEvent(bool bWork, MidiEventV008 *& pevent, imedia::position tkMax, bool bTkMaxInclusive);
   ::mus::midi::e_file_result _SeekBegin(bool bWork);
   virtual bool WorkIsEOT();
   virtual e_type get_type();
   ::mus::midi::file_flags & GetFlags();
   ::mus::midi::file_flags & _GetFlags();
   void WorkClear();
   virtual void allocate(DWORD dwNewLength);
   ::mus::midi::e_file_result SeekXFLyricsHeader();
   ::mus::midi::e_file_result ReadXFLyricsHeader(XFLyricsHeader * pxflh);
   ::mus::midi::e_file_result GetDelta(imedia::position & tkDelta);
   ::mus::midi::e_file_result ReadEvent();
   virtual ::mus::midi::e_file_result MoveNext();
   int GetMidiTrackIndex();
   imedia::position GetPosition();
   //int GetFlags();
   
   
   ::mus::midi::e_file_result GetPosition(imedia::position & tkPosition, imedia::position  tkMax);
    
   ::mus::midi::e_file_result WorkWriteEvent();
   ::mus::midi::e_file_result WorkWriteEvent(MidiEventV008 & event);
   
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
      MidiTrack *pTrk,
      int iMode);

   ::mus::midi::e_file_result WorkCopyWork(
      MidiTrack *pTrk,
      int iMode);

   imedia::position WorkGetPosition();


   virtual ::mus::midi::e_file_result WorkMoveNext();

   virtual void WorkGetEvent(
      MidiEventBase *&    pevent,
      imedia::position                  tkMax,
      BOOL                  bTkMaxInclusive);

   virtual void WorkGetEvent(
      MidiEventV008 *&    pevent,
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

   ::mus::midi::e_file_result MidiTrack::WriteXFLyricTrack(stringa & tokena, imedia::position_array & positiona);


   /*::mus::midi::e_file_result WorkReadShiftJisXFTokens(
      stringa &  tokena,
      imedia::position_array *   lptkaTicks);*/

   ::mus::midi::e_file_result WorkGetLevel2Events(MidiEventsV1 * pevents, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkGetNoteOnOffEventsV1(MidiEventsV1 * pEvents, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkGetStandardEventsV1(MidiEventsV1 * pEvents, int iFilter, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkGetStandardEventsV1OnlyMelodic(MidiEventsV1 * pEvents, int iFilter, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result WorkSeekXFLyricsHeader();
   ::mus::midi::e_file_result WorkReadXFLyricsHeader(XFLyricsHeader * pxflh);

   int GetCurrentEvent();
    ::mus::midi::e_file_result WriteEvent(MidiEventV008 & midiEvent);
   MidiTrackV008 & GetWorkTrack();
   VMSRESULT ToWorkStorage();
   VMSRESULT FromWorkTrack(bool bExcludeEOT);
   VMSRESULT FromWorkTrack(MidiTrackV008 & track);
   VMSRESULT ReadEvent(MidiEventV008 & midiEvent);
   VMSRESULT ReadEvent(MidiEventV001 & midiEvent);
   
   
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

   ::mus::midi::e_file_result GetStandardEventsV1(MidiEventsV1 * pEvents, int iFilter, int iTrack, bool bAnyTrack);
   ::mus::midi::e_file_result GetNoteOnOffEventsV1(MidiEventsV1 * pEvents, int iTrack, bool bAnyTrack);

   ::mus::midi::e_file_result GetLevel2Events(MidiEventsV1 *pevents, int iTrack, bool bAnyTrack);

   void SetAutoAllocation(BOOL bValue = TRUE);

   ::mus::midi::e_file_result copy(MidiTrack *pTrk, int iMode);
   
   ::mus::midi::e_file_result WriteXFLyricEvent(string &str, imedia::position tkPosition);

   ::mus::midi::e_file_result WriteHeader(CHUNKHDR *pHdr);
   ::mus::midi::e_file_result WriteHeaderLength();
   ::mus::midi::e_file_result WriteCompleteEvent(imedia::position tkMax, bool bUseEventPosition);
   ::mus::midi::e_file_result WriteCompleteEvent(MidiEventBase & event, imedia::position tkMax, bool bUseEventPosition);
   ::mus::midi::e_file_result WriteDelta();
   
   ::mus::midi::e_file_result WriteXFInfoHeader(const char * pSongName, XFInfoHeader *pXfih, XFInfoHeaderLS *pXfihls);
   
   virtual ::mus::midi::e_file_result GetEvent(MidiEventBase * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);
   virtual ::mus::midi::e_file_result GetEvent(MidiEventV001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);
   void _WorkGetEvent(MidiEventV008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);
   bool _WorkIsEOT();
   imedia::position _WorkGetPosition();
   ::mus::midi::e_file_result _WorkMoveNext();

   void dump(dump_context & dumpcontext) const;

};

