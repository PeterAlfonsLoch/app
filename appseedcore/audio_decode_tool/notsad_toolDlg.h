// notsad_toolDlg.h : header file
//

#pragma once


// notSadToolDlg dialog
class notSadToolDlg : public CDHtmlDialog
{
public:
	notSadToolDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_NOTSAD_TOOL_DIALOG, IDH = IDR_HTML_NOTSAD_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
