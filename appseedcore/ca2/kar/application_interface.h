#pragma once

namespace kar
{

   class CLASS_DECL_ca application_interface :
      virtual public ::ca::application_interface
   {
   public:
      void on_application_signal(::ca::application::signal_object * pobj);
   };


} // namespace kar