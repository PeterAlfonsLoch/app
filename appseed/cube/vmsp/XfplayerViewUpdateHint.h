#pragma once

class CLASS_DECL_CA2_CUBE XfplayerViewUpdateHint : public ::radix::object  
{
public:
   enum e_type
   {
      MidiLyricEvent,
      UpdateStart,
      UpdateFull,
      UpdateRepaint,
      TypeProgressRateChange,
      UpdateSongLabelInformation,
      UpdateSimpleLyricsNoRepaint,
      Play,
      PreparePhaseA,
      PreparePhaseB,
      Prepare,
      FullScreenChange,
      CompactModeChange,
      UpdateKaraokeEncoding,
      UpdateOnAttachPlaylistDoc,
      UpdateOnDetachPlaylistDoc,
      UpdateOnMidiPlayerNotifyEvent,
      UpdateOnMidiPlayerMmsgDone,
      TypeBeforeOpenDocument,
      TypeAfterOpenDocument,
      TypeCloseDocument,
      TypePlay,
      TypePlayCount,
      TypeWaitPlayCount,
      TypeShowPlayer,
   };
   
public:
   string        m_strBeforeOpenDocumentPath;
   bool           m_bBeforeOpenDocument;
   int            m_iPlayCount;
   int            m_iWaitPlayCount;
   bool           m_bShowPlayer;
public:
   XfplayerViewUpdateHint();
   virtual ~XfplayerViewUpdateHint();

protected:
   flags < e_type >   m_etypeflags;

public:
   void clear();
   bool HasType(e_type e_type);
   void AddType(e_type e_type);
   flags < e_type > & GetTypeFlags();
   ::mus::midi::player::NotifyEvent * m_pmidiplayernotifyeventdata;
   base_array<LyricEventV1, LyricEventV1&> * m_pevents;
   ::mus::midi::sequence * m_psequenceMidiPlayerMmsgDone;
   ::mus::midi::LPMIDIDONEDATA m_pmidinodedataMidiPlayerMmsgDone;
   

};

