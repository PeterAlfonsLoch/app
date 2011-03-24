// OptionsAudioDevices.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OptionsAudioDevicesView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(OptionsAudioDevicesView, SimpleFormView)

/////////////////////////////////////////////////////////////////////////////
// OptionsAudioDevicesView dialog


OptionsAudioDevicesView::OptionsAudioDevicesView() :
SimpleFormView(OptionsAudioDevicesView::IDD),
BaseFormView(OptionsAudioDevicesView::IDD)
{
	//{{AFX_DATA_INIT(OptionsAudioDevicesView)
	//}}AFX_DATA_INIT
   IGUI_WIN_ON_NOTIFY(CBN_SELCHANGE, IDC_COMBO_MIDI_PLAYBACK     , this, this, &OptionsAudioDevicesView::_001OnSelchangeComboMidiPlayback);
   IGUI_WIN_ON_NOTIFY(CBN_SELCHANGE, IDC_COMBO_SOUND_RECORDING   , this, this, &OptionsAudioDevicesView::_001OnSelchangeComboSoundRecording);
//	ON_CBN_SELCHANGE(IDC_COMBO_SOUND_RECORDING, OnSelchangeComboSoundRecording)
}

void OptionsAudioDevicesView::DoDataExchange(CDataExchange* pDX)
{
	SimpleFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionsAudioDevicesView)
	//DDX_Control(pDX, IDC_COMBO_SOUND_RECORDING, m_comboSoundRecording);
	//DDX_Control(pDX, IDC_COMBO_MIDI_PLAYBACK, m_comboMidiPlayback);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsAudioDevicesView, SimpleFormView)
	//{{AFX_MSG_MAP(OptionsAudioDevicesView)
//	ON_CBN_SELCHANGE(IDC_COMBO_MIDI_PLAYBACK, OnSelchangeComboMidiPlayback)
//	ON_CBN_SELCHANGE(IDC_COMBO_SOUND_RECORDING, OnSelchangeComboSoundRecording)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsAudioDevicesView message handlers

