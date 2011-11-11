#pragma once

class MixerDestination;
class MixerDevice;

class CLASS_DECL_ca MixerSource :
   virtual public ::radix::object
{
public:
   MixerSource(::ca::application * papp);
   MixerSource(MixerSource & source);
   virtual ~MixerSource();


public:

   MMRESULT mixerGetLineInfo(DWORD dwSource, DWORD dwDestination, DWORD fdwInfo);
   MMRESULT mixerGetLineInfo(DWORD dwSource, MixerDestination * pdestination);

   DWORD GetLineID();
   const char * GetSZName();
   void SendOnChangeAllControls();
   MIXERLINECONTROLS & GetMixerLineControls();
   MIXERLINE & GetMixerLine();
   MixerControlArray & _GetControls();

   MixerDevice * GetDevice();

   void SetDestination(MixerDestination * pdestination);
   MixerDestination * GetDestination();

   void OnMixerLineChange();
   //void OnArrayReallocation(void *pNewPointer);
   //MMRESULT GetControl(DWORD dwControlType, DWORD dwControlFlags, MixerControl ** ppControl);
   MMRESULT GetLineControls();

   inline bool HasV001Controls();

   MixerSource & operator = (const MixerSource & source);
   bool                m_bHasV001Controls;

   MixerControlArray    m_mixercontrola;
   MIXERLINE            m_mixerline;
   MIXERLINECONTROLS    m_mixerlinecontrols;
protected:
   MixerDestination *   m_pdestination;
};




class MixerSourceArray :
   public array_app_alloc <MixerSource, MixerSource &>
{
public:
};
