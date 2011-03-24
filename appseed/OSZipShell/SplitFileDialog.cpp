// SplitFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OSZipShell.h"
#include "SplitFileDialog.h"


// SplitFileDialog dialog

IMPLEMENT_DYNAMIC(SplitFileDialog, CDialog)

SplitFileDialog::SplitFileDialog(LPCTSTR lpcszFile, CWnd* pParent /*=NULL*/)
	: CDialog(SplitFileDialog::IDD, pParent)
   , m_iValue(0)
   , m_strMult(_T(""))
{
   m_strFile = lpcszFile;
}

SplitFileDialog::~SplitFileDialog()
{
}

void SplitFileDialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT1, m_iValue);
   DDV_MinMaxInt(pDX, m_iValue, 1, 1000000);
   DDX_CBString(pDX, IDC_COMBO1, m_strMult);
}


BEGIN_MESSAGE_MAP(SplitFileDialog, CDialog)
   ON_CBN_SELCHANGE(IDC_COMBO1, &SplitFileDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// SplitFileDialog message handlers

void SplitFileDialog::OnOK()
{

   if(UpdateData())
   {
      int iMult = 1;
      if(m_strMult == "bytes")
      {
         iMult = 1;
      }
      else if (m_strMult == "Kbytes")
      {
         iMult = 1024;
      }
      else if(m_strMult == "Mbytes")
      {
         iMult = 1024 * 1024;
      }

      int iSize = m_iValue * iMult;

      if(iSize > 50 * 1024 * 1024)
      {
         AfxMessageBox("Size greater thatn 50 mega bytes. Error.");
         return;
      }

      CString strSize;
      strSize.Format("%d", iSize);
      //AfxMessageBox(strSize);

      CStdioFile file;
      
      if(!file.Open(m_strFile, CFile::typeText | CFile::modeRead))
      {
         AfxMessageBox("Cannot open File for reading. Close other applications that may be using the file and than try again or cancel.");
         return;
      }

      int iFileSize = file.GetLength();

      int iCount = iFileSize / iSize;


      if(iCount > 100)
      {
         AfxMessageBox("By the time, The program does not split in more than approximately 100 pieces. Choose greater size please or cancel operation.");
         return;
      }

      int iPieceSize = iFileSize / iCount;


      CString strFileNew;
      CString strIndex;
      int iIndex = 1;
      CString strExtension;
      int iPos = m_strFile.ReverseFind('.');
      if(iPos >= 0)
      {
         strExtension = m_strFile.Mid(iPos);
      }
      CString strLine;
      int iPosStart;
      int iPosEnd;
      int iCurSize;
      while(true)
      {
         iCurSize = 0;
         while(true)
         {
            strFileNew = m_strFile;
            strFileNew += ".";
            strIndex.Format("%03d", iIndex);
            strFileNew += strIndex;
            strFileNew += strExtension;
            if(::GetFileAttributes(strFileNew) == INVALID_FILE_ATTRIBUTES)
            {
               break;
            }
            if(iIndex >= 1000)
            {
               AfxMessageBox("All the numeration is occupied by other files.");
               return;
            }
            iIndex++;
         }

         CStdioFile fileNew;

         fileNew.Open(strFileNew, CFile::typeText | CFile::modeCreate | CFile::modeWrite);

         iPosStart = file.GetPosition();
         while(file.ReadString(strLine))
         {
            strLine += "\r\n";
            fileNew.WriteString(strLine);
            iPosEnd = file.GetPosition();
            iCurSize = iPosEnd - iPosStart;
            if(iCurSize > iSize)
               break;
         }

         fileNew.Close();

         if(file.GetPosition() == file.GetLength())
         {
            break;
         }
      }

      CDialog::OnOK();
   }
}

void SplitFileDialog::OnCbnSelchangeCombo1()
{
   // TODO: Add your control notification handler code here
}

BOOL SplitFileDialog::OnInitDialog()
{
   m_strMult = "bytes";
   CDialog::OnInitDialog();


   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
