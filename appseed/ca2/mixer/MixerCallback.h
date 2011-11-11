#pragma once

namespace mixer
{

   class LevelControl;
   class toggle_control;
   class label;

class CLASS_DECL_ca MixerCallback
{
public:
   MixerCallback(void);
public:
   virtual ~MixerCallback(void);
public:
   virtual LevelControl * CreateLevelControl(void);
   virtual toggle_control * CreateToggleControl(void);
   virtual label * CreateLabel(void);
};


} // namespace mixer