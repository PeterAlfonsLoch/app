#include "StdAfx.h"
#include "MixerSource.h"

MixerSource::MixerSource(::ca::application * papp) :
   ca(papp),
   m_mixercontrola(papp)
{
   m_mixercontrola.set_app(papp);
   m_pdestination = NULL;
   m_mixerlinecontrols.pamxctrl = NULL;
}

MixerSource::MixerSource(MixerSource & source) :
   ::ca::ca(source.get_app()),
   m_mixercontrola(source.get_app())
{
    operator =(source);
}

MixerSource::~MixerSource()
{

}

MMRESULT MixerSource::GetLineControls()
{
   MMRESULT mmrc;
   m_bHasV001Controls = false;
   int iControlCount = m_mixerline.cControls;
   if (0 == iControlCount)
   {
      //        System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
      //"There are no controls associated with the selected line.");
      //        EndDialog(hwnd, FALSE);
      return MMSYSERR_NOERROR;
   }
   
   m_mixercontrola.set_size(iControlCount);
   
   if(m_mixerlinecontrols.pamxctrl != NULL)
      delete[] (MIXERCONTROL *) m_mixerlinecontrols.pamxctrl;
   m_mixerlinecontrols.cbStruct       = sizeof(MIXERLINECONTROLS);
   m_mixerlinecontrols.dwLineID       = m_mixerline.dwLineID;
   ////////////mxlc.dwControlID    = 0;
   ////////////mxlc.dwControlType  = 0;
   m_mixerlinecontrols.cControls      = iControlCount;
   m_mixerlinecontrols.cbmxctrl       = sizeof(*m_mixerlinecontrols.pamxctrl);
   m_mixerlinecontrols.pamxctrl       = new MIXERCONTROL[m_mixerline.cControls];

   for (int i = 0; i < iControlCount; i++)
   {
      m_mixerlinecontrols.pamxctrl[i].cbStruct = sizeof(MIXERCONTROL);
   }
   
   mmrc = mixerGetLineControls(
      (HMIXEROBJ)GetDevice()->m_hMixer, 
      &m_mixerlinecontrols,
      MIXER_GETLINECONTROLSF_ALL);
   if (MMSYSERR_NOERROR != mmrc)
   {
      System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
         "mixerGetLineControls(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
         m_mixerline.dwLineID, GetDevice()->m_hMixer, mmrc);
   }
   else
   {
      //        char       ach[128];
      //      char       szControlType[64];
      //        UINT        u;
      //    int         nIndex;
      PMIXERCONTROL       pamxctrl;
      //        LPMIXERCONTROLDETAILS lpmcd;
      MixerControl *     lpMixerControl;
      
      //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
      //          MixAppDebugLog(NULL);
      
      for (int i = 0; (UINT) i < m_mixerlinecontrols.cControls; i++)
      {
         lpMixerControl = m_mixercontrola.ptr_at(i);
         lpMixerControl->m_pmixersource = this;
         pamxctrl = &lpMixerControl->GetMixerControl();
         //m_mixerlinecontrols.pamxctrl = pamxctrl;
         //*m_mixerlinecontrols.pamxctrl = m_mixerlinecontrols.pamxctrl[i];
         *pamxctrl = m_mixerlinecontrols.pamxctrl[i];
         lpMixerControl->Prepare();
         //            CMixer::GetControlTypeName(pamxctrl, lpMixerControl->m_strTypeName);
         
         switch (pamxctrl->dwControlType)
         {
            //            case MIXERCONTROL_CONTROLTYPE_FADER:
         case MIXERCONTROL_CONTROLTYPE_VOLUME:
            //          case MIXERCONTROL_CONTROLTYPE_BASS:
            //        case MIXERCONTROL_CONTROLTYPE_TREBLE:
            //      case MIXERCONTROL_CONTROLTYPE_EQUALIZER:
            
            //    case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
            //  case MIXERCONTROL_CONTROLTYPE_ONOFF:
         case MIXERCONTROL_CONTROLTYPE_MUTE:
            //            case MIXERCONTROL_CONTROLTYPE_MONO:
            //          case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
            //        case MIXERCONTROL_CONTROLTYPE_STEREOENH:
            m_bHasV001Controls = true;
            break;
            
         default:;
         }
         //
         //
         //
         //            wsprintf(ach, gszLineControlsFormatList,
         //                  u,
         //                (LPTSTR)szControlType,
         //              pamxctrl[u].dwControlID,
         //            pamxctrl[u].fdwControl,
         //          pamxctrl[u].cMultipleItems,
         //        (char *)pamxctrl[u].szName);
         
         //            if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
         //          {
         //            MixAppDebugLog(ach);
         //          MixAppDebugLog(gszCRLF);
         //    }
         
         //            nIndex = ListBox_AddString(ptlb->hlb, ach);
         //          ListBox_SetItemData(ptlb->hlb, nIndex, pamxctrl[u].dwControlID);
      }
      
      //    ListBox_SetCurSel(ptlb->hlb, 0);
      //  EnableWindow(GetDlgItem(hwnd, IDD_LINECONTROLS_BTN_INFO), TRUE);
      //EnableWindow(GetDlgItem(hwnd, IDD_LINECONTROLS_BTN_SETTINGS), TRUE);
   }
   
   //    SetWindowRedraw(ptlb->hlb, TRUE);
   //  LocalFree((HLOCAL)pamxctrl);
   return mmrc;
   
}

