#pragma once

class CLASS_DECL_CA2_CUBE OptionsAudioDevicesView :
   public form_view
{
public:


   bool        m_bModified;


   void FillSoundRecordingCombo();
   void FillMidiPlaybackCombo();
   OptionsAudioDevicesView(::ca::application * papp);

   virtual void _001OnInitializeForm(user::control * pcontrol);

   BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);


   void set_modified_flag(bool bModified = true);
   bool is_modified();
   void SetSoundRecordingDevice(UINT uiDev);
   void SetMidiPlaybackDevice(UINT uiDev);
   UINT GetSoundRecordingDevice();
   UINT GetMidiPlaybackDevice();


   DECL_GEN_SIGNAL(_001OnSelchangeComboMidiPlayback)
   DECL_GEN_SIGNAL(_001OnSelchangeComboSoundRecording)
   virtual BOOL OnInitDialog();
};
