#include "StdAfx.h"
#include "OptionsAudioDevicesView.h"


OptionsAudioDevicesView::OptionsAudioDevicesView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   ::user::form(papp)
{
   m_etranslucency = TranslucencyPresent;
}

void OptionsAudioDevicesView::FillMidiPlaybackCombo()
{
   simple_combo_box * pcombo = dynamic_cast < simple_combo_box * > (GetDlgItem("IDC_COMBO_MIDI_PLAYBACK"));

   UINT uiDevs = midiOutGetNumDevs();
   MIDIOUTCAPS moc;
   int iItem;
   string str;
   throw not_implemented_exception();
//   str.load_string(IDS_MIDIMAPPER);
   iItem = pcombo->AddString(str);
   if(iItem == CB_ERR)
      return;
   pcombo->SetItemData(iItem, MIDI_MAPPER);

   MMRESULT mmrc;
   for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
   {
      if(MMSYSERR_NOERROR == (mmrc = midiOutGetDevCaps(uiDev, &moc, sizeof(moc))))
      {
         iItem = pcombo->AddString(moc.szPname);
         if(iItem == CB_ERR)
            return;
         pcombo->SetItemData(iItem, uiDev);
      }
   }
}

void OptionsAudioDevicesView::FillSoundRecordingCombo()
{
   simple_combo_box * pcombo = dynamic_cast < simple_combo_box * > (GetDlgItem("IDC_COMBO_SOUND_RECORDING"));
   
   UINT uiDevs = waveInGetNumDevs();
   WAVEINCAPS moc;
   int iItem;
   string str;
   throw not_implemented_exception();
   //str.load_string(IDS_WAVEMAPPER);
   iItem = pcombo->AddString(str);
    if(iItem == CB_ERR)
        return;
   pcombo->SetItemData(iItem, WAVE_MAPPER);
   MMRESULT mmrc;
   for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
   {
      if(MMSYSERR_NOERROR == (mmrc = waveInGetDevCaps(uiDev, &moc, sizeof(moc))))
      {
         pcombo->AddString(moc.szPname);
         if(iItem == CB_ERR)
            return;
         pcombo->SetItemData(iItem, uiDev);
      }
   }
   
}

BOOL OptionsAudioDevicesView::UpdateDatabase(BOOL bSaveAndValidate)
{
   if(bSaveAndValidate)
   {
      UINT uiDev = GetMidiPlaybackDevice();
      //data_set("MidiOutDevice", 0, 0, (int) uiDev);
      uiDev = GetSoundRecordingDevice();
      data_set("WaveInDevice", ::ca::system::idEmpty, (int) uiDev);
      set_modified_flag(false);
        
   }
   else
   {
      int iDev;
      if(!data_get("MidiOutDevice", ::ca::system::idEmpty, iDev))
         iDev = -1;
      SetMidiPlaybackDevice((UINT) iDev);
      if(!data_get("WaveInDevice", ::ca::system::idEmpty, iDev))
         iDev = -1;
      SetSoundRecordingDevice((UINT) iDev);
   }
   return TRUE;
}


UINT OptionsAudioDevicesView::GetMidiPlaybackDevice()
{
   simple_combo_box * pcombo = dynamic_cast < simple_combo_box * > (GetDlgItem("IDC_COMBO_MIDI_PLAYBACK"));
   return pcombo->GetItemData(pcombo->get_cur_sel());
}

UINT OptionsAudioDevicesView::GetSoundRecordingDevice()
{
   simple_combo_box * pcombo = dynamic_cast < simple_combo_box * > (GetDlgItem("IDC_COMBO_SOUND_RECORDING"));
   return pcombo->GetItemData(pcombo->get_cur_sel());
}

void OptionsAudioDevicesView::SetMidiPlaybackDevice(UINT uiDev)
{
   simple_combo_box * pcombo = dynamic_cast < simple_combo_box * > (GetDlgItem("IDC_COMBO_MIDI_PLAYBACK"));
   int iCount = pcombo->get_count();
   for(int i = 0; i < iCount; i++)
   {
      if(pcombo->GetItemData(i) == uiDev)
      {
         pcombo->set_cur_sel(i);
         break;
      }
   }
}

