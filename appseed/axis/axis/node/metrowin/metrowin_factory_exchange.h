#pragma once

namespace metrowin
{

   class CLASS_DECL_AXIS factory_exchange :
      virtual public ::object
   {
   public:
      factory_exchange(::axis::application * papp);
      virtual ~factory_exchange();
   };

} // namespace metrowin