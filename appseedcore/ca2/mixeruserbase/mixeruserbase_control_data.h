#pragma once


#include "mixer/MixerCallback.h"


namespace mixeruserbase
{

   class control_view;


   class CLASS_DECL_ca control_data :
      public mixer::MixerCallback,
      virtual public ::radix::object
   {
   public:


      Mixer *              m_pmixer;
      MixerDestination *   m_pdestination;
      control_view *       m_pview;


      control_data(control_view * pview);
      virtual ~control_data(void);

      
      bool Initialize(void);


      MMRESULT SetNewDestination(DWORD dwComponentType);
      MMRESULT SetNewDevice(UINT uiMixerID);

      MixerDestination * GetDestination();
      Mixer * GetMixer();

      mixer::LevelControl * CreateLevelControl(void);
      mixer::toggle_control * CreateToggleControl(void);
      mixer::label * CreateLabel(void);

   };


} // namespace mixeruserbase


