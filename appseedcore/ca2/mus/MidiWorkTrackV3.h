// MidiWorkTrackV3.h: interface for the CMidiWorkTrackV3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDIWORKTRACKV3_H__A672FBB1_1F73_4629_87E3_5D75096ED504__INCLUDED_)
#define AFX_MIDIWORKTRACKV3_H__A672FBB1_1F73_4629_87E3_5D75096ED504__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Midi.h"
#include "MidiEventBase.h"
#include "..\vms\VMS.h"


#ifdef _VMSMUS_DLL
    #define CLASS_DECL_VMSMUS  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSMUS  _declspec(dllimport)
#endif

class CLASS_DECL_VMSMUS CMidiWorkTrackV3  
{
public:
	class CEventA
	{
	public:
		CEventA();
		~CEventA();
	//    DECLARE_SERIAL(CMidiWorkEventV3A)
	public:
		void Clear();
	//    virtual void Serialize(CArchive& ar);
		VMSRESULT WriteParam(LPVOID lpData, int iSize);
		VMSRESULT FromData(LPVOID lpData, LPINT lpiLeft, BYTE &bRunningStatus);
	  //	virtual VMSRESULT ToData(CMidiTrack & midiTrack, LPINT lpiLeft, BYTE & bRunningStatus, DWORD tkMax);
		CMidiEventBase & operator=(CMidiEventBase &eventSrc);
		CEventA & operator =(const CEventA &eventSrc);

		//virtual VMSRESULT DeleteContents();
	//    virtual CMSEventMidi & operator=(CMSEvent &eventSrc);
	  //  virtual CMSEventMidi & operator=(CMSEventMidi &eventSrc);
		inline TICKS GetDelta() const;
		inline void SetDelta(TICKS tkDelta);
		inline TICKS GetPosition() const;
		inline void SetPosition(TICKS tkPosition);
		inline BYTE GetFullType() const;
		inline void SetFullType(BYTE bValue);
		inline BYTE GetType_() const;
		inline void SetType_(BYTE bValue);
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
		void SetImage(HPBYTE hpbImage);
		inline HPBYTE GetImage() const;
		inline DWORD GetImageSize() const;
		inline void SetImageSize(DWORD cbSize);
		//inline void SetParam(HPBYTE hpbParam);
		inline void SetParam(void * pVoid, int iSize);
		inline HPBYTE GetParam() const;
		//inline void SetParamSize(DWORD cbSize);
		inline DWORD GetParamSize() const;
		VMSRESULT SetParam(CFile & file, int iLength = -1);
		int GetFlags() const;
		void SetFlags(int iFlag);

		VMSRESULT GetMidiEventV001(CMidiEventV001 * lpMidiEventV001,  DWORD dwPositionTicks);

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

	CMidiWorkTrackV3();
	virtual ~CMidiWorkTrackV3();

	CBaseArray<CEventA, CEventA &> m_events;
};

#endif // !defined(AFX_MIDIWORKTRACKV3_H__A672FBB1_1F73_4629_87E3_5D75096ED504__INCLUDED_)