void OptionsAudioDevicesView::FillMidiPlaybackCombo()
{
   SimpleComboBox * pcombo = (SimpleComboBox *) GetDlgItem(IDC_COMBO_MIDI_PLAYBACK);

   UINT uiDevs = midiOutGetNumDevs();
   MIDIOUTCAPS moc;
   int iItem;
   CString str;
   str.LoadString(IDS_MIDIMAPPER);
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
   SimpleComboBox * pcombo = (SimpleComboBox *) GetDlgItem(IDC_COMBO_SOUND_RECORDING);
   
   UINT uiDevs = waveInGetNumDevs();
   WAVEINCAPS moc;
   int iItem;
   CString str;
   str.LoadString(IDS_WAVEMAPPER);
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

/*BOOL OptionsAudioDevicesView::Create(CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleFormView::Create(IDD, pParentWnd);
}*/

BOOL OptionsAudioDevicesView::Update(BOOL bSaveAndValidate)
{
	if(bSaveAndValidate)
	{
		if(!UpdateData())
			return FALSE;
		if(!UpdateDatabase())
			return FALSE;
	}
	else
	{
		if(!UpdateDatabase(FALSE))
			return FALSE;
		if(!UpdateData(FALSE))
			return FALSE;
	}
	return TRUE;
}

BOOL OptionsAudioDevicesView::UpdateDatabase(BOOL bSaveAndValidate)
{
	if(bSaveAndValidate)
	{
        UINT uiDev = GetMidiPlaybackDevice();
		//VmsDataSet(VMSDATAKEY(MidiOutDevice), 0, 0, (int) uiDev);
        uiDev = GetSoundRecordingDevice();
		VmsDataSet(VMSDATAKEY(WaveInDevice), 0, 0, (int) uiDev);
        SetModifiedFlag(false);
        
	}
	else
	{
        int iDev;
		if(!VmsDataGet(VMSDATAKEY(MidiOutDevice), 0, 0, iDev))
			iDev = -1;
        SetMidiPlaybackDevice((UINT) iDev);
        
		if(!VmsDataGet(VMSDATAKEY(WaveInDevice), 0, 0, iDev))
			iDev = -1;
        SetSoundRecordingDevice((UINT) iDev);
        
	}
	return TRUE;
}


UINT OptionsAudioDevicesView::GetMidiPlaybackDevice()
{
   SimpleComboBox * pcombo = (SimpleComboBox *) GetDlgItem(IDC_COMBO_MIDI_PLAYBACK);
   return pcombo->GetItemData(pcombo->GetCurSel());
}

UINT OptionsAudioDevicesView::GetSoundRecordingDevice()
{
   SimpleComboBox * pcombo = (SimpleComboBox *) GetDlgItem(IDC_COMBO_SOUND_RECORDING);
   return pcombo->GetItemData(pcombo->GetCurSel());
}

void OptionsAudioDevicesView::SetMidiPlaybackDevice(UINT uiDev)
{
   SimpleComboBox * pcombo = (SimpleComboBox *) GetDlgItem(IDC_COMBO_MIDI_PLAYBACK);
   int iCount = pcombo->GetCount();
   for(int i = 0; i < iCount; i++)
   {
      if(pcombo->GetItemData(i) == uiDev)
      {
         pcombo->SetCurSel(i);
         break;
      }
   }
}

void OptionsAudioDevicesView::SetSoundRecordingDevice(UINT uiDev)
{
   SimpleComboBox * pcombo = (SimpleComboBox *) GetDlgItem(IDC_COMBO_SOUND_RECORDING);
   int iCount = pcombo->GetCount();
   for(int i = 0; i < iCount; i++)
   {
      if(pcombo->GetItemData(i) == uiDev)
      {
         pcombo->SetCurSel(i);
         break;
      }
   }
}

bool OptionsAudioDevicesView::IsModified()
{
    return m_bModified;

}


void OptionsAudioDevicesView::_001OnSelchangeComboMidiPlayback(gen::signal_object *) 
{
	// TODO: Add your control notification handler code here
	SetModifiedFlag();
}

void OptionsAudioDevicesView::_001OnSelchangeComboSoundRecording(gen::signal_object *) 
{
	// TODO: Add your control notification handler code here
	SetModifiedFlag();
}

void OptionsAudioDevicesView::SetModifiedFlag(bool bModified)
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
//	SimpleFormView::OnInitDialog();
	
    FillMidiPlaybackCombo();
    FillSoundRecordingCombo();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void OptionsAudioDevicesView::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

 	control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.m_uiId = IDC_STATIC_AUDIO_RECORDING;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
   control.m_bTransparent = true;
	_001AddControl(control);

 	control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.m_uiId = IDC_STATIC_AUDIO_RECORDING_ICON;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
   control.m_bTransparent = true;
	_001AddControl(control);

   control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.m_uiId = IDC_STATIC_AUDIO_RECORDING_LABEL;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
   control.m_bTransparent = true;
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeComboBox);
	control.m_uiId = IDC_COMBO_SOUND_RECORDING;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleComboBox);
	//control.m_datakey = VMSDATAKEY(ForceMidRegistration);
	_001AddControl(control);


 	control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.m_uiId = IDC_STATIC_MIDI_PLAYBACK;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
   control.m_bTransparent = true;
	_001AddControl(control);

 	control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.m_uiId = IDC_STATIC_MIDI_PLAYBACK_ICON;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
   control.m_bTransparent = true;
	_001AddControl(control);

   control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.m_uiId = IDC_STATIC_MIDI_PLAYBACK_LABEL;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
   control.m_bTransparent = true;
	_001AddControl(control);

   control.SetType(Ex1FormInterfaceControl::TypeComboBox);
	control.m_uiId = IDC_COMBO_MIDI_PLAYBACK;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleComboBox);
	control.m_datakey = VMSDATAKEY(MidiOutDevice);
   control.GetComboBox()->m_datakeyFill = VMSDATAKEY(MidiOutDevices);
	_001AddControl(control);

}

void OptionsAudioDevicesView::_001OnInitializeForm(Ex1FormInterfaceControl &control)
{
   if(control.m_uiId == IDC_COMBO_SOUND_RECORDING)
   {
      FillSoundRecordingCombo();
   }
   else if(control.m_uiId == IDC_COMBO_MIDI_PLAYBACK)
   {
      //FillMidiPlaybackCombo();
      _001FillCombo(control);
   }
}
