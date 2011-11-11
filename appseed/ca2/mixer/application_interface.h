#pragma once

namespace mixer
{

   class CLASS_DECL_ca application_interface :
      virtual public ::ca::application_interface
   {
   public:
      void on_application_signal(::radix::application_signal_object * pobj);
   };

} // namespace mixguserbase