#pragma once

namespace ca
{

   // in would be unuseful to virtually derive this class:
   // the signal would be called only once throw on_application_signal
   class CLASS_DECL_ca application_interface :
      virtual public gen::signalizable
   {
   public:
      application_interface();

   };

   template < class IFACE >
   class interface_application :
      virtual public IFACE
   {
   public:


      interface_application();

      void on_signal(gen::signal_object * pobj)
      {
         SCAST_PTR(::radix::application_signal_object, papplicationsignal, pobj);
         // should implement the following function in IFACE, even if is_empty
         // void on_application_signal(::radix::application_signal_object * papplicationsignal);
         on_application_signal(papplicationsignal);
      }


   };



} // namespace mixeruserbase


