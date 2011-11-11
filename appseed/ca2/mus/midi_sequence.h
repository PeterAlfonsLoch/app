#pragma once


#define  VERSION_MINOR              0x00
#define  VERSION_MAJOR              0x04
#define  SEQ_VERSION                ((DWORD)(WORD)((BYTE)VERSION_MINOR | (((WORD)(BYTE)VERSION_MAJOR) << 8)))

//#define SEQ_F_EOF           0x00000001L
//#define SEQ_F_COLONIZED     0x00000002L
//#define SEQ_F_WAITING       0x00000004L
//#define SEQ_F_SETTING_POS   0x00000008L

//#define SEQ_S_NOFILE        0
//#define SEQ_S_OPENED        1
//#define SEQ_S_PREROLLING    2
//#define SEQ_S_PREROLLED     3
//#define SEQ_S_PLAYING       4
//#define SEQ_S_PAUSED        5
//#define SEQ_S_STOPPING      6
//#define SEQ_S_RESET         7

#define MMSG_DONE                   (WM_USER+20)




namespace mus
{

   namespace midi
   {

      typedef struct tag_preroll
      {
         imedia::position       tkBase;
         imedia::position       tkEnd;
      } PREROLL, FAR *LPPREROLL;

      struct midi_callback_data
      {
         sequence *          m_psequence;
      };






