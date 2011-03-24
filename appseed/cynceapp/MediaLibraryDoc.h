#if !defined(AFX_ALBUMDOC_H__4062A0E4_9C93_4D6C_98D2_A23F356841EF__INCLUDED_)
#define AFX_ALBUMDOC_H__4062A0E4_9C93_4D6C_98D2_A23F356841EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbumDoc.h : header file
//

// vmssqlite
namespace _vmssqlite
{
   class Database;
   class Dataset;
}

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryDoc document

class MediaLibraryDoc :
   public Document,
   public DBInterface,
   public VmsDataClientInterface
{
protected:
	MediaLibraryDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MediaLibraryDoc)

// Attributes
public:
   
   //mediamanager::AlbumBuild::FileInfo m_fileinfo;
   //_vmssqlite::CSQLiteDatabase *    m_pdb;
   //_vmssqlite::Dataset *     m_pds;
   _vmssqlite::Dataset *      m_pdsAlbum1;
   CCriticalSection *         m_pcsAlbum1;
   _vmssqlite::Dataset *      m_pdsAlbumRecord;
   //bool                             m_bBuilt;
   
   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MediaLibraryDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnSetSongDirectory();
	int GetSongCount();
	virtual ~MediaLibraryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(MediaLibraryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMDOC_H__4062A0E4_9C93_4D6C_98D2_A23F356841EF__INCLUDED_)
