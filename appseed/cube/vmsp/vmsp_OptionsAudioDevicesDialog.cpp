#include "StdAfx.h"
#include "OptionsAudioDevicesDialog.h"

OptionsSongsAudioDevicesDialog::OptionsSongsAudioDevicesDialog(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   dialog(papp)
{
}


/*void OptionsSongsAudioDevicesDialog::DoDataExchange(CDataExchange* pDX)
{
/*   dialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(OptionsSongsAudioDevicesDialog)
   DDX_Control(pDX, IDC_COMBO_SOUND_RECORDING, m_comboSoundRecording);
   DDX_Control(pDX, IDC_COMBO_MIDI_PLAYBACK, m_comboMidiPlayback);
   //}}AFX_DATA_MAP*/
//}



void OptionsSongsAudioDevicesDialog::FillMidiPlaybackCombo()
{
  /*  UINT uiDevs = midiOutGetNumDevs();
    MIDIOUTCAPS moc;
    int iItem;
    string str;
    str.load_string(IDS_MIDIMAPPER);
    iItem = m_comboMidiPlayback.AddString(str);
    if(iItem == CB_ERR)
        return;
    m_comboMidiPlayback.SetItemData(iItem, MIDI_MAPPER);
   MMRESULT mmrc;
    for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
    {
        if(MMSYSERR_NOERROR == (mmrc = midiOutGetDevCaps(uiDev, &moc, sizeof(moc))))
      {
         iItem = m_comboMidiPlayback.AddString(moc.szPname);
         if(iItem == CB_ERR)
            return;
         m_comboMidiPlayback.SetItemData(iItem, uiDev);
      }
    }*/
}

void OptionsSongsAudioDevicesDialog::FillSoundRecordingCombo()
{
/*    UINT uiDevs = waveInGetNumDevs();
    WAVEINCAPS moc;
    int iItem;
    string str;
    str.load_string(IDS_WAVEMAPPER);
    iItem = m_comboSoundRecording.AddString(str);
    if(iItem == CB_ERR)
        return;
    m_comboSoundRecording.SetItemData(iItem, WAVE_MAPPER);
   MMRESULT mmrc;
    for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
    {
        if(MMSYSERR_NOERROR == (mmrc = waveInGetDevCaps(uiDev, &moc, sizeof(moc))))
      {
         iItem = m_comboSoundRecording.AddString(moc.szPname);
         if(iItem == CB_ERR)
            return;
         m_comboSoundRecording.SetItemData(iItem, uiDev);
      }
    }
*/
}

BOOL OptionsSongsAudioDevicesDialog::create(::ca::window* pParentWnd) 
{
   // TODO: add your specialized code here and/or call the base class
   
   //return ::ca::window::create(IDD, pParentWnd);
   return FALSE;
}

BOOL OptionsSongsAudioDevicesDialog::Update(BOOL bSaveAndValidate)
{
   if(bSaveAndValidate)
   {
//      if(!UpdateData())
      //   return FALSE;
      if(!UpdateDatabase())
         return FALSE;
   }
   else
   {
      if(!UpdateDatabase(FALSE))
         return FALSE;
//      if(!UpdateData(FALSE))
      //   return FALSE;
   }
   return TRUE;
}

BOOL OptionsSongsAudioDevicesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
/*   if(bSaveAndValidate)
   {
        UINT uiDev = GetMidiPlaybackDevice();
      data_set("MidiOutDevice", (int) uiDev);
        uiDev = GetSoundRecordingDevice();
      data_set("WaveInDevice", (int) uiDev);
        set_modified_flag(false);
        
   }
   else
   {
        int iDev;
      if(!data_get("MidiOutDevice", iDev))
         iDev = -1;
        SetMidiPlaybackDevice((UINT) iDev);
        
      if(!data_get("WaveInDevice",iDev))
         iDev = -1;
        SetSoundRecordingDevice((UINT) iDev);
        
   }*/
   return TRUE;
}


UINT OptionsSongsAudioDevicesDialog::GetMidiPlaybackDevice()
{
//    return m_comboMidiPlayback.GetItemData(m_comboMidiPlayback.get_cur_sel());
   return 0;
}

UINT OptionsSongsAudioDevicesDialog::GetSoundRecordingDevice()
{
   return 0;
    //return m_comboSoundRecording.GetItemData(m_comboSoundRecording.get_cur_sel());
}

void OptionsSongsAudioDevicesDialog::SetMidiPlaybackDevice(UINT uiDev)
{
    /*int iCount = m_comboMidiPlayback.get_count();
    for(int i = 0; i < iCount; i++)
    {
        if(m_comboMidiPlayback.GetItemData(i) == uiDev)
        {
            m_comboMidiPlayback.set_cur_sel(i);
            break;
        }
    }*/
}

void OptionsSongsAudioDevicesDialog::SetSoundRecordingDevice(UINT uiDev)
{
    /*int iCount = m_comboSoundRecording.get_count();
    for(int i = 0; i < iCount; i++)
    {
        if(m_comboSoundRecording.GetItemData(i) == uiDev)
        {
            m_comboSoundRecording.set_cur_sel(i);
            break;
        }
    }*/
}

bool OptionsSongsAudioDevicesDialog::is_modified()
{
    return m_bModified;

}


void OptionsSongsAudioDevicesDialog::OnSelchangeComboMidiPlayback() 
{
   // TODO: add your control notification handler code here
   set_modified_flag();
}

void OptionsSongsAudioDevicesDialog::OnSelchangeComboSoundRecording() 
{
   // TODO: add your control notification handler code here
   set_modified_flag();
}

void OptionsSongsAudioDevicesDialog::set_modified_flag(bool bModified)
{
    if(bModified)
    {
        m_bModified = true;
//        GetParent()->PostMessage(WM_USER, 1000);
    }
    else
    {
        m_bModified = false;
    }

}

BOOL OptionsSongsAudioDevicesDialog::OnInitDialog() 
{
//   dialog::OnInitDialog();
   
   FillMidiPlaybackCombo();
   FillSoundRecordingCombo();

   return TRUE;
}
