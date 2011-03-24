#if !defined(AFX_VMSSE_H__425B3AF8_87E8_496E_A2FB_F65440DED14C__INCLUDED_)
#define AFX_VMSSE_H__425B3AF8_87E8_496E_A2FB_F65440DED14C__INCLUDED_

#include "VMSException.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "RelationV001.h"
#include "DataCentral.h"
#include "PointerListener.h"
#include "VmsGuiApp.h"

class CVmsseThread;


class CVmsseApp
	:
	public CVmsGuiApp,
	public CDataCentral,
	public CPointerListener<CVmsseThread>
{
public:
	virtual void OnPointerClear(CVmsseThread * pthread);
	bool StartMainThread();
	CVmsseApp();

	virtual bool MessageWindowListener(
		UINT message,
		WPARAM wparam, 
		LPARAM lparam);

    CVmsseThread    *   m_pthread;
	CEvent				m_evInit;
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsseApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVmsseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    
};

#endif // AFX_VMSSE_H__425B3AF8_87E8_496E_A2FB_F65440DED14C__INCLUDED_
