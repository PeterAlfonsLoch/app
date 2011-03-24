#pragma once

class Star350EventTrack;
class Star350File;

class CLASS_DECL_ca Star350EventV001 :
    public MidiEventBase,
    public Star350EventBase  
{
public:
   imedia::position     m_tkDelta;
   imedia::position     m_tkPosition;
   BYTE                 m_abEvent[3];        
   DWORD                m_cbParm;            
   byte *               m_hpbParm; 
   DWORD                  m_cbImage;
   byte *               m_hpbImage;
   Star350File *         m_pfile;
   Star350EventTrack *   m_ptrack;

   int                  m_iFlags;

   imedia::position     m_tkDuration;
   int                  m_iType;

   Star350EventV001();
   virtual ~Star350EventV001();

#if !core_level_1
   using ::MidiEventBase::SetParam;
#endif

   virtual void clear();

   virtual MidiEventBase & operator = (const MidiEventBase & eventSrc) { return MidiEventBase::operator = (eventSrc); }
   virtual MidiEventBase & operator = (const MidiEventV008 & eventSrc) { return MidiEventBase::operator = (eventSrc); }

   virtual Star350EventV001 & operator = (const Star350EventV001 & eventSrc);

   inline imedia::position GetDelta() const;
   inline void SetDelta(imedia::position tkDelta);
   inline imedia::position GetPosition() const;
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
   virtual VMSRESULT SetParam(ex1::file & file, int iLength = -1);
   inline byte * GetParam() const;
   inline int GetParamSize() const;

   virtual int GetFlags() const;
   virtual void SetFlags(int iFlag);

   virtual imedia::position GetDuration() const;
   virtual void SetDuration(imedia::position tkDelta);

   virtual int GetStar350Type() const;
   virtual void SetStar350Type(int iType);

   virtual WORD GetLyricsOffset() const;
   virtual void GetLyricsOffset(WORD iOffset);

   virtual WORD GetLyricsCount() const;
   virtual void GetLyricsCount(WORD iCount);

};
