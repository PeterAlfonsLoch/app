#pragma once

namespace fs
{

   class CLASS_DECL_ca application :
      virtual public ca8::application
   {
   public:




      application();
      virtual ~application();

      bool initialize();


   };

} // namespace fs