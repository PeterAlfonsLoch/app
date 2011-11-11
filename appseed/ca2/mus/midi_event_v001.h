#pragma once

class midi_event_v008;

class CLASS_DECL_ca midi_event_v001 : 
   public midi_event_base  
{
public:

   imedia::position        m_tkDelta;           
   imedia::position         m_tkPosition;
   BYTE                    m_abEvent[3];        
   DWORD                   m_cbParm;            
   byte *                  m_hpbParm; 
   DWORD                     m_cbImage;
   byte *                  m_hpbImage;
   ::mus::midi::file *               m_pFile;
   midi_track *               m_pTrack;
   int                     m_iFlags;

   midi_event_v001();
   virtual ~midi_event_v001();

   using ::midi_event_base::SetParam;
   virtual void clear();

   virtual midi_event_base & operator = (const midi_event_base & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_v001 & operator = (const midi_event_v001 & eventSrc);

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
      //inline void SetParam(byte * hpbParam);
   inline void SetParam(void * pVoid, int iSize);
   virtual VMSRESULT SetParam(ex1::file & file, int iLength = -1);
   inline byte * GetParam() const;
   //inline void SetParamSize(DWORD cbSize);
   inline int GetParamSize() const;

   virtual int GetFlags() const;
   virtual void SetFlags(int iFlag);

   static index CompareTkPosition(midi_event_v001 * pa1, midi_event_v001 * pa2);
   static void swap(midi_event_v001 * p1, midi_event_v001 * p2);

   imedia::position    _GetDelta() const;
   void     _SetDelta(imedia::position tkDelta);
   imedia::position    _GetPosition() const;
   void     _SetPosition(imedia::position tkPosition);
   BYTE     _GetFullType() const;
   void     _SetFullType(BYTE bValue);
   BYTE     _GetType() const;
   void     _SetType(BYTE bValue);
   BYTE     _GetTrack() const;
   void     _SetTrack(BYTE bValue);
   BYTE     _GetMetaType() const;
   void     _SetMetaType(BYTE bValue);
   BYTE     _GetChB1() const;
   void     _SetChB1(BYTE bValue);
   BYTE     _GetChB2() const;
   void     _SetChB2(BYTE bValue);
   BYTE     _GetNotePitch() const;
   void     _SetNotePitch(BYTE bValue);
   BYTE     _GetNoteVelocity() const;
   void     _SetNoteVelocity(BYTE bValue);
   void     _SetImage(byte * hpbImage);
   byte *   _GetImage() const;
   int      _GetImageSize() const;
   void     _SetImageSize(int cbSize);
   void     _SetParam(void * pVoid, int iSize);
   byte *   _GetParam() const;
   int      _GetParamSize() const;

   int      _GetFlags() const;
   void     _SetFlags(int iFlag);
};