/*MMRESULT MixerSource::GetControl(DWORD dwControlType, DWORD dwControlFlags,  MixerControl ** ppControl)
{
   MixerControlArray & controla = m_mixercontrola;
   if(controla.get_size() <= 0)
      GetLineControls();
   if(controla.get_size() <= 0)
      return MMSYSERR_ERROR;
   for(int i = 0; i < controla.get_size(); i++)
   {
      if((dwControlType != 0 && controla[i].GetControlType() == dwControlType)
         || (dwControlType == 0 && ((controla[i].GetControlType() & dwControlFlags) != 0)))
      {
         *ppControl = controla.ptr_at(i);
         return MMSYSERR_NOERROR;
      }
   }
   return MMSYSERR_ERROR;
}*/

/*void MixerSource::OnArrayReallocation(void *pNewPointer)
{
   m_pmixerdestination = (MixerDestination *) pNewPointer;
}*/

void MixerSource::OnMixerLineChange()
{

}



void MixerSource::SendOnChangeAllControls()
{
   MixerControlArray & controla = _GetControls();
   for(int i = 0; i < controla.get_size(); i++)
   {
      controla[i].OnMixerControlChange();
   }
}

MixerSource & MixerSource::operator = (const MixerSource & source)
{
   m_bHasV001Controls = source.m_bHasV001Controls;
   m_pdestination = source.m_pdestination;
   return *this;
}

const char * MixerSource::GetSZName()
{
   return m_mixerline.szName;
}

DWORD MixerSource::GetLineID()
{
   return m_mixerline.dwLineID;
}


MixerDevice * MixerSource::GetDevice()
{
   return m_pdestination->GetDevice();
}

void MixerSource::SetDestination(MixerDestination * pdestination)
{
   m_pdestination = pdestination;
}

MMRESULT MixerSource::mixerGetLineInfo(DWORD dwSource, DWORD dwDestination, DWORD fdwInfo)
{
   m_mixerline.cbStruct       = sizeof(MIXERLINE);
   m_mixerline.dwDestination  = dwDestination;
   m_mixerline.dwSource       = dwSource;
      
   MMRESULT mmrc = ::mixerGetLineInfo(
                     (HMIXEROBJ)GetDevice()->m_hMixer, 
                     &m_mixerline, 
                     fdwInfo);
   if (MMSYSERR_NOERROR != mmrc)
   {
      System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
         "mixerGetLineInfo(src=%u) failed on hmx=%.04Xh, mmr=%u!",
         dwSource, GetDevice()->m_hMixer, mmrc);
   }
   return mmrc;
}

MMRESULT MixerSource::mixerGetLineInfo(DWORD dwSource, MixerDestination * pdestination)
{
   MMRESULT mmrc = mixerGetLineInfo(dwSource, pdestination->m_mixerline.dwDestination, MIXER_GETLINEINFOF_SOURCE);
   SetDestination(pdestination);
   return mmrc;
}

MixerDestination * MixerSource::GetDestination()
{
   return m_pdestination;
}

bool MixerSource::HasV001Controls()
{
   return m_bHasV001Controls;
}

MixerControlArray & MixerSource::_GetControls()
{
   return m_mixercontrola;
}

MIXERLINE & MixerSource::GetMixerLine()
{
   return m_mixerline;
}

MIXERLINECONTROLS & MixerSource::GetMixerLineControls()
{
   return m_mixerlinecontrols;
}
