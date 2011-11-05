#pragma once


class midi_player;
class midi_player_command;
class midi_sequence_thread;

namespace mus
{

   namespace midi
   {

      typedef struct tag_midiDoneData MIDIDONEDATA, * LPMIDIDONEDATA;
      class file;
      class sequence;

   } // namespace midi

} // namespace mus


#define EVENT_ID_PAD 7
#define EVENT_ID_NOTE_ON 15
#define EVENT_ID_LYRIC_V1 5
#define EVENT_ID_LYRICS_V1 7
#define EVENT_ID_LYRICS_V2 8


enum EMidiPlayerCommand
{
   MidiPlayerCommandPlay,
   MidiPlayerCommandCloseDevice,
   MidiPlayerCommandStop,
   MidiPlayerCommandStopAndRestart
};


//   Extra SMF and KAR Format

//#define   MIDI_META_KAR_LYRICS            ((BYTE)0x01)
//#define   MIDI_META_KAR_HEADER            ((BYTE)0x03)


#define MAX_TICKS           ((imedia::position)0xFFFFFFFFL)

//#define SMF_SUCCESS         (0L)
//#define SMF_INVALID_FILE    (1L)
//#define SMF_NO_MEMORY       (2L)
//#define SMF_OPEN_FAILED     (3L)
//#define SMF_INVALID_TRACK   (4L)
//#define SMF_META_PENDING    (5L)
//#define SMF_ALREADY_OPEN    (6L)
//#define SMF_END_OF_TRACK    (7L)
//#define SMF_NO_META         (8L)
//#define SMF_INVALID_PARM    (9L)
//#define SMF_INVALID_BUFFER  (10L)
//#define SMF_END_OF_FILE     (11L)
//#define SMF_REACHED_TKMAX   (12L)

//SMF.c
//#define SMF_F_EOF               0x00000001L
//#define SMF_F_INSERTSYSEX       0x00000002L


//#define SMF_INVALID_TKPOSITION  (13L)

/* Handle structure for HSMF
*/

#define SMF_TF_EOT          0x00000001L
#define SMF_TF_INVALID      0x00000002L


namespace mus
{
   enum EStorage
   {
      StorageNone,
      StorageCopy,
      StorageOwn,
      StorageAttach,
   };
}


typedef DWORD SMFRESULT;
class LyricEventsV1;

typedef base_array<LyricEventsV1 *, LyricEventsV1 *> EventsTracksV1;

class midi_event_base;

class CLASS_DECL_ca MidiTempoMapEntry
{
public:
   MidiTempoMapEntry()
   {
      tkTempo  = 0;
      msBase   = 0;
      dwTempo  = 0;
   }

   imedia::position           tkTempo;
   DWORD           msBase;
   DWORD           dwTempo;
};

class MidiTempoMapEntryArray :
   public base_array<MidiTempoMapEntry, MidiTempoMapEntry &>
{
public:
};




//typedef struct tag_smf *PSMF;





//DWORD FNLOCAL smfGetVDword(
//    byte *              hpbImage,
  //  DWORD               dwLeft,
    //DWORD *            pdw);

/*
** Useful macros when dealing with hi-lo format integers
*/
#define DWORDSWAP(dw) \
    ((((dw)>>24)&0x000000FFL)|\
    (((dw)>>8)&0x0000FF00L)|\
    (((dw)<<8)&0x00FF0000L)|\
    (((dw)<<24)&0xFF000000L))

#define WORDSWAP(w) \
    ((((w)>>8)&0x00FF)|\
    (((w)<<8)&0xFF00))

#define FOURCC_RMID     mmioFOURCC('R','M','I','D')
#define FOURCC_data     mmioFOURCC('d','a','t','a')
#define FOURCC_MThd     mmioFOURCC('M','T','h','d')
#define FOURCC_MTrk     mmioFOURCC('M','T','r','k')
#define FOURCC_XFIH     mmioFOURCC('X','F','I','H')
#define FOURCC_XFKM     mmioFOURCC('X','F','K','M')

