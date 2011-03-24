#if !defined(AFX_SONGDAOSET_H__77CFFC8C_D05A_4266_99FE_3D2DE9A397C3__INCLUDED_)
#define AFX_SONGDAOSET_H__77CFFC8C_D05A_4266_99FE_3D2DE9A397C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SongDaoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSongDaoSet DAO recordset

class CSongDaoSet : public CDaoRecordset
{
public:
	CSongDaoSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSongDaoSet)

// Field/Param Data
	//{{AFX_FIELD(CSongDaoSet, CDaoRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSongDaoSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SONGDAOSET_H__77CFFC8C_D05A_4266_99FE_3D2DE9A397C3__INCLUDED_)
