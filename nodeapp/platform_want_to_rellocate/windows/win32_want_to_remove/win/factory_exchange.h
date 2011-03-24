#pragma once

namespace win
{

   class CLASS_DECL_VMSWIN factory_exchange :
      virtual public base_object
   {
   public:
      factory_exchange(::ca::application * papp);
	   virtual ~factory_exchange();
   };

} // namespace win