#include "StdAfx.h"
#include "MixerCallback.h"

namespace mixer
{

MixerCallback::MixerCallback(void)
{
}

MixerCallback::~MixerCallback(void)
{
}

LevelControl * MixerCallback::CreateLevelControl(void)
{
   return NULL;
}

toggle_control * MixerCallback::CreateToggleControl(void)
{
   return NULL;
}

label * MixerCallback::CreateLabel(void)
{
   return NULL;
}

} // namespace mixer