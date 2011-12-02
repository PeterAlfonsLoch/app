#pragma once


namespace cube5
{


   class CLASS_DECL_ca application :
      virtual public command::application
   {
   public:


      application();
      virtual ~application();


   };

   inline application & app_cast(::ax::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace cube4


