#pragma once


namespace cube4
{


   class CLASS_DECL_ca application :
      virtual public ::fontopus::application
   {
   public:


      application();
      virtual ~application();


   };


   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace cube4


