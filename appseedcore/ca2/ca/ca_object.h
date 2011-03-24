#pragma once

namespace ca
{

   class CLASS_DECL_ca object :
      virtual public ::ca::ca
   {
   public:

      object();
      object(const object & o);
      object & operator = (const object & o);
      virtual ~object();

      virtual void delete_this();

   };

}


