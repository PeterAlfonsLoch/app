#include "StdAfx.h"

namespace kar
{

   void application_interface::on_application_signal(::ca::application::signal_object * pobj)
   {
      if(pobj->m_esignal == ::ca::application::signal_initialize1)
      {
         System.factory().cloneable_large < LyricViewLine > ();
      }
   }

} // namespace kar