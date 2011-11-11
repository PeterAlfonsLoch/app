// MainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "notsad_tool.h"
#include "MainDialog.h"


// MainDialog dialog

IMPLEMENT_DYNAMIC(MainDialog, CDialog)

MainDialog::MainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MainDialog::IDD, pParent)
   , m_strFilePath(_T(""))
{
}

MainDialog::~MainDialog()
{
}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
   DDX_Control(pDX, IDC_BUTTON_EXECUTE_PLAY, m_btnPlay);
   DDX_Control(pDX, IDC_BUTTON_EXECUTE_STOP, m_btnStop);
}


BEGIN_MESSAGE_MAP(MainDialog, CDialog)
   ON_WM_CREATE()
   ON_BN_CLICKED(IDC_BUTTON_BROWSE, &MainDialog::OnBnClickedButtonBrowse)
   ON_BN_CLICKED(IDC_BUTTON_EXECUTE_PLAY, &MainDialog::OnBnClickedButtonExecutePlay)
   ON_BN_CLICKED(IDC_BUTTON_EXECUTE_STOP, &MainDialog::OnBnClickedButtonExecuteStop)
   ON_MESSAGE(MessageAudioPlayer, &MainDialog::OnAudioPlayerMessage)
END_MESSAGE_MAP()


// MainDialog message handlers

int MainDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CDialog::OnCreate(lpCreateStruct) == -1)
      return -1;

   SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);


   return 0;
}

void MainDialog::OnBnClickedButtonBrowse()
{
   CFileDialog dlg(TRUE, "*.wav");

   int iBufSize = 1024;
   dlg.GetOFN().lpstrFile = m_strFilePath.GetBuffer(iBufSize);
   dlg.GetOFN().nMaxFile = iBufSize;

   INT_PTR nResult = dlg.DoModal();
   m_strFilePath.ReleaseBuffer();

   if(nResult == IDOK)
   {
      UpdateData(FALSE);
   }

}

void MainDialog::OnBnClickedButtonExecutePlay()
{
   m_btnPlay.EnableWindow(FALSE);
   m_player.Open(m_strFilePath, GetSafeHwnd(), MessageAudioPlayer);
   m_player.Play();
   m_btnStop.EnableWindow();
}

void MainDialog::OnBnClickedButtonExecuteStop()
{
   m_btnStop.EnableWindow(FALSE);
   m_player.Stop();
   m_player.Close();
   m_btnPlay.EnableWindow();
}


LRESULT MainDialog::OnAudioPlayerMessage(WPARAM wparam, LPARAM lparam)
{
   switch(wparam)
   {
   case AudioPlayer::NotifyPlaybackEnd:
      m_btnStop.EnableWindow(FALSE);
      m_btnPlay.EnableWindow();
      break;
   }
   return 0;
}