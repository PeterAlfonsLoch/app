#pragma once

class OptionsSongsAudioDevicesDialog :
   public dialog
{
public:
   OptionsSongsAudioDevicesDialog(::ca::application * papp);

   void FillSoundRecordingCombo();
   void FillMidiPlaybackCombo();
   

   bool        m_bModified;

   BOOL Update(BOOL bSaveAndValidate = TRUE);
   BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

   virtual BOOL create(::ca::window* pParentWnd);

   
//   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   void set_modified_flag(bool bModified = true);
   bool is_modified();
   void SetSoundRecordingDevice(UINT uiDev);
   void SetMidiPlaybackDevice(UINT uiDev);
   UINT GetSoundRecordingDevice();
   UINT GetMidiPlaybackDevice();


   afx_msg void OnSelchangeComboMidiPlayback();
   afx_msg void OnSelchangeComboSoundRecording();
   virtual BOOL OnInitDialog();
};

