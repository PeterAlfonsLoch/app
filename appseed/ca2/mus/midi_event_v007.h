#pragma once


class CLASS_DECL_ca midi_event_v007 :
   public midi_event_base  
{
public:


   imedia::position           m_tkDelta;           
   imedia::position           m_tkPosition;
   BYTE                       m_abEvent[3];        
   DWORD                      m_cbParm;            
   byte *                     m_hpbParm; 
   DWORD                      m_cbImage;
   DWORD                      m_idxImage;
   DWORD                      m_idxParam;
   ::mus::midi::file *        m_pFile;
   midi_track *               m_pTrack;
   byte *                     m_hpbAllocation;
   DWORD                      m_dwAllocation;
   bool                       m_bAutoAllocation;
   DWORD                      m_dwAllocationAddUp;

   int                        m_iFlags;


   midi_event_v007(::mus::midi::file * pFile, midi_track * pTrack);
   midi_event_v007(::mus::midi::file * pFile, midi_track * pTrack, midi_event_v001 * pEvent);
   virtual ~midi_event_v007();

   using ::midi_event_base::SetParam;
   virtual void clear();

   virtual midi_event_base & operator = (const midi_event_base & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_v007 & operator = (const midi_event_v007 & eventSrc);

   BOOL allocate(DWORD dwNewLength);
   BOOL allocate_add_up(DWORD dwAddUp);
   void SetAutoAllocation(BOOL bValue = TRUE);

   BOOL IsAutoAllocated();

   void   AutoAllocate();
   SMFRESULT CreateMetaEvent(imedia::position tkDelta, BYTE bMetaType, byte * hpbParam, DWORD cbLength);
   SMFRESULT CreateXFInfoHeaderEvent(imedia::position tkDelta, XFInfoHeader * pXfih);
   DWORD SetVDWord(uint64_t ui);
   DWORD SetVDWord(byte * hpbImage, DWORD dw);
   inline imedia::position GetDelta() const;
   inline void SetDelta(imedia::position tkDelta);
   inline imedia::position get_position() const;
   inline void SetPosition(imedia::position tkPosition);
   inline int GetImageSize() const;
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
   byte * GetImage() const;
   inline void SetImageSize(int cbSize);
   inline void SetParam(void * pVoid, int iSize);
   virtual VMSRESULT SetParam(ex1::file & file, int iLength = -1);
   inline byte * GetParam() const;
   inline int GetParamSize() const;

   virtual int GetFlags() const;
   virtual void SetFlags(int iFlag);


};
