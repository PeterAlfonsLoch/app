#pragma once


namespace cube5
{


   class CLASS_DECL_ca2 application :
      virtual public command::application
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


