#pragma once

class CTune1000Info;
class midi_events_v1;
class midi_track_base;
class midi_lyric_track;


class CLASS_DECL_ca midi_tracks :
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
      
      array_ptr < midi_track_base >   m_tracka;
      array_ptr_copy < midi_track >        m_miditracka;
      array_ptr_copy < midi_lyric_track >   m_lyrictracka;
      midi_tracks   *                       m_ptracks;
      
   public:
      count GetTrackCount() const;
      count GetMidiTrackCount() const;
      count GetLyricTrackCount();
      midi_track_base * TrackAt(index iIndex);
      midi_lyric_track * LyricTrackAt(index iIndex);
      midi_track * MidiTrackAt(index iIndex);
      midi_track * MidiTrackAt(index iIndex) const;

      TrackPtrAllocArray(::ca::application * papp);
      void Initialize(midi_tracks * ptracks);
      void RemoveAllMidiTracks();
      void RemoveTrack(midi_track_base * ptrack);
      void remove_all();
      void remove_at(index iIndex);

      midi_track * CreateTrack(index iIndex, FOURCC fourcc = FOURCC_MTrk);
      midi_track * CreateTrack(FOURCC fourcc = FOURCC_MTrk);
      midi_lyric_track * CreateLyricTrack(index iIndex);
      midi_lyric_track * CreateLyricTrack();

      void copy(TrackPtrAllocArray & base_array);
   };

   class TrackPtrArray
   {
   protected:
   
      array_ptr < midi_track_base >   m_tracka;
      array_ptr < midi_track >       m_miditracka;
      array_ptr < midi_lyric_track >  m_lyrictracka;
      midi_tracks   *                       m_ptracks;

   public:
      count GetTrackCount() const;
      count GetMidiTrackCount() const;
      count GetLyricTrackCount();
      midi_track_base * TrackAt(index iIndex);
      midi_lyric_track * LyricTrackAt(index iIndex);
      midi_track * MidiTrackAt(index iIndex);

   public:
      TrackPtrArray();
      void Initialize(midi_tracks * ptracks);
      void RemoveAllMidiTracks();
      void RemoveTrack(midi_track_base * ptrack);
      void remove_all();
      void remove_at(index iIndex);

      void copy(TrackPtrAllocArray & base_array);

      TrackPtrArray & operator = (TrackPtrAllocArray & base_array);
   };

   midi_event_v008              m_midieventVolume;
   midi_event_v001              m_midieventV001Volume;
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


   midi_tracks(::ca::application * papp, ::mus::midi::file * pFile = NULL);
   virtual ~midi_tracks();


   void dump(dump_context & dumpcontext) const;

   bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);
   bool IsXFFile();
   bool IsTune1000File();

   VMSRESULT WorkCompactTracks(midi_track & trackUnion, bool bOnlyMTrk);

   VMSRESULT WorkCompactMidiTracks(midi_track & trackUnion, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetNextEvent(midi_event_v008 * & ppevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetNextRawEvent(midi_event_v008 * & ppevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetNextRawMidiEvent(midi_event_v008 * & ppevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk);

   void WorkSeekBegin();
   void WorkSeekEnd();

   VMSRESULT WorkCompactTracksWork(midi_track & trackUnion, bool bOnlyMTrk);

   VMSRESULT WorkCompactMidiTracksWork(midi_track & trackUnion, bool bOnlyMTrk);

   ::mus::midi::e_file_result WorkGetXFTokens(UINT uiCodePage, string2a & token2a, imedia::position_2darray * p2DTicks, ::mus::xf_lyrics_id_array * pxflh2a);

   ::mus::midi::e_file_result WorkGetXFTokens(UINT uiCodePage, string2a & token2a, imedia::position_2darray & p2DTicks, int2a & i2aTokenLine, ::mus::xf_lyrics_id_array * pxflh2a);

   ::mus::midi::e_file_result WorkGetEmptyXFTokens(int iTrack, string2a & token2a, imedia::position_2darray & p2DTicks, ::mus::xf_lyrics_id_array * pxflh2a);

   ::mus::midi::e_file_result WorkGetSoftKaraokeTokens(string2a & token2a, imedia::position_2darray *p2DTicks, ::mus::xf_lyrics_id_array * pxflh2a);
   
   int CalcMelodyTrack(midi_events_v1 ** ppEvents, imedia::position_array *p1DTokens, WORD   wFileFormat);

   int WorkCalcMelodyTrack(midi_events_v1 ** ppEventsRet, imedia::position_array & positiona, int_array & iaTokenLine, WORD wFileFormat);

   static BYTE m_paramEventNoteOnPositionCB[];
   static int m_iparamEventNoteOnPositionCB;
   
   ::mus::midi::e_file_result GetKarInfoHeader(SoftKaraokeInfo *pKarI);

   ::mus::midi::e_file_result GetTune1000InfoHeader(CTune1000Info *pTune1000I, int iTrack);

   void RemoveAllMidiTracks();
   count GetTrackCount();
   midi_track_base * TrackAt(index iIndex);
   midi_track * CreateTrack(FOURCC fourcc = FOURCC_MTrk);
   void remove_all();
   void clear();
   midi_track * CreateTrack(index iIndex, FOURCC fourcc = FOURCC_MTrk);
   bool WorkGetLongestXFLyrics(string &str);
   ::mus::midi::e_file_result GetVolumeEvent(::ca::application * papp, midi_event_v008 *& pevent);
   ::mus::midi::e_file_result GetVolumeEvent(::ca::application * papp, midi_event_v001 *& pevent);
   void OnStop();
   midi_track * seek(DWORD dwSeekWhat);

   bool m_bVolumeEventSent;
   VMSRESULT GetLyricDelay(int * lpiDelay);
   VMSRESULT SetLyricDelay(int iDelay);
   index GetMidiTrackIndex(index iIndex);
   
   VMSRESULT CompactTracks(midi_track & trackUnion, bool bOnlyMTrk, bool bOnlyMidiTrack);

   VMSRESULT ExpandTrack(index iTrackIndex);
   void ToWorkStorage();
   void FromWorkStorage();


   ::mus::midi::e_file_result GetKarTokens(string2a & token2a, imedia::position_2darray * pp2DTicks);

   ::mus::midi::e_file_result GetXFTokens(string2a & token2a, imedia::position_2darray *p2DTicks, ::mus::xf_lyrics_id_array * pxflh2a);

   void seek_begin();
   
   ::mus::midi::e_file_result GetNextEvent(midi_event_v001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive, bool bOnlyMTrk, bool bOnlyMidiTrack);

   ::mus::midi::e_file_result GetNextEvent(midi_event_v001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive, int iTrack);

   ::mus::midi::e_file_result GetXFInfoHeaders(CXFInfoHeaders * pxfihs);

   ::mus::midi::e_file_result GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

   imedia::position CalcTkLength();
   imedia::position get_position();
   count GetMidiTrackCount() const;
   count GetActiveMidiTrackCount() const;
   count GetActiveTrackCount() const;
   
   midi_track * MidiTrackAt(index iIndex);
   midi_track * MidiTrackAt(index iIndex) const;
   midi_track * ActiveMidiTrackAt(index iIndex);
   midi_track_base * ActiveTrackAt(index iIndex);
   void DeactivateTrack(midi_track_base * ptrack);

   ::mus::midi::file_flags & GetFlags();
   ::mus::midi::e_file_result WorkQuantizeVR();
   bool WorkGetLongestSoftKaraokeLyrics(string &str);
   void SetAutoAllocation(bool bSet = true);
   midi_lyric_track * CreateLyricTrack();
   void remove_at(index iIndex);

};


