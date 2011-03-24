#include "StdAfx.h"

namespace mixer
{

   void application_interface::on_application_signal(::ca::application::signal_object * pobj)
   {
      if(pobj->m_esignal == ::ca::application::signal_initialize1)
      {
         System.factory().creatable_small < MixerDestination > ();
         System.factory().creatable_small < MixerSource > ();
         System.factory().creatable_small < MixerControl > ();
      }
   }

} // namespace mixeruserbase