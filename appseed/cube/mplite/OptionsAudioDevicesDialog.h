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
   public ::userbase::form
{
// Construction
public:
   void FillSoundRecordingCombo();
   void FillMidiPlaybackCombo();
   COptionsAudioDevicesDialog(::ca::window* pParent = NULL);   // standard constructor

// Dialog Data
   //{{AFX_DATA(COptionsAudioDevicesDialog)
   enum { IDD = IDD_OPTIONS_AUDIO_DEVICES };
   simple_combo_box   m_comboSoundRecording;
   simple_combo_box   m_comboMidiPlayback;
   //}}AFX_DATA

protected:
    bool        m_bModified;
// Operations
public:
    BOOL Update(BOOL bSaveAndValidate = TRUE);
   BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);


// Overrides
public:
    virtual BOOL create(::ca::window* pParentWnd);

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(COptionsAudioDevicesDialog)
   public:
   
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
public:
   void set_modified_flag(bool bModified = true);
   bool is_modified();
   void SetSoundRecordingDevice(UINT uiDev);
   void SetMidiPlaybackDevice(UINT uiDev);
   UINT GetSoundRecordingDevice();
   UINT GetMidiPlaybackDevice();


   // Generated message ::collection::map functions
   //{{AFX_MSG(COptionsAudioDevicesDialog)
   afx_msg void OnSelchangeComboMidiPlayback();
   afx_msg void OnSelchangeComboSoundRecording();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   ()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSAUDIODEVICES_H__6B8ECF6A_23E3_4EDE_9AB0_BE4A03600D5B__INCLUDED_)
