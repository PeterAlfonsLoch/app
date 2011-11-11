#include "StdAfx.h"

MixerDevice::MixerDevice(Mixer * pmixer)
{
   m_mixerdestinationa.set_app(pmixer->get_app());
   m_pmixer = pmixer;
   m_hMixer = NULL;
}

MixerDevice::~MixerDevice()
{
   if(m_hMixer != NULL)
   {
      mixerClose(m_hMixer);
      m_hMixer = NULL;
   }

}

MMRESULT MixerDevice::open(UINT uiMixerId, DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen)
{
   MMRESULT            mmrc;
    HMIXER              hmx;
    MIXERCAPS           mxcaps;


    //
    //
    //
    mmrc = mixerGetDevCaps(uiMixerId, &mxcaps, sizeof(mxcaps));
    if (MMSYSERR_NOERROR != mmrc)
    {
        System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
                "mixerGetDevCaps() failed on uMxId=%u, mmr=%u!",
                uiMixerId, mmrc);
        return mmrc;
    }


    //
    //
    //
    mmrc = mixerOpen(&hmx, uiMixerId, dwCallback, dwInstance, fdwOpen);
    if (MMSYSERR_NOERROR != mmrc)
    {
        System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
                "mixerOpen() failed on uMxId=%u, mmr=%u!",
                uiMixerId, mmrc);
        return mmrc;
    }


    if (NULL != m_hMixer)
    {
        MMRESULT mmrct = close();
        if (MMSYSERR_NOERROR != mmrct)
        {
            System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
                      "mixerClose() failed on hmx=%.04Xh, mmr=%u!",
                      m_hMixer, mmrct);
        }
    }
   m_hMixer = hmx;
    m_uiMixerID = uiMixerId;
//    AppSetWindowText(hwnd, "Mixer Device: %s", (char *)mxcaps.szPname);
   return mmrc;

}

MMRESULT MixerDevice::GetCaps()
{
   MMRESULT mmrc;
   
   mmrc = mixerGetDevCaps(
      (UINT) m_hMixer, 
      &m_mixercaps,
      sizeof(MIXERCAPS));
   if (MMSYSERR_NOERROR != mmrc)
   {
      System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
         "mixerGetDevCaps() failed on uMxId=%u, mmr=%u!",
         m_uiMixerID, mmrc);
      return mmrc;
   }
   return mmrc;
}

MMRESULT MixerDevice::GetDestinations()
{
   MixerDestination *    lpDestination;
  
   m_mixerdestinationa.set_size(m_mixercaps.cDestinations);
   
   for (int i = 0; (UINT) i < m_mixercaps.cDestinations; i++)
   {
      lpDestination = m_mixerdestinationa.ptr_at(i);
      lpDestination->SetDevice(this);
      lpDestination->mixerGetLineInfo(0, i, MIXER_GETLINEINFOF_DESTINATION);
      //        CMixer::GetComponentName(lpmxl, lpDestination->m_strComponent);
      
      //        //
      //      //
      //    //
      //  wsprintf(ach, gszLineFormatList,
      //         (char *)szLineTypeDst,
      //       (MIXERLINE_LINEF_ACTIVE & mxl.fdwLine) ? '*' : ' ',
      //     (LPTSTR)szComponent,
      //   mxl.dwLineID,
      //   mxl.fdwLine,
      // mxl.cControls,
      // mxl.cConnections,
      //(char *)mxl.szName);
      
      //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
      //      {
      //        MixAppDebugLog(ach);
      //      MixAppDebugLog(gszCRLF);
      //  }
      
      //        nIndex = ListBox_AddString(ptlb->hlb, ach);
      //      ListBox_SetItemData(ptlb->hlb, nIndex, mxl.dwLineID);
      
   }
   
   
   //
   //
   //
   //    SetWindowRedraw(ptlb->hlb, TRUE);
   return MMSYSERR_NOERROR;
   
}

MMRESULT MixerDevice::GetDestination(DWORD dwComponentType, MixerDestination **ppDestination)
{
   if(m_mixerdestinationa.get_size() <= 0)
      GetDestinations();
   if(m_mixerdestinationa.get_size() <= 0)
      return MMSYSERR_ERROR;
   for(int i = 0; i < m_mixerdestinationa.get_size(); i++)
   {
      DWORD dw = m_mixerdestinationa[i].m_mixerline.dwComponentType;
      if(dw == dwComponentType)
      {
         *ppDestination = m_mixerdestinationa.ptr_at(i);
         return MMSYSERR_NOERROR;
      }
   }
   return MMSYSERR_ERROR;
}

