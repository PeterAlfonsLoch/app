#pragma once

class Star350EventBase;
class Star350EventTrack;
class Star350File;
class Star350TrackBase;


class CTune1000Info;
class CMidiEventsV1;


class CLASS_DECL_ca Star350Tracks : public primitive_array < Star350TrackBase *>
{
protected:
   int               m_iLyricDelay;
public:
   imedia::position               m_tkPosition;
   DWORD               m_fdwSMF;
   Star350File *     m_pfile;
   int               m_iMelodyTrackTipA; // set by kar to xf conversion
   int               m_iCurrentTrack;


   Star350Tracks(Star350File * pfile = NULL);
   virtual ~Star350Tracks();

public:
   bool IsXFFile();
   Star350EventTrack * seek(DWORD dwSeekWhat);
   VMSRESULT GetLyricDelay(int * lpiDelay);
   VMSRESULT SetLyricDelay(int iDelay);
   int GetMidiTrackIndex(int iIndex);
   void ToWorkStorage();

   void seek_begin();
   
   SMFRESULT GetNextEvent(
      midi_event_base * pEvent,
      imedia::position tkMax, 
      BOOL bTkMaxInclusive,
      bool bOnlyMTrk,
      bool bOnlyMidiTrack);


   SMFRESULT GetNextEventTkPosition(
      imedia::position * pTkPosition,
      imedia::position tkMax);
};

