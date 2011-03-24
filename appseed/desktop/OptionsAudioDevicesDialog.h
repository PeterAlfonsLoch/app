#if !defined(AFX_OPTIONSAUDIODEVICES_H__6B8ECF6A_23E3_4EDE_9AB0_BE4A03600D5B__INCLUDED_)
#define AFX_OPTIONSAUDIODEVICES_H__6B8ECF6A_23E3_4EDE_9AB0_BE4A03600D5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsAudioDevices.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsAudioDevicesDialog dialog

class COptionsAudioDevicesDialog :
   public BaseForm
{
// Construction
public:
	void FillSoundRecordingCombo();
	void FillMidiPlaybackCombo();
	COptionsAudioDevicesDialog(base_wnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsAudioDevicesDialog)
	enum { IDD = IDD_OPTIONS_AUDIO_DEVICES };
	CComboBox	m_comboSoundRecording;
	CComboBox	m_comboMidiPlayback;
	//}}AFX_DATA

protected:
    bool        m_bModified;
// Operations
public:
    BOOL Update(BOOL bSaveAndValidate = TRUE);
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);


// Overrides
public:
    virtual BOOL Create(base_wnd* pParentWnd);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsAudioDevicesDialog)
	public:
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
public:
	void SetModifiedFlag(bool bModified = true);
	bool IsModified();
	void SetSoundRecordingDevice(UINT uiDev);
	void SetMidiPlaybackDevice(UINT uiDev);
	UINT GetSoundRecordingDevice();
	UINT GetMidiPlaybackDevice();


	// Generated message map functions
	//{{AFX_MSG(COptionsAudioDevicesDialog)
	afx_msg void OnSelchangeComboMidiPlayback();
	afx_msg void OnSelchangeComboSoundRecording();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSAUDIODEVICES_H__6B8ECF6A_23E3_4EDE_9AB0_BE4A03600D5B__INCLUDED_)
