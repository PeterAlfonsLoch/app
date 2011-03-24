// SingleDocTemplateV003.h: interface for the CSingleDocTemplateV003 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGLEDOCTEMPLATEV003_H__12A9EB46_8D7C_4742_9299_D31DF3A76DBC__INCLUDED_)
#define AFX_SINGLEDOCTEMPLATEV003_H__12A9EB46_8D7C_4742_9299_D31DF3A76DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSingleDocTemplateV003 : public CSingleDocTemplate  
{
	DECLARE_DYNAMIC(CSingleDocTemplateV003)
public:
	CSingleDocTemplateV003( UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass );
// Constructors
public:
//	CSingleDocTemplateV003(UINT nIDResource, CRuntimeClass* pDocClass,
//		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

// Implementation
public:
    BOOL GetDocString(string& rString,
                            enum DocStringIndex i) const;
    DocumentTemplate::Confidence MatchDocType(const
        char* pszPathName, Document*& rpDocMatch);

    virtual void LoadTemplate();
	virtual ~CSingleDocTemplateV003();
	virtual void AddDocument(Document* pDoc);
	virtual void RemoveDocument(Document* pDoc);
	virtual POSITION GetFirstDocPosition() const;
	virtual Document* GetNextDoc(POSITION& rPos) const;
	virtual Document* OpenDocumentFile(
		LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE);
	virtual void SetDefaultTitle(Document* pDocument);
	virtual FrameWindow* CreateNewFrame(Document* pDoc, FrameWindow* pOther);


#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

//protected:  // standard implementation
//	Document* m_pOnlyDoc;
//	virtual ~CSingleDocTemplateV003();
//	virtual Document* OpenDocumentFile(
//		LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE);

};

#endif // !defined(AFX_SINGLEDOCTEMPLATEV003_H__12A9EB46_8D7C_4742_9299_D31DF3A76DBC__INCLUDED_)
