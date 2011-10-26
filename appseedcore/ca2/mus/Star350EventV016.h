#pragma once

class Star350EventV001;

class CLASS_DECL_ca Star350EventV016 :
   public midi_event_base,
   public Star350EventBase
{
public:
   
   Star350EventV016();
   virtual ~Star350EventV016();

#if !core_level_1
   using ::midi_event_base::SetParam;
#endif


   virtual void clear();

   virtual midi_event_base & operator = (const midi_event_base & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc) { return midi_event_base::operator = (eventSrc); }

   virtual Star350EventBase & operator = (const Star350EventBase & eventSrc) { return Star350EventBase::operator = (eventSrc); }
   virtual Star350EventV016 & operator = (const Star350EventV016 & eventSrc);

   virtual VMSRESULT WriteParam(LPVOID lpData, int iSize);
   virtual VMSRESULT FromData(LPVOID lpData, LPINT lpiLeft, EventType evtype);

   inline imedia::position GetDelta() const;
   inline void SetDelta(imedia::position tkDelta);
   inline imedia::position get_position() const;
   inline void SetPosition(imedia::position tkPosition);
   inline BYTE GetFullType() const;
   inline void SetFullType(BYTE bValue);
   inline BYTE get_type() const;
   inline void set_type(BYTE bValue);
   inline BYTE GetTrack() const;
   inline void SetTrack(BYTE bValue);
   inline BYTE GetMetaType() const;
   inline void SetMetaType(BYTE bValue);
   inline BYTE GetChB1() const;
   inline void SetChB1(BYTE bValue);
   inline BYTE GetChB2() const;
   inline void SetChB2(BYTE bValue);
   inline BYTE GetNotePitch() const;
   inline void SetNotePitch(BYTE bValue);
   inline BYTE GetNoteVelocity() const;
   inline void SetNoteVelocity(BYTE bValue);
   void SetImage(byte * hpbImage);
   inline byte * GetImage() const;
   inline int GetImageSize() const;
   inline void SetImageSize(int cbSize);
   inline void SetParam(void * pVoid, int iSize);
   inline byte * GetParam() const;
   inline int GetParamSize() const;
   virtual VMSRESULT SetParam(ex1::file & file, int iLength = -1);
   virtual int GetFlags() const;
   virtual void SetFlags(int iFlag);

   VMSRESULT GetEventV001(Star350EventV001 * lpMidiEventV001,  DWORD dwPositionTicks);

   virtual imedia::position GetDuration() const;
   virtual void SetDuration(imedia::position tkDelta);

   virtual int GetStar350Type() const;
   virtual void SetStar350Type(int iType);

   virtual WORD GetLyricsOffset() const;
   virtual void GetLyricsOffset(WORD iOffset);
    
   virtual WORD GetLyricsCount() const;
   virtual void GetLyricsCount(WORD iCount);

protected:
    union
    {
        DWORD               m_lpdwData[3];
        short               m_lpshData[3 * sizeof(DWORD) / sizeof(short)];
        unsigned short      m_lpushData[3 * sizeof(DWORD) / sizeof(short)];
        BYTE                m_lpbData[3 * sizeof(DWORD)];
    };
    int m_iFlags;
};
