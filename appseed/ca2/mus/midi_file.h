#pragma once

#define C_TEMPO_MAP_CHK     16

class LyricEventV1;
class midi_events_v1;
class midi_event_v001;
class midi_event_v007;
class midi_event_v008;
class midi_event_v016;
class midi_tracks;
class XFInfoHeader;


namespace mus
{

   namespace midi
   {

      class CLASS_DECL_ca file :
         virtual public primitive::memory_container
      {
      public:

         class CMidiStreamEventHeader
         {
         public:
            DWORD m_dwLength;
            DWORD m_dwType;
         };

         mus::EStorage                       m_estorage;
         imedia::position                    m_positionLastWorkRender;
         primitive::memory                   m_memstorageF1;
         file_flags                    m_flags;
         int                                 m_iKeyShift;
         int                                 m_iTempoShift;
         KEYFRAME                            m_keyframe;
         DWORD                               m_dwMelodyTrack;
         DWORD                               m_dwLyricTrack;
         int_array                           m_iaMuteTrack;
         imedia::position                     m_tkLastDelta;
         sequence *                     m_psequence;
         base_array < EventsTracksV1 * >     m_evtrkv1ptraSeek;

         imedia::position                     m_tkLength;
         DWORD                                 m_dwFormat;
         DWORD                                 m_dwTracks;
         DWORD                                 m_dwTimeDivision;

         int                                 m_iOpenMode;

         string                              m_strName;

         CHUNKHDR *                           m_pMThd;
         MIDIFILEHDR *                        m_pFileHeader;

         MidiTempoMapEntryArray              m_tempomap;

         DWORD                                 m_dwPendingUserEvent;
         DWORD                                 m_cbPendingUserEvent;
         byte *                              m_hpbPendingUserEvent;


         primitive_array < midi_event_v008 *>  m_mepaImmediate;
         primitive_array < midi_event_v008 *>  m_mepaOnQuarterNote;

         midi_event_v008 *                     m_pmePendingLyric;
         bool                                m_bPendingLyric;

         midi_tracks *                        m_ptracks;

         double GetTempoShiftRate();
         midi_tracks & GetTracks();
         file_flags & GetFlags();
         bool IsTrackMute(int iIndex);
         void MuteAll(bool bMute = true, int iExcludeTrack = -1);
         void MuteTrack(int iIndex, bool bMute = true);

         e_file_result WorkSeekBegin();
         e_file_result CalcTkLength();
         e_file_result CreateTempoMap();
         MMRESULT ImmediatePutTempoChange();
         VMSRESULT GetTempoEvent(midi_event_base & event);
         void OnStop();
         DWORD GetImageSize();
         LPBYTE GetImage();
         VMSRESULT Format0();
         VMSRESULT InsertTempoEvent();
         MidiTempoMapEntry * GetTempoMapEntry(const imedia::position & position);
         int GetTempoShift();
         VMSRESULT SetTempoShift(int iTempoShift);
         void ToWorkStorage();
         void FromWorkStorage();
         int GetKeyShift();
         int SetKeyShift(int iKeyShift);


         bool IsSoftKaraokeFile(bool bWork = false, stringa * pstra = NULL);
         bool IsXFFile();
         bool IsTune1000File();


         bool IsOpened();
         critical_section   m_cs;
         e_file_result RebuildIndex();
         e_file_result WriteHeader(MIDIFILEHDR * lpmfh);
         e_file_result ChangeEventDelta(midi_event_base *pEvent, imedia::position tkNewDelta);
         e_file_result ReplaceSameDeltaEvent(midi_event_base & pEventNew);
         //   VMSRESULT allocate(DWORD dwNewLength);
         //VMSRESULT allocate_add_up(DWORD dwAddUp);

         e_file_result GetPreviousEvent(
            midi_event_base * pPreviousEvent,
            midi_event_base * pEvent);
         //e_file_result DeleteEvent(midi_event_base  *pEvent);
         e_file_result SaveFile(const char * lpFilePath);


         e_file_result WorkWriteXFTracks(
            stringa &  tokena,
            imedia::position_array & positiona,
            XFInfoHeader & xfinfoheader);



         int CalcMelodyTrack(midi_events_v1 ** ppEvents, imedia::position_array * pTicks);

         int WorkCalcMelodyTrack(
            midi_events_v1 ** ppEvents, 
            imedia::position_array & positiona,
            int_array & iaTokenLine);



         int GetFormat();
         //   e_file_result MergeTracks(
         //      CHUNKHDR *   pCh,
         //      MIDIFILEHDR *   pFh);
         //   e_file_result MergeWorkTracks(
         //      CHUNKHDR *   pCh,
         //      MIDIFILEHDR *   pFh);
         e_file_result MergeTracks();
         e_file_result WorkMergeTracks();

         e_file_result WorkStreamRender(
            LPMIDIHDR lpmh,
            imedia::position tkMax,
            DWORD cbPrerollNomimalMax);

         e_file_result WorkGetNextEvent(
            midi_event_v008 *&    pevent,
            imedia::position                tkMax,
            BOOL                  bTkMaxInclusive);

         e_file_result WorkGetNextRawEvent(
            midi_event_v008 *&    pevent,
            imedia::position                tkMax,
            BOOL                  bTkMaxInclusive);

         e_file_result WorkGetNextRawMidiEvent(midi_event_v008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

         e_file_result WorkSeek(imedia::position tkPosition, LPMIDIHDR lpmh);

         file(::ca::application * papp);
         virtual ~file();

         void delete_contents();


         int GetDivision();
         imedia::position get_position();
         void AttachSeekSync(EventsTracksV1 * ptracksv1);

         bool IsNull();

         void WorkSeekEnd();

         e_file_result OpenFile(
            file &file,
            int openMode);

         e_file_result OpenFile(
            ex1::file & file,
            int openMode);

         e_file_result OpenFile(
            primitive::memory * pmemstorage,
            int openMode,
            mus::EStorage);

         e_file_result OpenFile(
            primitive::memory *  pmemstorage,
            e_file_open_mode eopenmode,
            mus::EStorage estorage);

         e_file_result SaveFile(
            ex1::file & file);

         e_file_result CloseFile();

         e_file_result GetFileInfo(
            PSMFFILEINFO psfi);

         DWORD TicksToMillisecs(
            imedia::position tkOffset);

         void TicksToMillisecs(
            imedia::time_array *pMillisArray,
            imedia::position_array *pTickArray,
            int tkOffset);

         void TicksToMillisecs(imedia::time_2darray *p2DMillisArray, imedia::position_2darray * p2DTicksArray, int tkOffset);

         void PositionToTime(imedia::time_2darray  & timea, imedia::position_2darray  & positiona, int tkOffset);

         void PositionToTime(imedia::time_array  & timea, imedia::position_array  & positiona, int tkOffset);

         imedia::position MillisecsToTicks(imedia::time msOffset);

         imedia::time PositionToTime(imedia::position msOffset);

         imedia::position TimeToPosition(imedia::time msOffset);

         void MillisecsToTicks(imedia::position_array * pTickArray, imedia::time_array *pMillisArray, imedia::time msOffset);

         void TimeToPosition(imedia::position_array & positiona, imedia::time_array & timea, imedia::time msOffset);

         e_file_result StreamRender(LPMIDIHDR lpmh, imedia::position tkMax, DWORD cbPrerollNomimalMax);

         VMSRESULT StreamEvent(imedia::position tkDelta, midi_event_base * Event, LPMIDIHDR lpmh, imedia::position tkMax, DWORD cbPrerollNomimalMax);

         VMSRESULT StreamEventF1(imedia::position tkDelta, base_array < midi_event_v008 *, midi_event_v008 * > & eventptra, LPMIDIHDR lpmh, imedia::position tkMax, DWORD cbPrerollNomimalMax);

         e_file_result seek(imedia::position tkPosition, LPMIDIHDR lpmh);

         e_file_result seek(imedia::position tkPosition);

         e_file_result Build();

         e_file_result GetNextEvent(midi_event_v001 *& pevent, imedia::position tkMax, BOOL   bTkMaxInclusive);

         e_file_result GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

         void _SyncSeek(imedia::position tkPosition, EventsTracksV1 * ptracksv1);
         void _SyncSeek(imedia::position tkPosition);
         e_file_result InsertParmData(imedia::position tkDelta, LPMIDIHDR lpmh);

         VMSRESULT InsertLyricEvents(LyricEventV1 * pLyricEvent, LPMIDIHDR lpmh);

         e_file_result InsertPadEvent(imedia::position tkDelta, LPMIDIHDR lpmh);

         void SetOpened(bool bOpened = true);
      };

   } // namespace midi

} // namespace mus