#include "StdAfx.h"

CMidiCentralListener::CMidiCentralListener()
{
   m_pmidicentral = NULL;
}

CMidiCentralListener::CMidiCentralListener(midi_central * pcentral)
{
   m_pmidicentral = NULL;
   SetMidiCentral(pcentral);
}

CMidiCentralListener::~CMidiCentralListener()
{
   m_pmidicentral->RemoveListener(this);
}

void CMidiCentralListener::OnAttributeChange(mus::EMidiCentralAttribute eattribute)
{
   UNREFERENCED_PARAMETER(eattribute);
}

void CMidiCentralListener::OnAttributeChange(int iAttribute)
{
   OnAttributeChange((mus::EMidiCentralAttribute) iAttribute);
}

void CMidiCentralListener::SetMidiCentral(midi_central *pcentral)
{
   if(m_pmidicentral != NULL)
   {
      m_pmidicentral->RemoveListener(this);
   }
   m_pmidicentral = pcentral;
   pcentral->AddListener(this);
}
