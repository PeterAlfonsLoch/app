#include "StdAfx.h"
#include "MixerControlData.h"
#include "MixerControlView.h"
#include "slider.h"
#include "mute_control.h"
#include "label.h"

MixerControlData::MixerControlData(MixerControlView * pview) :
   ::ca::ca(pview->get_app())
{
   m_pview = pview;
   m_pdestination = NULL;
   m_pmixer = NULL;
}

MixerControlData::~MixerControlData(void)
{
   if(m_pmixer != NULL)
   {
        delete m_pmixer;
      m_pmixer = NULL;
   }

}

bool MixerControlData::Initialize(void)
{
   if(m_pmixer == NULL)
   {
      m_pmixer = new Mixer(get_app());
   }

   if(m_pmixer == NULL)
      return false;

   m_pmixer->SetCallback(this);

   //if(MMSYSERR_NOERROR != SetNewDevice(0))
     // return false;

   //SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
   return true;
}

MMRESULT MixerControlData::SetNewDevice(UINT uiMixerID)
{
   MMRESULT mmrc;
   Mixer * pmixer = GetMixer();
   if(MMSYSERR_NOERROR != (mmrc = pmixer->SetNewDevice(
      uiMixerID)))
   {
      System.simple_message_box(NULL, "Could not open mixer device!");
      return mmrc;
   }
   m_pdestination = NULL;
   m_pmixer->m_pdevice->GetCaps();
   return mmrc;
}


MMRESULT MixerControlData::SetNewDestination(DWORD dwComponentType)
{
   MMRESULT mmrc;
   if(m_pdestination != NULL)
   {
      mmrc = SetNewDevice(m_pmixer->m_pdevice->m_uiMixerID);
      // Reset All Contents
      if(mmrc != MMSYSERR_NOERROR)
      {
         return mmrc;
      }
      m_pdestination = NULL;
   }

   mmrc =  m_pmixer->m_pdevice->GetDestination(
      dwComponentType,
      &m_pdestination);
   if(mmrc != MMSYSERR_NOERROR)
   {
      return mmrc;
   }

   m_pdestination->GetSourcesInfo();

   m_pview->_OnUpdate(NULL, 17, NULL);

   return mmrc;
}


mixer::LevelControl * MixerControlData::CreateLevelControl(void)
{
   mixer::LevelControl * pcontrol = new mixeruserbase::slider(get_app());

   return pcontrol;
}

mixer::toggle_control * MixerControlData::CreateToggleControl(void)
{
   mixer::toggle_control * pcontrol = new mixeruserbase::mute_control(get_app());
/*   if(!pcontrol->GetWnd()->create(
      WS_EX_TRANSPARENT,
      NULL,
      NULL,
      WS_CHILD | WS_VISIBLE ,
      rect,
      pParent,
      nBalanceID))
   {
      delete pcontrol;
      return NULL;
   }*/

   return pcontrol;
}

mixer::label * MixerControlData::CreateLabel(void)
{
   mixer::label * pcontrol = new mixeruserbase::label(get_app());
   /*if(!pcontrol->GetWnd()->CreateEx(
      WS_EX_TRANSPARENT,
      NULL,
      NULL,
      WS_CHILD | WS_VISIBLE ,
      rect,
      pParent,
      nBalanceID))
   {
      delete pcontrol;
      return NULL;
   }*/

   return pcontrol;
}


Mixer * MixerControlData::GetMixer()
{
   return m_pmixer;
}

MixerDestination * MixerControlData::GetDestination()
{
   return m_pdestination;
}