void OptionsAudioDevicesView::SetSoundRecordingDevice(UINT uiDev)
{
   simple_combo_box * pcombo = dynamic_cast < simple_combo_box * > (GetDlgItem("IDC_COMBO_SOUND_RECORDING"));
   int iCount = pcombo->get_count();
   for(int i = 0; i < iCount; i++)
   {
      if(pcombo->GetItemData(i) == uiDev)
      {
         pcombo->set_cur_sel(i);
         break;
      }
   }
}

bool OptionsAudioDevicesView::is_modified()
{
    return m_bModified;

}


void OptionsAudioDevicesView::_001OnSelchangeComboMidiPlayback(gen::signal_object *) 
{
   set_modified_flag();
}

void OptionsAudioDevicesView::_001OnSelchangeComboSoundRecording(gen::signal_object *) 
{
   set_modified_flag();
}

void OptionsAudioDevicesView::set_modified_flag(bool bModified)
{
    if(bModified)
    {
        m_bModified = true;
        GetParent()->PostMessage(WM_USER, 1000);
    }
    else
    {
        m_bModified = false;
    }

}

BOOL OptionsAudioDevicesView::OnInitDialog() 
{
//   SimpleFormView::OnInitDialog();
   
   FillMidiPlaybackCombo();
   FillSoundRecordingCombo();

// trans   UpdateData(FALSE);
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

/*void OptionsAudioDevicesView::_001InitializeFormPreData()
{
   user::control::descriptor control;

    control.set_type(user::control::type_static);
   control.m_uiId = IDC_STATIC_AUDIO_RECORDING;
   control.m_typeinfo = &typeid(simple_static);
   control.m_bTransparent = true;
   _001AddControl(control);

    control.set_type(user::control::type_static);
   control.m_uiId = IDC_STATIC_AUDIO_RECORDING_ICON;
   control.m_typeinfo = &typeid(simple_static);
   control.m_bTransparent = true;
   _001AddControl(control);

   control.set_type(user::control::type_static);
   control.m_uiId = IDC_STATIC_AUDIO_RECORDING_LABEL;
   control.m_typeinfo = &typeid(simple_static);
   control.m_bTransparent = true;
   _001AddControl(control);

   control.set_type(user::control::type_combo_box);
   control.m_uiId = IDC_COMBO_SOUND_RECORDING;
   control.m_typeinfo = &typeid(simple_combo_box);
   control.m_datakey = "WaveInDevice";
   control.GetComboBox()->m_datakeyFill = "WaveInDevices";
   _001AddControl(control);


    control.set_type(user::control::type_static);
   control.m_uiId = IDC_STATIC_MIDI_PLAYBACK;
   control.m_typeinfo = &typeid(simple_static);
   control.m_bTransparent = true;
   _001AddControl(control);

    control.set_type(user::control::type_static);
   control.m_uiId = IDC_STATIC_MIDI_PLAYBACK_ICON;
   control.m_typeinfo = &typeid(simple_static);
   control.m_bTransparent = true;
   _001AddControl(control);

   control.set_type(user::control::type_static);
   control.m_uiId = IDC_STATIC_MIDI_PLAYBACK_LABEL;
   control.m_typeinfo = &typeid(simple_static);
   control.m_bTransparent = true;
   _001AddControl(control);

   control.set_type(user::control::type_combo_box);
   control.m_uiId = IDC_COMBO_MIDI_PLAYBACK;
   control.m_typeinfo = &typeid(simple_combo_box);
   control.m_datakey = "MidiOutDevice";
   control.GetComboBox()->m_datakeyFill = "MidiOutDevices";
   _001AddControl(control);

}*/

void OptionsAudioDevicesView::_001OnInitializeForm(user::control * pcontrol)
{
   if(pcontrol->descriptor().m_id == "IDC_COMBO_SOUND_RECORDING")
   {
//      _001FillCombo(control);
   }
   else if(pcontrol->descriptor().m_id == "IDC_COMBO_MIDI_PLAYBACK")
   {
      //FillMidiPlaybackCombo();
//      _001FillCombo(control);
   }
}
