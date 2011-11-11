#include "StdAfx.h"

namespace kar
{

   void application_interface::on_application_signal(::radix::application_signal_object * pobj)
   {
      if(pobj->m_esignal == ::ca::application_signal_initialize1)
      {
         if(App(get_app()).is_system())
         {
            System.factory().cloneable_large < LyricViewLine > ();
         }
      }
   }

} // namespace kar