#pragma once

class CTune1000Info;
class MidiEventsV1;
class MidiTrackBase;
class MidiLyricTrack;


class CLASS_DECL_ca MidiTracks :
   virtual public ::radix::object
{

public:

   class TrackPtrArray;

   enum ETrackType
   {
      TypeMidiTrack,
      TypeMidiLyricTrack,
   };


   class TrackPtrAllocArray : 
      virtual public ::radix::object
   {
      friend class TrackPtrArray;
   protected:
      
      array_smart_ptr < MidiTrackBase >   m_tracka;
      array_ptr_copy < MidiTrack >        m_miditracka;
      array_ptr_copy < MidiLyricTrack >   m_lyrictracka;
      MidiTracks   *                       m_ptracks;
      
   public:
      count GetTrackCount() const;
      count GetMidiTrackCount() const;
      count GetLyricTrackCount();
      MidiTrackBase * TrackAt(index iIndex);
      MidiLyricTrack * LyricTrackAt(index iIndex);
      MidiTrack * MidiTrackAt(index iIndex);
      MidiTrack * MidiTrackAt(index iIndex) const;

      TrackPtrAllocArray(::ca::application * papp);
      void Initialize(MidiTracks * ptracks);
      void RemoveAllMidiTracks();
      void RemoveTrack(MidiTrackBase * ptrack);
      void remove_all();
      void remove_at(index iIndex);

      MidiTrack * CreateTrack(index iIndex, FOURCC fourcc = FOURCC_MTrk);
      MidiTrack * CreateTrack(FOURCC fourcc = FOURCC_MTrk);
      MidiLyricTrack * CreateLyricTrack(index iIndex);
      MidiLyricTrack * CreateLyricTrack();

      void copy(TrackPtrAllocArray & base_array);
   };

   class TrackPtrArray
   {
   protected:
   
      array_smart_ptr < MidiTrackBase >   m_tracka;
      array_smart_ptr < MidiTrack >       m_miditracka;
      array_smart_ptr < MidiLyricTrack >  m_lyrictracka;
      MidiTracks   *                       m_ptracks;

   public:
      count GetTrackCount() const;
      count GetMidiTrackCount() const;
      count GetLyricTrackCount();
      MidiTrackBase * TrackAt(index iIndex);
      MidiLyricTrack * LyricTrackAt(index iIndex);
      MidiTrack * MidiTrackAt(index iIndex);

   public:
      TrackPtrArray();
      void Initialize(MidiTracks * ptracks);
      void RemoveAllMidiTracks();
      void RemoveTrack(MidiTrackBase * ptrack);
      void remove_all();
      void remove_at(index iIndex);

      void copy(TrackPtrAllocArray & base_array);

      TrackPtrArray & operator = (TrackPtrAllocArray & base_array);
   };

   MidiEventV008              m_midieventVolume;
   MidiEventV001              m_midieventV001Volume;
   int                        m_iLyricDelay;
   TrackPtrAllocArray         m_tracka;
   TrackPtrArray              m_trackaActive;
   int_array                  m_iaLevel;
   int_array                  m_iaNoteOn;
   int_array                  m_iaInstrument;
   imedia::position           m_tkLevelLastUpdateInterval;
   BYTE                       m_uchRunningStatus;
   imedia::position           m_tkPosition;
   ::mus::midi::file_flags    m_flagsFile;
   ::mus::midi::file *        m_pFile;
   int                        m_iMelodyTrackTipA; // set by kar to xf conversion
   int                        m_iCurrentTrack;


   MidiTracks(::ca::application * papp, ::mus::midi::file * pFile = NULL);
   virtual ~MidiTracks();


   void dump(dump_context & dumpcontext) const;

   bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);
   bool IsXFFile();
   bool IsTune1000File();

   VMSRESULT WorkCompactTracks(MidiTrack & trackUnion, bool bOnlyMTrk);

   VMSRESULT WorkCompactMidiTracks(MidiTrack & trackUnion, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetNextEvent(MidiEventV008 * & ppevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetNextRawEvent(MidiEventV008 * & ppevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetNextRawMidiEvent(MidiEventV008 * & ppevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk);

   void WorkSeekBegin();
   void WorkSeekEnd();

   VMSRESULT WorkCompactTracksWork(MidiTrack & trackUnion, bool bOnlyMTrk);

   VMSRESULT WorkCompactMidiTracksWork(MidiTrack & trackUnion, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetXFTokens(UINT uiCodePage, string2a & token2a, imedia::position_2darray * p2DTicks, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a);

   ::mus::midi::e_file_result WorkGetXFTokens(UINT uiCodePage, string2a & token2a, imedia::position_2darray & p2DTicks, int2a & i2aTokenLine, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a);

   ::mus::midi::e_file_result WorkGetEmptyXFTokens(int iTrack, string2a & token2a, imedia::position_2darray & p2DTicks, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a);

   ::mus::midi::e_file_result WorkGetSoftKaraokeTokens(string2a & token2a, imedia::position_2darray *p2DTicks, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a);
   
   int CalcMelodyTrack(MidiEventsV1 ** ppEvents, imedia::position_array *p1DTokens, WORD   wFileFormat);

   int WorkCalcMelodyTrack(MidiEventsV1 ** ppEventsRet, imedia::position_array & positiona, int_array & iaTokenLine, WORD wFileFormat);

   static BYTE m_paramEventNoteOnPositionCB[];
   static int m_iparamEventNoteOnPositionCB;
   
   ::mus::midi::e_file_result GetKarInfoHeader(SoftKaraokeInfo *pKarI);

   ::mus::midi::e_file_result GetTune1000InfoHeader(CTune1000Info *pTune1000I, int iTrack);

   void RemoveAllMidiTracks();
   count GetTrackCount();
   MidiTrackBase * TrackAt(index iIndex);
   MidiTrack * CreateTrack(FOURCC fourcc = FOURCC_MTrk);
   void remove_all();
   void clear();
   MidiTrack * CreateTrack(index iIndex, FOURCC fourcc = FOURCC_MTrk);
   bool WorkGetLongestXFLyrics(string &str);
   ::mus::midi::e_file_result GetVolumeEvent(::ca::application * papp, MidiEventV008 *& pevent);
   ::mus::midi::e_file_result GetVolumeEvent(::ca::application * papp, MidiEventV001 *& pevent);
   void OnStop();
   MidiTrack * seek(DWORD dwSeekWhat);

   bool m_bVolumeEventSent;
   VMSRESULT GetLyricDelay(int * lpiDelay);
   VMSRESULT SetLyricDelay(int iDelay);
   index GetMidiTrackIndex(index iIndex);
   
   VMSRESULT CompactTracks(MidiTrack & trackUnion, bool bOnlyMTrk, bool bOnlyMidiTrack);

   VMSRESULT ExpandTrack(index iTrackIndex);
   void ToWorkStorage();
   void FromWorkStorage();


   ::mus::midi::e_file_result GetKarTokens(string2a & token2a, imedia::position_2darray * pp2DTicks);

   ::mus::midi::e_file_result GetXFTokens(string2a & token2a, imedia::position_2darray *p2DTicks, base_array<XFLyricsHeader, XFLyricsHeader &> * pxflh2a);

   void seek_begin();
   
   ::mus::midi::e_file_result GetNextEvent(MidiEventV001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk, bool bOnlyMidiTrack);

   ::mus::midi::e_file_result GetNextEvent(MidiEventV001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive, int iTrack);

   ::mus::midi::e_file_result GetXFInfoHeaders(CXFInfoHeaders * pxfihs);

   ::mus::midi::e_file_result GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

   imedia::position CalcTkLength();
   imedia::position GetPosition();
   count GetMidiTrackCount() const;
   count GetActiveMidiTrackCount() const;
   count GetActiveTrackCount() const;
   
   MidiTrack * MidiTrackAt(index iIndex);
   MidiTrack * MidiTrackAt(index iIndex) const;
   MidiTrack * ActiveMidiTrackAt(index iIndex);
   MidiTrackBase * ActiveTrackAt(index iIndex);
   void DeactivateTrack(MidiTrackBase * ptrack);

   ::mus::midi::file_flags & GetFlags();
   ::mus::midi::e_file_result WorkQuantizeVR();
   bool WorkGetLongestSoftKaraokeLyrics(string &str);
   void SetAutoAllocation(bool bSet = true);
   MidiLyricTrack * CreateLyricTrack();
   void remove_at(index iIndex);

};


