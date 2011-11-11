#include "StdAfx.h"

namespace mus
{

   midi_central_container::midi_central_container()
   {
      m_pmidicentral = NULL;
   }

   bool midi_central_container::initialize_central_container(::ca::application * papp)
   {
      m_papp = papp;
      m_pmidicentral = new midi_central(papp);
      if(m_pmidicentral == NULL)
      {
         TRACE("could not construct midi_central: memory_exception?");
         return false;
      }
      if(!m_pmidicentral->Initialize(this))
      {
         TRACE("could not Initialize midi_central");
         return false;
      }
      return true;
   }

   midi_central_container::~midi_central_container()
   {
      delete m_pmidicentral;
   }

   midi_central & midi_central_container::GetMidiCentral()
   {
      return *m_pmidicentral;
   }

   midi_central & midi_central_container::AppGetMidiCentral(::ca::application * papp)
   {
      return (dynamic_cast < midi_central_container * > (papp))->GetMidiCentral();
   }


} // namespace mus