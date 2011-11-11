// CRCFast.h: interface for the CCRCFast class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRCFAST_H__F2E3D06B_D44B_4925_8C46_6FD4D3025001__INCLUDED_)
#define AFX_CRCFAST_H__F2E3D06B_D44B_4925_8C46_6FD4D3025001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CRC.h"

class memory;

class CLASS_DECL_ca CCRCFast : public CCRC  
{
public:
	CCRCFast(CCRC::Type key);
	virtual ~CCRCFast();

public:
	void PutByte(unsigned byte);
   void PutBytes(LPBYTE lpb, int iCount);
   void PutBytes(memory * lpms);
private:
	class Table
	{
	public:
		Table (): m_key (0) {}
		void Init (CCRC::Type key);
		inline CCRC::Type operator [] (unsigned i);
	private:
		CCRC::Type m_table [256];
		CCRC::Type m_key;
	};
private:
	static Table m_table;
};

inline CCRC::Type CCRCFast::Table::operator [] (unsigned i)
{
	return m_table [i];
}

#endif // !defined(AFX_CRCFAST_H__F2E3D06B_D44B_4925_8C46_6FD4D3025001__INCLUDED_)
