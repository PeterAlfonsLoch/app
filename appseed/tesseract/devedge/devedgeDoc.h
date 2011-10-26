#pragma once

#include "devedgeView.h"

class CLASS_DECL_CA2_DEVEDGE devedgeDoc :
   public BaseDocument,
   public DBInterface,
   public VmsDataClientInterface
{
public:
	devedgeDoc(::ca::application * papp);           
	// DECLARE_DYNCREATE(devedgeDoc)

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
   virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

   Ex1File           m_file;
   int               m_iBranch;
   devedgeView *     m_pview;

   void reload();
   
public:
   BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo);

   DECL_GEN_SIGNAL(_001OnUpdateFileSave)
   DECL_GEN_SIGNAL(_001OnUpdateFilePut)
   DECL_GEN_SIGNAL(_001OnUpdateEditCut)
   DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
   DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
   DECL_GEN_SIGNAL(_001OnFileSave)
   DECL_GEN_SIGNAL(_001OnFilePut)
   DECL_GEN_SIGNAL(_001OnEditCut)
   DECL_GEN_SIGNAL(_001OnEditCopy)
   DECL_GEN_SIGNAL(_001OnEditPaste)

   void Put();
   void FtpPut(LPCTSTR lpcszLocal, LPCTSTR lpcszRemote);

	public:
//	virtual void Serialize(CArchive& ar);   
	protected:
	virtual BOOL OnNewDocument();

public:
	virtual ~devedgeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};

