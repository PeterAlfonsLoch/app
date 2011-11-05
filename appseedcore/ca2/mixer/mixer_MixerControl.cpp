#include "StdAfx.h"
#include "MixerControl.h"
#include "MixerSource.h"
#include "MixerCallback.h"
#include "MixerCentral.h"

MixerControl::MixerControl(::ca::application * papp) :
   ca(papp)
{
    m_pmixersource = NULL;
    m_mixercontrol.cbStruct = sizeof(MIXERCONTROL);
    m_mixercontroldetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
    m_mixercontroldetails.paDetails = NULL;
}

MixerControl::MixerControl(MixerControl & control)
{
   operator =(control);
}

MixerControl::~MixerControl()
{
    if(m_mixercontroldetails.paDetails != NULL)
        free(m_mixercontroldetails.paDetails);
    mixer::control * pcontrol;
    for(int i = 0; i < this->get_size(); i++)
    {

        if((pcontrol = this->element_at(i)) != NULL)
        {
           delete pcontrol;
        }
    }
}

bool MixerControl::CreateWindows(::user::interaction * pParent, int iStyle)
{
   UNREFERENCED_PARAMETER(pParent);
   UNREFERENCED_PARAMETER(iStyle);
   return true;
}



bool MixerControl::CreateWindowsVolumeV001(
    ::user::interaction *pParent,
    UINT nStartID,
    UINT * nNextID)
{
   ASSERT(m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME);

   static char        szScrollBar[] = TEXT("scrollbar");
   static char        szTitle[]     = TEXT("Fader Class: '%s'");

   UINT                        cb;
   UINT                        lcChannels;
   UINT                        lcMultipleItems;
   int                         nRange;
   int                         nPageInc;


   ASSERT(m_pmixersource != NULL);

   lcChannels = (UINT)m_pmixersource->m_mixerline.cChannels;
   if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
      m_mixercontroldetails.cChannels = 1;

   lcMultipleItems = 1;
   if (MIXERCONTROL_CONTROLF_MULTIPLE & m_mixercontrol.fdwControl)
      lcMultipleItems = (UINT)m_mixercontrol.cMultipleItems;

   if(lcChannels > 2)
      return false;
   if(lcMultipleItems != 1)
      return false;

   cb = lcChannels * lcMultipleItems * sizeof(MIXERCONTROLDETAILS_UNSIGNED);
   m_mixercontroldetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
   if(m_mixercontroldetails.paDetails != NULL)
      free(m_mixercontroldetails.paDetails);
   m_mixercontroldetails.paDetails = malloc(cb);

   nRange = (int) min(32767, m_mixercontrol.Metrics.cSteps - 1);
   bool bOk = false;
   for(int i = 5; i <= 10; i++)
   {
      nPageInc = nRange / i;
      if(nPageInc < 1)
      {
         bOk = true;
         nPageInc = 1;
         break;
      }
      if(nRange % i == 0)
      {
         bOk = true;
         break;
      }
   }
   if(!bOk)
   {
      for(int i = 5; i <= 10; i++)
      {
         nPageInc = nRange / i;
         if(nRange % i > (nPageInc / 2))
         {
            bOk = true;
            break;
         }
      }
   }

   UINT nID = nStartID;
   UINT nVolumeID = nID++;
   UINT nVolumeLabelID = nID++;
   UINT nBalanceID = nID++;
   UINT nBalanceLabelID = nID++;

   rect rect(0, 0, 0, 0);

   mixer::LevelControl * plevelcontrol = m_pmixersource->GetDevice()->GetMixer()->GetCallback()->CreateLevelControl();
   if(plevelcontrol == NULL)
      return false;
   plevelcontrol->Initialize(pParent, nVolumeID);
   MixerCtrlDataVolume & mcdvVolume = plevelcontrol->get_data();
   mcdvVolume.m_iType = MixerCtrlData::TypeStereoVolume;
   mcdvVolume.m_uiMixerID = m_pmixersource->GetDevice()->m_uiMixerID;
   mcdvVolume.m_uiLineID = ((MIXERLINE *) m_pmixersource)->dwLineID;
   mcdvVolume.m_uiControlID = m_mixercontrol.dwControlID;
   mcdvVolume.nRange  = nRange;
   mcdvVolume.nPageInc = nPageInc;
   plevelcontrol->SetOrientation(mixer::LevelControl::orientation_vertical);
   plevelcontrol->SetRange(0, mcdvVolume.nRange);
   plevelcontrol->SetLineSize(1);
   plevelcontrol->SetPageSize(mcdvVolume.nPageInc);
   *plevelcontrol->m_pdata = mcdvVolume;
   add(plevelcontrol);


   string str;
   mixer::label * plabelVolume = m_pmixersource->GetDevice()->GetMixer()->GetCallback()->CreateLabel();
   if(plabelVolume == NULL)
      return false;
   plabelVolume->Initialize(pParent, nVolumeLabelID);
//xxx   str.load_string(IDS_MIXER_VOLUME);
   plabelVolume->SetText(str);
   MixerCtrlData & mcdVolumeLabel = plabelVolume->get_data();
   mcdVolumeLabel.m_iType = MixerCtrlData::TypeStereoVolumeLabel;
   mcdVolumeLabel.m_uiMixerID = m_pmixersource->GetDevice()->m_uiMixerID;
   mcdVolumeLabel.m_uiLineID = ((MIXERLINE *) m_pmixersource)->dwLineID;
   mcdVolumeLabel.m_uiControlID = m_mixercontrol.dwControlID;
   add(plabelVolume);


   if(lcChannels == 2)
   {
      mixer::LevelControl * pcontrol = m_pmixersource->GetDevice()->GetMixer()->GetCallback()->CreateLevelControl();
      if(pcontrol == NULL)
         return false;

      pcontrol->Initialize(pParent, nBalanceID);
      MixerCtrlDataVolume & mcdvBalance = pcontrol->get_data();
      mcdvBalance.m_iType = MixerCtrlData::TypeStereoBalance;
      mcdvBalance.m_uiMixerID = m_pmixersource->GetDevice()->m_uiMixerID;
      mcdvBalance.m_uiLineID = ((MIXERLINE *) m_pmixersource)->dwLineID;
      mcdvBalance.m_uiControlID = m_mixercontrol.dwControlID;
      mcdvBalance.nRange  = nRange;
      mcdvBalance.nPageInc = nPageInc;

      pcontrol->SetOrientation(mixer::LevelControl::orientation_horizontal);
      pcontrol->SetRange(0, mcdvBalance.nRange);
      pcontrol->SetLineSize(1);
      pcontrol->SetPageSize(mcdvBalance.nPageInc);

      add(pcontrol);

      mixer::label * plabel = m_pmixersource->GetDevice()->GetMixer()->GetCallback()->CreateLabel();
      if(plabel == NULL)
         return false;

      plabel->Initialize(pParent, nBalanceLabelID);
      MixerCtrlData & mcdBalanceLabel = plabel->get_data();
      mcdBalanceLabel.m_iType = MixerCtrlData::TypeStereoBalanceLabel;
      mcdBalanceLabel.m_uiMixerID = m_pmixersource->GetDevice()->m_uiMixerID;
      mcdBalanceLabel.m_uiLineID = ((MIXERLINE *) m_pmixersource)->dwLineID;
      mcdBalanceLabel.m_uiControlID = m_mixercontrol.dwControlID;
//xxx      str.load_string(IDS_MIXER_BALANCE);
      plabel->SetText(str);
      add(plabel);
   }

   *nNextID = nID;
   return true;
}

