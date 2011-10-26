#pragma once


namespace mixeruserbase
{


   class central;


   class CLASS_DECL_ca application_interface :
      virtual public ::mixer::application_interface
   {
   public:


      central *   m_pcentral;


      application_interface();
      virtual ~application_interface();

      
      central & get_mixeruserbase_central();

      void on_application_signal(::radix::application_signal_object * pobj);

   };


} // namespace mixeruserbase

