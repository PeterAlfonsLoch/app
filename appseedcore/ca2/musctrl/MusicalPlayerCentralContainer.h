#pragma once

namespace musctrl
{

   class MusicalPlayerCentral;

   class CLASS_DECL_ca MusicalPlayerCentralContainer :
      virtual public ::radix::object
   {
   public:
      MusicalPlayerCentralContainer();
      virtual ~MusicalPlayerCentralContainer();

   protected:
      MusicalPlayerCentral *   m_pmusicalplayercentral;
   public:

      bool Initialize(::ca::application * papp);

      static MusicalPlayerCentral & AppGetMusicalPlayerCentral(::ca::application * papp);

      inline MusicalPlayerCentral & GetMusicalPlayerCentral();

   };


} // namespace musctrl
