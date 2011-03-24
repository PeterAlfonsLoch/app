#pragma once
#include "afxwin.h"

#include "AudioPlayer.h"


// MainDialog dialog

class MainDialog : public CDialog
{
	DECLARE_DYNAMIC(MainDialog)

public:
	MainDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MainDialog();

   enum EMessage
   {
      MessageAudioPlayer = WM_USER + 100
   };
// Dialog Data
	enum { IDD = IDD_MAINDIALOG };

   AudioPlayer m_player;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
   afx_msg void OnBnClickedButtonBrowse();
public:
   CString m_strFilePath;
public:
   afx_msg void OnBnClickedButtonExecutePlay();
public:
   afx_msg void OnBnClickedButtonExecuteStop();
   afx_msg LRESULT OnAudioPlayerMessage(WPARAM wparam, LPARAM lparam);
public:
   CButton m_btnPlay;
public:
   CButton m_btnStop;
};
