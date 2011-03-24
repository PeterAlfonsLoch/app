#pragma once

namespace acube
{

   class CLASS_DECL_CA2_CUBE application : 
      public ::icube::application
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