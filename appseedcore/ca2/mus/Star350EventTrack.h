#pragma once

class SoftKaraokeInfo;
class CTune1000Info;
//class CMidiFile;
//class CMidiEventsV1;

class Star350EventV001;
class Star350EventV008;
class Star350Tracks;
class Star350TrackV008;


struct AFX_EXT_CLASS CUDWordBytes
{
   union
   {
      DWORD   dw;
      BYTE   bytes[sizeof(DWORD)];
   };
   // Convert data in var Length Format
   DWORD ToVL()
   {
      ASSERT(dw <= 0x0fffffff);
      bytes[3] <<= 3;
      bytes[2] <<= 2;
      bytes[1] <<= 1;
      return 0;
   }

};


class CLASS_DECL_ca Star350EventTrack : public Star350TrackBase
{
    ;
public:
   Star350EventTrack();
   ~Star350EventTrack();
   enum States
   {
      StateOnDelta = 1,
      StateOnEvent = 2
   };

   enum CopyModes
   {
      CopyNormal = 1,
      CopyExcludeXFMetaLyrics = 2,
        CopyExcludeKarMetaLyrics = 4

   };
    Star350EventTrack & operator =(Star350EventTrack &eventSrc);
protected:
   int                m_nState;
   Star350EventV001 *   m_pevent;
    Star350Tracks *    m_ptracks;
    Star350TrackV008 * m_ptrackWorkStorage;
    bool                m_bLyricsTrack;
//   CMidiFile *      m_pFile;
public:
    DWORD           m_idxTrack;
    
   imedia::position           m_tkPosition;        
   DWORD           m_cbLeft;            
   byte *          m_hpbImage;          
   BYTE            m_bRunningStatus;   
   
   DWORD         m_dwUsed;
    
    DWORD           m_fdwTrack;
    struct tag_smti
    {
        imedia::position       m_tkLength;
        DWORD       m_cbLength;
    } m_smti;     

   imedia::position         m_tkDelta;
   byte *         m_hpbEventImage;

protected:
   DWORD      m_dwAllocation;
   BOOL      m_bAutoAllocation;
//   BOOL      m_bMirrorAllocation;
   DWORD      m_dwAllocationAddUp;
   byte *      m_hpbAllocation;
//   byte *      m_hpbMirrorAllocation;
//   byte *      m_hpbMirrorImage;
    int         m_iCurrentEvent;

   BOOL allocate(DWORD dwNewLength);
   BOOL allocate_add_up(DWORD dwAddUp);

public:
    void SetLyricsTrack(bool bLyricsTrack);
    bool IsLyricsTrack();
    void Initialize(Star350Tracks * pTracks);
   __forceinline int GetState();
   __forceinline Star350EventV001 * GetEvent();
   
   
   SMFRESULT ReadDelta();

   SMFRESULT ReadEvent(imedia::position tkMax, BOOL bTkMaxInclusive);

   SMFRESULT ReadXFTokens(stringa * lpstraTokens, imedia::position_array * lptkaTicks);
   
//   SMFRESULT ReadKarTokens(
//      StringArray *  lpstraTokens,
//      imedia::position_array *   lptkaTicks);

//   SMFRESULT ReadXFInfoHeader_(
//      LPTSTR *lppStr,
//      XFInfoHeader ** ppXfih,
//      XFInfoHeaderLS ** ppXfihls);

//   SMFRESULT GetNextXFInfoHeader(XFInfoHeader * pxfih);
//   SMFRESULT GetNextXFInfoHeaderLS(XFInfoHeaderLS * pxfihls);
//   SMFRESULT GetNextXFInfoHeaderLS(XFInfoHeaderLS * pxfihls ,const string &strLanguage);
//   SMFRESULT GetNextXFSongName(string &str);
//   SMFRESULT GetNextKarInfo(SoftKaraokeInfo *pKarI);
    //SMFRESULT GetNextTune1000Info(CTune1000Info *pTune1000I);


protected:
   DWORD GetVDWord(                              
      DWORD * pDw);

   DWORD GetVDWord(
      DWORD dwLeft,
      DWORD * pDw);

   DWORD SetVDWord(
      DWORD dwLeft,
      DWORD dw);
   
   DWORD SetVDWord(
      DWORD dw);

public:
   int GetMidiTrackIndex();
   imedia::position get_position();
   int GetFlags();
   VMSRESULT GetNextEventPosition(imedia::position * tkPosition, imedia::position  tkMax);
    VMSRESULT WorkSeek(DWORD dwSeekWhat);
   void WorkDeleteEvent();
   int GetCurrentEvent();
//    SMFRESULT WriteEvent(CMidiEventV008 & midiEvent);
   Star350TrackV008 * GetWorkTrack();
   VMSRESULT ToWorkStorage();
//   VMSRESULT FromWorkStorage();
   VMSRESULT ReadEvent(Star350EventV008 & midiEvent);
   SMFRESULT ReadTune1000Tokens(stringa * lpstraTokens, imedia::position_array * lptkaTicks);
   bool IsXFFile();
   SMFRESULT seek(DWORD dwSeekWhat);
    
    virtual VMSRESULT seek_begin();
   byte * GetImage();
//   BOOL ContainsEvent(midi_event_base * pEvent);
//   BOOL Mirror();
//   BOOL AllocateMirror(DWORD dwNewLength);
   bool IsSoftKaraokeFile(stringa * pstra = NULL);
//   SMFRESULT GetStandardEventsV1(
//      CMidiEventsV1 * pEvents,
//      int iFilter,
//      int iTrack,
//      bool bAnyTrack);
//   SMFRESULT GetNoteOnOffEventsV1(
//      CMidiEventsV1 * pEvents,
//      int iTrack,
//      bool bAnyTrack);
   
   SMFRESULT copy(Star350EventTrack *pTrk, int iMode);
   DWORD GetImageLength();
   byte * GetAllocationImage();
//   SMFRESULT WriteXFLyricEvent(string &str, imedia::position tkPosition);
//   SMFRESULT WriteHeader(CHUNKHDR *pHdr);
//   SMFRESULT WriteHeaderLength();
   SMFRESULT copy(Star350EventTrack *pTrk);
   SMFRESULT WriteCompleteEvent(imedia::position tkMax, bool bUseEventPosition);
   void SetAutoAllocation(BOOL bValue = TRUE);
   SMFRESULT WriteDelta();
//   SMFRESULT WriteXFInfoHeader(
//      const char * pSongName,
//      XFInfoHeader *pXfih,
//      XFInfoHeaderLS *pXfihls);
    //PSMF            pSmf;
    virtual VMSRESULT GetEvent(
        midi_event_base * pEvent,
      imedia::position   tkMax,
      BOOL   bTkMaxInclusive);


};

__forceinline int Star350EventTrack::GetState()
   {
      return m_nState;
   }


__forceinline Star350EventV001 * Star350EventTrack::GetEvent()
   {
      return m_pevent;
   }
