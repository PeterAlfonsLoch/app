#pragma once

#include "mixer/MixerCallback.h"

class MixerControlView;


class MixerControlData :
   public mixer::MixerCallback,
   virtual public ::radix::object
{
public:
   MixerControlData(MixerControlView * pview);

protected:
   Mixer            * m_pmixer;
   MixerDestination * m_pdestination;

public:
   MixerControlView * m_pview;
   MMRESULT SetNewDestination(DWORD dwComponentType);
   MMRESULT SetNewDevice(UINT uiMixerID);

   MixerDestination * GetDestination();
   Mixer * GetMixer();

   mixer::LevelControl * CreateLevelControl(void);
   mixer::toggle_control * CreateToggleControl(void);
   mixer::label * CreateLabel(void);

public:
   virtual ~MixerControlData(void);
public:
   bool Initialize(void);
};
