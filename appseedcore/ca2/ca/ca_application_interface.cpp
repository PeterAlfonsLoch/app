#include "StdAfx.h"

namespace ca
{

   application_interface::application_interface()
   {
      set_app(dynamic_cast < ::ca::application_interface * > (this)->get_app());
      // some ca2 verses that reversely, directly or both sings the assignment identity above:
      // application_interface assumes that a module that depends on the module that
      // has an application_interface that derives from this application_interface,
      // can get the application_interface of that module by dynamic-casting the application object.
   }

   /* template for application_interface implementation
   void application_interface::on_application_signal(::ca::application::signal_object * psignal)
   {
   }
   */

} // namespace kar