typedef struct CLASS_DECL_ca tag_chunkhdr
{
    FOURCC  fourccType;
    DWORD   dwLength;
}   CHUNKHDR,
    *PCHUNKHDR;

#pragma pack(1)   // override cl32 default packing, to match disk spfile->
typedef struct CLASS_DECL_ca tag_midifilehdr
{
    WORD    wFormat;
    WORD    wTracks;
    WORD    wDivision;
    DWORD  GetQuarterNoteTicks()
    {
        return WORDSWAP(wDivision) & ~0x80000000;
    }
}   MIDIFILEHDR,
    *LPMIDIFILEHDR;
#pragma pack()

/* NOTE: This is arbitrary and only used if there is a tempo ::collection::map but no
** entry at tick 0.
*/
typedef struct CLASS_DECL_ca tag_keyframe
{
    /*
    ** Meta events. All FF's indicates never seen.
    */
    BYTE        rbTempo[3];

    /*
    ** MIDI channel messages. FF indicates never seen.
    */
    BYTE        rbProgram[16];
    BYTE        rbControl[16*120];
}   KEYFRAME,
    FAR *PKEYFRAME;

#define KF_EMPTY ((BYTE)0xFF)




//#define MIDI_DEFAULT_TEMPO      (500000L)

//#define MIDI_MSG                ((BYTE)0x80)
//#define MIDI_NOTEOFF            ((BYTE)0x80)
//#define MIDI_NOTEON             ((BYTE)0x90)
//#define MIDI_POLYPRESSURE       ((BYTE)0xA0)
//#define MIDI_CONTROLCHANGE      ((BYTE)0xB0)
//#define MIDI_PROGRAMCHANGE      ((BYTE)0xC0)
//#define MIDI_CHANPRESSURE       ((BYTE)0xD0)
//#define MIDI_PITCHBEND          ((BYTE)0xE0)
//#define MIDI_META               ((BYTE)0xFF)
//#define MIDI_SYSEX              ((BYTE)0xF0)
//#define MIDI_SYSEXEND           ((BYTE)0xF7)

//#define MIDI_META_TRACKNAME     ((BYTE)0x03)
//#define MIDI_META_EOT           ((BYTE)0x2F)
//#define MIDI_META_TEMPO         ((BYTE)0x51)
//#define MIDI_META_TIMESIG       ((BYTE)0x58)
//#define MIDI_META_KEYSIG        ((BYTE)0x59)
//#define MIDI_META_SEQSPECIFIC   ((BYTE)0x7F)




//DECLARE_HANDLE(HSMF);

//typedef struct tag_smfopenstruct
//{
//    char *               pstrName;
//   LPTSTR               pstrName;
//    DWORD               dwTimeDivision;
//    HSMF                hSmf;
//}   SMFOPENFILESTRUCT,
//    FAR *PSMFOPENFILESTRUCT;

typedef struct tag_smffileinfo
{
    DWORD               dwTracks;
    DWORD               dwFormat;
    DWORD               dwTimeDivision;
    imedia::position               tkLength;
}   SMFFILEINFO,
    FAR *PSMFFILEINFO;



/* buffer described by LPMIDIHDR is in polymsg format, except that it
** can contain meta-events (which will be ignored during playback by
** the current system). This means we can use the pack functions, etc.
*/
#define PMSG_META       ((BYTE)0xC0)

class midi_player;




namespace mus
{

   namespace midi
   {

      enum
      {
         Msg               = 0x80,
         NoteOff           = 0x80,
         NoteOn            = 0x90,
         PolyPressure      = 0xA0,
         ControlChange     = 0xB0,
         ProgramChange     = 0xC0,
         ChanPressure      = 0xD0,
         PitchBend         = 0xE0,
         SysEx               = 0xF0,
         SysExEnd            = 0xF7,
         Meta               = 0xFF,
      };

      enum e_control_change
      {
         ControlChangeExpressionController   = 11,
         ControlChangeSostenuto              = 66,
      };