      class CLASS_DECL_ca sequence :
         virtual public ikar::karaoke
      {
      public:
         class BufferArray;

         class buffer
         {
         public:
            bool IsPrepared();
            MMRESULT midiStreamOut(HMIDISTRM hmidiout);
            MMRESULT midiOutPrepareHeader(HMIDIOUT hmidiout);
            friend class BufferArray;

            LPMIDIHDR GetMidiHdr();
            MMRESULT midiOutUnprepareHeader(HMIDIOUT hmidiout);
            void Reset();
            void Initialize(int iSize, DWORD dwUser);
            void SetNextMidiHdr(LPMIDIHDR);
            MIDIHDR              m_midihdr;
            primitive::memory       m_storage;
            bool                 m_bPrepared;
         };

         class BufferArray :
            public base_array < buffer, buffer >
         {
         public:
            MMRESULT midiStreamOut(HMIDISTRM hmidiout);
            MMRESULT midiOutPrepareHeader(HMIDIOUT hmidiout);
            MMRESULT midiOutUnprepareHeader(HMIDIOUT hmidiout);
            void Reset();
            void Initialize(int iCount, int iSize, DWORD dwUser);
         };

         enum e_flag
         {
            FlagNull                        = (long) 0x00000000,
            FlagEOF                        = (long) 0x00000001,
            FlagColonized                 = (long) 0x00000002,
            FlagWaiting                   = (long) 0x00000004,
            FlagSettingPos                  = (long) 0x00000008,
            FlagIsInSpecialModeV001       = (long) 0x00000010,
            FlagWasInSpecialModeV001      = (long) 0x00000020,
            FlagSpecialModeV001End        = (long) 0x00000040,
            FlagTempoChange               = (long) 0x00000080,
            FlagStop                        = (long) 0x00000100,
            FlagMidiOutDeviceChange         = (long) 0x00000200,
            FlagStopAndRestart            = (long) 0x00000400,

         };

         class flags :
            public ::flags<e_flag>
         {
         public:
         };

         enum SpecialModeV001Operations
         {
            SPMV001GMReset = 1,
            SPMV001TempoChange = 2
         };
         enum Status
         {
            StatusNoFile = 0,
            StatusOpened = 1,
            StatusPreRolling = 2,
            StatusPreRolled = 3,
            StatusPlaying = 4,
            StatusPaused = 5,
            StatusStopping = 6,
            StatusReset = 7,
            Success = 8
         };


         enum e_event
         {
            EventMidiPlaybackStart,
            EventStopped,
            EventMidiPlaybackEnd,
            EventMidiStreamOut,
            EventSpecialModeV001End,
         };

         class Event
         {
         public:
            e_event            m_eevent;
            sequence *    m_psequence;
            LPMIDIHDR         m_lpmh;
         };

         class PlayerLink
         {
         public:
            void ModifyFlag(e_flag eflagAdd, e_flag eflagRemove);
            bool TestFlag(e_flag eflag);
            void SetFlag(e_flag eflag);
            e_flag GetFlag();
            e_flag                  m_eflag;
            imedia::position                  m_tkRestart;
            ::ca::smart_pointer < midi_player_command >  m_spcommand;
            void OnFinishCommand(EMidiPlayerCommand ecommand);
            void SetCommand(midi_player_command * pcommand);
            PlayerLink();
         };

         BufferArray     m_buffera;

         event  m_evMmsgDone;

         event            m_eventMidiPlaybackEnd;
         mutex            m_mutex;
         UINT           m_uiDeviceID;          /* Requested MIDI device ID for MMSYSTEM        */
         UINT           m_uiState;             /* Sequencer state (SEQ_S_xxx)                  */
         UINT            m_uiPreviousState;
         UINT           m_uiPreSpecialModeV001State;


         imedia::position          m_tkLength;           /* Length of longest track                      */
         MMRESULT       m_mmrcLastErr;        /* Error return from last sequencer operation   */

         DWORD            m_msLength;
         gen::memory_file    m_memfile;

         file *      m_pfile;
         HMIDISTRM      m_hMidiStream;

         UINT           m_uiSpecialModeV001Operation;
         int_array   m_iaLevel;
         DWORD       m_dwTimeDivision;     /* File time division                           */

         LPBYTE      m_lpbAlloc;           /* Streaming buffers -- initial allocation      */
         DWORD       m_cbPreroll;          /* Streaming buffers -- size of lpmhPreroll     */
         DWORD       m_cbPrerollNominalMax;
         UINT        m_uBuffersInMMSYSTEM; /* Streaming buffers -- in use                  */
         imedia::position       m_tkPrerollBase;

         imedia::position    m_tkBase;             /* Where playback started from in stream        */
         imedia::position    m_tkEnd;              /* Where playback should end                    */

         flags                     m_flags; /* Various sequencer flags  */
         int                     m_iOpenMode;

         midi_callback_data m_midicallbackdata;
         PlayerLink   m_playerlink;
         ::event       m_evBuffersZero;
         //DWORD          m_cBuffer;            /* Number of streaming buffers to alloc         */
         DWORD          m_cbBuffer;           /* size of each streaming buffer                */
         //UINT           m_uMCIDeviceID;       /* Our MCI device ID given to us                */
         //UINT           m_uMCITimeFormat;     /* Current time format                          */
         //UINT           m_uMCITimeDiv;        /* MCI_SEQ_DIV_xxx for current file             */
         //HWND                     m_hWnd;            /* Where to post MMSG_DONE when done playing   */
         midi_sequence_thread *    m_pthread;




         sequence(::ca::application * papp);
         virtual ~sequence();
         file & GetFile();

         PlayerLink & GetPlayerLink();
         inline UINT GetState();
         inline UINT GetPreviousState();
         UINT SetState(UINT uiState);

         void SetSpecialModeV001Flag(bool bSet = true);

         void MuteAll(bool bMute = true, int iExcludeTrack = -1);
         void MuteTrack(int iIndex, bool bMute = true);


         virtual int GetDefaultCodePage();

         void Prepare(ikar::data & data);
         void Prepare(int iTrack, ikar::data & data);
         void Prepare(
            string2a & str2a,
            imedia::position_2darray & tka2DTokensTicks,
            int iMelodyTrack,
            int2a & ia2TokenLine,
            ikar::data & data);

         imedia::position GetPositionTicks();
         void OnEvent(e_event event);
         void OnEvent(Event * pevent);
         void SetLevelMeter(int iLevel);
         MMRESULT CloseStream();
         bool SetMidiOutDevice(UINT uiDevice);
         int SetKeyShift(int iKeyShift);
         int GetKeyShift();

         void OnMidiPlaybackEnd(sequence::Event * pevent);
         int SetTempoShift(int iTempoShift);

         sequence & GetMidiSequence();
         void OnPositionCB(LPMIDIHDR lpmidihdr);
         void OnDone(HMIDISTRM hmidistream, LPMIDIHDR lpmidihdr);
         virtual void GetTimeLength(imedia::time & time);
         virtual void GetPositionLength(imedia::position & position);

         using ::ikar::karaoke::TimeToPosition;
         using ::ikar::karaoke::PositionToTime;

         virtual imedia::position TimeToPosition(imedia::time time);
         virtual imedia::time PositionToTime(imedia::position position);

         virtual bool IsOpened();

         bool IsNull();
         void SetTempoChangeFlag(bool bSet = true);
         bool IsChangingTempo();

         int GetTempoShift();
         void GetMidiDoneData(LPMIDIDONEDATA lpmdd);
         bool IsInSpecialModeV001();
         bool WasInSpecialModeV001();
         void SetSpecialModeV001Operation(UINT uiOperation);


         MMRESULT AllocBuffers();

         VOID FreeBuffers();

         //MMRESULT OpenFile(const char * lpFileName, int openMode);
         MMRESULT OpenFile(sequence & sequence, int iOpenMode);
         MMRESULT OpenFile(ex1::file & ar, int openMode);
         MMRESULT OpenFile(const char * lpFileName, int openMode);
         MMRESULT OpenFile(primitive::memory * pmemorystorage, int openMode, mus::EStorage estorage);

         MMRESULT CloseFile();
         MMRESULT SaveFile(const char * lpFileName);
         MMRESULT SaveFile();
         MMRESULT SaveFile(ex1::filesp &ar);
         MMRESULT Preroll(::radix::thread * pthread, LPPREROLL lpPreroll, bool bThrow);
         MMRESULT Start();

         MMRESULT Pause();

         MMRESULT Restart();

         //MMRESULT Stop(DWORD dwEllapse);
         MMRESULT Stop();

         void get_position(imedia::position  & time);
         void get_time(imedia::time  & time);

         MMRESULT GetTicks(imedia::position & time);
         MMRESULT GetMillis(imedia::time & time);


         imedia::position MillisecsToTicks(imedia::time msOffset);

         DWORD TicksToMillisecs(imedia::position tkOffset);

         bool IsPlaying();

         /*   void MidiOutCallbackDeprecated(
         HMIDISTRM hms,
         UINT uMsg,
         DWORD dwUser,
         DWORD dw1,
         DWORD dw2,
         midi_player * lpMidiPlayer,
         CXfplayerView * pview);*/
         static void CALLBACK MidiOutProc(HMIDIOUT hmo, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

         BOOL IsSettingPosition();
         void SetSettingPositionFlag(BOOL bSet = TRUE);

         imedia::position GetQuarterNote();
      };



      typedef struct tag_midiDoneData
      {

         sequence::flags         m_flags;
         UINT                    m_uiSeqState;
         UINT                    m_uiSeqPreviousState;

         inline bool SequenceIsInSpecialModeV001()
         {
            return m_flags.is_signalized(sequence::FlagIsInSpecialModeV001);
         }
         inline bool SequenceWasInSpecialModeV001()
         {
            return m_flags.is_signalized(sequence::FlagWasInSpecialModeV001);
         }
         inline UINT SequenceGetPreviousState()
         {
            return m_uiSeqPreviousState;
         }
         inline UINT SequenceGetState()
         {
            return m_uiSeqState;
         }

      } MIDIDONEDATA, * LPMIDIDONEDATA;


   } // namespace midi


} // namespace mus
