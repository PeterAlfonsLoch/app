#pragma once

class ::userbase::single_document_template;

#include "document.h"
#include "AudioSpectrumDoc.h"

class XfplayerView;


class XfplayerThreadV1;
class XfplayerViewPlaylist;
class XfplayerServerItem;
class AudioSpectrumDoc;
class CLevelMeterDoc;
class CLevelMeterView;
class AudioSpectrumView;
class CPlayerDoc;
//class CPlayerControlSetV19View;
//class CPlayerControlSetV19Frame;
class CKaraokeUtil;
class MidiPlayer;
typedef struct tag_midiDoneData MIDIDONEDATA, * LPMIDIDONEDATA;

typedef struct tag_XfplayerDocInit
{
    XfplayerThreadV1 *    pthreadV1;
} XFPLAYERDOCINIT, * LPXFPLAYERDOCINIT;

class CLASS_DECL_CA2_CUBE XfplayerDoc :
   virtual public mplite::document,
   public pha(PlaylistDoc),
   public pha(AudioSpectrumDoc),
//   public pointer_array<CLevelMeterDoc>,
//   public pointer_array<CPlayerDoc>,
   public vmsp::DocumentInterface
{
public:
   enum EShow
   {
      ShowSongLabelInformation,
   };
   enum EMode
   {
      ModeNone,
      ModeMidi,
      ModeWave,
   };

   enum EFileType
   {
      FileTypeNone,
      FileTypeMidi,
      FileTypeAiff,
      FileTypeMpeg,
      FileTypeTwinVQ,
   };
public:
   XfplayerDoc(::ca::application * papp);
   // // DECLARE_DYNCREATE(XfplayerDoc)

   
   EMode                      m_emode;

   CPlayerDoc *               m_pplayerdoc;
   
   
   

   ::userbase::single_document_template * m_pdoctemplateLevelMeter;
   ::userbase::single_document_template * m_pdoctemplatePlayer;
   AudioSpectrumDoc *         m_paudiospectrumdoc;
   //CLevelMeterDoc *            m_plevelmeterdoc;


   comparable_array < EShow, EShow >   m_eshowaVisible;
   ex1::filesp                      m_fileWave;
// Attributes
public:
    critical_section    m_csSongData;
    critical_section    m_csMidi;
   CEvent            m_evMMDone;
   double            m_CurrentTokenPlayedPercentage;
   //C2DStringPtrArray *   m_p2DTokens;
    bool            m_bPlay;
    MIDIFILEHDR         m_mfh;

   //imedia::time_2darray       m_2DTokensMillis;
   //dword_array         m_DisplayOffsetEvents;
   //dword_array         m_PrePlayOffsetEvents;
   
   imedia::position            m_LyricsDisplayOffset;
   imedia::position            m_LyricsDisplay;
   //XFInfoHeader*      m_pInfoHeader;
   //XFInfoHeaderLS   *   m_pInfoHeaderLS;
   //LPTSTR            m_lpSongName;
   
   bool            m_bHasTitle;
   int               m_iGuessMelodyTrack;
   //bool            m_bIsSoftKaraokeFile;
   base_array<XFLyricsHeader, XFLyricsHeader & > m_xflha;
protected:
    bool                m_bOpening;
   dword_array         m_dwaSongsCodes;
//    bool                m_bSaving;
    bool                m_bClosing;

   PlaylistDoc *      m_pplaylistdoc;
//   DWORD               m_dwCodePage;
   EFileType            m_edocfiletype;
public:


   EFileType GetDocFileType();


   virtual BOOL on_new_document();
   virtual bool on_open_document(var varFile);
   virtual void on_close_document();
   virtual void delete_contents();
   virtual BOOL on_save_document(const char * lpszPathName);

   virtual void on_delete(::ca::ca * pca);
   
   bool IsAudioSpectrumOpened();
//   CLevelMeterDoc * GetLevelMeterDoc();
   AudioSpectrumDoc * GetAudioSpectrumDoc();
//   CLevelMeterDoc * OpenLevelMeterDoc(bool bMakeVisible);
   AudioSpectrumDoc * OpenAudioSpectrumDoc(XfplayerView * pxfplayerview, bool bMakeVisible);
   
protected:
   //::userbase::single_document_template * GetLevelMeterDocTemplate();
   ::userbase::single_document_template * GetAudioSpectrumDocTemplate();
public:
   ex1::filesp & GetWaveFile();
   //bool ExecuteIsPlaying();
   //bool ExecuteIsWaitingToPlay();
   EMode GetMode();
   ::radix::thread * GetMidiPlayerCallbackThread();
   ::radix::thread * HelperGetMidiPlayerCallbackThread();
   void SetLyricDelay(int iDelay);
   int GetGuessingMelodyTrack();
   void OnKaraokeEncodingChange();
   void DBLoadSongEncoding(const char * lpszPathName);
   void DBSaveSongEncoding(const char * lpszPathName);
   //void SetSongEncoding(DWORD dwCodePage);
   DWORD GetSongEncoding();
   
   void Show(EShow eshow, bool bShow);
   bool ShouldShow(EShow eshow);
   
   //void OnMidiPlayerNotifyEvent(MidiPlayer::NotifyEventPostData * pdata);
   //bool IsPlayerControlSetV19ViewOpened();
   bool IsPlayerDocOpened();
/*   CPlayerControlSetV19View * GetPlayerControlSetV19View();
   CPlayerControlSetV19Frame * GetPlayerControlSetV19Frame();*/
   //void OnPointerClear(pointer < CPlayerDoc> * pdoc);
   CPlayerDoc * OpenPlayerDoc(bool bMakeVisible);
   CPlayerDoc * GetPlayerDoc();
   //void CloseAllLevelMeterDocuments();
   void CloseAllAudioSpectrumDocuments();
   //virtual void OnPointerClear(pointer <CLevelMeterDoc > *pdoc);
   virtual void OnPointerClear(AudioSpectrumDoc * pdoc);
   //CTransparentFrameWndV8 * GetLevelMeterFrame();
   simple_frame_window * GetAudioSpectrumFrame();
   //CLevelMeterView * GetLevelMeterView();
   AudioSpectrumView * GetAudioSpectrumView();
   //bool IsLevelMeterOpened();

   virtual void OnChangeMidiPlayerTempoShift();
   virtual void OnChangeMidiPlayerTranspose();

   void OnPointerClear(PlaylistDoc * pdoc);
   PlaylistDoc * DetachPlaylistDoc();
   PlaylistDoc * GetPlaylistDoc();
   bool Attach(PlaylistDoc * pplaylistdoc);
   
   bool IsClosing();
//   bool IsSaving();
   virtual bool do_save(const char * lpszPathName, bool bReplace = true);
   //void UpdateProgress(::userbase::view * pview = NULL);
   int GetNextSong();
   //XfplayerViewPlaylist * GetPlaylistView();
   bool IsOpening();

   
//   void OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents);

   UINT GetMidiSequenceState();
//   inline ::mus::midi::sequence * GetMidiSequence();
   XFInfoHeaderLSArray * GetInfoHeadersLS();
   //XFInfoHeader * GetInfoHeader();
   
   //void SetScoreRate(double dScoreRate);
   XfplayerView * GetLyricView();
   
   
   void ClearTokens();
   //void SetApproximatePosition(double rate);
   void OnPositionCB();
   
   void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata);
   void OnMmsgDone(::mus::midi::sequence *pseq, LPMIDIDONEDATA lpmdd);

   virtual ~XfplayerDoc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

// Generated message ::collection::map functions
protected:
   //{{AFX_MSG(XfplayerDoc)
   afx_msg void OnViewLyrics();
   afx_msg void OnUpdateViewLyrics(cmd_ui * pcmdui);
   afx_msg void OnViewMidievents();
   afx_msg void OnUpdateViewMidievents(cmd_ui * pcmdui);
   afx_msg void OnFileProperties();
   afx_msg void OnUpdateFileProperties(cmd_ui * pcmdui);
   afx_msg LRESULT OnXfplayerDocMessage(WPARAM wParam, LPARAM lParam);

public:
   afx_msg BOOL open_document_file(const VARIANT FAR& varwszFilePath);
   afx_msg BOOL OpenFile(const char * bstrFilePath, BOOL bMakeVisible);
};

inline XfplayerDoc::EFileType XfplayerDoc::GetDocFileType()
{
   return m_edocfiletype;
}

