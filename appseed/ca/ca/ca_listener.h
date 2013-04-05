#pragma once

namespace ca
{

   class CLASS_DECL_ca listener :
      virtual public base_object
   {
   public:

      virtual void on_delete(sp(::ca::ca) pca);
   };

}// namespace ca
