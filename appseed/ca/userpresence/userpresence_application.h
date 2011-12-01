#pragma once


namespace userpresence
{


   class CLASS_DECL_ca application :
      virtual public ::simpleuser::application,
      virtual public ::userpresence::user::presence_central_container
   {
   public:

      application();
      virtual ~application();

      virtual bool initialize();
      virtual bool finalize();


      virtual void defer_initialize_user_presence();
      virtual void defer_finalize_user_presence();


   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace userpresence