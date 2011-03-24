// MidiEventV016.h: interface for the CMidiWorkEventV3A class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIEVENTV016_H__5A905530_3F21_42D6_9280_514AD8A742A9__INCLUDED_)
#define AFX_MIDIEVENTV016_H__5A905530_3F21_42D6_9280_514AD8A742A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef _VMSMUS_DLL
    #define CLASS_DECL_VMSMUS  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSMUS  _declspec(dllimport)
#endif

#include "Midi.h"
#include "MidiEventBase.h"
#include "MidiWorkTrackV3.h"
#include "..\vms\VMS.h"

class CMidiEventV001;

inline TICKS CMidiWorkTrackV3::CEventA::GetDelta() const
{
    return 0;
}

inline void CMidiWorkTrackV3::CEventA::SetDelta(TICKS tkDelta)
{
	ASSERT(FALSE);
}

inline TICKS CMidiWorkTrackV3::CEventA::GetPosition() const
{
	ASSERT(FALSE);
    return 0x7fffffff;
}

inline void CMidiWorkTrackV3::CEventA::SetPosition(TICKS tkPosition)
{
    ASSERT(FALSE);
}
inline BYTE CMidiWorkTrackV3::CEventA::GetFullType() const
{
	return m_lpbData[0];
}
inline void CMidiWorkTrackV3::CEventA::SetFullType(BYTE bValue)
{
	m_lpbData[0] = bValue;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetType_() const
{
	return m_lpbData[0] & 0xf0;
}
inline void CMidiWorkTrackV3::CEventA::SetType_(BYTE bValue)
{
	m_lpbData[0] &= 0x0f;
	m_lpbData[0] |= bValue & 0xf0;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetTrack() const
{
	return m_lpbData[0] & 0x0f;
}
inline void CMidiWorkTrackV3::CEventA::SetTrack(BYTE bValue)
{
	m_lpbData[0] &= 0xf0;
	m_lpbData[0] |= bValue & 0x0f;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetMetaType() const
{
	return m_lpbData[1];
}
inline void CMidiWorkTrackV3::CEventA::SetMetaType(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetChB1() const
{
	return m_lpbData[1];
}
inline void CMidiWorkTrackV3::CEventA::SetChB1(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetChB2() const
{
	return m_lpbData[2];
}
inline void CMidiWorkTrackV3::CEventA::SetChB2(BYTE bValue)
{
	m_lpbData[2] = bValue;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetNotePitch() const
{
	return m_lpbData[1];
}
inline void CMidiWorkTrackV3::CEventA::SetNotePitch(BYTE bValue)
{
	m_lpbData[1] = bValue;
}
inline BYTE CMidiWorkTrackV3::CEventA::GetNoteVelocity() const
{
	return m_lpbData[2];
}
inline void CMidiWorkTrackV3::CEventA::SetNoteVelocity(BYTE bValue)
{
	m_lpbData[2] = bValue;
}
inline HPBYTE CMidiWorkTrackV3::CEventA::GetImage() const
{
	return (HPBYTE) m_lpdwData[0];
}
inline void CMidiWorkTrackV3::CEventA::SetImage(HPBYTE hpbImage)
{
    ASSERT(FALSE);
}

inline DWORD CMidiWorkTrackV3::CEventA::GetImageSize() const
{
    ASSERT(FALSE);
    return 0x7fffffff;
}
inline void CMidiWorkTrackV3::CEventA::SetImageSize(DWORD cbImage)
{
    ASSERT(FALSE);
}
//inline void CMidiWorkTrackV3::CEventA::SetParam(HPBYTE hpbParam)
//{
//	m_lpdwData[2] = (DWORD) hpbParam;
//}
inline void CMidiWorkTrackV3::CEventA::SetParam(void * pVoid, int iSize)
{
	WriteParam(pVoid, iSize);
}
inline HPBYTE CMidiWorkTrackV3::CEventA::GetParam() const
{
	return (HPBYTE) m_lpdwData[2];
}
//inline void CMidiWorkTrackV3::CEventA::SetParamSize(DWORD cbSize)
//{
//	m_lpdwData[1] = cbSize;
//}
inline DWORD CMidiWorkTrackV3::CEventA::GetParamSize() const
{
	return m_lpdwData[1];
}

#endif // !defined(AFX_MIDIEVENTV016_H__5A905530_3F21_42D6_9280_514AD8A742A9__INCLUDED_)
