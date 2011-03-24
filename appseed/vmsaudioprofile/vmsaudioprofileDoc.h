// vmsaudioprofileDoc.h : interface of the AudioProfileDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSAUDIOPROFILEDOC_H__6268B39E_B7CA_4AEE_9F97_6BE998AFB736__INCLUDED_)
#define AFX_VMSAUDIOPROFILEDOC_H__6268B39E_B7CA_4AEE_9F97_6BE998AFB736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class AudioProfileDoc : public CDocument
{
protected: // create from serialization only
	AudioProfileDoc();
	DECLARE_DYNCREATE(AudioProfileDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AudioProfileDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~AudioProfileDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(AudioProfileDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(AudioProfileDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSAUDIOPROFILEDOC_H__6268B39E_B7CA_4AEE_9F97_6BE998AFB736__INCLUDED_)
