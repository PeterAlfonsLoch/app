// mk1expanderDoc.cpp : implementation of the CMk1expanderDoc class
//

#include "stdafx.h"
#include "mk1expander.h"

#include "mk1expanderDoc.h"
#include "unzip.h"
#include "_vmszipMemoryFile.h"
#include "_vmszipApi.h"

#include "MemoryStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderDoc

IMPLEMENT_DYNCREATE(CMk1expanderDoc, CDocument)

BEGIN_MESSAGE_MAP(CMk1expanderDoc, CDocument)
	//{{AFX_MSG_MAP(CMk1expanderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMk1expanderDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CMk1expanderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMk1expander to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {CC09B445-B133-4B5B-99CA-FE6170826449}
static const IID IID_IMk1expander =
{ 0xcc09b445, 0xb133, 0x4b5b, { 0x99, 0xca, 0xfe, 0x61, 0x70, 0x82, 0x64, 0x49 } };

BEGIN_INTERFACE_MAP(CMk1expanderDoc, CDocument)
	INTERFACE_PART(CMk1expanderDoc, IID_IMk1expander, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderDoc construction/destruction

CMk1expanderDoc::CMk1expanderDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CMk1expanderDoc::~CMk1expanderDoc()
{
	AfxOleUnlockApp();
}

BOOL CMk1expanderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMk1expanderDoc serialization

void CMk1expanderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{

	}
}

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderDoc diagnostics

#ifdef _DEBUG
void CMk1expanderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMk1expanderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderDoc commands

BOOL CMk1expanderDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
   MemoryStorage storage;
   if(!GetFile(lpszPathName, storage))
      return false;

   CString str(lpszPathName);
   str += ".kar";
   CFile file;

   file.Open(str, CFile::typeBinary | CFile ::modeWrite | CFile::modeCreate);

   file.Write(storage.GetAllocation(), storage.GetStorageSize());

   file.Close();
	return TRUE;
}

bool CMk1expanderDoc::GetFile(LPCTSTR lpcszPath, MemoryStorage & storage)
{
   CFile file(lpcszPath, CFile::modeRead | CFile::typeBinary);
   int iLen = file.GetLength();
   _vmszipMemoryFile memfile;
   memfile.Allocate(iLen);
   file.Read(memfile.GetAllocation(), iLen);
   
   unzFile pf = _vmszipApi::unzipOpen(&memfile);

   if(pf != NULL)
   {
      if(unzOpenCurrentFilePassword(pf, "bqN,Sepc;MqD,PAmnC!") == UNZ_OK)
      {
         MemoryFile target;
         target.Attach(&storage);
         BYTE buf[1024];
         int iRead;
         while((iRead = unzReadCurrentFile(pf, buf, sizeof(buf))) > 0)
         {
            target.Write(buf, iRead);
         }  
         target.Detach();
         return true;
      }
      else
      {
         return false;
      }

   }
   else
   {
      return false;
   }
}
