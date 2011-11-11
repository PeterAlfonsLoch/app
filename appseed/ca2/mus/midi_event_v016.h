#pragma once

class midi_event_v001;

class CLASS_DECL_ca midi_event_v016 :
   public midi_event_v508
{
protected:
    imedia::position m_tkDelta;

public:

   midi_event_v016(midi_event_v016 & event);
   midi_event_v016();
   virtual ~midi_event_v016();

   virtual void clear();


   virtual midi_event_base & operator = (const midi_event_base & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_v508 & operator = (const midi_event_v508 & eventSrc) { return midi_event_v508::operator = (eventSrc); }
   virtual midi_event_v016 & operator = (const midi_event_v016 & eventSrc);


   virtual VMSRESULT WriteParam(LPVOID lpData, int iSize);
   virtual VMSRESULT FromData(LPVOID lpData, LPINT lpiLeft, BYTE &bRunningStatus);
   VMSRESULT GetMidiEventV001(midi_event_v001 * lpMidiEventV001,  DWORD dwPositionTicks);
    
   imedia::position GetDelta() const;
   void SetDelta(imedia::position tkDelta);
   imedia::position get_position() const;
   void SetPosition(imedia::position tkPosition);
   BYTE GetFullType() const;
   void SetFullType(BYTE bValue);
   BYTE GetType_() const;
   void SetType_(BYTE bValue);
   BYTE GetTrack() const;
   void SetTrack(BYTE bValue);
   BYTE GetMetaType() const;
   void SetMetaType(BYTE bValue);
   BYTE GetChB1() const;
   void SetChB1(BYTE bValue);
   BYTE GetChB2() const;
   void SetChB2(BYTE bValue);
   BYTE GetNotePitch() const;
   void SetNotePitch(BYTE bValue);
   BYTE GetNoteVelocity() const;
   void SetNoteVelocity(BYTE bValue);
   byte * GetParam() const;
   int GetParamSize() const;

   imedia::position _GetDelta() const;
   void _SetDelta(imedia::position tkDelta);

};

__forceinline imedia::position midi_event_v016::GetDelta() const
{
   return m_tkDelta;
}

__forceinline void midi_event_v016::SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}

__forceinline imedia::position midi_event_v016::get_position() const
{
   return 0xffffffff;
}

__forceinline void midi_event_v016::SetPosition(imedia::position tkPosition)
{
   UNREFERENCED_PARAMETER(tkPosition);
   ASSERT(FALSE);
}

__forceinline BYTE midi_event_v016::GetFullType() const
{
   return m_lpbData[0];
}
__forceinline void midi_event_v016::SetFullType(BYTE bValue)
{
   m_lpbData[0] = bValue;
}
__forceinline BYTE midi_event_v016::GetType_() const
{
   return m_lpbData[0] & 0xf0;
}
__forceinline void midi_event_v016::SetType_(BYTE bValue)
{
   m_lpbData[0] &= 0x0f;
   m_lpbData[0] |= bValue & 0xf0;
}
__forceinline BYTE midi_event_v016::GetTrack() const
{
   return m_lpbData[0] & 0x0f;
}
__forceinline void midi_event_v016::SetTrack(BYTE bValue)
{
   m_lpbData[0] &= 0xf0;
   m_lpbData[0] |= bValue & 0x0f;
}
__forceinline BYTE midi_event_v016::GetMetaType() const
{
   return m_lpbData[1];
}
__forceinline void midi_event_v016::SetMetaType(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
__forceinline BYTE midi_event_v016::GetChB1() const
{
   return m_lpbData[1];
}
__forceinline void midi_event_v016::SetChB1(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
__forceinline BYTE midi_event_v016::GetChB2() const
{
   return m_lpbData[2];
}
__forceinline void midi_event_v016::SetChB2(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
__forceinline BYTE midi_event_v016::GetNotePitch() const
{
   return m_lpbData[1];
}
__forceinline void midi_event_v016::SetNotePitch(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
__forceinline BYTE midi_event_v016::GetNoteVelocity() const
{
   return m_lpbData[2];
}
__forceinline void midi_event_v016::SetNoteVelocity(BYTE bValue)
{
   m_lpbData[2] = bValue;
}


__forceinline byte * midi_event_v016::GetParam() const
{
   return (byte *) m_lpdwData[2];
}

__forceinline int midi_event_v016::GetParamSize() const
{
   return m_lpdwData[1];
}

__forceinline imedia::position midi_event_v016::_GetDelta() const
{
   return m_tkDelta;
}

__forceinline void midi_event_v016::_SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}
