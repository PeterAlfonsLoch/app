// PlayerCentralContainer.h: interface for the CPlayerCentralContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERCENTRALCONTAINER_H__20F30E9B_4DC3_4909_9207_5C271F54DE16__INCLUDED_)
#define AFX_PLAYERCENTRALCONTAINER_H__20F30E9B_4DC3_4909_9207_5C271F54DE16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPlayerCentral;

class CPlayerCentralContainer  
{
public:
	CPlayerCentralContainer();
	virtual ~CPlayerCentralContainer();

protected:
	CPlayerCentral *	m_pplayercentral;
	
public:

	static inline CPlayerCentral & AppGetPlayerCentral();

	inline CPlayerCentral & GetPlayerCentral();

};

inline CPlayerCentral & CPlayerCentralContainer::GetPlayerCentral()
{
	return *m_pplayercentral;
}

inline CPlayerCentral & CPlayerCentralContainer::AppGetPlayerCentral()
{
	return (dynamic_cast < CPlayerCentralContainer * > (AfxGetApp()))->GetPlayerCentral();
}


#endif // !defined(AFX_PLAYERCENTRALCONTAINER_H__20F30E9B_4DC3_4909_9207_5C271F54DE16__INCLUDED_)
