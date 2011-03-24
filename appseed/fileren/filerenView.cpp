// filerenView.cpp : implementation of the CFilerenView class
//

#include "stdafx.h"
#include "fileren.h"

#include "filerenDoc.h"
#include "filerenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilerenView

IMPLEMENT_DYNCREATE(CFilerenView, CFormView)

BEGIN_MESSAGE_MAP(CFilerenView, CFormView)
	//{{AFX_MSG_MAP(CFilerenView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonReplaceSpaceWithUnderscore)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonMakeExtensionLowercase)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_1, OnButtonMove1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
   ON_BN_CLICKED(IDC_BUTTON_REPLACE_SPECIAL, &CFilerenView::OnBnClickedButtonReplaceSpecial)
   ON_BN_CLICKED(IDC_BUTTON_REPLACE, &CFilerenView::OnBnClickedButtonReplace)
   ON_BN_CLICKED(IDC_EDIT1_PASTE, &CFilerenView::OnBnClickedEdit1Paste)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilerenView construction/destruction

CFilerenView::CFilerenView()
	: CFormView(CFilerenView::IDD)
{
	//{{AFX_DATA_INIT(CFilerenView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CFilerenView::~CFilerenView()
{
}

void CFilerenView::DoDataExchange(CDataExchange* pDX)
{
   CFormView::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CFilerenView)
   DDX_Control(pDX, IDC_EDIT1, m_edit);
   //}}AFX_DATA_MAP
   DDX_Control(pDX, IDC_EDIT_FIND, m_editFind);
   DDX_Control(pDX, IDC_EDIT_REPLACE, m_editReplace);
}

BOOL CFilerenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFilerenView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CFilerenView printing

BOOL CFilerenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFilerenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFilerenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFilerenView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CFilerenView diagnostics

