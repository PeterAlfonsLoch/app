// RemoveTwoDirDuplicatesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "fileren.h"
#include "RemoveTwoDirDuplicatesDialog.h"


// RemoveTwoDirDuplicatesDialog

IMPLEMENT_DYNCREATE(RemoveTwoDirDuplicatesDialog, CFormView)

RemoveTwoDirDuplicatesDialog::RemoveTwoDirDuplicatesDialog()
	: CFormView(RemoveTwoDirDuplicatesDialog::IDD)
{

}

RemoveTwoDirDuplicatesDialog::~RemoveTwoDirDuplicatesDialog()
{
}

void RemoveTwoDirDuplicatesDialog::DoDataExchange(CDataExchange* pDX)
{
   CFormView::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT_KEEP, m_editKeep);
   DDX_Control(pDX, IDC_EDIT_REMOVE, m_editRemove);
   DDX_Control(pDX, IDC_EDIT_REMOVED, m_editRemoved);
}

BEGIN_MESSAGE_MAP(RemoveTwoDirDuplicatesDialog, CFormView)
   ON_EN_CHANGE(IDC_EDIT_KEEP, &RemoveTwoDirDuplicatesDialog::OnEnChangeEditKeep)
   ON_BN_CLICKED(IDC_EDIT_PASTE_KEEP, &RemoveTwoDirDuplicatesDialog::OnBnClickedEditPasteKeep)
   ON_BN_CLICKED(IDC_EDIT_PASTE_REMOVE, &RemoveTwoDirDuplicatesDialog::OnBnClickedEditPasteRemove)
   ON_BN_CLICKED(IDC_BUTTON_PROCESS, &RemoveTwoDirDuplicatesDialog::OnBnClickedButtonProcess)
   ON_BN_CLICKED(IDC_EDIT_PASTE_REMOVED, &RemoveTwoDirDuplicatesDialog::OnBnClickedEditPasteRemoved)
END_MESSAGE_MAP()


// RemoveTwoDirDuplicatesDialog diagnostics

#ifdef _DEBUG
void RemoveTwoDirDuplicatesDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void RemoveTwoDirDuplicatesDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// RemoveTwoDirDuplicatesDialog message handlers

void RemoveTwoDirDuplicatesDialog::OnEnChangeEditKeep()
{
   // TODO:  If this is a RICHEDIT control, the control will not
   // send this notification unless you override the CFormView::OnInitDialog()
   // function and call CRichEditCtrl().SetEventMask()
   // with the ENM_CHANGE flag ORed into the mask.

   // TODO:  Add your control notification handler code here
}

void RemoveTwoDirDuplicatesDialog::OnBnClickedEditPasteKeep()
{
   m_editKeep.Paste();
}

void RemoveTwoDirDuplicatesDialog::OnBnClickedEditPasteRemove()
{
   m_editRemove.Paste();
}

void RemoveTwoDirDuplicatesDialog::OnBnClickedButtonProcess()
{
   String strKeep;
   String strRemove;
   String strRemoved;
   AStrArray straKeep;
   AStrArray straRemove;
   strKeep = MyGetWindowText((HWND) m_editKeep);
   strRemove = ::MyGetWindowText((HWND) m_editRemove);
   strRemoved = ::MyGetWindowText((HWND) m_editRemoved);
   CalcLongPathName(strKeep);
   CalcLongPathName(strRemove);
   if(strKeep == strRemove)
   {
      AfxMessageBox("Directories cannot be the same");
      return;
   }

   BaseIntArray iaLenKeep;
   BaseIntArray iaLenRemove;

   GetDirFiles(strKeep, straKeep);
   GetDirFiles(strRemove, straRemove);
   GetFilesSize(straKeep, iaLenKeep);
   GetFilesSize(straRemove, iaLenRemove);
   


   String strFileKeep;
   String strFileRemove;
   int iLenKeep;
   int iLenRemove;
   for(int iKeep = 0; iKeep < straKeep.GetSize();)
   {
      strFileKeep = straKeep[iKeep];
      iLenKeep = iaLenKeep[iKeep];
      if(iLenKeep == -1)
      {
         straKeep.RemoveAt(iKeep);
         iaLenKeep.RemoveAt(iKeep);
         continue;
      }
      for(int iRemove = 0; iRemove < straRemove.GetSize();)
      {
         strFileRemove = straRemove[iRemove];
         iLenRemove = iaLenRemove[iRemove];
         if(iLenRemove == -1)
         {
            straRemove.RemoveAt(iRemove);
            iaLenRemove.RemoveAt(iRemove);
            continue;
         }

         if(iLenKeep != iLenRemove)
         {
            iRemove++;
            continue;
         }
         
         if(RemoveDuplicate(strFileKeep, strFileRemove, strRemoved))
         {
            straRemove.RemoveAt(iRemove);
            iaLenRemove.RemoveAt(iRemove);
            continue;
         }
         iRemove++;
      }
      iKeep++;
   }

   

}