      enum e_meta
      {
         MetaTrackName            = 0x03,
         MetaEOT                  = 0x2F,
         MetaTempo               = 0x51,
         MetaTimeSig               = 0x58,
         MetaKeySig               = 0x59,
         MetaSeqSpecific         = 0x7F,
         MetaLyric               = 0x05,
         MetaXFLyricsHeader      = 0x07,
         MetaCuePoint            = 0x07,
         MetaChannelPrefix       = 0x20,
         MetaKarLyric            = 0x01,
         MetaKarHeader            = 0x01,
      };



      namespace player
      {
         enum ENotifyEvent
         {
            NotifyEventPlaybackStart,
            NotifyEventPlaybackEnd,
            NotifyEventStop,
            NotifyEventGenericMmsgDone,
            NotifyEventPositionSet,
            NotifyEventSetSequence,
            NotifyEventMidiStreamOut,
         };

      class NotifyEvent
      {
      public:
         midi_player *   m_pplayer;
         ENotifyEvent   m_enotifyevent;
      };

      } // namespace player

      enum e_file_result
      {
         Success = 0,
         SEventNotFound = 15,
         STrackNotFound = 16,
         SNotFound = 18,
         SEndOfFile = 11,
         SReachedTkMax = 12,
         SMetaPending = 5,
         SNoMeta = 8,
         SEndOfTrack = 7,
         EFail = -1,
         EInvalidFile = -1000,
         ENoMemory = -2,
         EOpenFailed = -3,
         EInvalidTrack = -4,
         EAlreadyOpen = -6,
         EInvalidParam = -9,
         EInvalidBuffer = -10,
         EInvalidTkPosition = 13,
         ESaveFailed = 14,
         EFunctionNotSupported = 17,
      };


      enum e_file_open_mode
      {
         OpenForPlaying,
         OpenForParsing,
         OpenForParsingLevel2,
         OpenForParsingLevel3,
         OpenForHeaders,
      };

      enum e_file_seek
      {
         SeekXFInfoHeader = 1,
         SeekXFInfoHeaderLS = 2,
         SeekXFSongName = 3,
         SeekKarID = 4,
         SeekXFLyricsHeader = 7,
      };

      enum e_file_flag
      {
         EndOfFile, // end of file
         EndOfTrack = EndOfFile, // end of track
         InsertSysEx,
         Opened,
         Expanded,
         DisablePlayLevel1Operations,
         DisableMute,
         FlagCount,
      };


      enum e_file_type
      {
         TypeNull = 0,
         TypeXF = 1,
         TypeKar = 2,
         TypeTune1000 = 3,
         TypeGM = 4
      };


      class CLASS_DECL_ca file_flags :
         public ::flags < e_file_flag >
      {
      public:
      };


      CLASS_DECL_ca MMRESULT TranslateSMFResult(::mus::midi::e_file_result smfrc);
      CLASS_DECL_ca DWORD GetVDWord(byte * & hpbMidiStream, DWORD dwLeft, DWORD &dwValue);
      CLASS_DECL_ca int GetMessageLen(BYTE bEvent);
      CLASS_DECL_ca VMSRESULT SelectTypeCombo(simple_combo_box * lpcombo, midi_event_base * lpevent);
      CLASS_DECL_ca VMSRESULT SelectPitchCombo(simple_combo_box * lpcombo, midi_event_base * lpevent);
      CLASS_DECL_ca VMSRESULT FillPitchCombo(simple_combo_box * lpcombo);
      CLASS_DECL_ca VMSRESULT FillTypeCombo(simple_combo_box * lpcombo);
      CLASS_DECL_ca double GetNoteFrequency(double dA3Frequency,BYTE bNote);
      CLASS_DECL_ca DWORD GetStateMaxSize(void);




      CLASS_DECL_ca extern const UINT grbChanMsgLen[];
      CLASS_DECL_ca extern const UINT voiceText[];
      CLASS_DECL_ca extern const char pitchText[][5];
      CLASS_DECL_ca extern const DWORD DefaultTempo;

   } // namespace midi

} // namespace mus
