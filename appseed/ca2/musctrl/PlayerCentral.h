// PlayerCentral.h: interface for the CPlayerCentral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERCENTRAL_H__4550EB22_D562_449D_9A7D_C340A90F890D__INCLUDED_)
#define AFX_PLAYERCENTRAL_H__4550EB22_D562_449D_9A7D_C340A90F890D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXfplayerSingleDocTemplate;

class CPlayerCentral  
{
public:
	CPlayerCentral();
	virtual ~CPlayerCentral();

	CRuntimeClass *		m_pruntimeclassDocument;
	CRuntimeClass *		m_pruntimeclassFrameWnd;
	CRuntimeClass *		m_pruntimeclassView;

protected:
    CXfplayerSingleDocTemplate *    m_pdoctemplateMid;
	CXfplayerSingleDocTemplate *    m_pdoctemplateKar;
	CXfplayerSingleDocTemplate *    m_pdoctemplateSt3;
public:
	static CPlayerCentral & AppGetPlayerCentral();
public:
	CXfplayerSingleDocTemplate * GetDocTemplate();
	CXfplayerSingleDocTemplate * CreateDocTemplate();

};

#endif // !defined(AFX_PLAYERCENTRAL_H__4550EB22_D562_449D_9A7D_C340A90F890D__INCLUDED_)
