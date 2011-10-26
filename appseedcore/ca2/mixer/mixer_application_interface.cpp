#include "StdAfx.h"

namespace mixer
{

   void application_interface::on_application_signal(::radix::application_signal_object * pobj)
   {
      if(pobj->m_esignal == ::ca::application_signal_initialize1)
      {
         System.factory().creatable_small < MixerDestination > ();
         System.factory().creatable_small < MixerSource > ();
         System.factory().creatable_small < MixerControl > ();
      }
   }

} // namespace mixeruserbase