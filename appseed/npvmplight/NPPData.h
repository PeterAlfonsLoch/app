// NPPData.h: interface for the CNPPData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPPDATA_H__5AAB84A4_E94F_4422_B23E_B35CE4766134__INCLUDED_)
#define AFX_NPPDATA_H__5AAB84A4_E94F_4422_B23E_B35CE4766134__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "..\vmsp\vmsp_i.h"
#include "npvmpLightDoc.h"
#include "npvmpLightView.h"

class CNPPData  
{
public:
	void UpdateWindowPos();
	CView * GetView();
	CFrameWnd * GetFrame();
	bool CreateDocTemplate();
	bool OpenDocumentFile(HWND hwnd, LPCTSTR lpcsz);
	bool OpenPlayerFile();
	CNPPData();
	virtual ~CNPPData();

	//CComPtr<IXfplayer>		m_spXfplayer;
	HWND					m_hwndParent;
//	COleWnd    				m_olewnd;
	CSingleDocTemplate *	m_pdoctemplate;
	CNpvmpDoc * 			m_pdoc;
	String					m_strFilePath;
	CRect					m_rectLast;


};

#endif // !defined(AFX_NPPDATA_H__5AAB84A4_E94F_4422_B23E_B35CE4766134__INCLUDED_)
