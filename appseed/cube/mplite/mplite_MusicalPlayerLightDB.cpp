#include "StdAfx.h"
#include "MusicalPlayerLightDB.h"


MusicalPlayerLightDB::MusicalPlayerLightDB(::ca::application * papp) :
   ca(papp)
{

}

MusicalPlayerLightDB::~MusicalPlayerLightDB()
{

}

bool MusicalPlayerLightDB::data_server_save(
   ::database::id idSection, 
   ::database::id id, 
   ::database::id idIndex,
   var & var, ::database::update_hint * puh)
{
   return ::database::server::data_server_save(
      idSection,
      id,
      idIndex,
      var, 
      puh);
}


bool MusicalPlayerLightDB::data_server_load(
   ::database::id idSection, 
   ::database::id id, 
   ::database::id idIndex,
   var & var, ::database::update_hint * puh)
{
   if(id == "WaveInDevices")
   {
      ASSERT(var.get_type() == var::type_ca2);
      if(var.get_type() == var::type_ca2)
      {
//         Ex1FormInterfaceComboBox * pcombo =
  //          dynamic_cast < Ex1FormInterfaceComboBox * >
    //           (var.m_pUnknown);
         Ex1FormInterfaceComboBox * pcombo =
            dynamic_cast < Ex1FormInterfaceComboBox * > (var.m_pca2);
         if(pcombo != NULL)
         {
            UINT uiDevs = waveInGetNumDevs();
            WAVEINCAPS moc;
      
            string str;
            throw not_implemented_exception();
            //str.load_string(IDS_WAVEMAPPER);
            pcombo->m_wstra.add(str);
            pcombo->m_dwaData.add(WAVE_MAPPER);

   
            MMRESULT mmrc;
            for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
            {
               if(MMSYSERR_NOERROR == (mmrc = waveInGetDevCaps(uiDev, &moc, sizeof(moc))))
               {
//                  gen::international::ACPToUnicode(str, moc.szPname);
                  pcombo->m_wstra.add(str);
                  pcombo->m_dwaData.add(uiDev);
               }
            }
            return true;
         }
      }
   }
   else if(id == "MidiOutDevices")
   {
      ASSERT(var.get_type() == var::type_ca2);
      if(var.get_type() == var::type_ca2)
      {
//         Ex1FormInterfaceComboBox * pcombo =
  //          dynamic_cast < Ex1FormInterfaceComboBox * >
    //           (var.m_pUnknown);
         Ex1FormInterfaceComboBox * pcombo =
            dynamic_cast < Ex1FormInterfaceComboBox * >
               (var.m_pca2);
         if(pcombo != NULL)
         {
            UINT uiDevs = midiOutGetNumDevs();
            MIDIOUTCAPS moc;
      
            string str;
            throw not_implemented_exception();
//            str.load_string(IDS_MIDIMAPPER);
            pcombo->m_wstra.add(str);
            pcombo->m_dwaData.add(MIDI_MAPPER);

   
            MMRESULT mmrc;
            for(UINT uiDev = 0; uiDev < uiDevs; uiDev++)
            {
               if(MMSYSERR_NOERROR == (mmrc = midiOutGetDevCaps(uiDev, &moc, sizeof(moc))))
               {
//                  gen::international::ACPToUnicode(str, moc.szPname);
                  pcombo->m_wstra.add(str);
                  pcombo->m_dwaData.add(uiDev);
               }
            }
            return true;
         }
      }
   }
   return ::database::server::data_server_load(
      idSection,
      id,
      idIndex,
      var,
      puh);
}
