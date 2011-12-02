#pragma once

namespace fs
{

   class CLASS_DECL_ca application :
      virtual public ::simpleuser::application
   {
   public:




      application();
      virtual ~application();

      bool initialize();


   };

} // namespace fs