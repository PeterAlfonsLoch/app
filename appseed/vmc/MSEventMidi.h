#pragma once

#include "mus/MidiEventBase.h"
#include "MSEvent.h"
#include "VMS_.h"

class MidiEventV001;

class CMSEventMidi : public CMSEvent, public MidiEventBase
{
public:
	CMSEventMidi();
    CMSEventMidi(CMSEvent &event);
	virtual ~CMSEventMidi();
public:
	virtual void Clear();
	VMSRESULT Write(LPVOID lpData, int iSize);
	VMSRESULT FromData(LPVOID lpData, LPINT lpiLeft);
	virtual VMSRESULT DeleteContents();
    virtual CMSEventMidi & operator=(CMSEvent &eventSrc);
    virtual CMSEventMidi & operator=(CMSEventMidi &eventSrc);
    virtual MidiEventBase & operator=(MidiEventBase &eventSrc);
	inline TICKS GetDelta() const;
	inline void SetDelta(TICKS tkDelta);
	inline TICKS GetPosition() const;
	inline void SetPosition(TICKS tkPosition);
	inline BYTE GetFullType() const;
	inline void SetFullType(BYTE bValue);
	inline BYTE GetType() const;
	inline void SetType(BYTE bValue);
	inline BYTE GetTrack() const;
	inline void SetTrack(BYTE bValue);
	inline BYTE GetMetaType( ) const;
	inline void SetMetaType(BYTE bValue);
	inline BYTE GetChB1() const;
	inline void SetChB1(BYTE bValue);
	inline BYTE GetChB2() const;
	inline void SetChB2(BYTE bValue);
	inline BYTE GetNotePitch() const;
	inline void SetNotePitch(BYTE bValue);
	inline BYTE GetNoteVelocity() const;
	inline void SetNoteVelocity(BYTE bValue);
	void SetImage(HPBYTE hpbImage);
	inline HPBYTE GetImage() const;
	inline int GetImageSize() const;
	inline void SetImageSize(int cbSize);
//	inline void SetParam(HPBYTE hpbParam);
    inline void SetParam(void * hpbParam, int iSize);
    inline VMSRESULT SetParam(CFile &file, int iLength = -1);
	inline HPBYTE GetParam() const;
//	inline void SetParamSize(DWORD cbSize);
	inline int GetParamSize() const;

    virtual void SetFlags(int iFlags);
    virtual int GetFlags() const;


    VMSRESULT GetMidiEventV001(MidiEventV001 * lpMidiEventV001,  DWORD dwPositionTicks);

};
inline TICKS CMSEventMidi::GetDelta() const
{
	return m_tkDelta;
}

inline void CMSEventMidi::SetDelta(TICKS tkDelta)
{
	m_tkDelta = tkDelta;
}

inline TICKS CMSEventMidi::GetPosition() const
{
	ASSERT(FALSE);
    return 0xffffffff;
}

inline void CMSEventMidi::SetPosition(TICKS tkPosition)
{
    ASSERT(FALSE);
}
inline BYTE CMSEventMidi::GetFullType() const
{
	return m_lpbData[0];
}
inline void CMSEventMidi::SetFullType(BYTE bValue)
{
	m_lpbData[0] = bValue;
}
inline BYTE CMSEventMidi::GetType() const
{
	return m_lpbData[0] & 0xf0;
}
inline void CMSEventMidi::SetType(BYTE bValue)
{
	m_lpbData[0] &= 0x0f;
	m_lpbData[0] |= bValue & 0xf0;
}
inline BYTE CMSEventMidi::GetTrack() const
{
	return m_lpbData[0] & 0x0f;
}
inline void CMSEventMidi::SetTrack(BYTE bValue)
{
	m_lpbData[0] &= 0xf0;
	m_lpbData[0] |= bValue & 0x0f;
}
inline BYTE CMSEventMidi::GetMetaType() const
{
	return m_lpbData[1];
}
inline void CMSEventMidi::SetMetaType(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline BYTE CMSEventMidi::GetChB1() const
{
	return m_lpbData[1];
}
inline void CMSEventMidi::SetChB1(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline BYTE CMSEventMidi::GetChB2() const
{
	return m_lpbData[2];
}
inline void CMSEventMidi::SetChB2(BYTE bValue)
{
	m_lpbData[2] = bValue;
}
inline BYTE CMSEventMidi::GetNotePitch() const
{
	return m_lpbData[1];
}
inline void CMSEventMidi::SetNotePitch(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline BYTE CMSEventMidi::GetNoteVelocity() const
{
	return m_lpbData[1];
}
inline void CMSEventMidi::SetNoteVelocity(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline HPBYTE CMSEventMidi::GetImage() const
{
	return (HPBYTE) m_lpdwData[0];
}
inline void CMSEventMidi::SetImage(HPBYTE hpbImage)
{
    ASSERT(FALSE);
}

inline int CMSEventMidi::GetImageSize() const
{
    ASSERT(FALSE);
    return 0xffffffff;
}
inline void CMSEventMidi::SetImageSize(int cbImage)
{
    ASSERT(FALSE);
}
//inline void CMSEventMidi::SetParam(HPBYTE hpbParam)
//{
//	m_lpdwData[2] = (DWORD) hpbParam;
//}
inline void CMSEventMidi::SetParam(void * hpbParam, int  iSize)
{
	m_lpdwData[2] = (DWORD) hpbParam;
    m_lpdwData[1] = iSize;
}

VMSRESULT CMSEventMidi::SetParam(CFile & file, int iLength )
{
    ASSERT(FALSE);
    return VMSR_E_FAIL;
}
inline HPBYTE CMSEventMidi::GetParam() const
{
	return (HPBYTE) m_lpdwData[2];
}
//inline void CMSEventMidi::SetParamSize(DWORD cbSize)
//{
//	m_lpdwData[1] = cbSize;
//}
inline int CMSEventMidi::GetParamSize() const
{
	return m_lpdwData[1];
}
