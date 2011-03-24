// LyricTrack.h: interface for the Star350LyricTrack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAR350LYRICTRACK_H__8449840C_43FB_4BE1_813F_360B3F00ADB2__INCLUDED_)
#define AFX_STAR350LYRICTRACK_H__8449840C_43FB_4BE1_813F_360B3F00ADB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class LyricEventsV1;
class LyricEventsV2;

class Star350File;


class CLASS_DECL_ca Star350LyricTrack : public Star350TrackBase
{
    
public:
   Star350LyricTrack(Star350File * pfile = NULL);
   virtual ~Star350LyricTrack();

public:
   VMSRESULT seek_begin();
   imedia::position GetPosition();
   virtual VMSRESULT GetNextEventPosition(imedia::position *tkPosition, imedia::position tkMax);
   virtual int GetFlags();
   virtual VMSRESULT GetEvent(
      MidiEventBase * pEvent,
      imedia::position   tkMax,
      BOOL   bTkMaxInclusive);

public:
   Star350File *    m_pfile;
   int               m_iDelay; // in milliseconds

protected:
   MidiTrackV008     m_trackWorkStorage;
   int               m_iFlags;
   imedia::position             m_tkPosition;
   int               m_iCurrentEvent;
};

#endif // !defined(AFX_STAR350LYRICTRACK_H__8449840C_43FB_4BE1_813F_360B3F00ADB2__INCLUDED_)
