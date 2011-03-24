// AlbumDoc.cpp : implementation file
//

#include "stdafx.h"
#include "MediaLibraryDoc.h"

#include "mediamanager/AlbumBuild.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryDoc

IMPLEMENT_DYNCREATE(MediaLibraryDoc, Document)

MediaLibraryDoc::MediaLibraryDoc()
{
//   m_pdb = NULL;
   m_pdsAlbum1       = NULL;
   m_pcsAlbum1       = NULL;
   m_pdsAlbumRecord  = NULL;
//   m_bBuilt = false;
}

BOOL MediaLibraryDoc::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);

   mediamanager::GetMediaManager()->BuildAlbum(wstra);

   m_pcsAlbum1        = &mediamanager::GetMediaManager()->GetAlbumBuild().m_csRead1;
   m_pdsAlbum1        = (_vmssqlite::Dataset *) mediamanager::GetMediaManager()->GetAlbumBuild().m_pdsRead1;


   UpdateAllViews(NULL, 0);

	return TRUE;
}

MediaLibraryDoc::~MediaLibraryDoc()
{
}


BEGIN_MESSAGE_MAP(MediaLibraryDoc, Document)
	//{{AFX_MSG_MAP(MediaLibraryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryDoc diagnostics

#ifdef _DEBUG
void MediaLibraryDoc::AssertValid() const
{
	Document::AssertValid();
}

void MediaLibraryDoc::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryDoc serialization

void MediaLibraryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryDoc commands

int MediaLibraryDoc::GetSongCount()
{
   //m_pds->query("select * from album;");
   //return m_pds->num_rows();
   //return m_fileinfo.m_wstraNew.GetSize();
   if(m_pcsAlbum1 == NULL)
      return 0;

   CSingleLock sl(m_pcsAlbum1, TRUE);
   if(m_pdsAlbum1 == NULL)
      return 0;
   else
      return m_pdsAlbum1->num_rows();
}

void MediaLibraryDoc::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
   if(key == VMSDATAKEY(SongDirectorySet))
   {
      OnSetSongDirectory();
   }
}

void MediaLibraryDoc::OnSetSongDirectory()
{

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);

   mediamanager::GetMediaManager()->BuildAlbum(wstra);

   UpdateAllViews(NULL, 0);

}
