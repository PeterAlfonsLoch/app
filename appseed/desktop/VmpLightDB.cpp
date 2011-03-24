// VmpLightDB.cpp: implementation of the CVmpLightDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VmpLightDB.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MusicalPlayerLightDB::MusicalPlayerLightDB()
{

}

MusicalPlayerLightDB::~MusicalPlayerLightDB()
{

}

bool MusicalPlayerLightDB::OnSetData(
   const VmsDataKeyInterface & key, 
   int iLine, 
   int iColumn, 
   gen::BaseSerializable & serializable,
   VmsDataUpdateHint * puh)
{
   return VmsDataServerInterface::OnSetData(
      key,
      iLine,
      iColumn,
      serializable,
      puh);
}

bool MusicalPlayerLightDB::OnSetData(
   const VmsDataKeyInterface & key, 
   int iLine, 
   int iColumn, 
   gen::Variable & var, VmsDataUpdateHint * puh)
{
   return VmsDataServerInterface::OnSetData(
      key,
      iLine,
      iColumn,
      var,
      puh);
}     

bool MusicalPlayerLightDB::GetData(
   const VmsDataKeyInterface & key, 
   int iLine, 
   int iColumn, 
   gen::BaseSerializable & serializable)
{
   return VmsDataServerInterface::GetData(
      key,
      iLine,
      iColumn,
      serializable);
}

bool MusicalPlayerLightDB::GetData(
   const VmsDataKeyInterface & key, 
   int iLine, 
   int iColumn, 
   gen::Variable & var)
{
   if(key == VMSDATAKEY(WaveInDevices))
   {
      ASSERT(var.GetType() == gen::VariableUnknown);
      if(var.GetType() == gen::VariableUnknown)
      {
//         Ex1FormInterfaceComboBox * pcombo =
  //          dynamic_cast < Ex1FormInterfaceComboBox * >
    //           (var.m_pUnknown);
         Ex1FormInterfaceComboBox * pcombo =
            ( Ex1FormInterfaceComboBox * )
               (var.m_pUnknown);
         if(pcombo != NULL)
         {
            UINT uiDevs = waveInGetNumDevs();
            WAVEINCAPS moc;
      
            WString wstr;
            wstr.LoadString(IDS_WAVEMAPPER);
            pcombo->m_wstra.Add(wstr);
            pcombo->m_dwaData.Add(WAVE_MAPPER);

   
            MMRESULT mmrc;
            for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
            {
               if(MMSYSERR_NOERROR == (mmrc = waveInGetDevCaps(uiDev, &moc, sizeof(moc))))
               {
                  International::ACPToUnicode(wstr, moc.szPname);
                  pcombo->m_wstra.Add(wstr);
                  pcombo->m_dwaData.Add(uiDev);
               }
            }
            return true;
         }
      }
	}
   else if(key == VMSDATAKEY(MidiOutDevices))
   {
      ASSERT(var.GetType() == gen::VariableUnknown);
      if(var.GetType() == gen::VariableUnknown)
      {
//         Ex1FormInterfaceComboBox * pcombo =
  //          dynamic_cast < Ex1FormInterfaceComboBox * >
    //           (var.m_pUnknown);
         Ex1FormInterfaceComboBox * pcombo =
            ( Ex1FormInterfaceComboBox * )
               (var.m_pUnknown);
         if(pcombo != NULL)
         {
            UINT uiDevs = midiOutGetNumDevs();
            MIDIOUTCAPS moc;
      
            WString wstr;
            wstr.LoadString(IDS_MIDIMAPPER);
            pcombo->m_wstra.Add(wstr);
            pcombo->m_dwaData.Add(MIDI_MAPPER);

   
            MMRESULT mmrc;
            for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
            {
               if(MMSYSERR_NOERROR == (mmrc = midiOutGetDevCaps(uiDev, &moc, sizeof(moc))))
		         {
                  International::ACPToUnicode(wstr, moc.szPname);
                  pcombo->m_wstra.Add(wstr);
                  pcombo->m_dwaData.Add(uiDev);
		         }
            }
            return true;
         }
      }
   }
   return VmsDataServerInterface::GetData(
      key,
      iLine,
      iColumn,
      var);
}
