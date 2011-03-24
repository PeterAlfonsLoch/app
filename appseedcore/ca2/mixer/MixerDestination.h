#pragma once

class MixerDevice;

class CLASS_DECL_ca MixerDestination :
   public MixerSource
{
public:
   MixerDestination(::ca::application * papp);
   MixerDestination(const MixerDestination & destination);
   virtual ~MixerDestination();
public:
   DWORD GetComponentType();
   void SendOnChangeAllControls();
   MMRESULT GetAllControls();
   MMRESULT GetSourcesInfo();
   
   MixerSourceArray & GetSources();
   void operator delete(void *);

   MixerDestination & operator = (const MixerDestination & device);

   MixerDevice * GetDevice();
   void SetDevice(MixerDevice * pdevice);
    //string         m_strComponent;
protected:
   MixerDevice *  m_pdevice;
   MixerSourceArray  m_mixersourcea; 
};

class MixerDestinationArray :
   public array_app_alloc <MixerDestination, MixerDestination &>
{
public:
};