void RemoveTwoDirDuplicatesDialog::CalcLongPathName(String & str)
{
   String strParam = str;
   String strRet = str;
   LPTSTR lpsz = strRet.GetBufferSetLength(1024);
   DWORD dw = ::GetLongPathName(strParam, lpsz, 1024);
   if(dw > 1024)
   {
      strRet.ReleaseBuffer();
      lpsz = strRet.GetBufferSetLength(dw);
      dw = ::GetLongPathName(strParam, lpsz, 1024);
   }
   strRet.ReleaseBuffer();
   str = strRet;
}

void RemoveTwoDirDuplicatesDialog::GetDirFiles(LPCSTR lpcszDir, AStrArray & stra)
{
   String strFolder(lpcszDir);

	if(strFolder.IsEmpty())
		return;

   if(strFolder[strFolder.GetLength() - 1] == '\\')
   {
      strFolder = strFolder.Left(strFolder.GetLength() - 1);
   }

   Ex1FileSet fileset;
   AStrArray straBase;
   AStrArray straFilter;
   straBase.Add(lpcszDir);
   straFilter.Add("*.*");
   fileset.AddSearch(straBase, straFilter);

   String str;
   for(int i = 0; i < fileset.GetFileCount(); i++)
   {
      fileset.FileAt(i, str);
      stra.Add(str);
   }
}

int RemoveTwoDirDuplicatesDialog::GetFileSize(LPCTSTR lpcszFile)
{
   Ex1File file;
   if(!file.Open(lpcszFile, Ex1File::modeRead | Ex1File::typeBinary))
      return -1;
   return file.GetLength();

}

bool RemoveTwoDirDuplicatesDialog::RemoveDuplicate(LPCTSTR lpcszKeep, LPCTSTR lpcszRemove, LPCTSTR lpcszRemoved)
{
   Ex1File fileKeep;
   Ex1File fileRemove;

   if(!fileKeep.Open(lpcszKeep, Ex1File::modeRead | Ex1File::typeBinary))
      return false;
   if(!fileRemove.Open(lpcszRemove, Ex1File::modeRead | Ex1File::typeBinary))
      return false;

   if(fileKeep.GetLength() != fileRemove.GetLength())
      return false;

   MemoryStorage mem1;
   MemoryStorage mem2;
   mem1.Allocate(1024 * 512);
   mem2.Allocate(1024 * 512);
   int iLen = fileKeep.GetLength();
   int iRemain = iLen;
   int iRead1;
   int iRead2;
   while(iRemain > 0)
   {
      iRead1 = fileKeep.Read(mem1.GetAllocation(), mem1.GetStorageSize());
      iRead2 = fileRemove.Read(mem2.GetAllocation(), mem2.GetStorageSize());
      if(iRead1 != iRead2)
      {
         return false;
      }
      if(memcmp(mem1.GetAllocation(), mem2.GetAllocation(), iRead2) != 0)
         return false;
      iRemain -= iRead1;
   }

   fileKeep.Close();
   fileRemove.Close();

   String strRemoved;
   strRemoved = lpcszRemoved;
   if(strRemoved.GetLength() == 0)
      return false;
   if(strRemoved.Right(1) != "\\")
      strRemoved += "\\";
   String strRemove;
   strRemove = lpcszRemove;
   strRemove = strRemove.Mid(strRemove.ReverseFind('\\') + 1);
   strRemoved += strRemove;
   WString wstrRemove;
   WString wstrRemoved;
   International::Utf8ToUnicode(wstrRemove, lpcszRemove);
   International::Utf8ToUnicode(wstrRemoved, strRemoved);
   ::MoveFileW(wstrRemove, wstrRemoved);
   return true;
}

void RemoveTwoDirDuplicatesDialog::GetFilesSize(AStrArray & stra, BaseIntArray & ia)
{
   ia.SetSize(stra.GetSize());
   for(int i = 0; i < stra.GetSize(); i++)
   {
      ia[i] = GetFileSize(stra[i]);
   }
}

void RemoveTwoDirDuplicatesDialog::OnBnClickedEditPasteRemoved()
{
   m_editRemoved.Paste();
}
