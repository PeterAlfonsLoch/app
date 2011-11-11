#include "StdAfx.h"


namespace musctrl
{

   MusicalPlayerCentralContainer::MusicalPlayerCentralContainer()
   {
      m_pmusicalplayercentral = NULL;
   }

   bool MusicalPlayerCentralContainer::Initialize(::ca::application * papp)
   {
      set_app(papp);
      if((m_pmusicalplayercentral = new MusicalPlayerCentral(get_app())) == NULL)
         throw new memory_exception;
      return true;
   }


   MusicalPlayerCentralContainer::~MusicalPlayerCentralContainer()
   {
      delete m_pmusicalplayercentral;
   }


   MusicalPlayerCentral & MusicalPlayerCentralContainer::GetMusicalPlayerCentral()
   {
      return *m_pmusicalplayercentral;
   }

   MusicalPlayerCentral & MusicalPlayerCentralContainer::AppGetMusicalPlayerCentral(::ca::application * papp)
   {
      return (dynamic_cast < MusicalPlayerCentralContainer * > (papp))->GetMusicalPlayerCentral();
   }

} // namespace musctrl