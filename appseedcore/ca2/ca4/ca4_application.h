#pragma once

namespace ca4
{

   class CLASS_DECL_ca application :
      virtual public colorertake5::application,
      virtual public ::ca::interface_application < sockets::application_interface >
   {
   public:


      application();
      virtual ~application();

      virtual bool base_support();

      virtual bool initialize();
      virtual int exit_instance();

      DECL_GEN_SIGNAL(on_application_signal);


   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca