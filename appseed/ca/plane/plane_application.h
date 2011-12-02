#pragma once
   

namespace plane
{


   class CLASS_DECL_ca application :
      virtual public ::netnode::application
   {
   public:


      application();
      virtual ~application();



   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace plane

