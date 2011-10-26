#include "StdAfx.h"

midi_central_listener::midi_central_listener()
{
   m_pmidicentral = NULL;
}

midi_central_listener::midi_central_listener(midi_central * pcentral)
{
   m_pmidicentral = NULL;
   SetMidiCentral(pcentral);
}

midi_central_listener::~midi_central_listener()
{
   m_pmidicentral->RemoveListener(this);
}

void midi_central_listener::OnAttributeChange(mus::e_midi_central_attribute eattribute)
{
   UNREFERENCED_PARAMETER(eattribute);
}

void midi_central_listener::OnAttributeChange(int iAttribute)
{
   OnAttributeChange((mus::e_midi_central_attribute) iAttribute);
}

void midi_central_listener::SetMidiCentral(midi_central *pcentral)
{
   if(m_pmidicentral != NULL)
   {
      m_pmidicentral->RemoveListener(this);
   }
   m_pmidicentral = pcentral;
   pcentral->AddListener(this);
}