#ifdef _DEBUG
void CFilerenView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFilerenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFilerenDoc* CFilerenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilerenDoc)));
	return (CFilerenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilerenView message handlers

void CFilerenView::OnButtonReplaceSpaceWithUnderscore() 
{
	String strFolder;
	
	m_edit.GetWindowText(strFolder);


	if(strFolder.IsEmpty())
		return;

   if(strFolder[strFolder.GetLength() - 1] == '\\')
   {
      strFolder = strFolder.Left(strFolder.GetLength() - 1);
   }

	CFileFind filefind;

	String strFrom;
	String strTo;

	SHFILEOPSTRUCT fo;
	int iFound;

	TCHAR szFrom[1024];
	TCHAR szTo[1024];

	bool bOk;
	if(filefind.FindFile(strFolder + "\\*.*"))
	{
		while(true)
		{
			bOk = filefind.FindNextFile();
			if(!filefind.IsDirectory())
			{
				strFrom = filefind.GetFilePath();
				iFound = -1;
				for(int i = strFrom.GetLength() - 1; i >= 0; i--)
				{
					if(strFrom[i] == '\\')
					{
						iFound = i;
						break;
					}
				}
				if(iFound >= 0)
				{
					strTo = strFrom.Mid(iFound + 1);
					strTo.Replace(" ", "_");
					strTo = strFrom.Left(iFound + 1) + strTo;
					fo.hwnd = m_hWnd;
					fo.wFunc = FO_RENAME;
					_tcscpy(szTo, strTo);
					szTo[strTo.GetLength() + 1] = 0;
					_tcscpy(szFrom, strFrom);
					szFrom[strFrom.GetLength() + 1] = 0;
					if(strTo != strFrom)
					{
						fo.pFrom = szFrom;
						fo.pTo = szTo;
						fo.fFlags = 0;
						SHFileOperation(&fo);
					}
				}
			}
			if(!bOk)
				break;

		}
	}

}

void CFilerenView::OnButtonMakeExtensionLowercase() 
{
	String strFolder;
	
	m_edit.GetWindowText(strFolder);


	if(strFolder.IsEmpty())
		return;

   if(strFolder[strFolder.GetLength() - 1] == '\\')
   {
      strFolder = strFolder.Left(strFolder.GetLength() - 1);
   }



	CFileFind filefind;

	String strFrom;
	String strTo;

	SHFILEOPSTRUCT fo;
	int iFound;
	int iFound2;

	TCHAR szFrom[1024];
	TCHAR szTo[1024];

	bool bOk;
	if(filefind.FindFile(strFolder + "\\*.*"))
	{
		while(true)
		{
			bOk = filefind.FindNextFile();
			if(!filefind.IsDirectory())
			{
				strFrom = filefind.GetFilePath();
				iFound = -1;
            int i;
				for( i = strFrom.GetLength() - 1; i >= 0; i--)
				{
					if(strFrom[i] == '\\')
					{
						iFound = i;
						break;
					}
				}
				iFound2 = -1;
				for( i = strFrom.GetLength() - 1; i >= iFound; i--)
				{
					if(strFrom[i] == '.')
					{
						iFound2 = i;
						break;
					}
				}
				if(iFound2 >= 0)
				{
					strTo = strFrom.Mid(iFound2 + 1);
					strTo.MakeLower();
					strTo = strFrom.Left(iFound2 + 1) + strTo;
					fo.hwnd = m_hWnd;
					fo.wFunc = FO_RENAME;
					_tcscpy(szTo, strTo);
					szTo[strTo.GetLength() + 1] = 0;
					_tcscpy(szFrom, strFrom);
					szFrom[strFrom.GetLength() + 1] = 0;
					if(strTo.Compare(strFrom) != 0)
					{
						fo.pFrom = szFrom;
						fo.pTo = szTo;
						fo.fFlags = 0;
						SHFileOperation(&fo);
					}
				}
			}
			if(!bOk)
				break;

		}
	}
	
}

void CFilerenView::OnButtonMove1() 
{
   String strFolder;
	
	m_edit.GetWindowText(strFolder);


	if(strFolder.IsEmpty())
		return;

   if(strFolder[strFolder.GetLength() - 1] == '\\')
   {
      strFolder = strFolder.Left(strFolder.GetLength() - 1);
   }

	CFileFind filefind;

	String strPath;
   String strName;
	String str;

   String strSrc;
   String strDst;
   int iFind;

   String strFolderDst;

	SHFILEOPSTRUCT fo;
	int iFound;
	int iFound2;

	TCHAR szFrom[1024];
	TCHAR szTo[1024];

	bool bOk = true;
   StringArray straPath;
   StringArray straName;
	if(filefind.FindFile(strFolder + "\\*.*"))
	{
      while(bOk)
      {
         bOk = filefind.FindNextFile();
		   if(!filefind.IsDirectory())
		   {
			   strPath = filefind.GetFilePath();
            iFind = strPath.Find("_-_");
            if(iFind > 0 && strPath.GetLength() - 3)
            {
               straPath.Add(strPath);
               strName = filefind.GetFileName();
               straName.Add(strName);
               TRACE("%s -> %s\n", strPath, strName);
            }
		   }
      }
	}
   for(int i = 0; i < straPath.GetSize(); i++)
   {
      strSrc = straPath[i];
      strName = straName[i];

      str = strName.Left(1);
      str.MakeLower();

      strFolderDst = strFolder + "\\" + str;
      strFolderDst.MakeLower();

      CreateDirectory(strFolderDst, NULL);

      iFind = strName.Find("_-_");
      if(iFind > 0)
      {
         strFolderDst += "\\" + strName.Left(iFind);
         strFolderDst.MakeLower();
         CreateDirectory(strFolderDst, NULL);
         strDst = strFolderDst + "\\" + strName;
         CopyFile(strSrc, strDst, FALSE);
      }
      
   }
}

void CFilerenView::OnBnClickedButtonReplaceSpecial()
{
	String strFolder;
	
	m_edit.GetWindowText(strFolder);


	if(strFolder.IsEmpty())
		return;
   if(strFolder[strFolder.GetLength() - 1] == '\\')
   {
      strFolder = strFolder.Left(strFolder.GetLength() - 1);
   }


	CFileFind filefind;

	String strFrom;
	String strTo;

	SHFILEOPSTRUCT fo;
	int iFound;

	TCHAR szFrom[1024];
	TCHAR szTo[1024];

	bool bOk;
	if(filefind.FindFile(strFolder + "\\*.*"))
	{
		while(true)
		{
			bOk = filefind.FindNextFile();
			if(!filefind.IsDirectory())
			{
				strFrom = filefind.GetFilePath();
				iFound = -1;
				for(int i = strFrom.GetLength() - 1; i >= 0; i--)
				{
					if(strFrom[i] == '\\')
					{
						iFound = i;
						break;
					}
				}
				if(iFound >= 0)
				{
					strTo = strFrom.Mid(iFound + 1);
               ReplaceSpecial(strTo);
					strTo = strFrom.Left(iFound + 1) + strTo;
					fo.hwnd = m_hWnd;
					fo.wFunc = FO_RENAME;
					_tcscpy(szTo, strTo);
					szTo[strTo.GetLength() + 1] = 0;
					_tcscpy(szFrom, strFrom);
					szFrom[strFrom.GetLength() + 1] = 0;
					if(strTo != strFrom)
					{
						fo.pFrom = szFrom;
						fo.pTo = szTo;
						fo.fFlags = 0;
						SHFileOperation(&fo);
					}
				}
			}
			if(!bOk)
				break;

		}
	}

}

void CFilerenView::ReplaceSpecial(String & str)
{
   str.Replace("'", "_");
   str.Replace(",", "_");
   str.Replace("à", "a");
   str.Replace("á", "a");
   str.Replace("í", "i");
   str.Replace("õ", "o");
   str.Replace("ò", "o");
   str.Replace("ó", "o");
   str.Replace("ù", "u");
}

void CFilerenView::OnBnClickedButtonReplace()
{
   String strFolder;
	m_edit.GetWindowText(strFolder);

   String strFind;
	m_editFind.GetWindowText(strFind);

   String strReplace;
	m_editReplace.GetWindowText(strReplace);

	if(strFolder.IsEmpty())
		return;
   if(strFolder[strFolder.GetLength() - 1] == '\\')
   {
      strFolder = strFolder.Left(strFolder.GetLength() - 1);
   }


	CFileFind filefind;

	String strFrom;
	String strTo;

	SHFILEOPSTRUCT fo;
	int iFound;

	TCHAR szFrom[1024];
	TCHAR szTo[1024];

	bool bOk;
	if(filefind.FindFile(strFolder + "\\*.*"))
	{
		while(true)
		{
			bOk = filefind.FindNextFile();
			if(!filefind.IsDirectory())
			{
				strFrom = filefind.GetFilePath();
				iFound = -1;
				for(int i = strFrom.GetLength() - 1; i >= 0; i--)
				{
					if(strFrom[i] == '\\')
					{
						iFound = i;
						break;
					}
				}
				if(iFound >= 0)
				{
					strTo = strFrom.Mid(iFound + 1);
               strTo.Replace(strFind, strReplace);
					strTo = strFrom.Left(iFound + 1) + strTo;
					fo.hwnd = m_hWnd;
					fo.wFunc = FO_RENAME;
					_tcscpy(szTo, strTo);
					szTo[strTo.GetLength() + 1] = 0;
					_tcscpy(szFrom, strFrom);
					szFrom[strFrom.GetLength() + 1] = 0;
					if(strTo != strFrom)
					{
						fo.pFrom = szFrom;
						fo.pTo = szTo;
						fo.fFlags = 0;
						SHFileOperation(&fo);
					}
				}
			}
			if(!bOk)
				break;

		}
	}

}

void CFilerenView::OnBnClickedEdit1Paste()
{
   m_edit.Paste();
}
