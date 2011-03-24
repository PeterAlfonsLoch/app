#pragma once

class MixerVisualCentral;

namespace mixeruserbase
{

   class CLASS_DECL_ca application_interface :
      virtual public ::mixer::application_interface
   {
   protected:
      MixerVisualCentral *   m_pvisualcentral;
   public:
      application_interface();
      virtual ~application_interface();

      MixerVisualCentral & GetMixerVisualCentral();

      void on_application_signal(::ca::application::signal_object * pobj);

   };

} // namespace mixeruserbase