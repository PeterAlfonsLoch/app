#include "StdAfx.h"

MixerDestination::MixerDestination(::ca::application * papp) :
   ca(papp),
   MixerSource(papp)
{
   m_mixersourcea.set_app(papp);
   m_pdevice = NULL;
   m_pdestination = this;
}

MixerDestination::MixerDestination(const MixerDestination & destination) :
   ::ca::ca(((MixerDestination &) destination).get_app()),
   MixerSource(((MixerDestination &)destination).get_app())
{
   m_mixersourcea.set_app(((MixerDestination &)destination).get_app());
   operator =(destination);
}

MixerDestination::~MixerDestination()
{
//    Carray<MixerSource, MixerSource &>::~Carray<MixerSource, MixerSource &>();
    //CMixerLine::~CMixerLine();
}

void MixerDestination::operator delete(void *it)
{
    ((MixerDestination *) it)->~MixerDestination();
    free(it);
    
}

MMRESULT MixerDestination::GetSourcesInfo()
{
   MixerSource *     lpSource;

   int iConnections = (int) m_mixerline.cConnections;

   m_mixersourcea.set_size(iConnections);

   for (int i = 0; i < iConnections; i++)
   {
      lpSource = m_mixersourcea.ptr_at(i);
      lpSource->SetDestination(this);
      lpSource->mixerGetLineInfo(i, this);
   }
   return MMSYSERR_NOERROR;
}

MMRESULT MixerDestination::GetAllControls()
{
   GetLineControls();
   
   MixerSourceArray & sourcea = m_mixersourcea;
   
   for(int i = 0; i < sourcea.get_size(); i++)
   {
      sourcea[i].GetLineControls();
   }
   return true;
}

void MixerDestination::SendOnChangeAllControls()
{
   MixerSource::SendOnChangeAllControls();
   MixerSourceArray & sourcea = m_mixersourcea;
   
   for(int i = 0; i < sourcea.get_size(); i++)
   {
      sourcea[i].SendOnChangeAllControls();
   }
}


MixerDestination & MixerDestination::operator = (const MixerDestination & destination)
{
   m_pdevice = destination.m_pdevice;
   return *this;
}

DWORD MixerDestination::GetComponentType()
{
   return m_mixerline.dwComponentType;
}


MixerDevice * MixerDestination::GetDevice()
{
   return m_pdevice;
}

void MixerDestination::SetDevice(MixerDevice * pdevice)
{
   m_pdevice = pdevice;
}

MixerSourceArray & MixerDestination::GetSources()
{
   return m_mixersourcea;
}
