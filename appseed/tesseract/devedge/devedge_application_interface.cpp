#include "StdAfx.h"

namespace devedge
{

   application_interface::application_interface()
   {
   }

   application_interface::~application_interface()
   {
   }

   void application_interface::on_application_signal(::radix::application_signal_object * pobj)
   {
      if(pobj->m_esignal == ::ca::application_signal_initialize1)
      {
         System.factory().creatable_small < document > ();
         System.factory().creatable_small < devedge_child_frame > ();
         System.factory().creatable_small < view > ();
         System.factory().creatable_small < MainDoc > ();
         System.factory().creatable_small < main_frame > ();
         System.factory().creatable_small < devedge::pane_view > ();
      }
   }


} // namespace devedge