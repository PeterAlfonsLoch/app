// OptionsAudioDevices.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OptionsAudioDevicesDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsAudioDevicesDialog dialog


COptionsAudioDevicesDialog::COptionsAudioDevicesDialog(CWnd* pParent /*=NULL*/)
	: BaseForm(COptionsAudioDevicesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsAudioDevicesDialog)
	//}}AFX_DATA_INIT
}


void COptionsAudioDevicesDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsAudioDevicesDialog)
	DDX_Control(pDX, IDC_COMBO_SOUND_RECORDING, m_comboSoundRecording);
	DDX_Control(pDX, IDC_COMBO_MIDI_PLAYBACK, m_comboMidiPlayback);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsAudioDevicesDialog, BaseForm)
	//{{AFX_MSG_MAP(COptionsAudioDevicesDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MIDI_PLAYBACK, OnSelchangeComboMidiPlayback)
	ON_CBN_SELCHANGE(IDC_COMBO_SOUND_RECORDING, OnSelchangeComboSoundRecording)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsAudioDevicesDialog message handlers

void COptionsAudioDevicesDialog::FillMidiPlaybackCombo()
{
    UINT uiDevs = midiOutGetNumDevs();
    MIDIOUTCAPS moc;
    int iItem;
    CString str;
    str.LoadString(IDS_MIDIMAPPER);
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
    }
}

void COptionsAudioDevicesDialog::FillSoundRecordingCombo()
{
    UINT uiDevs = waveInGetNumDevs();
    WAVEINCAPS moc;
    int iItem;
    CString str;
    str.LoadString(IDS_WAVEMAPPER);
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

}

BOOL COptionsAudioDevicesDialog::Create(CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return BaseForm::Create(IDD, pParentWnd);
}

BOOL COptionsAudioDevicesDialog::Update(BOOL bSaveAndValidate)
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

BOOL COptionsAudioDevicesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
	if(bSaveAndValidate)
	{
        UINT uiDev = GetMidiPlaybackDevice();
		VmsDataSet(VMSDATAKEY(MidiOutDevice), 0, 0, (int) uiDev);
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


UINT COptionsAudioDevicesDialog::GetMidiPlaybackDevice()
{
    return m_comboMidiPlayback.GetItemData(m_comboMidiPlayback.GetCurSel());
}

UINT COptionsAudioDevicesDialog::GetSoundRecordingDevice()
{
    return m_comboSoundRecording.GetItemData(m_comboSoundRecording.GetCurSel());
}

void COptionsAudioDevicesDialog::SetMidiPlaybackDevice(UINT uiDev)
{
    int iCount = m_comboMidiPlayback.GetCount();
    for(int i = 0; i < iCount; i++)
    {
        if(m_comboMidiPlayback.GetItemData(i) == uiDev)
        {
            m_comboMidiPlayback.SetCurSel(i);
            break;
        }
    }
}

void COptionsAudioDevicesDialog::SetSoundRecordingDevice(UINT uiDev)
{
    int iCount = m_comboSoundRecording.GetCount();
    for(int i = 0; i < iCount; i++)
    {
        if(m_comboSoundRecording.GetItemData(i) == uiDev)
        {
            m_comboSoundRecording.SetCurSel(i);
            break;
        }
    }
}

bool COptionsAudioDevicesDialog::IsModified()
{
    return m_bModified;

}


void COptionsAudioDevicesDialog::OnSelchangeComboMidiPlayback() 
{
	// TODO: Add your control notification handler code here
	SetModifiedFlag();
}

void COptionsAudioDevicesDialog::OnSelchangeComboSoundRecording() 
{
	// TODO: Add your control notification handler code here
	SetModifiedFlag();
}

void COptionsAudioDevicesDialog::SetModifiedFlag(bool bModified)
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

BOOL COptionsAudioDevicesDialog::OnInitDialog() 
{
	BaseForm::OnInitDialog();
	
    FillMidiPlaybackCombo();
    FillSoundRecordingCombo();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
