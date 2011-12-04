#pragma once


namespace acube
{


   class CLASS_DECL_ca2 application : 
      virtual public ::plane::application
   {
   public:
      application();
      virtual ~application();

      ::ca::application * get_system();

   };


   inline application & app_cast(::ca::application * papp)
   {
      return *(dynamic_cast < application * > (papp));
   }


} // namespace cube


