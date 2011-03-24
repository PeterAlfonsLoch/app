#pragma once

class CMixer;
class CMixerDestination;
class CMixerThread;

namespace mix
{
   enum EIds
   {
      IdsMuteAll,
      IdsMute
   };
} // namespace mix

class CLASS_DECL_ca MixerCentral :
   public ::user::interaction
{
public:
   MixerCentral(::ca::application * papp);

   bool Initialize();
    static void SetMixerCentral(MixerCentral * pmixercentral);
   virtual ~MixerCentral();

   afx_msg void OnClose();
};

