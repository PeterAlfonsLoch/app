#pragma once

namespace imedia
{

   class CLASS_DECL_ca position_array :
      virtual public numeric_array < position >
   {
   public:
      position_array();
      position_array(const position_array & base_array);
   };

   class CLASS_DECL_ca position_2darray :
      public array_ptr_alloc < position_array , const position_array & >
   {
   };

} // namespace imedia