void MixerDevice::MapControls()
{
   m_mapIDToControl.remove_all();
   
   for(int i = 0; i < m_mixerdestinationa.get_size(); i++)
   {
      MixerDestination & destination = m_mixerdestinationa[i];
      MapLineControls(&destination);
      MixerSourceArray & sourcea = destination.GetSources();
      for(int j = 0; j < sourcea.get_size(); j++)
      {
         MixerSource & source = sourcea[j];
         MapLineControls(&source);
      }
   }
}

void MixerDevice::MapLines()
{
   m_mapIDToLine.remove_all();
   for(int i = 0; i < m_mixerdestinationa.get_size(); i++)
   {
      MixerDestination & destination = m_mixerdestinationa[i];
      m_mapIDToLine.set_at(
         destination.GetMixerLine().dwLineID,
         &destination);
      MixerSourceArray & sourcea = destination.GetSources();
      for(int j = 0; j < sourcea.get_size(); j++)
      {
         MixerSource & source = sourcea[j];
         m_mapIDToLine.set_at(source.GetMixerLine().dwLineID, &source);
      }
   }
}

void MixerDevice::OnMixerLineChange(DWORD dwLineID)
{
   MixerSource * pSource;
   if(m_mapIDToLine.Lookup(dwLineID, pSource))
   {
      pSource->OnMixerLineChange();
   }
}

void MixerDevice::OnMixerControlChange(DWORD dwControlID)
{
   MixerControl * pControl;
   if(m_mapIDToControl.Lookup(dwControlID, pControl))
   {
      pControl->OnMixerControlChange();
   }
}

void MixerDevice::MapLineControls(MixerSource * psource)
{
   MixerControlArray & controla = psource->_GetControls();
   for(int k = 0; k < controla.get_size(); k++)
   {
      MixerControl & control = controla[k];
      m_mapIDToControl.set_at(control.GetMixerControl().dwControlID, &control);
      for(int l = 0; l < control.get_size(); l++)
      {
         mixer::control * pcontrol = control[l];
         m_mapDlgItemIDToControl.set_at(pcontrol->_GetDlgCtrlID(), &control);
      }
   }
}

void MixerDevice::MapDlgCtrlIDToControls()
{
   m_mapDlgItemIDToControl.remove_all();

   MixerDestinationArray & destinationa = m_mixerdestinationa;
   for(int i = 0; i < destinationa.get_size(); i++)
   {
      MixerDestination & destination = destinationa[i];
      MapDlgCtrlIDToLineControls(&destination);
      MixerSourceArray & sourcea = destination.GetSources();
      for(int j = 0; j < sourcea.get_size(); j++)
      {
         MixerSource & source = sourcea[j];
         MapDlgCtrlIDToLineControls(&source);
      }
   }

}

void MixerDevice::MapDlgCtrlIDToLineControls(MixerSource * psource)
{
   MixerControlArray & controla = psource->_GetControls();
   for(int k = 0; k < controla.get_size(); k++)
   {
      MixerControl & control = controla[k];
      for(int l = 0; l < control.get_size(); l++)
      {
         mixer::control * pcontrol = control[l];
         m_mapDlgItemIDToControl.set_at(pcontrol->_GetDlgCtrlID(), &control);
      }
   }
}

MMRESULT MixerDevice::close()
{
    MMRESULT mmrc;
    if(m_hMixer != NULL)
    {
        mmrc = mixerClose(m_hMixer);
        m_mixerdestinationa.remove_all();
        m_mapIDToControl.remove_all();
        m_mapDlgItemIDToControl.remove_all();
        m_mapIDToLine.remove_all();

    }
    return mmrc;
}

bool MixerDevice::OnCommand(WPARAM wparam, LPARAM lparam)
{
   UINT uiID = LOWORD(wparam);
   
   MixerControl * pcontrol;
   
   if(m_mapDlgItemIDToControl.Lookup(uiID, pcontrol)
      && pcontrol->OnCommand(wparam, lparam))
            return TRUE;
   return FALSE;
}

const char * MixerDevice::GetSZPName()
{
   return m_mixercaps.szPname;
}


Mixer * MixerDevice::GetMixer()
{
   return m_pmixer;
}