#pragma once

class midi_central;

namespace mus
{

   class CLASS_DECL_ca midi_central_container :
      virtual public ::radix::object
   {
   public:
      midi_central_container();
      virtual ~midi_central_container();

   protected:
      midi_central *   m_pmidicentral;
   public:

      bool initialize_central_container(::ca::application * papp);

      static inline midi_central & AppGetMidiCentral(::ca::application * papp);

      inline midi_central & GetMidiCentral();

   };


} // namespace mus