bool MixerControl::_001CreateMuteControl(
    ::user::interaction *pParent,
    UINT nStartID,
    UINT * nNextID)
{
    ASSERT((m_mixercontrol.dwControlType &  MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN);

    UINT                        cb;
    UINT                        lcChannels;
    UINT                        lcMultipleItems;


    ASSERT(m_pmixersource != NULL);

    lcChannels = (UINT)m_pmixersource->m_mixerline.cChannels;
    if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
        lcChannels = 1;

    lcMultipleItems = 1;
    if (MIXERCONTROL_CONTROLF_MULTIPLE & m_mixercontrol.fdwControl)
        lcMultipleItems = (UINT)m_mixercontrol.cMultipleItems;

    //if(lcChannels > 2)
      //  return false;
    //if(lcMultipleItems != 1)
      //  return false;

    int iItemCount = lcChannels * lcMultipleItems;

    cb = iItemCount * sizeof(MIXERCONTROLDETAILS_BOOLEAN);
    m_mixercontroldetails.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
    if(m_mixercontroldetails.paDetails != NULL)
        free(m_mixercontroldetails.paDetails);
    m_mixercontroldetails.paDetails = malloc(cb);

    UINT nID = nStartID;
    UINT nMuteID;



   string str;
   if(m_pmixersource == m_pmixersource->GetDestination())
   {
      str = System.load_string("mix::mute_all");
   }
   else
   {
      str = System.load_string("mix::mute");
   }
   for(int iItem = 0; iItem < iItemCount; iItem++)
   {
      nMuteID = nID++;
      mixer::toggle_control * pbtMute = m_pmixersource->GetDevice()->GetMixer()->GetCallback()->CreateToggleControl();
      pbtMute->Initialize(pParent, nMuteID);
      pbtMute->set_label(str);
      MixerCtrlDataSwitch & mcdmMute = pbtMute->get_data();
      mcdmMute.m_iType = MixerCtrlData::TypeUniformMute;
      mcdmMute.m_uiMixerID = m_pmixersource->GetDevice()->m_uiMixerID;
      mcdmMute.m_uiControlID = m_mixercontrol.dwControlID;
      mcdmMute.m_uiLineID = ((MIXERLINE *) m_pmixersource)->dwLineID;
      add(pbtMute);
   }

    *nNextID = nID;
    return true;
}

/*void MixerControl::OnArrayReallocation(void *pNewPointer)
{
   m_pmixersource = (MixerSource *) pNewPointer;
}
*/

void MixerControl::Prepare()
{
   m_mixercontroldetails.dwControlID = m_mixercontrol.dwControlID;
}

mixer::control * MixerControl::GetControl(
    int iType)
{
    mixer::control  * pWnd = NULL;
    for(int i = 0; i < this->get_size(); i++)
    {
        pWnd = this->element_at(i);
        if(pWnd == NULL)
            continue;
        if(pWnd->m_pdata->get_type() == iType)
        {
            return pWnd;
        }
    }
    return NULL;
}

mixer::control * MixerControl::GetControlByIndex(
    int iIndex)
{
   return this->element_at(iIndex);
}

void MixerControl::OnMixerControlChange()
{
    if(this->get_size() <= 0)
        return;
    MMRESULT                        mmrc;
//    HWND                            htxt;
//    PMACONTROLINSTANCE_FADER        pmaci_fader;
//    LPMACONTROLINSTANCE             pmaci;
//    LPMIXERLINE                     pmxl;
//    LPMIXERCONTROL                  pmxctrl;
    PMIXERCONTROLDETAILS_UNSIGNED   pmxcd_u;
    int                             nRange;
//    int                             nValue;
    UINT                            cChannels;
    UINT                            cMultipleItems;
//    UINT                            u;
//    UINT                            uIndex;
//    UINT                            v;
//    MIXERCONTROLDETAILS             mxcd;
 //   HWND                            hsbFocus;
//    HWND                            hsb;


//    hsbFocus = GetFocus();
//    if (NULL == hsbFocus)
//    {
//        hsbFocus = GetDlgItem(hwnd, IDD_MACONTROL_MULTICHANNEL_BASE);
//    }
//    else
//    {
//        uIndex = GetDlgCtrlId(hsbFocus);
//        if (uIndex < IDD_MACONTROL_MULTICHANNEL_BASE)
//        {
//            hsbFocus = GetDlgItem(hwnd, IDD_MACONTROL_MULTICHANNEL_BASE);
//        }
//    }


    //
    //
    //
//    pmaci_fader = (PMACONTROLINSTANCE_FADER)(UINT)GetWindowLong(hwnd, DWL_USER);
//    pmaci       = pmaci_fader->pmaci;
//    pmxl        = pmaci->pmxl;
//    pmxctrl     = pmaci->pmxctrl;
//    pmxcd_u     = &pmaci_fader->pmxcd_u[0];
//    nRange      = pmaci_fader->nRange;

   cChannels = (UINT)m_pmixersource->m_mixerline.cChannels;
   if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
      cChannels = 1;

   m_mixercontroldetails.cChannels = cChannels;


    //
    //
    //
//    m_mixercontroldetails.cChannels      = cChannels;
    m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;

    mmrc = mixerGetControlDetails(
       (HMIXEROBJ)m_pmixersource->GetDevice()->m_hMixer,
       &m_mixercontroldetails,
       MIXER_GETCONTROLDETAILSF_VALUE);
    if (MMSYSERR_NOERROR != mmrc)
    {
//        System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
  //                "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
    //              m_mixercontrol.dwControlID, m_pmixersource->GetDevice()->m_hMixer, mmrc);
        return;
    }


    cMultipleItems = 1;
    if (MIXERCONTROL_CONTROLF_MULTIPLE & m_mixercontrol.fdwControl)
        cMultipleItems = (UINT)m_mixercontrol.cMultipleItems;
    if(m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME)
    {
        ASSERT(cMultipleItems == 1);
        if(cChannels == 2)
        {
            mixer::LevelControl * pslVolume =
               (mixer::LevelControl *)
                  (GetControl(MixerCtrlData::TypeStereoVolume));
            MixerCtrlDataVolume * lpmcdVolume = (MixerCtrlDataVolume *) GetWindowData(MixerCtrlData::TypeStereoVolume);
            mixer::LevelControl * pslBalance =
               (mixer::LevelControl *)
                  (GetControl(MixerCtrlData::TypeStereoBalance));
            double dActualBalance = pslBalance->GetPos();

            nRange = lpmcdVolume->nRange;
            pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
            int nLeftValue = (int)MulDivRN(pmxcd_u[0].dwValue - m_mixercontrol.Bounds.dwMinimum, nRange, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum);
            int nRightValue = (int)MulDivRN(pmxcd_u[1].dwValue - m_mixercontrol.Bounds.dwMinimum, nRange, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum);


            int nMaxValue = max(nLeftValue, nRightValue);
            int nBalance = nMaxValue == 0 ?
                nRange / 2 :
                (nRange +
                    MulDivRN(nRightValue - nLeftValue, nRange, nMaxValue)) / 2;


            pslVolume->SetPos(nRange - nMaxValue);

            double dRangeSlack = nMaxValue == 0 ?
                nRange / 2 :
                ((double) nRange) / (2 * nMaxValue) + 0.5;
            if(dActualBalance > nBalance + dRangeSlack ||
                dActualBalance < nBalance - dRangeSlack)
            {
                pslBalance->SetPos(nBalance);
            }
            TRACE("Left %d Right %d nBalance %d\n", nLeftValue, nRightValue, nBalance);
        }
        else if(cChannels == 1)
        {
            mixer::LevelControl * pslVolume = (mixer::LevelControl *)
               (GetControl(MixerCtrlData::TypeStereoVolume));
            MixerCtrlDataVolume * lpmcdVolume = (MixerCtrlDataVolume *) GetWindowData(MixerCtrlData::TypeStereoVolume);

            nRange = lpmcdVolume->nRange;
            pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
            int nValue = (int)MulDivRN(pmxcd_u[0].dwValue - m_mixercontrol.Bounds.dwMinimum, nRange, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum);

            pslVolume->SetPos(nRange - nValue);
        }
    }
   else if((m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         mixer::toggle_control * pmutecontrol = (mixer::toggle_control *)
            GetControlByIndex(i);


         PMIXERCONTROLDETAILS_BOOLEAN pmxcd_f = (PMIXERCONTROLDETAILS_BOOLEAN) m_mixercontroldetails.paDetails;
         BOOL fValue = (BOOL) pmxcd_f[cMultipleItems - i - 1].fValue;

         pmutecontrol->_001SetCheck(fValue ? check::checked : check::unchecked);
      }
   }
}

MixerCtrlData * MixerControl::GetWindowData(int iType)
{
   mixer::control * pWnd = NULL;
   for(int i = 0; i < this->get_size(); i++)
   {
      pWnd = this->element_at(i);
      if(pWnd == NULL)
         continue;
      if(pWnd->m_pdata->get_type() == iType)
      {
         return pWnd->m_pdata;
      }
   }
   return NULL;
}

/*bool MixerControl::OnNotify(UINT nID, LPNMHDR lpnmhdr)
{
   UNREFERENCED_PARAMETER(nID);
    if(lpnmhdr->code == TB_BOTTOM ||
        lpnmhdr->code == TB_ENDTRACK ||
        lpnmhdr->code == TB_LINEDOWN ||
        lpnmhdr->code == TB_LINEUP ||
        lpnmhdr->code == TB_PAGEDOWN ||
        lpnmhdr->code == TB_PAGEUP ||
        lpnmhdr->code == TB_THUMBPOSITION ||
        lpnmhdr->code == TB_THUMBTRACK ||
        lpnmhdr->code == TB_TOP)
    {
       mixer::control * pcontrol = GetControlByDlgCtrlID(lpnmhdr->idFrom);
        if(pcontrol != NULL)
        {
//            mixer::LevelControl * plevelcontrol = (mixer::LevelControl *) pcontrol;
            /*if(base < CSliderCtrl >::bases(pWnd))
            {
                CSliderCtrl * pSlider = (CSliderCtrl *) pWnd;
                MixerCtrlData * pData;
                if(NULL != (pData = GetWindowDataByDlgCtrlID(lpnmhdr->idFrom)))
                {

                    if(pData->get_type() == MixerCtrlData::TypeStereoBalance ||
                        pData->get_type() == MixerCtrlData::TypeStereoVolume)
                    {
                        CSliderCtrl * pslBalance;
                        CSliderCtrl * pslVolume;
                        if(pData->get_type() == MixerCtrlData::TypeStereoBalance)
                        {
                            pslBalance = pSlider;
                            pslVolume = (CSliderCtrl *) GetControl(MixerCtrlData::TypeStereoVolume)->GetWnd();
                            ASSERT(pslVolume != NULL);
                        }
                        else if(pData->get_type() == MixerCtrlData::TypeStereoVolume)
                        {
                            pslVolume = pSlider;
                            pslBalance = (CSliderCtrl *) GetControl(MixerCtrlData::TypeStereoBalance)->GetWnd();
                            ASSERT(pslVolume != NULL);
                        }
                        m_mixercontroldetails.cChannels = (UINT)m_pmixersource->m_mixerline.cChannels;
                        if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
                            m_mixercontroldetails.cChannels = 1;

                        //
                        //
                        //
//                        m_mixercontroldetails.cChannels      = cChannels;
                        m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;
                        if(m_mixercontroldetails.cChannels == 2)
                        {
                            MixerCtrlDataVolume * lpmcdVolume = (MixerCtrlDataVolume *) GetWindowData(MixerCtrlData::TypeStereoVolume);
                            int nRange = lpmcdVolume->nRange;
                            int nBalance  = pslBalance->GetPos();
                            int nMaxValue = nRange - pslVolume->GetPos();
                            int nMinValue = nBalance * 2 * nMaxValue / nRange;
                            int nLeftValue;
                            int nRightValue;
                            if(nBalance == nRange / 2)
                            {
                                nLeftValue = nMaxValue;
                                nRightValue = nMaxValue;
                            }
                            else if(nBalance > nRange / 2)
                            {
                                nLeftValue = nMinValue;
                                nRightValue = nMaxValue;
                            }
                            else
                            {
                                nLeftValue = nMaxValue;
                                nRightValue = nMinValue;
                            }

                            PMIXERCONTROLDETAILS_UNSIGNED   pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
                            pmxcd_u[0].dwValue = (int)MulDivRN(
                                nLeftValue ,
                                m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
                                nRange) +  m_mixercontrol.Bounds.dwMinimum;
                            pmxcd_u[1].dwValue = (int)MulDivRN(
                                nRightValue ,
                                m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
                                nRange) +  m_mixercontrol.Bounds.dwMinimum;
                            MMRESULT mmrc = mixerSetControlDetails(
                               (HMIXEROBJ)m_pmixersource->GetDevice()->m_hMixer,
                               &m_mixercontroldetails,
                               MIXER_GETCONTROLDETAILSF_VALUE);
                            if (MMSYSERR_NOERROR == mmrc)
                            {
                                OnMixerControlChange();
                            }
                            else
                            {
//                                System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
  //                                        "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
    //                                      m_mixercontrol.dwControlID, m_pmixersource->GetDevice()->m_hMixer, mmrc);
                            }

                        }
                        else if(m_mixercontroldetails.cChannels == 1)
                        {
                            CSliderCtrl * pslVolume = (CSliderCtrl *) GetControl(MixerCtrlData::TypeStereoVolume)->GetWnd();
                            MixerCtrlDataVolume * lpmcdVolume = (MixerCtrlDataVolume *) GetWindowData(MixerCtrlData::TypeStereoVolume);
                            int nRange = lpmcdVolume->nRange;
                            int nValue = nRange - pslVolume->GetPos();
                            PMIXERCONTROLDETAILS_UNSIGNED pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
                            pmxcd_u[0].dwValue = (int)MulDivRN(nValue, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum, nRange) + m_mixercontrol.Bounds.dwMinimum;
                            MMRESULT mmrc = mixerSetControlDetails(
                               (HMIXEROBJ)m_pmixersource->GetDevice()->m_hMixer,
                               &m_mixercontroldetails,
                               MIXER_GETCONTROLDETAILSF_VALUE);
                            if (MMSYSERR_NOERROR == mmrc)
                            {
                                OnMixerControlChange();
                            }
                            else
                            {
//                                System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
  ///                                        "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
     //                                     m_mixercontrol.dwControlID, m_pmixersource->GetDevice()->m_hMixer, mmrc);
                            }
                        }
                        return true;
                    }
                }*/

//            }
        /*}

    }
    return false;

}*/

mixer::control * MixerControl::GetControlByDlgCtrlID(UINT nID)
{
    mixer::control * pWnd = NULL;
    for(int i = 0; i < this->get_size(); i++)
    {
        pWnd = this->element_at(i);
        if(pWnd == NULL)
            continue;
        if((UINT) pWnd->_GetDlgCtrlID() == nID)
        {
            return pWnd;
        }
    }
    return NULL;

}

MixerCtrlData * MixerControl::GetWindowDataByDlgCtrlID(UINT nID)
{
   mixer::control * pWnd = NULL;
   for(int i = 0; i < this->get_size(); i++)
   {
      pWnd = this->element_at(i);
      if(pWnd == NULL)
         continue;
      if((UINT) pWnd->GetWnd()->GetDlgCtrlId() == nID)
      {
         return pWnd->m_pdata;
      }
   }
   return NULL;
}

void MixerControl::OnVHScroll(UINT nSBCode, UINT nPos, ::user::interaction * pScrollBar)
{
   UNREFERENCED_PARAMETER(nPos);
   ::user::interaction * pParamWnd = pScrollBar;
   if(nSBCode == SB_LEFT ||
      nSBCode == SB_ENDSCROLL ||
      nSBCode == SB_LINELEFT ||
      nSBCode == SB_LINERIGHT ||
      nSBCode == SB_PAGELEFT ||
      nSBCode == SB_PAGERIGHT ||
      nSBCode == SB_THUMBPOSITION ||
      nSBCode == SB_THUMBTRACK ||
      nSBCode == SB_RIGHT ||
      nSBCode == SB_BOTTOM ||
      nSBCode == SB_ENDSCROLL ||
      nSBCode == SB_LINEUP ||
      nSBCode == SB_LINEDOWN ||
      nSBCode == SB_PAGEUP ||
      nSBCode == SB_PAGEDOWN ||
      nSBCode == SB_TOP )
   {
      mixer::control * pcontrol = GetControlByDlgCtrlID(pParamWnd->GetDlgCtrlId());
      if(pcontrol != NULL)
      {
         mixer::LevelControl * pSlider = dynamic_cast<mixer::LevelControl*>(pcontrol);
         if(NULL != pSlider)
         {
            //mix::SliderInterface * pSlider = dynamic_cast < mixer::LevelControl * > ( pWnd);
            MixerCtrlData * pData;
            if(NULL != (pData = GetWindowDataByDlgCtrlID(pParamWnd->GetDlgCtrlId())))
            {

               if(pData->get_type() == MixerCtrlData::TypeStereoBalance ||
                  pData->get_type() == MixerCtrlData::TypeStereoVolume)
               {
                  mixer::LevelControl * pslBalance;
                  mixer::LevelControl * pslVolume;
                  if(pData->get_type() == MixerCtrlData::TypeStereoBalance)
                  {
                     pslBalance = pSlider;
                     pslVolume = dynamic_cast < mixer::LevelControl * >
                        (GetControl(MixerCtrlData::TypeStereoVolume));
                     ASSERT(pslVolume != NULL);
                  }
                  else if(pData->get_type() == MixerCtrlData::TypeStereoVolume)
                  {
                     pslVolume = pSlider;
                     pslBalance = dynamic_cast < mixer::LevelControl * >
                        ( GetControl(MixerCtrlData::TypeStereoBalance));
                     ASSERT(pslVolume != NULL);
                  }
                  m_mixercontroldetails.cChannels = (UINT)m_pmixersource->m_mixerline.cChannels;
                  if (MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
                     m_mixercontroldetails.cChannels = 1;

                  //
                  //
                  //
                  //m_mixercontroldetails.cChannels      = cChannels;
                  m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;
                  if(m_mixercontroldetails.cChannels == 2)
                  {
                     MixerCtrlDataVolume * lpmcdVolume = (MixerCtrlDataVolume *) GetWindowData(MixerCtrlData::TypeStereoVolume);
                     int nRange = lpmcdVolume->nRange;
                     int nBalance  = pslBalance->GetPos();
                     int nMaxValue = nRange - pslVolume->GetPos();
                     int nLeftValue;
                     int nRightValue;
                     if(nBalance == nRange / 2)
                     {
                        nLeftValue = nMaxValue;
                        nRightValue = nMaxValue;
                     }
                     else if(nBalance > nRange / 2)
                     {
                        nLeftValue =  2 * nMaxValue - MulDivRN(nBalance, 2 * nMaxValue, nRange);
                        nRightValue = nMaxValue;
                     }
                     else
                     {
                        nLeftValue = nMaxValue;
                        nRightValue = MulDivRN(nBalance, 2 * nMaxValue, nRange);
                     }

                     PMIXERCONTROLDETAILS_UNSIGNED   pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
                     pmxcd_u[0].dwValue = (int)MulDivRN(
                        nLeftValue ,
                        m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
                        nRange) +  m_mixercontrol.Bounds.dwMinimum;
                     pmxcd_u[1].dwValue = (int)MulDivRN(
                        nRightValue ,
                        m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum,
                        nRange) +  m_mixercontrol.Bounds.dwMinimum;
                     MMRESULT mmrc = mixerSetControlDetails(
                        (HMIXEROBJ)m_pmixersource->GetDevice()->m_hMixer,
                        &m_mixercontroldetails,
                        MIXER_GETCONTROLDETAILSF_VALUE);
                     if (MMSYSERR_NOERROR == mmrc)
                     {
                        OnMixerControlChange();
                     }
                     else
                     {
                        //                                System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
                        //                                        "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                        //                                      m_mixercontrol.dwControlID, m_pmixersource->GetDevice()->m_hMixer, mmrc);
                     }

                  }
                  else if(m_mixercontroldetails.cChannels == 1)
                  {
                     //CSliderCtrl * pslVolume = (CSliderCtrl *) GetWindow(MixerCtrlData::TypeStereoVolume);
                     MixerCtrlDataVolume * lpmcdVolume = (MixerCtrlDataVolume *) GetWindowData(MixerCtrlData::TypeStereoVolume);
                     int nRange = lpmcdVolume->nRange;
                     int nValue = nRange - pslVolume->GetPos();
                     PMIXERCONTROLDETAILS_UNSIGNED pmxcd_u = (PMIXERCONTROLDETAILS_UNSIGNED) m_mixercontroldetails.paDetails;
                     pmxcd_u[0].dwValue = (int)MulDivRN(nValue, m_mixercontrol.Bounds.dwMaximum - m_mixercontrol.Bounds.dwMinimum, nRange) + m_mixercontrol.Bounds.dwMinimum;
                     MMRESULT mmrc = mixerSetControlDetails(
                        (HMIXEROBJ)m_pmixersource->GetDevice()->m_hMixer,
                        &m_mixercontroldetails,
                        MIXER_GETCONTROLDETAILSF_VALUE);
                     if (MMSYSERR_NOERROR == mmrc)
                     {
                        OnMixerControlChange();
                     }
                     else
                     {
                        System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
                           "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                           m_mixercontrol.dwControlID, m_pmixersource->GetDevice()->m_hMixer, mmrc);
                     }
                  }
                  return ;
               }
            }

         }
      }

   }
   return;
}

BOOL MixerControl::OnCommand(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   WORD wNotifyCode = HIWORD(wParam);
   WORD wID = LOWORD(wParam);

   mixer::control * pwnd = GetControlByDlgCtrlID((UINT)wID);

   mixer::toggle_control * pmutecontrol =
      dynamic_cast < mixer::toggle_control  * >
         (pwnd);

   if(pmutecontrol != NULL)
   {
      MixerCtrlData * pData;
      if(NULL != (pData = GetWindowDataByDlgCtrlID((UINT) wID)))
      {
         if(pData->get_type() == MixerCtrlData::TypeUniformMute)
         {
            if(wNotifyCode == BN_CLICKED)
            {
               m_mixercontroldetails.cChannels = (UINT)m_pmixersource->m_mixerline.cChannels;
               if(MIXERCONTROL_CONTROLF_UNIFORM & m_mixercontrol.fdwControl)
                  m_mixercontroldetails.cChannels = 1;


               int iSel = pmutecontrol->get_data().m_iIndex;

               //m_mixercontroldetails.cChannels      = cChannels;
               m_mixercontroldetails.cMultipleItems = m_mixercontrol.cMultipleItems;
               int cMultipleItems = m_mixercontrol.cMultipleItems;
               PMIXERCONTROLDETAILS_BOOLEAN   pmxcd_f = (PMIXERCONTROLDETAILS_BOOLEAN) m_mixercontroldetails.paDetails;
               for(int i = 0; i < this->get_size(); i++)
               {
                  BOOL fValue = i == iSel ? 1 : 0;
                  pmxcd_f[cMultipleItems - i - 1].fValue = fValue;
               }
               MMRESULT mmrc = mixerSetControlDetails(
                  (HMIXEROBJ)m_pmixersource->GetDevice()->m_hMixer,
                  &m_mixercontroldetails,
                  MIXER_GETCONTROLDETAILSF_VALUE);
               if(MMSYSERR_NOERROR == mmrc)
               {
                  OnMixerControlChange();
               }
               else
               {
                  System.simple_message_box(NULL, MB_OK | MB_ICONEXCLAMATION,
                     "mixerGetControlDetails(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                     m_mixercontrol.dwControlID, m_pmixersource->GetDevice()->m_hMixer, mmrc);
               }
               return TRUE;
            }
         }
      }
   }
   return FALSE;
}

MixerControl & MixerControl::operator =(const MixerControl & control)
{
   m_pmixersource = control.m_pmixersource ;
   return *this;
}

DWORD MixerControl::GetControlType() const
{
   return m_mixercontrol.dwControlType;
}

INT_PTR MixerControl::add(mixer::control * pcontrol)
{
   pcontrol->m_pdata->m_iIndex = this->get_size();
   return ControlArray::add(pcontrol);
}


MIXERCONTROL & MixerControl::GetMixerControl()
{
   return m_mixercontrol;
}

MIXERCONTROLDETAILS & MixerControl::GetMixerControlDetails()
{
   return m_mixercontroldetails;
}


MixerControlArray::MixerControlArray(::ca::application * papp) :
   ::array_app_alloc < MixerControl, MixerControl & >(papp)
{
}


