#pragma once

namespace ca5
{

   class CLASS_DECL_ca application :
      virtual public ::userbase::application,
      virtual public ::ca5::user::presence_central_container
   {
   public:

      application();
      virtual ~application();

      virtual bool initialize();


      virtual void defer_initialize_user_presence();


   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca5