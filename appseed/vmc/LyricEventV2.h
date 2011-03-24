// LyricEventV2.h: interface for the CLyricEventV2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICEVENTV2_H__A1B13E87_B529_4A37_8483_2F44591E4EFC__INCLUDED_)
#define AFX_LYRICEVENTV2_H__A1B13E87_B529_4A37_8483_2F44591E4EFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLyricEventV2  
{
public:
	void ToData(LPDWORD lpdwData, DWORD cbLeft);
	void FromData(LPDWORD lpdwData);
	union
	{
		struct
		{
			int	m_iType			: sizeof(int) * 8;
			int	m_iTrack		: sizeof(int) * 8;
			int	m_iCurrentToken	: sizeof(int) * 8;
		};
		BYTE m_pbData[sizeof(int) * 3];
	};

	CLyricEventV2();
	virtual ~CLyricEventV2();

};

#endif // !defined(AFX_LYRICEVENTV2_H__A1B13E87_B529_4A37_8483_2F44591E4EFC__INCLUDED_)
