#pragma once


#define C_TEMPO_MAP_CHK     16

//class CMidiEventV007;
class Star350EventBase;
class Star350InfoHeader;
class Star350Tracks;

class CLASS_DECL_ca Star350File :
   public primitive::memory_container
{
public:
   Star350File(::ca::application * papp);
   ~Star350File();

public:
   enum
   {
      OpenForPlaying = 1,
      OpenForParsing = 2,
      OpenForParsingLevel2 = 3,
      OpenForIdentifying = 4
   };
   enum
   {
      Success = 0,
      InvalidFile = 1,
      NoMemory = 2,
      OpenFailed = 3,
      InvalidTrack = 4,
      MetaPending = 5,
      AlreadyOPen = 6,
      EndOfTrack = 7,
      NoMeta = 8,
      InvalidParam = 9,
      InvalidBuffer = 10,
      EndOfFile = 11,
      ReachedTkMax = 12,
      InvalidTkPosition = 13,
      SaveFailed = 14,
      EventNotFound = 15,
      TrackNotFound = 16,
      FunctionNotSupported = 17,
        NotFound = 18
   };
   enum flags
   {
      FlagEof = (long) 1,
      FlagInsertSysEx = (long) 2,
      FlagOpened = (long) 4,
      FlagExpanded = (long) 8
   };
/*   enum
   {
      SeekXFInfoHeader = 1,
      SeekXFInfoHeaderLS = 2,
      SeekXFSongName = 3,
      SeekKarID = 4
   };*/
protected:
   Star350InfoHeader *    m_pinfoheader;
   int         m_iKeyShift;
   int         m_iTempoShift;
   string     m_strLyrics;

public:
   DWORD GetImageSize();
   LPBYTE GetImage();
   int GetLyricTrack();
   void GetLyricsText(string & str);

   bool IsStar350(const char * lpcszPath);
   bool IsStar350(primitive::memory & storage);
   static const char m_lpchHeader[];
   void ToWorkStorage();
   inline bool IsOpened();
   critical_section   m_cs;
   VMSRESULT GetPreviousEvent(
      midi_event_base * pPreviousEvent,
      midi_event_base * pEvent);
   void delete_contents();


   string               m_strName;

   LPBYTE               m_pchHeader;

   LPSTAR350FILEHDR     m_pevheader; // Event Header
   DWORD                m_dwMelodyTrack;
   DWORD                m_dwLyricTrack;


   DWORD                  m_dwPendingUserEvent;
   DWORD                  m_cbPendingUserEvent;
   byte *               m_hpbPendingUserEvent;


    bool                m_bPendingLyric;
    
protected:
   Star350Tracks   *   m_ptracks;
public:
    //CMidiLyricTracks        m_tracksLyric;
   imedia::position             m_tkLength;
    DWORD             m_dwFormat;
    DWORD            m_dwTracks;
    DWORD            m_dwTimeDivision;
    DWORD            m_fdwSMF;


   int               m_iOpenMode;

   mus::EStorage    m_estorage;

   SMFRESULT OpenFile(
      Star350File &file,
      int openMode);

   
   SMFRESULT OpenFile(
      ex1::filesp & file,
      int openMode);
    
   SMFRESULT OpenFile(
      primitive::memory * pmemstorage,
      int openMode,
      mus::EStorage estorage);

    SMFRESULT SaveFile(ex1::file & file);

    Star350Tracks   & GetTracks();
    

      //    PSMFOPENFILESTRUCT  psofs);

   SMFRESULT CloseFile();

   SMFRESULT GetFileInfo(
      PSMFFILEINFO psfi);

    Star350InfoHeader * GetInfoHeader();

   SMFRESULT ReadEvents(
      LPMIDIHDR lpmh,
      imedia::position tkMax,
        DWORD cbPrerollNomimalMax);

    VMSRESULT ReadEvent(
        midi_event_base * pEvent,
      LPMIDIHDR lpmh,
      imedia::position tkMax,
        DWORD cbPrerollNomimalMax);

   SMFRESULT seek(imedia::position tkPosition, LPMIDIHDR lpmh);

   SMFRESULT seek(imedia::position tkPosition);

   static DWORD GetStateMaxSize(void);

   SMFRESULT BuildIndex();


   SMFRESULT GetNextEvent(midi_event_base * pevent, imedia::position tkMax, BOOL   bTkMaxInclusive);

   SMFRESULT GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

protected:
   SMFRESULT InsertParmData(imedia::position tkDelta, LPMIDIHDR lpmh);


   SMFRESULT InsertPadEvent(imedia::position            tkDelta, LPMIDIHDR         lpmh);


private:
   inline void SetOpened(bool bOpened = true);
};

