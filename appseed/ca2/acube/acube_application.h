#pragma once


namespace acube
{


   class CLASS_DECL_ca application : 
      public ::cube8::application
   {
   public:
      application();
      virtual ~application();

      ::ax::application * get_system();

   };


   inline application & app_cast(::ax::application * papp)
   {
      return *(dynamic_cast < application * > (papp));
   }


} // namespace cube


